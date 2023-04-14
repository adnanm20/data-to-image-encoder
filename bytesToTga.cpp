#include <iostream>
#include <fstream>
#include <string>
#include <cmath>

int main(void)
{
  std::ofstream fs("cpptest.tga", std::fstream::binary | std::fstream::out);
  char buff[3] = {0, 0, 0};
  std::string text = "Lorem ipsum dolor sit amet, consectetur adipiscing elit. Aliquam aliquam lectus ultrices sagittis dapibus. Curabitur dapibus lorem nec tellus consequat.";
  int dataSize = text.size()/3;
  int imgSize = (int)ceil(sqrt(dataSize));
  char header[] = {0x00, 0x00, 0x02, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, (char)imgSize, 0x00, (char)imgSize, 0x00, 0x18, 0x00};
  fs.write(header, 18);
  imgSize *= imgSize;

  for(uint8_t i = 0; i < imgSize; i+=3) {
    buff[0] = i < text.size() ? text[i] : 0;
    buff[1] = i+1 < text.size() ? text[i+1] : 0;
    buff[2] = i+2 < text.size() ? text[i+2] : 0;
    fs.write(buff, 3);
  }

  
  fs.close();
  return 0;
}
