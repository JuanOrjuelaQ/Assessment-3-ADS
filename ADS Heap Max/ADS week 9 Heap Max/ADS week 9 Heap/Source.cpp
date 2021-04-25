#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include "BinaryMaxHeap.h"

using namespace std;

void WriteToFile(string filePath, string line)
{
	// Create and open a text file
	ofstream MyFile;
	MyFile.open(filePath, ios_base::app);
	MyFile << line << endl;

	// Close the file
	MyFile.close();
}
vector<int> StringToVector(string numbers)
{
	stringstream numbersStringStream(numbers);
	string number;
	vector<int> numbersVector;

	while (getline(numbersStringStream, number, ' '))
	{
		numbersVector.push_back(stoi(number));
	}

	return numbersVector;

}
vector<int> GetNumbersFromFile(string filePath)
{
	// Create a text string, which is used to output the text file
	string myText;

	// Read from the text file
	ifstream MyReadFile(filePath);

	getline(MyReadFile, myText);

	int numberOfItems = stoi(myText);

	getline(MyReadFile, myText);

	// Close the file
	MyReadFile.close();

	return StringToVector(myText);

}


void main() {

	vector<int> numbersIn = GetNumbersFromFile("numbersIn.txt");
	BinaryMaxHeap heap;
	string fileOutName = "heapOut.txt";

	for(size_t i = 0; i < numbersIn.size(); i++)
	{
		heap.Insert(numbersIn[i]);
		cout << heap.returnHeap() << endl;
		WriteToFile(fileOutName, heap.returnHeap());
	}

	system("pause");
}