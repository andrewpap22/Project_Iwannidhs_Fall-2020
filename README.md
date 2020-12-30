# Information Systems Project 
### Fall 2020 - 2021 
[![Open Source](https://badges.frapsoft.com/os/v1/open-source.svg?v=103)](https://opensource.org/)

<hr>

### 📁 Project File Structure

<ul>
  <li>
    <a href="https://github.com/andrewpap22/Project_Iwannidhs_Fall-2020/tree/master/dataset">📂 Dataset</a>
    <ul>
      <li>
        <a href="https://github.com/andrewpap22/Project_Iwannidhs_Fall-2020/tree/master/dataset/camera_specs/2013_camera_specs">📂 camera_specs</a>
      </li>
    </ul>
    <p>📄 sigmod_large_labelled_dataset.csv</p>
    <p>📄 sigmod_medium_labelled_dataset.csv</p>
  </li>
  <li>
    <a href="https://github.com/andrewpap22/Project_Iwannidhs_Fall-2020/tree/master/src">📂 src</a>
    <ul>
      <li>
        <a href="https://github.com/andrewpap22/Project_Iwannidhs_Fall-2020/tree/master/src/dot-C_files">📂 dot-C_files</a>
      </li>
      <li>
        <a href="https://github.com/andrewpap22/Project_Iwannidhs_Fall-2020/tree/master/src/external">📂 external</a>
      </li>
      <li>
        <a href="https://github.com/andrewpap22/Project_Iwannidhs_Fall-2020/tree/master/src/headers">📂 headers</a>
      </li>
      <li>
        <a href="https://github.com/andrewpap22/Project_Iwannidhs_Fall-2020/tree/master/src/test">📂 test</a>
      </li>
    </ul>
    <p>📄 makefile</p>
    <p>📄 project.c</p>
    <p>📄 output.csv</p>
  </li>
  <li>
    <a href="https://github.com/andrewpap22/Project_Iwannidhs_Fall-2020/tree/master/valgrind_output">📂 valgrind_output</a>
  </li>
</ul>

<hr>

### Compilation: 
```
$ make
``` 

### Execution:
```
$ ./project2 ../dataset/sigmod_large_labelled_dataset.csv

  or

$ ./project2 ../dataset/sigmod_medium_labelled_dataset.csv  
```

**(Execution time on large dataset = 3sec)**

To delete binary files: 
```
$ make clean
```

--------------------------------

## Project1 Analysis: 

First of all, this project uses the libjson-c-dev library, so you need to install it on your system by providing
(**for ubuntu systems**) :
```
$ sudo apt install libjson-c-dev
```
For non ubuntu systems adjust accordingly, <a href="https://github.com/json-c/json-c">Info.</a>

<hr>

*The whole project is implemented in a Linux operating system (Ubuntu 20.04) and the compiler used is (gcc version (Ubuntu 9.3.0-17ubuntu1~20.04) 9.3.0)* <br><br>
The data structure that is used on this 1st project is a binary search tree whose nodes consists of linked lists of buckets. <br>
The program at first opens the dataset directory where the camera specs are located and for each and every subdirectory it opens it and searches and opens each and every one of the json files. <br> Afterwards we insert each and every of the json files inside the 1st tree node (i.e. bucket) and when the 1st bucket is full of json files we allocate proper memory from the heap to create a new bucket to insert the remaining json files. <br>  
The above operation described is dynamic (not hardcoded), and that means that it will keep adding json files by creating the linked list of buckets on each and every node of the tree based on the total json files that are provided to the application. <br> After we're done and all the files are inserted we're deallocating the memory memory that we have previously located from the heap! <br><br>
Our program, checks (as requested from the project description) the files with each other and 'prints' into a .csv file the relation of each and every file with each other, (i.e. all the json files that are the same with each other based on the specs that are contained inside). 

<hr>

## Details

Following the path: <br>
**src** ~> **dot-C_files** ~> *W_handler.c* <br>
We have: 
```C++
void insert_entry(tree_entry *entry, bucket* first_bucket);
```
who's responsible for adding the pointers (relations) inside the buckets of the tree. <br>
```C++
void add_relation(tree_entry* root, char* json1, char* json2, int relation);
```
who's responsible for comparing the specs of the .json files and add their relation *(the ones that are the same)* to our linked list of buckets. <br>
```C++
void print_all_relations(tree_entry *,FILE*);
```
who's responsible for printing out into the .csv all the specs that consist of the same commodity. <br><br>

Inside: <br>
**src** ~> **dot-C_files** ~> *structs.c* <br>
We have implemented our data structures described above and whatever helper function we needed and they consist of the following: <br>

- Helper function that compares our string to be inserted in the tree
  - *returns 0 if a is smaller, 1 if its bigger, 3 if they are the same (should never return 3)*
```C++
int compare(char* a, char* b);
```
- The data structures and their operations:
```C++
tree_entry *insert(tree_entry *T, int x, char *path_with_JSON, char* json_specs);
tree_entry *search(tree_entry *T, char* x);
tree_entry *Delete(tree_entry *T,int x);
int height(tree_entry *T);
tree_entry *rotateright(tree_entry *x);
tree_entry *rotateleft(tree_entry *x);
tree_entry *RR(tree_entry *T);
tree_entry *LL(tree_entry *T);
tree_entry *LR(tree_entry *T);
tree_entry *RL(tree_entry *T);
int BF(tree_entry *T);
void preorder(tree_entry *T);
void inorder(tree_entry *T);
void free_node(tree_entry *T);
```
- Helper Function to read and store the contents of the json files.
  - *It takes as input a .json file it parses the json object of each and every file and then converts it into a C string format, it stores that string by allocating proper memory (the size of each json object) and then stores it into our tree buckets*
```C++
char* read_json(char* json_filename);
```

## Unit Testing Part_1 & Part_2

Following the path: <br>
**src** ~> **test** ~> *simple_test.c* <br>
We have: 
```C++
void test_compare(void);
```
- responsible for testing the function compare. <br>
```C++
void test_height(void);
```
- responsible for testing the function height. <br>
```C++
void test_BF(void);
```
- responsible for testing the function BF. <br>
```C++
void test_read_json(void);
```
- responsible for testing the function updated-improved read_json. <br>
```C++
void test_insert(void);
```
- responsible for testing the function insert. <br>
```C++
void test_insert_entry(void);
```
- responsible for testing the function insert_entry. <br>
```C++
void test_search(void);
```
- responsible for testing the function search. <br>
```C++
void test_clique_tree_search(void);
```
- responsible for testing the function clique_tree_search. <br>
```C++
void test_clique_tree_insert(void);
```
- responsible for testing the function clique_tree_insert. <br>
```C++
void test_add_positive_relation(void);
```
- responsible for testing the function add_positive_relation. <br>
```C++
void test_add_negative_relation(void);
```
- responsible for testing the function add_negative_relation. <br>
```C++
void test_create_bow_tree(void);
```
- responsible for testing the function create_bow_tree. <br>
```C++
void test_create_tf_idf(void);
```
- responsible for testing the function create_tf_idf. <br>
```C++
void test_create_train_set_bow(void);
```
- responsible for testing the function create_train_set_bow. <br>
```C++
void test_create_train_set_tfidf(void);
```
- responsible for testing the function create_train_set_tfidf. <br>
```C++
void test_print_node_relations(void);
```
- responsible for testing the function print_all_positive/negative_relations. <br><br>


- Helper Function to compare 2 .csv files.
  - *It takes as input 2 .csv files and compare them char by char. Return 0 if the files are same and -1 if files are different.*
```C++
int helper_compareFile(FILE * fPtr1, FILE * fPtr2, int * line, int * col);
```

Run the Unit Testing: <br>
How to compile the Unit tests <br>
- gcc simple_test.c ../dot-C_files/structs.c ../dot-C_files/W_handler.c ../dot-C_files/json_parser.c ../dot-C_files/train_set_handler.c -o simple_test -ljson-c -lm <br>
How to run the tests <br>
- We can run all tests in the suite 
  - *./simple_tests*
- We can run only tests specified
  - *./simple_tests insert*
  - *./simple_tests add_relation*

<hr>

- *The code is thoroughly commented wherever needed for it's better comprehension.*
- **Thank you!** 😄

<hr>

# `Part 2` of the Project

From here and on we'll continue the documentation of the `part2` of the project.

## Negative Relations

For the negative relations, a tree is added to the headbucket of every clique. Every node of that tree has a pointer to other cliques(to their headbucket specifically). These pointers are effectively connecting different cliques, and are created during the reading of the W file.

## Parsing

For json parsing we first read every json and put all its contents in a string just like project1. Then parse it line by line and only keep the words by removing the labels and
symbols surrounding the lines.

## Creating BoW-IDF

### Dictionary

The dictionary is stored in a AVL tree. Every node of the tree holds the string of the word, an array of wordcounts(which represents the column of the BoW representation for that word) and an integer key of that word(so that we can use arrays later). The dictionary tree is created by reading every word of every json, preprocessing it and updating/creating tree nodes based on it.

### Preprocessing

The preprocessing is composed of a series of functions that alter the word, by:
- lowercasing it
- removing symbols from it, for instance "camera)," becomes "camera" (not every symbol though, because for example we don't want "3.5" to become "35" as it changes the word meaning)
- ignoring really big words (uses MAXWORDSIZE = 10 in train_handler.h file, changeable)
- the stopwords are removed after the BoW tree is created

### Creating BoW and TF_IDF arrays
The BoW array is created by recursively iterating the BoW Dictionary, and combining the columns of non stopwords. The TF_IDF array is created by first iterating the BoW array and getting the necessary extra data (number of words in a json for tf, and number of jsons that contain a specific word atleast once for idf). The rest data needed for tf and idf(bow entries and number of jsons) we already have. Then the TF_IDF array is allocated and filled based on the data above.

## Improving Bow and TF_IDF

Because the different words are way to many even with preprocessing (about 30000) we need to select the most "important" ones, so that the train and test sets aren't huge, and we avoid uneccessary noise.

This is done by saving the idf value of every word column to an array (during the TF_IDF creation), and the only using the ones with the lowest value(most importance). This sorting functions returns the indexes of the best word columns, which are used to create the improved arrays. 

## Creating Machine learing data

The dataset is created based on the positive_relations.csv, the negative_relations.csv and the improved BoW or TF_IDF (based on what the user asks for). Every relation is translated to the subtraction of the two vectors of its jsons, creating a vector for ML. These vectors are split to Train_Set.csv and Test_Set.csv (4/5 to train and 1/5 to test) to be used for Machine Learning.

### Compilation: 
```
$ make
``` 

### Execution:
```
$ ./project2 bow

  or

$ ./project2 tf_idf  
```
## Machine Learning

### Logistic Regression 

First and foremost the machine learning (logistic regression) part of the project is implemented in standard C++ without using any external libraries! 

 - To compile change directory into the MachineLearning directory and provide the following: 

```bash
$ g++ -o log_regr main_log_regr.cpp
```

 - To run: 

```bash
$ time ./log_regr
```

> The logistic regression part of the project is implemented following the project's description without any further modifications. (Source code is well commented for further understanding.)

### Unit Testing (for logistic regression)

The unit testing made for the machine learning part of the project is done using `Googletest - Google Testing and Mocking Framework`. <br>
Installation instructions for the framework can be found here ~> [gtest](https://github.com/google/googletest).

 - To run the tests: 

Get into the src/MachineLearning/tests directory and provide the following: 

 - Compile: 

```bash
$ g++ ML_test.cpp -lgtest -lgtest_main -pthread 
```

 - Run: 

```bash
$ ./a.out
```

<a href="mailto:sdi1400176@di.uoa.gr">🧑 Nikitas Sakkas</a>, <a href="mailto:sdi1500201@di.uoa.gr">🧔 Andrew Pappas</a>, <a href="mailto:sdi1400126@di.uoa.gr">👩 Konstantina Nika</a> <br>
:copyright: 2020 - 2021, All Rights Reserved.
