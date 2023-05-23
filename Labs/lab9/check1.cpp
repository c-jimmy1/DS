#include <iostream>
#include <fstream>
#include <map>
#include <vector>

void Mode(std::map<std::string, int> &numbers){
  int max = 0;
  std::vector<std::string> modes;
  std::map<std::string, int>::const_iterator itr;
  for (itr = numbers.begin(); itr != numbers.end(); ++itr) {
    if (itr->second > max) {
      max = itr->second;
    }
  }
  for (itr = numbers.begin(); itr != numbers.end(); ++itr) {
    if (itr->second == max) {
      modes.push_back(itr->first);
    }
  }
  std::cout << "Modes: ";
  for (std::string &mode : modes) {
    std::cout << mode << " ";
  }
  std::cout << std::endl;
}

int main(int argc, char *argv[]) {
  std::ifstream inStr(argv[1]);
  std::string num;
  std::map<std::string, int> numbers;

  while (inStr >> num) {
    numbers[num]++;
  }

  Mode(numbers);
  return 0;
}