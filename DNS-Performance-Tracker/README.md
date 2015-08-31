# Tracking DNS performance to top sites
Importance: Such performance numbers to top sites can be used as benchmarks for others to compare to.

Description:
Write a C++ (not C) program on Linux/BSD(Mac) that periodically sends DNS queries to the nameservers of the top 10 Alexa domains and stores the latency values in a mysql table. The frequency of queries should be specified by the user on command line. The program needs to make sure it doesn't hit the DNS cache while trying to query for a site and should use a random string prepended to a domain. E.g. to query foo.bar, make sure to prepend a random string, e.g. 1234xpto.foo.bar.

Besides the timeseries values, the code needs to keep track in db stats per domain about:
+ the average query times
+ standard deviation of DNS query times
+ number of queries made so far
+ time stamp of first query made per domain and last query made


Refs:
a. Mysql lib, use mysql++:
http://tangentsoft.net/mysql++/
b. DNS lib, use ldns:
http://www.nlnetlabs.nl/projects/ldns/

Top 10 domains to query:

+---------+---------------+
|    rank | name      	  |

+------+------------------+

|	1 | google.com	  |

|	2 | facebook.com  |

|	3 | youtube.com   |
|	4 | yahoo.com 	  |
|	5 | live.com  	  |
|	6 | wikipedia.org |
|	7 | baidu.com 	  |
|	8 | blogger.com   |
|	9 | msn.com   	  |
|      10 | qq.com    	  |
+------+------------------+
=================================

# Implementation details
1. Program uses "ldns_pkt_querytime()" method to find time required to resolve the query
2. This software use "Welford's online algorithm" to keep track of standard deviation.
3. This program us tested on "Ubuntu 14.04.3 LTS"
4. All times[first Query, Last Query, Query Time] are stored as number of 'miliseconds' from the epoch (i.e.Thursday, 1 January 1970)
5. This program will create two tables 'stat' and 'timeseries'

# Requirements
You will need following libraries to compile programs,
a. Mysql lib, use mysql++:
http://tangentsoft.net/mysql++/

b. DNS lib, use ldns:
http://www.nlnetlabs.nl/projects/ldns/

c. boost:
http://www.boost.org/

# Compilation:
1. Unzip the tarball 
2. run $make

# Sample run
$./dpt --help (This will print option list) (NOTE: for password please use 'w')

DNS Performance Tracker

Usage: dpt [OPTIONS]

         -f, --frequency        Frequency of DNS Query [per second][Default: 10]

         -s, --server           Address of mysql database server [Default: localhost]

         -p, --port             Port number of mysql database server [Default: 3306]

         -d, --database         Mysql database name [Default: DNSPerformance]

         -u, --user             User name for accessing mysql database [Mandatory]

         -w, --password         Password for accessing mysql database [Mandatory]

         -i, --iteration        Maximum number of iterations [default: infinite iterations)
