//
// Created by B on 12/1/2023.
//
#ifndef SIGHITNG_HEAP_H
#define SIGHITNG_HEAP_H
#include <vector>
#include "ufo.h"
using namespace std;

class maxheap {
private:
    vector<UFOSighting> heap;
    int getParent(int ind) { return (ind - 1) / 2; }
    int getLeft(int ind) { return (2 * ind + 1); }
    int getRight(int ind) { return (2 * ind + 2); }

public:
    UFOSighting getMax() { return heap[0]; }
    void heapifyUp(int ind);
    void heapifyDown(int ind);
    void maxHeapify(vector<UFOSighting> sightings);
    UFOSighting closestSighting(string city, string state);
    vector<UFOSighting> stateList(string state);

};


#endif //SIGHITNG_HEAP_H
