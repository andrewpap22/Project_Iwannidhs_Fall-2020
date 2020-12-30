#include <stdio.h>
#include <string.h>
#include "../external/acutest.h"    
#include "../headers/structs.h"
#include "../headers/W_handler.h"
#include "../headers/json_parser.h"
#include "../headers/includes_for_parser.h"
#include "../headers/train_set_handler.h"

// Function only for help the Unit Testing
int helper_compareFile(FILE * fPtr1, FILE * fPtr2, int * line, int * col)
{
    char ch1, ch2;

    *line = 1;
    *col  = 0;

    do
    {
        // Input character from both files
        ch1 = fgetc(fPtr1);
        ch2 = fgetc(fPtr2);
        
        // Increment line 
        if (ch1 == '\n')
        {
            *line += 1;
            *col = 0;
        }

        // If characters are not same then return -1
        if (ch1 != ch2)
            return -1;

        *col  += 1;

    } while (ch1 != EOF && ch2 != EOF);


    // If both files have reached end 
    if (ch1 == EOF && ch2 == EOF)
        return 0;
    else
        return -1;
};

// Testing the function height in struct.c
void test_height(void){
    tree_entry *database_root = NULL;
    char *json_specs;
    int ht = 0;
    int num_of_json  = 0; 
    char *name_of_json;
    char *full_json_path;

    // Creating a test tree
    // First insertion of tree
    num_of_json = 4233;
    name_of_json = malloc(sizeof(char *));
    strcpy(name_of_json, "buy.net//4233");
    full_json_path = "../../dataset/camera_specs/2013_camera_specs/buy.net/4233.json";
    json_specs = read_json(full_json_path);
    database_root = insert(database_root, num_of_json, name_of_json, json_specs);

    // Second insertion of tree
    num_of_json = 4236;
    name_of_json = malloc(sizeof(char *));
    strcpy(name_of_json, "buy.net//4236");
    full_json_path = "../../dataset/camera_specs/2013_camera_specs/buy.net/4236.json";
    json_specs = read_json(full_json_path);
    database_root = insert(database_root, num_of_json, name_of_json, json_specs);

    // Third insertion of tree
    num_of_json = 4239;
    name_of_json = malloc(sizeof(char *));
    strcpy(name_of_json, "buy.net//4239");
    full_json_path = "../../dataset/camera_specs/2013_camera_specs/buy.net/4239.json";
    json_specs = read_json(full_json_path);
    database_root = insert(database_root, num_of_json, name_of_json, json_specs);

    // Forth insertion of tree
    num_of_json = 5449;
    name_of_json = malloc(sizeof(char *));
    strcpy(name_of_json, "www.alibaba.com//5449");
    full_json_path = "../../dataset/camera_specs/2013_camera_specs/www.alibaba.com/5449.json";
    json_specs = read_json(full_json_path);
    database_root = insert(database_root, num_of_json, name_of_json, json_specs);

    // Testing the height of the tree - It has to be 2
    ht = height(database_root);
    TEST_CHECK(ht == 2);
    TEST_MSG("Expected: %d", 2);
    TEST_MSG("Produced: %d", ht);

}

// Testing the function BF in struct.c
void test_BF(void){
    tree_entry *database_root = NULL;
    char *json_specs;
    int bf = 0;
    int num_of_json  = 0; 
    char *name_of_json;
    char *full_json_path;

    // Creating a test tree
    // First insertion of tree
    num_of_json = 4233;
    name_of_json = malloc(sizeof(char *));
    strcpy(name_of_json, "buy.net//4233");
    full_json_path = "../../dataset/camera_specs/2013_camera_specs/buy.net/4233.json";
    json_specs = read_json(full_json_path);
    database_root = insert(database_root, num_of_json, name_of_json, json_specs);

    // Second insertion of tree
    num_of_json = 4236;
    name_of_json = malloc(sizeof(char *));
    strcpy(name_of_json, "buy.net//4236");
    full_json_path = "../../dataset/camera_specs/2013_camera_specs/buy.net/4236.json";
    json_specs = read_json(full_json_path);
    database_root = insert(database_root, num_of_json, name_of_json, json_specs);

    // Third insertion of tree
    num_of_json = 4239;
    name_of_json = malloc(sizeof(char *));
    strcpy(name_of_json, "buy.net//4239");
    full_json_path = "../../dataset/camera_specs/2013_camera_specs/buy.net/4239.json";
    json_specs = read_json(full_json_path);
    database_root = insert(database_root, num_of_json, name_of_json, json_specs);

    // Forth insertion of tree
    num_of_json = 5449;
    name_of_json = malloc(sizeof(char *));
    strcpy(name_of_json, "www.alibaba.com//5449");
    full_json_path = "../../dataset/camera_specs/2013_camera_specs/www.alibaba.com/5449.json";
    json_specs = read_json(full_json_path);
    database_root = insert(database_root, num_of_json, name_of_json, json_specs);

    // Testing the BF of the tree - For those tree nodes thw BF has to be -1
    bf = BF(database_root);
    TEST_CHECK(bf == -1);
    TEST_MSG("Expected: %d", -1);
    TEST_MSG("Produced: %d", bf);

}

// Testing the function compare in struct.c
void test_compare(void){
    char *name_of_json_1, *name_of_json_2;
    int cm;

    // Give value in the variables that we are going to compare
    name_of_json_1 = malloc(sizeof(char *));
    strcpy(name_of_json_1, "buy.net//4236");
    name_of_json_2 = malloc(sizeof(char *));
    strcpy(name_of_json_2, "buy.net//4239");

    // Testing the comparison of 2 string variables - it has to be different name_of_json_1 < name_of_json_2
    cm = compare(name_of_json_1,name_of_json_2);
    TEST_CHECK(cm == 0);
    TEST_MSG("Expected: %d", 1);
    TEST_MSG("Produced: %d", cm);

    // Give value in the variables that we are going to compare
    name_of_json_1 = malloc(sizeof(char *));
    strcpy(name_of_json_1, "buy.net//4236");
    name_of_json_2 = malloc(sizeof(char *));
    strcpy(name_of_json_2, "buy.net//4236");

    // Testing the comparison of 2 string variables - it has to be different name_of_json_1 = name_of_json_2
    cm = compare(name_of_json_1,name_of_json_2);
    TEST_CHECK(cm == 3);
    TEST_MSG("Expected: %d", 3);
    TEST_MSG("Produced: %d", cm);
}

