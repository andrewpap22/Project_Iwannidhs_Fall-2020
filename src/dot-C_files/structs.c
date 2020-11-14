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


tree_entry *insert(tree_entry *T, int x, char *path_with_JSON, char* json_specs)
{

	if (T == NULL){

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
	else if (compare(path_with_JSON,T->path_with_JSON)==1) // insert in right subtree

	{
		T->right = insert(T->right, x, path_with_JSON, json_specs);
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
		T->left = insert(T->left, x, path_with_JSON, json_specs);
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

char* read_json(char* json_filename)
{
	/* --- needed to handle json files --- */

    char buffer[200000]; // stores contents of json files

		const int STRING_LENGTH = 1000000;
		const int NO_OF_SPECS = 1;
		char **json_specs; // array of strings (json specs: page title, camera type, color, etc...)

    struct json_object *parsed_json; // this holds the entire json document
    // struct json_object *page_title; // needed to read page title of jsons.
		// struct json_object *camera_type;
		// struct json_object *color;

	FILE *fp;
	long file_size;
    fp = fopen(json_filename, "r");
	fseek(fp,0L,SEEK_END);
	file_size = ftell(fp);
	// printf("%ld\n",file_size);
    fread(buffer, file_size, 1, fp); //read the file and put its contents into the buffer.
    fclose(fp);

    //parse json's file contents and convert it into json object.
    parsed_json = json_tokener_parse(buffer);

		/* pairnei olo to json object apo panw kai to metatrepei se string kai to printarei. */
		//printf("%s\n",json_object_to_json_string_ext(parsed_json,JSON_C_TO_STRING_PLAIN)); 

    //get the value of the key from json object
    // json_object_object_get_ex(parsed_json, "<page title>", &page_title);
		// json_object_object_get_ex(parsed_json, "brand", &camera_type);
		// json_object_object_get_ex(parsed_json, "dimension", &color);

		// const char *pageTitle = json_object_get_string(page_title);
		// const char *cameraType = json_object_get_string(camera_type);
		// const char *cameraColor = json_object_get_string(color);

	// json_specs = malloc(NO_OF_SPECS * sizeof(char*));
	char* specs = malloc(file_size*sizeof(char));
	// for (int i = 0; i < NO_OF_SPECS; i++){
	// 	json_specs[i] = malloc(STRING_LENGTH * sizeof(char));
	// 	strcpy(json_specs[i], (json_object_to_json_string_ext(parsed_json, JSON_C_TO_STRING_PLAIN)));
	// }
	strcpy(specs, json_object_to_json_string(parsed_json));
	// printf("%s\n",specs);



		// strcpy(json_specs[0], pageTitle);
		// strcpy(json_specs[1], cameraType);
		// strcpy(json_specs[2], cameraColor);

    //print the above value that we got to check correctness
    // printf("<page title> : %s\n", pageTitle);
		// printf("camera type : %s\n", cameraType);
		// printf("camera color : %s\n", cameraColor);



		/* poio einai to provlhma: den exoun ola ta json files tin idia onomasia sta specs. Opote den borw na kanw hardcode ena ena
		 * opws exw kanei apo panw ta specs giati uparxoyn periptwseis opou h json_object_get_string 8a gurisei null
		 * epeidh den 8a vrei to antistoixo json spec pou ths dinw. me apotelesma parakatw sto array na pernaei null anti gia string
		 * kai na trwei segmentation. 
		 * Ara, prepei na vrw tropo na pernaei oloklhro to json spec ws 1 string anti gia ena ena ka8e spec ksexwrista...
		 * ====================== ETOIMO!!!!!!!!!!!! ===========================
		 * akrivws auto pou periegrapsa ginetai me polu aplo tropo me tin json_object_to_json_string_ext pou exw xrhsimopoihsei apo panw!!!
		 * 
		 * references: 
		 * https://alan-mushi.github.io/2014/10/28/json-c-tutorial-part-1.html
		 * https://stackoverflow.com/questions/4085372/how-to-return-a-string-array-from-a-function/11543552
		 * https://json-c.github.io/json-c/json-c-0.10/doc/html/json__object_8h.html#a84421dab94ccad42e901e534c6d7b658
		 * */


		return (specs);
}

void printoutarray(char **specs)
{
  // for (int i = 0; i < 3; ++i) {
  //       char *pos = specs[i];
  //       while (*pos != '\0') {
  //           printf("%c\n", *(pos++));
  //       }
  //       printf("\n");
  //   }
	printf("%s\n",specs[0]);
}