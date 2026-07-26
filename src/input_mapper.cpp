#include "input_mapper.h"

#include <sstream>

namespace guemu {

void InputMapper::addTapMapping(std::string key, TouchPoint touch) {
    mappings_.push_back(MappingAction{std::move(key), touch, false, 0});
}

void InputMapper::addLookMapping(std::string key, TouchPoint center, int radius) {
    mappings_.push_back(MappingAction{std::move(key), center, true, radius});
}

std::optional<MappingAction> InputMapper::resolve(const std::string& key) const {
    for (const auto& mapping : mappings_) {
        if (mapping.key == key) {
            return mapping;
        }
    }
    return std::nullopt;
}

std::string InputMapper::serialize() const {
    std::ostringstream out;
    for (const auto& mapping : mappings_) {
        out << mapping.key << " -> (" << mapping.touch.x << ',' << mapping.touch.y << ')';
        if (mapping.locksMouse) {
            out << " look_radius=" << mapping.lookRadius;
        }
        out << '\n';
    }
    return out.str();
}

} // namespace guemu
