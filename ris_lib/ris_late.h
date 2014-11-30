#pragma once

#include <utility>
#include <string>
#include <boost/regex.hpp>

namespace ris {
    /// mustache/ctemplate inspired (http://mustache.github.io/mustache.5.html)
    template <typename TContext>
    class late {
        TContext&& context;
        std::string late_;
        boost::regex simple_placeholder;
        boost::regex all_placeholders;
        late(late const&);
    public:
        late(std::string const& tmp,TContext&& c) :
            late_(tmp),
            context(std::forward<TContext>(c)),
            simple_placeholder("\\{\\{\\s*([\\w_-\\.]+)\\s*\\}\\}"),
            all_placeholders("\\{\\{\\s*[#/^!>]?\\s*([\\w_]+)\\s*[\\?]?\\s*\\}\\}")
        {}
    public:
        template <typename TStream>
        void render(TStream& s) {
            boost::sregex_iterator current (
                late_.begin(),
                late_.end(),
                all_placeholders);
            boost::sregex_iterator end;
            size_t pos_before_placeholder = 0;
            for (; current != end; ++current) {
                std::string before_placeholder = late_.substr(pos_before_placeholder, current->position() - pos_before_placeholder);
                pos_before_placeholder = current->position() + current->length();
                s << before_placeholder;

                boost::smatch capture;
                std::string token = current->str();
                if (boost::regex_match(token, capture, simple_placeholder)) {
                    context.stream(capture[1].str(), s);
                }
                else if (boost::regex_match(token, capture, all_placeholders)) {
                    // stream nothing
                }
                else {
                    s << token;
                }
            }
            if (late_.length() && pos_before_placeholder<late_.length())
                s << late_.substr(pos_before_placeholder, pos_before_placeholder - late_.length());
        }
    };

    template <typename TContext,typename TStream>
    void render(std::string const& tmp,TContext ctx,TStream& s) {
        late<TContext>(tmp,std::forward<TContext>(ctx)).render(s);
    }
}