// Testing the function read_json in struct.c
void test_All_json_Values(void){

    char *full_json_path;
    char *json_specs;
    char *json_str;
    int len1 = 0 ,len2 = 0;
    int cm = 0;
    // Store a json into a string
    char* str = " Polaroid Is426 16 Megapixel Compact Camera - Red - 2.4\\\" Lcd - 4x Optical Zoom - Pictbridge IS426RED Price Comparison at Buy.net Polaroid Yes Scene Modes: Portrait Night Auto No No 1 B00DJGZIU4 Yes iS426 No";

    // First Test
    // Give the path with the json file that we are going to compare with the static variable
    full_json_path = "../../dataset/camera_specs/2013_camera_specs/buy.net/4236.json";

    // Call the function All_json_Values
    json_specs = All_json_Values(full_json_path);

    // Compare the static string with the result of the testing function - they have to be same
    cm = strcmp(str,json_specs);
    TEST_CHECK(cm == 0);
    TEST_MSG("Expected: %d", 0);
    TEST_MSG("Produced: %d", cm);

    // Second Test
    // Testing the length of the 2 strings - they must have the same length
    len1 = strlen(str);
    len2 = strlen(json_specs);

    TEST_CHECK(len1 == len2);
    TEST_MSG("Expected: %d", TRUE);
    TEST_MSG("Produced: %d", len1 == len2);

    // Third Test
    // Give the path with the json file that we are going to compare with the static variable
    full_json_path = "../../dataset/camera_specs/2013_camera_specs/buy.net/4233.json";

    // Call the function read_json
    json_specs = All_json_Values(full_json_path);

    // Compare the static string with the result of the testing function - they have to be different 
    cm = strcmp(str,json_specs);
    TEST_CHECK(cm != 0);
    TEST_MSG("Expected: %d", 1);
    TEST_MSG("Produced: %d", cm);

}

// Testing the function insert in struct.c 
void test_insert(void){
    tree_entry *database_root = NULL;
    char *json_specs;
    int ht = 0, bf = 0;
    int num_of_json  = 0; 
    char *name_of_json;
    char *full_json_path;

      // Creating a test tree
    // First insertion of tree
    num_of_json = 4233;
    name_of_json = malloc(sizeof(char *));
    strcpy(name_of_json, "buy.net//4233");
    full_json_path = "../../dataset/camera_specs/2013_camera_specs/buy.net/4233.json";
    json_specs = read_json(full_json_path);
    database_root = insert(database_root, num_of_json, name_of_json, json_specs);

    // Second insertion of tree
    num_of_json = 4236;
    name_of_json = malloc(sizeof(char *));
    strcpy(name_of_json, "buy.net//4236");
    full_json_path = "../../dataset/camera_specs/2013_camera_specs/buy.net/4236.json";
    json_specs = read_json(full_json_path);
    database_root = insert(database_root, num_of_json, name_of_json, json_specs);

    //Testing for height of the tree
    ht = height(database_root);
    TEST_CHECK(ht == 1);
    TEST_MSG("Expected: %d", 1);
    TEST_MSG("Produced: %d", ht);

    //Testing for BF of the tree
    bf = BF(database_root);
    TEST_CHECK(bf == -1);
    TEST_MSG("Expected: %d", -1);
    TEST_MSG("Produced: %d", bf);

    // Third insertion of tree
    num_of_json = 4239;
    name_of_json = malloc(sizeof(char *));
    strcpy(name_of_json, "buy.net//4239");
    full_json_path = "../../dataset/camera_specs/2013_camera_specs/buy.net/4239.json";
    json_specs = read_json(full_json_path);
    database_root = insert(database_root, num_of_json, name_of_json, json_specs);

    //Testing for height of the tree
    ht = height(database_root);
    TEST_CHECK(ht == 1);
    TEST_MSG("Expected: %d", 1);
    TEST_MSG("Produced: %d", ht);
    //Testing for BF of the tree
    bf = BF(database_root);
    TEST_CHECK(bf == 0);
    TEST_MSG("Expected: %d", 0);
    TEST_MSG("Produced: %d", bf);

    // Forth insertion of tree
    num_of_json = 5449;
    name_of_json = malloc(sizeof(char *));
    strcpy(name_of_json, "www.alibaba.com//5449");
    full_json_path = "../../dataset/camera_specs/2013_camera_specs/www.alibaba.com/5449.json";
    json_specs = read_json(full_json_path);
    database_root = insert(database_root, num_of_json, name_of_json, json_specs);

    //Testing for BF of the tree
    bf = BF(database_root);
    TEST_CHECK(bf == -1);
    TEST_MSG("Expected: %d", -1);
    TEST_MSG("Produced: %d", bf);

    //Testing for height of the tree
    ht = height(database_root);
    TEST_CHECK(ht == 2);
    TEST_MSG("Expected: %d", 2);
    TEST_MSG("Produced: %d", ht);

    free(name_of_json);
    free_node(database_root);
}

// Testing the function search in struct.c 
void test_search(void){

    tree_entry *database_root = NULL;
    char *json_specs;
    int cm = 0;
    int num_of_json  = 0; 
    char *name_of_json;
    char *full_json_path;
    tree_entry *entry1 = NULL;
    tree_entry *entry2 = NULL;

    // First insertion of tree
    num_of_json = 4233;
    name_of_json = malloc(sizeof(char *));
    strcpy(name_of_json, "buy.net//4233");
    full_json_path = "../../dataset/camera_specs/2013_camera_specs/buy.net/4233.json";
    json_specs = read_json(full_json_path);
    database_root = insert(database_root, num_of_json, name_of_json, json_specs);

    // Second insertion of tree
    num_of_json = 4236;
    name_of_json = malloc(sizeof(char *));
    strcpy(name_of_json, "buy.net//4236");
    full_json_path = "../../dataset/camera_specs/2013_camera_specs/buy.net/4236.json";
    json_specs = read_json(full_json_path);
    database_root = insert(database_root, num_of_json, name_of_json, json_specs);

    // Third insertion of tree
    num_of_json = 4239;
    name_of_json = malloc(sizeof(char *));
    strcpy(name_of_json, "buy.net//4239");
    full_json_path = "../../dataset/camera_specs/2013_camera_specs/buy.net/4239.json";
    json_specs = read_json(full_json_path);
    database_root = insert(database_root, num_of_json, name_of_json, json_specs);

    // Forth insertion of tree
    num_of_json = 5449;
    name_of_json = malloc(sizeof(char *));
    strcpy(name_of_json, "www.alibaba.com//5449");
    full_json_path = "../../dataset/camera_specs/2013_camera_specs/www.alibaba.com/5449.json";
    json_specs = read_json(full_json_path);
    database_root = insert(database_root, num_of_json, name_of_json, json_specs);

    // Fifth insertion of tree
    num_of_json = 5;
    name_of_json = malloc(sizeof(char *));
    strcpy(name_of_json, "www.cambuy.com.au//5");
    full_json_path = "../../dataset/camera_specs/2013_camera_specs/www.cambuy.com.au/5.json";
    json_specs = read_json(full_json_path);
    database_root = insert(database_root, num_of_json, name_of_json, json_specs);

    // Search the jsons in the tree
    entry1 = search(database_root, "buy.net//4239");
    entry2 = search(database_root, "www.alibaba.com//5449");

    // Testing if the json of entry1 is the 4239
    TEST_CHECK(entry1->json == 4239);
    TEST_MSG("Expected: %d", TRUE);
    TEST_MSG("Produced: %d", entry1->json == 4239);

    // Testing if the path_json of entry2 is "www.alibaba.com//5449"
    cm = compare(entry2->path_with_JSON, "www.alibaba.com//5449");
    TEST_CHECK(cm == 3);
    TEST_MSG("Expected: %d", 3);
    TEST_MSG("Produced: %d", cm);

}

