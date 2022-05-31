#include <futils.h>
#include <utils.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <stddef.h>

#if defined (_WIN32) || defined(_WIN64)
#include <shlwapi.h>
#endif

char *dir(const char *path) {
	const char *sep;
	sep = strlchr(path, FSEP);

	if (sep == NULL)
		return NULL;

	int dirl = sep - path;
	char *dirName = (char*)malloc(dirl + 1);
	memcpy(dirName, path, dirl);
	dirName[dirl] = '\0';

	return dirName;
}

int fcopy(const char *p1, const char *p2) {
	if (!strcmp(p1, p2)) 
		return 0;

	FILE *f1, *f2;
	if ((f1 = fopen(p1, "rb")) == NULL)
		return -1;
	if ((f2 = fopen(p2, "wb")) == NULL) {
		free(f1);
		return -1;
	}

	int err = 0;
	char buffer[4096];
	while(!feof(f1)) {
		size_t bytes = fread(buffer, 1, sizeof(buffer), f1);
		if (bytes) 
		   	fwrite(buffer, 1, bytes, f2);
	}

	fclose(f1);
	fclose(f2);

	return err;
}

char *combine(const char *dir, const char *file) {
	int dirl = strlen(dir);
	int filel = strlen(file);

	char *fpath = (char*)malloc(dirl + filel + 2);
	memcpy(fpath, dir, dirl);
	memcpy(fpath + dirl + 1, file, filel);
	fpath[dirl] = FSEP;
	fpath[dirl + filel + 1] = '\0';

	return fpath;
}

int isAbsPath(const char *p) {
#if defined(_WIN32) || defined(_WIN64)
	size_t s = strlen(p) + 1;
	wchar_t path[s];
	mbstowcs(path, p, s);
	return PathIsRelativeW((LPWSTR)path);
#else
	return p[0] == FSEP;
#endif
}
