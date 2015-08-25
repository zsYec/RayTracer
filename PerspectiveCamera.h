//
// Created by for Ye in Debugging : on 15/8/26.
//

#ifndef RAY_PERSPECTIVECAMERA_H
#define RAY_PERSPECTIVECAMERA_H

#include "Vector3.h"
#include "Ray3.h"

class PerspectiveCamera {
private:
    Vector3 eye, front, right, up;
    float fovScale;
public:
    PerspectiveCamera(const Vector3& e, const Vector3& f, const Vector3& u, float fov)
            :eye(e), front(f), right(f.cross(u)), up(right.cross(f)), fovScale(tan(fov * 0.5 * 3.1415926 / 180) * 2) {}

    Ray3 generateRay(float x, float y) const {
        Vector3 r = right * ((x - 0.5) * fovScale);
        Vector3 u = up * ((y - 0.5) * fovScale);
        return Ray3(eye, (front + r + u).normalize());
    }
};
#endif //RAY_PERSPECTIVECAMERA_H
