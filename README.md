# Information Systems Project 
### Fall 2020 - 2021 

--------------------------------

Compilation: **$ make** 

Execution: **$ ./project1 ../dataset/sigmod_large_labelled_dataset.csv**

*(Execution time on large dataset = 3sec)*

To delete binary files: $ make clean

--------------------------------

## Project1 Details: 

First of all, this project uses the libjson-c-dev library, so you need to install it on your system by providing
(for ubuntu systems) : $ sudo apt install libjson-c-dev 
For non ubuntu systems adjust accordingly, <a href="https://github.com/json-c/json-c">Info.</a>

The data structure that is used on this 1st project is a binary search tree whose nodes consists of linked lists of buckets.
The program at first opens the dataset directory where the camera specs are located there and for each and every subdirectory it opens it and searches and opens each and every one of the json files. Afterwards we insert each and every of the json files inside the 1st tree node (i.e. bucket) and when the 1st bucket is full of json files we allocate proper memory from the heap to create a new bucket to insert the remaining json files. The above operation described is dynamic (not hardcoded), and that means that it will keep adding json files by created the linked list o buckets on each and every node of the tree based on the total json files that are provided to the application. After we're done and all the files are inserted we're deallocating the memory memory that we have previously located from the heap! 
Finally we output the relation of the files to an external .csv file.
Thank you!


--------------------------------

:copyright: <a href="mailto:sdi1400126@di.uoa.gr">Konstantina Nika</a>, <a href="mailto:sdi1400176@di.uoa.gr">Nikitas Sakkas</a>, <a href="mailto:sdi1500201@di.uoa.gr">Andrew Pappas</a>, 2020 - 2021, All Rights Reserved.
