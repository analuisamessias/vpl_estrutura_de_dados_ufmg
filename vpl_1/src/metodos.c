#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <unistd.h>
#include <time.h>

#define ALGINSERTION 1
#define ALGSELECTION 2
#define ALGQSORT     3
#define ALGQSORT3    4
#define ALGQSORTINS  5
#define ALGQSORT3INS 6
#define ALGSHELLSORT 7
#define ALGRECSEL    8

alg_t algvet[]={
  {ALGINSERTION,"i"},
  {ALGSELECTION,"s"},
  {ALGQSORT,"q"},
  {ALGQSORT3,"q3"},
  {ALGQSORTINS,"qi"},
  {ALGQSORT3INS,"q3i"},
  {ALGSHELLSORT,"h"},
  {ALGRECSEL,"rs"},
  {0,0}
};

int name2num(char * name){
  int i=0;
  while (algvet[i].num){
    if (!strcmp(algvet[i].name,name)) return algvet[i].num;
    i++;
  }
  return 0;
}

char * num2name(int num){
  int i=0;
  while (algvet[i].num){
    if (algvet[i].num==num) return algvet[i].name;
    i++;
  }
  return 0;
}

void resetcounter(sortperf_t * s){
// Descricao: inicializa estrutura
// Entrada: 
// Saida: s
  s->cmp = 0;
  s->move = 0;
  s->calls = 0;
}

void inccmp(sortperf_t * s, int num){
// Descricao: incrementa o numero de comparacoes em num 
// Entrada: s, num
// Saida: s
  s->cmp += num;
}

void incmove(sortperf_t * s, int num){
// Descricao: incrementa o numero de movimentacoes de dados em num 
// Entrada: s, num
// Saida: s
  s->move += num;
}

void inccalls(sortperf_t * s, int num){
// Descricao: incrementa o numero de chamadas de função em num 
// Entrada: s, num
// Saida: s
  s->calls += num;
}

char * printsortperf(sortperf_t * s, char * str, char * pref){
// Descricao: gera string com valores de sortperf 
// Entrada: s, pref
// Saida: str

 sprintf(str,"%s cmp %d move %d calls %d", pref, s->cmp, s->move, s->calls); 
 return str;
}


void initVector(int * vet, int size){
// Descricao: inicializa vet com valores aleatorios
// Entrada: vet
// Saida: vet
  int i;
  // inicializa a parte alocada da vetor com valores aleatorios
  for (i=0; i<size; i++){
    vet[i] = (int)(drand48()*size);
  }
}

void printVector(int * vet, int size){
// Descricao: inicializa vet com valores aleatorios
// Entrada: vet
// Saida: vet
  int i;
  for (i=0; i<size; i++){
    printf("%d ",vet[i]);
  }
  printf("\n");
}

void swap(int *xp, int *yp, sortperf_t *s){
    int temp = *xp;
    *xp = *yp;
    *yp = temp;
    incmove(s,3);
}

// shellsort
void shellSort(int *A, int n, sortperf_t *s) {
    int intervalo, i, j, temp;
    for (intervalo = n / 2; intervalo > 0; intervalo /= 2) {
        for (i = intervalo; i < n; i++) {
            temp = A[i];
            for (j = i; j >= intervalo; j -= intervalo) {
                if (temp < A[j - intervalo]) {
                    A[j] = A[j - intervalo];
                    incmove(s, 1); // Incrementa o número de movimentos
                } else {
                    break;
                }
            }
            A[j] = temp;
        }
    }
}


// recursive selection sort
void recursiveSelectionSort(int arr[], int l, int r, sortperf_t * s)
{
    // find the minimum element in the unsorted subarray `[i…n-1]`
    // and swap it with `arr[i]`
    int min = l;
    inccalls(s,1);
    for (int j = l + 1; j <= r; j++)
    {
        // if `arr[j]` is less, then it is the new minimum
	inccmp(s,1);
        if (arr[j] < arr[min]) {
            min = j;    // update the index of minimum element
        }
    }

    // swap the minimum element in subarray `arr[i…n-1]` with `arr[i]`
    if (min!=l)
      swap(&arr[min], &arr[l], s);

    if (l + 1 < r) {
        recursiveSelectionSort(arr, l + 1, r, s);
    }
}

