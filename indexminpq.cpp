#include<iostream>
#include <stdio.h>
#include<stdlib.h>
#include "indexminpq.h"

using namespace std;

static void exch(indexminpq_t* current, int i, int j){
  int swap;
  swap = current->pq[i]; 
  current->pq[i] = current->pq[j]; 
  current->pq[j] = swap;
  
  current->qp[current->pq[i]] = i; 
  current->qp[current->pq[j]] = j;
}

static int larger(indexminpq_t* current, int i, int j)
{
  return current->keycmp(current->keys[current->pq[i]],current->keys[current->pq[j]]) > 0;
}

static void sink(indexminpq_t* current, int k) 
{
  int j;
  while (2*k <= current->N) 
  {
    j = 2*k;
    if (j < current->N && larger(current, j, j+1)) j++;
    if (!larger(current, k, j)) break;
    exch(current, k, j);
    k = j;
  }
}

static void swim(indexminpq_t* current, int k)  
{
  while (k > 1 && larger(current, k/2, k)) 
  {
    exch(current, k, k/2);
    k = k/2;
  }
}

void indexminpq_init(indexminpq_t* current, int NMAX, int (*keycmp)(indexminpq_key a, indexminpq_key b))
{
  int i;

  current->NMAX = NMAX;
  current->N = 0;
  current->pq = new int[NMAX + 1];
  current->qp = new int[NMAX + 1];
  current->keys = new indexminpq_key[NMAX + 1];
  current->keycmp = keycmp;

  for(i = 0; i <= NMAX; i++)
    current->qp[i] = -1;

}

void indexminpq_insert(indexminpq_t* current, int i, indexminpq_key key) {
  if (i < 0 || i >= current->NMAX){
    fprintf(stderr, "Error: Argument to indexminpq_contains out of bounds\n");
    fflush(stderr);
    exit(EXIT_FAILURE);
  }
  
  if (indexminpq_contains(current, i)){
    fprintf(stderr, "Error: index %d is already in the indexminpq structure.", i);
    fflush(stderr);
    exit(EXIT_FAILURE);
  }
   
   current->N++;
   current->qp[i] = current->N;
   current->pq[current->N] = i;
   current->keys[i] = key;
   swim(current, current->N);
}

int indexminpq_contains(indexminpq_t* current, int i) {
  if (i < 0 || i >= current->NMAX){
    fprintf(stderr, "Error: Argument to indexminpq_contains out of bounds\n");
    fflush(stderr);
    exit(EXIT_FAILURE);
  }
  return current->qp[i] != -1;
}

int indexminpq_delmin(indexminpq_t* current) 
{ 
  int min;
  
  if(current->N == 0)
  {
    fprintf(stderr, "Error: underflow in indexminpq_delmin.");
    fflush(stderr);
    exit(EXIT_FAILURE);
  }
  
  min = current->pq[1]; 
  exch(current, 1, current->N); 
  current->N--;
  sink(current, 1);
  current->qp[min] = -1;  /* marking as deleted */
  return min; 
}

void indexminpq_increasekey(indexminpq_t *current, int i, indexminpq_key key) {
  if (i < 0 || i >= current->NMAX){
    fprintf(stderr, "Error: Argument to indexminpq_increasekey out of bounds\n");
    fflush(stderr);
    exit(EXIT_FAILURE);
  }

  if (!indexminpq_contains(current, i)){
    fprintf(stderr,
	    "Invalid argument to indexminpq_increasekey: index %d is not in the priority queue\n", i);
    fflush(stderr);
    exit(EXIT_FAILURE);  
  }
  
  if (current->keycmp(current->keys[i], key) > 0){
    fprintf(stderr,"Error: indexminpq_increasekey called with decreasing key\n");
    fflush(stderr);
    exit(EXIT_FAILURE);
  }

  current->keys[i] = key;
  sink(current, current->qp[i]);
}

void indexminpq_delete(indexminpq_t *current, int i) {
  int index;
  
  if (i < 0 || i >= current->NMAX){
    fprintf(stderr, "Error: Argument to indexminpq_increasekey out of bounds\n");
    fflush(stderr);
    exit(EXIT_FAILURE);
  }
  
  if (!indexminpq_contains(current, i)){
    fprintf(stderr,"Error: Invalid argument to indexminpq_delete: index %d is not in the priority queue", i);
    fflush(stderr);
    exit(EXIT_FAILURE);  
  }

  index = current->qp[i];
  exch(current, index, current->N);
  current->N--;
  swim(current, index);
  sink(current, index);
  current->qp[i] = -1;
}

void indexminpq_destroy(indexminpq_t* current){
  delete current->pq;
  delete current->qp;
  delete current->keys;
}

int indexminpq_isempty(indexminpq_t* current){ 
  return current->N == 0; 
}

indexminpq_key indexminpq_keyof(indexminpq_t* current, int i) {
  if (i < 0 || i >= current->NMAX){
    fprintf(stderr, "Error: Argument to indexminpq_keyof out of bounds\n");
    fflush(stderr);
    exit(EXIT_FAILURE);
  }

  if (!indexminpq_contains(current, i)){
    fprintf(stderr, 
	    "Invalid argument to indexminpq_keyof: index %d is not in the priority queue", i);
    fflush(stderr);exit(EXIT_FAILURE);
  }
  return current->keys[i];
}

int indexminpq_minindex(indexminpq_t* current) { 
  if (current->N == 0){
    fprintf(stderr, "Error: underflow in indexminpq_minindex.");
    fflush(stderr);
    exit(EXIT_FAILURE);
  }
  return current->pq[1];        
}
