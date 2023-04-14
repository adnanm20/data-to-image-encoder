#include <iostream>
#include <fstream>
#include <string>
#include <cmath>

int main(void)
{
  std::ifstream fs("cpptest.tga", std::fstream::binary | std::fstream::in);
  char buff[3] = {0};
  char header[18];
  std::string text = "";
  fs.read(header, 18);
  uint16_t width = header[12] | (header[13] << 8);
  uint16_t height = header[14] | (header[15] << 8);

  int size = width * height;
  for(int i = 0; i < size; ++i) {
    fs.read(buff, 3);
    if(buff[0] == 0)
    {
      break;
    }
    text += buff[0];
    if(buff[1] == 0)
    {
      break;
    }
    text += buff[1];
    if(buff[2] == 0)
    {
      break;
    }
    text += buff[2];
  }

  std::cout << text << std::endl;


  
  fs.close();
  return 0;
}
