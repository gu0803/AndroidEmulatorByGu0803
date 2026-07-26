#pragma once

#include <optional>
#include <string>
#include <vector>

namespace guemu {

struct TouchPoint {
    int x = 0;
    int y = 0;
};

struct MappingAction {
    std::string key;
    TouchPoint touch;
    bool locksMouse = false;
    int lookRadius = 0;
};

class InputMapper {
public:
    void addTapMapping(std::string key, TouchPoint touch);
    void addLookMapping(std::string key, TouchPoint center, int radius);
    std::optional<MappingAction> resolve(const std::string& key) const;
    std::string serialize() const;

private:
    std::vector<MappingAction> mappings_;
};

} // namespace guemu
