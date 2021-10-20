using namespace std;

Dictionary(String fname, String paramFileName) {

	int tableSize;
	int words;
	unsigned long rand_a, rand_b, rand_c;
	Hash24 mainHash = new Hash24(rand_a, rand_b, rand_c);

	int sizeArray[tableSize] = {0};

	
	// Hash24 function to dump data
	mainHash.dump();

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
	
	// For loop for # of secondary hash tables trying hash functions
	cout << "Average # of hash functions tried = " << avgTries << endl;
	
	cout << "Queries:" << endl;
	// Query print depending on find function
	
}

bool find(String word) {
	return false;
}
