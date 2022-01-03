#include "bufferlist.h"

//constructor
BufferList::BufferList(int minBufCapacity){
  //fixing negative minBufCapacity
  if(minBufCapacity < 1){
    m_minBufCapacity = DEFAULT_MIN_CAPACITY;
  }
  else{
    m_minBufCapacity = minBufCapacity;
  }
  m_cursor = new Buffer(m_minBufCapacity);
  m_cursor->m_next = m_cursor;
  m_listSize = 1;
}

//destructor
BufferList::~BufferList(){
  clear();
}

//clears memory
void BufferList::clear(){
  Buffer* temp = m_cursor;
  while(m_listSize > 0){
    Buffer* next = temp->m_next;
    temp->clear();
    delete temp;
    temp = next;
    m_listSize--;
  }
  m_cursor = nullptr;
}

//enqueues data
void BufferList::enqueue(const int& data) {
  try{
    m_cursor->enqueue(data);
  }
  catch(overflow_error &e){
    Buffer* newBuffer = new Buffer(m_minBufCapacity);
    newBuffer->m_next = m_cursor->m_next;
    m_cursor->m_next = newBuffer;
    m_cursor = newBuffer;
    m_listSize++;
    m_cursor->enqueue(data);
  }
  /*if(m_cursor->full()){//*******EXCEPTION*****
    Buffer* newBuffer = new Buffer(m_minBufCapacity);
    newBuffer->m_next = m_cursor->m_next;
    m_cursor->m_next = newBuffer;
    m_cursor = newBuffer;
    m_listSize++;
    m_cursor->enqueue(data);
  }
  else{
    m_cursor->enqueue(data);
    }*/
}

//dequeues data
int BufferList::dequeue() {
  if(m_cursor->empty()){
    throw underflow_error("Buffer list is empty");
  }
  else if(!m_cursor->m_next->empty()){
    return m_cursor->m_next->dequeue();
  }
  else if(m_cursor->m_next->empty()){
    Buffer* newStart = m_cursor->m_next->m_next;
    m_cursor->m_next->clear();
    delete m_cursor->m_next;
    m_cursor->m_next = newStart;
    m_listSize--;
    return newStart->dequeue();
  }
  return 0;
}

//copy constructor
BufferList::BufferList(const BufferList & rhs){
  m_minBufCapacity = rhs.m_minBufCapacity;
  m_cursor = new Buffer(m_minBufCapacity);
  m_cursor->m_next = m_cursor;
  m_listSize = 1;
  Buffer* temp = rhs.m_cursor->m_next;
  for(int i=0; i<rhs.m_listSize;i++){
    for(int j=0;j<temp->m_count;j++){
      enqueue(temp->m_buffer[j]);
    }
    temp = temp->m_next;
  }
}

//overloaded assignment operator
const BufferList & BufferList::operator=(const BufferList & rhs){
  if(this == &rhs){
    return *this;
	}
  clear();
  m_minBufCapacity = rhs.m_minBufCapacity;
  m_cursor = new Buffer(m_minBufCapacity);
  m_cursor->m_next = m_cursor;
  m_listSize = 1;
  Buffer* temp = rhs.m_cursor->m_next;
  for(int i=0; i<rhs.m_listSize;i++){
    for(int j=0;j<temp->m_count;j++){
      enqueue(temp->m_buffer[j]);
    }
    temp = temp->m_next;
  }
  return *this;
}

//prints out list
void BufferList::dump(){
  Buffer* temp = m_cursor->m_next;
  for(int i=0;i<m_listSize;i++){
    temp->dump();
    temp = temp->m_next;
    cout << endl;
  }
  cout << endl;
}
