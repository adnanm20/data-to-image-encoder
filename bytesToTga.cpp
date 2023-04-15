#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <cmath>

int main(void)
{
  std::ofstream fs("cpptest.tga", std::fstream::binary | std::fstream::out);
  std::ifstream ifs("lorem50kB", std::fstream::binary | std::fstream::in);
  char buff[3] = {0};
  char readBuff[99] = {0};
  char header[] = {0x00, 0x00, 0x02, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x18, 0x00};
  fs.write(header, 18);

  int k = 0;
  uint16_t pixelsNeeded = 0; 

  ifs.read(readBuff, 99);
  int actualRead = 99;

  while(actualRead != 0) {
    ++pixelsNeeded;
    if(k >= 99) 
    {
      ifs.read(readBuff, 99);
      k = 0;
      actualRead = 99;
    }
    if(!ifs) {
      actualRead = ifs.gcount();
    }
    buff[0] = k < actualRead ? readBuff[k] : 0;
    buff[1] = k+1 < actualRead ? readBuff[k+1] : 0;
    buff[2] = k+2 < actualRead ? readBuff[k+2] : 0;
    fs.write(buff, 3);
    k += 3;
  }

  int imgSize = (uint16_t)ceil(sqrt(pixelsNeeded));
  header[12] = (char)(imgSize & 0xff);
  header[13] = (char)(imgSize & 0xff00);
  header[14] = (char)(imgSize & 0xff);
  header[15] = (char)(imgSize & 0xff00);
  fs.seekp(0);
  fs.write(header, 18);
  
  fs.close();
  return 0;
}
