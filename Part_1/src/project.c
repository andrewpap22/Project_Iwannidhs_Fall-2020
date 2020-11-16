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
  char *json_remover;
  char *full_json_path;
  char *json_specs;

  //read W stuff
  char *w_path = "../dataset/sigmod_large_labelled_dataset.csv";
  FILE *w_fp;
  char *line = NULL;
  size_t len = 0;
  ssize_t read;
  char *json1 = malloc(sizeof(char) * 50);
  char *json2 = malloc(sizeof(char) * 50);
  int relation;
  char *part_of_string;

  printf("\nAdding json files to database...\n");

  //  read json dataset
  while ((dir = readdir(dirp)))
  {
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

    //open subdirectories inside the dataset
    dirp_JSON = opendir(file_path);
    while ((dir_JSON) = readdir(dirp_JSON))
    {
      if (!strcmp(dir_JSON->d_name, ".")) // current directory
      {
        continue;
      }
      if (!strcmp(dir_JSON->d_name, "..")) // previous directory
      {
        continue;
      }

      //  add every entry to database
      name_of_json = malloc(sizeof(dir->d_name));

      strcpy(name_of_json, dir->d_name);
      strcat(name_of_json, "//");
      strcat(name_of_json, dir_JSON->d_name);

      // allocate proper memory for the full path containing each and every .json files to be read by read_json()
      full_json_path = malloc(sizeof(*absolute_path) + sizeof(dir->d_name) + sizeof(char) + sizeof(char) + sizeof(dir_JSON->d_name));

      strcpy(full_json_path, file_path);
      strcat(full_json_path, "/");
      strcat(full_json_path, dir_JSON->d_name);

      // read each and every .json file from the dataset and store it's contents into a single string to be used as BOW later on...
      json_remover = strstr(name_of_json, ".json"); //remove ".json" substring from all strings
      *json_remover = '\0';

      json_specs = read_json(full_json_path);

      num_of_json = atoi(strtok(dir_JSON->d_name, "."));

      // store everything needed inside our data structures.
      database_root = insert(database_root, num_of_json, name_of_json, json_specs);
    }
  }

  printf("All json files have been added.\n\n");

  printf("Adding relations...\n");

  //  read W dataset
  w_fp = fopen(w_path, "r");

  if (w_fp == NULL)
  {
    printf("Can't find W file!\n");
  }

  read = getline(&line, &len, w_fp);
  while ((read = getline(&line, &len, w_fp)) != -1)
  {
    part_of_string = strtok(line, ",");
    strcpy(json1, part_of_string);
    part_of_string = strtok(NULL, ",");
    strcpy(json2, part_of_string);
    part_of_string = strtok(NULL, "\n");
    relation = atoi(part_of_string);
    add_relation(database_root, json1, json2, relation);
  }
  printf("All relations are added.\n\n");

  FILE *fp2;
  char *filename = NULL;

  printf("Enter the filename:\n");
  read = getline(&filename, &len, stdin);
  if (-1 == read)
  {
    printf("No line read\n");
  }
  json_remover = strstr(filename, "\n"); //remove "\n" substring from filename
  *json_remover = '\0';
  filename = strcat(filename, ".csv");

  printf("\nCreating %s...\n", filename);
  fp2 = fopen(filename, "w+");
  fprintf(fp2, "left_spec_id,right_spec_id\n");
  print_all_relations(database_root, fp2);
  fclose(fp2);
  printf("%s created.\n\n", filename);

  printf("Freeing Database...\n");
  free_node(database_root);
  printf("Database Freed.\n\n");

  printf("Shutting Down.\n");

  return 0; // program has ended successfully.
}