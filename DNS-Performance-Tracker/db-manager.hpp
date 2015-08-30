/*
 * File Name: db-manager.hpp
 * Author : Darshan Washimkar
 * Email : darshan.wash@gmail.com
 * Created On : 26th Aug 2015
 *
 */

#define _DB_MANAGER_HPP
#include <mysql++.h>
#include <iostream>
#include <sstream>

#ifndef _INPUT_HANDLER_HPP
#include "input-handler.hpp"
#endif

class DBManager {
   mysqlpp::Connection conn;
   std::stringstream ss;
   mysqlpp::SimpleResult result;
   
public:

DBManager(InputHandler *);
~DBManager();
bool insertToStat(std::string &, int &, double, double, 
                  unsigned long int, unsigned long int, 
                                    unsigned long int);
};
