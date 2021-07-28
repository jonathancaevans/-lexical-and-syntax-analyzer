/* 1.
<Lexeme> -> <Operator> | <Operand>
<Operator> -> '+' | '-' | '/' | '%' | '<' | '>' | '!'<SecondOp> | = | '='<SecondOp>
<SecondOp> -> =
<Operand> -> <Number> | <Variable>
<Variable> -> ((a-z)|(A-Z)) | ((a-z)|(A-Z))<Variable>
<Number> -> <Digit> | <Digit><Number> | <Decimal> | <Float>
<Decimal> -> '.'<Digit> | '.'<Digit><Float>
<Digit> -> (0-9) | <0-9><Digit>
<Float> -> 'X'<Digit>'E'<Digit>

2.
<Start> -> <Start> = <Equal> | <Equal>
<Equal> -> <Equal> == <Not Equal> | <Not Equal>
<Not Equal> -> <Not Equal> != <Less> | <Less>
<Less> -> <Less> < <Greater> | <Greater>
<Greater> -> <Greater> > <Add> | <Add>
<Add> -> <Add> + <Sub> | <Sub>
<Sub> -> <Sub> - <Mult> | <Mult>
<Mult> -> <Mult> * <Div> | <Div>
<Div> -> <Div> / <Mod> | <Mod>
<Mod> -> <Mod> % <Paren> | <Paren>
<Paren> -> (<Paren>)<Num> | <Num>
<Operands> -> <Operands> | <Operands><Operands>*/
#include <stdio.h>
#include <ctype.h>

/* Global declarations */
/* Variables */
int charClass;
char lexeme[100];
char nextChar;
int lexLen;
int token;
int nextToken;
FILE *in_fp;

/* Function declarations */
int lookup(char ch);
void addChar(void);
void getChar(void);
void getNonBlank(void);
int lex(void);

/* Character classes */
#define LETTER 0
#define DIGIT 1
#define UNKNOWN 99

/* Token codes */
#define INT_LIT 10
#define IDENT 11
#define ASSIGN_OP 20
#define ADD_OP 21
#define SUB_OP 22
#define MULT_OP 23
#define DIV_OP 24
#define LEFT_PAREN 25
#define RIGHT_PAREN 26
#define MOD 27
#define LESS 28
#define GREATER 29
#define NOT 30
#define EQUAL 31
#define ASSIGNMENT 32

/******************************************************/
/* main driver */
int main(void) {
	/* Open the input data file and process its contents */
	 if ((in_fp = fopen("front.in", "r")) == NULL)
	 	printf("ERROR - cannot open front.in \n");
	 else {
	 	getChar();
	 do {
	 	lex();
	 } while (nextToken != EOF);
	 }
	 return 0;
}
/******************************************************/
/* lookup - a function to look up operators and
 parentheses and return the token */
int lookup(char ch) {
	 switch (ch) {
		 case '(':
			 addChar();
			 nextToken = LEFT_PAREN;
			 break;
		 case ')':
			 addChar();
			 nextToken = RIGHT_PAREN;
			 break;
		 case '+':
			 addChar();
			 nextToken = ADD_OP;
			 break;
		 case '-':
			 addChar();
			 nextToken = SUB_OP;
			 break;
		 case '*':
			 addChar();
			 nextToken = MULT_OP;
			 break;
		 case '/':
			 addChar();
			 nextToken = DIV_OP;
			 break;
		 case '>':
			 addChar();
			 nextToken = LESS;
			 break;
		 case '<':
			 addChar();
			 nextToken = GREATER;
			 break;
		 case '!':
			 addChar();
			 nextToken = NOT;
			 break;
		 case '=':
			 addChar();
			 nextToken = EQUAL;
			 break;
		 case '%':
			 addChar();
			 nextToken = MOD;
			 break;
		 default:
			 addChar();
			 nextToken = EOF;
			 break;
	 }
	 return nextToken;
}

/******************************************************/
/* addChar - a function to add nextChar to lexeme */
void addChar(void) {
	if (lexLen <= 98) {
		lexeme[lexLen++] = nextChar;
		lexeme[lexLen] = '\0';
	} else
	printf("Error - lexeme is too long \n");
}


/******************************************************/
/* getChar - a function to get the next character of
 input and determine its character class */
void getChar(void) {
	 if ((nextChar = getc(in_fp)) != EOF) {
		 if (isalpha(nextChar))
		 	charClass = LETTER;
		 else if (isdigit(nextChar))
		 	charClass = DIGIT;
		 else
		 	charClass = UNKNOWN;
	 } else
	 	charClass = EOF;
}


/******************************************************/
/* getNonBlank - a function to call getChar until it
 returns a non-whitespace character */
void getNonBlank(void) {
	while (isspace(nextChar))
	getChar();
}

/******************************************************/
/* lex - a simple lexical analyzer for arithmetic
 expressions */
int lex(void) {
	 lexLen = 0;
	 getNonBlank();
	 switch (charClass) {
		/* Identifiers */
		 case LETTER:
			 addChar();
			 getChar();
			 while (charClass == LETTER || charClass == DIGIT) {
				 addChar();
				 getChar();
			 }
			 nextToken = IDENT;
			 break;
		/* Integer literals */
		 case DIGIT:
			 addChar();
			 getChar();
			 while (charClass == DIGIT) {
				 addChar();
				 getChar();
			 }
			 nextToken = INT_LIT;
		 	break;
		/* Parentheses and operators */
		 case UNKNOWN:
			 lookup(nextChar);
			 getChar();
			 break;
			/* EOF */
		case EOF:
			 nextToken = EOF;
			 lexeme[0] = 'E';
			 lexeme[1] = 'O';
			 lexeme[2] = 'F';
			 lexeme[3] = '\0';
		 	break;
	 } /* End of switch */
	 printf("Next token is: %d, Next lexeme is %s\n",
	 nextToken, lexeme);
	 return nextToken;
} /* End of function lex */
