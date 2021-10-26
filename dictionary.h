#ifndef DICTIONARY_H
#define DICTIONARY_H

#include <fstream>
#include <vector>
#include <cmath>
#include <iostream>
#include "hash24.h"

using namespace std;

class Dictionary {

	public:
		string ** hashTable;
		Hash24 * mainHash;
		Hash24 ** hashArray;
		int tableSize;
		int * intArray;

		Dictionary(string fname, string paramFileName);
		bool find(string word);

};

#endif
