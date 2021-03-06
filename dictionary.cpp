#ifndef DICT_CPP
#define DICT_CPP

#include <algorithm>
#include "dictionary.h"

using namespace std;

Dictionary::Dictionary(string fname, string paramFileName) {

		// General variables for main hash table
		int words;
		unsigned long rand_a, rand_b, rand_c;

		// Read the parameter file in order to create main hash function
		ifstream paramFile(paramFileName);
		string getA, getB, getC, getTableSize;

		getline(paramFile,getTableSize);
		tableSize = stoul(getTableSize);

		getline(paramFile,getA);
		rand_a = stoul(getA);

		getline(paramFile,getB);
		rand_b = stoul(getB);

		getline(paramFile,getC);
		rand_c = stoul(getC);

		paramFile.close();

		// Initialize the main hash function using data from file 
		mainHash = new Hash24(rand_a, rand_b, rand_c);

		// Initialize necessary arrays for the main hash table

		// Main hash table
		hashTable = new string * [tableSize];
		vector<int> hashAttemptArray(tableSize, 0);

		int sizeArray[tableSize] = {0}; 	// Store number of collisions in main hash here
		hashArray = new Hash24 * [tableSize];	// Store Hash24 objects here

		// Hash24 function to dump data of main hash object
		mainHash->dump();

		// Variables for loading words from file and necessary data
		ifstream wordBase(fname);
		vector<vector<string>> wordVector;
		intArray = new int[tableSize];
		int totalWords = 0;
		int uniqueWords = 0;
		int index = 0;
		string word = "";

		// Create a 2D vector for storing words
		for(int i = 0; i < tableSize; i++) {

			wordVector.push_back(vector<string>());

		}

		// This is to read in the wordbase file and hash the words into a intArray and wordVector
		while(getline(wordBase,word)) {

			//getline(wordBase, word);
			//if(word.empty()) break;
			totalWords++;
			index = (mainHash->hash(word) % tableSize);
			wordVector[index].push_back(word);
			intArray[index]++;

		}

		// Set the max of uniqueWords to totalWords
		uniqueWords = totalWords;

		wordBase.close();

		// To remove duplicates from wordVector
		for(int i = 0; i < wordVector.size(); i++) {
			
			for(int j = 0; j < wordVector[i].size(); j++) {

				word = wordVector[i][j];

				if(!wordVector[i][j].empty()) {

					for(int k = j + 1; k < wordVector[i].size(); k++) {

						if(wordVector[i][j] == wordVector[i][k]) {

							wordVector[i].erase(wordVector[i].begin() + k);
							intArray[i]--;
							j--;
							k--;
							uniqueWords--;

						}

					}

				}

			}

		}
		
		// Initializes the string arrays within the hashtable to the right size and if it is zero it is null
		for(int i = 0; i < tableSize; i++) {

			if(intArray[i] > 0) {
				//Hash24 replaceHash;
				hashTable[i] = new string[intArray[i] * intArray[i]];
				//cout << "Int Array Squared: " << intArray[i] * intArray[i] << endl;
				//cout << "Hash Bucket Size: " << hashTable[i]->size() << endl;
				//hashArray[i] = replaceHash;
				hashArray[i] = new Hash24(rand_a, rand_b, rand_c);
				//hashArray[i] = new Hash24(rand_a,rand_b,rand_c); shouldn't it be this?
				hashAttemptArray[i]++;

			}

		}

		bool completedSecondHash = false;
		
		// Inputs all the strings from wordVector into the hashtable
		for(int i = 0; i < wordVector.size(); i++) {

			while(!completedSecondHash) {

				tryAgain:
				for(int j = 0; j < intArray[i]; j++) {
					int tempIndex = hashArray[i]->hash(wordVector[i][j]) % (intArray[i] * intArray[i]);

					// If there is a collision within the secondary table
					if(hashTable[i][tempIndex] != "") {

						// Randomize the secondary hash's a,b,c values
						hashArray[i] = new Hash24();
						hashAttemptArray[i]++;

						//clears out the secondary table of values
						for(int g = 0; g < intArray[i] * intArray[i]; g++) {

							hashTable[i][g] = "";

						}

						//Repeat while loop
						goto tryAgain;

					} else {
						hashTable[i][tempIndex] = wordVector[i][j];

					}

				}

				// Complete for loop without colliding
				completedSecondHash = true;

			}

			completedSecondHash = false;

		}

		// Basic information about hash table
		cout << "Number of words = " << uniqueWords << endl;
		cout << "Table size = " << tableSize << endl;

		// Function to find max collisions and index of bucket
		int maxCol = intArray[0];
		int maxColIndex = 0;

		for(int i = 1; i < tableSize; i++) {

			if(intArray[i] > maxCol) {

				maxCol = intArray[i];
				maxColIndex = i;

			}

		}


		if(maxCol == 1) maxCol = 0;
		cout << "Max collisions = " << maxCol << endl;

		// For loop for # of primary slots with number of words
		int numArray[21] = {0};

		for(int i = 0; i < tableSize; i++) {

			if(intArray[i] < 21) {
				
				numArray[intArray[i]]++;

			}

		}

		for(int i = 0; i < 21; i++) {

			cout << "# of primary slots with " << i << " words = " << numArray[i] << endl;

		}

		cout << "** Words in the slot with most collisions ***" << endl;

		vector<string> maxColList;

		// For loop to print all words in the slot with most collisions
		for(int i = 0; i < (intArray[maxColIndex] * intArray[maxColIndex]); i++) {

			if(hashTable[maxColIndex][i] != "" && maxCol > 0)
			maxColList.push_back(hashTable[maxColIndex][i]);	

		}

		sort(maxColList.begin(), maxColList.end());

		for(int i = 0; i < maxColList.size(); i++) cout << maxColList[i] << endl;

		// For loop for # of secondary hash tables trying hash functions
		cout << "Number of hash functions tried:" << endl;

		vector<int> numSecondAttempt(20,0);

		// Counts number of secondary attempts
		for(int i = 0; i < hashAttemptArray.size(); i++) {

			if(hashAttemptArray[i] > 0 && hashAttemptArray[i] < 21) {

				numSecondAttempt[hashAttemptArray[i] - 1]++;

			}

		}

		for(int i = 0; i < numSecondAttempt.size(); i++) {

			cout << "# of secondary hash tables trying " << (i + 1) << " hash functions = " << numSecondAttempt[i] << endl;

		}

		// Calculate the average # of hash functions tried
		int sum = 0;
		int avgTries = 0;
		for(int i = 0 ; i < hashAttemptArray.size(); i++) {

			sum += hashAttemptArray[i];

		}

		avgTries = sum / hashAttemptArray.size();

		cout << "Average # of hash functions tried = " << avgTries << endl;

	}

	bool Dictionary::find(string word) {
		
		int hashValue = mainHash->hash(word) % tableSize;
		
		if(hashTable[hashValue] != nullptr) {
			
			//int hash2Value = hashArray[hashValue]->hash(word) % hashTable[hashValue]->size() - 1;
			int hash2Value = hashArray[hashValue]->hash(word) % (intArray[hashValue] * intArray[hashValue]);
			if(hash2Value < 0) hash2Value = 0;


			if(hashTable[hashValue][hash2Value] == word) {

				cout << word << " found at " << hashValue << endl;
				return true;

			}
		}

		//Print not found if not found
		cout << word << " not found" << endl;

		return false;

	}

//};	

#endif
