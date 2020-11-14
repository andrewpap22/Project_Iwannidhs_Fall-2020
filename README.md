# Information Systems Project 
### Fall 2020 - 2021 
[![Open Source](https://badges.frapsoft.com/os/v1/open-source.svg?v=103)](https://opensource.org/)

<hr>

### Compilation: 
```
$ make
``` 

### Execution:
```
$ ./project1 ../dataset/sigmod_large_labelled_dataset.csv
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
The above operation described is dynamic (not hardcoded), and that means that it will keep adding json files by creating the linked list of buckets on each and every node of the tree based on the total json files that are provided to the application. <br> After we're done and all the files are inserted we're deallocating the memory memory that we have previously located from the heap! <br>
Our program, checks (as requested from the project description) the files with each other and 'prints' into a .csv file the relation of each and every file with each other, (i.e. all the json files that are the same with each other based on the specs that are contained inside). 

<hr>

## Details

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
        <a href="https://github.com/andrewpap22/Project_Iwannidhs_Fall-2020/tree/master/src/headers">📂 headers</a>
      </li>
    </ul>
    <p>📄 makefile</p>
    <p>📄 project.c</p>
  </li>
  <li>
    <a href="https://github.com/andrewpap22/Project_Iwannidhs_Fall-2020/tree/master/valgrind_output">📂 valgrind_output</a>
  </li>
</ul>

<hr>

:copyright: <a href="mailto:sdi1400126@di.uoa.gr">Konstantina Nika</a>, <a href="mailto:sdi1400176@di.uoa.gr">Nikitas Sakkas</a>, <a href="mailto:sdi1500201@di.uoa.gr">Andrew Pappas</a>, 2020 - 2021, All Rights Reserved.
