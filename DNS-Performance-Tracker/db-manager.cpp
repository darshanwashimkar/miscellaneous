/*
 * File Name: db-manager.cpp
 * Author : Darshan Washimkar
 * Email : darshan.wash@gmail.com
 * Created On : 28th Aug 2015
 *
 */

#include "db-manager.hpp"


DBManager::DBManager(InputHandler *input){

   /* Try to connect to DB server*/
   try{
      conn.connect(NULL,
                   input->getDbServer(), 
                   input->getDbUser(),
                   input->getPassword(),
                   input->getPort());

      conn.set_option(new mysqlpp::ReconnectOption(true));
      std::cout<<"Connected to the database"<<std::endl;

      /* Creating database if doesn't exist */
      ss.str("");
      ss << "CREATE DATABASE IF NOT EXISTS ";
      ss << input->getDbName();
      ss << ";";
      mysqlpp::Query query = conn.query(ss.str());
      result = query.execute();
      if (!result) {
         throw std::string("Unable to create database");
      }

      /* Select database */
      ss.str("");
      ss << "USE ";
      ss << input->getDbName();
      query = conn.query(ss.str());
      result = query.execute();
      if (!result) {
         throw std::string("Unable to select database");
      }

      /* Creating "stat" table */
      ss.str("");
      ss << "CREATE TABLE stat ";
      ss << "(";
      ss << "domain varchar(255) NOT NULL,";
      ss << "domain_id int NOT NULL,";
      ss << "avg_q_time decimal(19,4),";
      ss << "std_dev_q decimal(19,4),";
      ss << "m2 decimal(19,4),";
      ss << "q_count BIGINT,";
      ss << "first_q_time BIGINT,";
      ss << "last_q_time BIGINT,";
      ss << "PRIMARY KEY (domain_id)";
      ss << ")";
      query = conn.query(ss.str());
      result = query.execute();
      if (!result) {
         throw std::string("Unable to create table \'stat\' ");
      }

     /* Creating "stat" table */
      ss.str("");
      ss << "CREATE TABLE timeseries ";
      ss << "(domain_id int NOT NULL,";
      ss << "query_time BIGINT NOT NULL,";
      ss << "latency int NOT NULL,";
      ss << "FOREIGN KEY (domain_id) REFERENCES stat(domain_id))";
      query = conn.query(ss.str());
      result = query.execute();
      if (!result) {
         throw std::string("Unable to create table \'timeseries\' ");
      }      
   }
   catch (const mysqlpp::Exception& er) {
      // Catch-all for any other MySQL++ exceptions
      std::cerr << "Error: " << er.what() << std::endl;
      exit(EXIT_FAILURE);
   }
}

DBManager::~DBManager(){
}

bool DBManager::insertToStat(std::string &domain, int &id, double &avg_q_time,
                             double &std_dev_q, double &m2,
                             unsigned long long &count,
                             unsigned long long &first_q_time, 
                             unsigned long long &last_q_time){
   try{
      ss.str("");
      ss << "INSERT INTO stat (domain, domain_id, avg_q_time, std_dev_q,";
      ss << "m2, q_count, first_q_time, last_q_time)";
      ss << "VALUES ('";
      ss << domain;
      ss << "','";
      ss << id;
      ss << "','";
      ss << avg_q_time;
      ss << "','";
      ss << std_dev_q;
      ss << "','";
      ss << m2;
      ss << "','";
      ss << count;
      ss << "','";
      ss << first_q_time;
      ss << "','";
      ss << last_q_time;
      ss << "');";
      mysqlpp::Query query = conn.query(ss.str());
      result = query.execute();
      if (!result) {
         throw std::string("Unable to insert value in \'stat\' table");
      }
   }
   catch (const mysqlpp::Exception& er) {
      // Catch-all for any other MySQL++ exceptions
      std::cerr << "Error: " << er.what() << std::endl;
      exit(EXIT_FAILURE);
   }

   return(true);
}


bool DBManager::readStatTable(int id, double &avg, double &m2, 
                              unsigned long long &count,
                              unsigned long long & first_q_time, 
                              unsigned long long & last_q_time){
   try{
      ss.str("");
      ss << "select * from stat where domain_id =";
      ss << id;
      ss <<";";
      mysqlpp::Query query = conn.query(ss.str());
      mysqlpp::StoreQueryResult res = query.store();

      if(res && (res.num_rows() == 1)){
         avg = res[0]["avg_q_time"];
         m2 = res[0]["m2"];
         count = res[0]["q_count"];
         first_q_time = res[0]["first_q_time"];
         last_q_time = res[0]["last_q_time"];
      }
      else{
         throw std::string("Unable to get values from \'stat\' table");
      }
   }
   catch (const mysqlpp::Exception& er) {
      // Catch-all for any other MySQL++ exceptions
      std::cerr << "Error: " << er.what() << std::endl;
      return(false);
   }
   return(true);
}



bool DBManager::updateStat(int &id, double &avg_q_time,
                             double &std_dev_q, double &m2,
                             unsigned long long &count,
                             unsigned long long &first_q_time, 
                             unsigned long long &last_q_time){
   try{
      ss.str("");
      ss << "UPDATE stat ";
      ss << "SET avg_q_time='";
      ss << avg_q_time;
      ss << "', std_dev_q='";
      ss << std_dev_q;
      ss <<"', m2 = '";
      ss << m2;
      ss << "',q_count= '";
      ss << count;
      ss << "', first_q_time = '";
      ss << first_q_time;
      ss << "', last_q_time = '";
      ss << last_q_time;
      ss << "' WHERE domain_id='";
      ss << id;
      ss << "';";
  
      mysqlpp::Query query = conn.query(ss.str());
      result = query.execute();
      if (!result) {
         throw std::string("Unable to update value in \'stat\' table");
      }
   }
   catch (const mysqlpp::Exception& er) {
      // Catch-all for any other MySQL++ exceptions
      std::cerr << "Error: " << er.what() << std::endl;
      return(false);
   }

   return(true);
}


bool DBManager::updateTimeseriesTable(int &id, unsigned long long &q_time, uint32_t &latenct){

   try{
      ss.str("");
      ss << "INSERT INTO timeseries (domain_id, query_time, latency)";
      ss << "VALUES ('";
      ss << id;
      ss << "','";
      ss << q_time;
      ss << "','";
      ss << latenct;
      ss << "');";
      mysqlpp::Query query = conn.query(ss.str());
      result = query.execute();
      if (!result) {
         throw std::string("Unable to insert value in \'timeseries\' table");
      }
   }
   catch (const mysqlpp::Exception& er) {
      // Catch-all for any other MySQL++ exceptions
      std::cerr << "Error: " << er.what() << std::endl;
      return(false);
   }

   return(true);
}








