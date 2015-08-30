/*
 * File Name: domain-stat.manager.cpp
 * Author : Darshan Washimkar
 * Email : darshan.wash@gmail.com
 * Created On : 26th Aug 2015
 *
 */

#include "domain-stat-manager.hpp"

StatManager::StatManager(InputHandler *input){
   top_sites.insert( top_sites.end(), {"google.com", "facebook.com", 
                             "youtube.com", "yahoo.com", "live.com", 
                         "wikipedia.org", "baidu.com", "blogger.com", 
                                             "msn.com", "qq.com"});
   if((iter_rem = input->getIteration()) == 0){
      iter_rem = UINT_MAX;
   }      

   qm = new QueryManager();
   dbm = new DBManager(input);

   /* Initialize database 'stat' table */
   for(int i = 0; i < top_sites.size(); i++){
      dbm->insertToStat(top_sites.at(i), i, 0.0, 0.0, 0, 0, 0);
   }   
}

StatManager::~StatManager(){
   top_sites.clear();
   delete(qm);
   delete(dbm);
}


void StatManager::recordQueryStat(std::string &url){
   std::cout<<qm->queryDomain(url)<<std::endl;
}

void StatManager::runIteration(){
   
   for(int i = 0; i < top_sites.size(); i++){
      recordQueryStat(top_sites.at(i));
   }
}


void StatManager::run(unsigned int freq){

   unsigned int wait_time = (1000000/freq); // microseconds
//   boost::thread_group tg;

   while(iter_rem--){
      std::cout<<"-"<<iter_rem<<"-";
      boost::thread(boost::bind(&StatManager::runIteration, this)).detach();
      //tg.create_thread(boost::bind(&StatManager::runIteration, this));
      usleep(wait_time);
   }
//   tg.join_all();

   std::cout<<"\nI'm Done"<<std::endl;

}
