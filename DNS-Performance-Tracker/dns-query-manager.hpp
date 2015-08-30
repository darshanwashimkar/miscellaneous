/*
 * File Name: dns-query-manager.hpp
 * Author : Darshan Washimkar
 * Email : darshan.wash@gmail.com
 * Created On : 26th Aug 2015
 *
 */

#define _DNS_QUERY_MANAGER_HPP
#include <string>
#include <sstream>
#include <iostream>
#include <cstdlib>
#include <ldns/ldns.h>

class QueryManager {

public:
   QueryManager();
   ~QueryManager();
   std::string genRandomURL(std::string&);
   uint32_t queryDomain(std::string);   
};
