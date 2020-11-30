#include "../headers/structs.h"
#include "../headers/W_handler.h"
int sum = 0;

void insert_entry(tree_entry *entry, bucket *first_bucket)
{

	bucket *current_bucket = first_bucket;
	//Find last bucket
	while (current_bucket->next_bucket != NULL)
	{
		current_bucket = current_bucket->next_bucket;
	}
	//If it's full make a new one and add entry
	if (current_bucket->numofentries == BUCKETSIZE)
	{
		bucket *new_bucket = malloc(sizeof(bucket));
		new_bucket->next_bucket = NULL;
		new_bucket->identical_entries[0] = entry;
		new_bucket->numofentries = 1;
		current_bucket->next_bucket = new_bucket;
	}
	//Otherwise just add entry
	else
	{
		current_bucket->identical_entries[current_bucket->numofentries] = entry;
		current_bucket->numofentries += 1;
	}
}

void add_positive_relation(tree_entry *root, char *json1, char *json2, int relation){
	if (relation == 1)
	{
		//if the jsons are already in the same group return

		//find the jsons in the tree
		tree_entry *entry1 = search(root, json1);
		tree_entry *entry2 = search(root, json2);
		//return if the clique already exists
		if (entry1->headbucket == entry2->headbucket)
		{
			return;
		}
		bucket *current_bucket_2 = entry2->headbucket->first_bucket;
		bucket *prev_bucket_2 = entry2->headbucket->first_bucket;
		bucket *current_bucket_1 = entry1->headbucket->first_bucket;

		int json2_numofbuckets = 0;

		//find the last and the second last buckets of json2
		while (current_bucket_2->next_bucket != NULL)
		{
			prev_bucket_2 = current_bucket_2;
			current_bucket_2 = current_bucket_2->next_bucket;
			json2_numofbuckets++;
		}
		//Find last bucket of json1 (where the entries will go)
		while (current_bucket_1->next_bucket != NULL)
		{
			current_bucket_1 = current_bucket_1->next_bucket;
		}
		//add the last bucket entries of json2 bucketlist to json1 bucketlist
		for (int i = 0; i < current_bucket_2->numofentries; i++)
		{
			insert_entry(current_bucket_2->identical_entries[i], current_bucket_1);
		}
		//if there are json2 buckets left add them to the front of json1 bucketlist..
		if (json2_numofbuckets > 1)
		{
			prev_bucket_2->next_bucket = entry1->headbucket->first_bucket;
			//..and change every node pointer to point to head of json 2
			current_bucket_2 = entry2->headbucket->first_bucket;
			while (current_bucket_2)
			{
				for (int i = 0; i < current_bucket_2->numofentries; i++)
				{
					current_bucket_2->identical_entries[i]->headbucket = entry2->headbucket;
				}
				current_bucket_2 = current_bucket_2->next_bucket;
			}
		}
		//if not change every pointer to point to head of json1
		else
		{
			current_bucket_1 = entry2->headbucket->first_bucket;
			while (current_bucket_1)
			{
				for (int i = 0; i < current_bucket_1->numofentries; i++)
				{
					current_bucket_1->identical_entries[i]->headbucket = entry1->headbucket;
				}
				current_bucket_1 = current_bucket_1->next_bucket;
			}
		}
	}
	return;
}

void add_negative_relation(tree_entry *root, char *json1, char *json2, int relation){
	if (relation == 0){
		tree_entry *entry1 = search(root, json1);
		tree_entry *entry2 = search(root, json2);
		if (entry1!=NULL && entry2!=NULL){
			
			clique_tree_entry *negative_relation_entry = clique_tree_search(entry1->headbucket->different_cliques_root, entry2->headbucket->key);
			if (negative_relation_entry==NULL){
				entry1->headbucket->different_cliques_root = clique_tree_insert(entry1->headbucket->different_cliques_root, entry2->headbucket);
				// printf("%s\n",entry1->path_with_JSON);
				entry2->headbucket->different_cliques_root = clique_tree_insert(entry2->headbucket->different_cliques_root, entry1->headbucket);
			}
		}
	}	
}

void print_node_positive_relations(tree_entry *node, FILE* fp2){
	bucket *iterator = node->headbucket->first_bucket;
	while (iterator){
		for (int i = 0; i < iterator->numofentries; i++){
			if (compare(node->path_with_JSON, iterator->identical_entries[i]->path_with_JSON) == 0){
				fprintf(fp2,"%s, %s, 1\n",node->path_with_JSON, iterator->identical_entries[i]->path_with_JSON);				
			}
		}
		iterator = iterator->next_bucket;
	}
}

void print_all_positive_relations(tree_entry *root, FILE* fp2){
	if (root)
	{
		print_node_positive_relations(root, fp2);
		print_all_positive_relations(root->right, fp2);
		print_all_positive_relations(root->left, fp2);
	}
}



void print_node_negative_relations(tree_entry *node, clique_tree_entry* neg_root, FILE* fp2){
	if (neg_root){
		bucket *iterator = neg_root->different_clique_headbucket->first_bucket;
		while (iterator){
			for (int i = 0; i < iterator->numofentries; i++){
				if (compare(node->path_with_JSON, iterator->identical_entries[i]->path_with_JSON) == 0){
					fprintf(fp2,"%s, %s, 0\n",node->path_with_JSON, iterator->identical_entries[i]->path_with_JSON);	
					// sum++;
				}
			}
			iterator = iterator->next_bucket;
		}
		// printf("sum: %d\n",sum);			
		print_node_negative_relations(node, neg_root->right, fp2);
		print_node_negative_relations(node, neg_root->left, fp2);
	}
}

void print_all_negative_relations(tree_entry *root, FILE* fp2){
	if (root){
		print_node_negative_relations(root, root->headbucket->different_cliques_root, fp2);
		print_all_negative_relations(root->right, fp2);
		print_all_negative_relations(root->left, fp2);
	}
}