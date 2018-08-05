//standard library inclusion
#include<stdio.h>
#include<ctype.h>
#include <time.h>
#include <limits.h>
#include <math.h>
#include <stdlib.h>

#define MAX_VALUE 9999

#define MAX_LIMIT 10
#define MIN_LIMIT 1
#define MAX_VERTEX 10
#define MIN_VERTEX 5

//global variable declaration
int num_of_vertices = 0;

//function declaration
int prim_algorithm(int **g_matrix);

int print_path(int index_q, int index_r, int **p_matrix);

int make_queue(int *queue);

int get_min_node(char *chk_non_tree_node, int *queue, int *cost);

typedef struct edge_wt_str {
    int wt;
    int edge_src;
    int edge_dest;
} edge_wt_typ;

edge_wt_typ *edge_wt;

int kruskal_algorithm(int **g_matrix);

int find3(int node, int *set);

int union_node3(int rep_node1, int rep_node2, int *height_matrix, int *set);