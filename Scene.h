//
// Created by for Ye in Debugging : on 15/8/25.
//

#ifndef RAY_SCENE_H
#define RAY_SCENE_H

#include "Vector3.h"
#include "IntersectResult.h"
#include "Ray3.h"
#include "Material.h"
#include "Geometry.h"

#include <memory>
#include <cfloat>

class Scene {
public:
    virtual ~Scene() {}
    virtual IntersectResult intersect(const Ray3& ray) const = 0;
};

struct Geometry : public Scene {
    virtual ~Geometry() {}
    std::unique_ptr<Material> material;
    Geometry(Material* m = NULL) : material(m) {}
};

class Sphere : public Geometry {
public:
    Vector3 center;
    float radius, sqrRadius;

    Sphere(const Vector3& c, float r, Material *m = NULL) :
            Geometry(m), center(c), radius(r), sqrRadius(r * r) {}
    IntersectResult intersect(const Ray3& ray) const {
        Vector3 v = ray.origin - center;
        float a0 = v.sqrLength() - sqrRadius;
        float DdotV = ray.direction.dot(v);
        if (DdotV <= 0.0) {
            float discr = DdotV * DdotV - a0;
            if (discr >= 0.0) {
                float d = -DdotV - sqrt(discr);
                Vector3 p = ray.getPoint(d);
                Vector3 n = (p - center).normalize();
                return IntersectResult(this, d, p, n);
            }
        }
        return IntersectResult();
    }
};

struct Plane : public Geometry {
    Vector3 normal, position;
    std::auto_ptr<Material> material;

    Plane(const Vector3& n, float d, Material* m = NULL) :
            Geometry(m), normal(n), position(normal * d) {}

    IntersectResult intersect(const Ray3& ray) const {
        float a = ray.direction.dot(normal);
        if (a >= 0.0)
            return IntersectResult();
        float b = normal.dot(ray.origin - position);
        float d = -b / a;
        return IntersectResult(this, d, ray.getPoint(d), normal);
    }
};

struct Union : public Scene {
    std::unique_ptr<Geometry> geometries[6];
    int n;
    Union(Geometry* g1 = NULL, Geometry* g2 = NULL, Geometry* g3 = NULL, Geometry* g4 = NULL, Geometry* g5 = NULL, Geometry* g6 = NULL) {
        n = 0;
        if (g1) geometries[n++].reset(g1);
        if (g2) geometries[n++].reset(g2);
        if (g3) geometries[n++].reset(g3);
        if (g4) geometries[n++].reset(g4);
        if (g5) geometries[n++].reset(g5);
        if (g6) geometries[n++].reset(g6);
    }
    IntersectResult intersect(const Ray3& ray) const {

        float minDistance = FLT_MAX;
        IntersectResult minResult;
        for (int i = 0; i < n; ++i) {
            IntersectResult result = geometries[i]->intersect(ray);
            if (result.geometry && result.distance < minDistance) {
                minDistance = result.distance;
                minResult = result;
            }
        }
        return minResult;
    }
};

#endif //RAY_SCENE_H
