#include <stdio.h>

#define BIT_SYS_32
/* #define BIT_SYS_64 */

#ifdef BIT_SYS_32
#define SIZE_T_MAX 32
#elif BIT_SYS_64
#define SIZE_T_MAX 64
#endif

#define PATTERN "0011"

size_t charInBits(char c)
{
	if (c == '1')
		return 0x1;
	return 0x0;
}

size_t strToBits(char str[])
{
	size_t x = 0;
	size_t size = 0, i = 0;
	while (str[i] && ++size<SIZE_T_MAX) {
		x |= charInBits(str[i]);
		x <<= 1;
		i++;
	}
	return x>>1;
}

int main(int argc, char **argv)
{
	const size_t patternBits = strToBits(PATTERN);
	size_t inputBits=0;
	int c;

	printf("Enter your binary stream here:\n");
	while ((c = getchar())!=EOF) {
		if (c!='0' && c!='1') {
			putchar(c);
			continue;
		}
		inputBits |= charInBits(c);
		if (patternBits != (patternBits & inputBits))
			printf("0");
		else
			printf("1");
		inputBits <<= 1;
	}
	printf("\n");

	return 0;
}