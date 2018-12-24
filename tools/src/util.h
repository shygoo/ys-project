#ifndef _UTIL_H_
#define _UTIL_H_

#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>

#ifdef _WIN32
#include <direct.h>
#else
#include <sys/stat.h>
#include <sys/types.h>
#endif

void makedir(const char *dirpath)
{
    #ifdef _WIN32
	mkdir(dirpath);
	#else
	mkdir(dirpath, 0777);
	#endif
}

void writefile(const char *path, uint8_t *data, size_t size)
{
    FILE *fp = fopen(path, "wb");
    fwrite(data, 1, size, fp);
    fclose(fp); 
}

#endif // _UTIL_H_
