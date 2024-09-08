#include "CloudInfoFetcher.hpp"

namespace mpss {

namespace {
constexpr auto ContentLocation{
    "https://cloud-images.ubuntu.com/releases/streams/v1/com.ubuntu.cloud:released:download.json"
};
constexpr auto ContentIndexLocation{
    "https://cloud-images.ubuntu.com/releases/streams/v1/index.json"
};
} // namespace

CloudInfoFetcher::CloudInfoFetcher(std::unique_ptr<IContentDownloader> &&loader)
    : _loader{ std::move(loader) }
{
}

void CloudInfoFetcher::fetchInfo()
{
    _content = _loader->getContent();
}

std::vector<std::string> CloudInfoFetcher::getSupportedReleases() const
{
    return std::vector<std::string>();
}
std::string CloudInfoFetcher::getCurrentLtsRelease() const
{
    return std::string();
}

std::string CloudInfoFetcher::getSha256(std::string_view releaseName) const
{
    return std::string();
}
} // namespace mpss