// Testing the function insert_entry in w_handler.c
void test_insert_entry(void){
    tree_entry *database_root = NULL;
    char *json_specs;
    int ht = 0;
    int num_of_json  = 0; 
    char *name_of_json;
    char *full_json_path;
    tree_entry *entry1 = NULL;
    tree_entry *entry2 = NULL;

    // First insertion of tree
    num_of_json = 4233;
    name_of_json = malloc(sizeof(char *));
    strcpy(name_of_json, "buy.net//4233");
    full_json_path = "../../dataset/camera_specs/2013_camera_specs/buy.net/4233.json";
    json_specs = read_json(full_json_path);
    database_root = insert(database_root, num_of_json, name_of_json, json_specs);

    // Second insertion of tree
    num_of_json = 4236;
    name_of_json = malloc(sizeof(char *));
    strcpy(name_of_json, "buy.net//4236");
    full_json_path = "../../dataset/camera_specs/2013_camera_specs/buy.net/4236.json";
    json_specs = read_json(full_json_path);
    database_root = insert(database_root, num_of_json, name_of_json, json_specs);

    // Third insertion of tree
    num_of_json = 4239;
    name_of_json = malloc(sizeof(char *));
    strcpy(name_of_json, "buy.net//4239");
    full_json_path = "../../dataset/camera_specs/2013_camera_specs/buy.net/4239.json";
    json_specs = read_json(full_json_path);
    database_root = insert(database_root, num_of_json, name_of_json, json_specs);

    // Forht insertion of tree
    num_of_json = 5449;
    name_of_json = malloc(sizeof(char *));
    strcpy(name_of_json, "www.alibaba.com//5449");
    full_json_path = "../../dataset/camera_specs/2013_camera_specs/www.alibaba.com/5449.json";
    json_specs = read_json(full_json_path);
    database_root = insert(database_root, num_of_json, name_of_json, json_specs);

    // Fifth insertion of tree
    num_of_json = 5;
    name_of_json = malloc(sizeof(char *));
    strcpy(name_of_json, "www.cambuy.com.au//5");
    full_json_path = "../../dataset/camera_specs/2013_camera_specs/www.cambuy.com.au/5.json";
    json_specs = read_json(full_json_path);
    database_root = insert(database_root, num_of_json, name_of_json, json_specs);

    // Search the jsons in the tree
    entry1 = search(database_root, "buy.net//4239");
    entry2 = search(database_root, "buy.net//4233");

    bucket *current_bucket_2 = entry2->headbucket->first_bucket;
    bucket *prev_bucket_2 = entry2->headbucket->first_bucket;
    bucket *current_bucket_1 = entry1->headbucket->first_bucket;

    // Find the last and the second last buckets of json2
    while (current_bucket_2->next_bucket != NULL)
    {
      prev_bucket_2 = current_bucket_2;
      current_bucket_2 = current_bucket_2->next_bucket;
    }
    // Find last bucket of json1 (where the entries will go)
    while (current_bucket_1->next_bucket != NULL)
    {
      current_bucket_1 = current_bucket_1->next_bucket;
    }
    // Add the last bucket entries of json2 bucketlist to json1 bucketlist
    for (int i = 0; i < current_bucket_2->numofentries; i++)
    {
       insert_entry(current_bucket_2->identical_entries[i], current_bucket_1);
    }

    // Checking if the identical_entries of 2 current_buckets are the same
    TEST_CHECK(current_bucket_1->identical_entries[current_bucket_1->numofentries] == current_bucket_2->identical_entries[current_bucket_2->numofentries]);
    TEST_MSG("Expected: %d", TRUE);
    TEST_MSG("Produced: %d", current_bucket_1->identical_entries[current_bucket_1->numofentries] == current_bucket_2->identical_entries[current_bucket_2->numofentries]);

}

// Testing the function add_positive_relation in w_handler.c
void test_add_positive_relation(void){

    tree_entry *database_root = NULL;
    char *json_specs;
    int ht = 0;
    int num_of_json  = 0; 
    char *name_of_json;
    char *full_json_path;
    tree_entry *entry1 = NULL;
    tree_entry *entry2 = NULL;

    // First insertion of tree
    num_of_json = 4233;
    name_of_json = malloc(sizeof(char *));
    strcpy(name_of_json, "buy.net//4233");
    full_json_path = "../../dataset/camera_specs/2013_camera_specs/buy.net/4233.json";
    json_specs = read_json(full_json_path);
    database_root = insert(database_root, num_of_json, name_of_json, json_specs);

    // Second insertion of tree
    num_of_json = 4236;
    name_of_json = malloc(sizeof(char *));
    strcpy(name_of_json, "buy.net//4236");
    full_json_path = "../../dataset/camera_specs/2013_camera_specs/buy.net/4236.json";
    json_specs = read_json(full_json_path);
    database_root = insert(database_root, num_of_json, name_of_json, json_specs);

    // Third insertion of tree
    num_of_json = 4239;
    name_of_json = malloc(sizeof(char *));
    strcpy(name_of_json, "buy.net//4239");
    full_json_path = "../../dataset/camera_specs/2013_camera_specs/buy.net/4239.json";
    json_specs = read_json(full_json_path);
    database_root = insert(database_root, num_of_json, name_of_json, json_specs);

    // Forth insertion of tree
    num_of_json = 5449;
    name_of_json = malloc(sizeof(char *));
    strcpy(name_of_json, "www.alibaba.com//5449");
    full_json_path = "../../dataset/camera_specs/2013_camera_specs/www.alibaba.com/5449.json";
    json_specs = read_json(full_json_path);
    database_root = insert(database_root, num_of_json, name_of_json, json_specs);

    // Fifth insertion of tree
    num_of_json = 5;
    name_of_json = malloc(sizeof(char *));
    strcpy(name_of_json, "www.cambuy.com.au//5");
    full_json_path = "../../dataset/camera_specs/2013_camera_specs/www.cambuy.com.au/5.json";
    json_specs = read_json(full_json_path);
    database_root = insert(database_root, num_of_json, name_of_json, json_specs);

    // Call add_realtion to test the function
    add_positive_relation(database_root,"buy.net//4239","www.alibaba.com//5449",1);
    add_positive_relation(database_root,"buy.net//4233","buy.net//4236",1);
    add_positive_relation(database_root,"buy.net//4236","www.alibaba.com//5449",0);
    add_positive_relation(database_root,"buy.net//4236","buy.net//4233",1);
    add_positive_relation(database_root,"www.cambuy.com.au//5","buy.net//4239",1);
    add_positive_relation(database_root,"www.cambuy.com.au//5","buy.net//4233",0);

    // Search the jsons in the tree
    entry1 = search(database_root, "buy.net//4239");
    entry2 = search(database_root, "www.alibaba.com//5449");

    // Check if the headbuckets of the entries are the same
    TEST_CHECK(entry1->headbucket == entry2->headbucket);
    TEST_MSG("Expected: %d", TRUE);
    TEST_MSG("Produced: %d", entry1->headbucket == entry2->headbucket);

    entry1 = NULL;
    entry2 = NULL;

    // Search the jsons in the tree
    entry1 = search(database_root, "buy.net//4233");
    entry2 = search(database_root, "www.alibaba.com//5449");

    // Check if the headbuckets of the entries are different
    TEST_CHECK(entry1->headbucket != entry2->headbucket);
    TEST_MSG("Expected: %d", TRUE);
    TEST_MSG("Produced: %d", entry1->headbucket != entry2->headbucket);

    entry1 = NULL;
    entry2 = NULL;

    // Search the jsons in the tree
    entry1 = search(database_root, "www.cambuy.com.au//5");
    entry2 = search(database_root, "www.alibaba.com//5449");

    // Check if the headbuckets of the entries are the same 
    TEST_CHECK(entry1->headbucket == entry2->headbucket);
    TEST_MSG("Expected: %d", TRUE);
    TEST_MSG("Produced: %d", entry1->headbucket == entry2->headbucket); 

    }

