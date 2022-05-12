#ifndef CAMERA_H
#define CAMERA_H

#include "raytracer.h"

class camera {
public:
    point3 origin;
    point3 lower_left_corner;
    vec3 horizontal;
    vec3 vertical;
public:
    camera() {
        const auto ASPECT_RATIO = 16.0 / 9.0;
        auto VIEWPORT_HEIGHT = 2.0;
        auto VIEWPORT_WIDTH = ASPECT_RATIO * VIEWPORT_HEIGHT;
        auto FOCAL_LENGTH = 1.0;

        origin = point3(0, 0, 0);
        horizontal = vec3(VIEWPORT_WIDTH, 0, 0);
        vertical = vec3(0, VIEWPORT_HEIGHT, 0);
        lower_left_corner = origin - horizontal/2 - vertical/2 - vec3(0, 0, FOCAL_LENGTH);
    }

    ray getRay(double u, double v) const {
        return ray(origin, lower_left_corner + u*horizontal + v*vertical - origin);
    }
};

#endif //CAMERA_H
