//
// Created by sven on 12/22/20.
//

#pragma once

#include <string>


void write_png(const std::string &path, const unsigned char *img, int w, int h);


void write_rgb_png(const std::string &path, const unsigned char *img, int w, int h);
