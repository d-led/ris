#pragma once

#include <unordered_map>

namespace ris {
    typedef std::unordered_map<std::string, std::string> snapshot_t;

    template <typename TResource>
    snapshot_t resource_snapshot(TResource const& resource) {
        snapshot_t res;
        resource.GetKeys([&res, &resource](std::string const& key) {
            res[key] = resource.Get(key);
        });
        return res;
    }
}
