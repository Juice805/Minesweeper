//
//  juice.cpp
//  Minesweeper
//
//  Created by Justin Oroz on 10/27/14.
//  Copyright (c) 2014 jmoroz. All rights reserved.
//

#include "juice.h"

bool valid(const int& number, const int& max, const int& min = 0) {
    if ((number >= min) && (number <= max))
        return true;
    else return false;
}

bool valid(const float& number, const float& max, const float& min = 0.0) {
    if ((number >= min) && (number <= max))
        return true;
    else return false;
}

string stringtolower(string str) {
    string lowerString = str;
    
    transform(lowerString.begin(), lowerString.end(), lowerString.begin(), ::tolower);
    return lowerString;
}

bool prompt(string prompt){
    string response;
    bool validResponse = false;
    bool answer;
    
    cout << endl << prompt << " (y/n)\n";
    do {
        cin >> response;
        cin.ignore(INT_MAX,'\n');
        cin.clear();
        
        if (tolower(response[0]) == 'y') {
            validResponse = true;
            answer = true;
        } else if (tolower(response[0]) == 'n') {
            validResponse = true;
            answer = false;
        } else {
            cout << "\nPlease enter a valid response (y/n)\n";
            validResponse = false;
            answer = false;
        }
    } while (!validResponse);
    
    return answer;
}

