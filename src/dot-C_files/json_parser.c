#include <stdio.h>
#include <fcntl.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>

#include "../headers/json_parser.h"
#include "../headers/includes_for_parser.h"

char *json_get_var_char(char *rdbuf, char *getbuf)
{
  char *retbuf;
  int len, glen, index = 0, sindex = 0, bindex = 0, firstqouta = 0, ourindex, sstart = 0;

  if (strstr(rdbuf, getbuf) == 0)
    return NULL;

  len = strlen(rdbuf);
  glen = strlen(getbuf);

  retbuf = (char *)malloc(len);

  for (int i = 0; i < len; i++)
  {
    if (rdbuf[i] == '\"' && rdbuf[i + glen + 1] == '\"')
    {
      for (int l = i + glen + 1; l < len; l++)
      {
        if (rdbuf[l] == ':')
        {
          json.json_name[index] = i + 1;
          json.colon_index[index++] = l;
          break;
        }
      }
    }
  }

  for (int i = 0; i < index; i++)
  {
    for (int k = json.json_name[i]; k < len; k++)
    {
      if (rdbuf[k] == '\"')
        break;

      retbuf[bindex++] = rdbuf[k];
      retbuf[bindex] = 0;
    }

    if (strcmp(getbuf, retbuf) == 0)
    {
      ourindex = json.json_name[i];
      break;
    }
    else
    {
      bindex = 0;
      memset(retbuf, 0, len);
    }
  }

  for (int k = ourindex; k < len; k++)
  {
    if (rdbuf[k] == '\"')
    {
      if (firstqouta == 1)
      {
        sstart = k + 1;
        break;
      }
      firstqouta++;
    }
  }

  memset(retbuf, 0, len);

  for (int i = sstart; i < len; i++)
  {
    if ((rdbuf[i] == '\"' && rdbuf[i + 1] == ',') || (rdbuf[i] == '\"' && rdbuf[i + 1] == '\r') || (rdbuf[i] == '\"' && rdbuf[i + 1] == '\n'))
      break;

    retbuf[sindex++] = rdbuf[i];
    retbuf[sindex] = 0;
  }

  return (char *)retbuf;
}

/*
 * This function is a helper function for the 
 * All_json_Values function. 
 * It takes as an input a different label of a json file and the json value to be changed each time and it needs the json_buffer as well.
 * And it returns the final modified json value as a string.
*/
// char *Final_Json_Value(char *json_value, char *json_label, char *json_buffer)
// {

//   /*
//    * [!] IMPORTANT NOTE TO SELF! 
//    * 8a prepei kapws na akolou8w tin idia logiki pou kanw edw, alla xwris na dinw ws parametro ton json buffer.
//    * dhladh an to label pou dinw se kapoio arxeio den uparxei (dhladh einai null) 
//    * na kanw concatenate apla ena space sto string h akomh kalutera kapws na to agnow teleiws kai na proxwrame sto epomeno label
//    * an den einai null omws tote apla na parsarw to value tou label (else block) sto json_value string kai na to epistrefw...
//    */

//   if (json_get_var_char(json_buffer, json_label) == NULL)
//   {
//     json_value = strcat(json_value, " ");
//   }
//   else
//   {
//     json_value = strcat(json_value, " ");
//     json_value = strcat(json_value, json_get_var_char(json_buffer, json_label));
//   }

//   return (json_value);
// }

/*
 * This functions gets as input a json file
 * and returns the value of the <page_title> as a single string 
 * [!] Works as expected!
*/
char *Page_Title_Value(char *json_filename)
{
  FILE *json_fp;
  long file_size;
  char *json_value = NULL;
  char *json_buffer = NULL;

  json_fp = fopen(json_filename, "r");
  fseek(json_fp, 0L, SEEK_END);
  file_size = ftell(json_fp);
  fseek(json_fp, 0L, SEEK_SET);

  json_buffer = malloc(sizeof(char) * file_size);
  fread(json_buffer, file_size, 1, json_fp);
  fclose(json_fp);

  //json_value = json_get_var_char(json_buffer, "<page title>");
  // printf("\n%s\n", json_value);

  json_value = malloc(file_size * sizeof(char));
  strcpy(json_value, json_get_var_char(json_buffer, "<page title>"));

  free(json_buffer);

  return (json_value);
}

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

  json_fp = fopen(json_filename, "r");
  fseek(json_fp, 0L, SEEK_END);
  file_size = ftell(json_fp);
  fseek(json_fp, 0L, SEEK_SET);
  char* parsed_json = malloc(sizeof(char) * file_size);
  while ((read = getline(&line, &len, json_fp)) != -1) {

        character = line;
        i=0;
        while (i<read)
        {
          if ((*(character+i)==':') && (*(character+i+1)==' ') && (*(character+i+2)=='\"'))
          {
            *(line + read - 3) = '\0';
            parsed_json = strcat(parsed_json," ");
            // printf("yo\n");
            parsed_json = strcat(parsed_json,character+i+3);
            break;
          }
          i++;
        }       
    }
  fclose(json_fp);
        // token = strtok(line,"\": \"");
        // token = strtok(NULL,"\",\n");
        // if(token!=NULL){
        //   printf("%s\n",token);
        // }

  // token = strtok(NULL,">\": \"");

  // token = strtok(NULL,"\0");

  // printf("%s\n",token);
  // json_value = malloc(file_size * sizeof(char));
  // strcpy(json_value, json_get_var_char(json_buffer, "<page title>"));

  // for (int i = 0; i < array_length; i++)
  // {
  //   if (json_get_var_char(json_buffer, json_labels[i]) == NULL)
  //   {
  //     json_value = strcat(json_value, "");
  //   }
  //   else
  //   {
  //     json_value = strcat(json_value, " ");
  //     json_value = strcat(json_value, json_get_var_char(json_buffer, json_labels[i]));
  //   }
  // }

  // free(json_buffer);
  return (parsed_json);
}