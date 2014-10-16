#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <dirent.h>
#include <sys/types.h>
#include <string.h>
#include <sys/stat.h>
#include <unistd.h>
#include <jni.h>
#include "JavaNativeInterface.h"

JNIEXPORT jint JNICALL Java_JavaNativeInterface_randomNumber(JNIEnv *env, jobject obj, jint bound) {
  srand(time(NULL));
  return rand() % bound;
}

JNIEXPORT jobjectArray JNICALL Java_JavaNativeInterface_listFiles(JNIEnv *env, jobject obj, jstring jDirectory) {
   DIR               *dp;
   struct dirent     *ep;
   struct stat        buf;
   FILE              *fp;
   int                count = 0;
   int                i = 0;
   const char        *directory = (*env)->GetStringUTFChars(env, jDirectory, NULL);
   jclass            j_fileinfo_class;
   jmethodID         j_fileinfo_constructor;
   jobject          *object_array = NULL;
   jobjectArray      j_fileinfo_array = NULL;


   if ( (j_fileinfo_class = (*env)->FindClass(env, "JavaNativeInterface$FileListItem")) == NULL) {
      printf("Could not load class FileListItem\n");
      return NULL;
   }

   if ( (j_fileinfo_constructor = (*env)->GetMethodID(env, j_fileinfo_class, "<init>", "(Ljava/lang/String;J)V")) == NULL) {
      printf("Could not find constructor for FileListItem\n");
      return NULL;
   }

   dp = opendir(directory);
   if (dp != NULL) {
      while (ep = readdir(dp)) {
         if ( ep->d_type != DT_REG )
            continue; 
         
         fp = fopen(ep->d_name, "r");
         if (fp != NULL ) {
            if (fstat(fileno(fp), &buf) == 0) {
               jobject j_fileinfo;
               object_array = realloc(object_array, ++count * sizeof(jobject)); 
               
               jstring jFileName = (*env)->NewStringUTF(env, ep->d_name);
               j_fileinfo = (*env)->NewObject(env, j_fileinfo_class, j_fileinfo_constructor, jFileName, (jlong)buf.st_size); 
               object_array[count-1] = j_fileinfo; 

               (*env)->ReleaseStringUTFChars(env, jFileName, NULL);
            }
            fclose(fp);
         }
      }
      closedir(dp);


      j_fileinfo_array = (*env)->NewObjectArray(env, count, j_fileinfo_class, NULL);
      for (i = 0; i < count; i++) {
         (*env)->SetObjectArrayElement(env, j_fileinfo_array, i, object_array[i]);
         (*env)->DeleteLocalRef(env, object_array[i]);
      }
      free(object_array);
   }

   (*env)->DeleteLocalRef(env, j_fileinfo_class);
   return j_fileinfo_array;
}

