//
// Created by sven on 12/22/20.
//

#include "png_utils.h"

#include <png++/png.hpp>


void write_png(const std::string &path, const unsigned char *img, int w, int h) {
    png::image<png::gray_pixel> image(w, h);
    for (int j = 0; j < h; ++j) {
        for (int k = 0; k < w; ++k) {
            image[j][k] = img[j * w + k];
        }
    }
    image.write(path);
}

void write_rgb_png(const std::string &path, const unsigned char *img, int w, int h) {
    png::image<png::rgb_pixel> image(w, h);
    for (int j = 0; j < h; ++j) {
        for (int k = 0; k < w; ++k) {
            image[j][k].blue = *(img + (j * w + k) * 3);
            image[j][k].green = *(img + (j * w + k) * 3 + 1);
            image[j][k].red = *(img + (j * w + k) * 3 + 2);
        }
    }
    image.write(path);
}
