%{ 
/*
 * $Id$
 */

#include <stdio.h>
#include <string.h>
#include "config-parser.h"
#include "ConfigFile.h"
#include "Memory.h"

extern int param_value_add(xvr2::Util::ConfigFile *store, const char *param_name, int data);
extern int param_value_add(xvr2::Util::ConfigFile *store, const char *param_name, double data);
extern int param_value_add(xvr2::Util::ConfigFile *store, const char *param_name, const char *data);

/** A reference to a bison/yacc generated parser */
extern int __xvr2_cfg_yyparse(void);
/** A reference to a flex/lex generated lexical analizer */
extern int __xvr2_cfg_yylex(void);

static xvr2::Util::ConfigFile *__pvStore;


void __xvr2_cfg_yyerror(const char *str)
{
	fprintf(stderr,"error: %s\n",str);
}

#ifdef __cplusplus
extern "C" {
#endif

int __xvr2_cfg_yywrap()
{
	return 1;
}
#ifdef __cplusplus
}
#endif


extern FILE *__xvr2_cfg_yyin;

/**
 * This function reads a file sets up a ConfigFile object by parsing its input file
 * and filling the plist anv vlist arrays with parameter names and value data.
 * This function is not intended to be used outside the scope of xvr2 so try not
 * to call it from outside the xvr2 internal code.
 */
int config_parse(xvr2::Util::ConfigFile *store, const char *filepath)
{
	int ret;
	__pvStore = store;
	__xvr2_cfg_yyin = fopen(filepath, "r");
	ret = __xvr2_cfg_yyparse();
	fclose(__xvr2_cfg_yyin);
	return ret;
}


%}

%token TOK_ASSIGNMENT 
%token TOK_COMMENT

%union
{
int integer;
char *string;
double fp;
}

%token <integer>TOK_INTEGER
%token <fp>TOK_FLOAT
%token <string>TOK_STRING
%token <string>TOK_VARIABLE
%token <string>TOK_PATH
%token <string>TOK_LITERAL_STRING

%%

expression:	/*empty */
		expr
		|
		expr expression
		;
		

expr:	/* empty */
	assig_str
	|
	assig_litstr
	|
	assig_int
	|
	assig_float
	|
	assig_path
	|
	TOK_COMMENT
	|
	error
	{
		yyerrok;
	}
	;
	
assig_litstr:
	TOK_VARIABLE TOK_ASSIGNMENT TOK_LITERAL_STRING
	{
#ifdef USE_DEBUG
		printf("\nPARAM[%s]=VALUE[%s]\n", $1, $3);
#endif
		param_value_add(__pvStore, (const char *)$1, (const char *)$3);
		xvr2::Memory::freeBuffer((void **)&($3));
	}

assig_str:
	TOK_VARIABLE TOK_ASSIGNMENT TOK_VARIABLE
	{
#ifdef USE_DEBUG
		printf("\nPARAM[%s]=VALUE[%s]\n", $1, $3);
#endif
		param_value_add(__pvStore, (const char *)$1, (const char *)$3);
		xvr2::Memory::freeBuffer((void **)&($3));
	}

assig_path:
	TOK_VARIABLE TOK_ASSIGNMENT TOK_PATH
	{
#ifdef USE_DEBUG
		printf("\nPARAM[%s]=VALUE[%s]\n", $1, $3);
#endif
		param_value_add(__pvStore, (const char *)$1, (const char *)$3);
		xvr2::Memory::freeBuffer((void **)&($3));
	}

assig_int:
	TOK_VARIABLE TOK_ASSIGNMENT TOK_INTEGER
	{
#ifdef USE_DEBUG
		printf("\nPARAM[%s]=VALUE[%d]\n", $1, $3);
#endif
		param_value_add(__pvStore, (const char *)$1, (int)$3);
	}

assig_float:
	TOK_VARIABLE TOK_ASSIGNMENT TOK_FLOAT
	{
#ifdef USE_DEBUG
		printf("\nPARAM[%s]=VALUE[%lf]\n", $1, (double)$3);
#endif
		param_value_add(__pvStore, (const char *)$1, (double)$3);
	}

%%
