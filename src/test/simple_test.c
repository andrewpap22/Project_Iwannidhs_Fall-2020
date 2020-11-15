#include <stdio.h>
#include <string.h>
#include "../external/acutest.h"	
#include "../headers/structs.h"
#include "../headers/W_handler.h"

void test_read_json(void){

    char *full_json_path;
    char *json_specs;
    full_json_path = "../../dataset/camera_specs/2013_camera_specs/buy.net/4233.json";
    json_specs = read_json(full_json_path);

}

void test_insert(void){
    tree_entry *database_root = NULL;
    char *json_specs;
    int ht = 0, bf = 0;
    int num_of_json  = 0; 
    char *name_of_json;
    char *full_json_path;

	//Tree 1 node
  	num_of_json = 4233;
    name_of_json = malloc(sizeof(char *));
  	strcpy(name_of_json, "buy.net//4233");
  	full_json_path = "../../dataset/camera_specs/2013_camera_specs/buy.net/4233.json";
  	json_specs = read_json(full_json_path);
  	database_root = insert(database_root, num_of_json, name_of_json, json_specs);

    //Tree 2 nodes
  	num_of_json = 4236;
    name_of_json = malloc(sizeof(char *));
  	strcpy(name_of_json, "buy.net//4236");
  	full_json_path = "../../dataset/camera_specs/2013_camera_specs/buy.net/4236.json";
  	json_specs = read_json(full_json_path);
  	database_root = insert(database_root, num_of_json, name_of_json, json_specs);

    //Test for height of the tree
  	ht = height(database_root);
  	TEST_CHECK(ht == 1);
  	TEST_MSG("Expected: %d", 1);
    TEST_MSG("Produced: %d", ht);
    //Test for BF of the tree
    bf = BF(database_root);
    TEST_CHECK(bf == -1);
    TEST_MSG("Expected: %d", -1);
    TEST_MSG("Produced: %d", bf);

    //Tree 3 nodes
    num_of_json = 4239;
    name_of_json = malloc(sizeof(char *));
    strcpy(name_of_json, "buy.net//4239");
    full_json_path = "../../dataset/camera_specs/2013_camera_specs/buy.net/4239.json";
    json_specs = read_json(full_json_path);
    database_root = insert(database_root, num_of_json, name_of_json, json_specs);

    //Test for height of the tree
    ht = height(database_root);
    TEST_CHECK(ht == 1);
    TEST_MSG("Expected: %d", 1);
    TEST_MSG("Produced: %d", ht);
    //Test for BF of the tree
    bf = BF(database_root);
    TEST_CHECK(bf == 0);
    TEST_MSG("Expected: %d", 0);
    TEST_MSG("Produced: %d", bf);

    free(name_of_json);
    free_node(database_root);
}

void test_compare(void){
    char *name_of_json_1, *name_of_json_2;
    int cm;

    name_of_json_1 = malloc(sizeof(char *));
    strcpy(name_of_json_1, "buy.net//4236");
    name_of_json_2 = malloc(sizeof(char *));
    strcpy(name_of_json_2, "buy.net//4239");

    cm = compare(name_of_json_1,name_of_json_2);
    TEST_CHECK(cm == 0);
    TEST_MSG("Expected: %d", 1);
    TEST_MSG("Produced: %d", cm);

}

TEST_LIST = {
    { "read_json", test_read_json },
    { "insert", test_insert },
    { "compare", test_compare },
    { NULL, NULL }
};

/*
//tree_entry* node
void test_print_node_relations(void);	

//tree_entry* root, int json1, int json2, int relation
void test_add_relation(void){

	// allocate proper memory for the full path containing each and every .json files to be read by read_json()
    full_json_path = malloc(sizeof(*absolute_path) + sizeof(dir->d_name) + sizeof(char) + sizeof(char) + sizeof(dir_JSON->d_name));

    strcpy(full_json_path, file_path);
    strcat(full_json_path, "/");
    strcat(full_json_path, dir_JSON->d_name);

	//create data files stuff
  	tree_entry *database_root = NULL;
  	int num_of_json = 4343;
  	char *name_of_json = '4343.json';
  	json_specs = read_json(full_json_path);
  	//name_of_json = malloc(sizeof(dir->d_name));

  	database_root = insert(database_root, num_of_json, name_of_json, json_specs);
  	

}

*/
