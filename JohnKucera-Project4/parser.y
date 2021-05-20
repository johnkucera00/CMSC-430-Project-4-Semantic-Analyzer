/* Creator: John Kucera (originated from Dr. Duane J. Jarc)
* Filename: parser.y (for Project 4)
* Date: May 4, 2021
* Code Description: parser.y is the bison input file that will call the lexical
* analyzer created from flex in order to generate a parser. It contains the
* grammar productions, token declarations, interpretations, and main function
* to call the parser.
*/

%{

#include <string>
#include <vector>
#include <map>

using namespace std;

#include "types.h"
#include "listing.h"
#include "symbols.h"

int yylex();
void yyerror(const char* message);

Symbols<Types> symbols;

bool began = false;

%}

%define parse.error verbose

%union
{
	CharPtr iden;
	Types type;
}

%token <iden> IDENTIFIER
%token <type> INT_LITERAL REAL_LITERAL BOOL_LITERAL

%token ADDOP MULOP RELOP ANDOP OROP REMOP EXPOP ARROWOP
%token BEGIN_ BOOLEAN END ENDREDUCE FUNCTION INTEGER IS REDUCE RETURNS
%token CASE ELSE ENDCASE ENDIF IF OTHERS REAL THEN WHEN NOT

%type <type> type statement statement_ reductions expression expression2 relation term
	factor primary exponent case unary

%%

function:
	function_header optional_variable body ;

function_header:
  FUNCTION IDENTIFIER RETURNS type ';' {storeReturnType($4);} |
  FUNCTION IDENTIFIER parameters RETURNS type ';' {storeReturnType($5);} |
  error ';' ;

parameters:
  parameter optional_parameter ;

optional_parameter:
  optional_parameter ',' parameter |
  ;

parameter:
	IDENTIFIER ':' type {symbols.insert($1, $3);} ;

optional_variable:
	optional_variable variable |
	;

variable:
	IDENTIFIER ':' type IS statement_
		{checkAssignment($3, $5, "Variable Initialization");
    symbols.findDuplicate($1, $3);
		symbols.insert($1, $3);} ;

type:
	INTEGER {$$ = INT_TYPE;} |
	BOOLEAN {$$ = BOOL_TYPE;} |
  REAL {$$ = REAL_TYPE;} ;

body:
	BEGIN_ {began = true;} statement_ END ';' ;

statement_:
	statement ';'
  {
    if (began == true) {
      checkReturnType($1);
    }
  } |
	error ';' {$$ = MISMATCH;} ;

statement:
	expression |
	REDUCE operator reductions ENDREDUCE {$$ = $3;} |
  IF expression THEN {checkIf($2);} statement_ ELSE statement_ ENDIF
	{
	checkThenElse($5, $7);
	if (began == true) {
		storeReturnType(REAL_TYPE);
	}} |
	CASE expression {checkCaseExpression($2);} IS cases OTHERS ARROWOP statement_ ENDCASE
	{
	checkCaseWhen($8, "Others");
	if (began == true) {
		storeReturnType(REAL_TYPE);
	}} ;

operator:
	ADDOP |
	MULOP ;

reductions:
	reductions statement_ {$$ = checkArithmetic($1, $2);} |
	{$$ = INT_TYPE;} ;

cases:
	WHEN INT_LITERAL ARROWOP statement_ {storeFirstWhen($4);} optional_case ;

optional_case:
  optional_case case |
  ;

case:
  WHEN INT_LITERAL ARROWOP statement_ {checkCaseWhen($4, "When");};

expression:
	expression OROP expression2 {checkLogical($1, $3);} |
	expression2 ;

expression2:
	expression2 ANDOP relation {checkLogical($1, $3);} |
	relation ;

relation:
	relation RELOP term {$$ = checkRelational($1, $3);} |
	term ;

term:
	term ADDOP factor {$$ = checkArithmetic($1, $3);} |
	factor ;

factor:
	factor MULOP primary {$$ = checkArithmetic($1, $3);} |
  factor REMOP primary {$$ = checkRemainder($1, $3);} |
  exponent ;

exponent:
  exponent EXPOP unary {$$ = checkArithmetic($1, $3);} |
  unary ;

unary:
  NOT primary {$$ = $2;} |
  primary ;

primary:
	'(' expression ')' {$$ = $2;} |
	INT_LITERAL {$$ = INT_TYPE;} |
  BOOL_LITERAL {$$ = BOOL_TYPE;} |
  REAL_LITERAL {$$ = REAL_TYPE;} |
	IDENTIFIER {if (!symbols.find($1, $$)) appendError(UNDECLARED, $1);} ;

%%

void yyerror(const char* message)
{
	appendError(SYNTAX, message);
}

int main(int argc, char *argv[])
{
	firstLine();
	yyparse();
	lastLine();
	return 0;
}
