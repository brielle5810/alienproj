#include <iostream>
using namespace std;
#include "unordered_map"
// Project 3b for COP3530 Ana Garcia Andrea Mueller and Brielle Stokes
// data analysis
#define CAPACITY 100

class Hash{

private:
    float loadF = .75;
    int numItems = 0;
    struct hashNode{

        string key;
        int value;
        hashNode *next;
        int index;

        hashNode(string & k, int v){
            key = k;
            value = v;
            next = nullptr;
            index = 0;
        }

    };

    hashNode *table[CAPACITY];
    // need to create your own hash map you cant use unordered map
    // location of the sighting and year
public:
    int hashfunct(string s){
        //node->key = s
        // requirements of a good hash function: key%tablesize, easy to compute,
        // deterministic, should be able to evenly distribute data
        int index = 0;
        int key = 0;
        for(char i :s){
            int k = static_cast<int>(i);
            key+=k;
        }
        index = key%CAPACITY;
        return index;
    }
    void resize(){
        // how to double an array?
        CAPACITY*=2;
    }
    void insert(string name, int year){
        // create new node to be put in the array "table"
        hashNode *node = new hashNode(name,year);
        //hash function makes index
        int index = hashfunct(node->key);
        // if the string is unique put it in the table, else move spots ex: of linear probing
        /*
        while (table[index] != nullptr) {
            index = (index + 1) % CAPACITY;
        }*/
        // separate chaining: linked list implementation will be better for large data sets
        node->index = index;
        table[index] = node;
        numItems++;
        if(float(numItems/CAPACITY)>loadF){
            //increase table size
            resize();
        }

        // if location is unique, put it in the table, if not then put it in the next available space?
        // using linear probing or quadratic?
        // what is the bucket size and how to increase it

    }
    void deleteUFO(){}
    string getUFO(){
        string ufo = "";
        return ufo;
    }
    int getDistance(string location){
        int distance;
        return distance;
    }
    int getYear(unordered_map<string,int> ufo, string sighting){
        int ufoYear;
        //ufoYear = ufo.find(sighting);
        return ufoYear;
    }
    void print(unordered_map<string,int> map){
        for(auto &it : map){
            cout<<"Sighting location: "<<it.first<<"\nSighting date: "<<it.second<<endl;
        }
    }

};
