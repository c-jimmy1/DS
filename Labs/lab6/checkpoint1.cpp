#include <iostream>
#include <string>
#include <vector>


template <class T>
void print(std::vector<T> &data, const std::string &label) {
  std::cout << label << " ";
  for (int i = 0; i < (int)data.size(); i++) {
    std::cout << " " << data[i];
  }
  std::cout << std::endl;
}


template <class T>
void reverse(std::vector<T> &data) {

  // FILL IN THIS FUNCTION
  for (unsigned int i = 0, j = data.size() - 1; i < data.size(); i++, j--) {
    if(i < data.size()/2){ // Prevents undoing the reverse 
      T temp = data[i];
      data[i] = data[j]; // Setting the last index's value to the first
      data[j] = temp; // setting the first index's value to the last
    }
  }
}


int main() {
  std::vector<int> data;
  data.push_back(1);
  data.push_back(2);
  data.push_back(3);
  data.push_back(4);
  data.push_back(5);
  data.push_back(6);
  data.push_back(7);

  print(data,"before:");
  reverse(data);
  print(data,"after: ");

  std::vector<std::string> data2;
  data2.push_back("apple");
  data2.push_back("banana");
  data2.push_back("carrot");
  data2.push_back("date");

  print(data2,"before:");
  reverse(data2);
  print(data2,"after: ");
  
  // EXTRA TESTS
  std::vector<int> data3;
  data3.push_back(1);

  print(data3,"before:");
  reverse(data3);
  print(data3,"after: ");

  std::vector<int> data4;
  data4.push_back(1);
  data4.push_back(2);

  print(data4,"before:");
  reverse(data4);
  print(data4,"after: ");

  std::vector<int> data5;

  print(data5,"before:");
  reverse(data5);
  print(data5,"after: ");
}
