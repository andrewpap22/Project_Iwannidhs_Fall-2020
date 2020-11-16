#include "../headers/structs.h"

int compare(char *a, char *b)
{
	//returns 0 if a is smaller, 1 if its bigger, 3 if they are the same (should never return 3)
	int i = 0;
	while (1)
	{
		if (i < strlen(a) && i < strlen(b))
		{
			if (*(a + i) < *(b + i))
			{
				return 0;
			}
			else if (*(a + i) > *(b + i))
			{
				return 1;
			}
		}
		else if (i == strlen(a) && i != strlen(b))
		{
			return 0;
		}
		else if (i == strlen(b) && i != strlen(a))
		{
			return 1;
		}
		else
		{
			return 3;
		}
		i++;
	}
}

tree_entry *insert(tree_entry *T, int x, char *path_with_JSON, char *json_specs)
{

	if (T == NULL)
	{

		T = (tree_entry *)malloc(sizeof(tree_entry));

		T->json = x;
		T->path_with_JSON = path_with_JSON;
		T->specs = json_specs;

		T->left = NULL;
		T->right = NULL;

		T->headbucket = malloc(sizeof(headBucket));
		T->headbucket->first_bucket = malloc(sizeof(bucket));
		T->headbucket->first_bucket->next_bucket = NULL;
		T->headbucket->first_bucket->identical_entries[0] = T;
		T->headbucket->first_bucket->numofentries = 1;
	}
	// else if (x > T->json) // insert in right subtree
	else if (compare(path_with_JSON, T->path_with_JSON) == 1) // insert in right subtree

	{
		T->right = insert(T->right, x, path_with_JSON, json_specs);
		if (BF(T) == -2)
			// if (x > T->right->json)
			if (compare(path_with_JSON, T->right->path_with_JSON) == 1)
				T = RR(T);
			else
				T = RL(T);
	}
	// else if (x < T->json)
	else if (compare(path_with_JSON, T->path_with_JSON) == 0) // insert in left subtree
	{
		T->left = insert(T->left, x, path_with_JSON, json_specs);
		if (BF(T) == 2)
			// if (x < T->left->json)
			if (compare(path_with_JSON, T->left->path_with_JSON) == 0)
				T = LL(T);
			else
				T = LR(T);
	}

	T->ht = height(T);

	return (T);
}

tree_entry *search(tree_entry *T, char *x)
{
	if (T == NULL)
	{
		return NULL;
	}
	// if (x > T->json)
	if (compare(x, T->path_with_JSON) == 1)
	{
		return (search(T->right, x));
	}
	// else if (x < T->json)
	else if (compare(x, T->path_with_JSON) == 0)
	{
		return (search(T->left, x));
	}
	else
	{
		// printf("search: found!\n");
		return (T);
	}
}

/* 
tree_entry *Delete(tree_entry *T,int x)
{
	tree_entry *p;
	
	if(T==NULL){
		return NULL;
	}
	else
		if(x > T->json)		// insert in right subtree
		{
			T->right=Delete(T->right,x);
			if(BF(T)==2)
				if(BF(T->left)>=0)
					T=LL(T);
				else
					T=LR(T);
		}
		else
			if(x<T->json)
			{
				T->left=Delete(T->left,x);
				if(BF(T)==-2)	//Rebalance during windup
					if(BF(T->right)<=0)
						T=RR(T);
					else
						T=RL(T);
			}
			else
			{
				//json to be deleted is found
				if(T->right!=NULL)
				{	//delete its inorder succesor
					p=T->right;
					
					while(p->left!= NULL)
						p=p->left;
					
					T->json=p->json;
					T->right=Delete(T->right,p->json);
					
					if(BF(T)==2)//Rebalance during windup
						if(BF(T->left)>=0)
							T=LL(T);
						else
							T=LR(T);
				}
				else
					return(T->left);
			}
	T->ht=height(T);
	return(T);
}
*/

int height(tree_entry *T)
{
	int lh, rh;
	if (T == NULL)
		return (0);

	if (T->left == NULL)
		lh = 0;
	else
		lh = 1 + T->left->ht;

	if (T->right == NULL)
		rh = 0;
	else
		rh = 1 + T->right->ht;

	if (lh > rh)
		return (lh);

	return (rh);
}

tree_entry *rotateright(tree_entry *x)
{
	tree_entry *y;
	y = x->left;
	x->left = y->right;
	y->right = x;
	x->ht = height(x);
	y->ht = height(y);
	return (y);
}

tree_entry *rotateleft(tree_entry *x)
{
	tree_entry *y;
	y = x->right;
	x->right = y->left;
	y->left = x;
	x->ht = height(x);
	y->ht = height(y);

	return (y);
}

tree_entry *RR(tree_entry *T)
{
	T = rotateleft(T);
	return (T);
}

tree_entry *LL(tree_entry *T)
{
	T = rotateright(T);
	return (T);
}

tree_entry *LR(tree_entry *T)
{
	T->left = rotateleft(T->left);
	T = rotateright(T);

	return (T);
}

tree_entry *RL(tree_entry *T)
{
	T->right = rotateright(T->right);
	T = rotateleft(T);
	return (T);
}

int BF(tree_entry *T)
{
	int lh, rh;
	if (T == NULL)
		return (0);

	if (T->left == NULL)
		lh = 0;
	else
		lh = 1 + T->left->ht;

	if (T->right == NULL)
		rh = 0;
	else
		rh = 1 + T->right->ht;

	return (lh - rh);
}

void preorder(tree_entry *T)
{
	if (T != NULL)
	{
		printf("%d(Bf=%d)", T->json, BF(T));
		preorder(T->left);
		preorder(T->right);
	}
}

void inorder(tree_entry *T)
{
	if (T != NULL)
	{
		inorder(T->left);
		printf("%d(Bf=%d)", T->json, BF(T));
		inorder(T->right);
	}
}

void free_list_of_buckets(bucket* B){
	if (B!=NULL){
		free_list_of_buckets(B->next_bucket);
		free(B);
	}
}

void free_node(tree_entry *T){
	if (T){
		free(T->specs);
		free(T->path_with_JSON);
		free_list_of_buckets(T->headbucket->first_bucket);
		T->headbucket->first_bucket=NULL;
		free_node(T->left);
		free_node(T->right);
		free(T);
	}
}


char* read_json(char* json_filename)
{
	/* --- needed to handle json files --- */

	struct json_object *parsed_json; // this holds the entire json document

	FILE *fp;
	long file_size;
	char *buffer = NULL;
	char *specs = NULL;

	fp = fopen(json_filename, "r"); // open and read json files.
	fseek(fp, 0L, SEEK_END);
	file_size = ftell(fp); // determine the file size of each and every json file to allocate proper memory.
	fseek(fp, 0L, SEEK_SET);

	buffer = malloc(sizeof(char)*file_size); // stores contents of json files
	fread(buffer, file_size, 1, fp); //read the file and put its contents into the buffer.
	fclose(fp);
	//parse json's file contents and convert it into json object.
	parsed_json = json_tokener_parse(buffer);
	specs = malloc(file_size * sizeof(char));
	strcpy(specs, json_object_to_json_string(parsed_json)); // stringify the json object and store it as a single string.

	free(buffer);
	return (specs); // return the stringified version of the json object of each and every .json file.
}
