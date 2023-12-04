#pragma once
#include <iostream>
#include <vector>
#include "ufo.h"
using namespace std;

// Project 3b for COP3530 Ana Garcia Andrea Mueller and Brielle Stokes
// data analysis

class Hash{

private:
    float loadF = .75;
    int numItems = 0;
    int capacity = 100;
    struct hashNode{
        UFOSighting sighting;
        int key;
        string value;

        hashNode(){
            key = 0;
            value = "";
            sighting = UFOSighting();

        }

        hashNode(UFOSighting sighting) : sighting(sighting), key(sighting.year+sighting.month+sighting.day+sighting.hour+sighting.minute),value(sighting.city+", "+sighting.state){}

    };
    vector<vector<hashNode*>> hashTable;

    // need to create your own hash map you cant use unordered map
    // location of the sighting and date
public:
    Hash(): hashTable(capacity){}
    ~Hash() {
        for (auto& bucket : hashTable) {
            for (hashNode* node : bucket) {
                delete node;
            }
        }
    }

    long hash(int s){
        return s%capacity;
    }
    void resize(vector<vector<hashNode*>>& hashTable) {
        capacity = capacity * 2;
        vector<vector<hashNode*>> newTable(capacity);

        for (auto& row : hashTable) {
            for (auto& node : row) {
                int index = hash(node->key);
                newTable[index].push_back(node);
            }
        }
        for (auto& row : hashTable) {
            row.clear();
        }
        hashTable = newTable;
    }

    void insert(UFOSighting sighting){
        // create new node to be put in the array "table"
        hashNode *node = new hashNode(sighting);
        //hash function makes index
        int index = hash(node->key);
        // separate chaining: linked list implementation will be better for large data sets
        hashTable[index].push_back(node);
        numItems++;
        if(float(numItems/capacity)>loadF){
            //increase table size
            resize(hashTable);
        }

    }

    bool findUFO(int date) {
        int index = hash(date);
        for (auto &i : hashTable[index]) {
            if (i->key == date) {
                return true;
            }
        }
        return false;
    }
    UFOSighting closestSighting(string city, string state){
        UFOSighting closest;
        UFOSighting closestInState;

        for(auto &i :hashTable){
            for(auto &node :i ){
                if(node->sighting.city == city && node->sighting.state == state){
                    if(closest.city!="NULL" && closest.date < node->sighting.date) {
                        closest = node->sighting;
                    }
                        closest = node->sighting;
                }
                else if(node->sighting.state == state){
                    if(closestInState.state!="NULL" && closestInState.date< node->sighting.date){
                        closestInState = node->sighting;
                    }
                    closestInState = node->sighting;
                }
            }
        }
        if(closest.city!="NULL"){
            return closest;
        }
        else{
            return closestInState;
        }

    }
   UFOSighting mostRecent(){
        vector<UFOSighting> recents;
        hashNode *mostRecent;
        for(auto &vector : hashTable){
            for(auto& node : vector){
                if(node->sighting.date > mostRecent->sighting.date){
                    mostRecent = node;
                }
            }
        }
        return mostRecent->sighting;
    }

    vector<UFOSighting> ListofSightings(string &state){
        vector<UFOSighting> sightings;
        for(auto& i : hashTable){
            for(auto &node :i){
                if(node->sighting.state == state){
                    sightings.push_back(node->sighting);
                }
            }
        }
        sort(sightings.begin(), sightings.end());
        return sightings;
    }
    void print(){
        for(auto&index :hashTable) {
            for (auto &it: index) {
                cout << "Sighting location: " << it->key << "\nSighting date: " << it->value << endl;
            }
        }
    }

};
