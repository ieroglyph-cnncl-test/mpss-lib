#pragma once

#include <string>
#include <string_view>

namespace mpss {

using std::string;
using std::string_view;

class IContentDownloader
{
public:
    [[nodiscard]] virtual string getContent() const = 0;

    virtual ~IContentDownloader() {};
};

class ContentDownloader : public IContentDownloader
{
public:
    ContentDownloader(string url);
    [[nodiscard]] string getContent() const override;

private:
    string _url;
};

} // namespace mpss