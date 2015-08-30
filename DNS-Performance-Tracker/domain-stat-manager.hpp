/*
 * File Name: domain-stat-manager.hpp
 * Author : Darshan Washimkar
 * Email : darshan.wash@gmail.com
 * Created On : 28th Aug 2015
 *
 */

#define _DOMAIN_STAT_MANAGER_HPP
#include<vector>
#include<string>
#include <limits.h>
#include <unistd.h>
#include <boost/thread.hpp>
#include <mutex>
#include <cmath>
#include <atomic>

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

   double avg;
   double m2;
   double std_dev;
   unsigned long long count;
   unsigned long long first_q_time;
   unsigned long long last_q_time;

   std::mutex db_mutex;
   std::atomic<unsigned int> no_threads;

   public:
   StatManager(InputHandler*);
   ~StatManager();
   void run(unsigned int);
   void runIteration();
   void recordQueryStat(std::string &, int);
   /* Welford's online algorithm to find standard deviation variance */
   double stdDev(uint32_t value, double &mean, unsigned long long &n, double& M2);
   unsigned long long findCurrentUTCTimeMilliseconds();
};
