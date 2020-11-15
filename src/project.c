#include "headers/structs.h"
#include "headers/W_handler.h"

#define NUMOFENTRIES 29787
#define NUMOFWEBSITES 24

//read dataset stuff
int main(void)
{

  char *absolute_path = "../dataset/camera_specs/2013_camera_specs";
  char *file_path;
  DIR *dirp = opendir(absolute_path);
  DIR *dirp_JSON;
  struct dirent *dir, *dir_JSON;

  //create data files stuff
  tree_entry *database_root = NULL;
  int num_of_json = 0;
  char *name_of_json;

  char *full_json_path;
  char *json_specs;

  //read W stuff
  char *w_path = "../dataset/sigmod_large_labelled_dataset.csv";
  FILE *w_fp;
  char *line = NULL;
  size_t len = 0;
  ssize_t read;
  char* json1 = malloc(sizeof(char)*50);
  char* json2 = malloc(sizeof(char)*50);
  int relation;
  char *part_of_string;

  printf("adding json files to database\n");
  //  read json dataset
  while ((dir = readdir(dirp))){
    if (!strcmp(dir->d_name, "."))
    {
      continue;
    }
    if (!strcmp(dir->d_name, ".."))
    {
      continue;
    }
    file_path = malloc(sizeof(*absolute_path) + sizeof(dir->d_name) + sizeof(char));
    
    //create filepath
    strcpy(file_path, absolute_path);
    strcat(file_path, "/");
    strcat(file_path, dir->d_name);
    //printf("filepath: %s\n",file_path);

    dirp_JSON = opendir(file_path);
    while ((dir_JSON) = readdir(dirp_JSON))
    {
      if (!strcmp(dir_JSON->d_name, "."))
        continue;
      if (!strcmp(dir_JSON->d_name, ".."))
        continue;
      //  add every entry to database
      name_of_json = malloc(sizeof(dir->d_name));

      strcpy(name_of_json, dir->d_name);
      strcat(name_of_json, "//");
      strcat(name_of_json, dir_JSON->d_name);

      full_json_path = malloc(sizeof(*absolute_path) + sizeof(dir->d_name) + sizeof(char) + sizeof(char) + sizeof(dir_JSON->d_name));
      strcpy(full_json_path, file_path);
      strcat(full_json_path, "/");
      strcat(full_json_path, dir_JSON->d_name);
      //printf("full json path is: %s\n",full_json_path);

      // printf("=====================================================================\n");
      json_specs = read_json(full_json_path);
      // printf("%s\n",json_specs);
      // printoutarray(json_specs); // auto to print einai gia testing.. twra pou exoume to array of strings me ola ta specs apo ka8e json arxeio boroume na to pros8esoume mesa sto bucket tou tree!
      //printf("The title of the page is: %s\n",json_spec);
      // printf("=====================================================================\n");

      num_of_json = atoi(strtok(dir_JSON->d_name, "."));

      database_root = insert(database_root, num_of_json, name_of_json, json_specs); 
      // printf("%s\n",name_of_json);
    }
  }
  printf("all jsons added\n");

  // tree_entry* it = database_root;
  // while (it){
  //   printf("%s\n",it->specs);
  //   it = it->right;
  // }
  printf("adding relations...\n");

  //  read W /*
  w_fp = fopen(w_path, "r");
  if (w_fp == NULL){
    printf("can't find W file!\n");
  }
  read = getline(&line, &len, w_fp);
  while ((read = getline(&line, &len, w_fp)) != -1){
    part_of_string = strtok(line, ",");
    strcpy(json1,part_of_string);
    strcat(json1,".json");
    part_of_string = strtok(NULL, ",");
    strcpy(json2,part_of_string);
    strcat(json2,".json");
    part_of_string = strtok(NULL, "\n");
    relation = atoi(part_of_string);
    add_relation(database_root, json1, json2, relation);
  }
  printf("All relations are added\n");

  // FILE *fp2;
	// char *filename;

	// printf("Enter the filename: ");
	// gets(filename); 

	// printf("\nCreating %s.csv file", filename);
	// filename = strcat(filename, ".csv");

	// fp2 = fopen(filename, "w+");
	// fprintf(fp2, "left_spec_id,right_spec_id");
  
  print_all_relations(database_root);

  //delete the tree
  free_node(database_root);
  printf("Shutting Down\n");

  
  // fclose(fp2);
	// printf("\n%s file has been created.", filename);
  // printf("\n");

  // fclose(w_fp);
  return 0;
}


/* =============== menei mono na tupwnoume ta apotelesmata sto csv arxeio kai oxi sto stdout!!! ================ */