#include "iostream"
#include "fstream"
#include "inipp.h"

int main(int argc, char** argv) {
  inipp::Ini<char> ini;
  std::ifstream is("/home/kirill/Desktop/study/MAI_OS/KP/config/config.ini");
  ini.parse(is);
  std::cout << "raw ini file:" << std::endl;
  ini.generate(std::cout);
  ini.strip_trailing_comments();
  ini.default_section(ini.sections["DEFAULT"]);
  ini.interpolate();
  std::cout << "ini file after default section and interpolation:" << std::endl;
  ini.generate(std::cout);
  int compression_level = -1;
  inipp::get_value(ini.sections["bitbucket.org"], "CompressionLevel", compression_level);
  std::cout << "bitbucket.org compression level: " << compression_level << std::endl;
  return 0;
}