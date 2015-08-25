//
// Created by for Ye in Debugging : on 15/8/26.
//
#include <iostream>

#include "BMPWriter.h"
#include "RayTracing.h"

int main(void) {
    clock_t t_start = clock();

    render(Union(new Plane(Vector3(0, 0.5, 0), 0, new CheckerMaterial(0.1, 0.5)),
                 new Sphere(Vector3(-10, 20, -10), 5, new PhongMaterial(Color(0.3, 1, 0.8), Color(1, 1, 1), 16, 0.25)),
                 new Sphere(Vector3( 10, 10, -10), 10, new PhongMaterial(Color(1, 1, 0), Color(1, 1, 1), 16, 0.25)),
                 new Sphere(Vector3(-10, 10,  -5), 5, new PhongMaterial(Color(0, 1, 0), Color(1, 1, 1), 16, 0.25)),
                 new Sphere(Vector3(-5, 5,  -5), 5, new PhongMaterial(Color(1, 1, 1), Color(1, 1, 1), 16, 0.25)),
                 new Sphere(Vector3(5, 15,  -15), 10, new PhongMaterial(Color(1, 0.5, 0.5), Color(1, 1, 1), 16, 0.25))
           ),
           PerspectiveCamera(Vector3(0, 5, 15), Vector3(0, 0, -1), Vector3(0, 1, 0), 90),
           RayTracer<maxReflect>());

    clock_t t_end = clock();
    std::cout << (t_end - t_start) / float(CLOCKS_PER_SEC) << std::endl;
    BMPWriter::write("/Users/mac/Desktop/RayTracing.bmp", image, width, height);

    return 0;
}