// selection sort
void selectionSort(int arr[], int l, int r, sortperf_t *s) {
    int i, j, min_idx;
    for (i = l; i < r; i++) {
        min_idx = i;
        for (j = i + 1; j <= r; j++) {
            if (arr[j] < arr[min_idx]) {
                min_idx = j;
            }
            inccmp(s, 1); // Incrementa o número de comparações
        }
        if (min_idx != i) {
            swap(&arr[min_idx], &arr[i], s);
        }
    }
}

//insertion sort
void insertionSort(int * vet, int l, int r, sortperf_t * s) {
    for (int i = l + 1; i <= r; i++) {
        int key = vet[i];
        int j = i - 1;

        while (j >= l && vet[j] > key) {
            vet[j + 1] = vet[j];
            j--;
            incmove(s, 1); 
            inccmp(s, 1);  
        }
        vet[j + 1] = key;
    }
}

// median of 3 integers
int median (int a, int b, int c) {
    if ((a <= b) && (b <= c)) return b;  // a b c
    if ((a <= c) && (c <= b)) return c;  // a c b
    if ((b <= a) && (a <= c)) return a;  // b a c
    if ((b <= c) && (c <= a)) return c;  // b c a
    if ((c <= a) && (a <= b)) return a;  // c a b
    return b;                            // c b a
}

// quicksort partition using median of 3
void partition3(int *A, int l, int r, int *i, int *j, sortperf_t *s) {
    int mid = l + (r - l) / 2;
    int pivot = median(A[l], A[mid], A[r]);
    *i = l - 1;
    *j = r + 1;

    while (1) {
        do {
            (*i)++;
            inccmp(s, 1); 
        } while (A[*i] < pivot); 
        do {
            (*j)--;
            inccmp(s, 1); 
        } while (A[*j] > pivot); 
        if (*i >= *j) {
            return;
        }
        swap(&A[*i], &A[*j], s);
    }
}

// standard quicksort partition
void partition(int *A, int l, int r, int *i, int *j, sortperf_t *s) {
    int pivot = A[r];
    *i = l - 1;
    *j = r + 1;

    while (1) {
        do {
            (*i)++;
            inccmp(s, 1); 
        } while (A[*i] < pivot); 
        do {
            (*j)--;
            inccmp(s, 1); 
        } while (A[*j] > pivot); 
        if (*i >= *j) {
            return;
        }
        swap(&A[*i], &A[*j], s);
    }
}

// standard quicksort
void quickSort(int *A, int l, int r, sortperf_t *s) {
    if (l < r) {
        int i, j;
        partition(A, l, r, &i, &j, s); 

        quickSort(A, l, j, s); //Ordena a parte esquerda
        quickSort(A, j + 1, r, s);  //Ordena a parte direita
    }
}

// quicksort with median of 3
// Median of 3
int median3(int *A, int l, int r, sortperf_t *s) {
    int mid = l + (r - l) / 2;
    if (A[l] > A[mid]) {
        swap(&A[l], &A[mid], s);
    }
    if (A[l] > A[r]) {
        swap(&A[l], &A[r], s);
    }
    if (A[mid] > A[r]) {
        swap(&A[mid], &A[r], s);
    }
    return A[mid];
}

// Partition of median 3
void partition3(int *A, int l, int r, int *i, int *j, sortperf_t *s) {
    int pivot = median3(A, l, r, s); // Encontra a mediana de 3
    *i = l - 1;
    *j = r + 1;
    while (1) {
        do {
            (*i)++;
        } while (A[*i] < pivot); // Encontra o primeiro elemento maior que o pivô
        do {
            (*j)--;
        } while (A[*j] > pivot); // Encontra o primeiro elemento menor que o pivô
        if (*i >= *j) return; 
        swap(&A[*i], &A[*j], s); 
    }
}

