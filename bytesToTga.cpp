#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <cmath>
#include <string.h>

#define READBUFFERSIZE 8192

int main(int argc, char *argv[])
{
  char *input;
  char defaultOutput[] = "output.tga";
  char *output = defaultOutput;
  bool inputSet = false;
  for(int i = 0; i < argc; ++i) {
    if(strcmp(argv[i], "-i") == 0 && (i+1) < argc) {
      input = argv[i+1];
      inputSet = true;
    }
    if(strcmp(argv[i], "-o") == 0 && (i+1) < argc) {
      output = argv[i+1];
    }
  }
  if(!inputSet)
  {
    std::cout << "provide input file \"-i inputfilename {-o outputfilename}\"" << std::endl;
    return 0;
  }
  std::ofstream fs(output, std::fstream::binary | std::fstream::out);
  std::ifstream ifs(input, std::fstream::binary | std::fstream::in);
  char buff[3] = {0};
  char readBuff[READBUFFERSIZE] = {0};
  char header[] = {0x00, 0x00, 0x02, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x18, 0x00};
  fs.write(header, 18);

  uint16_t pixelsNeeded = 0; 

  int actualRead = 0;

  while(actualRead = ifs.read(readBuff, READBUFFERSIZE).gcount()) {
    for(int i = 0; i < actualRead; i+=3) {
      buff[0] = i < actualRead ? readBuff[i] : 0;
      buff[1] = i+1 < actualRead ? readBuff[i+1] : 0;
      buff[2] = i+2 < actualRead ? readBuff[i+2] : 0;
      fs.write(buff, 3);
      ++pixelsNeeded;
    }
  }

  buff[0] = 0;
  buff[1] = 0;
  buff[2] = 0;
  fs.write(buff, 3);
  ++pixelsNeeded;

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
