//
// Created by for Ye in Debugging : on 15/8/25.
//

#ifndef RAY_VECTOR3_H
#define RAY_VECTOR3_H

#include <math.h>

class Vector3 {
public:
    float x, y, z;
    Vector3(float x_, float y_, float z_) : x(x_), y(y_), z(z_) {}
    Vector3(const Vector3 &r) : x(r.x), y(r.y), z(r.z) {}
    float sqrLength() const {
        return x * x + y * y + z * z;
    }

    float length() const {
        return sqrt(sqrLength());
    }

    Vector3 operator+(const Vector3& r) const {
        return Vector3(x + r.x, y + r.y, z + r.z);
    }

    Vector3 operator-(const Vector3& r) const {
        return Vector3(x - r.x, y - r.y, z - r.z);
    }

    Vector3 operator*(float v) const {
        return Vector3(v * x, v * y, v * z);
    }

    Vector3 operator/(float v) const {
        float inv = 1 / v;
        return *this * inv;
    }

    Vector3 normalize() const {
        float invlen = 1 / length();
        return *this * invlen;
    }

    float dot(const Vector3& r) const {
        return x * r.x + y * r.y + z * r.z;
    }

    Vector3 cross(const Vector3& r) const {
        return Vector3(-z * r.y + y * r.z,
                       z * r.x - x * r.z,
                       -y * r.x + x * r.y);
    }

    static Vector3 zero() {
        return Vector3(0, 0, 0);
    }
};
inline Vector3 operator*(float l, const Vector3& r) {
    return r * l;
}

#endif //RAY_VECTOR3_H
