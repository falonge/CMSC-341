// CMSC 341 - Spring 2021 - Project 3
// RQueue: 

#include "rqueue.h"
using namespace std;
using std::cout;
using std::endl;
using std::domain_error;

RQueue::RQueue(prifn_t priFn)
{
  _heap = nullptr;
  _size = 0;
  priority = priFn;
}

RQueue::~RQueue()
{
  clear();
}

RQueue::RQueue(const RQueue& rhs)
{
  if(rhs._size == 0){
    cout << "Queue is empty.\n";
  }
  else{
    _heap = rhs._heap;
    _size = rhs._size;
    priority = rhs.priority;
    copyNodes(_heap, rhs._heap);
  }
}


RQueue& RQueue::operator=(const RQueue& rhs)
{
  if(this == &rhs){
    cout << "Self Assignment.\n";
  }
  else{
    clear();
    _heap = rhs._heap;
    _size = rhs._size;
    priority = rhs.priority;
    copyNodes(_heap, rhs._heap);
    return *this;
  }
}

void RQueue::insertStudent(const Student& input) {
  Node* newNode = new Node(input);
  _heap = merge(newNode, _heap);
  _size++;
}

Student RQueue::getNextStudent() {
  if(_heap == nullptr){
    throw domain_error("Queue is empty");
  }
  string name = _heap->getStudent().getName();
  int studentPriority = _heap->getStudent().getPriority();
  int year = _heap->getStudent().getYear();
  int major = _heap->getStudent().getMajor();
  int group = _heap->getStudent().getGroup();
  Student removed(name, studentPriority, year, major, group);
  Node* left = _heap->_left;
  Node* right = _heap->_right;
  delete _heap;
  _heap = nullptr;
  _heap = merge(left, right);
  _size--;
  return removed;
}


void RQueue::mergeWithQueue(RQueue& rhs) {
  if(rhs.priority != priority){
    throw domain_error("Queues have different priority functions");
  }
  if(this != &rhs){
    _heap = merge(_heap,rhs._heap);
    _size += rhs._size;
    rhs._heap = nullptr;
    rhs._size = 0;
  }
}

Node* RQueue :: merge(Node* queue1, Node* queue2){
  if(queue1 == nullptr){
    return queue2;
  }
  if(queue2 == nullptr){
    return queue1;
  }
  if(priority(queue1->getStudent()) > priority(queue2->getStudent())){
    swap(queue1,queue2);
  }
  swap(queue1->_left, queue1->_right);
  queue1->_left = merge(queue1->_left, queue2);
  return queue1;
}

void RQueue::clear() {
  clearAllNodes(_heap);
}

void RQueue :: clearAllNodes(Node* node){
  if(node == nullptr){
    return;
  }
  else{
    clearAllNodes(node->_left);
    clearAllNodes(node->_right);
    delete node;
  }
}

int RQueue::numStudents() const
{
  return _size;
}

void RQueue::printStudentQueue() const {
  print(_heap);
}

void RQueue :: print(Node* node) const{
  if(node == nullptr){
    return;
  }
  else{
    cout << "[" << priority(node->getStudent()) << "] " << node->getStudent() << endl;
    print(node->_left);
    print(node->_right);
  }
}

prifn_t RQueue::getPriorityFn() const {
  return priority;
}

void RQueue::setPriorityFn(prifn_t priFn) {
  RQueue newRqueue(priFn);
  while(_heap != nullptr){
	  newRqueue.insertStudent(getNextStudent());
  }
  _heap = newRqueue._heap;
  newRqueue._heap = nullptr;
  _size = newRqueue._size;
  priority = priFn;
}

void RQueue :: copyNodes(Node*& node1, Node* node2) const{
  if(node2 == nullptr){
    node1 = nullptr;
  }
  else{
    node1 = new Node(node2->getStudent());
    copyNodes(node1->_left, node2->_left);
    copyNodes(node1->_right, node2->_right);
  }
}

// for debugging
void RQueue::dump() const
{
  if (_size == 0) {
    cout << "Empty skew heap.\n" ;
  } else {
    dump(_heap);
    cout << endl;
  }
}

// for debugging
void RQueue::dump(Node *pos) const {
  if ( pos != nullptr ) {
    cout << "(";
    dump(pos->_left);
    cout << priority(pos->_student) << ":" << pos->_student.getName();
    dump(pos->_right);
    cout << ")";
  }
}

// overloaded insertion operator for Student class
ostream& operator<<(ostream& sout, const Student& student) {
  sout << "Student: " << student.getName() << ", priority: " << student.getPriority()
       << ", year: " << student.getYear() << ", major: " << student.getMajorStr() 
       << ", group: " << student.getGroupStr();
  return sout;
}

// overloaded insertion operator for Node class
ostream& operator<<(ostream& sout, const Node& node) {
  sout << node.getStudent();
  return sout;
}
