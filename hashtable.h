
#include <iostream>
#include "vector"
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
    vector<vector<hashNode>> hashTable;
    // need to create your own hash map you cant use unordered map
    // location of the sighting and date
public:
    Hash(): hashTable(capacity){}
    long hash(int s){
        return s%capacity;
    }
    void resize(vector<vector<hashNode>>& hashTable) {
        capacity = capacity * 2;
        vector<vector<hashNode>> newTable(capacity);

        for (auto& row : hashTable) {
            for (auto& node : row) {
                int index = hash(node.key);
                newTable[index].push_back(node);
            }
        }
        hashTable = newTable;
    }

    void insert(UFOSighting sighting){
        // create new node to be put in the array "table"
        hashNode *node = new hashNode(sighting);
        //hash function makes index
        int index = hash(node->key);
        // separate chaining: linked list implementation will be better for large data sets
        hashTable[index].push_back(*node);
        numItems++;
        if(float(numItems/capacity)>loadF){
            //increase table size
            resize(hashTable);
        }
    }

    bool findUFO(int date) {
        int index = hash(date);
        for (auto &i : hashTable[index]) {
            if (i.key == date) {
                return true;
            }
        }
        return false;
    }
    UFOSighting closestSighting(string city, string state){
        UFOSighting closest;
        for(auto &i :hashTable){
            for(auto &node :i ){
                if(node.sighting.city == city && node.sighting.state == state){
                    return node.sighting;
                }
                else if(node.sighting.state == state){
                    closest = node.sighting;
                }
            }
        }

        return closest;
    }
    vector<UFOSighting> mostRecentSighting(){
        vector<UFOSighting> recents;
        vector<hashNode> mostRecent = hashTable.back();
        for( auto &i : mostRecent){
            // if there is a tie then what
            recents.push_back(i.sighting);
        }
        return recents;
    }

    vector<UFOSighting> ListofSightings(string &state){
        vector<UFOSighting> sightings;
        for(auto& i : hashTable){
            for(auto &node :i){
                if(node.sighting.state == state){
                    sightings.push_back(node.sighting);
                }
            }
        }
        return sightings;
    }
    void print(){
        for(auto&index :hashTable) {
            for (auto &it: index) {
                cout << "Sighting location: " << it.key << "\nSighting date: " << it.value << endl;
            }
        }
    }
};
