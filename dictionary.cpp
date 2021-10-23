using namespace std;
#include <fstream>
#include <vector>
#include <cmath>
#include "hash24.cpp"

String hashTable[][];
Hash24 mainHash;

Dictionary(String fname, String paramFileName) {

	int tableSize;
	int words;
	unsigned long rand_a, rand_b, rand_c;

	
	//To read the file containing table size, a, b, and c values
	ifstream paramFile(paramFileName);
	string getA, getB, getC, getTableSize;
	getline(paramFile,getTableSize);
	tableSize = stoi(getTableSize);
	getline(paramFile,getA);
	rand_a = stoi(getA);
	getline(paramFile,getB);
	rand_b = stoi(getB);
	getline(paramFile,getC);
	rand_c = stoi(getC);
	
	paramFile.close();

	mainHash = new Hash24(rand_a, rand_b, rand_c);

	int sizeArray[tableSize] = {0};
	Hash24 hashArray[tableSize];
	Hash24 mainHash(rand_a, rand_b, rand_c);

	// Hash24 function to dump data
	mainHash.dump();

	ifstream wordBase(fname);
	vector<vector<string>> wordVector;
	int intArray[tableSize] = {0};
	int totalWords = 0;
	int uniqueWords = 0;
	int index = 0;
	string word = "";

	for(int i = 0; i < tableSize; i++){
		wordVector.push_back(vector<string>());
	}
	//This is to read in the wordbase file and hash the words into a intArray and wordVector
	while(wordBase)
	{
		getline(wordBase, word);
		if(word.empty())
			break;
		totalWords++;
		index = mainHash.hash(word);
		wordVector[index].push_back(word);
		intArray[index]++;
	}

	//Set the max of uniqueWords to totalWords
	uniqueWords = totalWords;

	wordBase.close();
	
	//To remove duplicates from wordVector
	for(int i = 0; i < wordVector.size(); i++)
	{
		for(int j = 0; j < wordVector[i].size()-1; j++)
		{
			word = wordVector[i][j]
			if(!wordVector[i][j].empty())
			{
				for(int k = j + 1; k < wordVector[i].size(); k++)
				{
					if(wordVector[i][j] == wordVector[i][k])
					{
						wordVector[i].erase(k);
						intArray[i]--;
						j--;
						k--;
						uniqueWords--;
					}
				}
			}
		}
	}

	//Initializes the string arrays within the hashtable to the right size and if it is zero it is null
	for(int i = 0; i < tableSize; i++) {

		if(intArray[i] > 0) {
			
			hashTable[i] = new string[intArray[i] * intArray[i]];

		}
		hashArray = new Hash24(rand_a, rand_b, rand_c);

	}

	bool completedSecondHash = false;
	int secondHashTries[] = {0};

	//Inputs all the strings from wordVector into the hashtable
	for(int i = 0; i < wordVector.size(); i++) {
		
		while(!completedSecondHash)
		{
			secondHashTries[i]++;
			for(int j = 0; j < intArray[i]; j++)
			{
				//if there is a collision within the secondary table
				if(hashTable[i][hashArray[i].hash(wordVector[i][j])] != null)
				{
					//randomize the secondary hash's a,b,c values
					hashArray[i].();
					
					//clears out the secondary table of values
					for(int g = 0; g < intArray[i] * intArray[i]; g++)
					{
						hashTable[i][g] = null;
					}
					
					//Repeat while loop
					goto tryAgain;
				}
				else{
					hashTable[i][hashArray[i].hash(wordVector[i][j])] = wordVector[i][j];
				}
			}
			//complete for loop without colliding
			completedSecondHash = true;

			label tryAgain:

		}
		completedSecondHash = false;

	}

	// Basic information about hash table
	cout << "Number of words = " << words << endl;
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
	cout << "Max collisions" << maxCol << endl;
	
	// For loop for # of primary slots with number of words
	int numArray[21] = {0};
	for(int i = 0; i < tableSize; i++) {
		if(intArray[i] < 21) {
			numArray[intArray[i]]++;
		}
	}
	for(int i = 0; i < 21; i++) {
		cout << "# of primary slots with " << i << "words = " << numArray[i] << endl;
	}
	
	cout << "** Words in the slot with most collisions ***" << endl;
	// For loop to print all words in the slot with most collisions
	for(int i = 0; i < maxCol; i++) {
		cout << hashTable[maxColIndex][i] << endl;	
	}
	
	// For loop for # of secondary hash tables trying hash functions
	cout << "Average # of hash functions tried = " << avgTries << endl;
	
	cout << "Queries:" << endl;
	// Query print depending on find function
	
}

bool find(String word) {

	return false;

}
