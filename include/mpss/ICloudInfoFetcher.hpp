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
    /// @return An optional with a vector of string
    [[nodiscard]] virtual std::vector<std::string> getSupportedReleases() = 0;

    /// @brief Returns the current Ubuntu LTS version.
    /// @return An optional with a string
    [[nodiscard]] virtual std::string getCurrentLtsRelease() = 0;

    /// @brief Return the sha256 of the disk1.img item of a given Ubuntu release.
    /// @return An optional with a string
    [[nodiscard]] virtual std::string getSha256(std::string_view releaseName) = 0;

    virtual ~ICloudInfoFetcher() = default;
};
} // namespace mpss