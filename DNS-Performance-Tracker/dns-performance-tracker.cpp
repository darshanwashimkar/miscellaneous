/*
 * File Name: dns-performance-tracker.cpp
 * Author : Darshan Washimkar
 * Email : darshan.wash@gmail.com
 * Created On : 26th Aug 2015
 *
 */

#include <stdlib.h> 
#include "input-handler.hpp"

#ifndef _DOMAIN_STAT_MANAGER_HPP
#include "domain-stat-manager.hpp"
#endif

int main(int argc, char* argv[]){

InputHandler *input =  new InputHandler();

if(input->getParameters(argc, argv) < 0){
   delete input;
   return(EXIT_FAILURE);
}


/* ------------------------------- */
input->printParameters();
/* ------------------------------- */

/* seeding rand */
srand(time(0));

StatManager *stat = new StatManager(input);
stat->run(input->getFreq());

return(EXIT_SUCCESS);
}
