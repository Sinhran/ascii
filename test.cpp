#include <iostream>
#include <fstream>
#include <iomanip>
#include <cstdint>

uint16_t checksize(std::fstream &file);
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

    const uint headersize = 54;
    struct bith {
      int bmdib;
      int bmsize;
      int reser;
      int juice;
    };

    struct bitdibh {
      int bitdibhsize;
      int bwidth;
      int bheight;
      int bcolorplanes;
      int bcolordepth;
      int bcomp;
      int bimgsize;
      int bhpres;
      int bvpres;
      int bcolorn;
      int bcolornimp;
    };

    bith bith;

  if (testfile.is_open()) {
    uint16_t sizeaz = checksize(testfile);
    // Hmmmmmm
    // Now that we know the file size, I guess it's
    // a good time to read it into memory
    char *buffer = new char[sizeaz];

    testfile.read(buffer, sizeaz);

    if (testfile) {
      std::cout << "All characters read successfully." << std::endl;
    } else {
      std::cout << "Error: Only " << testfile.gcount() << " characters could be read." << std::endl;
    }

    // So buffer is the same size as the file now
    // So to access the image data, we need to move
    // 54 bytes
    // How do we do that?
    // Let's start with making a variable to hold 54
    // bytes of data
    // char *headers = new char[headersize]; // No need of this yet
    // Creating a pointer that points to the buffer
    char *ptr = buffer;
    // Checking if it worked to keep sanity
    // static_cast<void*>(buffer) to cast the
    // value at the memory address to void type
    // so that it shows the memory address and
    // not random garbage
    std::cout << static_cast<void*>(buffer) << " " << static_cast<void*>(ptr) << std::endl;
    std::cout << static_cast<void*>(ptr+54) << std::endl;
    // Now we are going to make a variable for output
    // file. And then open the file and dump the headers.
    std::fstream testout;
    testout.open("testout.bmp", std::ios::out | std::ios::binary);
    if (testout.fail()) {
        std::cerr << "Error opening file: " << strerror(errno) << std::endl;
      return 2;
    }
    if (testout.is_open()) {
      // Let's create a loop that iterates while
      // ptr < (ptr+54) and copy byte by byte from
      // buffer into the output file
      for (int i = 0; i < headersize; ++i) {
        char byte = *(ptr + i);
        testout << byte;
      }

      for (int i = (headersize); i < sizeaz; ++i) {
        char byte = *(ptr + i);
        testout << byte;
      }
      std::cout << sizeaz << std::endl;
      testout.close();
    }
    testfile.close();
    // delete[] headers;
    delete[] buffer;
  } else {
    std::cout << "Unable to open file." << std::endl;
    return 1;
  }
  return 0;
}

uint16_t checksize(std::fstream &file) {
  // Read the file byte by byte
  // Store the filesize in size variable
  uint16_t size = 0;
  char byte;
  while (file.read((&byte), sizeof(byte))) {
    size++;
  }
  // Reset EOF flag
  file.clear();
  // Move the file pointer to the beginning of file
  file.seekg(0, std::ios::beg);
  return size;
}
