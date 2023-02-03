#pragma once
namespace sog
{
struct static_init
{
    template <typename C> static_init(C constractor)
    {
        constractor();
    }
};
} // namespace sog
