#ifndef QUEUE_H
#define QUEUE_H

#include <bits/stdc++.h>
#include "Logistic_Regr.hpp"

using namespace std;

#define nl '\n'

typedef struct queue_node
{
    struct job *job;
    struct queue_node  *next;
}queue_node;

typedef struct queuestruct{
struct queue_node *front;
struct queue_node *end;
}queuestruct;

void printqueue(struct queuestruct *root);
void enqueue(struct queuestruct *root, struct job* j);
void dequeue(struct queuestruct *root);
int isempty(struct queuestruct* root);

// //sort stuff
// typedef struct sort_node
// {
//     struct unsorted_record *unsortedtable;
//     struct histogram *hist;
//     struct sort_node  *next;
//     int hist_pos;
// }sort_node;

// typedef struct sort_queuestruct{
// int numofrecords;
// int byte;
// pthread_mutex_t *sort_dequeue_mutex;
// struct sort_node *front;
// struct sort_node *end;
// }sort_queuestruct;

int sort_isempty(struct sort_queuestruct* sortstruct);
// void sort_enqueue(struct sort_queuestruct* sortstruct, sort_node data);
void sort_dequeue(struct sort_queuestruct* sortstruct);
void sort_printqueue(struct sort_queuestruct* sortstruct);





#endif /* QUEUE_REGR_H */