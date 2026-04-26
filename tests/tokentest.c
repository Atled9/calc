#include <stdio.h>
#include "../token/token.h"

int main()
{
	Token *token0 = pack("-3.0");
	Token *token1 = pack("*");
	Token *token2 = pack(4.0);

	printf("%d\n", getprecedence(token0));
	printf("%d\n", getprecedence(token1));

	double l_operand = unpackoperand(token0);
	double r_operand = unpackoperand(token2);
	Operation operation = unpackoperator(token1);

	double result = operation(l_operand, r_operand);
	printf("%lf\n", result);

	return 0;
}
