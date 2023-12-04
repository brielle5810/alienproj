//
// Created by B on 12/1/2023.
//
#include <algorithm>
#include "heap.h"


void maxheap::heapifyUp(int ind){
    while (ind > 0) {
        int p = getParent(ind);
        if (heap[p].date < heap[ind].date){
            swap(heap[p], heap[ind]);
            ind = p;
        }
        else {
            break;
        }
    }
}
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


    for (UFOSighting& sighting : heap) {
        // Check if the sighting is in the target city or state
        if (sighting.city == city && sighting.state==state) {
            if (closestSightingCity.date < sighting.date) {
                closestSightingCity = sighting;
            }
        }
        if (sighting.state == state && closestSightingState.date < sighting.date) {
            closestSightingState = sighting;
        }
    }
    // If there is a sighting in the target city, return it; otherwise, return the most recent in the state
    if (closestSightingCity.city == city && closestSightingCity.state== state) {
        return closestSightingCity;
    } else {
        return closestSightingState;
    }

}
vector<UFOSighting> maxheap::stateList(string state){
    vector<UFOSighting> stateList;
    for (UFOSighting& sighting : heap) {
        if (sighting.state == state) {
            stateList.push_back(sighting);
        }
    }
    sort(stateList.begin(), stateList.end());
    return stateList;
}