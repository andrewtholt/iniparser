#include "iniUtils.h"
#include <stdio.h>
#include <stdint.h>

#include <stdbool.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>


#define FNAME "./gauge.ini"


int parseIni(char *fname) {

    char buffer[132];

    char key[132];
    char value[132];
    char section[132];
    char *tmp;

    int fd;
    int rc=0;
    bool runFlag = true;
    int len=0;

    fd=open( fname, O_RDONLY);

    if(!fd) {
        perror(FNAME);
        exit(1);
    }

    while(runFlag) {
        rc = readLine(fd,buffer,132);

        if( rc == 0) {
            runFlag=false;
        }

        if( rc > 0 ) {
            len=strlen( buffer);
            len--;
            buffer[len] = '\0';
            len--;

            if(len > 0) {

                if( (buffer[0] == '[') && (buffer[len]) == ']') {
                    memset(section,0,132);
                    printf("Section\n");
                    strncpy(section, &buffer[1], --len);
                } else {
                    tmp=strtok(buffer,"=");
                    strcpy(key, section);
                    strcat(key,".");
                    strcat(key,tmp);
                    tmp=strtok(NULL,"\n");

                    strcpy(value,tmp);

                    printf("Key   : >%s<\n", key);
                    printf("Value : >%s<\n", value);
                }
            }
        }
    }
}


int main() {
    parseIni(FNAME);
}
