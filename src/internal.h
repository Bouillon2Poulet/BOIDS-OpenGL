#ifndef __INTERNAL__HPP
#define __INTERNAL__HPP

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
}
#endif