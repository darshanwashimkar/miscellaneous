/*
 * File Name: input-handler.cpp
 * Author : Darshan Washimkar
 * Email : darshan.wash@gmail.com
 * Created On : 26th Aug 2015
 *
 */

#include <iostream>
#include "input-handler.hpp"

int InputHandler::usage(){
   std::cout<<"DNS Performance Tracker"<<std::endl;
   std::cout<<"Usage: dpt [OPTIONS]";
}

void InputHandler::setFreq(unsigned int newfreq){
   freq = newfreq;
}

unsigned int InputHandler::getFreq(){
   return(freq);
}
