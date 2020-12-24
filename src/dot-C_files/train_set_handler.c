#include "../headers/train_set_handler.h"

char stopwords[NUMOFSTOPWORDS][15] = {
	"i",
	"me",
	"my",
	"myself",
	"we",
	"our",
	"ours",
	"ourselves",
	"you",
	"your",
	"yours",
	"yourself",
	"yourselves",
	"he",
	"him",
	"his",
	"himself",
	"she",
	"her",
	"hers",
	"herself",
	"it",
	"its",
	"itself",
	"they",
	"them",
	"their",
	"theirs",
	"themselves",
	"what",
	"which",
	"who",
	"whom",
	"this",
	"that",
	"these",
	"those",
	"am",
	"is",
	"are",
	"was",
	"were",
	"be",
	"been",
	"being",
	"have",
	"has",
	"had",
	"having",
	"do",
	"does",
	"did",
	"doing",
	"a",
	"an",
	"the",
	"and",
	"but",
	"if",
	"or",
	"because",
	"as",
	"until",
	"while",
	"of",
	"at",
	"by",
	"for",
	"with",
	"about",
	"against",
	"between",
	"into",
	"through",
	"during",
	"before",
	"after",
	"above",
	"below",
	"to",
	"from",
	"up",
	"down",
	"in",
	"out",
	"on",
	"off",
	"over",
	"under",
	"again",
	"further",
	"then",
	"once",
	"here",
	"there",
	"when",
	"where",
	"why",
	"how",
	"all",
	"any",
	"both",
	"each",
	"few",
	"more",
	"most",
	"other",
	"some",
	"such",
	"no",
	"nor",
	"not",
	"only",
	"own",
	"same",
	"so",
	"than",
	"too",
	"very",
	"s",
	"t",
	"can",
	"will",
	"just",
	"don",
	"should",
	"now",
	",",
	".",
	"\\",
	"/",
	")",
	"(",
	"!",
	"@",
	"#",
	"$",
	"%",
	"^",
	"&",
	"*",
	"-",
	"_",
	"=",
	"+",
	"~",
	"`",
	"?",
	"]",
	"[",
	"}",
	"{",
	"<",
	">"
	};


int json_key = 0;
int word_key = 0;
int num_of_unique_words = 0;
int num_of_unique_usefull_words = 0;


//Functions 

int stopword_check(char* word){
    for(int i = 0; i < NUMOFSTOPWORDS; i++){
        if(strcmp(word,stopwords[i])==0){
            return -1;
        }
    }
	return 0;
}
void create_train_set_tfidf(float** data_array, int num_of_words, tree_entry* database_root, char* relations_file){
	FILE * fp;
	FILE * fp_dest;
    char * line = NULL;
    size_t len = 0;
    ssize_t read;
	char* part_of_string;
	char* json1 = malloc(40*sizeof(char));
	char* json2 = malloc(40*sizeof(char));
	int relation;
	float num;
	tree_entry* entry1;
	tree_entry* entry2;

	fp_dest = fopen("Train_Set", "w");
    fp = fopen(relations_file, "r");
    if (fp == NULL){
        exit(EXIT_FAILURE);
	}

    while ((read = getline(&line, &len, fp)) != -1) {
	
		part_of_string = strtok(line, ", "); 
		strcpy(json1, part_of_string);
		part_of_string = strtok(NULL, ", "); 
		strcpy(json2, part_of_string);
		part_of_string = strtok(NULL, "\0"); 
		relation = atoi(part_of_string);
        // printf("%s ", json1);
		// printf("%s ", json2);
		entry1 = search(database_root,json1);
		entry2 = search(database_root,json2);

		for (int i = 0; i < 1000; i++){
			num = (data_array[i][entry1->json] - data_array[i][entry2->json]);
			fprintf(fp_dest, "%f, ",num);
		}
		fprintf(fp_dest, "%d\n",relation);
    }
    fclose(fp);
	fclose(fp_dest);
	free(json1);
	free(json2);
}

void create_train_set_bow(int** data_array, int num_of_words, tree_entry* database_root, char* relations_file){
	FILE * fp;
	FILE * fp_dest;
    char * line = NULL;
    size_t len = 0;
    ssize_t read;
	char* part_of_string;
	char* json1 = malloc(40*sizeof(char));
	char* json2 = malloc(40*sizeof(char));
	int relation;
	float num;
	tree_entry* entry1;
	tree_entry* entry2;

	fp_dest = fopen("Train_Set", "w");
    fp = fopen(relations_file, "r");
    if (fp == NULL)
        exit(EXIT_FAILURE);

    while ((read = getline(&line, &len, fp)) != -1) {
	
		part_of_string = strtok(line, ", "); 
		strcpy(json1, part_of_string);
		part_of_string = strtok(NULL, ", "); 
		strcpy(json2, part_of_string);
		part_of_string = strtok(NULL, "\0"); 
		relation = atoi(part_of_string);
        // printf("%s ", json1);
		// printf("%s ", json2);
		entry1 = search(database_root,json1);
		entry2 = search(database_root,json2);

		for (int i = 0; i < 1000; i++){
			num = (data_array[i][entry1->json] - data_array[i][entry2->json]);
			fprintf(fp_dest, "%f, ",num);
		}
		fprintf(fp_dest, "%d\n",relation);
    }
    fclose(fp);
	fclose(fp_dest);
	free(json1);
	free(json2);
}

