/*
 * File Name: input-handler.hpp
 * Author : Darshan Washimkar
 * Email : darshan.wash@gmail.com
 * Created On : 26th Aug 2015
 *
 */

class InputHandler {

unsigned int freq;
char * db_server;
unsigned int port;
char * db_name;
char * db_uname;
char * passwd;


public:
   InputHandler();
   ~InputHandler();
   static int usage();
   void setFreq(unsigned int);
   unsigned int getFreq();
   /* Returns -ve on failure*/
   int getParameters(int, char**);
};
