#include<stdio.h>
#include<stdlib.h>
#include<errno.h>
#include<string.h>
#include<sys/utsname.h>
#include<ctype.h>


#define RED   "\x1B[31m"
#define GRN   "\x1B[32m"
#define YEL   "\x1B[33m"
#define BLU   "\x1B[34m"
#define MAG   "\x1B[35m"
#define CYN   "\x1B[36m"
#define WHT   "\x1B[37m"
#define RESET "\x1B[0m"

int getInt(char **str){
	char *p = str;
	while (*p) {
	    if ( isdigit(*p) || ( (*p=='-'||*p=='+') && isdigit(*(p+1)) )) {
	        int val = strtol(p, &p, 10);
	        return val;//printf("%ld\n", val);
	    } else {
	        p++;
	    }
	}
}
int getMem(){
	FILE* meminfo = fopen("/proc/meminfo","r");
	char* mem1[1000];
	char* mem2[1000];
	char* mem3[1000];
	fgets(mem1, 1000, meminfo);
	fgets(mem2, 1000, meminfo);
	fgets(mem3, 1000, meminfo);
	int totalMem = getInt(mem1);
	int memAvailable = getInt(mem3);
	int memUsed = totalMem-=memAvailable;
	memUsed = memUsed/1124;
	//char m[] = ("%d/%d",memUsed,totalMem);
	fclose(meminfo);
	return memUsed;
}
int main()
{
	struct utsname buf1;	
	char *test;
	errno = 0;
	if(uname(&buf1)!=0){
	
		exit(EXIT_FAILURE);
	}
	int memUsed = getMem();
	printf(YEL "      _____\n");
	printf(YEL "    \\-     -/\n");
	printf(YEL " \\_/         \\ \thostname  %s\t%s\n",RESET, buf1.nodename);
	printf(YEL " |        %sO O%s |\tVersion  %s\t%s\n",CYN,YEL,RESET, buf1.version);
	printf(YEL " |_  <   )  3 )\tkernel  %s\t%s\n",RESET, buf1.release);
	printf(YEL " / \\         /\tmemory%s\t\t%dM\n",RESET,memUsed);
	printf(test);
	free(test);
	printf(YEL "    /-_____-\\\n");
	
}

/*	  _____
    \-     -/
 \_/         \
 |        O O |
 |_  <   )  3 )
 / \         /
    /-_____-\
*/
