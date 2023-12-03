#include <iostream>
#include "vector"
using namespace std;

// Project 3b for COP3530 Ana Garcia Andrea Mueller and Brielle Stokes
// data analysis

class Hash{

private:
    float loadF = .75;
    int numItems = 0;
    int capacity = 100;
    struct hashNode{

        string key = "";
        int value = 0;
        hashNode(){
            key = "";
            value = 0;
            
        }
        hashNode(string & k, int v){
            key = k;
            value = v;
            
        }
        ~hashNode();

    };
    vector<vector<hashNode>> hashTable;
    // location of the sighting and year

public:
    Hash(): hashTable(capacity){}
    int hash(string s){
        return s.length()%capacity;
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
    void insert(string name, int year){
        // create new node to be put in the array "table"
        hashNode *node = new hashNode(name,year);
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
    bool findUFO(string name) {
        int index = hash(name);
        for (auto &i : hashTable[index]) {
            if (i.key == name) {
                return true;
            }
        }
        return false;
    }
    int getDistance(string location){// NOT IMPLEMENTED
        int distance;
        
        return distance;
    }
    int getYear(string sighting){ // EDIT to make the time more specific ( minutes hours days months etc)
        int ufoYear;
        int index = hash(sighting);
        for (auto &i : hashTable[index]) {
            if (i.key == sighting) {
               ufoYear = i.value;
            }
        }
        return ufoYear;
    }
    void print(){
        for(auto &index : hashTable){
            for(auto &it : index){
            cout<<"Sighting location: "<<it.key<<"\nSighting date: "<<it.value<<endl;
        }
        }
    }

};
