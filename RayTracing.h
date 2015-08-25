//
// Created by for Ye in Debugging : on 15/8/26.
//

#ifndef RAY_RAYTRACING_H
#define RAY_RAYTRACING_H

#include "Color.h"
#include "Scene.h"
#include "Ray3.h"
#include "PerspectiveCamera.h"

const int width = 2048, height = 2048;
const int maxReflect = 5;
Color image[width * height];

template <int maxReflect>
class RayTracer {
public:
    Color operator()(const Scene& scene, const Ray3& ray_) const {
        Color color;
        float reflectiveness = 1.0;
        int reflect_times = 0;
        float r = 1.0;
        Color c;
        Ray3 ray = ray_;
        for (int i = 0; i < maxReflect; ++i) {
            IntersectResult result;
            result = scene.intersect(ray);
            if (!result.geometry) {
                reflect_times = i;
                break;
            }
            color += reflectiveness * (1 - r) * c;
            reflectiveness = reflectiveness * r;
            r = result.geometry->material->reflectiveness;
            c = result.geometry->material->sample(ray, result.position, result.normal);
            if (reflectiveness > 0) {
                ray = Ray3(result.position, result.normal * (-2 * result.normal.dot(ray.direction)) + ray.direction);
            } else
                break;
        }
        return color + reflectiveness * c;
    }
};

template <typename RenderFuncT>
void render(const Scene& scene, const PerspectiveCamera& camera, const RenderFuncT& f) {
#pragma omp parallel for num_threads(4)
    for (int i = 0; i < height * width; ++i) {
        int y = i / width;
        int x = i % width;
        float sy = y / float(height);
        float sx = x / float(width);
        Ray3 ray = camera.generateRay(sx, sy);
        image[i] = f(scene, ray);
    }
}
#endif //RAY_RAYTRACING_H
