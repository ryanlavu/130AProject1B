#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <cmath>

using namespace std;

int main(int argc, char *argv[]) {

	//To read the file containing p and c values
	string getA, getB, getC, getTableSize;
	ifstream firstFileObj(argv[1]);
	getline(firstFileObj,getA);
	int a = stoi(getA);
	getline(firstFileObj,getB);
	int b = stoi(getB);
	getline(firstFileObj,getC);
	int c = stoi(getC);
	getline(firstFileObj,getTableSize);
	int tableSize = stoi(getTableSize);


	firstFileObj.close();



}