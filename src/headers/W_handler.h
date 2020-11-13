#ifndef W_HANDLER_H
#define W_HANDLER_H

/* Inserts json entries inside the buckets of the tree.
 * If the bucket is full it allocates memory from the heap to create a new one
 * and adds the entry inside the newly created bucket 
 */
void insert_entry(tree_entry *, bucket *);

/* Inserts into the tree nodes (buckets) the relations of each and every json file.
 * i.e. if they're equal or not equal files (based on the project's description) 
 */
void add_relation(tree_entry *, char*, char*, int);

/* Prints the relations of json files on each and every node of the tree. */
void print_node_relations(tree_entry *);

/* prints the relations of each and every of the files. 
 * (!!!) -- must be converted to output the relations to a .csv file.
 */
void print_all_relations(tree_entry *);

#endif /* W_HANDLER_H */