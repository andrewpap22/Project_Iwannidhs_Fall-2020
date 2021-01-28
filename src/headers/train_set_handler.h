#ifndef TRAIN_SET_HANDLER_H
#define TRAIN_SET_HANDLER_H

#include <stdio.h>
#include <fcntl.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <dirent.h>
#include <errno.h>
#include <ctype.h>
#include <math.h> 
#include <time.h>
// #include <json-c/json.h>
#include "../headers/structs.h"

#define NUMOFSTOPWORDS 155
#define NUMOFENTRIES 29787
#define MAXWORDSIZE 7
#define WORDS_FOR_DATASET 100
// #define WORD_BUFFER 50

typedef struct bow_tree_entry{

  struct bow_tree_entry *left;
  struct bow_tree_entry *right;
  int ht;

  char *word; 
  int wordcounts[NUMOFENTRIES];

} bow_tree_entry;

void create_train_set_tfidf(float**, tree_entry*, char*, char*);
void create_train_set_bow(int**, tree_entry*, char*, char*);
int stopword_check(char*);
void add_json_keys(tree_entry*);
int* sort_idf_array();
int ** improve_bow(int**);
float ** improve_tf_idf(float**);
bow_tree_entry* create_bow_tree(tree_entry*);
bow_tree_entry* add_jsons_to_bow(bow_tree_entry*, tree_entry*);
bow_tree_entry* json_to_bow(bow_tree_entry*, tree_entry*);
bow_tree_entry* word_to_bow(bow_tree_entry*, char*, int);
int ** create_bow_array(tree_entry*);
void get_bow_tree_entries(bow_tree_entry*, int**);
float ** create_tf_idf(int**);

bow_tree_entry *bow_insert(bow_tree_entry *, int, char *);
bow_tree_entry *bow_search(bow_tree_entry *, char *);
int bow_height(bow_tree_entry *);
bow_tree_entry *bow_rotateright(bow_tree_entry *);
bow_tree_entry *bow_rotateleft(bow_tree_entry *);
bow_tree_entry *bow_RR(bow_tree_entry *);
bow_tree_entry *bow_LL(bow_tree_entry *);
bow_tree_entry *bow_LR(bow_tree_entry *);
bow_tree_entry *bow_RL(bow_tree_entry *);
int bow_BF(bow_tree_entry *);

#endif /* TRAIN_SET_HANDLER_H */