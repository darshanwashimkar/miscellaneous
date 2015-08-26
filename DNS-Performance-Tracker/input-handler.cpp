/*
 * File Name: input-handler.cpp
 * Author : Darshan Washimkar
 * Email : darshan.wash@gmail.com
 * Created On : 26th Aug 2015
 *
 */

#include <iostream>
#include <getopt.h>
#include "input-handler.hpp"

InputHandler::InputHandler(){
   freq = 30;
   db_server = NULL;
   port = 0;
   db_name = NULL;
   db_uname = NULL;
   passwd = NULL;
}

InputHandler::~InputHandler(){
   free(db_server);
   free(db_name);
   free(db_uname);
   free(passwd);   
}

int InputHandler::usage(){
   std::cout<<"DNS Performance Tracker"<<std::endl;
   std::cout<<"Usage: dpt [OPTIONS]";
}

int InputHandler::getParameters(int argc, char** argv){
   std::cout<<"HAHAHA";
   return(1);
}

void InputHandler::setFreq(unsigned int newfreq){
   freq = newfreq;
}

unsigned int InputHandler::getFreq(){
   return(freq);
}
