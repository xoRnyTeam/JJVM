
#include <cstring>
#include <iostream>
#include <jjvm.hpp>
//
#include "timer.hpp"

void parse(int argc, char **argv, std::string &class_name, std::string &lang) {
  if (argc < 3) {
    std::cout
        << "Error. It is necessary to specify the file class name at the input"
        << std::endl;
    exit(1);
  } else if (argc == 3) {
    class_name = argv[2];
    for (auto& c : class_name) {
        if (c == '.') {
            c = '/';
        }
    }
    lang = argv[1] + strlen("--lib=");
  } else {
    std::cout << "Error. incorrect number of input arguments" << std::endl;
    std::cout << "Example: Usage ./jjvm Middle" << std::endl;
    exit(3);
  }
}

int main(int argc, char **argv) {
  std::string class_name, lang;
  parse(argc, argv, class_name, lang);
  vm::jjvm jjvm(lang);

  timer::Timer timer{};
  jjvm.execute(class_name);
  std::cout << timer.elapsed<timer::Timer::microsecs>() << " microseconds\n";

  std::cout << "END!" << std::endl;

  return 0;
}
