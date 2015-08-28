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

   qm = new QueryManager();
   dbm = new DBManager();
}

StatManager::~StatManager(){
   top_sites.clear();
   delete(qm);
   delete(dbm);
}


void StatManager::run(){
   std::string str = "google.com";
   std::cout<<qm->genRandomURL(str.c_str())<<std::endl;
}
