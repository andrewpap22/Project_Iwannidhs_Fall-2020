#include "../include/Logistic_Regr.hpp"

#include <bits/stdc++.h>
using namespace std;

int isempty(queuestruct* root){
    if (root->front == NULL && root->end == NULL)
    {
        return 1;
    }
    else{
        return 0;
    }
}
void enqueue(queuestruct* root, job *job){

    if (root->front == NULL && root->end == NULL){
    queue_node* a = (queue_node*)malloc(sizeof(queue_node));
        a->job = job;
        a->next = root->front;
        root->front = a; 
        root->end = a;   
    }
    else{
        queue_node* a = (queue_node*)malloc(sizeof(queue_node));
        a->job = job;
        a->next = root->front;
        root->front = a;
    } 
}
void dequeue(struct queuestruct* root){
    if (isempty(root) == 1)
    {
        return;
    }
    
    queue_node* a = root->front;
    if (a == root->end){
        free (a);
        root->front = NULL;
        root->end = NULL;
    return;
    }
    while (a->next != root->end){
        a = a->next;
    }
    // free(root->end->job);
    free(root->end);
    root->end = a;
    root->end->next = NULL;
}
void printqueue( queuestruct* root){
    if (isempty(root)==1){
      printf("queue empty cant print\n");
      return;        
    }
    queue_node* a = root->front;
    while (a!=NULL){   
      printf("JOB ID: %d\n",a->job->id);
       a = a->next;
    }
}

// int sort_isempty(sort_queuestruct* sortstruct){
//     if (sortstruct->front == NULL && sortstruct->end == NULL)
//     {
//         return 1;
//     }
//     else{
//         return 0;
//     }
// }
// void sort_enqueue(sort_queuestruct* sortstruct, sort_node data){
   
//     if (sortstruct->front == NULL && sortstruct->end == NULL){
//         data.next = sortstruct->front;
//         sortstruct->front = &data; 
//         sortstruct->end = &data;   
//     }
//     else{
//         data.next = sortstruct->front;
//         sortstruct->front = &data; 
//     } 
// }
// void sort_dequeue(struct sort_queuestruct* sortstruct){
//     if (sort_isempty(sortstruct) == 1)
//     {
//         return;
//     }
    
//     sort_node* a = sortstruct->front;
//     if (a == sortstruct->end){
//         free (a);
//         sortstruct->front = NULL;
//         sortstruct->end = NULL;
//     return;
//     }
//     while (a->next != sortstruct->end){
//         a = a->next;
//     }
//     free(sortstruct->end);
//     sortstruct->end = a;
//     sortstruct->end->next = NULL;
// }
// void sort_printqueue( sort_queuestruct* sortstruct){
//     if (sort_isempty(sortstruct)==1)
//     {
//     printf("queue empty cant print\n");
//     return;        
//     }
//     sort_node* a = sortstruct->front;
//     while (a!=NULL)
//     {   printf("Hist pos: %d\n",a->hist_pos);
//         a = a->next;
//     }
// }