#ifndef TOKEN
#define TOKEN

int isfloat(char *str);

typedef struct Token Token;

Token *packarg(char *str);
Token *packoperand(double operand);
#define pack(T) _Generic((T),	\
char * : packarg,		\
double : packoperand)(T) 

double unpackoperand(Token *token);
double (*unpackoperator(Token *token))(double, double);
typedef double (*Operation)(double, double);

int getp(Token *token);
int geta(Token *token);
int getu(Token *token);
char *getstr(Token *token);

#endif
