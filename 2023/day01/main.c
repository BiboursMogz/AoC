#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>

int partOne(char *Input)
{
	int res = 0;

	char *first = 0;
	char *last = 0;
	for (char *c = Input; *c; ++c) 
	{
	if (('0' <= *c) && (*c <= '9'))
		{
			if (!first)
			{
				last = first = c;
			} else if (last < c)
			{
				last = c;
			}
		}

	if (*c == '\n')
		{
			if (first)
			{
				res += (((*first) - '0') * 10) + ((*last) - '0');
			}
			first = 0;
			last = 0;
		}
	}
	return res;
}

int main(int argc, char **argv)
{
	if (argc != 2)
	{
		fprintf(stderr,"ERROR : wrong usage\n");
		printf("Usage : %s *.txt\n", *argv);
		return 1;
	}

	#define FILENAME_MAX_SIZE 256
	char filename[FILENAME_MAX_SIZE] = {0};
	char *p = filename;
	++argv;
	int i;
	for (i= 0; i < FILENAME_MAX_SIZE - 1, **argv; ++i, ++p)
	{
		*p = **argv;
		++*argv;
	}
	printf("Input file name : %s\n", filename);

	FILE *f = fopen(filename, "rb");
	if (!f)
	{
		fprintf(stderr, "ERROR: Could not open file %s : %s\n", filename, strerror(errno));
		return 1;
	}
	if (fseek(f, 0, SEEK_END))
	{
		fprintf(stderr, "ERROR: Could not seek to the end of the file: %s\n", strerror(errno));
		fclose(f);
		return 1;
	}
	long int size = ftell(f);
	if (size == -1L)
	{
		fprintf(stderr, "ERROR: Could not read file size: %s\n", strerror(errno));
		fclose(f);
		return 1;
	}
	if (fseek(f, 0, SEEK_SET))
	{
		fprintf(stderr, "ERROR: Could not seek to the start of the file: %s\n", strerror(errno));
		fclose(f);
		return 1;
	}

	char *content = calloc(1, size + 1);
	if (!content)
	{
		fprintf(stderr, "ERROR: Could not allocate memory to read from the file (please buy more RAM): %s\n", strerror(errno));
		fclose(f);
		return 1;
	}

	const size_t readSize = fread(content, 1,size,  f);
	if (readSize != (size_t)size)
	{
		if (feof(f))
		{
			fprintf(stderr, "ERROR: Unexpected end of file: %s\n", strerror(errno));
		}
		else if (ferror(f))
		{
			fprintf(stderr, "ERROR: Could not read from file: %s\n", strerror(errno));
		}

		free(content);
		fclose(f);
		return 1;
	}
	fclose(f);

	int res = partOne(content);
	printf("Result = %d", res);

	free(content);


	printf("\nDone !\n");
	return 0;
}
