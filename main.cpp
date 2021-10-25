//#include <iostream>
//#include <fstream>
//#include <string>
//#include <vector>
//#include <cmath>
#include "dictionary.h"

using namespace std;

int main(int argc, char *argv[]) {
		string parameterFile = argv[1];
		string dataBaseFile = argv[2];
		Dictionary * dictionaryObject = new Dictionary(dataBaseFile, parameterFile);

		string query = "";

		ifstream queryFile(argv[3]);
		cout << "Queries:" << endl;
		while(queryFile)
		{
			getline(queryFile, query);
			if(query.empty())
				break;
			dictionaryObject->find(query);
		}

		

}
