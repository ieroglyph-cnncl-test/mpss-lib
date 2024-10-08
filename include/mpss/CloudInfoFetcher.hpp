#pragma once

#include "../mpssexport.hpp"
#include "ICloudInfoFetcher.hpp"

#include "ContentDownloader.hpp"

#include <memory>

namespace mpss {

class MPSS_EXPORT CloudInfoFetcher : public ICloudInfoFetcher
{
public:
    CloudInfoFetcher(std::unique_ptr<IContentDownloader> &&loader);

    /// @brief Fetches the content of the file from the API
    void fetchInfo() override;

    /// @brief Returns a list of all currently supported Ubuntu releases.
    /// @return A vector of string
    [[nodiscard]] std::vector<std::string> getSupportedReleases() override;

    /// @brief Returns the current Ubuntu LTS version.
    /// @return A string
    [[nodiscard]] std::string getCurrentLtsRelease() override;

    /// @brief Return the sha256 of the disk1.img item of a given Ubuntu release.
    /// @return A string
    [[nodiscard]] std::string getSha256(std::string_view releaseName) override;

    virtual ~CloudInfoFetcher();

private:
    // A bit of pimpl idiom to hold temp data, simplify compability on changes
    class CloudInfoFetcherImpl;
    std::unique_ptr<CloudInfoFetcherImpl> _content{};
};
} // namespace mpss
