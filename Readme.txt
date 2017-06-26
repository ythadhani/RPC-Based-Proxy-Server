Readme:

When we initially compiled our code, we came across this error
"error while loading shared libraries: libthrift-0.9.3.so: cannot open shared object file: No such file or directory"

Apparently, it was searching for libthrift-0.9.3.so in the /usr/lib directory when it was actually present in the /usr/local/lib directory inspite of mentioning the correct path in the MakeFile

We did some digging online and found this fix:
On the command line type, (before actually compiling the code) 
export LD_LIBRARY_PATH=$LD_LIBRARY_PATH:/usr/local/lib for linking

Once this is done, we can go ahead and compile and run the code

How to compile and run our code:

1. In the directory, type 'make' and hit Enter
2. Start the server first by typing ./rpc_server <cache eviction policy> <cache size in KB> and hit Enter

For example,
To start a server that supports the lru eviction scheme and has a cache size of 100 KB type "./rpc_server lru 100" and hit Enter
For random, use "rnd" and "maxs" for MAXS.

3. Start the client on a different terminal window by typing ./rpc_client and hit Enter
4. The client will start making a bunch of requests to the server and once all the requests have been serviced, the Statistics of "Hit Ratio" and "Average Time per access" will be displayed.

Files included in the directory:
rpc_client.cpp: This file includes the code for the client which performs rpc calls to the server.
rpc_server.cpp: This file includes the server code.
cache.h: header files which include functions used in the cache implementation
cache.cpp: implementation of caching mechanisms
cache_vector_randevict: the eviction queue of the random eviction policy was implemented using a vector (not included in the Makefile)
indexminpq.cpp: implementation of the indexminpq data structure
indexrndq.cpp: implementation of the indexrndq data structure 
batch_generator.cpp: This file includes code which generated Workload1.txt
urls.txt: Used by batch_generator.cpp to generate Workload1.txt
Workload1.txt and Workload2.txt: The two workloads used by us
URL_sizes.txt: All URLs used by us in the project and their corresponding sizes


The rest were a bunch of files which were created by apache thrift.

