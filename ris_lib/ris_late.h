#pragma once

#include <utility>
#include <string>

namespace ris {
    /// mustache/ctemplate inspired
    template <typename TContext>
    class late {
        //{{\s*[#/^!>]?\s*([\w\.]+)\s*[\?]?\s*}}
        TContext&& context;
        std::string late_;
    public:
        late(std::string const& tmp,TContext&& c) :
            late_(tmp),
            context(std::forward<TContext>(c))
        {}
    public:
        template <typename TStream>
        void render(TStream& s) {
        }
    };

    template <typename TString,typename TContext,typename TStream>
    void render(TString const& tmp,TContext&& ctx,TStream& s) {
        auto temp = late<TContext>(tmp,ctx);
        temp.render(s);
    }
}
