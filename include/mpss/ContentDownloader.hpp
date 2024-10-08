#pragma once

#include "../mpssexport.hpp"

#include <string>
#include <string_view>

namespace mpss {

constexpr auto DefaultDataUrl{
    "https://cloud-images.ubuntu.com/releases/streams/v1/com.ubuntu.cloud:released:download.json"
};

using std::string;
using std::string_view;

class MPSS_EXPORT IContentDownloader
{
public:
    [[nodiscard]] virtual string getContent() const = 0;

    virtual ~IContentDownloader() = default;
};

class MPSS_EXPORT ContentDownloader : public IContentDownloader
{
public:
    ContentDownloader(string url = DefaultDataUrl);
    [[nodiscard]] string getContent() const override;

    virtual ~ContentDownloader();

private:
    string _url;
};

} // namespace mpss
