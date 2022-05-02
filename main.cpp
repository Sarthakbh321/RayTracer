#include <iostream>
#include "headers/vec3.h"
#include "headers/color.h"
using namespace std;

int main() {
    const int IMAGE_WIDTH = 256;
    const int IMAGE_HEIGHT = 256;

    cout << "P3\n" << IMAGE_WIDTH << " " << IMAGE_HEIGHT << "\n255\n";

    for(int j = IMAGE_HEIGHT-1; j >= 0; j--) {
        cerr << "\rLines remaining: " << j << endl;
        for(int i = 0; i < IMAGE_WIDTH; i++) {
            auto r = double(i) / (IMAGE_WIDTH - 1);
            auto g = double(j) / (IMAGE_HEIGHT - 1);
            auto b = 0.25;

            color pixel_color(r,g,b);
            write_color(cout, pixel_color);
        }
    }

    cerr << "\nDone!\n";

    return 0;
}
