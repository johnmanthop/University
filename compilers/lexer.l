%{
    #include <stdio.h>
    #include <string.h>
    #include "y.tab.h"
%}

a [aA]
b [bB]
c [cC]
d [dD]
e [eE]
f [fF]
g [gG]
h [hH]
i [iI]
j [jJ]
k [kK]
l [lL]
m [mM]
n [nN]
o [oO]
p [pP]
q [qQ]
r [rR]
s [sS]
t [tT]
u [uU]
v [vV]
w [wW]
x [xX]
y [yY]
z [zZ] 


POSITIVEDIGIT [1-9]
DIGIT         [0-9]
LETTERDIGIT   [a-zA-Z0-9]
HEXDIGIT      [0-9a-fA-F]
POSITIVEHEX   [1-9a-fA-F]
OCTALDIGIT    [0-7]
POSITIVEOCTAL [1-7]
LETTER        [a-zA-Z]
BINARY        [01]
POSITIVEBIN   [1]
PRINTABLE     [ !"#&%'()*+,`\-./0-9:;<=>?@A-Z[\]^_a-z{|}~]
SPRINTABLE    [ !#&%'()*+,`\-./0-9:;<=>?@A-Z[\]^_a-z{|}~]
SPECIALCHARS  (\\f)|(\\n)|(\\t)|(\\r)|(\\b)|(\\v)|(\\)



P1 ({POSITIVEDIGIT}{DIGIT}*)?\.{DIGIT}*{POSITIVEDIGIT}{DIGIT}*
P2 {POSITIVEDIGIT}{DIGIT}*(\.({DIGIT}*{POSITIVEDIGIT}{DIGIT}*)*)?
P3 0\.({DIGIT}*{POSITIVEDIGIT}{DIGIT}*)?
P4 {P1}|{P2}|{P3}
P5 {P4}({e}\-?({POSITIVEDIGIT}{DIGIT}*|0))?

H1 ({POSITIVEHEX}{HEXDIGIT}*)?\.{HEXDIGIT}*{POSITIVEHEX}{HEXDIGIT}*
H2 {POSITIVEHEX}{HEXDIGIT}*(\.({HEXDIGIT}*{POSITIVEHEX}{HEXDIGIT}*)*)?
H3 0\.({HEXDIGIT}*{POSITIVEHEX}{HEXDIGIT}*)?

O1 ({POSITIVEOCTAL}{OCTALDIGIT}*)?\.{OCTALDIGIT}*{POSITIVEOCTAL}{OCTALDIGIT}*
O2 {POSITIVEOCTAL}{OCTALDIGIT}*(\.({OCTALDIGIT}*{POSITIVEOCTAL}{OCTALDIGIT}*)*)?
O3 0\.({OCTALDIGIT}*{POSITIVEOCTAL}{OCTALDIGIT}*)?

B1 ({POSITIVEBIN}{BINARY}*)?\.{BINARY}*{POSITIVEBIN}{BINARY}*
B2 {POSITIVEBIN}{BINARY}*(\.({BINARY}*{POSITIVEBIN}{BINARY}*)*)?
B3 0\.{BINARY}*{POSITIVEBIN}{BINARY}*

RCONST {P5}|(0{x}{H1})|(0{x}{H2})|(0{x}{H3})|(0{o}{O1})|(0{o}{O2})|(0{o}{O3})|(0{b}{B1})|(0{b}{B2})|(0{b}{B3})

LISTFUNC {c}(({d}*{a}{d}*)|({d}+)){r} 
ICONST ({POSITIVEDIGIT}({DIGIT}*))|(0{x}{POSITIVEHEX}{HEXDIGIT}*)|(0{o}{POSITIVEOCTAL}{OCTALDIGIT}*)|(0{b}1{BINARY}*)|0 
LCONST (\.{t}{r}{u}{e}\.)|(\.{f}{a}{l}{s}{e}\.)
CCONST ('{PRINTABLE}')|('{SPECIALCHARS}')
SCONST (\"(({SPRINTABLE}|{SPECIALCHARS})|(\\)|(\\\")|(\\\n))*\")
OROP   (\.{o}{r}\.)
ANDOP  (\.{a}{n}{d}\.)
NOTOP  (\.{n}{o}{t}\.)
RELOP  (\.{g}{t}\.)|(\.{g}{e}\.)|(\.{l}{t}\.)|(\.{l}{e}\.)|(\.{e}{q}\.)|(\.{n}{e}\.)
ADDOP  (\+)|(\-)
MULOP  (\*)
DIVOP  (\/)
POWOP  (\*\*)

ID     {LETTER}((_?(({LETTERDIGIT})+_)*)|({LETTERDIGIT})*|_) 
LPAREN \(
RPAREN \)
COMMA  ,
ASSIGN =
COLON  :
LBRACK \[
RBRACK \]
COMMENT \$.*


%%
{COMMENT}                       { /*Nothing*/ }
{f}{u}{n}{c}{t}{i}{o}{n}        { return T_function; } 
{s}{u}{b}{r}{o}{u}{t}{i}{n}{e}  { return T_subroutine; }
{e}{n}{d}                       { return T_end; }
{c}{o}{m}{m}{o}{n}              { return T_common; }
{l}{i}{s}{t}                    { return T_list; }
{d}{a}{t}{a}                    { return T_data; }
{c}{o}{n}{t}{i}{n}{u}{e}        { return T_continue; }
{g}{o}{t}{o}                    { return T_goto; }
{c}{a}{l}{l}                    { return T_call; }
{r}{e}{a}{d}                    { return T_read; }
{w}{r}{i}{t}{e}                 { return T_write; }
{l}{e}{n}{g}{t}{h}              { return T_length; }
{n}{e}{w}                       { return T_new; }
{i}{f}                          { return T_if; }
{t}{h}{e}{n}                    { return T_then; }
{e}{l}{s}{e}                    { return T_else; }
{e}{n}{d}{i}{f}                 { return T_endif; }
{d}{o}                          { return T_do; }
{e}{n}{d}{d}{o}                 { return T_enddo; }
{s}{t}{o}{p}                    { return T_stop; }
{r}{e}{t}{u}{r}{n}              { return T_return; }
{i}{n}{t}{e}{g}{e}{r}		    { return T_intlit; }
{r}{e}{a}{l}			        { return T_reallit; }
{c}{o}{m}{p}{l}{e}{x}	        { return T_complexlit; }
{l}{o}{g}{i}{c}{a}{l}		    { return T_logicallit; }
{c}{h}{a}{r}{a}{c}{t}{e}{r}	    { return T_characterlit; }
{s}{t}{r}{i}{n}{g}		        { return T_stringlit; }
{ICONST}                        { yylval.strvalue = strdup(yytext); return T_integer; }
{RCONST}			            { yylval.strvalue = strdup(yytext); return T_real; }
{LCONST}                        { yylval.strvalue = strdup(yytext); return T_logical; }
{CCONST}                        { yylval.strvalue = strdup(yytext); return T_character; }
{SCONST}                        { yylval.strvalue = strdup(yytext); return T_string; }
{OROP}                          { return T_orop; }                         
{ANDOP}                         { return T_andop; }
{NOTOP}                         { return T_notop; }
{RELOP}                         { yylval.strvalue = strdup(yytext); return T_relop; }
{ADDOP}                         { yylval.strvalue = strdup(yytext); return T_addop; }
{MULOP}                         { return T_mulop; }
{DIVOP}                         { return T_divop; }
{POWOP}                         { return T_powop; }
{LPAREN}                        { return T_lparen; }
{RPAREN}                        { return T_rparen; }
{COMMA}                         { return T_comma; }
{ASSIGN}                        { return T_assign; }
{COLON}                         { return T_colon; }                 
{LISTFUNC}                      { yylval.strvalue = strdup(yytext); return T_listfunc; }
{LBRACK}                        { return T_lbrack; }
{RBRACK}                        { return T_rbrack; }
{ID}                            { yylval.strvalue = strdup(yytext); return T_id; }
[,\.\(\)=\[\]\+\-\*\\_]         { return yytext[0]; }
[ ]                             {}
\n {}
<<EOF>>     { return 0; }

%%

int yywrap() { return 1; }

