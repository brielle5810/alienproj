#include "ufo.h"
#include <iostream>
#include <string>
#include <limits>
#include <fstream>
#include <vector>
#include <algorithm>
#include "heap.h"
#include <unordered_map>
#include <unordered_set>
#include "RedBlackTree.h"
using namespace std;
#include "hashtable.h"


int main() {
    string city, state;
    int choice;
    unordered_map<string, string> stateMap = {
            {"Alabama", "AL"}, {"alabama", "AL"}, {"Alaska", "AK"}, {"alaska", "AK"},
            {"Arizona", "AZ"}, {"arizona", "AZ"}, {"Arkansas", "AR"}, {"arkansas", "AR"},
            {"California", "CA"}, {"california", "CA"}, {"Colorado", "CO"}, {"colorado", "CO"},
            {"Connecticut", "CT"}, {"connecticut", "CT"}, {"Delaware", "DE"}, {"delaware", "DE"},
            {"Florida", "FL"}, {"florida", "FL"}, {"Georgia", "GA"}, {"georgia", "GA"},
            {"Hawaii", "HI"}, {"hawaii", "HI"}, {"Idaho", "ID"}, {"idaho", "ID"},
            {"Illinois", "IL"}, {"illinois", "IL"}, {"Indiana", "IN"}, {"indiana", "IN"},
            {"Iowa", "IA"}, {"iowa", "IA"}, {"Kansas", "KS"}, {"kansas", "KS"},
            {"Kentucky", "KY"}, {"kentucky", "KY"}, {"Louisiana", "LA"}, {"louisiana", "LA"},
            {"Maine", "ME"}, {"maine", "ME"}, {"Maryland", "MD"}, {"maryland", "MD"},
            {"Massachusetts", "MA"}, {"massachusetts", "MA"}, {"Michigan", "MI"}, {"michigan", "MI"},
            {"Minnesota", "MN"}, {"minnesota", "MN"}, {"Mississippi", "MS"}, {"mississippi", "MS"},
            {"Missouri", "MO"}, {"missouri", "MO"}, {"Montana", "MT"}, {"montana", "MT"},
            {"Nebraska", "NE"}, {"nebraska", "NE"}, {"Nevada", "NV"}, {"nevada", "NV"},
            {"New Hampshire", "NH"}, {"new hampshire", "NH"}, {"New Jersey", "NJ"}, {"new jersey", "NJ"},
            {"New Mexico", "NM"}, {"new mexico", "NM"}, {"New York", "NY"}, {"new york", "NY"},
            {"North Carolina", "NC"}, {"north carolina", "NC"}, {"North Dakota", "ND"}, {"north dakota", "ND"},
            {"Ohio", "OH"}, {"ohio", "OH"}, {"Oklahoma", "OK"}, {"oklahoma", "OK"},
            {"Oregon", "OR"}, {"oregon", "OR"}, {"Pennsylvania", "PA"}, {"pennsylvania", "PA"},
            {"Rhode Island", "RI"}, {"rhode island", "RI"}, {"South Carolina", "SC"}, {"south carolina", "SC"},
            {"South Dakota", "SD"}, {"south dakota", "SD"}, {"Tennessee", "TN"}, {"tennessee", "TN"},
            {"Texas", "TX"}, {"texas", "TX"}, {"Utah", "UT"}, {"utah", "UT"},
            {"Vermont", "VT"}, {"vermont", "VT"}, {"Virginia", "VA"}, {"virginia", "VA"},
            {"Washington", "WA"}, {"washington", "WA"}, {"West Virginia", "WV"}, {"west virginia", "WV"},
            {"Wisconsin", "WI"}, {"wisconsin", "WI"}, {"Wyoming", "WY"}, {"wyoming", "WY"}
    };
    unordered_set<string> stateAbbrev={
            "AL", "AK", "AZ", "AR", "CA", "CO", "CT", "DE", "FL", "GA",
            "HI", "ID", "IL", "IN", "IA", "KS", "KY", "LA", "ME", "MD",
            "MA", "MI", "MN", "MS", "MO", "MT", "NE", "NV", "NH", "NJ",
            "NM", "NY", "NC", "ND", "OH", "OK", "OR", "PA", "RI", "SC",
            "SD", "TN", "TX", "UT", "VT", "VA", "WA", "WV", "WI", "WY"
    };
    vector<UFOSighting> sightings= parseJSON("ufo_sightings.json");
    string temp2="";

    maxheap UFOHeap;
    UFOHeap.maxHeapify(sightings);

    RedBlackTree UFOTree;
    for (const auto& sighting : sightings) {
        UFOTree.insert(sighting);
    }
    
    Hash UFOTable;
    for (const auto& sighting : sightings) {
        UFOTable.insert(sighting);
    }

    //printMenuBorder();
    while (true) {
        choice = 0;
        cout << "  +--------------------------------------------------------+\n";
        cout << "  |                      Alien Atlas                       |\n";
        cout << "  +--------------------------------------------------------+\n";
        cout << "  |   Menu:                                                |\n";
        cout << "  |   1. Find closest UFO sighting                         |\n";
        cout << "  |   2. Find most recent UFO sighting                     |\n";
        cout << "  |   3. Find list of sightings in a state                 |\n";
        cout << "  |   4. Quit                                              |\n";
        cout << "  +--------------------------------------------------------+\n";
        cout << "  Enter your choice (1-4): ";

        if (!(cin >> choice) || choice > 4 || choice < 1){
            // clear cin and ignore choice
            cin.clear();
            cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            cout << "  Invalid input. Please enter a number between 1 and 4.\n";
            continue; //start over
        }
        string tempCity;
        switch (choice) {
            case 1:
                //to implement next: CHECK FOR NEWLINE CHARS FOR CITY/STATE
                cout << "  Enter city: ";
                cin.clear();
                cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                std::getline(std::cin, city);
                for (char& i : city) {//accept Chicago as chicago (how json is stored)
                    i = (char) tolower(i);
                }
                //CHECK VALID STATE
                cout << "  Enter a state or state abbreviation: ";
                getline(std::cin, state);
                while (true) {
                    if ((stateMap.find(state) != stateMap.end() || stateAbbrev.find(state) != stateAbbrev.end()) &&
                        state.length() > 0) {
                        if (stateMap.find(state) != stateMap.end()) {
                            state = stateMap[state];
                        }
                        break;
                    } else {
                        cout << "  Invalid state. Please enter a valid state or state abbreviation.\n";
                        cin.clear();
                        cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                    }
                    getline(std::cin, state);
                }

                //case 1 functionality
                cout << "  The closest UFO sighting was on:                   \n";
                //HEAP
                cout << "  Using a MaxHeap:                                   \n";

                if (UFOHeap.getsize()<1){
                    cout << "  IMPROPER HEAP!";
                    //UFOSighting heapObj = UFOHeap.closestSighting(city, state);
                }
                else {
                    UFOSighting heapObj = UFOHeap.closestSighting(city, state);
                    tempCity = (char) toupper(heapObj.city[0]) + heapObj.city.substr(1);
                    for (int i = 1; i < tempCity.size(); i++) {
                        if (isspace(tempCity[i - 1])) {
                            tempCity[i] = toupper(tempCity[i]);
                        }
                    }
                    cout << "  " << heapObj.date.month << "/"
                         << heapObj.date.day << "/"
                         << heapObj.date.year << " at "
                         << heapObj.date.hour << ":"
                         << heapObj.date.minute << " in "
                         << tempCity << ", " << heapObj.state
                         << ", " << heapObj.country << "              \n";
                    UFOHeap.maxHeapify(sightings);
                }
                //TREE
                cout << "  Using a RedBlackTree:                              \n";
                UFOTree.closestSighting(city,state);
                if(UFOTree.closestSighting(city,state).date.year == 0){
                    break;
                }
                tempCity = (char) toupper(UFOTree.closestSighting(city,state).city[0]) + UFOTree.closestSighting(city,state).city.substr(1);
                for (int i = 1; i < tempCity.size(); i++) {
                    if (isspace(tempCity[i - 1])) {
                        tempCity[i] = toupper(tempCity[i]);
                    }
                }
                cout << "  " << UFOTree.closestSighting(city,state).date.month << "/" << UFOTree.closestSighting(city,state).date.day << "/" << UFOTree.closestSighting(city, state).date.year << " at " << UFOTree.closestSighting(city, state).date.hour << ":" << UFOTree.closestSighting(city, state).date.minute << " in " << tempCity << ", " << UFOTree.closestSighting(city, state).state << ", " << UFOTree.closestSighting(city, state).country << "               \n";
                // hashtable
                cout<<"  Using Hash Table: "<<endl;
                UFOTable.closestSighting(city, state);
                if(UFOTable.closestSighting(city, state).date.year == 0){
                    break;
                }
                tempCity = (char) toupper(UFOTable.closestSighting(city,state).city[0]) +UFOTable.closestSighting(city,state).city.substr(1);
                for (int i = 1; i < tempCity.size(); i++) {
                    if (isspace(tempCity[i - 1])) {
                        tempCity[i] = toupper(tempCity[i]);
                    }
                }
                cout<<"  "<< UFOTable.closestSighting(city, state).date.month<<"/"
                <<UFOTable.closestSighting(city,state).date.day<<"/"
                <<UFOTable.closestSighting(city,state).date.year<<" at "
                <<UFOTable.closestSighting(city,state).date.hour<<":"
                <<UFOTable.closestSighting(city,state).date.minute<<" in "
                <<tempCity<<", "
                <<UFOTable.closestSighting(city,state).state<<", "
                <<UFOTable.closestSighting(city,state).country<< "               \n";
                break;

            case 2:
                //case 2 functionality
                cout << "  The most recent UFO sighting was on:               \n";
                //HEAP
                cout << "  Using a MaxHeap:                                   \n";
                tempCity= (char) toupper(UFOHeap.getMax().city[0])+UFOHeap.getMax().city.substr(1);
                for (int i = 1; i < tempCity.size(); i++) {
                    if (isspace(tempCity[i - 1])) {
                        tempCity[i] = toupper(tempCity[i]);
                    }
                }
                cout << "  " << UFOHeap.getMax().date.month << "/" << UFOHeap.getMax().date.day << "/"
                     << UFOHeap.getMax().date.year << " at " << UFOHeap.getMax().date.hour << ":"
                     << UFOHeap.getMax().date.minute << " in " << tempCity << ", "
                     << UFOHeap.getMax().state << ", " << UFOHeap.getMax().country << "              \n";

                //REDBLACKTREE
                cout << "  Using a RedBlackTree:                                \n";
                tempCity = (char) toupper(UFOTree.mostRecentSighting().city[0]) + UFOTree.mostRecentSighting().city.substr(1);
                for (int i = 1; i < tempCity.size(); i++) {
                    if (isspace(tempCity[i - 1])) {
                        tempCity[i] = toupper(tempCity[i]);
                    }
                }
                cout << "  " << UFOTree.mostRecentSighting().date.month << "/" << UFOTree.mostRecentSighting().date.day << "/" << UFOTree.mostRecentSighting().date.year << " at " << UFOTree.mostRecentSighting().date.hour << ":" << UFOTree.mostRecentSighting().date.minute << " in " << tempCity << ", " << UFOTree.mostRecentSighting().state << ", " << UFOTree.mostRecentSighting().country << "              \n";

                // Hashtable
                cout<<"  Using HashTable: "<<endl;
                cout << "  " << UFOTable.mostRecent().date.month << "/" << UFOTable.mostRecent().date.day
                << "/" << UFOTable.mostRecent().date.year << " at " << UFOTable.mostRecent().date.hour
                << ":" << UFOTable.mostRecent().date.minute << " in " << tempCity << ", "
                << UFOTable.mostRecent().state << ", " << UFOTable.mostRecent().country << "              \n";
                break;

            case 3:

                cout << "  Enter a state or state abbreviation: ";
                cin.clear();
                cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                getline(std::cin, state);

                while (true) {
                    if ((stateMap.find(state) != stateMap.end() || stateAbbrev.find(state) != stateAbbrev.end()) &&
                        state.length() > 0) {
                        if (stateMap.find(state) != stateMap.end()) {
                            state = stateMap[state];
                        }
                        break;
                    }
                    else {
                        cout << "  Invalid state. Please enter a valid state or state abbreviation.\n";
                        cin.clear();
                        cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                    }
                    getline(std::cin, state);
                }
                //case 3 functionality

                //HEAP
                cout << "  The UFO sightings in " << state << " are:              \n";
                cout << "  +--------------------------------------------------------+\n";
                cout << "  |                     Using MaxHeap                      |\n";
                cout << "  +--------------------------------------------------------+\n";
                for (auto &sighting : UFOHeap.stateList(state)) {
                    tempCity= (char) toupper(sighting.city[0])+sighting.city.substr(1);
                    for (int i = 1; i < tempCity.size(); i++) {
                        if (isspace(tempCity[i - 1])) {
                            tempCity[i] = toupper(tempCity[i]);
                        }
                    }
                    cout << "  Sighting in " << tempCity << ", " << state << " on "
                         << sighting.date.month << "/" << sighting.date.day << "/" << sighting.date.year
                         << " at " << sighting.date.hour << ":" << sighting.date.minute << endl;
                }
                UFOHeap.maxHeapify(sightings);
                //REDBLACKTREE
                cout << "  +--------------------------------------------------------+\n";
                cout << "  |                 Using RedBlackTree                     |\n";
                cout << "  +--------------------------------------------------------+\n";
                UFOTree.sightingsInState(state);
                if (UFOTree.sightingsInState(state).empty()) {
                    cout << "  No sightings found in " << state << endl;
                } else {
                    for (const auto& sighting : UFOTree.sightingsInState(state)) {
                        tempCity= (char)toupper(sighting.city[0])+sighting.city.substr(1);
                        for (int i = 1; i < tempCity.size(); i++) {
                            if (isspace(tempCity[i - 1])) {
                                tempCity[i] = toupper(tempCity[i]);
                            }
                        }
                        cout << "  Sighting in " << tempCity << ", " << state << " on "
                             << sighting.date.month << "/" << sighting.date.day << "/" << sighting.date.year
                             << " at " << sighting.date.hour << ":" << sighting.date.minute << endl;
                    }
                }
                //Hashtable
                cout << "  +--------------------------------------------------------+\n";
                cout << "  |                    Using HashTable                     |\n";
                cout << "  +--------------------------------------------------------+\n";
                UFOTable.ListofSightings(state);
                if (UFOTable.ListofSightings(state).empty()) {
                    cout << "  No sightings found in " << state << endl;
                } else {
                    for (const auto& sighting : UFOTable.ListofSightings(state)) {
                        tempCity = (char) toupper(sighting.city[0]) + sighting.city.substr(1);
                        for (int i = 1; i < tempCity.size(); i++) {
                            if (isspace(tempCity[i - 1])) {
                                tempCity[i] = toupper(tempCity[i]);
                            }
                        }
                        cout << "  Sighting in " << tempCity << ", " << state << " on "
                             << sighting.date.month << "/" << sighting.date.day << "/" << sighting.date.year
                             << " at " << sighting.date.hour << ":" << sighting.date.minute << endl;
                    }
                }
                break;


            case 4:
                cout << "  Exiting the program.\n";
                return 0;

            default:
                cout << "  Invalid choice. Please enter a number between 1 and 4.\n";
                cin.clear();
                cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                break;

        }

    }

}
