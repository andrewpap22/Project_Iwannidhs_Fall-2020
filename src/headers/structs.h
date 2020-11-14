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
#include <json-c/json.h>

#define BUCKETSIZE 200

/* no need for that struct anymore */
// typedef struct specs
// {

//   char *page_title;
//   char *brand;
//   char *dimension;
//   char *display;
//   char *pixels;
//   char *battery;
// } specs;

typedef struct headBucket
{

  struct bucket *first_bucket;
  struct specs *product_specs;
  // int count_identicals;

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
  struct headBucket *headbucket;

} tree_entry;


/* Basic Binary Search tree operatons for our project. */
int compare(char*, char*);
tree_entry *insert(tree_entry *, int, char *);
tree_entry *search(tree_entry *, char *);
// tree_entry *Delete(tree_entry *,int);
void preorder(tree_entry *);
void inorder(tree_entry *);
int height(tree_entry *);
tree_entry *rotateright(tree_entry *);
tree_entry *rotateleft(tree_entry *);
tree_entry *RR(tree_entry *);
tree_entry *LL(tree_entry *);
tree_entry *LR(tree_entry *);
tree_entry *RL(tree_entry *);
int BF(tree_entry *);

/* for ubuntu: sudo apt install libjson-c-dev
 * to use the json-c library 
 * we need to compile with: -ljson-c
 * 
 * Reads and opens each and every json file from each (sub)directory of the dataset directory.
 */
char** read_json(char *);

void printoutarray(char **);

#endif /* STRUCTS_H */
