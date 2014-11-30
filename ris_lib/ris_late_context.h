#pragma once

#include <functional>
#include <unordered_map>
#include <ostream>
#include <string>

namespace ris {

    template<typename TMap>
    class late_context {
    public:
        typedef std::function<void(std::ostream&)> lazy_stream_t;
        typedef std::unordered_map<std::string, lazy_stream_t> lazy_streams_t;
    private:
        lazy_streams_t lazy_streams;
        TMap&& non_lazy;
    public:
        late_context(TMap&& m):
            non_lazy(std::forward<TMap>(m)) {}
    public:
        late_context& lazy(std::string const& key, lazy_stream_t lazy) {
            lazy_streams[key] = lazy;
            return *this;
        }

        void stream(std::string const& key,std::ostream& s) {
            if (lazy_streams.find(key) != lazy_streams.end()) {
                lazy_streams[key](s);
            }
            else {
                s << non_lazy[key];
            }
        }
    };

    template<typename TMap>
    late_context<TMap> get_context(TMap&& m) {
        return late_context<TMap>(m);
    }
}
