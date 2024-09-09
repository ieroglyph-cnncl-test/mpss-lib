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

template<typename DownloaderT>
auto makeFetcher()
{
    std::shared_ptr<mpss::IContentDownloader> cd = std::make_shared<DownloaderT>();
    std::unique_ptr<mpss::ICloudInfoFetcher> fetcher =
            std::make_unique<mpss::CloudInfoFetcher>(std::move(cd));
    return fetcher;
};

auto makeDemoFetcher = makeFetcher<mpss::DemoDataContentDownloader>;
auto makeThrowingFetcher = makeFetcher<mpss::AlwaysThrowingContentDownloader>;

} // namespace

TEST_CASE("Sanity test")
{
    REQUIRE(2 * 2 == 4);
}

TEST_CASE("Real content downloader downloads content", "[requires-connection]")
{
    SECTION("With directly specified url")
    {
        REQUIRE_NOTHROW([] {
            const mpss::ContentDownloader cd{ ::RealJsonUrl };
            try {
                const auto content = cd.getContent();
                REQUIRE(!content.empty());
            } catch (const std::runtime_error &err) {
                std::cout << err.what();
            }
        }());
    }

    SECTION("Without directly specified url")
    {
        REQUIRE_NOTHROW([] {
            const mpss::ContentDownloader cd{};
            try {
                const auto content = cd.getContent();
                REQUIRE(!content.empty());
            } catch (const std::runtime_error &err) {
                std::cout << err.what();
            }
        }());
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
        auto fetcher = makeThrowingFetcher();
        fetcher->fetchInfo();
    }());
}

TEST_CASE("With normal content loader no exceptions happen")
{
    REQUIRE_NOTHROW([] {
        auto fetcher = makeDemoFetcher();
        fetcher->fetchInfo();
    }());
}

TEST_CASE("Testing on demo data")
{
    auto fetcher = makeDemoFetcher();
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
        REQUIRE(sha256.has_value());
        REQUIRE(sha256.value() == ExpectedSha256);
    }

    SECTION("Testing non existing sha256")
    {
        const auto sha256{ fetcher->getSha256("Some random string") };
        REQUIRE(!sha256.has_value());
    }
}

TEST_CASE("Manual call to fetchInfo is not important")
{
    auto fetcher1 = makeDemoFetcher();
    auto fetcher2 = makeDemoFetcher();
    fetcher1->fetchInfo();

    REQUIRE_NOTHROW([&] {
        REQUIRE(fetcher1->getCurrentLtsRelease() == fetcher2->getCurrentLtsRelease());
    }());
}

TEST_CASE("There is no need for writing verbose types")
{
    using std::make_shared;
    using std::make_unique;
    auto loader = make_shared<mpss::DemoDataContentDownloader>();
    auto fetcher = make_unique<mpss::CloudInfoFetcher>(loader);

    const auto currentLtsRelease{ fetcher->getCurrentLtsRelease() };
    REQUIRE(currentLtsRelease == ExpectedCurrentLtsRelease);
}