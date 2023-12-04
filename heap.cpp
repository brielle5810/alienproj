#include <algorithm>
#include "heap.h"



void maxheap::heapifyDown(int ind){
    int size = heap.size();
    while (ind < size){
        int l = getLeft(ind);
        int r = getRight(ind);
        int largest = ind;

        if (l < size && heap[largest].date < heap[l].date) {
            largest = l;
        }
        if (r < size && heap[largest].date < heap[r].date) {
            largest = r;
        }
        if (largest != ind) {
            swap(heap[ind], heap[largest]);
            ind = largest;
        } else {
            break;
        }

    }
}
void maxheap::maxHeapify(vector<UFOSighting> sightings){
    heap = sightings;
    for (int i = (sightings.size()/2) - 1; i >= 0; i--){
        heapifyDown(i);
    }
}


UFOSighting maxheap::closestSighting(string city, string state){
    UFOSighting closestSightingCity = UFOSighting();
    closestSightingCity.city = "N/A";
    closestSightingCity.state = state;
    closestSightingCity.country ="N/A";
    closestSightingCity.date.year = INT_MIN;
    closestSightingCity.date.month = INT_MIN;
    closestSightingCity.date.day = INT_MIN;
    closestSightingCity.date.hour = INT_MIN;
    closestSightingCity.date.minute = INT_MIN;

    UFOSighting closestSightingState = UFOSighting();
    closestSightingState.city = city;
    closestSightingState.state = "N/A";
    closestSightingState.country ="N/A";
    closestSightingState.date.year = INT_MIN;
    closestSightingState.date.month = INT_MIN;
    closestSightingState.date.day = INT_MIN;
    closestSightingState.date.hour = INT_MIN;
    closestSightingState.date.minute = INT_MIN;
    while (!heap.empty()) {
        swap(heap[0], heap.back());
        UFOSighting tempSighting = heap.back();
        cout << tempSighting.city<<endl;
        heap.pop_back();
        if (tempSighting.city == city && tempSighting.state == state) {
            if (closestSightingCity.date < tempSighting.date) {
                closestSightingCity = tempSighting;
            }
        }
        if (tempSighting.state == state && closestSightingState.date < tempSighting.date) {
            closestSightingState = tempSighting;
        }
        heapifyDown(0);
    }
    if (closestSightingCity.city == city && closestSightingCity.state== state) {
        return closestSightingCity;
    } else {
        return closestSightingState;
    }
}
vector<UFOSighting> maxheap::stateList(string state){
    vector<UFOSighting> stateList;
    while (!heap.empty()) {
        swap(heap[0], heap.back());
        UFOSighting tempSighting = heap.back();
        heap.pop_back();

        if (tempSighting.state==state) {
            stateList.push_back(tempSighting);
        }
        heapifyDown(0);
    }
    return stateList;
}