#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <time.h>


int isfloat(char *str);

static double sum(double l_operand, double r_operand);
static double difference(double l_operand, double r_operand);
static double product(double l_operand, double r_operand);
static double quotient(double l_operand, double r_operand);
static double mod(double l_operand, double r_operand);

static double sine(double dummy, double operand);
static double cosine(double dummy, double operand);
static double tangent(double dummy, double operand);

static double logarithm(double l_operand, double r_operand);
static double max(double l_operand, double r_operand);
static double randint(double l_operand, double r_operand);

typedef struct {
	union {
		double (*operator)(double, double);
		double operand;
	};
	char *arg;
	int precedence;
	int associativity;
	int unary;
} Token;

Token *packarg(char *str) 
{
	Token *token = (Token *)malloc(sizeof(Token));
	token->arg = str;

	if (isfloat(str)) {
		token->operand = atof(str);
		token->precedence = 0;
		token->associativity = 0;
		token->unary = 0;
		return token;
	}
	switch (*str) {
		case '(':
			token->operator = NULL;
			token->precedence = -1;
			token->associativity = 0;
			token->unary = 0;
			return token;
		case ')':
			token->operator = NULL;
			token->precedence = -2;
			token->associativity = 0;
			token->unary = 0;
			return token;
		case '+':
			token->operator = sum;
			token->precedence = 1;
			token->associativity = 0;
			token->unary = 0;
			return token;
		case '-':
			token->operator = difference;
			token->precedence = 1;
			token->associativity = 0;
			token->unary = 0;
			return token;
		case '*':
			token->operator = product;
			token->precedence = 2;
			token->associativity = 0;
			token->unary = 0;
			return token;
		case '/':
			token->operator = quotient;
			token->precedence = 2;
			token->associativity = 0;
			token->unary = 0;
			return token;
		case '%':
			token->operator = mod;
			token->precedence = 2;
			token->associativity = 0;
			token->unary = 0;
			return token;
		case '^':
			token->operator = pow;
			token->precedence = 3;
			token->associativity = 1;
			token->unary = 0;
			return token;
		case 'E':
			token->operand = M_E;
			token->precedence = 0;
			token->associativity = 0;
			token->unary = 0;
			return token;
	}
	if (strstr(str, "PI")) {
		token->operand = M_PI;
		token->precedence = 0;
		token->associativity = 0;
		token->unary = 0;
		return token;
	}
	if (strstr(str, "sin")) {
		token->operator = sine;
		token->precedence = 4;
		token->associativity = 0;
		token->unary = 1;
		return token;
	}
	if (strstr(str, "cos")) {
		token->operator = cosine;
		token->precedence = 4;
		token->associativity = 0;
		token->unary = 1;
		return token;
	}
	if (strstr(str, "tan")) {
		token->operator = tangent;
		token->precedence = 4;
		token->associativity = 0;
		token->unary = 1;
		return token;
	}

	if (strstr(str, "log")) {
		token->operator = logarithm;
		token->precedence = 4;
		token->associativity = 0;
		token->unary = 0;
		return token;
	}
	if (strstr(str, "max")) {
		token->operator = max;
		token->precedence = 4;
		token->associativity = 0;
		token->unary = 0;
		return token;
	}
	if (strstr(str, "rand")) {
		token->operator = randint;
		token->precedence = 4;
		token->associativity = 0;
		token->unary = 0;
		return token;
	}
	free(token);
	return NULL;
}
Token *packoperand(double operand)
{
	Token *token = (Token *)malloc(sizeof(Token));

	token->operand = operand;
	token->precedence = 0;
	return token;
}

double unpackoperand(Token *token)
{
	double operand = token->operand;
	free(token);
	return operand;
}
double (*unpackoperator(Token *token))(double, double)
{
	double (*operator)(double, double) = token->operator;
	free(token);
	return operator;
}

int getp(Token *token)
{
	return token->precedence;
}
int geta(Token *token)
{
	return token->associativity;
}
int getu(Token *token)
{
	return token->unary;
}
char *getstr(Token *token)
{
	return token->arg;
}

int isfloat(char *str)
{
	if (*str >= '0' && *str <= '9' ||
	    *str == '-' && *(str + 1) >= '0' && *(str + 1) <= '9' ||
	    *str == '+' && *(str + 1) >= '0' && *(str + 1) <= '9')
		return 1;
	return 0;
}

static double sum(double l_operand, double r_operand)
{
	return l_operand + r_operand;
}
static double difference(double l_operand, double r_operand)
{
	return l_operand - r_operand;
}
static double product(double l_operand, double r_operand)
{
	return l_operand * r_operand;
}
static double quotient(double l_operand, double r_operand)
{
	return l_operand / r_operand;
}
static double mod(double l_operand, double r_operand)
{
	return (int)l_operand % (int)r_operand;
}

static double sine(double dummy, double operand)
{
	return sin(operand);
}
static double cosine(double dummy, double operand)
{
	return cos(operand);
}
static double tangent(double dummy, double operand)
{
	return tan(operand);
}

static double logarithm(double l_operand, double r_operand)
{
	return (log(r_operand) / log(l_operand));
}
static double max(double l_operand, double r_operand)
{
	return l_operand > r_operand ? l_operand : r_operand;
}
static double randint(double l_operand, double r_operand)
{
	return rand() % (int)(r_operand - l_operand) + (int)l_operand;
}
