#include <stdio.h>

#if !defined __X86_64__
#define SIZE_T_MAX 32
#else
#define SIZE_T_MAX 64
#endif

#define PATTERN "0011"

size_t charInBits(char c)
{
	if (c == '1')
		return 0x1;
	return 0x0;
}

size_t strToBits(char str[], size_t *bit)
{
	size_t x = 0;
	size_t size = 0, i = 0;
	while (str[i] && ++size<SIZE_T_MAX) {
		x <<= 1;
		x |= charInBits(str[i]);
		i++;
	}
	*bit=x;
	return size;
}

int main(int argc, char **argv)
{
	size_t patternBits, reset=0, inputBits=0, inSize=0;
	const size_t patSize = strToBits(PATTERN, &patternBits);
	int c, i=patSize;

	while (i--) {
		reset <<= 0x1;
		reset |= 0x1;
	}

	printf("Enter your binary stream here:\n");
	while ((c = getchar())!=EOF) {
		if (c!='0' && c!='1') {
			putchar(c);
			continue;
		}

		inputBits |= charInBits(c);
		inSize++;

		if (inSize > patSize)
			inputBits &= reset;

		if ((patternBits^inputBits)!=0)
			printf("0");
		else
			printf("1");

		inputBits <<= 1;
	}

	printf("\n");

	return 0;
}
