#include <iostream>
#include <fstream>
#include <string>
#include <cmath>

int main(void)
{
  std::ifstream fs("cpptest.tga", std::fstream::binary | std::fstream::in);
  std::ofstream ofs("output", std::fstream::binary | std::fstream::out);
  char buff[3] = {0};
  char header[18];
  std::string text = "";
  fs.read(header, 18);
  unsigned short width = (uint16_t)(uint8_t)header[12] | ((uint16_t)header[13] << 8);
  unsigned short height = (uint16_t)(uint8_t)header[14] | ((uint16_t)header[15] << 8);

  uint16_t size = width * height;
  for(int i = 0; i < size; ++i) {
    if(text.size() > 100) {
      ofs << text;
      text = "";
    }
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

  ofs << text;
  
  fs.close();
  return 0;
}
