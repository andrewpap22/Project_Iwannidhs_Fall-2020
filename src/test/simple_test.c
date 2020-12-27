#include <stdio.h>
#include <string.h>
#include "../external/acutest.h"    
#include "../headers/structs.h"
#include "../headers/W_handler.h"
#include "../headers/json_parser.h"
#include "../headers/includes_for_parser.h"
#include "../headers/train_set_handler.h"


#define NUMOFENTRIES 29787
#define NUMOFWORDS 79782

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
    char* str = "Polaroid Is426 16 Megapixel Compact Camera - Red - 2.4\\\" Lcd - 4x Optical Zoom - Pictbridge IS426RED Price Comparison at Buy.net Polaroid Yes Scene Modes: Portrait Night Auto No No 1 B00DJGZIU4 Yes iS426 No";

    // First Test
    // Give the path with the json file that we are going to compare with the static variable
    full_json_path = "../../dataset/camera_specs/2013_camera_specs/buy.net/4236.json";

    // Call the function read_json
    //json_str = All_json_Values();
    json_specs = All_json_Values(full_json_path);
    printf("\n");
    printf("%s\n", json_specs);
    printf("\n");
    printf("%s\n", str);

    // Compare the static string with the result of the testing function - they have to be same
    cm = compare(str,json_specs);
    TEST_CHECK(cm == 3);
    TEST_MSG("Expected: %d", 3);
    TEST_MSG("Produced: %d", cm);

    // Second Test
    // Testing the length of the 2 strings - they must have the same length
    len1 = strlen(str);
    len2 = strlen(json_specs);
    printf("str %d\n", len1 );
    printf("json_specs %d\n", len2 );

    TEST_CHECK(len1 == len2);
    TEST_MSG("Expected: %d", TRUE);
    TEST_MSG("Produced: %d", len1 == len2);

    // Third Test
    // Give the path with the json file that we are going to compare with the static variable
    full_json_path = "../../dataset/camera_specs/2013_camera_specs/buy.net/4233.json";

    // Call the function read_json
    json_specs = read_json(full_json_path);

    // Compare the static string with the result of the testing function - they have to be different 
    cm = compare(str,json_specs);
    TEST_CHECK(cm == 1);
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
/*void test_print_all_relations(void){
    tree_entry *database_root = NULL;
    char *json_specs;
    int num_of_json  = 0; 
    char *name_of_json;
    char *full_json_path;
    FILE *fp1;
    FILE *fp2;
    FILE *fp3;
    fp1 = fopen("Unit_test.csv", "w+");
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

    // Call add_relation to relate the json entries
    add_relation(database_root,"buy.net//4239","www.alibaba.com//5449",1);
    add_relation(database_root,"buy.net//4233","buy.net//4236",1);
    add_relation(database_root,"buy.net//4236","www.alibaba.com//5449",0);
    add_relation(database_root,"buy.net//4236","buy.net//4233",1);
    add_relation(database_root,"www.cambuy.com.au//5","buy.net//4239",1);
    add_relation(database_root,"www.cambuy.com.au//5","buy.net//4233",0);

    // Call print_all_relations to write a .csv file 
    fprintf(fp1, "left_spec_id,right_spec_id\n");
    print_all_relations(database_root, fp1);
    fclose(fp1);

    // Preparation of the comparison of 2 .csv files 
    fp2 = fopen("Unit_test.csv", "r");        // open the already written .csv file
    fp3 = fopen("Unit_test_byme.csv", "r");   // open the test .csv file
    
    // Call the helper_comparison of 2 .csv files
    diff = helper_compareFile(fp2, fp3, &line, &col);

    fclose(fp2);
    fclose(fp3);

    // Testing if the files are the same
    TEST_CHECK(diff == 0);
    TEST_MSG("Expected: %d", 0);
    TEST_MSG("Produced: %d", diff);
} */


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
   /* { "print_all_relations", test_print_all_relations },*/
    { NULL, NULL }
};

