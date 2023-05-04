#pragma once

#include <string>
enum class FishType {
    koi,
    tuna,
    shark
};

inline std::string fishTypeToString(FishType type)
{
    switch (type)
    {
    case FishType::koi:
        return "koi";
    case FishType::tuna:
        return "tuna";
    case FishType::shark:
        return "shark";
    default:
        return "unknown";
    }
}