#include <futils.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <limits.h>
#include <errno.h>
#include <string.h>

int main(int argc, char **argv) {
	char cwd[PATH_MAX];
	if (getcwd(cwd, sizeof(cwd)) != NULL) {
		if (argc < 3) {
			fprintf(stderr, "Unexpected argument count. Command usage: %s <srcfile> <destfile>\n", argv[0]);
			return -1;
		}

		char *srcFile = argv[1], *destFile = argv[2];
		if (!isAbsPath(srcFile))
			srcFile = combine(cwd, srcFile);
		if (!isAbsPath(destFile))
			destFile = combine(cwd, destFile);

		int err = fcopy(srcFile, destFile);

		if (!isAbsPath(argv[1]))
			free(srcFile);
		if (!isAbsPath(argv[2]))
			free(destFile);

		if (err) {
			char *errmsg = strerror(errno);
			fprintf(stderr, "%s\n", errmsg);

			return -1;
		}

		return 0;
	}
	else {
		fprintf(stderr, "Couldn't get executing directory");
		return -1;
	}
}