float ** create_tf_idf(int** bow_array){
	int word_count = num_of_unique_usefull_words;
	int json_count = json_key;
	// printf("word_count %d\n",word_count);
	// printf("json_count %d\n",json_count);

	int json_total_words[json_count];	//num of words for every json
	int jsons_including_word_array[word_count];	//num of jsons that every word appears in atleast once

	for (int cur_json = 0; cur_json < json_count; cur_json++){
		json_total_words[cur_json] = 0;
	}	
	//fill the arrays above^^
	for (int cur_word = 0; cur_word < word_count; cur_word++){
		jsons_including_word_array[cur_word] = 0;
		for (int cur_json = 0; cur_json < json_count; cur_json++){
			if (bow_array[cur_word][cur_json]>0){
				jsons_including_word_array[cur_word] += 1 ;
				// printf("%d\n",bow_array[cur_word][cur_json]);
				json_total_words[cur_json] += bow_array[cur_word][cur_json];
				// printf("%d\n\n",json_total_words[cur_json]);
			}
		}
	}
	float tf;
	float idf;
	float** tf_idf_array = malloc(word_count*sizeof(float*));
	// for (int cur_word = 0; cur_word < word_count; cur_word++){
	// 	for (int cur_json = 0; cur_json < json_count; cur_json++){
	// 		printf("%d\n",cur_word);
	// 		tf_idf_array[cur_word][cur_json] = 0;
	// 	}
	// }
	//create tf_idf_array
	for (int cur_word = 0; cur_word < word_count; cur_word++){
		//allocate tf_idf_array column by column
		tf_idf_array[cur_word] = malloc(sizeof(float)*json_count);
		if (jsons_including_word_array[cur_word] == 0){
			printf("Empty column!?!?\n");
			break;
		}
	}
	//fill tf_idf_array
	for (int cur_word = 0; cur_word < word_count; cur_word++){
		idf = log10f(((float)(json_count))/((float)(jsons_including_word_array[cur_word])));
		// printf("idf:                        %lf\n\n",idf);
		for (int cur_json = 0; cur_json < json_count; cur_json++){
			if (bow_array[cur_word][cur_json] == 0){
				tf = 0;
			}
			else{
				tf = (float)bow_array[cur_word][cur_json]/(float)json_total_words[cur_json];
			}
			// printf("tf:          %lf\n\n",tf);
			// printf("tf idf:     %lf\n", tf*idf);
			tf_idf_array[cur_word][cur_json] = tf*idf;
		}
		// free(bow_array[cur_word]);
		// printf("%d\n",cur_word);
	}
	return tf_idf_array;
}


int ** create_bow_array(tree_entry* json_node){
	bow_tree_entry* bow_root = create_bow_tree(json_node);

	int** bow_array = malloc(num_of_unique_words*sizeof(int*));
	for (int i = 0; i < num_of_unique_words; i++){
		bow_array[i] = malloc(sizeof(int)*json_key);
	}
	printf("%d different words in BoW\n",num_of_unique_words);
	get_bow_tree_entries(bow_root, bow_array);
	printf("%d different words in BoW after stopword removal\n",num_of_unique_usefull_words);

	return bow_array;
}


void get_bow_tree_entries(bow_tree_entry* bow_root, int** bow_array){
	if (bow_root == NULL){
		return;
	}
	else{
		get_bow_tree_entries(bow_root->left, bow_array);
		if (stopword_check(bow_root->word)==0){
			bow_array[word_key] = bow_root->wordcounts;
			word_key++;
			num_of_unique_usefull_words++;
			/*print dictionary*/
			//printf("%s ",bow_root->word);
		}
		get_bow_tree_entries(bow_root->right, bow_array);
	}
}

bow_tree_entry* create_bow_tree(tree_entry* json_node){
	add_json_keys(json_node);
	bow_tree_entry* bow_root = NULL;
	bow_root = add_jsons_to_bow(bow_root,json_node);
	return bow_root;
}
void add_json_keys(tree_entry* root){
	if (root==NULL){
		return;
	}
	else{
		add_json_keys(root->left);
		root->json = json_key;
		// printf("%d\n",json_key);
		json_key +=1;
		add_json_keys(root->right);
	}
}

bow_tree_entry* add_jsons_to_bow(bow_tree_entry* bow_root, tree_entry* json_node){
	if (json_node==NULL){
		return bow_root;
	}
	bow_root = json_to_bow(bow_root, json_node);

	bow_root = add_jsons_to_bow(bow_root, json_node->right);
	bow_root = add_jsons_to_bow(bow_root, json_node->left);
	return bow_root;
}

