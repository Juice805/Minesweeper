//
//  juice.h
//  Minesweeper
//
//  Created by Justin Oroz on 10/27/14.
//  Copyright (c) 2014 jmoroz. All rights reserved.
//

// This includes most of the functions that I reuse regularly

#ifndef juice_h
#define juice_h

#include <stdio.h>
#include <iostream>
#include <string>
#include <algorithm>
#include <ctype.h>
#include <string>
using namespace std;


bool valid(const int&, const int&, const int&);
bool valid(const float&, const float&, const float&);
string stringtolower(string);
bool prompt(string);


#endif /* defined(juice_h) */
