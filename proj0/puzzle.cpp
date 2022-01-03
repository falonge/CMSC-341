#include "puzzle.h"

//constructor
Puzzle::Puzzle(int size){
  if(size <= 0){
    m_size = 0;
    m_table = nullptr;
  }
  else{
    m_size = size;
    makeMem();
    fill();
  }
}

//destructor
Puzzle::~Puzzle(){
  clear();
}

//deletes each member of m_table
void Puzzle::clear(){
  //for loop deleting each member in m_table
  for(int i=0;i<m_size;i++){
    delete[] m_table[i];
    m_table[i] = nullptr;
  }
  delete[] m_table; //deleting m_table
  m_table = nullptr;
}

//allocating memory for m_table
void Puzzle::makeMem(){
  m_table = new char*[m_size];
  for(int i=0;i<m_size;i++){
    m_table[i] = new char[m_size];
  }
}

//copy constructor
Puzzle::Puzzle(const Puzzle& rhs){
  //checking if user enters 0 or negative number when making a Puzzle
  if(rhs.m_size <= 0){
    m_size = 0;
    m_table = nullptr;
  }
  else{
    m_size = rhs.m_size;
    makeMem();
    //copying by assigning each value to the corresponding one in rhs
    for(int i=0;i<m_size;i++){
      for(int j=0;j<m_size;j++){
	m_table[i][j] = rhs.m_table[i][j];
      }
    }
  }
}

//overloaded assignment operator
const Puzzle& Puzzle::operator=(const Puzzle& rhs){
  //checking for self-assignment
  if(this == &rhs){
    return *this;
  }
  //checking if user enters 0 or negative number
  else if(rhs.m_size <= 0){
    clear();
    m_size = 0;
    m_table = nullptr;
  }
  else{
    clear();
    m_size = rhs.m_size;
    makeMem();
    //copying
    for(int i=0;i<m_size;i++){
      for(int j=0;j<m_size;j++){
        m_table[i][j] = rhs.m_table[i][j];
      }
    }
  }
  return *this;
}

//displays m_table
void Puzzle::dump(){
  if (m_size > 0){
    int i=0;
    int j=0;
    while(i<m_size){
      while(j<m_size){
	cout << m_table[i][j] << " ";
	j++;
      }
      cout << endl;
      j=0;
      i++;
    }
    cout << endl;
  }
}

//fills m_table
void Puzzle::fill(){
  srand(time(NULL));//create the seed value using the current time
  int i=0;
  int j=0;
  while(i<m_size){
    while(j<m_size){
      m_table[i][j] = ALPHA[rand() % MAX];//find a random char from the chars list
      j++;
    }
    j=0;
    i++;
  }
}
