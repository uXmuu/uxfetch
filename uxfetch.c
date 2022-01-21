#include<stdio.h>
#include<stdlib.h>
#include<errno.h>
#include<string.h>
#include<sys/utsname.h>

#define RED   "\x1B[31m"
#define GRN   "\x1B[32m"
#define YEL   "\x1B[33m"
#define BLU   "\x1B[34m"
#define MAG   "\x1B[35m"
#define CYN   "\x1B[36m"
#define WHT   "\x1B[37m"
#define RESET "\x1B[0m"

char *replace(const char *text, const char *oldWord, const char *newWord) {
   int i = 0, cnt = 0;
   int len1 = strlen(newWord);
   int len2 = strlen(oldWord);
   for (i = 0; text[i] != '\0'; i++) {
      if (strstr(&text[i], oldWord) == &text[i]) {
         cnt++;
         i += len2 - 1;
      }
   }
   char *newString = (char *)malloc(i + cnt * (len1 - len2) + 1);
   i = 0;
   while (*text) {
      if (strstr(text, oldWord) == text) {
         strcpy(&newString[i], newWord);
         i += len1;
         text += len2;
      }
      else
      newString[i++] = *text++;
   }
   char *a[1000];
   *a = newString;
   printf(YEL " / \\         /\tmemory:%s\t\t%s",RESET,*a);
}
int main()
{
	FILE* status = fopen("/proc/meminfo","r");
	char* mem_used[1000];
	for(int i=0; i<10; i++){
		fgets(mem_used, 1000, status);
	}
	struct utsname buf1;	
	char* test;
	errno = 0;
	if(uname(&buf1)!=0){
	
		exit(EXIT_FAILURE);
	}
	printf(YEL "      _____\n");
	printf(YEL "    \\-     -/\n");
	printf(YEL " \\_/         \\ \tos  %s\t\t%s\n",RESET, buf1.nodename);
	printf(YEL " |        O O |\tVersion  %s\t%s\n",RESET, buf1.version);
	printf(YEL " |_  <   )  3 )\tkernel  %s\t%s\n",RESET, buf1.release);
	fclose(status);
	test = replace(mem_used,"Inactive(anon):  ","");
	printf(YEL "    /-_____-\\\n");
}


/* 
    \-     -/      
 \_/         \     
 |        O O |    
 |_  <   )  3 )    
 / \         /    
    /-_____-\  
*/