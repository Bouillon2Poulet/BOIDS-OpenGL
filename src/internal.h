#pragma once

#include <p6/p6.h>
#include <codecvt>
#include <locale>
#include <string>
#include "glm/fwd.hpp"

namespace internal {
/// \brief return the sign of val or zero if val is equal to zero
/// \tparam T : the value Type, MUST BE a number
/// \param val : the value to get the sign from
/// \return the sign of value, zero if value is equal to zero
template<typename T>
constexpr int sign(T val)
{
    return (T{0} <= val) - (val < T{0});
}

inline std::u16string to_u16string(int const& i)
{
    std::wstring_convert<std::codecvt_utf8_utf16<char16_t, 0x10ffff, std::little_endian>, char16_t> conv;
    return conv.from_bytes(std::to_string(i));
}

inline glm::vec3 randomPosInBoundingBox(const glm::vec3& maxDistanceFromCenter)
{
    return glm::vec3(p6::random::number(-maxDistanceFromCenter.x, maxDistanceFromCenter.x), p6::random::number(-maxDistanceFromCenter.y, maxDistanceFromCenter.y), p6::random::number(-maxDistanceFromCenter.z, maxDistanceFromCenter.z)) / 2.f;
}
} // namespace internal