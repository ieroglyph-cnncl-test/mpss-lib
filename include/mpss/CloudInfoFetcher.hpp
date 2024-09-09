#pragma once

#include "ICloudInfoFetcher.hpp"

#include "ContentDownloader.hpp"

#include <memory>

namespace mpss {

class CloudInfoFetcher : public ICloudInfoFetcher
{
public:
    CloudInfoFetcher(std::shared_ptr<IContentDownloader> loader);

    /// @brief Fetches the content of the file from the API
    /// The call to fetchInfo is not necessary, and if not called manually, will be performed
    /// automatically when first get* method is called.
    /// @throws Can throw std::runtime_error with details
    void fetchInfo() override;

    /// @brief Returns a list of all currently supported Ubuntu releases.
    /// Only releases for amd64 are checked.
    /// Returns the latest versions of each supported release.
    /// @return A vector of string
    /// @throws Can throw std::length_error if there is no enought memory to allocate for the
    /// result, or std::runtime_error if no fetchInfo was called before and it throws during this
    /// call.
    [[nodiscard]] std::vector<std::string> getSupportedReleases() override;

    /// @brief Returns the current Ubuntu LTS release.
    /// Includes the latest version of the current release.
    /// @return A string
    /// @throws Can throw std::runtime_error if no fetchInfo was called before and it throws during
    /// this call.
    [[nodiscard]] std::string getCurrentLtsRelease() override;

    /// @brief Return the sha256 of the disk1.img item of a given Ubuntu release.
    /// Works only with currently supported releases.
    /// Expects to have the same format as the output of getSupportedReleases.
    /// @param releaseName A std::string_view with release name, including version.
    /// @return An optional of string. A nullopt if no release is found.
    /// @throws Can throw std::runtime_error with details
    [[nodiscard]] std::optional<std::string> getSha256(std::string_view releaseName) override;

    virtual ~CloudInfoFetcher();

private:
    // A bit of pimpl idiom to hold temp data, simplifies compability on changes
    class CloudInfoFetcherImpl;
    std::unique_ptr<CloudInfoFetcherImpl> _content{};
};
} // namespace mpss