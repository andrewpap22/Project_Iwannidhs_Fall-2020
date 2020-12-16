#include "../headers/train_set_handler.h"


int json_key = 0;
int word_key = 0;

int ** create_bow_array(tree_entry* json_node){
	bow_tree_entry* bow_root = create_bow_tree(json_node);

	int** bow_array = malloc(word_key*sizeof(int*));
	for (int i = 0; i < word_key; i++){
		bow_array[i] = malloc(sizeof(int)*json_key);
	}
	get_bow_tree_entries(bow_root, bow_array);
	printf("%d different words\n",word_key);
	return bow_array;
}
void get_bow_tree_entries(bow_tree_entry* bow_root, int** bow_array){
	if (bow_root == NULL){
		return;
	}
	else{
		// printf("%d\n",bow_root->word_key);
		bow_array[bow_root->word_key] = bow_root->wordcounts;
		for (int i = 0; i < json_key; i++){
			// printf("%d\n", bow_array[bow_root->word_key][i]);
		}
		
		get_bow_tree_entries(bow_root->right, bow_array);
		get_bow_tree_entries(bow_root->left, bow_array);
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
		root->json = json_key;
		// printf("%d\n",json_key);
		json_key +=1;
		add_json_keys(root->right);
		add_json_keys(root->left);
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

	while (current_word){
		// printf("%s\n",current_word);
		current_word = strtok(NULL," ");

		// preproccessing edw
		
		bow_root = word_to_bow(bow_root, current_word, json_node->json);
	}
	
	// printf("json to add to bow: %d\n",json_node->json);
	return bow_root;

}

bow_tree_entry* word_to_bow(bow_tree_entry* bow_root, char* word, int jsonkey){
	if (word==NULL){
		return bow_root;
	}
	
	// printf("word: %s\n",word);
	bow_tree_entry* search_result = bow_search(bow_root, word);
	if (search_result!=NULL){
		search_result->wordcounts[jsonkey] += 1; 
	}
	else{
		// printf("^^ new word ^^\n");
		char* new_word = malloc(sizeof(char)*strlen(word)+2);
		strcpy(new_word,word);
		bow_root = bow_insert(bow_root, jsonkey, new_word);
	}
	return bow_root;
}

bow_tree_entry *bow_insert(bow_tree_entry *T, int current_json, char *word)
{
	if (T == NULL)
	{
		T = (bow_tree_entry *)malloc(sizeof(bow_tree_entry));

		T->word_key = word_key;
		word_key++;
		T->word = word;
		T->left = NULL;
		T->right = NULL;
		T->wordcounts[current_json] = 1;
	}
	// else if (word > T->word) // insert in right subtree
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
	// else if (word < T->word)
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