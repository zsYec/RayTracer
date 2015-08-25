//
// Created by for Ye in Debugging : on 15/8/25.
//

#ifndef RAY_RAY3_H
#define RAY_RAY3_H

#include "Color.h"
#include "Vector3.h"

class Ray3 {
public:
    Vector3 origin, direction;
    Ray3(const Vector3& o, const Vector3& d) : origin(o), direction(d) {}

    Vector3 getPoint(float t) const { return origin + t * direction; }
};

#endif //RAY_RAY3_H
