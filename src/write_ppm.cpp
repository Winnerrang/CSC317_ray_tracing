#include "write_ppm.h"
#include <fstream>
#include <cassert>
#include <iostream>

bool write_ppm(
  const std::string & filename,
  const std::vector<unsigned char> & data,
  const int width,
  const int height,
  const int num_channels)
{
  ////////////////////////////////////////////////////////////////////////////
  // Replace with your code here:
    assert(
        (num_channels == 3 || num_channels == 1) &&
        ".ppm only supports RGB or grayscale images");

    std::ofstream ofs(filename, std::ios_base::out);
    char* version;
    if (num_channels == 1) {
        version = "P2";
    }
    else if (num_channels == 3) {
        version = "P3";
    }

    ofs << version << std::endl;
    ofs << (unsigned int)width << ' ' << (unsigned int)height << std::endl;
    ofs << "255" << std::endl;

    for (int pixel_index = 0; pixel_index < width * height; pixel_index++) {

        for (int i = 0; i < num_channels; i++) {
            ofs << (int)data[pixel_index * num_channels + i] << " ";
        }
        ofs << std::endl;
    }

    ofs.close();

    return true;
  ////////////////////////////////////////////////////////////////////////////
}
