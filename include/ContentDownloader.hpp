#pragma once

#include <string>
#include <string_view>

namespace mpss {

using std::string;
using std::string_view;

class ContentDownloader
{
public:
    string getContent(string_view url) const;
};

} // namespace mpss