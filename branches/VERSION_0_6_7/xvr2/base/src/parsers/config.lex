%{
/*
 * $Id$
 */
#include<stdio.h>
#include<string.h>
#include "config-parser.h"

static void __debug_msg(const char *msg){
#ifdef USE_DEBUG
	fprintf(stderr, "%s", msg);
#endif
}

static void __debug_comment(const char *msg){
#ifdef USE_DEBUG
	fprintf(stderr, "COMMENT *** %s ***\n", msg);
#endif
}

//int __xvr2_cfg_yywrap()

%}
%%
\".*\"				__xvr2_cfg_yylval.string = strdup((const char *)__xvr2_cfg_yytext); __debug_msg("LITERAL_STRING "); return TOK_LITERAL_STRING;
[0-9]+				__xvr2_cfg_yylval.integer = atoi((const char *)__xvr2_cfg_yytext); __debug_msg("INTEGER ") ; return TOK_INTEGER;
[+-]?[0-9]+[.[0-9]+]?		__xvr2_cfg_yylval.fp = atof((const char *)__xvr2_cfg_yytext); __debug_msg("FLOAT "); return TOK_FLOAT;
[_a-zA-Z][_0-9A-Za-z]*		__xvr2_cfg_yylval.string = strdup((const char *)__xvr2_cfg_yytext); __debug_msg("STRING "); return TOK_VARIABLE;
[/\._a-zA-Z0-9][/\._0-9A-Za-z]*		__xvr2_cfg_yylval.string = strdup((const char *)__xvr2_cfg_yytext); __debug_msg("PATH "); return TOK_PATH;
[:=]				__debug_msg("ASSIGN "); return TOK_ASSIGNMENT;
[ \t]+				/* ignore this thing */
\n				/* ignore this thing too */
#.*				__debug_comment(__xvr2_cfg_yytext); return TOK_COMMENT;
%%
