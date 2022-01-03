#include "bufferlist.h"
#include <cstdlib>
#include <ctime>

class Tester{
public:
  bool BufferEnqueueDequeue(Buffer &buffer, int dataCount);
  bool BufListEnqueueDequeue(BufferList &bufferlist, int dataCount);
  bool BufferEnqueueFull(int size);
  bool BufListDequeueEmpty();
  bool BufferCopyConstructor(const Buffer &buffer);
  bool BufListCopyConstructor(const BufferList &bufferlist, int size);
  bool BufListAssignment(const BufferList &bufferlist, int size);
  void BufListEnqueuePerformance(int numTrials, int N);
};
int main(){
  Tester tester;
  int bufferSize = 1000;
  Buffer buffer(bufferSize);
  {
    //testing insertion/removal for 1 data item
    cout << "\nTest case: Buffer class: Inserting/removing 1 data item:\n";
    if (tester.BufferEnqueueDequeue(buffer, 1))
      cout << "\tTest passed!\n";
    else
      cout << "\tTest failed!\n";
  }
  {
    //testing insertion/removal for half data size
    cout << "\nTest case: Buffer class: Inserting/removing half data size:\n";
    if (tester.BufferEnqueueDequeue(buffer, bufferSize/2))
      cout << "\tTest passed!\n";
    else
      cout << "\tTest failed!\n";
  }
  {
    //testing insertion/removal for full data size
    cout << "\nTest case: Buffer class: Inserting/removing full data size:\n";
    if (tester.BufferEnqueueDequeue(buffer, bufferSize))
      cout << "\tTest passed!\n";
    else
      cout << "\tTest failed!\n";
  }
  {
    //testing insertion in a full buffer
    cout << "\nTest case: Buffer class: Throwing exception while inserting in full buffer:\n";
    if (tester.BufferEnqueueFull(1000))
      cout << "\tTest passed!\n";
    else
      cout << "\tTest failed!\n";
  }
  {
    //testing Buffer class copy constructor with buffer size less than zero
    cout << "\nTest case: Buffer class: Copy constructor, negative buffer size:\n";
    Buffer buffer(-10);
    if (tester.BufferCopyConstructor(buffer))
      cout << "\tTest passed!\n";
    else
      cout << "\tTest failed!\n";
  }
  {
    //testing BufferList class copy constructor with one item
    cout << "\nTest case: BufferList class: Copy constructor, 1 item:\n";
    BufferList bufferlist(10);
    bufferlist.enqueue(1);
    if (tester.BufListCopyConstructor(bufferlist,1))
      cout << "\tTest passed!\n";
    else
      cout << "\tTest failed!\n";
  }
  {
    //testing BufferList class copy constructor with 100 items
    cout << "\nTest case: BufferList class: Copy constructor, buffer size 100:\n";
    BufferList bufferlist(10);
    for(int j=0;j<100;j++){
      bufferlist.enqueue(j);
    }
    if (tester.BufListCopyConstructor(bufferlist,100))
      cout << "\tTest passed!\n";
    else
      cout << "\tTest failed!\n";
  }
  {
    //testing BufferList class copy constructor with 10,000 items
    cout << "\nTest case: BufferList class: Copy constructor, buffer size 10,000:\n";
    BufferList bufferlist(10);
    for(int j=0;j<10000;j++){
      bufferlist.enqueue(j);
    }
    if (tester.BufListCopyConstructor(bufferlist,10000))
      cout << "\tTest passed!\n";
    else
      cout << "\tTest failed!\n";
  }
  {
    //testing BufferList class copy constructor with 10,000 items
    cout << "\nTest case: BufferList class: Copy constructor, 10,000 items:\n";
    BufferList bufferlist(10);
    for(int j=0;j<10000;j++){
      bufferlist.enqueue(j);
    }
    if (tester.BufListAssignment(bufferlist,10000))
      cout << "\tTest passed!\n";
    else
      cout << "\tTest failed!\n";
  }
  {
    //testing BufferList class dequeue on empty buffer
    cout << "\nTest case: Bufferlist class: Throwing exception while removing from empty buffer\n";
    BufferList bufferlist(10);
    if (tester.BufListDequeueEmpty())
      cout << "\tTest passed!\n";
    else
      cout << "\tTest failed!\n";
  }
  {
    //testing BufferList class enqueue and dequeue with 1 item
    cout << "\nTest case: Bufferlist class: Inserting/Removing 1 data item:\n";
    BufferList bufferlist(10);
    if (tester.BufListEnqueueDequeue(bufferlist, 1))
      cout << "\tTest passed!\n";
    else
      cout << "\tTest failed!\n";
  }
  {
    //testing BufferList class enqueue and dequeue with 10,000 items
    cout << "\nTest case: Bufferlist class: Inserting/Removing 10,000 data items:\n";
    BufferList bufferlist(10);
    if (tester.BufListEnqueueDequeue(bufferlist, 11))
    	cout << "\tTest passed!\n";
    else
    	cout << "\tTest failed!\n";
	}
  {
    //Measuring the efficiency of insertion functionality
    cout << "\nMeasuring the efficiency of insertion functionality:" << endl;
    int M = 5;//number of trials
    int N = 10000;//original input size
    tester.BufListEnqueuePerformance(M, N);
  }
  {
    //an example of BufferList::dump()
    cout << "\nHere is an example of a linked list:" << endl;
    BufferList bufferList(5);
    for (int i=40;i>0;i--)
      bufferList.enqueue(i);
    bufferList.dump();
  }
  return 0;
}

