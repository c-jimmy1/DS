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
  std::map<std::string, int> numbers;
  std::string num;
  while (inStr >> num) {
    if (numbers.find(num) == numbers.end()){
      numbers.insert(std::pair<std::string, int>(num, 1));
    }
    else { 
      numbers.find(num)->second += 1;
    }
  }

  Mode(numbers);
  return 0;
}