// Testing the function add_negative_relation in w_handler.c
void test_add_negative_relation(void){

    tree_entry *database_root = NULL;
    char *json_specs;
    int ht = 0;
    int num_of_json  = 0; 
    char *name_of_json;
    char *full_json_path;
    tree_entry *entry1 = NULL;
    tree_entry *entry2 = NULL;

    // First insertion of tree
    num_of_json = 4233;
    name_of_json = malloc(sizeof(char *));
    strcpy(name_of_json, "buy.net//4233");
    full_json_path = "../../dataset/camera_specs/2013_camera_specs/buy.net/4233.json";
    json_specs = read_json(full_json_path);
    database_root = insert(database_root, num_of_json, name_of_json, json_specs);

    // Second insertion of tree
    num_of_json = 4236;
    name_of_json = malloc(sizeof(char *));
    strcpy(name_of_json, "buy.net//4236");
    full_json_path = "../../dataset/camera_specs/2013_camera_specs/buy.net/4236.json";
    json_specs = read_json(full_json_path);
    database_root = insert(database_root, num_of_json, name_of_json, json_specs);

    // Third insertion of tree
    num_of_json = 4239;
    name_of_json = malloc(sizeof(char *));
    strcpy(name_of_json, "buy.net//4239");
    full_json_path = "../../dataset/camera_specs/2013_camera_specs/buy.net/4239.json";
    json_specs = read_json(full_json_path);
    database_root = insert(database_root, num_of_json, name_of_json, json_specs);

    // Forth insertion of tree
    num_of_json = 5449;
    name_of_json = malloc(sizeof(char *));
    strcpy(name_of_json, "www.alibaba.com//5449");
    full_json_path = "../../dataset/camera_specs/2013_camera_specs/www.alibaba.com/5449.json";
    json_specs = read_json(full_json_path);
    database_root = insert(database_root, num_of_json, name_of_json, json_specs);

    // Fifth insertion of tree
    num_of_json = 5;
    name_of_json = malloc(sizeof(char *));
    strcpy(name_of_json, "www.cambuy.com.au//5");
    full_json_path = "../../dataset/camera_specs/2013_camera_specs/www.cambuy.com.au/5.json";
    json_specs = read_json(full_json_path);
    database_root = insert(database_root, num_of_json, name_of_json, json_specs);

    // Call add_realtion to test the function
    add_negative_relation(database_root,"buy.net//4239","www.alibaba.com//5449",1);
    add_positive_relation(database_root,"buy.net//4239","www.alibaba.com//5449",1);
    add_negative_relation(database_root,"buy.net//4233","buy.net//4236",1);
    add_positive_relation(database_root,"buy.net//4233","buy.net//4236",1);
    add_negative_relation(database_root,"buy.net//4236","www.alibaba.com//5449",0);
    add_negative_relation(database_root,"buy.net//4236","buy.net//4233",1);
    add_negative_relation(database_root,"www.cambuy.com.au//5","buy.net//4239",1);
    add_negative_relation(database_root,"www.cambuy.com.au//5","buy.net//4233",0);

    // Search the jsons in the tree
    entry1 = search(database_root, "buy.net//4236");
    entry2 = search(database_root, "www.alibaba.com//5449");

    // Check if the headbuckets of the entries are the same
    TEST_CHECK(entry1->headbucket->different_cliques_root != entry2->headbucket->different_cliques_root);
    TEST_MSG("Expected: %d", TRUE);
    TEST_MSG("Produced: %d", entry1->headbucket->different_cliques_root != entry2->headbucket->different_cliques_root);

    entry1 = NULL;
    entry2 = NULL;

    // Search the jsons in the tree
    entry1 = search(database_root, "buy.net//4233");
    entry2 = search(database_root, "buy.net//4236");

    // Check if the headbuckets of the entries are different
    TEST_CHECK(entry1->headbucket == entry2->headbucket);
    TEST_MSG("Expected: %d", TRUE);
    TEST_MSG("Produced: %d", entry1->headbucket == entry2->headbucket);

    entry1 = NULL;
    entry2 = NULL;

    // Search the jsons in the tree
    entry1 = search(database_root, "www.cambuy.com.au//5");
    entry2 = search(database_root, "buy.net//4236");

    // Check if the headbuckets of the entries are the same 
    TEST_CHECK(entry1->headbucket->different_cliques_root != entry2->headbucket->different_cliques_root);
    TEST_MSG("Expected: %d", TRUE);
    TEST_MSG("Produced: %d", entry1->headbucket->different_cliques_root != entry2->headbucket->different_cliques_root); 

    }

// Testing the function clique_tree_insert in struct.c 
void test_clique_tree_insert(void){
    tree_entry *database_root = NULL;
    char *json_specs;
    int ht = 0, bf = 0;
    int num_of_json  = 0; 
    char *name_of_json;
    char *full_json_path;
    tree_entry *entry1 = NULL;
    tree_entry *entry2 = NULL;

      // Creating a test tree
    // First insertion of tree
    num_of_json = 4233;
    name_of_json = malloc(sizeof(char *));
    strcpy(name_of_json, "buy.net//4233");
    full_json_path = "../../dataset/camera_specs/2013_camera_specs/buy.net/4233.json";
    json_specs = read_json(full_json_path);
    database_root = insert(database_root, num_of_json, name_of_json, json_specs);

    // Second insertion of tree
    num_of_json = 4236;
    name_of_json = malloc(sizeof(char *));
    strcpy(name_of_json, "buy.net//4236");
    full_json_path = "../../dataset/camera_specs/2013_camera_specs/buy.net/4236.json";
    json_specs = read_json(full_json_path);
    database_root = insert(database_root, num_of_json, name_of_json, json_specs);

    // Third insertion of tree
    num_of_json = 4239;
    name_of_json = malloc(sizeof(char *));
    strcpy(name_of_json, "buy.net//4239");
    full_json_path = "../../dataset/camera_specs/2013_camera_specs/buy.net/4239.json";
    json_specs = read_json(full_json_path);
    database_root = insert(database_root, num_of_json, name_of_json, json_specs);

    // Forth insertion of tree
    num_of_json = 5449;
    name_of_json = malloc(sizeof(char *));
    strcpy(name_of_json, "www.alibaba.com//5449");
    full_json_path = "../../dataset/camera_specs/2013_camera_specs/www.alibaba.com/5449.json";
    json_specs = read_json(full_json_path);
    database_root = insert(database_root, num_of_json, name_of_json, json_specs);
    
    // Search the jsons in the tree
    entry1 = search(database_root, "buy.net//4239");
    entry2 = search(database_root, "www.alibaba.com//5449");

    entry1->headbucket->different_cliques_root = clique_tree_insert(entry1->headbucket->different_cliques_root, entry2->headbucket);
    entry2->headbucket->different_cliques_root = clique_tree_insert(entry2->headbucket->different_cliques_root, entry1->headbucket);


    //Testing for BF of the tree
    bf = clique_tree_BF(entry1->headbucket->different_cliques_root);
    TEST_CHECK(clique_tree_BF(entry1->headbucket->different_cliques_root) == 0);
    TEST_MSG("Expected: %d", 0);
    TEST_MSG("Produced: %d", bf);

    //Testing for height of the tree
    ht = clique_tree_height(entry1->headbucket->different_cliques_root);
    TEST_CHECK(ht == 0);
    TEST_MSG("Expected: %d", 0);
    TEST_MSG("Produced: %d", ht);

    //Testing for BF of the tree
    bf = clique_tree_BF(entry2->headbucket->different_cliques_root);
    TEST_CHECK(clique_tree_BF(entry2->headbucket->different_cliques_root) == 0);
    TEST_MSG("Expected: %d", 0);
    TEST_MSG("Produced: %d", bf);

    //Testing for height of the tree
    ht = clique_tree_height(entry2->headbucket->different_cliques_root);
    TEST_CHECK(ht == 0);
    TEST_MSG("Expected: %d", 0);
    TEST_MSG("Produced: %d", ht);

    free(name_of_json);
    free_node(database_root);
}

