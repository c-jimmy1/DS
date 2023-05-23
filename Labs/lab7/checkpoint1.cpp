#include <iostream>
#include <string>


// Note: It's ok that all the member variables are public for this
// tiny class.  We'll build up to a more robust and complete linked
// list implementation in lecture 10.
template <class T>
class Node {
public:
  T value;
  Node<T> *ptr;
};



template <class T>
void print(Node<T> *data, const std::string &label) {
  std::cout << label;
  Node<T> *tmp = data;
  while (tmp != NULL) {
    std::cout << " " << tmp->value;
    tmp = tmp->ptr;
  }
  std::cout << std::endl;
}



template <class T>
void reverse(Node<T>* &input) {
  Node<T>* previous = NULL;
  Node<T>* current = input;
  Node<T>* next = NULL;


  while (current != NULL) {
    next = current->ptr;
    current->ptr = previous;
    previous = current;
    current = next;
  }
  input = previous;

}




int main() {

  // manually create a linked list of notes with 4 elements
  Node<int>* my_list = new Node<int>; 
  my_list->value = 1; 
  my_list->ptr = new Node<int>;
  my_list->ptr->value = 2;
  my_list->ptr->ptr = new Node<int>;
  my_list->ptr->ptr->value = 3;
  my_list->ptr->ptr->ptr = new Node<int>;
  my_list->ptr->ptr->ptr->value = 4;
  my_list->ptr->ptr->ptr->ptr = NULL;

  
  print(my_list,"my_list before");
  reverse(my_list);
  print(my_list,"my_list after ");

  Node<int>* my_list2 = new Node<int>; 
  my_list2->value = 1; 
  print(my_list2,"my_list before");
  reverse(my_list2);
  print(my_list2,"my_list after ");

  Node<int>* my_list3 = new Node<int>; 
  my_list3->value = 1; 
  my_list->ptr = new Node<int>;
  my_list->ptr->value = 2;
  print(my_list3,"my_list before");
  reverse(my_list3);
  print(my_list3,"my_list after ");

  // Note: We are not deleting any of the Nodes we created...  so this
  // program has memory leaks!  More on this in Checkpoint 2!

}

// ===========================================================================
