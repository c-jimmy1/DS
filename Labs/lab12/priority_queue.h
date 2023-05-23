#ifndef priority_queue_h_
#define priority_queue_h_

#include <iostream>
#include <vector>
#include <cassert>


template <class T>
class priority_queue {
private:
  std::vector<T> m_heap;

public:
  priority_queue() {}

  priority_queue( std::vector<T> const& values )
  {
    for (unsigned int i =  0; i <values.size(); ++i) {
      push(values[i]);
    }
  }

  const T& top() const 
  {
    assert( !m_heap.empty() );
    return m_heap[0]; 
  }

  void push( const T& entry )
  {
    m_heap.push_back(entry);
    const unsigned int size = m_heap.size();
    unsigned int current = size - 1;
    while (current != 0) { 
      unsigned int parent = (current - 1) / 2;
      if (m_heap[current] < m_heap[parent]) {
        unsigned int temp = m_heap[current];
        m_heap[current] = m_heap[parent];
        m_heap[parent] = temp;
        current = parent;
      } 
      else {
        break;
      }
    }
  }

  void pop() 
  {
    assert( !m_heap.empty() );
    m_heap[0] = m_heap.back();
    m_heap.pop_back();

    unsigned int index = 0;
    if (index < 0 || index >= m_heap.size() || m_heap.size() == 1) {
      return;
    }

    int left = (2*index)+1;
    int right = (2*index)+2;
    int size = m_heap.size();
    int child; 

    while (left < size) {
      if (right < size && m_heap[right] < m_heap[left]) {
        child = right; 
      }
      else {
        child = left; 
      }

      if (m_heap[index] >= m_heap[child]) {
        int temp = m_heap[index]; 
        m_heap[index] = m_heap[child]; 
        m_heap[child] = temp;

        index = child; 
        left = (2*index)+1; 
        right = left+1; 
      }
      else {
        break;
      }
    }
  }

  int size() { return m_heap.size(); }
  bool empty() { return m_heap.empty(); }


  //  The following three functions are used for debugging.

  //  Check to see that internally the heap property is realized.
  bool check_heap( )
  {
    return this->check_heap( this->m_heap );
  }

  //  Check an external vector to see that the heap property is realized.
  bool check_heap( const std::vector<T>& heap )
  {
    unsigned int size = heap.size();
    for (unsigned int i = 0; i < size; ++i) {
      unsigned int left = i * 2 + 1;
      unsigned int right = i * 2 + 2;
      if (left < size && heap[i] > heap[left]) {
        return false;
      }
      if (right < size && heap[i] > heap[right]) {
        return false;
      }
    }
    return true;
  }

  //  A utility to print the contents of the heap.  Use it for debugging.
  void print_heap( std::ostream & ostr )
  {
    for ( unsigned int i=0; i<m_heap.size(); ++i )
      ostr << i << ": " << m_heap[i] << std::endl;
  }
  
};


template <class T>
void heap_sort( std::vector<T> & v )
{
  if (v.size() == 0 || v.size() == 1) return;
  
  const unsigned int size = v.size();
  for (int i = size / 2 - 1; i >= 0; --i) {
    unsigned int parent = i;
    unsigned int child = parent * 2 + 1;
    while (child < size) {
      if (child + 1 < size && v[child] < v[child + 1]) child += 1;
      if (v[parent] < v[child]) {
        std::swap(v[parent], v[child]);
        parent = child;
        child = parent * 2 + 1;
      } else break;
    }
  }
  
  for (unsigned int i = size - 1; i > 0; i--) {
    std::swap(v[0], v[i]);
    
    unsigned int parent = 0;
    unsigned int child = parent * 2 + 1;
    while (child < i) {
      if (child + 1 < i && v[child] < v[child + 1]) child += 1;
      if (v[parent] < v[child]) {
        std::swap(v[parent], v[child]);
        parent = child;
        child = parent * 2 + 1;
      } else break;
    }
  }
}

#endif