//testing overflow_error in Buffer
bool Tester::BufferEnqueueFull(int size){
  Buffer aBuffer(size);
  for (int i=0;i<size;i++)
    aBuffer.enqueue(i);
  try{
    //trying to insert in a full buffer
    aBuffer.enqueue(size+1);
  }
  catch(overflow_error &e){
    //the exception that we expect
    return true;
  }
  catch(...){
    //any other exception, this case is not acceptable
    return false;
  }
  //no exception thrown, this case is not acceptable
  return false;
}

//testing enqueue and dequeue
bool Tester :: BufferEnqueueDequeue(Buffer &buffer, int dataCount){
  int starting = buffer.count();
  buffer.enqueue(1);
  if(buffer.count() == starting+1){
    buffer.dequeue();
    if(buffer.count() == starting){
      return true;
    }
    else{
      return false;
    }
  }
  else{
    return false;
  }
}

//testing Buffer copy constructor
bool Tester :: BufferCopyConstructor(const Buffer &buffer){
  Buffer testBuffer(buffer);
  //checking for deep copy
  if(&buffer == &testBuffer){
    return false;
  }
  //checking items match
  for(int i=0;i<buffer.m_capacity;i++){
    if(testBuffer.m_buffer[i] != buffer.m_buffer[i]){
      return false;
    }
  }
  return true;
}

//testing bufferlist copy constructor
bool Tester :: BufListCopyConstructor(const BufferList &bufferlist, int size){
  int counter = 0;
  BufferList testList(bufferlist);
  //checking for deep copy
  if(&bufferlist == &testList){
    return false;
  }
  Buffer* temp = bufferlist.m_cursor;
  Buffer* temp2 = testList.m_cursor;
  for(int i=0;i<bufferlist.m_listSize;i++){
    for(int j=0;j<temp->m_capacity;j++){
      counter++;
      //checking items match
      if(temp->m_buffer[j] != temp2->m_buffer[j]){
	return false;
      }
      if(counter == size){
	return true;
      }
    }
    temp = temp->m_next;
    temp2 = temp;
  }
  return true;
}

//testing bufferlist assignment operator
bool Tester :: BufListAssignment(const BufferList &bufferlist, int size){
  int counter = 0;
  BufferList testList(10);
  testList = bufferlist;
  //checking for deep copy
  if(&bufferlist == &testList){
    return false;
  }
  Buffer* temp = bufferlist.m_cursor;
  Buffer* temp2 = testList.m_cursor;
  for(int i=0;i<bufferlist.m_listSize;i++){
    for(int j=0;j<temp->m_capacity;j++){
      counter++;
      //checking items match
      if(temp->m_buffer[j] != temp2->m_buffer[j]){
	return false;
      }
      if(counter == size){
	return true;
      }
    }
    temp = temp->m_next;
    temp2 = temp;
  }
  return true;
}

//testing enqueue performance
void Tester :: BufListEnqueuePerformance(int numTrials, int N){
  int scaling = 2;
  double time = 0.0;
  clock_t start,stop;
  for(int i=0;i<numTrials;i++){
    BufferList bufferlist(10);
    start = clock();
    for(int j=0;j<N;j++){
      bufferlist.enqueue(j);
    }
    stop = clock();
    time = stop-start;
    cout << "Enqueuing " << N << " members took " << time << " clock ticks (" << time/CLOCKS_PER_SEC << " seconds!)\n";
    N *= scaling;
  }
}

//testing bufferlist enqueue and dequeue
bool Tester :: BufListEnqueueDequeue(BufferList &bufferlist, int dataCount){
  for(int i=0;i<dataCount;i++){
    bufferlist.enqueue(i);
  }
  for(int i=0;i<dataCount;i++){
    bufferlist.dequeue();
  }
  return true;
}

//testing underflow error for bufferlist
bool Tester :: BufListDequeueEmpty(){
  BufferList bufferlist(1);
  try{
    //trying to insert in an empty buffer
    bufferlist.dequeue();
  }
  catch(underflow_error &e){
    //the exception that we expect
    return true;
  }
  catch(...){
    //any other exception, this case is not acceptable
    return false;
  }
  //no exception thrown, this case is not acceptable
  return false;
}


