#ifndef TRACEPP_MATH_H
#define TRACEPP_MATH_H

#include "types.h"

namespace trace {

// VECTORS

struct Vec4b {
    u8 x = 0;
    u8 y = 0;
    u8 z = 0;
    u8 w = 0;

    constexpr Vec4b() : x{0}, y{0}, z{0}, w{0} {}

    constexpr Vec4b(u8 x_, u8 y_, u8 z_, u8 w_) : x{x_}, y{y_}, z{z_}, w{w_} {}
};

struct Vec2i {
    i32 x = 0;
    i32 y = 0;

    constexpr Vec2i() : x{0}, y{0} {}

    constexpr Vec2i(i32 x_, i32 y_) : x{x_}, y{y_} {}

    inline bool operator==(const Vec2i &other) const {
        return this->x == other.x && this->y == other.y;
    }
};

struct Vec3i {
    i32 x = 0;
    i32 y = 0;
    i32 z = 0;

    constexpr Vec3i() : x{0}, y{0}, z{0} {}

    constexpr Vec3i(i32 x_, i32 y_, i32 z_) : x{x_}, y{y_}, z{z_} {}
};

struct Vec4i {
    i32 x = 0;
    i32 y = 0;
    i32 z = 0;
    i32 w = 0;

    constexpr Vec4i() : x{0}, y{0}, z{0}, w{0} {}

    constexpr Vec4i(i32 x_, i32 y_, i32 z_, i32 w_) : x{x_}, y{y_}, z{z_}, w{w_} {}
};

constexpr auto zero2i = Vec2i{0, 0};

struct Vec2f {
    f32 x = 0;
    f32 y = 0;

    constexpr Vec2f() : x{0}, y{0} {}

    constexpr Vec2f(f32 x_, f32 y_) : x{x_}, y{y_} {}
};

struct Vec3f {
    f32 x = 0;
    f32 y = 0;
    f32 z = 0;

    constexpr Vec3f() : x{0}, y{0}, z{0} {}

    constexpr Vec3f(f32 x_, f32 y_, f32 z_) : x{x_}, y{y_}, z{z_} {}
};

struct Vec4f {
    f32 x = 0;
    f32 y = 0;
    f32 z = 0;
    f32 w = 0;

    constexpr Vec4f() : x{0}, y{0}, z{0}, w{0} {}

    constexpr Vec4f(f32 x_, f32 y_, f32 z_, f32 w_) : x{x_}, y{y_}, z{z_}, w{w_} {}
};

struct Frame3f {
    Vec3f x = {1, 0, 0};
    Vec3f y = {0, 1, 0};
    Vec3f z = {0, 0, 1};
    Vec3f o = {0, 0, 0};

    constexpr Frame3f() : x{1, 0, 0}, y{0, 1, 0}, z{0, 0, 1}, o{0, 0, 0} {}

    constexpr Frame3f(Vec3f x_, Vec3f y_, Vec3f z_, Vec3f o_)
            : x{x_}, y{y_}, z{z_}, o{o_} {}
};

constexpr auto identity3x4f = Frame3f{
        {1, 0, 0},
        {0, 1, 0},
        {0, 0, 1},
        {0, 0, 0}};

}

#endif //TRACEPP_MATH_H