// Testing the function clique_tree_search in struct.c 
void test_clique_tree_search(void){
    tree_entry *database_root = NULL;
    char *json_specs;
    int ht = 0;
    int c = 0;
    int num_of_json  = 0; 
    char *name_of_json;
    char *full_json_path;
    tree_entry *entry1 = NULL;
    tree_entry *entry2 = NULL;

    // First insertion of tree
    num_of_json = 4233;
    name_of_json = malloc(sizeof(char *));
    strcpy(name_of_json, "buy.net//4233");
    full_json_path = "../../dataset/camera_specs/2013_camera_specs/buy.net/4233.json";
    json_specs = read_json(full_json_path);
    database_root = insert(database_root, num_of_json, name_of_json, json_specs);

    // Second insertion of tree
    num_of_json = 4236;
    name_of_json = malloc(sizeof(char *));
    strcpy(name_of_json, "buy.net//4236");
    full_json_path = "../../dataset/camera_specs/2013_camera_specs/buy.net/4236.json";
    json_specs = read_json(full_json_path);
    database_root = insert(database_root, num_of_json, name_of_json, json_specs);

    // Third insertion of tree
    num_of_json = 4239;
    name_of_json = malloc(sizeof(char *));
    strcpy(name_of_json, "buy.net//4239");
    full_json_path = "../../dataset/camera_specs/2013_camera_specs/buy.net/4239.json";
    json_specs = read_json(full_json_path);
    database_root = insert(database_root, num_of_json, name_of_json, json_specs);

    // Forth insertion of tree
    num_of_json = 5449;
    name_of_json = malloc(sizeof(char *));
    strcpy(name_of_json, "www.alibaba.com//5449");
    full_json_path = "../../dataset/camera_specs/2013_camera_specs/www.alibaba.com/5449.json";
    json_specs = read_json(full_json_path);
    database_root = insert(database_root, num_of_json, name_of_json, json_specs);

    // Fifth insertion of tree
    num_of_json = 5;
    name_of_json = malloc(sizeof(char *));
    strcpy(name_of_json, "www.cambuy.com.au//5");
    full_json_path = "../../dataset/camera_specs/2013_camera_specs/www.cambuy.com.au/5.json";
    json_specs = read_json(full_json_path);
    database_root = insert(database_root, num_of_json, name_of_json, json_specs);

    // Call add_realtion to test the function
    add_negative_relation(database_root,"buy.net//4239","www.alibaba.com//5449",1);
    add_positive_relation(database_root,"buy.net//4239","www.alibaba.com//5449",1);
    add_negative_relation(database_root,"buy.net//4233","buy.net//4236",1);
    add_positive_relation(database_root,"buy.net//4233","buy.net//4236",1);
    add_negative_relation(database_root,"buy.net//4236","www.alibaba.com//5449",0);
    add_negative_relation(database_root,"buy.net//4236","buy.net//4233",1);
    add_negative_relation(database_root,"www.cambuy.com.au//5","buy.net//4239",1);
    add_negative_relation(database_root,"www.cambuy.com.au//5","buy.net//4233",0);

    // Search the jsons in the tree
    entry1 = search(database_root, "buy.net//4236");
    entry2 = search(database_root, "www.alibaba.com//5449");

    clique_tree_entry *negative_relation_entry1 = clique_tree_search(entry1->headbucket->different_cliques_root, entry2->headbucket->key);
    c = compare(entry2->headbucket->key, negative_relation_entry1->different_clique_headbucket->key);
    // Check if the headbuckets of the entries are the same
    TEST_CHECK(c == 3);
    TEST_MSG("Expected: %d", TRUE);
    TEST_MSG("Produced: %d", c);


    free(name_of_json);
    free_node(database_root);
}

