#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "indexrndq.h"
#include <iostream>
#include <time.h>

using namespace std;

void indexrndq_init(indexrndq_t* current, int NMAX){
  int i;
  
  current->NMAX = NMAX;
  current->N = 0;
  current->pi = new int[NMAX];
  current->ip = new int[NMAX];

  for(i = 0; i < NMAX; i++)
    current->ip[i] = -1;
}

int indexrndq_isempty(indexrndq_t* current){
  return current->N == 0;
}

void indexrndq_enqueue(indexrndq_t* current, int i){
  if (i < 0 || i >= current->NMAX){
    fprintf(stderr, "Error: Argument to indexrndq_enqueue out of bounds\n");
    fflush(stderr);
    exit(EXIT_FAILURE);
  }
  
  if (indexrndq_contains(current, i)){
    fprintf(stderr, "Error: index %d is already in the indexrndq structure.", i);
    fflush(stderr);
    exit(EXIT_FAILURE);
  }

  current->ip[i] = current->N;
  current->pi[current->N] = i;
  current->N++;

  return;
}

int indexrndq_contains(indexrndq_t* current, int i){
  return current->ip[i] != -1;
}

void indexrndq_delete(indexrndq_t* current, int i){
   if (i < 0 || i >= current->NMAX){
    fprintf(stderr, "Error: Argument to indexrndq_contains out of bounds\n");
    fflush(stderr);
    exit(EXIT_FAILURE);
  }
  
  if (!indexrndq_contains(current, i)){
    fprintf(stderr, "Error: index %d is not in the indexrndq structure.", i);
    fflush(stderr);
    exit(EXIT_FAILURE);
  }
  
  current->N--;
  current->pi[current->ip[i]] = current->pi[current->N];
  current->ip[current->pi[current->N]] = current->ip[i];
  current->ip[i] = -1;
}

int indexrndq_dequeue(indexrndq_t* current){
  int ans, k;
  srand(time(NULL));
  /* Testing for underflow */
  if(current->N <= 0){
    fprintf(stderr, "Error: indexrndq underflow\n");
    fflush(stderr);
    exit(EXIT_FAILURE);
  }
  
  k = (int) (1.0 * current->N * rand() / (RAND_MAX + 1.0));
  ans = current->pi[k];
  //cout<<"Check this number: "<<ans<<endl;
  --current->N;

  current->pi[k] = current->pi[current->N];
  current->ip[current->pi[k]] = k;
  current->ip[ans] = -1;

  return ans;
}

void indexrndq_destroy(indexrndq_t* current){
  delete current->pi;
  delete current->ip;
}
