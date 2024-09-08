#include <catch2/catch_test_macros.hpp>
#include <iostream>
#include <memory>

#include "CloudInfoFetcher.hpp"
#include "ContentDownloader.hpp"

namespace {
constexpr auto RealJsonUrl{
    "https://cloud-images.ubuntu.com/releases/streams/v1/com.ubuntu.cloud:released:download.json"
};
constexpr auto UnrealJsonUrl{ "https://best.jsons.out.there/top1.json" };
} // namespace

TEST_CASE("Sanity test")
{
    REQUIRE(2 * 2 == 4);
}

TEST_CASE("Content downloader downloads content")
{
    const mpss::ContentDownloader cd{ ::RealJsonUrl };
    try {
        const auto content = cd.getContent();
        REQUIRE(!content.empty());
    } catch (const std::runtime_error &err) {
        std::cout << err.what();
    }
}

TEST_CASE("Content downloader throws when failed to download")
{
    REQUIRE_THROWS([] {
        const mpss::ContentDownloader cd{ ::UnrealJsonUrl };
        const auto content = cd.getContent();
    }());
}

TEST_CASE("With normal content loader we should be fine")
{
    std::unique_ptr<mpss::IContentDownloader> cd =
            std::make_unique<mpss::ContentDownloader>(::RealJsonUrl);
    std::unique_ptr<mpss::ICloudInfoFetcher> fetcher =
            std::make_unique<mpss::CloudInfoFetcher>(std::move(cd));
    fetcher->fetchInfo();
}