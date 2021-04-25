#include "BinaryMaxHeap.h"
#include "string"

int BinaryMaxHeap::parentIndex(int child)
{/*
    int parent = (child - 1) / 2;
    if (child == 0)
        return -1;
    else
        return parent;
        */
    if (child == 0)
        return -1;
    return child - 1;
}
//after inserting, we heapifyup from where that new inserted player ended up
//compares current node to parent and swaps the smaller to the top
//recursive function, each swap means we call heapifyup on the next higher level
//where we swapped a value
void BinaryMaxHeap::heapifyup(int index)
{
    //IF index is not the root(top of the tree)
    //AND parent index within heap bounds (not negative)
    //AND current nodes rank less then parent nodes rank
    if (index >= 0 && parentIndex(index) >= 0 && heap[index] > heap[parentIndex(index)]) {
        //if so, swap values between current node and parent
        int temp = heap[index];
        heap[index] = heap[parentIndex(index)];
        heap[parentIndex(index)] = temp;
        //since we swapped, lets run heapifyup again recursively on the parent from here
        heapifyup(parentIndex(index));
    }
}
//inserts at the lowest next free spot in the tree (this keeps things balanced :D)
void BinaryMaxHeap::Insert(int element) {
    heap.push_back(element);
    heapifyup(heap.size() - 1);
}

void BinaryMaxHeap::showHeap() {
    cout << "Heap -->";
    for (int p : heap)
    {
        cout <<"["<< p << "] ";
    }
    cout << endl;
}

string BinaryMaxHeap::returnHeap() {

    string s;
    for (int p : heap)
    {
         s +=  " [" + to_string(p) + "] ";
    }
    return s;
}

int BinaryMaxHeap::Size() {
    return heap.size();
}