bow_tree_entry* json_to_bow(bow_tree_entry* bow_root, tree_entry* json_node){

	char *current_word = strtok(json_node->specs," ");
	while (current_word!=NULL){
		current_word = strtok(NULL," ");		
		bow_root = word_to_bow(bow_root, current_word, json_node->json);
	}
	return bow_root;

}

bow_tree_entry* word_to_bow(bow_tree_entry* bow_root, char* word, int jsonkey){
	
	if (word==NULL){
		return bow_root;
	}
	// printf("%s\n", word);
	if (strlen(word)>MAXWORDSIZE){
		return bow_root;
	}
	

	//Lowercase
	for(int i = 0; i < strlen(word); i++){
 		*(word+i) = tolower(*(word+i));
	}

	/////////////////
    int i = 0; 
    while(i<strlen(word)){
        if((*(word+i)==',') || (*(word+i)=='(') || (*(word+i)==')') || (*(word+i)==':') || (*(word+i)=='!') || (*(word+i)==';') || (*(word+i)=='\"') || (*(word+i)=='~') || (*(word+i)=='[') || (*(word+i)==']') || (*(word+i)=='{') || (*(word+i)=='}')){
            memmove(&word[i], &word[i + 1], strlen(word) - i);
        }
        i++;
    }
	i=0;
	while(i<strlen(word)){
        if((*(word+i)==',') || (*(word+i)=='(') || (*(word+i)==')') || (*(word+i)==':') || (*(word+i)=='!') || (*(word+i)==';') || (*(word+i)=='\"') || (*(word+i)=='~') || (*(word+i)=='[') || (*(word+i)==']') || (*(word+i)=='{') || (*(word+i)=='}')){
            memmove(&word[i], &word[i + 1], strlen(word) - i);
        }
        i++;
    }
	/////////////////
	
	// else{
		bow_tree_entry* search_result = bow_search(bow_root, word);
		if (search_result!=NULL){
			search_result->wordcounts[jsonkey] += 1; 
		}
		else{
			// printf("^^ new word^^\n");
			char* new_word = malloc(sizeof(char)*strlen(word)+2);
			strcpy(new_word,word);
			bow_root = bow_insert(bow_root, jsonkey, new_word);
		}
		return bow_root;
	// }
}

bow_tree_entry *bow_insert(bow_tree_entry *T, int current_json, char *word)
{
	if (T == NULL)
	{
		T = (bow_tree_entry *)malloc(sizeof(bow_tree_entry));

		// T->word_key = word_key;
		num_of_unique_words++;
		T->word = word;
		T->left = NULL;
		T->right = NULL;
		T->wordcounts[current_json] = 1;
	}
	else if (compare(word, T->word) == 1) // insert in right subtree
	{
		T->right = bow_insert(T->right, current_json, word);
		if (bow_BF(T) == -2)
			// if (word > T->right->word)
			if (compare(word, T->right->word) == 1)
				T = bow_RR(T);
			else
				T = bow_RL(T);
	}
	else if (compare(word, T->word) == 0) // insert in left subtree
	{
		T->left = bow_insert(T->left, current_json, word);
		if (bow_BF(T) == 2)
			// if (word < T->left->word)
			if (compare(word, T->left->word) == 0)
				T = bow_LL(T);
			else
				T = bow_LR(T);
	}
	T->ht = bow_height(T);
	return (T);
}

bow_tree_entry *bow_search(bow_tree_entry *T, char *x)
{
	if (T == NULL)
	{
		return NULL;
	}
	// if (x > T->json)
	if (compare(x, T->word) == 1)
	{
		return (bow_search(T->right, x));
	}
	// else if (x < T->json)
	else if (compare(x, T->word) == 0)
	{
		return (bow_search(T->left, x));
	}
	else
	{
		// printf("bow_search: found!\n");
		return (T);
	}
}

int bow_height(bow_tree_entry *T)
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

bow_tree_entry *bow_rotateright(bow_tree_entry *x)
{
	bow_tree_entry *y;
	y = x->left;
	x->left = y->right;
	y->right = x;
	x->ht = bow_height(x);
	y->ht = bow_height(y);
	return (y);
}

bow_tree_entry *bow_rotateleft(bow_tree_entry *x)
{
	bow_tree_entry *y;
	y = x->right;
	x->right = y->left;
	y->left = x;
	x->ht = bow_height(x);
	y->ht = bow_height(y);

	return (y);
}

bow_tree_entry *bow_RR(bow_tree_entry *T)
{
	T = bow_rotateleft(T);
	return (T);
}

bow_tree_entry *bow_LL(bow_tree_entry *T)
{
	T = bow_rotateright(T);
	return (T);
}

bow_tree_entry *bow_LR(bow_tree_entry *T)
{
	T->left = bow_rotateleft(T->left);
	T = bow_rotateright(T);

	return (T);
}

bow_tree_entry *bow_RL(bow_tree_entry *T)
{
	T->right = bow_rotateright(T->right);
	T = bow_rotateleft(T);
	return (T);
}

int bow_BF(bow_tree_entry *T)
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