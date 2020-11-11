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

  //read W stuff
  char *w_path = "../dataset/sigmod_large_labelled_dataset.csv";
  FILE *w_fp;
  char *line = NULL;
  size_t len = 0;
  ssize_t read;
  int json1;
  int json2;
  int relation;
  char *part_of_string;

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

      printf("================================\n");
      read_json(full_json_path);
      printf("================================\n");

      //printf("name of json is: %s\n",dir_JSON->d_name);

      num_of_json = atoi(strtok(dir_JSON->d_name, ".")); //auto edw einai pou prepei na ginei string kai oxi int.

      database_root = insert(database_root, num_of_json, name_of_json); 
      //printf("%s\n",name_of_json2);
    }
  }

  // char *json_filename = "../dataset/camera_specs/2013_camera_specs/buy.net/5372.json";
  // printf("================================\n");
  // read_json(json_filename);
  // printf("================================\n");

  printf("adding relations\n");

  //  read W /*
  w_fp = fopen(w_path, "r");
  if (w_fp == NULL)
  {
    printf("can't find W file!\n");
  }
  read = getline(&line, &len, w_fp);
  while ((read = getline(&line, &len, w_fp)) != -1)
  {
    // printf("%s",line);
    part_of_string = strtok(line, "//");
    part_of_string = strtok(NULL, ",");
    part_of_string += 1;
    json1 = atoi(part_of_string);
    part_of_string = strtok(NULL, "//");
    part_of_string = strtok(NULL, ",");
    part_of_string += 1;
    json2 = atoi(part_of_string);

    part_of_string = strtok(NULL, "\n");
    relation = atoi(part_of_string);
    // printf("%d, %d, %d\n", json1, json2, relation);
    add_relation(database_root, json1, json2, relation);
  }
  printf("all relations added!\n");
  sleep(1);
  printf("printing in:\n");
  for (int i = 0; i < 3; i++)
  {
    printf("%d\n", 3 - i);
    sleep(1);
  }

  FILE *fp2;
	char *filename;

	printf("Enter the filename: ");
	gets(filename); 

	printf("\nCreating %s.csv file", filename);
	filename = strcat(filename, ".csv");

	fp2 = fopen(filename, "w+");
	fprintf(fp2, "left_spec_id,right_spec_id");
  
  print_all_relations(database_root);

  fclose(fp2);
	printf("\n%s file has been created.", filename);
  printf("\n");

  fclose(w_fp);
  return 0;
}


// menei na ftiaksw tin read json (etoimh check!)
// menei na allaksw to int se string pou pername mesa stin insert sto dentro kai na xrhsimopoihsw gia tis sugkriseis
// tin sunarthsh pou mou edwse o allos sto discord
// kai telos menei na printarw ta apotelesmata sto csv arxeio.