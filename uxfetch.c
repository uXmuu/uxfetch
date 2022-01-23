#include<stdio.h>
#include<stdlib.h>
#include<errno.h>
#include<string.h>
#include<sys/utsname.h>
#include<ctype.h>

#define YEL   "\x1B[33m"
#define CYN   "\x1B[36m"
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
	fclose(meminfo);
	return memUsed;
}
int getTotalMem(){
	FILE* meminfo = fopen("/proc/meminfo","r");
	char* mem[1000];
	fgets(mem, 1000, meminfo);
	int totalMem = getInt(mem);
	totalMem = totalMem/1024;
	fclose(meminfo);
	return totalMem;
}
int main(int argc, char *argv[])
{
	struct utsname buf1;
	errno = 0;
	if(uname(&buf1)!=0){
	
		exit(EXIT_FAILURE);
	}
	int totalMem = getTotalMem();
	int memUsed = getMem();

	printf(YEL "      _____\n    \\-     -/\n \\_/         \\ \thostname %s\t%s\n %s|        %sO O%s |\tVersion  %s\t%s\n %s|_  <   )  3 )\tkernel  %s\t%s\n%s / \\         /\tmemory%s\t\t%dM / %dM\n    %s/-_____-\\\n",RESET,buf1.nodename,YEL,CYN,YEL,RESET,buf1.version,YEL,RESET,buf1.release,YEL,RESET,memUsed,totalMem,YEL);

	/*
	printf(YEL "      _____\n");
	printf(YEL "    \\-     -/\n");
	printf(YEL " \\_/         \\ \thostname  %s\t%s\n",RESET, buf1.nodename);
	printf(YEL " |        %sO O%s |\tVersion  %s\t%s\n",CYN,YEL,RESET, buf1.version);
	printf(YEL " |_  <   )  3 )\tkernel  %s\t%s\n",RESET, buf1.release);
	printf(YEL " / \\         /\tmemory%s\t\t%dM / %dM\n",RESET,memUsed,totalMem);
	printf(YEL "    /-_____-\\\n");
	*/
}

/*
      _____
    \-     -/
 \_/         \
 |        O O |
 |_  <   )  3 )
 / \         /
    /-_____-\

*/
