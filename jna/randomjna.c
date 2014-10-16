#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <dirent.h>
#include <sys/types.h>
#include <string.h>
#include <sys/stat.h>
#include <unistd.h>

struct my_struct {
   char *filename;
   long  filesize;
};


int randomNumber(int bound) {
  srand(time(NULL));
  return rand() % bound;
}

struct my_struct* list_files(char *directory, int *elements) {
   DIR           *dp;
   struct dirent *ep;
   struct stat    buf;
   FILE          *fp;
   struct my_struct  *files = NULL;


   *elements = 0;
   dp = opendir(directory);
   if (dp != NULL) {
      while (ep = readdir(dp)) {
         if ( ep->d_type != DT_REG )
            continue; 
         
         fp = fopen(ep->d_name, "r");
         if (fp != NULL ) {
            if (fstat(fileno(fp), &buf) == 0) {
               files = realloc(files, ++(*elements)* sizeof(struct my_struct));
               files[*elements-1].filename = strdup(ep->d_name);
               files[*elements-1].filesize = buf.st_size;
            }
            fclose(fp);
         }
      }
      closedir(dp);
   }

   return files;
}

void free_struct(struct my_struct *structure, int num_elements) {
   int i;

   for (i = 0; i < num_elements; i++) {
      free(structure[i].filename);
   }

   free(structure);
}


void main() {
   int i;
   list_files("./", &i);
}

