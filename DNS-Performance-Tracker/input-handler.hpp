/*
 * File Name: input-handler.hpp
 * Author : Darshan Washimkar
 * Email : darshan.wash@gmail.com
 * Created On : 28th Aug 2015
 *
 */

#define _INPUT_HANDLER_HPP
#include <iostream>
#include <getopt.h>
#include <string.h>

class InputHandler {

unsigned int freq;
char * db_server;
unsigned int port;
char * db_name;
char * db_user;
char * passwd;
unsigned int iter;

public:
   InputHandler();
   ~InputHandler();
   static int usage();
   /* getters */
   unsigned int getFreq();
   char * getDbServer();
   unsigned int getPort();
   char * getDbName();
   char * getDbUser();
   char * getPassword();
   unsigned int getIteration();

   /* Returns -ve if something is wrong */
   int getParameters(int, char**);

//---------- delete below method after completing tool -------
   void printParameters();
//------------------------------------------------------------

};
