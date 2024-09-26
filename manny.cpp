#include <iostream>

int main(void) {
  int width;
  int height;
  std::cout << "Enter the width in pixels: ";
  std::cin >> width;
  std::cout << "Enter the height in pixels: ";
  std::cin >> height;
  const int resolution = height*width;

  std::cout << width << "x" << height << std::endl;

  bool *pixels[resolution];
  for (int i = 0; i < resolution; i++) {
    pixels[i] = new bool;

  }

  std::cout << "Enter the string of pixels. 0 for black; 1 for white. " << std::endl;
  for (int i = 0; i < resolution; i++) {
    bool temp;
    std::cin >> temp;
    *pixels[i] = temp;
  }

  for (int i = 0; i < resolution; i++) {
    if (i%width == 0 && i != 0) {
      std::cout << std::endl;
    }
    if (*pixels[i] == 1) {
      std::cout << "󰝤";
    } else {
      std::cout << "󰝣";
    }
  }
    std::cout << std::endl;

  for (int i = 0; i < resolution; i++) {
    delete pixels[i];
  }
  // std::cout << "󰝤" << "&" << "󰝣" << std::endl;
  return 0;
}
