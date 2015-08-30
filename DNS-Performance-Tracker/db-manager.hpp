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
#include <cmath>

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
bool insertToStat(std::string &, int &, long double, long double, 
                  long double, unsigned long long,
                  unsigned long long, unsigned long long);

void readStatTable(int id, long double &avg, long double &m2, long long &count);

};


