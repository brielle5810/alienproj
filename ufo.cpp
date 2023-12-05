//
// Created by B on 11/23/2023.
//

#include "ufo.h"
#include <iostream>
#include <string>
#include <limits>
#include <fstream>
#include <random>
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
                }
            }
            //add to sighitngs vector
            sightings.push_back(sighting);
        }
    }

    file.close();
    return sightings;
}
string getRand(vector<string>& vals, mt19937& rng) {
    uniform_int_distribution<int> distribution(0, vals.size() - 1);
    int index = distribution(rng);
    return vals[index];
}

UFOSighting genPoints(mt19937& rng){
    UFOSighting sighting;
    srand(time(nullptr));
    vector<string> cities = {"New York", "Los Angeles", "Chicago", "Key West", "Wellington","Key Largo","Houston", "Phoenix", "Philadelphia", "San Antonio", "San Diego", "Dallas", "San Jose",
                                          "Austin", "Jacksonville", "San Francisco", "Indianapolis", "Columbus", "Fort Worth", "Charlotte", "Seattle", "Denver", "El Paso",
                                          "Detroit", "Washington", "Boston","Alpharetta","Jonesville","Micanopy","Gotham","Memphis", "Nashville", "Portland", "Oklahoma City", "Las Vegas", "Baltimore", "Louisville",
                                          "Milwaukee", "Albuquerque", "Metropolis","Tucson", "Fresno", "Sacramento", "Kansas City", "Long Beach", "Mesa", "Atlanta", "Colorado Springs",
                                          "Virginia Beach", "Raleigh", "Omaha", "Miami", "Oakland", "Minneapolis", "Tulsa", "Arlington", "Gainesville", "Wichita"};

    vector<string> states = {"AL", "AK", "AZ", "AR", "CA", "CO", "CT", "DE", "FL", "GA", "HI", "ID", "IL", "IN", "IA", "KS", "KY", "LA", "ME", "MD",
                                          "MA", "MI", "MN", "MS", "MO", "MT", "NE", "NV", "NH", "NJ", "NM", "NY", "NC", "ND", "OH", "OK", "OR", "PA", "RI", "SC", "SD",
                                          "TN", "TX", "UT", "VT", "VA", "WA", "WV", "WI", "WY"};
    sighting.country = "US";
    sighting.city = getRand(cities, rng);
    sighting.state = getRand(states, rng);
    sighting.year = uniform_int_distribution<int>(1990, 2013)(rng);
    sighting.month = uniform_int_distribution<int>(1, 12)(rng);
    sighting.day = uniform_int_distribution<int>(1, 28)(rng);
    sighting.hour = uniform_int_distribution<int>(0, 23)(rng);
    sighting.minute = uniform_int_distribution<int>(0, 59)(rng);

    sighting.date.year = sighting.year;
    sighting.date.month=sighting.month;
    sighting.date.day=sighting.day;
    sighting.date.hour=sighting.hour;
    sighting.date.minute=sighting.minute;

    return sighting;
}


vector<UFOSighting> fauxPoints() { //generate points bc dataset itself is not large enough
    mt19937 rng(static_cast<unsigned>(time(0)));
    vector<UFOSighting> fauxPointVect;
    for (int i = 0; i < 20000; i++) {
        fauxPointVect.push_back(genPoints(rng));
    }
    return fauxPointVect;
}
