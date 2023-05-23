#include <iostream>
#include <string>
#include <list>


template <class T>
void print(std::list<T> &data, const std::string &label) {
  std::cout << label << " ";
  typename std::list<T>::iterator i;

  for (i = data.begin(); i != data.end(); ++i) {
    std::cout << " " << *i;
  }
  std::cout << std::endl;
}


template <class T>
void reverse(std::list<T> &data) {

  // FILL IN THIS FUNCTION
  typename std::list<T>::iterator i;

  unsigned int counter = 0;
  for(i = data.begin(); i != data.end(); ++i) {
    if (counter != data.size()-1) {
    T temp = data.back();
    i = data.insert(i, temp);
    data.pop_back();
    }
    counter++;
  }
}

int main() {
  std::list<int> data;
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

  std::list<std::string> data2;
  data2.push_back("apple");
  data2.push_back("banana");
  data2.push_back("carrot");
  data2.push_back("date");

  print(data2,"before:");
  reverse(data2);
  print(data2,"after: ");
  
  // EXTRA TESTS
  std::list<int> data3;
  data3.push_back(1);

  print(data3,"before:");
  reverse(data3);
  print(data3,"after: ");

  std::list<int> data4;
  data4.push_back(1);
  data4.push_back(2);

  print(data4,"before:");
  reverse(data4);
  print(data4,"after: ");

  std::list<int> data5;

  print(data5,"before:");
  reverse(data5);
  print(data5,"after: ");
}