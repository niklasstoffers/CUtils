#ifndef FUTILS_H
#define FUTILS_H

#if defined(_WIN32) || defined(_WIN64)
#define FSEP '\\'
#else
#define FSEP '/'
#endif

char *dir(const char*);
int fcopy(const char*, const char*);
char *combine(const char*, const char*);
int isAbsPath(const char*);

#endif
