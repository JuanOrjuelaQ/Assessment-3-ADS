#pragma once
#include <iostream>
#include <cstdlib>
#include <vector>
#include <iterator>

using namespace std;

class BinaryMaxHeap
{
public:
	vector<int> heap;
	int parentIndex(int child);

	void heapifyup(int index);

	void Insert(int element);
	void showHeap();
	string returnHeap();

	int Size();

};

