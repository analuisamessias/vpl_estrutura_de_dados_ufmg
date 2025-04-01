#ifndef METODOS_H
#define METODOS_H
#include <time.h>

struct timespec inittp, endtp, restp;

typedef struct alg {
    int num;
    char * name;
} alg_t;

typedef struct opt {
    int size;
    int seed;
    int alg;
} opt_t;

typedef struct sortperf {
    int cmp;
    int move;
    int calls;
} sortperf_t;

int median (int a, int b, int c);
int median3(int *A, int l, int r, sortperf_t *s);
void insertionSort(int * vet, int l, int r, sortperf_t * s);
void selectionSort(int * vet, int l, int r, sortperf_t * s);
void quickSort(int * vet, int l, int r, sortperf_t * s);
void quickSort3(int * vet, int l, int r, sortperf_t * s);
void quickSortIns(int * vet, int l, int r, sortperf_t * s);
void quickSort3Ins(int * vet, int l, int r, sortperf_t * s);
void shellSort(int * vet, int n, sortperf_t * s);
void recursiveSelectionSort(int * arr, int l, int r, sortperf_t * s);
void resetcounter(sortperf_t * s);
void inccmp(sortperf_t * s, int num);
void incmove(sortperf_t * s, int num);
void inccalls(sortperf_t * s, int num);
char * printsortperf(sortperf_t * s, char * str, char * pref);
void initVector(int * vet, int size);
void printVector(int * vet, int size);
void swap(int *xp, int *yp, sortperf_t *s);
void partition3(int *A, int l, int r, int *i, int *j, sortperf_t *s);
void uso();
void parse_args(int argc, char ** argv, opt_t * opt);
void clkDiff(struct timespec t1, struct timespec t2, struct timespec * res);

#endif