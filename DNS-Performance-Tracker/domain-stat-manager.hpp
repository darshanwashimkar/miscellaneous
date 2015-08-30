/*
 * File Name: domain-stat-manager.hpp
 * Author : Darshan Washimkar
 * Email : darshan.wash@gmail.com
 * Created On : 26th Aug 2015
 *
 */

#define _DOMAIN_STAT_MANAGER_HPP
#include<vector>
#include<string>
#include <limits.h>
#include <unistd.h>
#include <boost/thread.hpp>
#include <mutex>

#ifndef _INPUT_HANDLER_HPP
#include "input-handler.hpp"
#endif

#ifndef _DNS_QUERY_MANAGER_HPP
#include "dns-query-manager.hpp"
#endif

#ifndef _DB_MANAGER_HPP
#include "db-manager.hpp"
#endif

class StatManager {
   std::vector<std::string> top_sites;
   unsigned int iter_rem;
   QueryManager *qm;
   DBManager *dbm;
   std::mutex db_mutex;

   public:
   StatManager(InputHandler*);
   ~StatManager();
   void run(unsigned int);
   void runIteration();
   void recordQueryStat(std::string &);
   /* Welford's online algorithm to find standard deviation variance */
   long double stdDev(uint32_t value, double &mean, int &n, double& M2);
};
