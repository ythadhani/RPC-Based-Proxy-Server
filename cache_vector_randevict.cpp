#include <stdlib.h>
#include <stdio.h>
#include <string>
#include <sys/time.h>
#include "cache.h"
#include "indexminpq.h"
#include <map>
#include <deque>
#include <vector>
#include <iostream>

using namespace std;


int cache_policy;
 
typedef struct{
  string key;  //URL
  string value;  //HTML content of page fetched via HTTP
  size_t val_size;
  int id;
  struct timeval tv;
  int frequency;
  size_t val_size_complement; //cache_capacity - val_size
} cache_entry_t;

map<string,cache_entry_t*> cache_hash;
map<string,cache_entry_t*>::iterator cache_hash_iter;
deque<int> id_queue;
vector<int> rand_vector;

static size_t min_size;
static size_t used_mem;
static size_t cache_capacity;

static cache_entry_t* cache;

static indexminpq_t eviction_queue;

int keycmp(indexminpq_key a, indexminpq_key b)
{
  switch (cache_policy)
  { 
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
  cache_hash.erase(e->key);
 
  id_queue.push_front(e->id);

}

static void delete_rand_entry(cache_entry_t* e, int index)
{
	used_mem -= e->val_size > min_size ? e->val_size : min_size;  

        cache_hash.erase(e->key);

	rand_vector.erase(rand_vector.begin()+index); //check this
 
        id_queue.push_front(e->id);
}

void cache_init(size_t capacity, size_t min_entry_size, const string& cache_pol){
  int j, nmax;
  //cout<<"Cache policy: "<<cache_policy<<endl;
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
  
  cache = new cache_entry_t[nmax];
 
  indexminpq_init(&eviction_queue, nmax, keycmp);  
    
  for( j = 0; j < nmax; j++){    
    cache[j].id = j;
    cache[j].frequency = 0;
    id_queue.push_front(j);
  }
  
  return;
}

void cache_get(string key, string& url_body)
{
  cache_entry_t* e;
 
  cache_hash_iter= cache_hash.find(key);

  //While calling this function, keep in mind that if it not found in cache, the url_body variable in caller would remain unchanged, set ""
  if(cache_hash_iter == cache_hash.end())
    return;

  e = cache_hash_iter->second;

  switch (cache_policy)
  {
	case 0:
		gettimeofday(&e->tv, NULL);
		indexminpq_increasekey(&eviction_queue, e->id, &e->tv);
		break;
	
	
	case 1:
		//indexminpq_increasekey(&eviction_queue, e->id, &e->val_size_complement);
		break;

	case 2:
		break;
  }
   
  url_body = e->value;  
}

int cache_set(string key, string const& value)
{
  size_t data_size = value.length();
  if (data_size > cache_capacity)
  {
    /* It's hopeless. */
    fprintf(stderr, "Value exceeds cache limit\n");
    return -1;
  }
  if(cache_policy==3)
  {
	int size,rand_index;
	srand(time(NULL));
	while(used_mem + data_size > cache_capacity)
	{
		size = rand_vector.size();
		rand_index = rand()%size;
		delete_rand_entry(&cache[rand_vector[rand_index]],rand_index);
	}
  }
  else
  {
  	while(used_mem + data_size > cache_capacity)
    		deleteentry(&cache[indexminpq_delmin(&eviction_queue)]);
  }
  if(id_queue.empty()){
    fprintf(stderr, "ran out of ids for cache entries!\n");
    return -1;
  }

  cache_entry_t* e;
  
  e = &cache[id_queue.front()];
  id_queue.pop_front();
  e->key = key;
  e->value = value;
  e->val_size = data_size;
  used_mem += e->val_size;

  cache_hash.insert ( pair<string,cache_entry_t*>(e->key,e) );
  
  switch (cache_policy)
  {
	case 0:
		gettimeofday(&e->tv, NULL);
  		indexminpq_insert(&eviction_queue, e->id, &e->tv);
		break;

	case 1:
		e->val_size_complement = cache_capacity - e->val_size;
		indexminpq_insert(&eviction_queue, e->id, &e->val_size_complement);
		break;
	
	case 2:
		rand_vector.push_back(e->id);
		break;
		
  }
  return 0;
}

int cache_memused(){
  return used_mem;
}

void cache_destroy()
{  
  id_queue.clear();
 
  indexminpq_destroy(&eviction_queue);
  
  delete[] cache;

  used_mem = 0;
  
  rand_vector.clear();

  cache_hash.clear(); 
}
