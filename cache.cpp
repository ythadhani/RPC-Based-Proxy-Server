#include <stdlib.h>
#include <stdio.h>
#include <string>
#include <sys/time.h>
#include "cache.h"
#include "indexminpq.h"
#include "indexrndq.h"
#include <map>
#include <deque>
#include <iostream>

using namespace std;

int cache_policy;
 
//cache entry structure 
typedef struct {
  string key;                  //URL
  string value;                //HTML content of page fetched via HTTP
  size_t val_size;             //represents size of page
  int id;                      //unique identifier
  struct timeval tv;           //timestamp for this entry
  size_t val_size_complement;  //cache_capacity - val_size
} cache_entry_t;

//cache as a map data structure 
map<string,cache_entry_t*> cache_hash;
map<string,cache_entry_t*>::iterator cache_hash_iter;

//for unique identifiers
deque<int> id_queue;

static size_t min_size;
static size_t used_mem;
static size_t cache_capacity;

static cache_entry_t* cache;

//eviction queue for the RANDOM eviction policy
static indexrndq_t rand_evict_queue;

//eviction queue for LRU and MAXS eviction policy
static indexminpq_t eviction_queue;

//function that compares keys in the indexminpq data structure
int keycmp(indexminpq_key a, indexminpq_key b)
{
  switch (cache_policy)
  { 
    //for LRU
    case 0: 
     {
  	   struct timeval* tva;
  	   struct timeval* tvb;

      	tva = (struct timeval*) a;
      	tvb = (struct timeval*) b;
      	
      	if (tva->tv_sec > tvb->tv_sec)
        		return 1;
      	else if (tva->tv_sec < tvb->tv_sec)		//Basically return 1 if tva>tvb, -1 if tva<tvb or 0 if both are equal
        		return -1;
      	else if (tva->tv_usec > tvb->tv_usec)
        		return 1;
      	else if (tva->tv_usec < tvb->tv_usec)
        		return -1;
      	else
        		return 0;
            break;
      }
      
    //for MAXS
    case 1:
      { 
      	size_t val_comp1 = *(size_t*)a;
    		size_t val_comp2 = *(size_t*)b;
    		if(val_comp1>val_comp2)
    			return 1;
    	 	else if(val_comp2>val_comp1)
    			return -1;
    	 	else
    			return 0;
          break;
      }
      //don't need to do anything for RANDOM

   }
   return 0; 
}

static void deleteentry(cache_entry_t* e)
{
  /*
    e is assumed to have already been evicted from the priority queue.
  */
  used_mem -= e->val_size > min_size ? e->val_size : min_size;  
  //Since an entry is deleted, the used_mem reduces/ free memory increases
  
  //erasing the key in the map
  cache_hash.erase(e->key);

  //freeing the unique identifier associated with this entry
  id_queue.push_front(e->id);

}

void cache_init(size_t capacity, size_t min_entry_size, const string& cache_pol){
  int j, nmax;

  if(cache_pol.compare("lru")==0)
  {
	cache_policy=0;
  }
  else if(cache_pol.compare("maxs")==0)
  {
	cache_policy=1;
  }
  else if(cache_pol.compare("rnd")==0)
  {
	cache_policy=2;
  }
  
  min_size = min_entry_size;
  cache_capacity = capacity;
  used_mem = 0;

  nmax = cache_capacity / min_size;
  
  //dynamic array of cache entry structure
  cache = new cache_entry_t[nmax];
 
  //initializing eviction queues
  indexminpq_init(&eviction_queue, nmax, keycmp);  

  indexrndq_init(&rand_evict_queue, nmax);
    
  //assigning unique identifiers and populating deque with it
  for( j = 0; j < nmax; j++){    
    cache[j].id = j;
    id_queue.push_front(j);
  }
  
  return;
}

void cache_get(string key, string& url_body)
{
  cache_entry_t* e;
 
  //finding the particular URL in the map
  cache_hash_iter= cache_hash.find(key);

  //While calling this function, keep in mind that if it not found in cache, 
  //the url_body variable in caller would remain unchanged, set ""
  if(cache_hash_iter == cache_hash.end())
    return;

  //obtaining the cache entry structure from the map (for this URL)
  e = cache_hash_iter->second;

  switch (cache_policy)
  {
    //for LRU
	 case 0:
	   gettimeofday(&e->tv, NULL);
		 indexminpq_increasekey(&eviction_queue, e->id, &e->tv);
		 break;
	  //for MAXS, do nothing
	 case 1:
		 break;
   //for RANDOM, do nothing
	 case 2:
		 break;
  }
  //HTML content of the web page 
  url_body = e->value;  
}

int cache_set(string key, string const& value)
{
  size_t data_size = value.length(); //obtaining page size
  
  if (data_size > cache_capacity)
  {
    /* It's hopeless. */
    fprintf(stderr, "Value exceeds cache limit\n");
    return -1;
  }
  
  if(cache_policy==2)
  {   
	while(used_mem + data_size > cache_capacity)
    		deleteentry(&cache[indexrndq_dequeue(&rand_evict_queue)] );
  }
  else
  {
  	while(used_mem + data_size > cache_capacity)
    		deleteentry(&cache[indexminpq_delmin(&eviction_queue)]);
  }

  //check if enough identifiers are available
  if(id_queue.empty()){
    fprintf(stderr, "ran out of ids for cache entries!\n");
    return -1;
  }

  cache_entry_t* e;
  
  //setting fields in the cache entry structure
  e = &cache[id_queue.front()];
  id_queue.pop_front();
  e->key = key;
  e->value = value;
  e->val_size = data_size;
  used_mem += e->val_size;

  //inserting <URL,cache entry structure> in the map
  cache_hash.insert ( pair<string,cache_entry_t*>(e->key,e) );


  //inserting corresponding identifier and key in the eviction queue
  switch (cache_policy)
  {
  	//for LRU
	case 0:
		gettimeofday(&e->tv, NULL);
  		indexminpq_insert(&eviction_queue, e->id, &e->tv);
		break;
	//for MAXS
	case 1:
		e->val_size_complement = cache_capacity - e->val_size;
		indexminpq_insert(&eviction_queue, e->id, &e->val_size_complement);
		break;
	//for RANDOM
	case 2:
		indexrndq_enqueue(&rand_evict_queue, e->id);
		break;
		
  }
  return 0;
}

int cache_memused(){
  return used_mem;
}

//deleting structures
void cache_destroy()
{  
  id_queue.clear();
 
  indexminpq_destroy(&eviction_queue);

  indexrndq_destroy(&rand_evict_queue);
  
  delete[] cache;

  used_mem = 0;
  
  cache_hash.clear(); 
}

