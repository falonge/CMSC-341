// CMSC 341 - Spring 2021 - Project 4
// hash.cpp
// The impleme ntation of the class HashTable
#include "hash.h"
#include "math.h"
HashTable::HashTable(unsigned size, hash_fn hash){
	m_capacity = size;
	while(!isPrime(m_capacity)){
			m_capacity++;
	}
	if(size < MINPRIME){
		m_capacity = MINPRIME;
	}
	else if(size > MAXPRIME){
		m_capacity = MAXPRIME;
	}
	m_hash = hash;
    m_size = 0;
    m_numDeleted = 0;
    m_table = new Person[m_capacity];
    for(unsigned int i=0;i<m_capacity;i++){
    	m_table[i] = EMPTY;
    }
    m_currentProb = LINEAR;
}

HashTable::~HashTable(){
	for(unsigned int i=0;i<m_capacity;i++){
		m_table[i] = EMPTY;
	}
    delete[] m_table;
    m_table = nullptr;
}

void HashTable :: rehashInsert(){
	int sizeCounter = 0;
	for(int i=0;i<m_capacity;i++){
		if(m_table[i].key() != "DELETED"){
			sizeCounter++;
		}
	}
	Person tempTable[sizeCounter];
	int secondIndex = 0;
	for(unsigned int i=0;i<m_capacity;i++){
		if(!m_table[i].key().empty() && m_table[i].key() != "DELETED"){
			tempTable[secondIndex] = m_table[i];
			secondIndex++;
		}
	}
	m_capacity = 4 * m_size;
	while(!isPrime(m_capacity)){
		m_capacity++;
	}
	delete[] m_table;
	m_table = new Person[m_capacity];
	for(unsigned int i=0;i<m_capacity;i++){
		m_table[i] = EMPTY;
	}
	m_size = 0;
	for(unsigned int i=0;i<secondIndex;i++){
		insert(tempTable[i]);
	}
}

void HashTable :: rehashDelete(){
	int sizeCounter = 0;
	int secondIndex = 0;
	for(unsigned int i=0;i<m_capacity;i++){
		if(m_table[i].key() != "DELETED" && !m_table[i].key().empty()){
			sizeCounter++;
		}
	}
	Person tempTable[sizeCounter];
	for(unsigned int i=0;i<m_capacity;i++){
		if(m_table[i].key() != "DELETED" && !m_table[i].key().empty()){
			tempTable[secondIndex] = m_table[i];
			secondIndex++;
		}
	}
	m_capacity = 4 * sizeCounter;
	while(!isPrime(m_capacity)){
		m_capacity++;
	}
	delete[] m_table;
	m_table = new Person[m_capacity];
	for(unsigned int i=0;i<m_capacity;i++){
		m_table[i] = EMPTY;
	}
	m_numDeleted = 0;
	m_size = 0;
	for(unsigned int i=0;i<38;i++){
		insert(tempTable[i]);
	}
}


bool HashTable::insert(Person person){
    if(m_currentProb == LINEAR){
    	if(insertLinear(person,0)){
    		setProbingPolicy(LINEAR);
    		return true;
    	}
    	else{
    		return false;
    	}
    }
    else if(m_currentProb == QUADRATIC){
    	if(insertQuadratic(person,0)){
    		setProbingPolicy(QUADRATIC);
    		return true;
    	}
    	else{
    		return false;
    	}

    }
}

bool HashTable :: insertLinear(Person person, int index){
	int currentBucket = (m_hash(person.key())+index) % m_capacity;
	if(person == m_table[currentBucket]){
		return false;
	}
	else{
		if(m_table[currentBucket] == EMPTY){
			m_table[currentBucket] = Person(person);
			m_size++;
			return true;
		}
		else{
			return insertLinear(person, index+1);
		}
	}
}

bool HashTable :: insertQuadratic(Person person, int index){
	int currentBucket = ((m_hash(person.key()) % m_capacity) + (index*index)) % m_capacity;
	if(person == m_table[currentBucket]){
		return false;
	}
	else{
		if(m_table[currentBucket] == EMPTY){
			m_table[currentBucket] = Person(person);
			m_size++;
			return true;
		}
		else{
			return insertQuadratic(person, index+1);
		}
	}
}

bool HashTable::remove(Person person){
    if(m_currentProb == LINEAR){
    	if(removeLinear(person, 0)){
    		setProbingPolicy(LINEAR);
    		return true;
    	}
    	else{
    		return false;
    	}
    }
    else if(m_currentProb == QUADRATIC){
    	if(removeQuadratic(person, 0)){
    		setProbingPolicy(QUADRATIC);
    		return true;
    		}
    	}
    	else{
    		return false;
    	}
}

bool HashTable :: removeLinear(Person person, int index){
	for(unsigned int i=0;i<m_capacity;i++){
		if(m_table[i] == person){
			m_table[i] = DELETED;
			m_numDeleted++;
		}
	}
}

bool HashTable :: removeQuadratic(Person person, int index){
	for(unsigned int i=0;i<m_capacity;i++){
		if(m_table[i] == person){
			m_table[i] = DELETED;
			m_numDeleted++;
		}
	}
}

void HashTable::setProbingPolicy(probing prob){
	m_currentProb = prob;
	if(m_currentProb == LINEAR){
		if(lambda() > .5){
			rehashInsert();
			return;
		}
		else if(deletedRatio() > .25){
			rehashDelete();
			return;
		}
	}
	else if(m_currentProb == QUADRATIC){
		if(lambda() > .5){
			rehashInsert();
			return;
		}
		else if(deletedRatio() > .25){
			rehashDelete();
			return;
		}
	}
}

float HashTable::lambda() const {
     return float(m_size)/float(m_capacity);
}

float HashTable::deletedRatio() const {
    return float(m_numDeleted)/float(m_size);
}

void HashTable::dump() const {
  for (int i = 0; i < m_capacity; i++) {
    cout << "[" << i << "] : " << m_table[i] << endl;
  }
}

bool HashTable::isPrime(int number){
    // If number is prime this function returns true
    // otherwise it returns false
    bool result = true;
    for (int i = 2; i <= number / 2; ++i) {
        if (number % i == 0) {
            result = false;
            break;
        }
    }
    return result;
}

int HashTable::findNextPrime(int current){
    //we won't go beyond MAXPRIME
    //the smallest prime would be next after MINPRIME
    if (current < MINPRIME) current = MINPRIME;
    for (int i=current; i<MAXPRIME; i++) { 
        for (int j=2; j*j<=i; j++) {
            if (i % j == 0) 
                break;
            else if (j+1 > sqrt(i) && i != current) {
                return i;
            }
        }
    }
    //if a user tries to go over MAXPRIME
    return MAXPRIME;
}
