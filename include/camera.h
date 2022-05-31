#ifndef CAMERA_H
#define CAMERA_H

#include "raytracer.h"

class camera {
public:
    point3 origin;
    point3 lower_left_corner;
    vec3 horizontal;
    vec3 vertical;
    vec3 u,v,w;
    double lens_radius;
public:
    camera(
            point3 lookfrom,
            point3 lookat,
            vec3 vup,
            double vfov,
            double aspect_ratio,
            double aperture,
            double focus_dist
    ) {
        auto theta = degrees_to_radians(vfov);
        auto h = tan(theta/2);
        auto VIEWPORT_HEIGHT = 2.0 * h;
        auto VIEWPORT_WIDTH = aspect_ratio * VIEWPORT_HEIGHT;
        auto FOCAL_LENGTH = 1.0;

        w = unit_vector(lookfrom - lookat);
        u = unit_vector(cross(vup, w));
        v = cross(w, u);

        origin = lookfrom;
        horizontal = focus_dist * VIEWPORT_WIDTH * u;
        vertical = focus_dist * VIEWPORT_HEIGHT * v;
        lower_left_corner = origin - horizontal/2 - vertical/2 - focus_dist*w;

        lens_radius = aperture / 2;
    }

    ray getRay(double s, double t) const {
        vec3 rd = lens_radius * random_in_unit_sphere();
        vec3 offset = u * rd.x() + v * rd.y();

        return ray(origin + offset, lower_left_corner + s*horizontal + t*vertical - origin - offset);
    }
};

#endif //CAMERA_H
