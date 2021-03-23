#ifndef HASHTABLE_H_
#define HASHTABLE_H_
#include <vector>

using namespace std;
 
template <class HashedObj>
class HashTable
{
public:
    HashTable(int size = 101):array(nextPrime(size)),currentSize(0){}
	HashTable(const HashTable & rhs):array(rhs.array),currentSize(rhs.currentSize){ }
	const HashedObj & find(const HashedObj & x) const;
	//void makeEmpty( );
	void insert(const HashedObj & x);
    void remove(const HashedObj & x);
	int findPos(const HashedObj & x)const;
	const HashedObj & returnElement(int i) const;
	const HashTable & operator=( const HashTable & rhs );

	enum EntryType {ACTIVE,EMPTY, DELETED};
 
private:
    struct HashEntry
	{
        HashedObj element;
        EntryType info;
		HashEntry(const HashedObj & e = HashedObj(), EntryType i = EMPTY):element(e), info(i){ }
    };
	vector<HashEntry> array;
	int currentSize;
	const HashedObj ITEM_NOT_FOUND;
	bool isActive( int currentPos ) const;
	
	void rehash( );
};
 int nextPrime(int n);
 bool isPrime(int n);
 int hash(string, int);
 
 template <class HashedObj>
int HashTable<HashedObj>::findPos( const HashedObj & x ) const
{
    int collisionNum = 0;
    int currentPos = hashing( x, array.size( ));
	while(array[currentPos].info != EMPTY && array[currentPos].element != x)
            {
                   currentPos += 2 * ++collisionNum-1;  // add the difference
                   if(currentPos >= array.size())            // perform the mod
                       currentPos-= array.size();                // if necessary
            }

     return currentPos;
}

template <class HashedObj>
bool HashTable<HashedObj>::isActive(int currentPos)const
{
    return array[currentPos].info == ACTIVE;
}
 
template <class HashedObj>
void HashTable<HashedObj>::remove(const HashedObj & x)
{
    int currentPos = findPos(x);
    if( isActive(currentPos))
        array[currentPos].info = DELETED;
}
 
template <class HashedObj>
const HashedObj & HashTable<HashedObj>::find(const HashedObj & x)const
{
    int currentPos = findPos(x);
    if (isActive(currentPos)) 
        return array[currentPos].element; 
	return  ITEM_NOT_FOUND;
}
 
template <class HashedObj>
void HashTable<HashedObj>::insert(const HashedObj & x)
{
    // Insert x as active
    int currentPos = findPos(x);
    if( isActive(currentPos))
       return;
    array[currentPos] = HashEntry(x, ACTIVE);
 
    // enlarge the hash table if necessary 
    if(++currentSize >= array.size( )/2)
        rehash( );
}
 
template <class HashedObj>
void HashTable<HashedObj>::rehash( )
{
    vector<HashEntry> oldArray = array;
 
    // Create new double-sized, empty table
    array.resize( nextPrime(2 * oldArray.size()));
    for(int j = 0;j< array.size( ); j++)
        array[j].info = EMPTY;
 
    // Copy table over
    currentSize = 0;
    for( int i = 0; i < oldArray.size(); i++)
        if(oldArray[i].info == ACTIVE)
            insert(oldArray[i].element);
}

template <class HashedObj>
const HashedObj &  HashTable<HashedObj>::returnElement(int i) const
{
    if(array[ i ].info==ACTIVE)
        return array[i].element;
    return ITEM_NOT_FOUND;
}
 
int nextPrime(int n)
{
	if (n <= 1) 
        return 2; 
  
	int prime = n; 
    bool found = false; 
	while (!found) 
	{ 
        prime++; 
		if (isPrime(prime)) 
           found = true; 
    } 
	return prime; 
}

bool isPrime(int n)
{
	for(int i=2;i<= sqrt(n);i++)
    {
		if ((n%i)!= 0)
            return true;
        else
            return false;
    }
}
int hashing(string x, int size)
{
    if(x.length()==1)
        return (unsigned char(x.at(0)));
    return 256;
}

#endif