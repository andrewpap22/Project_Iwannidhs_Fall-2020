#include <stdio.h>
#include <fcntl.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>

#include "../headers/json_parser.h"
#include "../headers/includes_for_parser.h"

/*
 * This functions gets as input a json file
 * and returns the values of ALL of the json file's labels 
*/
char *All_json_Values(char *json_filename)
{
  FILE *json_fp;
  long file_size;
  char *json_value = NULL;
  char *json_buffer = NULL;
  char * line = NULL;
  size_t len = 0;
  ssize_t read;
  char* token;
  char* character;
  int i = 0;
  int num_of_lines = 0; 
  int current_line = 0;

  json_fp = fopen(json_filename, "r");
  fseek(json_fp, 0L, SEEK_END);
  file_size = ftell(json_fp);
  fseek(json_fp, 0L, SEEK_SET);
  char* parsed_json = malloc(sizeof(char) * file_size);

  while ((read = getline(&line, &len, json_fp)) != -1) {
    num_of_lines++;
  }
  fseek(json_fp, 0L, SEEK_SET);
  while ((read = getline(&line, &len, json_fp)) != -1) {

    character = line;
    if (current_line == num_of_lines-2){
      i=0;
      while (i<read){
        if ((*(character+i)==':') && (*(character+i+1)==' ') && (*(character+i+2)=='\"')){
          *(line + read - 2) = '\0';
          parsed_json = strcat(parsed_json," ");
          // printf("yo\n");
          parsed_json = strcat(parsed_json,character+i+3);
          break;
        }
        i++;
      }
    }
    else{
      i=0;
      while (i<read){
        if ((*(character+i)==':') && (*(character+i+1)==' ') && (*(character+i+2)=='\"')){
          *(line + read - 3) = '\0';
          parsed_json = strcat(parsed_json," ");
          // printf("yo\n");
          parsed_json = strcat(parsed_json,character+i+3);
          break;
        }
        i++;
      }    
    }   
    current_line ++;
  }
  fclose(json_fp);

  // free(json_buffer);
  return (parsed_json);
}