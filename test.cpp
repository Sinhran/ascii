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
    // Read the file byte by byte
    // Store the filesize in size variable
    char byte;
    long size = 0;
    while (testfile.read((&byte), sizeof(byte))) {
      size++;
    }
    // Reset EOF flag
    testfile.clear();
    // Move the file pointer to the beginning of file
    testfile.seekg(0, std::ios::beg);

    // Hmmmmmm
    // Now that we know the file size, I guess it's
    // a good time to read it into memory
    char *buffer = new char[size];

    testfile.read(buffer, size);

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
    const uint headersize = 54;
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

      for (int i = (headersize); i < size; ++i) {
        char byte = *(ptr + i);
        testout << byte;
      }
      std::cout << size << std::endl;
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
