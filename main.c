#include <stdio.h>
#include "token/token.h"
#include "collections/collections.h"

double calc(Collection *in, int verbose);
Collection *shunt(Collection *in);

int main(int argc, char **argv)
{
	int postfix = 0;
	int verbose = 0;
	char **argp = argv + 1;

	char *optp = NULL;
	while (argp < argv + argc && **argp == '-' && !isfloat(*argp)) {

		optp = *argp + 1;
		while (*optp) {

			switch(*optp) {
				case 'p':
					postfix = 1;
					break;
				case 'v':
					verbose = 1;
					break;
				case 'l':
					printf("listing currently saved variables\n");
					break;
				default:
					printf("\'%c\' is not a valid option\n", *optp);
					return 0;
			}
			optp++;
		}
		argp++;
	}
	Token *tokenp;
	Collection *in = initQueue();

	while (argp < argv + argc) {
		tokenp = pack(*argp);

		if (!tokenp) {
			printf("Cannot parse \"%s\"\n", *argp);
			printf("Aborting\n");
			freeCollection(in);
			return 0;
		}
		enqueue(in, tokenp);
		argp++;
	}
	double result;

	if (postfix)
		result = calc(in, verbose);
	else
		result = calc(shunt(in), verbose);

	printf("%lf\n", result);
	return 0;
}
