#include <iostream>
#include <fstream>
#include <iomanip>

int main() {
  // Variable to store file
  std::fstream testfile;

  // Make a variable to separate four bytes with one space
  int count = 0;

  // Opening the file
  testfile.open("test.bmp");//, std::ios::binary);
  if (testfile.fail()) {
      std::cerr << "Error opening file: " << strerror(errno) << std::endl;
  }

  if (testfile.is_open()) {
   std::cout << "File opened successfully." << std::endl;
    // Read the file byte by byte
    unsigned char byte;
    while (testfile.read(reinterpret_cast<char*>(&byte), sizeof(byte))) {
      // Print each byte as hex value with leading zero
      if (count == 1) {
        std::cout << std::hex << std::setw(2) << std::setfill('0') << static_cast<int>(byte) << " ";
        count = 0;
      } else {
        std::cout << std::hex << std::setw(2) << std::setfill('0') << static_cast<int>(byte);
        count++;
      }
    }
    std::cout << std::endl;
    testfile.close();
  } else {
    std::cout << "Unable to open file." << std::endl;
    return 1;
  }
  return 0;
}
