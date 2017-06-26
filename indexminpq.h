#ifndef INDEXMINPQ_H
#define INDEXMINPQ_H

typedef void* indexminpq_key;

typedef struct{
  int NMAX;
  int N;
  int* pq;
  int* qp;
  indexminpq_key* keys;
  int (*keycmp)(indexminpq_key a, indexminpq_key b);
}indexminpq_t;

void indexminpq_init(indexminpq_t* current, int NMAX, int (*keycmp)(indexminpq_key a, indexminpq_key b));
void indexminpq_insert(indexminpq_t* current, int i, indexminpq_key key);
int indexminpq_contains(indexminpq_t* current, int i);
void indexminpq_increasekey(indexminpq_t *current, int i, indexminpq_key key);
void indexminpq_delete(indexminpq_t *current, int i);
int indexminpq_isempty(indexminpq_t* current);
void indexminpq_destroy(indexminpq_t* current);
indexminpq_key indexminpq_keyof(indexminpq_t* current, int i);
int indexminpq_minindex(indexminpq_t* current);
int indexminpq_delmin(indexminpq_t* current);

#endif
