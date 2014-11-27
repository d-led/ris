#pragma once

#include <utility>
#include <string>

namespace ris {
    /// mustache/ctemplate inspired
    template <typename TContext>
    class late {
        //{{\s*[#/^!>]?\s*([\w\.]+)\s*[\?]?\s*}}
        TContext&& context;
    public:
        late(TContext&& c) :context(std::forward<TContext>(c)) {}
    public:
        std::string render(std::string const& what) {
            return "";
        }
    };

    template <typename TString,typename TContext>
    std::string render(TString const& s,TContext&& c) {
        auto temp = late<TContext>(c);
        return temp.render(s);
    }
}
