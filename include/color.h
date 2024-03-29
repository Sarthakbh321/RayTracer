#ifndef COLOR_H
#define COLOR_H

#include "vec3.h"

void write_color(std::ostream &out, color pixel_color, int samples_per_pixel) {
    auto r = pixel_color.x();
    auto g = pixel_color.y();
    auto b = pixel_color.z();

    // Divide colors by number of samples
    auto scale = 1.0 / samples_per_pixel;
    r = sqrt(r * scale);
    g = sqrt(g * scale);
    b = sqrt(b * scale);

    // Output values clamped between [0, 256)
    out << static_cast<int>(256 * clamp(r, 0, 0.999)) << " "
        << static_cast<int>(256 * clamp(g, 0, 0.999)) << " "
        << static_cast<int>(256 * clamp(b, 0, 0.999)) << "\n";
}

#endif //COLOR_H
