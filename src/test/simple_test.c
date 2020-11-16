#include <stdio.h>
#include <string.h>
#include "../external/acutest.h"	
#include "../headers/structs.h"
#include "../headers/W_handler.h"

void test_height(void){
    tree_entry *database_root = NULL;
    char *json_specs;
    int ht = 0;
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

    //Tree 3 nodes
    num_of_json = 4239;
    name_of_json = malloc(sizeof(char *));
    strcpy(name_of_json, "buy.net//4239");
    full_json_path = "../../dataset/camera_specs/2013_camera_specs/buy.net/4239.json";
    json_specs = read_json(full_json_path);
    database_root = insert(database_root, num_of_json, name_of_json, json_specs);

    //Tree 4 nodes
    num_of_json = 5449;
    name_of_json = malloc(sizeof(char *));
    strcpy(name_of_json, "www.alibaba.com//5449");
    full_json_path = "../../dataset/camera_specs/2013_camera_specs/www.alibaba.com/5449.json";
    json_specs = read_json(full_json_path);
    database_root = insert(database_root, num_of_json, name_of_json, json_specs);

    ht = height(database_root);
    TEST_CHECK(ht == 2);
    TEST_MSG("Expected: %d", 2);
    TEST_MSG("Produced: %d", ht);

}

void test_BF(void){
    tree_entry *database_root = NULL;
    char *json_specs;
    int bf = 0;
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

    //Tree 3 nodes
    num_of_json = 4239;
    name_of_json = malloc(sizeof(char *));
    strcpy(name_of_json, "buy.net//4239");
    full_json_path = "../../dataset/camera_specs/2013_camera_specs/buy.net/4239.json";
    json_specs = read_json(full_json_path);
    database_root = insert(database_root, num_of_json, name_of_json, json_specs);

    //Tree 4 nodes
    num_of_json = 5449;
    name_of_json = malloc(sizeof(char *));
    strcpy(name_of_json, "www.alibaba.com//5449");
    full_json_path = "../../dataset/camera_specs/2013_camera_specs/www.alibaba.com/5449.json";
    json_specs = read_json(full_json_path);
    database_root = insert(database_root, num_of_json, name_of_json, json_specs);

    bf = BF(database_root);
    TEST_CHECK(bf == -1);
    TEST_MSG("Expected: %d", -1);
    TEST_MSG("Produced: %d", bf);

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

void test_read_json(void){

    char *full_json_path;
    char *json_specs;
    int len1 = 0 ,len2 = 0;
    int cm = 0;
    char* str = "{\
 \"<page title>\": \"Polaroid Is426 16 Megapixel Compact Camera - Red - 2.4\\\" Lcd - 4x Optical Zoom - Pictbridge IS426RED Price Comparison at Buy.net\",\
 \"brand name\": \"Polaroid\",\
 \"builtin flash\": \"Yes\",\
 \"camera modes\": \"Scene Modes: Portrait Night\",\
 \"exposure control\": \"Auto\",\
 \"maximum diopter adjustment\": \"No\",\
 \"minimum diopter adjustment\": \"No\",\
 \"number of batteries support\": \"1\",\
 \"parent retsku\": \"B00DJGZIU4\",\
 \"pictbridge\": \"Yes\",\
 \"product model\": \"iS426\",\
 \"viewfinder type\": \"No\"\
 }";

    full_json_path = "../../dataset/camera_specs/2013_camera_specs/buy.net/4236.json";
    json_specs = read_json(full_json_path);

    cm = compare(str,json_specs);
    TEST_CHECK(cm == 3);
    TEST_MSG("Expected: %d", 3);
    TEST_MSG("Produced: %d", cm);

    len1 = strlen(str);
    len2 = strlen(json_specs);

    TEST_CHECK(len1 == len2);
    TEST_MSG("Expected: %d", TRUE);
    TEST_MSG("Produced: %d", len1 == len2);

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

    //Tree 4 nodes
    num_of_json = 5449;
    name_of_json = malloc(sizeof(char *));
    strcpy(name_of_json, "www.alibaba.com//5449");
    full_json_path = "../../dataset/camera_specs/2013_camera_specs/www.alibaba.com/5449.json";
    json_specs = read_json(full_json_path);
    database_root = insert(database_root, num_of_json, name_of_json, json_specs);

    //Test for BF of the tree
    bf = BF(database_root);
    TEST_CHECK(bf == -1);
    TEST_MSG("Expected: %d", -1);
    TEST_MSG("Produced: %d", bf);

    //Test for height of the tree
    ht = height(database_root);
    TEST_CHECK(ht == 2);
    TEST_MSG("Expected: %d", 2);
    TEST_MSG("Produced: %d", ht);

    free(name_of_json);
    free_node(database_root);
}

void test_search(void){

    tree_entry *database_root = NULL;
    char *json_specs;
    int cm = 0;
    int num_of_json  = 0; 
    char *name_of_json;
    char *full_json_path;
    tree_entry *entry1 = NULL;
    tree_entry *entry2 = NULL;

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

    //Tree 3 nodes
    num_of_json = 4239;
    name_of_json = malloc(sizeof(char *));
    strcpy(name_of_json, "buy.net//4239");
    full_json_path = "../../dataset/camera_specs/2013_camera_specs/buy.net/4239.json";
    json_specs = read_json(full_json_path);
    database_root = insert(database_root, num_of_json, name_of_json, json_specs);

    //Tree 4 nodes
    num_of_json = 5449;
    name_of_json = malloc(sizeof(char *));
    strcpy(name_of_json, "www.alibaba.com//5449");
    full_json_path = "../../dataset/camera_specs/2013_camera_specs/www.alibaba.com/5449.json";
    json_specs = read_json(full_json_path);
    database_root = insert(database_root, num_of_json, name_of_json, json_specs);

    //Tree 5 nodes
    num_of_json = 5;
    name_of_json = malloc(sizeof(char *));
    strcpy(name_of_json, "www.cambuy.com.au//5");
    full_json_path = "../../dataset/camera_specs/2013_camera_specs/www.cambuy.com.au/5.json";
    json_specs = read_json(full_json_path);
    database_root = insert(database_root, num_of_json, name_of_json, json_specs);

    //find the jsons in the tree
    entry1 = search(database_root, "buy.net//4239");
    entry2 = search(database_root, "www.alibaba.com//5449");

    TEST_CHECK(entry1->json == 4239);
    TEST_MSG("Expected: %d", TRUE);
    TEST_MSG("Produced: %d", entry1->json == 4239);

    cm = compare(entry2->path_with_JSON, "www.alibaba.com//5449");
    TEST_CHECK(cm == 3);
    TEST_MSG("Expected: %d", 3);
    TEST_MSG("Produced: %d", cm);

    add_relation(database_root,"buy.net//4239","www.alibaba.com//5449",1);
    TEST_CHECK(entry1->headbucket == entry2->headbucket);
    TEST_MSG("Expected: %d", TRUE);
    TEST_MSG("Produced: %d", entry1->headbucket == entry2->headbucket);

}

void test_insert_entry(void){

}

void test_add_relation(void){

    tree_entry *database_root = NULL;
    char *json_specs;
    int ht = 0;
    int num_of_json  = 0; 
    char *name_of_json;
    char *full_json_path;
    tree_entry *entry1 = NULL;
    tree_entry *entry2 = NULL;

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

    //Tree 3 nodes
    num_of_json = 4239;
    name_of_json = malloc(sizeof(char *));
    strcpy(name_of_json, "buy.net//4239");
    full_json_path = "../../dataset/camera_specs/2013_camera_specs/buy.net/4239.json";
    json_specs = read_json(full_json_path);
    database_root = insert(database_root, num_of_json, name_of_json, json_specs);

    //Tree 4 nodes
    num_of_json = 5449;
    name_of_json = malloc(sizeof(char *));
    strcpy(name_of_json, "www.alibaba.com//5449");
    full_json_path = "../../dataset/camera_specs/2013_camera_specs/www.alibaba.com/5449.json";
    json_specs = read_json(full_json_path);
    database_root = insert(database_root, num_of_json, name_of_json, json_specs);

    //Tree 5 nodes
    num_of_json = 5;
    name_of_json = malloc(sizeof(char *));
    strcpy(name_of_json, "www.cambuy.com.au//5");
    full_json_path = "../../dataset/camera_specs/2013_camera_specs/www.cambuy.com.au/5.json";
    json_specs = read_json(full_json_path);
    database_root = insert(database_root, num_of_json, name_of_json, json_specs);

    add_relation(database_root,"buy.net//4239","www.alibaba.com//5449",1);
    add_relation(database_root,"buy.net//4233","buy.net//4236",1);
    add_relation(database_root,"buy.net//4236","www.alibaba.com//5449",0);
    add_relation(database_root,"buy.net//4236","buy.net//4233",1);
    add_relation(database_root,"www.cambuy.com.au//5","buy.net//4239",1);
    add_relation(database_root,"www.cambuy.com.au//5","buy.net//4233",0);

    //find the jsons in the tree
    entry1 = search(database_root, "buy.net//4239");
    entry2 = search(database_root, "www.alibaba.com//5449");

    TEST_CHECK(entry1->headbucket == entry2->headbucket);
    TEST_MSG("Expected: %d", TRUE);
    TEST_MSG("Produced: %d", entry1->headbucket == entry2->headbucket);

    entry1 = NULL;
    entry2 = NULL;

    //find the jsons in the tree
    entry1 = search(database_root, "buy.net//4233");
    entry2 = search(database_root, "www.alibaba.com//5449");

    TEST_CHECK(entry1->headbucket != entry2->headbucket);
    TEST_MSG("Expected: %d", TRUE);
    TEST_MSG("Produced: %d", entry1->headbucket == entry2->headbucket);

    entry1 = NULL;
    entry2 = NULL;

    //find the jsons in the tree
    entry1 = search(database_root, "www.cambuy.com.au//5");
    entry2 = search(database_root, "www.alibaba.com//5449");

    TEST_CHECK(entry1->headbucket == entry2->headbucket);
    TEST_MSG("Expected: %d", TRUE);
    TEST_MSG("Produced: %d", entry1->headbucket == entry2->headbucket);

    }

void test_print_node_relations(void){}

TEST_LIST = {
    { "compare", test_compare },
    { "height", test_height },
    { "BF", test_BF },
    { "read_json", test_read_json },
    { "insert", test_insert },
    { "insert_entry", test_insert_entry },
    { "search", test_search },
    { "add_relation", test_add_relation },
    { "print_node_relations", test_print_node_relations },
    { NULL, NULL }
};

