/*
 * File Name: domain-stat.manager.cpp
 * Author : Darshan Washimkar
 * Email : darshan.wash@gmail.com
 * Created On : 28th Aug 2015
 *
 */

#include "domain-stat-manager.hpp"

StatManager::StatManager(InputHandler *input){

   no_threads = 0;

   top_sites.insert( top_sites.end(), {"google.com", "facebook.com", 
                             "youtube.com", "yahoo.com", "live.com", 
                         "wikipedia.org", "baidu.com", "blogger.com", 
                                             "msn.com", "qq.com"});
   avg = 0.0;
   m2 = 0.0;
   std_dev = 0.0;
   count = 0;
   first_q_time = 0;
   last_q_time = 0;


   if((iter_rem = input->getIteration()) == 0){
      iter_rem = UINT_MAX;
   }      

   qm = new QueryManager();
   dbm = new DBManager(input);

   /* Initialize database 'stat' table */
   for(int i = 0; i < top_sites.size(); i++){
      dbm->insertToStat(top_sites.at(i), i, avg, std_dev, m2, count, 
                                          first_q_time,last_q_time);
   }   
}

StatManager::~StatManager(){
   top_sites.clear();
   delete(qm);
   delete(dbm);
}


void StatManager::recordQueryStat(std::string &url, int id){
   unsigned long long cur_time = findCurrentUTCTimeMilliseconds();
   uint32_t latency = qm->queryDomain(url);

   if(latency == 0){
      return;
   }

   /* Critical section start from here */
   {
      std::lock_guard<std::mutex> lock(db_mutex);

      if(!dbm->readStatTable(id, avg, m2, count, first_q_time, last_q_time)){
         return;
      }

      std_dev = stdDev(latency, avg, count, m2);
      if(count == 1){
         if(!dbm->updateStat(id, avg, std_dev, m2, count, cur_time, cur_time)){
            return;
         }
      }
      else{
         if(cur_time > last_q_time){
            if(!dbm->updateStat(id, avg, std_dev, m2, count, first_q_time, cur_time)){
               return;
            }
         }
         else{
            if(!dbm->updateStat(id, avg, std_dev, m2, count, first_q_time, last_q_time)){
               return;
            }
         }
      }
      
      /* Update timeserease table */
      if(!dbm->updateTimeseriesTable(id, cur_time, latency)){
         return;
      }

   }

   /* Critical section ends here */
}

void StatManager::runIteration(){

   no_threads++;

   for(int i = 0; i < top_sites.size(); i++){
      recordQueryStat(top_sites.at(i), i);
   }
   
   no_threads--;
}


void StatManager::run(unsigned int freq){

   unsigned int wait_time = (1000000/freq); // microseconds

   while(iter_rem--){
      std::cout<<"-"<<iter_rem<<"-";
      boost::thread(boost::bind(&StatManager::runIteration, this)).detach();
      usleep(wait_time);
   }

   while(no_threads != 0){
      // Waiting for all threads to finish 
      // (I know this is a short-cut, not a proper way to do it)
      // Need to finish this today
   }

   std::cout<<"\nI'm Done"<<std::endl;

}


double StatManager::stdDev(uint32_t value, double &mean, unsigned long long &n, double& m2){
    n++;
    double delta = value - mean;
    mean = mean + delta/n;
    m2 = m2 + delta*(value - mean);
    
    if (n < 2)
        return(0);
    else
        return sqrt(m2 / (n - 1));
}


unsigned long long StatManager::findCurrentUTCTimeMilliseconds(){
    struct timeval tv;

   gettimeofday(&tv, NULL);
   unsigned long long millisecondsSinceEpoch =
      (unsigned long long)(tv.tv_sec) * 1000 +
      (unsigned long long)(tv.tv_usec) / 1000;
      
   return(millisecondsSinceEpoch);
}

