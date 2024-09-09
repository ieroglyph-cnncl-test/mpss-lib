#include <catch2/catch_test_macros.hpp>
#include <iostream>
#include <memory>

#include "TestContentDownloader.hpp"
#include "mpss/CloudInfoFetcher.hpp"
#include "mpss/ContentDownloader.hpp"

namespace {
constexpr auto RealJsonUrl{
    "https://cloud-images.ubuntu.com/releases/streams/v1/com.ubuntu.cloud:released:download.json"
};
constexpr auto UnrealJsonUrl{ "https://best.jsons.out.there/top1.json" };
constexpr auto ExpectedCurrentLtsRelease{ "ubuntu-noble-24.04-amd64-server-20240821" };
constexpr auto ExpectedSha256{ "0e25ca6ee9f08ec5d4f9910054b66ae7163c6152e81a3e67689d89bd6e4dfa69" };
} // namespace

TEST_CASE("Sanity test")
{
    REQUIRE(2 * 2 == 4);
}

TEST_CASE("Real content downloader downloads content", "[requires-connection]")
{
    const mpss::ContentDownloader cd{ ::RealJsonUrl };
    try {
        const auto content = cd.getContent();
        REQUIRE(!content.empty());
    } catch (const std::runtime_error &err) {
        std::cout << err.what();
    }
}

TEST_CASE("Real content downloader throws when failed to download", "[requires-connection]")
{
    REQUIRE_THROWS([] {
        const mpss::ContentDownloader cd{ ::UnrealJsonUrl };
        const auto content = cd.getContent();
    }());
}

TEST_CASE("With error during fetching info the exception is thrown")
{
    REQUIRE_THROWS([] {
        std::unique_ptr<mpss::IContentDownloader> cd =
                std::make_unique<mpss::AlwaysThrowingContentDownloader>();
        std::unique_ptr<mpss::ICloudInfoFetcher> fetcher =
                std::make_unique<mpss::CloudInfoFetcher>(std::move(cd));
        fetcher->fetchInfo();
    }());
}

TEST_CASE("With normal content loader no exceptions happen")
{
    REQUIRE_NOTHROW([] {
        std::unique_ptr<mpss::IContentDownloader> cd =
                std::make_unique<mpss::DemoDataContentDownloader>();
        std::unique_ptr<mpss::ICloudInfoFetcher> fetcher =
                std::make_unique<mpss::CloudInfoFetcher>(std::move(cd));
        fetcher->fetchInfo();
    }());
}

TEST_CASE("Testing on demo data")
{
    std::unique_ptr<mpss::IContentDownloader> cd =
            std::make_unique<mpss::DemoDataContentDownloader>();
    std::unique_ptr<mpss::ICloudInfoFetcher> fetcher =
            std::make_unique<mpss::CloudInfoFetcher>(std::move(cd));
    fetcher->fetchInfo();

    SECTION("Testing current lts release")
    {
        const auto currentLtsRelease{ fetcher->getCurrentLtsRelease() };
        REQUIRE(currentLtsRelease == ExpectedCurrentLtsRelease);
    }

    SECTION("Testing supported releases")
    {
        const auto supportedReleases{ fetcher->getSupportedReleases() };
        REQUIRE(supportedReleases.size() == 2);
        REQUIRE(supportedReleases[0] != ExpectedCurrentLtsRelease);
        REQUIRE(supportedReleases[1] == ExpectedCurrentLtsRelease);
    }

    SECTION("Testing existing sha256")
    {
        const auto sha256{ fetcher->getSha256(ExpectedCurrentLtsRelease) };
        REQUIRE(sha256 == ExpectedSha256);
    }

    SECTION("Testing non existing sha256")
    {
        REQUIRE_THROWS_AS(
                [&fetcher] {
                    const auto sha256{ fetcher->getSha256("Some random string") };
                }(),
                std::runtime_error);
    }
}
