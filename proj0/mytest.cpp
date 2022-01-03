#include <iostream>
using namespace std;

/*#include "puzzle.h"

class Tester{//this is your tester class, you add your test functions in this class
public:
  bool testCopyConstructor(const Puzzle& puzzle);
  bool testAssignmentOperator(const Puzzle& puzzle);
  void measureInsertionTime(int numTrials, int N);
  void measureCopyTime(int numTrials, int N);
};

int main() {
  Tester tester;
  {
    cout << "\n***************Copy Constructor***************\n";
    //test deep copy, object with many members
    Puzzle p1(1000);
    cout << "Test case, Copy Constructor: same members, same size, different pointers (deep copy):" << endl;
    if (tester.testCopyConstructor(p1)) cout << "Copy constructor passed!" << endl;
    else cout << "Copy constructor failed!" << endl;
  }
  {
    //test the edge case, object with 1 member
    cout << "\nTest case, Copy Constructor: 1 member:" << endl;
    Puzzle p1(1);
    if (tester.testCopyConstructor(p1)) cout << "Copy constructor passed!" << endl;
    else cout << "Copy constructor failed!" << endl;
  }
  {
    //test the edge case, 0 member, i.e. empty object
    cout << "\nTest case, Copy Constructor: zero members:" << endl;
    Puzzle p1(0);
    if (tester.testCopyConstructor(p1)) cout << "Copy constructor passed!" << endl;
    else cout << "Copy constructor failed!" << endl;
  }
  {
    //test the user error case, creating object with table size less than 0
    cout << "\nTest case, Copy Constructor: table size less than 0:" << endl;
    Puzzle p1(-10);
    if (tester.testCopyConstructor(p1)) cout << "Copy constructor passed!" << endl;
    else cout << "Copy constructor failed!" << endl;
  }
  cout << "\n***************Assignment Operator***************\n";
  {
    //test deep copy, object with many members
    Puzzle p1(1000);
    cout << "Test case, Assignment Operator: same members, same size, different pointers (deep copy):" << endl;
    if (tester.testAssignmentOperator(p1)) cout << "Assignment Operatorr passed!" << endl;
    else cout << "Assignment Operator failed!" << endl;
  }
  {
    //test the edge case, object with 1 member
    cout << "\nTest case, Assignment Operator: 1 member:" << endl;
    Puzzle p1(1);
    if (tester.testAssignmentOperator(p1)) cout << "Assignment Operator passed!" << endl;
    else cout << "Assignment Operator failed!" << endl;
  }
  {
    //test the edge case, 0 member, i.e. empty object
    cout << "\nTest case, Assignment Operator: zero members:" << endl;
    Puzzle p1(0);
    if (tester.testAssignmentOperator(p1)) cout << "Assignment Operator passed!" << endl;
    else cout << "Assignment Operator failed!" << endl;
  }
  {
    //test the user error case, creating object with table size less than 0
    cout << "\nTest case, Assignment Operator: table size less than 0:" << endl;
    Puzzle p1(-10);
    if (tester.testAssignmentOperator(p1)) cout << "Assignment Operator passed!" << endl;
    else cout << "Assignment Operator failed!" << endl;
  }
  cout << "\n***************Insertion Time***************\n";
  {
    //Measuring the efficiency of insertion functionality
    cout << "\nMeasuring the efficiency of insertion functionality:" << endl;
    int M = 5;//number of trials
    int N = 1000;//original input size
    tester.measureInsertionTime(M, N);
  }
  cout << "\n***************Copy Time***************\n";
  {
    //Measuring the efficiency of copy constructor
    cout << "\nMeasuring the efficiency of the copy constructor:" << endl;
    int M = 5;//number of trials
    int N = 100;//original input size
    Puzzle p1(N);
    tester.measureCopyTime(M, N);
  }
  cout << "\n***************Dump Test***************\n";
  {
    //an example of dump
    cout << "\nHere is an example of a table:" << endl;
    Puzzle p1(10);
    p1.dump();
    cout << endl;
  }
  return 0;
}

bool Tester::testCopyConstructor(const Puzzle& puzzle){
  Puzzle copy(puzzle);
  //the case of empty object
  if (puzzle.m_size == 0 && copy.m_size == 0) return true;
  //the case that sizes are the same and the table pointers are not the same
  else if (puzzle.m_size == copy.m_size && puzzle.m_table != copy.m_table){
    for (int i=0;i<puzzle.m_size;i++){
      for (int j=0;j<puzzle.m_size;j++)
	{
	  if ((puzzle.m_table[i][j] != copy.m_table[i][j]) || //check the value
	      (puzzle.m_table[i] == copy.m_table[i])){        //check the ith pointer
	    return false;
	  }
	}
    }
    return true;
  }
  //everything else
  else return false;
}

bool Tester :: testAssignmentOperator(const Puzzle& puzzle){
  Puzzle copy(1);
  copy = puzzle;
  if (puzzle.m_size == 0 && copy.m_size == 0) return true;
  //the case that sizes are the same and the table pointers are not the same
  else if (puzzle.m_size == copy.m_size && puzzle.m_table != copy.m_table){
    for (int i=0;i<puzzle.m_size;i++){
      for (int j=0;j<puzzle.m_size;j++)
	{
	  if ((puzzle.m_table[i][j] != copy.m_table[i][j]) || //check the value
	      (puzzle.m_table[i] == copy.m_table[i])){        //check the ith pointer
	    return false;
	  }
	}
    }
    return true;
  }
  //everything else
  else return false;
}

void Tester::measureInsertionTime(int numTrials, int N)
{
  //Measuring the efficiency of insertion algorithm with system clock ticks
  //Clock ticks are units of time of a constant but system-specific length, as those returned by function clock().
  //Dividing a count of clock ticks by CLOCKS_PER_SEC yields the number of seconds.
  const int a = 2;//scaling factor for input size
  double T = 0.0;//to store running times
  clock_t start, stop;//stores the clock ticks while running the program
  for (int k=0;k<numTrials-1;k++)
    {
      start = clock();
      Puzzle p1(N);//the algorithm to be analyzed for efficiency
      stop = clock();
      T = stop - start;//number of clock ticks the algorithm took
      cout << "Inserting " << N * N << " members took " << T << " clock ticks ("<< T/CLOCKS_PER_SEC << " seconds)!" << endl;
      N = N * a;//increase the input size by the scaling factor
    }
}

void Tester :: measureCopyTime(int numTrials, int N){
  //Measuring the efficiency of insertion algorithm with system clock ticks
  //Clock ticks are units of time of a constant but system-specific length, as those returned by function clock().
  //Dividing a count of clock ticks by CLOCKS_PER_SEC yields the number of seconds.
  const int a = 2;//scaling factor for input size
  double T = 0.0;//to store running times
  clock_t start, stop;//stores the clock ticks while running the program
  for (int k=0;k<numTrials;k++)
    {
      Puzzle puzzle(N);
      start = clock();
      Puzzle copy = puzzle;
      stop = clock();
      T = stop - start;//number of clock ticks the algorithm took
      cout << "Copying " << N*N << " members  took " << T << " clock ticks ("<< T/CLOCKS_PER_SEC << " seconds)!" << endl;
      N = N * a;//increase the input size by the scaling factor
    }
}

*/

void buildMatrix(int **matrix, int m, int n){
  int init = 10;
  // matrix = new int*[m];
  // cout << "Making matrix\n";
  for(int i = 0; i < m; i++){
    cout << "making variable " << i << endl;
    matrix[i] = new int[n];
  }
}

void deleteMatrix(int **matrix, int m){
  for (int i=0;i<m;i++){
    cout << "deleting variable " << i << endl;
    delete [] matrix[i];
  }
  cout << "deleting matrix\n";
  delete [] matrix;
}

int main(){
  int **array = new int*[2];
  buildMatrix(array, 2, 2);
  deleteMatrix(array, 2);
  return 0;
}
