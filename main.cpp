#include "include/raytracer.h"
#include <iostream>

#include "include/color.h"
#include "include/sphere.h"
#include "include/hittable_list.h"
using namespace std;


color ray_color(const ray& r, const hittable& world) {
    hit_record rec;
    if(world.hit(r, 0, infinity, rec)) {
        return 0.5 * (rec.normal + color(1,1,1));
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

    // World
    hittable_list world;
    world.add(make_shared<sphere>(point3(0, 0, -1), 0.5));
    world.add(make_shared<sphere>(point3(0, -100.5, -1), 100));


    // CAMERA
    auto VIEWPORT_HEIGHT = 2.0;
    auto VIEWPORT_WIDTH = ASPECT_RATIO * VIEWPORT_HEIGHT;
    auto FOCAL_LENGTH = 1.0;

    auto origin = point3(0, 0, 0);
    auto horizontal = vec3(VIEWPORT_WIDTH, 0, 0);
    auto vertical = vec3(0, VIEWPORT_HEIGHT, 0);
    auto lower_left_corner = origin - horizontal/2 - vertical/2 - vec3(0, 0, FOCAL_LENGTH);


    cout << "P3\n" << IMAGE_WIDTH << " " << IMAGE_HEIGHT << "\n255\n";

    for(int j = IMAGE_HEIGHT-1; j >= 0; j--) {
        cerr << "\rLines remaining: " << j << endl;
        for(int i = 0; i < IMAGE_WIDTH; i++) {
            auto u = double(i) / (IMAGE_WIDTH - 1);
            auto v = double(j) / (IMAGE_HEIGHT - 1);

            ray r(origin, lower_left_corner + u*horizontal + v*vertical - origin);
            color pixel_color = ray_color(r, world);
            write_color(cout, pixel_color);
        }
    }

    cerr << "\nDone!\n";

    return 0;
}
