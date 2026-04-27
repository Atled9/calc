#include <stdlib.h>
#include <stdio.h>
#include "token/token.h"
#include "collections/collections.h"

double calc(Collection *rpn, int verbose)
{
	Collection *operands = initStack();
	double *valp;
	double l_operand;
	double r_operand;
	Operation operation;
	double result = 0.0;

	while (peek(rpn)) {

		if (verbose) {
			printf("%s ", getstr(peek(rpn)));
		}

		if (getp(peek(rpn)) == 0) {
			valp = (double *)malloc(sizeof(double));
			*valp = unpackoperand(dequeue(rpn));
			push(operands, valp);

		} else if (getu(peek(rpn))) {
			operation = unpackoperator(dequeue(rpn));

			if (!peek(operands)) {
				break;
			}
			valp = pop(operands);
			r_operand = *valp;
			free(valp);
			
			valp = (double *)malloc(sizeof(double));
			*valp = operation(0.0, r_operand);
			push(operands, valp);

		} else {
			operation = unpackoperator(dequeue(rpn));

			if (!peek(operands)) {
				break;
			}
			valp = pop(operands);
			r_operand = *valp;
			free(valp);

			if (!peek(operands)) {
				break;
			}
			valp = pop(operands);
			l_operand = *valp;
			free(valp);

			valp = (double *)malloc(sizeof(double));
			*valp = operation(l_operand, r_operand);
			push(operands, valp);
		}
	}
	if (verbose)
		printf("\n");

	if (peek(operands)) {
		valp = pop(operands);
		result = *valp;
		free(valp);
	}
	freeCollection(rpn);
	freeCollection(operands);

	return result;
}

Collection *shunt(Collection *in)
{
	Collection *out = initQueue();
	Collection *operators = initStack();

	while (peek(in)) {

		if (getp(peek(in)) == 0) {
			enqueue(out, dequeue(in));

		} else if (getp(peek(in)) == -1) {
			push(operators, dequeue(in));

		} else if (getp(peek(in)) == -2) {
			while (peek(operators) && getp(peek(operators)) != -1) {
				enqueue(out, pop(operators));
			}
			unpackoperator(pop(operators));
			unpackoperator(dequeue(in));	

			if (peek(operators) && getp(peek(operators)) == 4) {
				enqueue(out, pop(operators));
			}

		} else if (!peek(operators)) {
			push(operators, dequeue(in));


		} else if (getp(peek(in)) > getp(peek(operators)) ||
			   geta(peek(in)) && getp(peek(in)) == getp(peek(operators))) {
			push(operators, dequeue(in));

		} else {
			while(peek(operators) && getp(peek(operators)) > getp(peek(in))) {
				enqueue(out, pop(operators));
			}
			push(operators, dequeue(in));
		}
	}
	while (peek(operators)) {
		enqueue(out, pop(operators));
	}
	freeCollection(in);
	freeCollection(operators);

	return out;
}
