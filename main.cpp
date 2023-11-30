#include "ufo.h"
#include <iostream>
#include <string>
#include <limits>
#include <fstream>
#include <vector>
using namespace std;



int main() {
    string city, state;
    int choice;

    vector<UFOSighting> sightings= parseJSON("ufo_sightings.json");


    //printMenuBorder();
    while (true) {
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
        //cin >> choice;

        if (!(cin >> choice) || choice > 4 || choice < 1) {
            // clear cin and ignore choice
            cin.clear();
            cin.ignore('\n');
            cout << "Invalid input. Please enter a number between 1 and 4.\n";
            continue; //start over
        }

        switch (choice) {
            case 1:
                cout << "Enter city: ";
                cin >> city;
                cout << "Enter state: ";
                cin >> state;
                //case 1 functionality
                break;

            case 2:
                //case 2 functionality
                break;

            case 3:
                cout << "Enter state: ";
                cin >> state;
               //case 3 functionality
                break;

            case 4:
                cout << "Exiting the program.\n";
                return 0;

            default:
                cout << "Invalid choice. Please enter a number between 1 and 4.\n";
                cin.clear();
                break;
        }
    }

}