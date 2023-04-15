#include <iostream>
#include <fstream>
#include <string>
#include <cmath>
#include <string.h>

int main(int argc, char *argv[])
{
  char *input;
  char defaultOutput[] = "output";
  char *output = defaultOutput;
  bool inputSet = false, outputSet = false;
  for(int i = 0; i < argc; ++i) {
    if(strcmp(argv[i], "-i") == 0 && (i+1) < argc) {
      input = argv[i+1];
      inputSet = true;
    }
    if(strcmp(argv[i], "-o") == 0 && (i+1) < argc) {
      output = argv[i+1];
      outputSet = true;
    }
  }
  if(!inputSet || !outputSet)
  {
    std::cout << "provide input and output file \"-i inputfilename -o outputfilename\"" << std::endl;
    return 0;
  }
  std::ifstream fs(input, std::fstream::binary | std::fstream::in);
  std::ofstream ofs(output, std::fstream::binary | std::fstream::out);
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
