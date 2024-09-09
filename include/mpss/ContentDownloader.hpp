#pragma once

#include <string>
#include <string_view>

namespace mpss {

constexpr auto DefaultDataUrl{
    "https://cloud-images.ubuntu.com/releases/streams/v1/com.ubuntu.cloud:released:download.json"
};

using std::string;
using std::string_view;

/// @brief Defines interface for downloading the data
/// Can be used to perform dependency injection to CloudInfoFetcher.
/// Can be replaced by mock implementations for testing purposes
class IContentDownloader
{
public:
    /// @brief Implements retreiving the data on releases
    /// @return std::string containing the data
    [[nodiscard]] virtual string getContent() const = 0;

    virtual ~IContentDownloader() = default;
};

/// @brief The basic implementation of non-caching content downloader
class ContentDownloader : public IContentDownloader
{
public:
    /// @brief Constructs the downloaded object
    /// @param url
    explicit ContentDownloader(string url = DefaultDataUrl);

    [[nodiscard]] string getContent() const override;

    virtual ~ContentDownloader();

private:
    string _url;
};

} // namespace mpss