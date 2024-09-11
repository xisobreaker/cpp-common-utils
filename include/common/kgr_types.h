#pragma once

namespace kgr {

template <typename To, typename From>
inline To implicit_cast(From const &f)
{
    return f;
}

} // namespace kgr