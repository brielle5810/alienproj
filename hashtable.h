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
        int index = 0;
        hashNode(){
            key = "";
            value = 0;
            index = 0;
        }
        hashNode(string & k, int v){
            key = k;
            value = v;
            index = 0;
        }
        ~hashNode();

    };
    vector<vector<hashNode>> hashTable;
    // need to create your own hash map you cant use unordered map
    // location of the sighting and year
public:
    Hash(): hashTable(capacity){}
    int hash(string s){
        return s.length()%capacity;
    }
    void resize(vector<vector<hashNode>> &vector){
         ::vector<::vector<hashNode>> table;
         for( auto &i : vector){
             for(auto &node :i){
                 int index = hash(node.key);
                 table[index].push_back(node);
             }
         }
        capacity*=2;
        vector = table;
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
    void deleteUFO(){}
    bool findUFO(string name) {
        int index = hash(name);
        for (auto &i : hashTable[index]) {
            if (i.key == name) {
                return true;
            }
        }
        return false;
    }
    int getDistance(string location){
        int distance;
        return distance;
    }
    int getYear(string sighting){
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
