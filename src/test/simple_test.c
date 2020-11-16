#include <stdio.h>
#include <string.h>
#include "../external/acutest.h"	
#include "../headers/structs.h"
#include "../headers/W_handler.h"

// function only for help the Unit Testing
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


    /* If both files have reached end */
    if (ch1 == EOF && ch2 == EOF)
        return 0;
    else
        return -1;
};

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

    //find the jsons in the tree
    entry1 = search(database_root, "buy.net//4239");
    entry2 = search(database_root, "buy.net//4233");

    bucket *current_bucket_2 = entry2->headbucket->first_bucket;
    bucket *prev_bucket_2 = entry2->headbucket->first_bucket;
    bucket *current_bucket_1 = entry1->headbucket->first_bucket;

    //find the last and the second last buckets of json2
    while (current_bucket_2->next_bucket != NULL)
    {
      prev_bucket_2 = current_bucket_2;
      current_bucket_2 = current_bucket_2->next_bucket;
    }
    //Find last bucket of json1 (where the entries will go)
    while (current_bucket_1->next_bucket != NULL)
    {
      current_bucket_1 = current_bucket_1->next_bucket;
    }
    //add the last bucket entries of json2 bucketlist to json1 bucketlist
    for (int i = 0; i < current_bucket_2->numofentries; i++)
    {
       insert_entry(current_bucket_2->identical_entries[i], current_bucket_1);
    }

    TEST_CHECK(current_bucket_1->identical_entries[current_bucket_1->numofentries] == current_bucket_2->identical_entries[current_bucket_2->numofentries]);
    TEST_MSG("Expected: %d", TRUE);
    TEST_MSG("Produced: %d", current_bucket_1->identical_entries[current_bucket_1->numofentries] == current_bucket_2->identical_entries[current_bucket_2->numofentries]);

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

void test_print_all_relations(void){
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

    fprintf(fp1, "left_spec_id,right_spec_id\n");
    print_all_relations(database_root, fp1);
    fclose(fp1);

    fp2 = fopen("Unit_test.csv", "r"); // open the already written .csv file
    fp3 = fopen("Unit_test_byme.csv", "r"); // open the test .csv file
    
    diff = helper_compareFile(fp2, fp3, &line, &col);

    fclose(fp2);
    fclose(fp3);

    TEST_CHECK(diff == 0);
    TEST_MSG("Expected: %d", 0);
    TEST_MSG("Produced: %d", diff);
}



TEST_LIST = {
    { "compare", test_compare },
    { "height", test_height },
    { "BF", test_BF },
    { "read_json", test_read_json },
    { "insert", test_insert },
    { "insert_entry", test_insert_entry },
    { "search", test_search },
    { "add_relation", test_add_relation },
    { "print_all_relations", test_print_all_relations },
    { NULL, NULL }
};

