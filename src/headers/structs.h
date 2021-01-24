#ifndef STRUCTS_H
#define STRUCTS_H

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
//#include <json-c/json.h>

#define BUCKETSIZE 200

typedef struct headBucket
{
  char* key;
  struct clique_tree_entry* different_cliques_root;
  struct bucket *first_bucket;

} headBucket;

typedef struct bucket
{
  struct bucket *next_bucket;
  int numofentries;
  struct tree_entry *identical_entries[BUCKETSIZE];

} bucket;

typedef struct tree_entry
{

  struct tree_entry *left;
  struct tree_entry *right;
  int ht;

  int json;
  char *path_with_JSON; //www.ebay.com//[spec_number]
  char *specs;

  struct headBucket *headbucket;

} tree_entry;

typedef struct clique_tree_entry
{
  struct clique_tree_entry *left;
  struct clique_tree_entry *right;
  int ht;

  struct headBucket *different_clique_headbucket;

} clique_tree_entry;

/* Basic Binary Search tree operatons for our project. */
int compare(char *, char *);

tree_entry *insert(tree_entry *, int, char *, char *);
tree_entry *search(tree_entry *, char *);
int height(tree_entry *);
tree_entry *rotateright(tree_entry *);
tree_entry *rotateleft(tree_entry *);
tree_entry *RR(tree_entry *);
tree_entry *LL(tree_entry *);
tree_entry *LR(tree_entry *);
tree_entry *RL(tree_entry *);
int BF(tree_entry *);

clique_tree_entry *clique_tree_insert(clique_tree_entry*, headBucket*);
clique_tree_entry *clique_tree_search(clique_tree_entry *, char *);
int clique_tree_height(clique_tree_entry *);
clique_tree_entry *clique_tree_rotateright(clique_tree_entry *);
clique_tree_entry *clique_tree_rotateleft(clique_tree_entry *);
clique_tree_entry *clique_tree_RR(clique_tree_entry *);
clique_tree_entry *clique_tree_LL(clique_tree_entry *);
clique_tree_entry *clique_tree_LR(clique_tree_entry *);
clique_tree_entry *clique_tree_RL(clique_tree_entry *);
int clique_tree_BF(clique_tree_entry *);

void free_list_of_buckets(bucket*);
void free_node(tree_entry *);
// tree_entry *Delete(tree_entry *,int);
// void preorder(tree_entry *);
// void inorder(tree_entry *);


/* for ubuntu: sudo apt install libjson-c-dev
 * to use the json-c library 
 * we need to compile with: -ljson-c
 * 
 * Reads and opens each and every json file from each (sub)directory of the dataset directory.
 *  
 * References: 
 * https://alan-mushi.github.io/2014/10/28/json-c-tutorial-part-1.html
 * https://stackoverflow.com/questions/4085372/how-to-return-a-string-array-from-a-function/11543552
 * https://json-c.github.io/json-c/json-c-0.10/doc/html/json__object_8h.html#a84421dab94ccad42e901e534c6d7b658
 */
char* read_json(char *);

#endif /* STRUCTS_H */
