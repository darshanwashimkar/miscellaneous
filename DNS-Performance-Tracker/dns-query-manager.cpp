/*
 * File Name: dns-query-manager.cpp
 * Author : Darshan Washimkar
 * Email : darshan.wash@gmail.com
 * Created On : 26th Aug 2015
 *
 */

#include "dns-query-manager.hpp"

/* Got help from http://stackoverflow.com/questions/440133/how-do-i-create-a-random-alpha-numeric-string-in-c*/
std::string QueryManager::genRandomURL(const char *url){
   if(url == NULL)
      return(NULL);

   std::stringstream ss;
   static const char alphanum[] = "0123456789"
                                  "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
                                   "abcdefghijklmnopqrstuvwxyz";   
   for (int i = 0; i < 16; i++) {
      ss << (alphanum[rand() % (sizeof(alphanum) - 1)]);
   }
   
   ss << url;
   return(ss.str());
}