// Testing the function print_all_relations in w_handler.c
void test_print_node_relations(void){
    tree_entry *database_root = NULL;
    char *json_specs;
    int num_of_json  = 0; 
    char *name_of_json;
    char *full_json_path;
    FILE *fp1;
    FILE *fp2;
    FILE *fp3;
    FILE *fp4;
    fp1 = fopen("Unit_test_pos.csv", "w+");
    fp2 = fopen("Unit_test_neg.csv", "w+");
    int diff;
    int line, col;

    // First insertion of tree
    num_of_json = 4233;
    name_of_json = malloc(sizeof(char *));
    strcpy(name_of_json, "buy.net//4233");
    full_json_path = "../../dataset/camera_specs/2013_camera_specs/buy.net/4233.json";
    json_specs = read_json(full_json_path);
    database_root = insert(database_root, num_of_json, name_of_json, json_specs);

    // Second insertion of tree
    num_of_json = 4236;
    name_of_json = malloc(sizeof(char *));
    strcpy(name_of_json, "buy.net//4236");
    full_json_path = "../../dataset/camera_specs/2013_camera_specs/buy.net/4236.json";
    json_specs = read_json(full_json_path);
    database_root = insert(database_root, num_of_json, name_of_json, json_specs);

    // Third insertion of tree
    num_of_json = 4239;
    name_of_json = malloc(sizeof(char *));
    strcpy(name_of_json, "buy.net//4239");
    full_json_path = "../../dataset/camera_specs/2013_camera_specs/buy.net/4239.json";
    json_specs = read_json(full_json_path);
    database_root = insert(database_root, num_of_json, name_of_json, json_specs);

    // Forth insertion of tree
    num_of_json = 5449;
    name_of_json = malloc(sizeof(char *));
    strcpy(name_of_json, "www.alibaba.com//5449");
    full_json_path = "../../dataset/camera_specs/2013_camera_specs/www.alibaba.com/5449.json";
    json_specs = read_json(full_json_path);
    database_root = insert(database_root, num_of_json, name_of_json, json_specs);

    // Fifth insertion of tree
    num_of_json = 5;
    name_of_json = malloc(sizeof(char *));
    strcpy(name_of_json, "www.cambuy.com.au//5");
    full_json_path = "../../dataset/camera_specs/2013_camera_specs/www.cambuy.com.au/5.json";
    json_specs = read_json(full_json_path);
    database_root = insert(database_root, num_of_json, name_of_json, json_specs);

// Call add_positive_realtion to test the function
    add_positive_relation(database_root,"buy.net//4239","www.alibaba.com//5449",1);
    add_positive_relation(database_root,"buy.net//4233","buy.net//4236",1);
    add_positive_relation(database_root,"buy.net//4236","www.alibaba.com//5449",0);
    add_positive_relation(database_root,"buy.net//4236","buy.net//4233",1);
    add_positive_relation(database_root,"www.cambuy.com.au//5","buy.net//4239",1);
    add_positive_relation(database_root,"www.cambuy.com.au//5","buy.net//4233",0);

    // Call add_negative_realtion to test the function
    add_negative_relation(database_root,"buy.net//4239","www.alibaba.com//5449",1);
    add_negative_relation(database_root,"buy.net//4233","buy.net//4236",1);
    add_negative_relation(database_root,"buy.net//4236","www.alibaba.com//5449",0);
    add_negative_relation(database_root,"buy.net//4236","buy.net//4233",1);
    add_negative_relation(database_root,"www.cambuy.com.au//5","buy.net//4239",1);
    add_negative_relation(database_root,"www.cambuy.com.au//5","buy.net//4233",0);


    // Call print_all_relations to write a .csv file 
    print_all_positive_relations(database_root, fp1);
    print_all_negative_relations(database_root, fp2);
    fclose(fp1);
    fclose(fp2);

    // Preparation of the comparison of 2 .csv files 
    fp1 = fopen("Unit_test_pos.csv", "r");        // open the already written .csv file
    fp3 = fopen("test_pos.csv", "r");   // open the test .csv file
   
    // Call the helper_comparison of 2 .csv files
    diff = helper_compareFile(fp1, fp3, &line, &col);

    fclose(fp1);
    fclose(fp3);

    //Testing if the files are the same
    TEST_CHECK(diff == 0);
    TEST_MSG("Expected: %d", 0);
    TEST_MSG("Produced: %d", diff);


    fp2 = fopen("Unit_test_neg.csv", "r");         // open the already written .csv file
    fp4 = fopen("test_neg.csv", "r");              // open the test .csv file
 
    // Call the helper_comparison of 2 .csv files
    diff = helper_compareFile(fp2, fp4, &line, &col);

    fclose(fp2);
    fclose(fp4);

    //Testing if the files are the same
    TEST_CHECK(diff == 0);
    TEST_MSG("Expected: %d", 0);
    TEST_MSG("Produced: %d", diff);
}

void test_create_bow_tree(void){

    tree_entry *database_root = NULL;
    char *json_specs;
    int ht = 0;
    int num_of_json  = 0; 
    char *name_of_json;
    char *full_json_path;
    tree_entry *entry1 = NULL;
    tree_entry *entry2 = NULL;
    int num_of_test;
    // Bow stuff
    int** bow_array;

    // First insertion of tree
    num_of_json = 4233;
    name_of_json = malloc(sizeof(char *));
    strcpy(name_of_json, "buy.net//4233");
    full_json_path = "../../dataset/camera_specs/2013_camera_specs/buy.net/4233.json";
    json_specs = read_json(full_json_path);
    database_root = insert(database_root, num_of_json, name_of_json, json_specs);

    // Second insertion of tree
    num_of_json = 4236;
    name_of_json = malloc(sizeof(char *));
    strcpy(name_of_json, "buy.net//4236");
    full_json_path = "../../dataset/camera_specs/2013_camera_specs/buy.net/4236.json";
    json_specs = read_json(full_json_path);
    database_root = insert(database_root, num_of_json, name_of_json, json_specs);

    // Third insertion of tree
    num_of_json = 4239;
    name_of_json = malloc(sizeof(char *));
    strcpy(name_of_json, "buy.net//4239");
    full_json_path = "../../dataset/camera_specs/2013_camera_specs/buy.net/4239.json";
    json_specs = read_json(full_json_path);
    database_root = insert(database_root, num_of_json, name_of_json, json_specs);

    // Forth insertion of tree
    num_of_json = 5449;
    name_of_json = malloc(sizeof(char *));
    strcpy(name_of_json, "www.alibaba.com//5449");
    full_json_path = "../../dataset/camera_specs/2013_camera_specs/www.alibaba.com/5449.json";
    json_specs = read_json(full_json_path);
    database_root = insert(database_root, num_of_json, name_of_json, json_specs);

    // Fifth insertion of tree
    num_of_json = 5;
    name_of_json = malloc(sizeof(char *));
    strcpy(name_of_json, "www.cambuy.com.au//5");
    full_json_path = "../../dataset/camera_specs/2013_camera_specs/www.cambuy.com.au/5.json";
    json_specs = read_json(full_json_path);
    database_root = insert(database_root, num_of_json, name_of_json, json_specs);

    // Call add_positive_realtion to test the function
    add_positive_relation(database_root,"buy.net//4239","www.alibaba.com//5449",1);
    add_positive_relation(database_root,"buy.net//4233","buy.net//4236",1);
    add_positive_relation(database_root,"buy.net//4236","www.alibaba.com//5449",0);
    add_positive_relation(database_root,"buy.net//4236","buy.net//4233",1);
    add_positive_relation(database_root,"www.cambuy.com.au//5","buy.net//4239",1);
    add_positive_relation(database_root,"www.cambuy.com.au//5","buy.net//4233",0);

    // Call add_negative_realtion to test the function
    add_negative_relation(database_root,"buy.net//4239","www.alibaba.com//5449",1);
    add_negative_relation(database_root,"buy.net//4233","buy.net//4236",1);
    add_negative_relation(database_root,"buy.net//4236","www.alibaba.com//5449",0);
    add_negative_relation(database_root,"buy.net//4236","buy.net//4233",1);
    add_negative_relation(database_root,"www.cambuy.com.au//5","buy.net//4239",1);
    add_negative_relation(database_root,"www.cambuy.com.au//5","buy.net//4233",0);

    bow_array = create_bow_array(database_root);
    num_of_test = bow_array[446][4];
    
    //Testing if the function in Unit testing have the same results with the original
    TEST_CHECK(num_of_test == 9);
    TEST_MSG("Expected: %d", TRUE);
    TEST_MSG("Produced: %d", num_of_test);
    
    }

