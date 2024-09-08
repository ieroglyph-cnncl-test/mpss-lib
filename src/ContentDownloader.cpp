#include "ContentDownloader.hpp"

#include <cpr/cpr.h>
#include <exception>
#include <string>

namespace {
constexpr int StatusCodeOk{ 200 };
constexpr auto ErrorMsgBadResponse{ "Cannot reach the file" };
} // namespace

namespace mpss {
string ContentDownloader::getContent(string_view url) const
{
    try {
        const auto r = cpr::Get(cpr::Url{ url });
        if (r.status_code != ::StatusCodeOk) {
            throw std::runtime_error(ErrorMsgBadResponse);
        }
        return r.text; // JSON text string
    } catch (const std::exception &e) {
        throw e;
    }
};
} // namespace mpss