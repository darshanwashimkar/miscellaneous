/*
 * File Name: input-handler.cpp
 * Author : Darshan Washimkar
 * Email : darshan.wash@gmail.com
 * Created On : 26th Aug 2015
 *
 */

#include "input-handler.hpp"

InputHandler::InputHandler(){
   freq = 10;
   db_server = NULL;
   port = 0;
   db_name = NULL;
   db_user = NULL;
   passwd = NULL;
   iter = -1; // infinite number of iterations
}

InputHandler::~InputHandler(){
   free(db_server);
   free(db_name);
   free(db_user);
   free(passwd);   
}

int InputHandler::usage(){
   std::cout<<"DNS Performance Tracker"<<std::endl;
   std::cout<<"Usage: dpt [OPTIONS]";
   std::cout<<"frequency need to be +ve";
}

int InputHandler::getParameters(int argc, char** argv){
   int help_flag = 0;
   static struct option long_options[] = {
      {"help",      no_argument,        &help_flag, 1  },
      {"frequency", required_argument,  0,         'f' },
      {"server",    required_argument,  0,         's' },
      {"port",      required_argument,  0,         'p' },
      {"database",  required_argument,  0,         'd' },
      {"user",      required_argument,  0,         'u' },
      {"pawssword", required_argument,  0,         'w' },
      {"iteration", required_argument,  0,         'i' },
      {0,           0,                  0,          0  }
   };
   
   int option_index = 0;
   int opt;
   while((opt = getopt_long (argc, argv, "f:s:p:d:u:w:i:", long_options, 
                                               &option_index)) != -1){
      switch (opt){
         case 'f':
            freq = atoi(optarg);
            break;     
         case 's':
            db_server = strdup(optarg);
            break;     
         case 'p':
            port = atoi(optarg);
            break;
         case 'd':
            db_name = strdup(optarg);
            break;     
         case 'u':
            db_user = strdup(optarg);
            break;     
         case 'w':
            passwd = strdup(optarg);
            break;
         case 'i':
            iter = atoi(optarg);
            break;     
         case '?':
         default:
            usage();
            return(-1);
      }
    
      if(help_flag) {
         usage();
         return(-1);
      }

      if(freq < 1 ) {
         usage();
         return(-1);
      }

   }

   return(0);
}

unsigned int InputHandler::getFreq(){
   return(freq);
}

char * InputHandler::getDbServer(){
   return(db_server);
}

unsigned int InputHandler::getPort(){
   return(port);
}

char * InputHandler::getDbName(){
   return(db_name);
}

char * InputHandler::getDbUser(){
   return(db_user);
}

char * InputHandler::getPassword(){
   return(passwd);
}

unsigned int InputHandler::getIteration(){
   return(iter);
}

void InputHandler::printParameters(){
   std::cout<<"Frequency: "<<freq<<std::endl;
   if(db_server != NULL)
      std::cout<<"Database Server IP: "<<db_server<<std::endl;
   std::cout<<"Port: "<<port<<std::endl;
   if(db_name != NULL)
      std::cout<<"Database name: "<<db_name<<std::endl;
   if(db_user != NULL)
      std::cout<<"User name: "<<db_user<<std::endl;
   if(passwd != NULL)
      std::cout<<"Password: "<<passwd<<std::endl;
}
