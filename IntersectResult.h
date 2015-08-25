//
// Created by for Ye in Debugging : on 15/8/25.
//

#ifndef RAY_INTERSECTRESULT_H
#define RAY_INTERSECTRESULT_H

#include <iostream>
#include "Vector3.h"
#include "Geometry.h"

class IntersectResult {
public:
    const Geometry* geometry;
    float distance;
    Vector3 position;
    Vector3 normal;

    IntersectResult() : geometry(NULL), distance(0), position(Vector3::zero()), normal(Vector3::zero()) {}
    IntersectResult(const Geometry* g, float d, const Vector3& p, const Vector3& n) : geometry(g), distance(d), position(p), normal(n) {}
};
#endif //RAY_INTERSECTRESULT_H
