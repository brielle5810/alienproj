//
// Created by B on 11/23/2023.
//

#include "ufo.h"
#include <iostream>
#include <string>
#include <limits>
#include <fstream>
#include <algorithm>
#include <sstream>

using namespace std;
bool UFOSighting::operator<(UFOSighting& rhs) {
    return this->date < rhs.date;
}


bool Date::operator<(const Date& rhs) const { //ana- made a change to this, made const because wasn't working in comparison
    if (year != rhs.year) {
        return this->year < rhs.year;
    }
    if (month != rhs.month) {
        return this->month < rhs.month;
    }
    if (day != rhs.day) {
        return this->day < rhs.day;
    }
    if (hour != rhs.hour) {
        return this->hour < rhs.hour;
    }
    return this->minute < rhs.minute;
}

UFOSighting::UFOSighting() {

    city="NULL";
    country="NULL";
    state="NULL";
}
// bool insert(UFOSighting& node, UFOSighting& data) {
//    example use of the Date comparison operator!
//    if (data.date < node->date) {
//        insert (node->left, data);
//    }
//    else {
//        insert (node->right, data);
//    }

vector<UFOSighting> parseJSON(const string& jsonFileName) {
    //read in all siting and create Sighting add to sightings vector
    vector<UFOSighting> sightings;
    ifstream file(jsonFileName);
    cout << jsonFileName << endl;//check correct file
    if (!file.is_open()) { //check if file open
        cerr << "CANT OPEN FILE" << endl;
        return sightings;
    }
    string line;
    while (getline(file, line)) {
        if (line.find("{") != string::npos) {
            UFOSighting sighting;
            int openBraces = 1;  // track open braces
            int closeBraces = 0; // track close braces
            // so it knows when a sighting begins/ends bc nested {}
            while (openBraces != closeBraces) {
                //until end of sighting
                getline(file, line);
                // count braces
                openBraces += count(line.begin(), line.end(), '{');
                closeBraces += count(line.begin(), line.end(), '}');
                int colonPos = line.find(":");
                if (colonPos != string::npos) {
                    //get key and value. ex "City": "San Diego" and assign to sighting
                    //use colon to split
                    string key = line.substr(0, colonPos);
                    string value = line.substr(colonPos + 1);
                    //remove spaces
                    key.erase(remove_if(key.begin(), key.end(), ::isspace), key.end());
                    if (key!="\"City\""){ //ignore for cities-> some have spaces "San Diego"
                        value.erase(remove_if(value.begin(), value.end(), ::isspace), value.end());
                    }
                    //assign all values
                    if (key == "\"City\"") {
                        sighting.city =  value.substr(2, value.size() - 4);
                    } else if (key == "\"State\"") {
                        sighting.state = value.substr(1, value.size() - 3);
                    } else if (key == "\"Country\"") {
                        sighting.country = value.substr(1, value.size() - 3);
                    } else if (key == "\"Latitude\"") {
                        sighting.latitude = stod(value);
                    } else if (key == "\"Longitude\"") {
                        sighting.longitude = stod(value);
                    } else if (key == "\"Shape\"") {
                        sighting.shape = value.substr(1, value.size() - 3);
                    } else if (key == "\"Encounter duration\"") {
                        sighting.duration = stod(value);
                    } else if (key == "\"Description excerpt\"") {
                        sighting.description = value.substr(1, value.size() - 3);
                    } else if (key == "\"Year\"") {
                        sighting.year = stoi(value);
                        sighting.date.year=sighting.year;
                    } else if (key == "\"Month\"") {
                        sighting.month = stoi(value);
                        sighting.date.month=sighting.month;
                    } else if (key == "\"Day\"") {
                        sighting.day = stoi(value);
                        sighting.date.day=sighting.day;
                    } else if (key == "\"Hour\"") {
                        sighting.hour = stoi(value);
                        sighting.date.hour=sighting.hour;
                    } else if (key == "\"Minute\"") {
                        sighting.minute = stoi(value);
                        sighting.date.minute=sighting.minute;
                    }

                    else if (key == "\"Documented Year\"") {
                        sighting.docyear = stoi(value);
                    } else if (key == "\"Documented Month\"") {
                        sighting.docmonth = stoi(value);
                    } else if (key == "\"Documented Day\"") {
                        sighting.docday = stoi(value);
                    }
                }
            }
            //add to sighitngs vector
            sightings.push_back(sighting);
        }
    }

    file.close();
    //test that it works
//    for (int i=0;i<10;i++){
//        cout <<i + 1<<". "<< sightings[i].city << " at "<< sightings[i].date.month<<"/"<<sightings[i].date.day<<"/"<<sightings[i].date.year<<endl;
//        cout<<"At time: "<< sightings[i].date.hour<<":"<<sightings[i].date.minute<<endl;
//    }
    return sightings;
}
