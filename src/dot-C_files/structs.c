#include "../headers/structs.h"

int compare(char* a, char* b){
	//returns 0 if a is smaller, 1 if its bigger, 3 if they are the same (should never return 3)
    int i=0;
    while(1){
        if(i<strlen(a) && i<strlen(b)){
            if(*(a+i)<*(b+i)){
                return 0;
            }
			else if(*(a+i)>*(b+i)){
                return 1;
            }
        }
        else if(i==strlen(a) && i!=strlen(b)){
            return 0;
        }
        else if(i==strlen(b) && i!=strlen(a)){
            return 1;
        }
        else{
            return 3;
        }
    i++;
    }
}


tree_entry *insert(tree_entry *T, int x, char *path_with_JSON)
{

	if (T == NULL){

		T = (tree_entry *)malloc(sizeof(tree_entry));
		T->json = x;
		T->path_with_JSON = path_with_JSON;
		T->left = NULL;
		T->right = NULL;

		T->headbucket = malloc(sizeof(headBucket));
		/* specs copy edw */
		T->headbucket->first_bucket = malloc(sizeof(bucket));
		T->headbucket->first_bucket->next_bucket = NULL;
		T->headbucket->first_bucket->identical_entries[0] = T;
		T->headbucket->first_bucket->numofentries = 1;
	}
	// else if (x > T->json) // insert in right subtree
	else if (compare(path_with_JSON,T->path_with_JSON)==1) // insert in right subtree

	{
		T->right = insert(T->right, x, path_with_JSON);
		if (BF(T) == -2)
			// if (x > T->right->json)
			if (compare(path_with_JSON,T->right->path_with_JSON)==1)
				T = RR(T);
			else
				T = RL(T);
	}
	// else if (x < T->json)
	else if (compare(path_with_JSON,T->path_with_JSON)==0) // insert in left subtree
	{
		T->left = insert(T->left, x, path_with_JSON);
		if (BF(T) == 2)
			// if (x < T->left->json)
			if (compare(path_with_JSON,T->left->path_with_JSON)==0)
				T = LL(T);
			else
				T = LR(T);
	}

	T->ht = height(T);

	return (T);
}

tree_entry *search(tree_entry *T, char* x)
{
	if (T == NULL)
	{
		return NULL;
	}
	// if (x > T->json)
	if (compare(x,T->path_with_JSON)==1)
	{
		return (search(T->right, x));
	}
	// else if (x < T->json)
	else if (compare(x,T->path_with_JSON)==0)
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

void read_json(char* json_filename)
{
	/* --- needed to handle json files --- */

    char buffer[20000]; // store contents of json files
    struct json_object *parsed_json; // this holds the entire json document
    struct json_object *page_title; // needed to read page title of jsons.
		FILE *fp;

    fp = fopen(json_filename, "r");
    fread(buffer, 20000, 1, fp); //read the file and put its contents into the buffer.
    fclose(fp);

    //parse json's file contents and convert it into json object.
    parsed_json = json_tokener_parse(buffer);

    //get the value of the key from json object (in our case the page_title only)
    json_object_object_get_ex(parsed_json, "<page title>", &page_title);

    //print the above value that we got to check correctness
    printf("<page title> : %s\n", json_object_get_string(page_title));
}