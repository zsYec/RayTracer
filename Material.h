//
// Created by for Ye in Debugging : on 15/8/25.
//

#ifndef RAY_MATERIAL_H
#define RAY_MATERIAL_H

#include "Color.h"
#include "Ray3.h"
#include "Vector3.h"

class Material {
public:
    float reflectiveness;
    virtual ~Material() {}
    Material(float r = 0.0) : reflectiveness(r) {}
    virtual Color sample(const Ray3& ray, const Vector3& position, const Vector3& normal) const = 0;
};

inline int iabs(int x) {
    return x < 0 ? -x : x;
}

struct CheckerMaterial : public Material {
    float scale;
    CheckerMaterial(float s, float r = 0.0) : Material(r), scale(s) {}
    Color sample(const Ray3& ray, const Vector3& position, const Vector3& normal) const {
        if (iabs(floor(position.x * 0.1) + floor(position.z * scale)) % 2 < 1)
            return Color(0, 0, 0);
        else
            return Color(1.0, 1.0, 1.0);
    }
};

Vector3 lightDir = Vector3(1, 1, 1).normalize();
Color lightColor = Color(1, 1, 1);
inline float max(float a, float b) {
    return a > b ? a : b;
}

struct PhongMaterial : public Material {
    Color diffuse, specular;
    int shininess;
    PhongMaterial(const Color& d, const Color& sp, int sh, float r = 0.0) :
            Material(r), diffuse(d), specular(sp), shininess(sh) {}

    Color sample(const Ray3& ray, const Vector3& position, const Vector3& normal) const {
        float NdotL = normal.dot(lightDir);
        Vector3 H = (lightDir - ray.direction).normalize();
        float NdotH = normal.dot(H);
        Color diffuseTerm = diffuse * max(NdotL, 0.0);
        Color specularTerm = specular * pow(max(NdotH, 0.0), shininess);
        //Color r = lightColor.modulate(diffuseTerm + specularTerm);
        //cerr << r.r << " " << r.g << " " << r.b << endl;
        return lightColor.modulate(diffuseTerm + specularTerm);
    }
};

#endif //RAY_MATERIAL_H
