//adapted from Dominic Battre's implementation of the Hungarian algorithm by hbc@mit.edu

#ifndef ASP_H
#define ASP_H

typedef double cost;
#define COST_TYPE tFloat64
#define COST_TYPE_NPY NPY_DOUBLE

#define INF 100000

void asp(int size, cost **Array, long *col_mate, long *row_mate);

#endif
