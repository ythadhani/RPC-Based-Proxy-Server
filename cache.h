#ifndef CACHE_H
#define CACHE_H

#include<string>
using namespace std;

/*
 * The cache_init procedure initializes data structures needed for
 * the cache.  Call this procedure before any others.  
 *
 * The parameter capacity controls the capacity of the cache.  That
 * is, the sum of the sizes of the entries should be no larger than
 * capacity.  
 *
 * The parameter min_entry_size controls how many entries the cache
 * will expect--i.e. capacity/min_entry_size.  An eviction may occur
 * even when all entries would otherwise fit if there are this many
 * entries in the cache.
 *
 * The parameter num_levels is only relevent for the lrumin
 * replacment.
 */
void cache_init(size_t capacity, size_t min_entry_size, const string& cache_pol);

/*
 * The cache_set procedure associates the first val_size bytes after
 * the pointer value with the key.  A defensive copy of the data is made.
 */
int cache_set(string key, string const& value);

/*
 * The cache_get procedure returns a copy of the data associated
 * with the key.  If the parameter val_size is NULL, it is ignored.
 * Otherwise, the length of the data array is stored in it.
 */

void cache_get(string key, string& url_body);

/* 
 * The cache_memused procedure returns the sum of the sizes of the
 * entries in the cache.  This amount should never exceed capacity.
 */
int cache_memused();

/*
 * The cache_destroy procedure cleans up the memory created for the
 * cache.  The procedure cache_init must be called before the cache
 * can be used again.
 */
void cache_destroy();

#endif
