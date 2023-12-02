/*
 * BSD 3-Clause License
 * Copyright (c) 2023, Alexandra Stratton, Riley Sirimongkhon-Dyck,
 * Timo Aranjo, Victor Maduka, Ellia Morse, Deborah Onuosa
 */

//Include the header file "IOHandler.hpp" to makek the declarations in IOHandler.hpp avaialbe for use in this file
#include "IOHandler.hpp"

//The main function, where the execution begins
int main() {
  //Creates an instance of the IOHandler class named ioHandler
  IOHandler ioHandler; 
  //Calls the execute() method of the ioHandler instance, which prompts the user for input and displays the output
  ioHandler.execute();
  //Return 0 to indicate successful execution
  return 0;
}
