#pragma once

#include <string>
enum class FishType {
    koi,
    shark
};

inline std::string fishTypeToString(FishType type)
{
    switch (type)
    {
    case FishType::koi:
        return "koi";
    case FishType::shark:
        return "shark";
    default:
        return "unknown";
    }
}