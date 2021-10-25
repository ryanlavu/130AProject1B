//#include <iostream>
//#include <fstream>
//#include <string>
//#include <vector>
//#include <cmath>
#include "dictionary.cpp"

using namespace std;

int main(int argc, char *argv[]) {
		string parameterFile = argv[1];
		string dataBaseFile = argv[2];
		Dictionary * dictionaryObject = new Dictionary(parameterFile, dataBaseFile);

		string query = "";

		ifstream queryFile(argv[3]);
		while(queryFile)
		{
			getline(queryFile, query);
			if(query.empty())
				break;
			cout << "Queries:" << endl;
			dictionaryObject->find(query);
		}

		

}
