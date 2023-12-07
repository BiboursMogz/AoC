#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <stdbool.h>

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

typedef struct 
{
	bool found;
	int result;
}probe_result;

probe_result probe(char* input)
{
	switch (*input)
	{
		case 'o':{

		} break;
	}
}

void recordNumber(const int Nbr,char* pNbr, char **pFirst, int* firstNbr, char **pLast, int *lastNbr)
{
	if (!(*pFirst))
	{
		*lastNbr = Nbr;
		*firstNbr = Nbr * 10;

		*pFirst = *pLast = pNbr;
	} else if (*pLast < pNbr)
	{
		*lastNbr = Nbr;
		*pLast = pNbr;
	}
}

int partTwo(char* input)
{
	int result = 0;

	int firstNbr = -1;
	char *pFirst = 0;

	int lastNbr = -1;
	char *pLast = 0;

	for (;*input; ++input)
	{
		char c = *input;

		if (('0' <= c) && (c <= '9'))
		{
			recordNumber(c - '0', input, &pFirst, &firstNbr, &pLast, &lastNbr);
		} 
		else if ((c == 'o') && (*(input + 1) == 'n') && (*(input + 2) == 'e'))
		{
			recordNumber(1, input, &pFirst, &firstNbr, &pLast, &lastNbr);
		} 
		else if ((c == 't') && (*(input + 1) == 'w') && (*(input + 2) == 'o'))
		{
			recordNumber(2, input, &pFirst, &firstNbr, &pLast, &lastNbr);
		}
		else if ((c == 't') && (*(input + 1) == 'h') && (*(input + 2) == 'r') && (*(input + 3) == 'e')&& (*(input + 4) == 'e'))
		{
			recordNumber(3, input, &pFirst, &firstNbr, &pLast, &lastNbr);
		}
		else if ((c == 'f') && (*(input + 1) == 'o') && (*(input + 2) == 'u') && (*(input + 3) == 'r'))
		{
			recordNumber(4, input, &pFirst, &firstNbr, &pLast, &lastNbr);
		}
		else if ((c == 'f') && (*(input + 1) == 'i') && (*(input + 2) == 'v') && (*(input + 3) == 'e'))
		{
			recordNumber(5, input, &pFirst, &firstNbr, &pLast, &lastNbr);
		}
		else if ((c == 's') && (*(input + 1) == 'i') && (*(input + 2) == 'x') )
		{
			recordNumber(6, input, &pFirst, &firstNbr, &pLast, &lastNbr);
		}
		else if ((c == 's') && (*(input + 1) == 'e') && (*(input + 2) == 'v') && (*(input + 3) == 'e')&& (*(input + 4) == 'n'))
		{
			recordNumber(7, input, &pFirst, &firstNbr, &pLast, &lastNbr);
		}
		else if ((c == 'e') && (*(input + 1) == 'i') && (*(input + 2) == 'g') && (*(input + 3) == 'h')&& (*(input + 4) == 't'))
		{
			recordNumber(8, input, &pFirst, &firstNbr, &pLast, &lastNbr);
		}
		else if ((c == 'n') && (*(input + 1) == 'i') && (*(input + 2) == 'n') && (*(input + 3) == 'e'))
		{
			recordNumber(9, input, &pFirst, &firstNbr, &pLast, &lastNbr);
		}
		else if (c == '\n')
		{
			result += firstNbr + lastNbr;

			pFirst = 0;
			pLast = 0;
			fprintf(stdout, "\t\tFound : %d and %d", firstNbr, lastNbr);
		}
		fprintf(stdout, "%c", c);

		//
		// for (char *probe = input;*probe; ++probe)
		// {
		//
		// 	fprintf(stdout, "%c", *probe);
		// }
	}

	/*
	* 'o' -> 'n' -> 'e'
	*/
	return result;
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

	// int res = partOne(content);
	int res = partTwo(content);
	printf("Result = %d", res);

	free(content);


	printf("\nDone !\n");
	return 0;
}
