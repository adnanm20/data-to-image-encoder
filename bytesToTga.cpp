#include <iostream>
#include <fstream>
#include <string>
#include <cmath>

int main(void)
{
  std::ofstream fs("cpptest.tga", std::fstream::binary | std::fstream::out);
  std::ifstream ifs("lorem100w", std::fstream::binary | std::fstream::in);
  char buff[3] = {0};
  std::string data(std::istreambuf_iterator<char>(ifs), {});
  uint16_t dataSize = data.size();
  uint16_t pixelsNeeded = ceil(data.size()/3.);
  uint16_t imgSize = (uint16_t)ceil(sqrt(pixelsNeeded));
  char header[] = {0x00, 0x00, 0x02, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, (char)(imgSize & 0xff), (char)(imgSize & 0xff00), (char)(imgSize & 0xff), (char)(imgSize & 0xff00), 0x18, 0x00};
  fs.write(header, 18);
  imgSize *= imgSize;

  int k = 0;
  for(uint8_t i = 0; i < imgSize; ++i) {
    buff[0] = k < dataSize ? data[k] : 0;
    buff[1] = k+1 < dataSize ? data[k+1] : 0;
    buff[2] = k+2 < dataSize ? data[k+2] : 0;
    fs.write(buff, 3);
    k += 3;
  }

  
  fs.close();
  return 0;
}
