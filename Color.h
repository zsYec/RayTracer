//
// Created by for Ye in Debugging : on 15/8/25.
//

#ifndef RAY_COLOR_H
#define RAY_COLOR_H

#include <math.h>

inline float clampf(float v, float min, float max) {
    return v < min ? min : v > max ? max : v;
}

class Color {
public:
    float r, g, b;
    Color(float r_ = 0.0, float g_ = 0.0, float b_ = 0.0) :
            r(r_), g(g_), b(b_) {}
    Color(const Color& c) : r(c.r), g(c.g), b(c.b) {}
    Color clamp() const {
        return Color( clampf(r, 0.0, 1.0),
                      clampf(g, 0.0, 1.0),
                      clampf(b, 0.0, 1.0));
    }

    Color operator+(const Color& o) const {
        return Color(r + o.r , g + o.g, b + o.b);
    }

    Color& operator+=(const Color& o) {
        r += o.r; g += o.g; b += o.b;
        return *this;
    }

    Color operator*(float v) const {
        return Color(v * r, v * g, v * b);
    }

    Color modulate(const Color& o) const {
        return Color(r * o.r, g * o.g, b * o.b);
    }
};

inline Color operator*(float v, const Color& o) {return o * v;}

#endif //RAY_COLOR_H
