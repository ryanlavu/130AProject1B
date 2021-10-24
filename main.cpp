#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <cmath>
#include "hash24.cpp"
#include "dictionary.cpp"

using namespace std;

int main(int argc, char *argv[]) {
		string parameterFile = argv[1];
		string dataBaseFile = argv[2];
		Dictionary dictionaryObject = new Dictionary(parameterFile, dataBaseFile);

		string query = "";

		ifstream queryFile(argv[3]);
		while(queryFile)
		{
			getLine(queryFile, query);
			if(query.empty())
				break;
			cout << "Queries:" << endl;
			dictionaryObject.find(query);
		}

		

}
