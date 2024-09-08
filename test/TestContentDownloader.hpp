#pragma once

#include <exception>
#include <string>
#include <string_view>

namespace mpss {

using std ::string;
using std::string_view;

class TestContentDownloader
{
public:
    string getContent(string_view url)
    {
        throw std::runtime_error("Always throws");
    }
};

} // namespace mpss