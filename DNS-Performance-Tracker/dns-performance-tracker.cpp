/*
 * File Name: dns-performance-tracker.cpp
 * Author : Darshan Washimkar
 * Email : darshan.wash@gmail.com
 * Created On : 26th Aug 2015
 *
 */

#include <stdlib.h> 
#include "input-handler.hpp"

int main(int argc, char* argv[]){

InputHandler *input =  new InputHandler();

if(input->getParameters(argc, argv) < 0){
   delete input;
   return(EXIT_FAILURE);
}

return(EXIT_SUCCESS);
}
