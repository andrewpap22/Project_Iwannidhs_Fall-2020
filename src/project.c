#include "headers/structs.h"
#include "headers/W_handler.h"
#include "headers/json_parser.h"
#include "headers/includes_for_parser.h"
#include "headers/train_set_handler.h"


#define NUMOFENTRIES 29787  // 29787 jsons
#define NUMOFWORDS 42329  // 42329 different words


int k = 0;

//read dataset stuff
int main(int argc,char** argv)
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

  // Bow stuff
  int** bow_array;
  float** tf_idf_array;
  //parsing stuff
  char *all_json_values = NULL;

  if(argv[1]==NULL){
    printf("Wrong arguments. Type %s bow/tf_idf\n", argv[0]);
    return -1;
  }
  if((strcmp(argv[1],"bow")!=0) && (strcmp(argv[1],"tf_idf")!=0)){
    printf("Wrong arguments. Type %s bow/tf_idf\n", argv[0]);
    return -1;
  }
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
    while (((dir_JSON) = readdir(dirp_JSON)))
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

      all_json_values = All_json_Values(full_json_path);

      num_of_json = atoi(strtok(dir_JSON->d_name, "."));
      // store everything needed inside our data structures.
      database_root = insert(database_root, num_of_json, name_of_json, all_json_values);
      k++;
    }
  }
  printf("All json files have been added(%d in total).\n\n",k);

  //  read W dataset
  printf("Adding positive relations...\n");

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
    add_positive_relation(database_root, json1, json2, relation);
  }
  fclose(w_fp);
  printf("Adding negative relations...\n");
  w_fp = fopen(w_path, "r");

  read = getline(&line, &len, w_fp);
  while ((read = getline(&line, &len, w_fp)) != -1)
  {
    part_of_string = strtok(line, ",");
    strcpy(json1, part_of_string);
    part_of_string = strtok(NULL, ",");
    strcpy(json2, part_of_string);
    part_of_string = strtok(NULL, "\n");
    relation = atoi(part_of_string);
    add_negative_relation(database_root, json1, json2, relation);
  }

  printf("All relations are added.\n\n");
  fclose(w_fp);

  FILE *fp2;
  FILE *fp3;
  char *positive_relations = "positive_relations.csv";
  char *negative_relations = "negative_relations.csv";

  // json_remover = strstr(filename, "\n"); //remove "\n" substring from filename
  // *json_remover = '\0';
  // filename = strcat(filename, ".csv");

  printf("Creating %s...\n", positive_relations);
  fp2 = fopen(positive_relations, "w+");
  print_all_positive_relations(database_root, fp2);
  fclose(fp2);
  printf("%s created.\n\n", positive_relations);

  printf("Creating %s...\n", negative_relations);
  fp3 = fopen(negative_relations, "w+");
  print_all_negative_relations(database_root, fp3);
  fclose(fp2);
  printf("%s created.\n\n", negative_relations);

  printf("Creating BOW...\n");
  bow_array = create_bow_array(database_root);

  printf("Bow created.\n\n");

  printf("Creating TF_IDF...\n");
  tf_idf_array = create_tf_idf(bow_array);
  printf("TF_IDF created.\n\n");
  // for (int i = 0; i < NUMOFENTRIES; i++){
  //   for (int j = 0; j < NUMOFWORDS; j++){
  //     printf("%lf ", tf_idf_array[j][i]);
  //   }
  //   printf("\n");
  // }

  if(strcmp(argv[1],"bow")==0){
    printf("Creating Training Set using BoW...\n");
    create_train_set_bow(bow_array, NUMOFWORDS, database_root, positive_relations, negative_relations);
    printf("Training Set created...\n");
  }
  else if(strcmp(argv[1],"tf_idf")==0){
    printf("Creating Training Set using tf idf...\n");
    create_train_set_tfidf(tf_idf_array, NUMOFWORDS, database_root, positive_relations, negative_relations);
    printf("Training Set created...\n");
  }

  printf("Freeing Database...\n");
  free_node(database_root);
  printf("Database Freed.\n\n");

  printf("Shutting Down.\n");

  return 0; // program has ended successfully.
}