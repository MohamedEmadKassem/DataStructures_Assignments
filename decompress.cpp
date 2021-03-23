#include "dictionary.h"
#include "HashTable.h"
#include <iostream>
#include <fstream>
#include <string>
using namespace std;

string decompressing(HashTable<Dictionary> & table, unsigned current, unsigned previous, unsigned & adding)
{
    string notfound, added;
    added=table.find(previous).key;                     
    if(table.find(current).key==notfound)
        added+=added.at(0);  
    else
        added+=table.find(current).key.at(0);
    table.insert(Dictionary(adding++,added));           
    return table.find(current).key;
}
 
void takeInput(HashTable<Dictionary> & table)
{
    ifstream input;
    string inName("compout");
    input.open(inName.c_str());
	ofstream output;
    string outName="decompout";
	output.open(outName.c_str());
    unsigned current, previous, adding=256;
    input>>previous;
	output << table.find(Dictionary(previous)).key; 
    while(!input.eof())
	{
		input>>current;
		output << decompressing(table, current, previous, adding);
        previous=current;
    }
	output.close();
    input.close();
}
 
 
int main()
{
	string x, compressed;
    int SIZE = 4096;
	HashTable<Dictionary> compress(SIZE);
    for(int i=0; i<256; i++){
        x=i;
        compress.insert(Dictionary(i,x));
    }
    takeInput(compress);
 
    return 0;
}