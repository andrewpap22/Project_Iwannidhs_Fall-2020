#include "../headers/structs.h"
#include "../headers/W_handler.h"
	int sum =0;

void insert_entry(tree_entry *entry, bucket* first_bucket){

	bucket* current_bucket = first_bucket;
	//Find last bucket
	while (current_bucket->next_bucket!=NULL){
		current_bucket = current_bucket->next_bucket;
	}
	//If it's full make a new one and add entry
	if (current_bucket->numofentries == BUCKETSIZE){
		bucket* new_bucket = malloc(sizeof(bucket));
		new_bucket->next_bucket = NULL;	
		new_bucket->identical_entries[0] = entry;
		new_bucket->numofentries = 1;
		current_bucket->next_bucket = new_bucket;
	}
	//Otherwise just add entry
	else{
		current_bucket->identical_entries[current_bucket->numofentries] = entry;
		current_bucket->numofentries += 1;
	}
}	
	
// }
void add_relation(tree_entry* root, char* json1, char* json2, int relation){
	if(relation==1){
		//if the jsons are already in the same group return

		//find the jsons in the tree
		tree_entry* entry1 = search(root, json1);
		tree_entry* entry2 = search(root, json2);
		//return if the clique already exists
		if (entry1->headbucket == entry2->headbucket){
			return;
		}
		bucket* current_bucket_2 = entry2->headbucket->first_bucket;
		bucket* prev_bucket_2 = entry2->headbucket->first_bucket;
		bucket* current_bucket_1 = entry1->headbucket->first_bucket;
	
		int json2_numofbuckets = 0;

		//find the last and the second last buckets of json2
		while (current_bucket_2->next_bucket != NULL){
			prev_bucket_2 = current_bucket_2;
			current_bucket_2 = current_bucket_2->next_bucket;
			json2_numofbuckets++;
		}
		//Find last bucket of json1 (where the entries will go)
		while (current_bucket_1->next_bucket!=NULL){
			current_bucket_1 = current_bucket_1->next_bucket;
		}
		//add the last bucket entries of json2 bucketlist to json1 bucketlist
		for (int i = 0; i < current_bucket_2->numofentries; i++){
			insert_entry(current_bucket_2->identical_entries[i], current_bucket_1);
		}
		//if there are json2 buckets left add them to the front of json1 bucketlist..
		if (json2_numofbuckets > 1){
			prev_bucket_2->next_bucket = entry1->headbucket->first_bucket;
		//..and change every node pointer to point to head of json 2
			current_bucket_2 = entry2->headbucket->first_bucket;
			while (current_bucket_2){
				for (int i = 0; i < current_bucket_2->numofentries; i++){
					current_bucket_2->identical_entries[i]->headbucket = entry2->headbucket;
				}
				current_bucket_2 = current_bucket_2->next_bucket;
			}
		}
		//if not change every pointer to point to head of json1
		else{
			current_bucket_1 = entry2->headbucket->first_bucket;
			while (current_bucket_1){
				for (int i = 0; i < current_bucket_1->numofentries; i++){
					current_bucket_1->identical_entries[i]->headbucket = entry1->headbucket;
				}
				current_bucket_1 = current_bucket_1->next_bucket;
			}
		}
	}
	return;
}

void print_node_relations(tree_entry* node){
	bucket* iterator = node->headbucket->first_bucket;
	// int sum =0;
	// int i = 0;
	while(iterator){
		
		for (int i = 0; i < iterator->numofentries; i++){
			if (compare(node->path_with_JSON,iterator->identical_entries[i]->path_with_JSON)==0){
			// if (node->json != iterator->identical_entries[i]->json){
				sum += 1;
				// printf("json: %d, entry: %d\n",node->json,i);
				// printf("json %d is the same with json %d\n",node->json,iterator->identical_entries[i]->json);
			}
		}
		iterator = iterator->next_bucket;
	}
	if(sum){
		printf("json %d has a total of %d entries\n",node->json,sum);
	}
}
void print_all_relations(tree_entry* root){
	if (root){
		print_node_relations(root);
		print_all_relations(root->right);
		print_all_relations(root->left);
	}
}