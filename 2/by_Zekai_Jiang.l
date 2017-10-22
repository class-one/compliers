%{
  #include <stdlib.h>
  #include <stdio.h>

  #define FOR 1
  #define IF 2
  #define THEN 3
  #define ELSE 4
  #define WHILE 5
  #define DO 6
  #define ID 10
  #define NUMBER 11
  #define PLUS 13
  #define MINUS 14
  #define ASTERISK 15   //  '*'
  #define SLASH 16      //  '/'
  #define COLON 17      //  ':'
  #define EQUAL 18      //  ':='
  #define LT 20         //  '<'
  #define NE 21         //  '<>'
  #define LE 22         //  '<='
  #define GT 23         //  '>'
  #define GE 24         //  '>='
  #define EVA 25        //  '='
  #define SEMI 26
  #define LB 27
  #define RB  28
  #define UNTIL 29
  #define INT 30
  #define INPUT 31
  #define OUTPUT 32
  #define HASHTAG 0
  #define ERRORCHAR 255

%}


delim       [ \t \n]
ws          {delim}+
letter      [A-Za-z_]
digit       [0-9]
id          {letter}({letter}|{digit})*
number      {digit}+(\.{digit}+)?(E[+-]?{digit}+)?|{digit}+\/{digit}+

/* 状态（或条件）定义可以定义在这里
 * INITIAL是一个默认的状态，不需要定义
 */
%s COMMENT
%s COMMENT2
%%

<INITIAL>"/*"                     {BEGIN COMMENT;}
<COMMENT>"*/"                     {BEGIN INITIAL;}
<COMMENT>.|\n                     {;}
<INITIAL>"//"                     {BEGIN COMMENT2;}
<COMMENT2>\n                      {BEGIN INITIAL;}
<COMMENT2>.                       {;}

 /* ECHO是一个宏，相当于 fprintf(yyout, "%s", yytext)*/

<INITIAL>{ws}  {;}
<INITIAL>while {return (WHILE);}
<INITIAL>do {return (DO);}
<INITIAL>then {return (THEN);}
<INITIAL>"<" {return (LT);}
<INITIAL>"<=" {return (LE);}
<INITIAL>"=" {return (EVA);}
<INITIAL>"<>" {return (NE);}
<INITIAL>">" {return (GT);}
<INITIAL>">=" {return (GE);}
<INITIAL>for {return (FOR);}
<INITIAL>if {return(IF);}
<INITIAL>else {return(ELSE);}
<INITIAL>until {return(UNTIL);}
<INITIAL>int {return(INT);}
<INITIAL>input {return(INPUT);}
<INITIAL>output {return(OUTPUT);}
<INITIAL>"+" {return(PLUS);}
<INITIAL>"-" {return(MINUS);}
<INITIAL>"*" {return(ASTERISK);}
<INITIAL>"/" {return(SLASH);}
<INITIAL>":" {return(COLON);}
<INITIAL>":=" {return(EQUAL);}
<INITIAL>"#" {return(HASHTAG);}
<INITIAL>"(" {return(LB);}
<INITIAL>")" {return(RB);}
<INITIAL>";" {return(SEMI);}
<INITIAL>{id} {return (ID);}
<INITIAL>{number} {return (NUMBER);}
<INITIAL>. {return ERRORCHAR;}


%%

int yywrap() {
  return 1;
}

void analysis(int a) {
  switch(a) {
    case ERRORCHAR: fprintf(yyout, "(%d, %s) ", ERRORCHAR, yytext);break;
    case PLUS:  fprintf(yyout, "(%d, %s) ", PLUS, yytext);break;
    case MINUS: fprintf(yyout, "(%d, %s) ", MINUS, yytext);break;
    case ASTERISK:  fprintf(yyout, "(%d, %s) ", ASTERISK, yytext);break;
    case SLASH: fprintf(yyout, "(%d, %s) ", SLASH, yytext);break;
    case COLON:  fprintf(yyout, "(%d, %s) ", COLON, yytext);break;
    case EQUAL: fprintf(yyout, "(%d, %s) ", EQUAL, yytext);break;
    case LT:  fprintf(yyout, "(%d, %s) ", LT, yytext);break;
    case NE:  fprintf(yyout, "(%d, %s) ", NE, yytext);break;
    case LE:  fprintf(yyout, "(%d, %s) ", LE, yytext);break;
    case GT:  fprintf(yyout, "(%d, %s) ", GT, yytext);break;
    case GE:  fprintf(yyout, "(%d, %s) ", GE, yytext);break;
    case EVA: fprintf(yyout, "(%d, %s) ", EVA, yytext);break;
    case SEMI:  fprintf(yyout, "(%d, %s) ", SEMI, yytext);break;
    case LB:  fprintf(yyout, "(%d, %s) ", LB, yytext);break;
    case RB:  fprintf(yyout, "(%d, %s) ", RB, yytext);break;
    case UNTIL: fprintf(yyout, "(%d, %s) ", UNTIL, yytext);break;
    case INT: fprintf(yyout, "(%d, %s) ", INT, yytext);break;
    case INPUT: fprintf(yyout, "(%d, %s) ", INPUT, yytext);break;
    case OUTPUT:  fprintf(yyout, "(%d, %s) ", OUTPUT, yytext);break;
    case HASHTAG: fprintf(yyout, "(%d, %s) ", HASHTAG, yytext);break;
    case WHILE: fprintf(yyout, "(%d, %s) ", WHILE, yytext);break;
    case DO: fprintf(yyout, "(%d, %s) ", DO, yytext);break;
    case IF: fprintf(yyout, "(%d, %s) ", IF, yytext);break;
    case THEN: fprintf(yyout, "(%d, %s) ", THEN, yytext);break;
    case ELSE: fprintf(yyout, "(%d, %s) ", ELSE, yytext);break;
    case NUMBER: fprintf(yyout, "(%d, %s) ", NUMBER, yytext);break;
    case ID: fprintf(yyout, "(%d, %s) ", ID, yytext);break;
    default:break;
    }
    return ;
  }

  int main(int argc, char ** argv) {
    int c;
    if (argc>=2){
      if ((yyin = fopen(argv[1], "r")) == NULL){
        printf("Can't open file %s\n", argv[1]);
        return 1;
      }
      if (argc>=3){
        yyout=fopen(argv[2], "w");
      }
    }

    while (c = yylex()){
        analysis(c);
        printf("\n");
    }
    if(argc>=2){
      fclose(yyin);
      if (argc>=3) fclose(yyout);
    }
    return 0;
}
