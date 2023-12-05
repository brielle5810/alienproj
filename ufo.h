//
// Created by B on 11/23/2023.
//

#ifndef SIGHITNG_UFO_H
#define SIGHITNG_UFO_H
#pragma once
#include <iostream>
#include <vector>
#include <string>
#include <ctime>
#include <cstdlib>
using namespace std;

struct Date {
    int year;
    int month;
    int day;
    int hour;
    int minute;
    bool operator<(const Date& rhs) const;
    bool operator>(const Date& rhs) const { // ana- added this too
        return !(*this < rhs);
    }

};
struct UFOSighting {
    string country;
    string city;
    string state;
    string shape;
    double latitude;
    double longitude;
    int year;
    int month;
    int day;
    string duration;
    string description;
    bool operator<(UFOSighting& rhs);
    int docyear;
    int docmonth;
    int docday;
    int hour;
    int minute;
    UFOSighting(); //default constructor
    UFOSighting *parent;
    UFOSighting *left;
    UFOSighting *right;
    int color;
    Date date;
    bool operator<(const UFOSighting& rhs) const {
        return date < rhs.date;
    }
};

vector<UFOSighting> parseJSON(const string& jsonFileName);
vector<UFOSighting> fauxPoints();

string getRand();


#endif //SIGHITNG_UFO_H
