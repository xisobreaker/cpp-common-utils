#pragma once

namespace xiso {

template <typename To, typename From>
inline To implicit_cast(From const &f)
{
    return f;
}

} // namespace xiso