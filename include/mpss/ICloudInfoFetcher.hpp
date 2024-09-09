#pragma once

#include <optional>
#include <string>
#include <vector>

namespace mpss {
class ICloudInfoFetcher
{
public:
    /// @brief Fetches the content of the file from the API
    virtual void fetchInfo() = 0;

    /// @brief Returns a list of all currently supported Ubuntu releases.
    /// Only releases for amd64 are checked.
    /// Returns the latest versions of each supported release.
    /// Behaviour if the data isn't fetched yet depends on implementation.
    /// @return A vector of string
    /// @throws Can throw exceptions, depending on implementation
    [[nodiscard]] virtual std::vector<std::string> getSupportedReleases() = 0;

    /// @brief Returns the current Ubuntu LTS release.
    /// Includes the latest version of the current release.
    /// Behaviour if the data isn't fetched yet depends on implementation.
    /// @return A string
    /// @throws Can throw exceptions, depending on implementation
    [[nodiscard]] virtual std::string getCurrentLtsRelease() = 0;

    /// @brief Return the sha256 of the disk1.img item of a given Ubuntu release.
    /// Works only with currently supported releases.
    /// Expects to have the same format as the output of getSupportedReleases.
    /// Behaviour if the data isn't fetched yet depends on implementation.
    /// @param releaseName A std::string_view with release name, including version.
    /// @return An optional of string. A nullopt if no release is found.
    /// @throws Can throw exceptions, depending on implementation
    [[nodiscard]] virtual std::optional<std::string> getSha256(std::string_view releaseName) = 0;

    virtual ~ICloudInfoFetcher() = default;
};
} // namespace mpss