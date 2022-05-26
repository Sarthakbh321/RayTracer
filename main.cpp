#include "include/raytracer.h"
#include <iostream>

#include "include/color.h"
#include "include/sphere.h"
#include "include/hittable_list.h"
#include "include/camera.h"
#include "include/materials.h"
using namespace std;


color ray_color(const ray& r, const hittable& world, int depth) {
    hit_record rec;

    if(depth <= 0) {
        return color(0,0,0);
    }

    if(world.hit(r, 0.001, infinity, rec)) {
        ray scattered;
        color attenuation;

        if(rec.mat_ptr->scatter(r, rec, attenuation, scattered)) {
            return attenuation * ray_color(scattered, world, depth-1);
        }

        return color(0,0,0);
    }

    vec3 unit_dir = unit_vector(r.direction());
    auto t = 0.5*(unit_dir.y() + 1.0); // denormalizing the vector

    return (1.0-t) * color(1, 1, 1)+ t * color(0.5, 0.7, 1.0);
}

int main() {
    // IMAGE
    const auto ASPECT_RATIO = 16.0 / 9.0;
    const int IMAGE_WIDTH = 400;
    const int IMAGE_HEIGHT = static_cast<int>(IMAGE_WIDTH / ASPECT_RATIO);
    const int SAMPLES_PER_PIXEL = 100;
    const int MAX_DEPTH = 50;

    // World
    hittable_list world;

    auto material_ground = make_shared<lambertian>(color(0.8, 0.8, 0.0));
    auto material_center = make_shared<lambertian>(color(0.7, 0.3, 0.3));
    auto material_left = make_shared<dielectric>(1.5);
    auto material_right = make_shared<metal>(color(0.8, 0.6, 0.2), 1.0);

    world.add(make_shared<sphere>(point3(0, 0, -1), 0.5, material_center));
    world.add(make_shared<sphere>(point3(-1, 0, -1), -0.5, material_left));
    world.add(make_shared<sphere>(point3(1, 0, -1), 0.5, material_right));
    world.add(make_shared<sphere>(point3(0, -100.5, -1), 100, material_ground));


    // CAMERA
    camera cam;

    cout << "P3\n" << IMAGE_WIDTH << " " << IMAGE_HEIGHT << "\n255\n";

    for(int j = IMAGE_HEIGHT-1; j >= 0; j--) {
        cerr << "\rLines remaining: " << j << endl;
        for(int i = 0; i < IMAGE_WIDTH; i++) {
            color pixel_color(0, 0, 0);
            for(int s = 0; s < SAMPLES_PER_PIXEL; s++) {
                auto u = double(i + random_double()) / (IMAGE_WIDTH - 1);
                auto v = double(j + random_double()) / (IMAGE_HEIGHT - 1);

                ray r = cam.getRay(u, v);
                pixel_color += ray_color(r, world, MAX_DEPTH);
            }

            write_color(cout, pixel_color, SAMPLES_PER_PIXEL);
        }
    }

    cerr << "\nDone!\n";

    return 0;
}
