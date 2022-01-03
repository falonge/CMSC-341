#include "buffer.h"

//constructor
Buffer::Buffer(int capacity){
  //fixing negative capacity
  if(capacity <= 0){
    m_capacity = 0;
  }
  else{
    m_capacity = capacity;
  }
  m_buffer = new int[m_capacity];
  m_count = 0;
  m_start = 0;
  m_end = 0;
  m_next = nullptr;
}

//clears data
void Buffer::clear(){
  delete[] m_buffer;
  m_buffer = nullptr;;
  m_count = 1;
  m_start = 0;
  m_end = 0;
  m_next = nullptr;
}

//destructor
Buffer::~Buffer(){
  clear();
}

//returns count
int Buffer::count(){return m_count;}

//returns capacity
int Buffer::capacity(){return m_capacity;}

//returns whether the buffer is full or not
bool Buffer::full(){
  if(m_count >= m_capacity){
    return true;
  }
  return false;
}

//returns whether the buffer is empty or not
bool Buffer::empty(){
  if(m_count == 0){
    return true;
  }
  return false;
}

//enqueues data
void Buffer::enqueue(int data){
  if(!full()){
    m_buffer[m_end] = data;
    m_count++;
    m_end = (m_end + 1) % m_capacity;
  }
  else{
    throw overflow_error("List is full\n");
  }
}

//dequeues data
int Buffer::dequeue(){
  int removed = m_buffer[m_start];
  if(!empty()){
    m_count--;
    m_start = (m_start + 1) % m_capacity;
    return removed;
  }
  else{
    throw underflow_error("List is empty\n");
  }
}

//copy constructor
Buffer::Buffer(const Buffer & rhs){
  if(rhs.m_capacity <= 0){
    m_capacity = 0;
  }
  else{
    m_capacity = rhs.m_capacity;
  }
  m_buffer = new int[m_capacity];
  int i = rhs.m_start;
  while (i != rhs.m_end) {
    m_buffer[i];
    i += 1;
    i = i % rhs.m_capacity;
  }
  m_count = rhs.m_count;
  m_start = rhs.m_start;
  m_end = rhs.m_end;
  m_next = rhs.m_next;
}
//overloaded assignment operator
const Buffer & Buffer::operator=(const Buffer & rhs){
  if(this == &rhs){
    return *this;
  }
  m_capacity = rhs.m_capacity;
  m_buffer = new int[m_capacity];
  for(int i=rhs.m_start;i<=rhs.m_end;i++){
    m_buffer[i] = rhs.m_buffer[i];
  }
  m_count = rhs.m_count;
  m_start = rhs.m_start;
  m_end = rhs.m_end;
  m_next = rhs.m_next;
  return *this;
}

//prints data
void Buffer::dump(){
  int start = m_start;
  int end = m_end;
  int counter = 0;
  cout << "Buffer size: " << m_capacity << " : ";
  if (!empty()){
    while(counter < m_count){
      cout << m_buffer[start] << "[" << start << "]" << " ";
      start = (start + 1) % m_capacity;
      counter++;
    }
    cout << endl;
  }
  else cout << "Buffer is empty!" << endl;
}
