/*
 * File Name: dns-query-manager.cpp
 * Author : Darshan Washimkar
 * Email : darshan.wash@gmail.com
 * Created On : 26th Aug 2015
 *
 */

#include "dns-query-manager.hpp"


QueryManager::QueryManager(){

}


QueryManager::~QueryManager(){

}

uint32_t QueryManager::queryDomain(std::string domain_str){
   ldns_resolver *res;
   ldns_rdf *domain;
   ldns_pkt *p;
   ldns_status s;
   
   domain = ldns_dname_new_frm_str(genRandomURL(domain_str));
   if (!domain) {
      std::cerr<<"Unable to create ldns_rdf for "<<domain_str<<std::endl;
      /* Log error and return */
      return(0);
   }

   /* create a new resolver from /etc/resolv.conf */
   s = ldns_resolver_new_frm_file(&res, NULL);
   if (s != LDNS_STATUS_OK) {
      std::cerr<<"Unable to create resolver for "<<domain_str<<std::endl;
      /* Log error and return */
      return(0);
   }

   p = ldns_resolver_query(res,
                           domain,
                           LDNS_RR_TYPE_MX,
                           LDNS_RR_CLASS_IN,
                           LDNS_RD);

   ldns_rdf_deep_free(domain);

   if (!p){
      std::cerr<<"Error in resolving query for "<<domain_str<<std::endl;
      /* Log error and return */
      return(0);
   }

   uint32_t query_time = ldns_pkt_querytime(p);

   ldns_pkt_free(p);
   ldns_resolver_deep_free(res);
   
   return(query_time);
}

const char* QueryManager::genRandomURL(std::string url){
   if(url == "")
      return(NULL);

   std::stringstream ss;
   static const char alphanum[] = "0123456789"
                                  "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
                                   "abcdefghijklmnopqrstuvwxyz";   
   for (int i = 0; i < 16; i++) {
      ss << (alphanum[rand() % (sizeof(alphanum) - 1)]);
   }
   
   ss << url;
   return(ss.str().c_str());
}



