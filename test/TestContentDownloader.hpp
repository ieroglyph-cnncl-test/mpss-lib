#pragma once

#include "mpss/ContentDownloader.hpp"

#include <exception>
#include <string>
#include <string_view>

namespace mpss {

using std ::string;
using std::string_view;

class AlwaysThrowingContentDownloader : public IContentDownloader
{
public:
    [[nodiscard]] string getContent() const override
    {
        throw std::runtime_error("Always throws");
    }
};

class DemoDataContentDownloader : public IContentDownloader
{
public:
    [[nodiscard]] string getContent() const override
    {
        return
#include "longjson.hpp"
                ;
    }
};

} // namespace mpss