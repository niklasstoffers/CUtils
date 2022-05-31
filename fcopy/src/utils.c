#include <utils.h>
#include <string.h>

const char *strlchr(const char *str, int c) {
	int length = strlen(str);
	for(int i = length - 1; i >= 0; i--) {
		if (str[i] == c)
			return str + i;
	}
	return NULL;
}