void test_create_tf_idf(void){

    tree_entry *database_root = NULL;
    char *json_specs;
    int ht = 0;
    int num_of_json  = 0; 
    char *name_of_json;
    char *full_json_path;
    tree_entry *entry1 = NULL;
    tree_entry *entry2 = NULL;
    float num_of_test;
    // Bow stuff
    int** bow_array;
    float** tf_idf_array;

    int json_total_words[5];   //num of words for every json 
    int jsons_including_word_array[449]; //num of jsons that every word appears in atleast once   
    int cur_word = 0;
    int cur_json = 0;
    float tf;
    float idf;

    // First insertion of tree
    num_of_json = 4233;
    name_of_json = malloc(sizeof(char *));
    strcpy(name_of_json, "buy.net//4233");
    full_json_path = "../../dataset/camera_specs/2013_camera_specs/buy.net/4233.json";
    json_specs = read_json(full_json_path);
    database_root = insert(database_root, num_of_json, name_of_json, json_specs);

    // Second insertion of tree
    num_of_json = 4236;
    name_of_json = malloc(sizeof(char *));
    strcpy(name_of_json, "buy.net//4236");
    full_json_path = "../../dataset/camera_specs/2013_camera_specs/buy.net/4236.json";
    json_specs = read_json(full_json_path);
    database_root = insert(database_root, num_of_json, name_of_json, json_specs);

    // Third insertion of tree
    num_of_json = 4239;
    name_of_json = malloc(sizeof(char *));
    strcpy(name_of_json, "buy.net//4239");
    full_json_path = "../../dataset/camera_specs/2013_camera_specs/buy.net/4239.json";
    json_specs = read_json(full_json_path);
    database_root = insert(database_root, num_of_json, name_of_json, json_specs);

    // Forth insertion of tree
    num_of_json = 5449;
    name_of_json = malloc(sizeof(char *));
    strcpy(name_of_json, "www.alibaba.com//5449");
    full_json_path = "../../dataset/camera_specs/2013_camera_specs/www.alibaba.com/5449.json";
    json_specs = read_json(full_json_path);
    database_root = insert(database_root, num_of_json, name_of_json, json_specs);

    // Fifth insertion of tree
    num_of_json = 5;
    name_of_json = malloc(sizeof(char *));
    strcpy(name_of_json, "www.cambuy.com.au//5");
    full_json_path = "../../dataset/camera_specs/2013_camera_specs/www.cambuy.com.au/5.json";
    json_specs = read_json(full_json_path);
    database_root = insert(database_root, num_of_json, name_of_json, json_specs);

    // Call add_positive_realtion to test the function
    add_positive_relation(database_root,"buy.net//4239","www.alibaba.com//5449",1);
    add_positive_relation(database_root,"buy.net//4233","buy.net//4236",1);
    add_positive_relation(database_root,"buy.net//4236","www.alibaba.com//5449",0);
    add_positive_relation(database_root,"buy.net//4236","buy.net//4233",1);
    add_positive_relation(database_root,"www.cambuy.com.au//5","buy.net//4239",1);
    add_positive_relation(database_root,"www.cambuy.com.au//5","buy.net//4233",0);

    // Call add_negative_realtion to test the function
    add_negative_relation(database_root,"buy.net//4239","www.alibaba.com//5449",1);
    add_negative_relation(database_root,"buy.net//4233","buy.net//4236",1);
    add_negative_relation(database_root,"buy.net//4236","www.alibaba.com//5449",0);
    add_negative_relation(database_root,"buy.net//4236","buy.net//4233",1);
    add_negative_relation(database_root,"www.cambuy.com.au//5","buy.net//4239",1);
    add_negative_relation(database_root,"www.cambuy.com.au//5","buy.net//4233",0);

    bow_array = create_bow_array(database_root);
    tf_idf_array = create_tf_idf(bow_array);

    // Process the vars=val into function of tf_idf
    for (int cur_json = 0; cur_json < 5; cur_json++){
        json_total_words[cur_json] = 0;
    }   
    //fill the arrays above^^
    for (cur_word = 0; cur_word < 449; cur_word++){
        jsons_including_word_array[cur_word] = 0;
        for (cur_json = 0; cur_json < 5; cur_json++){
            if (bow_array[cur_word][cur_json]>0){
                jsons_including_word_array[cur_word] += 1 ;
                // printf("%d\n",bow_array[cur_word][cur_json]);
                json_total_words[cur_json] += bow_array[cur_word][cur_json];
                // printf("%d\n\n",json_total_words[cur_json]);
            }
        }
    }
    idf = log10f(((float)(5))/((float)(jsons_including_word_array[446])));
    if (bow_array[446][0] == 0){
        tf = 0;
    }
    else 
        tf = (float)bow_array[446][0]/(float)json_total_words[0];

    num_of_test = tf*idf;

    //Testing if the function in Unit testing have the same results with the original
    TEST_CHECK(num_of_test == tf_idf_array[446][0]);
    TEST_MSG("Expected: %d", TRUE);
    TEST_MSG("Produced: %lf", num_of_test);
    
    }


void test_create_train_set_bow(void){

    tree_entry *database_root = NULL;
    char *json_specs;
    int ht = 0;
    int num_of_json  = 0; 
    char *name_of_json;
    char *full_json_path;
    tree_entry *entry1 = NULL;
    tree_entry *entry2 = NULL;
    FILE *fp1;
    FILE *fp2;
    int diff;
    int line, col;
    char *positive_relations = "test_pos.csv";
    char *negative_relations = "test_neg.csv";
    // Bow stuff
    int** bow_array;

    // First insertion of tree
    num_of_json = 4233;
    name_of_json = malloc(sizeof(char *));
    strcpy(name_of_json, "buy.net//4233");
    full_json_path = "../../dataset/camera_specs/2013_camera_specs/buy.net/4233.json";
    json_specs = read_json(full_json_path);
    database_root = insert(database_root, num_of_json, name_of_json, json_specs);

    // Second insertion of tree
    num_of_json = 4236;
    name_of_json = malloc(sizeof(char *));
    strcpy(name_of_json, "buy.net//4236");
    full_json_path = "../../dataset/camera_specs/2013_camera_specs/buy.net/4236.json";
    json_specs = read_json(full_json_path);
    database_root = insert(database_root, num_of_json, name_of_json, json_specs);

    // Third insertion of tree
    num_of_json = 4239;
    name_of_json = malloc(sizeof(char *));
    strcpy(name_of_json, "buy.net//4239");
    full_json_path = "../../dataset/camera_specs/2013_camera_specs/buy.net/4239.json";
    json_specs = read_json(full_json_path);
    database_root = insert(database_root, num_of_json, name_of_json, json_specs);

    // Forth insertion of tree
    num_of_json = 5449;
    name_of_json = malloc(sizeof(char *));
    strcpy(name_of_json, "www.alibaba.com//5449");
    full_json_path = "../../dataset/camera_specs/2013_camera_specs/www.alibaba.com/5449.json";
    json_specs = read_json(full_json_path);
    database_root = insert(database_root, num_of_json, name_of_json, json_specs);

    // Fifth insertion of tree
    num_of_json = 5;
    name_of_json = malloc(sizeof(char *));
    strcpy(name_of_json, "www.cambuy.com.au//5");
    full_json_path = "../../dataset/camera_specs/2013_camera_specs/www.cambuy.com.au/5.json";
    json_specs = read_json(full_json_path);
    database_root = insert(database_root, num_of_json, name_of_json, json_specs);

    // Call add_positive_realtion to test the function
    add_positive_relation(database_root,"buy.net//4239","www.alibaba.com//5449",1);
    add_positive_relation(database_root,"buy.net//4233","buy.net//4236",1);
    add_positive_relation(database_root,"buy.net//4236","www.alibaba.com//5449",0);
    add_positive_relation(database_root,"buy.net//4236","buy.net//4233",1);
    add_positive_relation(database_root,"www.cambuy.com.au//5","buy.net//4239",1);
    add_positive_relation(database_root,"www.cambuy.com.au//5","buy.net//4233",0);

    // Call add_negative_realtion to test the function
    add_negative_relation(database_root,"buy.net//4239","www.alibaba.com//5449",1);
    add_negative_relation(database_root,"buy.net//4233","buy.net//4236",1);
    add_negative_relation(database_root,"buy.net//4236","www.alibaba.com//5449",0);
    add_negative_relation(database_root,"buy.net//4236","buy.net//4233",1);
    add_negative_relation(database_root,"www.cambuy.com.au//5","buy.net//4239",1);
    add_negative_relation(database_root,"www.cambuy.com.au//5","buy.net//4233",0);

    fp1 = fopen(positive_relations, "r");
    fp2 = fopen(negative_relations, "r");

    bow_array = create_bow_array(database_root);
    create_train_set_bow(bow_array, database_root, positive_relations, negative_relations);

    fclose(fp1);
    fclose(fp2);

    fp1 = fopen("Train_Set.csv", "r");
    fp2 = fopen("test_Train_Set_b.csv", "r");

    diff = helper_compareFile(fp1, fp2, &line, &col);

    fclose(fp1);
    fclose(fp2);

    //Testing if the files are the same
    TEST_CHECK(diff == 0);
    TEST_MSG("Expected: %d", 0);
    TEST_MSG("Produced: %d", diff);
    
    }

