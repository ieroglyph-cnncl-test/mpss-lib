#include "mpss/CloudInfoFetcher.hpp"

#include <algorithm>
#include <fmt/format.h>
#include <map>
#include <nlohmann/json.hpp>

namespace mpss {

using std::map;
using std::string;
using std::vector;
using json = nlohmann::json;

// Struct to store the data we would actually need to perform the requests
struct ReleaseRecord
{
    string sha256;
};

class CloudInfoFetcher::CloudInfoFetcherImpl
{
public:
    explicit CloudInfoFetcherImpl(std::unique_ptr<IContentDownloader> &&loader)
        : loader(std::move(loader))
    {
    }
    std::unique_ptr<IContentDownloader> loader;
    map<string, ReleaseRecord> supportedReleases{};
    string currentLtsRelease{};
    bool isFetched{ false };
    ~CloudInfoFetcherImpl() = default;
};

CloudInfoFetcher::CloudInfoFetcher(std::unique_ptr<IContentDownloader> &&loader)
    : _content{ std::make_unique<CloudInfoFetcherImpl>(std::move(loader)) }
{
}

void CloudInfoFetcher::fetchInfo()
{
    _content->supportedReleases.clear();
    using namespace std::string_view_literals;
    try {
        const auto stringData{ _content->loader->getContent() };
        json data = json::parse(stringData);
        const auto products = data.find("products"sv);
        if (products == data.end())
            throw std::runtime_error("JSON schema error: object 'Products' not found");
        for (const auto &product : *products) {
            const auto isSupported{ product.at("supported"sv).template get<bool>() == true };
            const auto isArch{ product.at("arch"sv).template get<string>() == "amd64"sv };
            if (!isSupported || !isArch) continue;

            const auto curVersion = product.at("versions"sv).back();
            const auto pubname{ curVersion.at("pubname"sv).template get<string>() };
            const auto sha256{
                curVersion.at("items"sv).at("disk1.img"sv).at("sha256"sv).template get<string>()
            };
            _content->supportedReleases.insert({ pubname, { sha256 } });

            const auto aliases{ product.at("aliases"sv).template get<string>() };
            const auto isCurrentLts{ aliases.find("lts"sv) != string::npos };
            if (isCurrentLts) {
                _content->currentLtsRelease = pubname;
            }
        }
        _content->isFetched = true;
    } catch (const std::runtime_error &err) {
        throw err;
    } catch (const json::exception &e) {
        throw std::runtime_error(fmt::format("JSON exception: {}, id: {}", e.what(), e.id));
    }
}

std::vector<std::string> CloudInfoFetcher::getSupportedReleases()
{
    if (!_content->isFetched) fetchInfo();
    vector<string> ret;
    ret.reserve(_content->supportedReleases.size());
    for (const auto &[key, _] : _content->supportedReleases) {
        ret.push_back(key);
    }
    return ret;
}

std::string CloudInfoFetcher::getCurrentLtsRelease()
{
    if (!_content->isFetched) fetchInfo();
    return _content->currentLtsRelease;
}

std::string CloudInfoFetcher::getSha256(std::string_view releaseName)
{
    if (!_content->isFetched) fetchInfo();
    const auto ret = _content->supportedReleases.find(string(releaseName));
    if (ret == _content->supportedReleases.end()) {
        throw std::runtime_error("No records with release name");
    }
    return ret->second.sha256;
}

CloudInfoFetcher::~CloudInfoFetcher() = default;
} // namespace mpss