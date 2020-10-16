// Keypad.cpp
// Member-function definition for class Keypad (the ATM's keypad).
#include <iostream>
#include "Keypad.h" // Keypad class definition
using namespace std;

// return an integer value entered by user
int Keypad::getInput() const
{
   int input; // variable to store the input
   cin >> input; // we assume that user enters an integer
   return input; // return the value entered by user
} // end function getInput

