#include <catch2/catch_test_macros.hpp>
#include <iostream>

#include "ContentDownloader.hpp"

TEST_CASE("Sanity test")
{
    REQUIRE(2 * 2 == 4);
}

TEST_CASE("Content downloader downloads content")
{
    const mpss::ContentDownloader cd;
    try {
        const auto content = cd.getContent();
        REQUIRE(!content.empty());
    } catch (const std::runtime_error &err) {
        std::cout << err.what();
    }
}

TEST_CASE("With Fake Content downloader we should get an exception") { }