void test_create_train_set_tfidf(void){

    tree_entry *database_root = NULL;
    char *json_specs;
    int ht = 0;
    int num_of_json  = 0; 
    char *name_of_json;
    char *full_json_path;
    tree_entry *entry1 = NULL;
    tree_entry *entry2 = NULL;
    FILE *fp1;
    FILE *fp2;
    int diff;
    int line, col;
    char *positive_relations = "test_pos.csv";
    char *negative_relations = "test_neg.csv";
    // Bow stuff
    int** bow_array;
    float** tf_idf_array;

    // First insertion of tree
    num_of_json = 4233;
    name_of_json = malloc(sizeof(char *));
    strcpy(name_of_json, "buy.net//4233");
    full_json_path = "../../dataset/camera_specs/2013_camera_specs/buy.net/4233.json";
    json_specs = read_json(full_json_path);
    database_root = insert(database_root, num_of_json, name_of_json, json_specs);

    // Second insertion of tree
    num_of_json = 4236;
    name_of_json = malloc(sizeof(char *));
    strcpy(name_of_json, "buy.net//4236");
    full_json_path = "../../dataset/camera_specs/2013_camera_specs/buy.net/4236.json";
    json_specs = read_json(full_json_path);
    database_root = insert(database_root, num_of_json, name_of_json, json_specs);

    // Third insertion of tree
    num_of_json = 4239;
    name_of_json = malloc(sizeof(char *));
    strcpy(name_of_json, "buy.net//4239");
    full_json_path = "../../dataset/camera_specs/2013_camera_specs/buy.net/4239.json";
    json_specs = read_json(full_json_path);
    database_root = insert(database_root, num_of_json, name_of_json, json_specs);

    // Forth insertion of tree
    num_of_json = 5449;
    name_of_json = malloc(sizeof(char *));
    strcpy(name_of_json, "www.alibaba.com//5449");
    full_json_path = "../../dataset/camera_specs/2013_camera_specs/www.alibaba.com/5449.json";
    json_specs = read_json(full_json_path);
    database_root = insert(database_root, num_of_json, name_of_json, json_specs);

    // Fifth insertion of tree
    num_of_json = 5;
    name_of_json = malloc(sizeof(char *));
    strcpy(name_of_json, "www.cambuy.com.au//5");
    full_json_path = "../../dataset/camera_specs/2013_camera_specs/www.cambuy.com.au/5.json";
    json_specs = read_json(full_json_path);
    database_root = insert(database_root, num_of_json, name_of_json, json_specs);

    // Call add_positive_realtion to test the function
    add_positive_relation(database_root,"buy.net//4239","www.alibaba.com//5449",1);
    add_positive_relation(database_root,"buy.net//4233","buy.net//4236",1);
    add_positive_relation(database_root,"buy.net//4236","www.alibaba.com//5449",0);
    add_positive_relation(database_root,"buy.net//4236","buy.net//4233",1);
    add_positive_relation(database_root,"www.cambuy.com.au//5","buy.net//4239",1);
    add_positive_relation(database_root,"www.cambuy.com.au//5","buy.net//4233",0);

    // Call add_negative_realtion to test the function
    add_negative_relation(database_root,"buy.net//4239","www.alibaba.com//5449",1);
    add_negative_relation(database_root,"buy.net//4233","buy.net//4236",1);
    add_negative_relation(database_root,"buy.net//4236","www.alibaba.com//5449",0);
    add_negative_relation(database_root,"buy.net//4236","buy.net//4233",1);
    add_negative_relation(database_root,"www.cambuy.com.au//5","buy.net//4239",1);
    add_negative_relation(database_root,"www.cambuy.com.au//5","buy.net//4233",0);


    fp1 = fopen(positive_relations, "r");
    fp2 = fopen(negative_relations, "r");

    bow_array = create_bow_array(database_root);
    tf_idf_array = create_tf_idf(bow_array);
    create_train_set_tfidf(tf_idf_array, database_root, positive_relations, negative_relations);
    
    fclose(fp1);
    fclose(fp2);

    fp1 = fopen("Train_Set.csv", "r");
    fp2 = fopen("test_Train_Set_f.csv", "r");

    diff = helper_compareFile(fp1, fp2, &line, &col);

    fclose(fp1);
    fclose(fp2);

    //Testing if the files are the same
    TEST_CHECK(diff == 0);
    TEST_MSG("Expected: %d", 0);
    TEST_MSG("Produced: %d", diff);
    
    }

// A list of the testing functions
TEST_LIST = {
    { "compare", test_compare },
    { "height", test_height },
    { "BF", test_BF },
    { "All_json_Values", test_All_json_Values },
    { "insert", test_insert },
    { "insert_entry", test_insert_entry },
    { "search", test_search },
    { "add_positive_relation", test_add_positive_relation },
    { "add_negative_relation", test_add_negative_relation },
    { "clique_tree_insert", test_clique_tree_insert},
    { "clique_tree_search", test_clique_tree_search},
    { "print_node_relations", test_print_node_relations },
    { "create_bow_tree", test_create_bow_tree },  
    { "create_tf_idf", test_create_tf_idf },
    { "create_train_set_bow", test_create_train_set_bow },
    { "create_train_set_tfidf", test_create_train_set_tfidf },
    { NULL, NULL }
};