// quicksort with median of 3
void quickSort3(int *A, int l, int r, sortperf_t *s) {
    if (l < r) {
        int i, j;
        partition3(A, l, r, &i, &j, s); // Particiona o array
        quickSort3(A, l, j, s); // Ordena a parte à esquerda do pivô
        quickSort3(A, j + 1, r, s); // Ordena a parte à direita do pivô
    }
}

// quicksort with insertion for small partitions
void quickSortIns(int *A, int l, int r, sortperf_t *s) {
    // Utiliza o insertion sort
    if (r - l <= 10) {
        insertionSort(A, l, r, s);
        return;
    }
    
    if (l < r) {
        int i, j;
        partition(A, l, r, &i, &j, s); // Particiona o array
        quickSortIns(A, l, j, s); // Ordena a parte à esquerda do pivô
        quickSortIns(A, j + 1, r, s); // Ordena a parte à direita do pivô
    }
}

// quicksort with insertion for small partitions and median of 3
void quickSort3Ins(int *A, int l, int r, sortperf_t *s) {
    // Utiliza o insertion sort 
    if (r - l <= 10) {
        insertionSort(A, l, r, s);
        return;
    }

    if (l < r) {
        int i, j;
        partition3(A, l, r, &i, &j, s); // Particiona o array usando a mediana de 3
        quickSort3Ins(A, l, j, s); // Ordena a parte à esquerda do pivô
        quickSort3Ins(A, j + 1, r, s); // Ordena a parte à direita do pivô
    }
}

void uso()
// Descricao: imprime as opcoes de uso
// Entrada: nao tem
// Saida: impressao das opcoes de linha de comando
{
  fprintf(stderr,"sortperf\n");
  fprintf(stderr,"\t-z <int>\t(vector size)\n");
  fprintf(stderr,"\t-s <int>\t(initialization seed)\n");
  fprintf(stderr,"\t-a <s|i|q|q3|qi|q3i|h|rs>\t(algorithm)\n");
  fprintf(stderr,"\t    s\tselection\n");
  fprintf(stderr,"\t    i\tinsertion\n");
  fprintf(stderr,"\t    q\tquicksort\n");
  fprintf(stderr,"\t    q3\tquicksort+median3\n");
  fprintf(stderr,"\t    qi\tquicksort+insertion\n");
  fprintf(stderr,"\t    q3i\tquicksort+median3+insertion\n");
  fprintf(stderr,"\t    h\theapsort\n");
  fprintf(stderr,"\t    rs\trecursive selection\n");
}

void parse_args(int argc, char ** argv, opt_t * opt)
// Descricao: le as opcoes da linha de comando e inicializa variaveis
// Entrada: argc, argv, opt
// Saida: opt
{
     // variaveis externas do getopt
     extern char * optarg;
     extern int optind;

     // variavel auxiliar
     int c;

     // inicializacao variaveis globais para opcoes
     opt->seed = 1;
     opt->size = 10;
     opt->alg = 1;

     // getopt - letra indica a opcao, : junto a letra indica parametro
     // no caso de escolher mais de uma operacao, vale a ultima
     while ((c = getopt(argc, argv, "z:s:a:h")) != EOF){
       switch(c) {
         case 'z':
	          opt->size = atoi(optarg);
                  break;
         case 's':
	          opt->seed = atoi(optarg);
                  break;
         case 'a':
		  opt->alg = name2num(optarg);
                  break;
         case 'h':
         default:
                  uso();
                  exit(1);

       }
     }
     if (!opt->alg) {
       uso();
       exit(1);
     }
}

void clkDiff(struct timespec t1, struct timespec t2,
                   struct timespec * res)
// Descricao: calcula a diferenca entre t2 e t1, que e armazenada em res
// Entrada: t1, t2
// Saida: res
{
  if (t2.tv_nsec < t1.tv_nsec){
    // ajuste necessario, utilizando um segundo de tv_sec
    res-> tv_nsec = 1000000000+t2.tv_nsec-t1.tv_nsec;
    res-> tv_sec = t2.tv_sec-t1.tv_sec-1;
  } else {
    // nao e necessario ajuste
    res-> tv_nsec = t2.tv_nsec-t1.tv_nsec;
    res-> tv_sec = t2.tv_sec-t1.tv_sec;
  }
}