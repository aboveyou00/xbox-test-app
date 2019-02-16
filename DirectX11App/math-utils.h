#pragma once

template <typename T>
inline constexpr T degToRad(T degrees) {
    return degrees * ((T)3.141592654 / (T)180.0);
}

template <typename T>
inline constexpr T radToDeg(T radians) {
    return radians * ((T)180.0 / (T)3.141592654);
}

template <typename T>
inline constexpr T pointDirection(T x1, T y1, T x2, T y2)
{
    auto xdiff = x2 - x1;
    auto ydiff = y2 - y1;
    auto dir = (T)fmod(radToDeg(atan2(-ydiff, xdiff)), (T)360.0);
    if (dir < (T)0)
    {
        dir += (T)360.0;
    }
    return dir;
}

template <typename T>
inline constexpr T pointDistance2(T x1, T y1, T x2, T y2)
{
    return (T)(pow(x2 - x1, 2) + pow(y2 - y1, 2));
}

template <typename T>
inline constexpr T pointDistance(T x1, T y1, T x2, T y2)
{
    return (T)sqrt(pointDistance2(x1, y1, x2, y2));
}
