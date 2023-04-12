#pragma once

#include <string>
enum class FishType {
    koi,
    tuna,
    whale
};

inline std::string fishTypeToString(FishType type)
{
    switch (type)
    {
    case FishType::koi:
        return "koi";
    case FishType::tuna:
        return "tuna";
    case FishType::whale:
        return "whale";
    default:
        return "unknown";
    }
}