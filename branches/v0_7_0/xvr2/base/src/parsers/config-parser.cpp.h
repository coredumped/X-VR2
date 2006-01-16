#ifndef YYERRCODE
#define YYERRCODE 256
#endif

#define TOK_ASSIGNMENT 257
#define TOK_COMMENT 258
#define TOK_INTEGER 259
#define TOK_FLOAT 260
#define TOK_STRING 261
#define TOK_VARIABLE 262
#define TOK_LITERAL_STRING 263
typedef union
{
int integer;
char *string;
double fp;
} YYSTYPE;
extern YYSTYPE __xvr2_cfg_yylval;
