#pragma once

#include "ContentDownloader.hpp"
#include "ICloudInfoFetcher.hpp"

namespace {
constexpr auto ContentLocation{
    "https://cloud-images.ubuntu.com/releases/streams/v1/com.ubuntu.cloud:released:download.json"
};
}

namespace mpss {
template<typename ContentDownloaderT = ContentDownloader>
class CloudInfoFetcher : public ICloudInfoFetcher
{
public:
    /// @brief Fetches the content of the file from the API
    [[nodiscard]] virtual void fetchInfo() = 0;

    /// @brief Returns a list of all currently supported Ubuntu releases.
    /// @return An optional with a vector of string
    [[nodiscard]] virtual std::vector<std::string> getSupportedReleases() const = 0;

    /// @brief Returns the current Ubuntu LTS version.
    /// @return An optional with a string
    [[nodiscard]] virtual std::string getCurrentLtsRelease() const = 0;

    /// @brief Return the sha256 of the disk1.img item of a given Ubuntu release.
    /// @return An optional with a string
    [[nodiscard]] virtual std::string getSha256(std::string_view releaseName) const = 0;

private:
    ContentDownloaderT _loader{};
};
} // namespace mpss