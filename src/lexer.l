%{
#include "y.tab.h"
#include <stdlib.h>
%}

%%
[a-zA-Z][a-zA-Z0-9]*   { yylval.str = strdup(yytext); return ID; }
[0-9]+                 { yylval.str = strdup(yytext); return NUM; }
"="                    { return ASSIGN; }
";"                    { return SEMI; }
"+"                    { return PLUS; }
"-"                    { return MINUS; }
"*"                    { return MUL; }
"/"                    { return DIV; }
"("                    { return LPAREN; }
")"                    { return RPAREN; }
[ \t\r\n]+             ; /* Ignore whitespace */
.                      { return yytext[0]; }
%%

int yywrap(void) {
    return 1;
}
