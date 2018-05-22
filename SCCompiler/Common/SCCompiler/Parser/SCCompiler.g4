//
//  Simple C Compiler Grammar File
//
//  Created by Arkin Terli on 3/31/18.
//  Copyright © 2018 Arkin Terli. All rights reserved.
//

grammar SCCompiler;


// ----------------------------------------------------------
// Parser Rules
// ----------------------------------------------------------

// Parser grammer begin rule name must be "program".

program
    :   (varDecl | functionDecl)+ EOF
    ;

varDecl
    :   type ID ('=' expr)? ';'
    ;

type
    :   'float' | 'int' | 'void' | 'bool'
    ;

functionDecl
    :   type ID '(' formalParameters? ')' '{' stat* '}'     #FuncDeclaration
    ;

formalParameters
    :   formalParameter (',' formalParameter)*
    ;

formalParameter
    :   type ID                                 #FuncArgDeclaration
    ;

block
    :  '{' stat* '}'
    ;


// Anything that can make up a meaningful line or lines (If, While etc) are called statement.

stat
    :   block                                   #BlockStatement         // Ignore
    |   varDecl                                 #VarDeclStatement       // Ignore
//    |   'if' '(' expr ')' stat ('else' stat)?   #IfStatement
    |   'return' expr? ';'                      #ReturnStatement
    |   expr '=' expr ';'                       #AssignmentStatement
    |   expr ';'                                #FuncCallStatement      // Ignore
    ;

exprList
    :   expr (',' expr)*        // Argument list
    ;


// Expressions are part of statements. Anything that can be reduced to a value is called expression.

expr
    :   ID '(' exprList? ')'    #FuncCallExpr       // Func call like f(), f(x), f(1,2)
    |   ('float' | 'int' | 'bool') '(' expr ')'     #ExplicitTypeConversion
//    |   ID '[' expr ']'         #ArrayIndexExpr     // Array index like a[i]
    |   ('-' | '+') expr        #UnaryExpr
//    |   '!' expr                #BoolNotExpr        // Boolean not
    |   expr ('*'|'/') expr     #AOPExpr
    |   expr ('+'|'-') expr     #AOPExpr
    |   expr ('=='|'!='|'<='|'>='|'<'|'>') expr     #CompExpr             // Comparison Operations
    |   (ID | FLOAT | INT | BOOL)    #LiteralExpr
    |   '(' expr ')'            #ParenthesisExpr      // Ignore
    ;


// ----------------------------------------------------------
// Lexer Rules
// ----------------------------------------------------------

// Reserved language words must be defined first in lexer.
BOOL
    :   ('true' | 'false')
    ;

fragment
DIGIT
    :   [0-9]
    ;

fragment
LETTER
    :   [a-zA-Z]
    ;

INT
    :   DIGIT+
    ;

FLOAT
    :   DIGIT+ '.' DIGIT+
    |   '.' DIGIT+ 'f'?
    ;

ID
    :   LETTER (LETTER | [0-9])*
    ;

WS
    :   [ \t\n\r]+ -> skip
    ;

LINECOMMENT
    :   '//' ~[\r\n]* -> skip
    ;

BLOCKCOMMENT
    :   '/*' .*? '*/' -> skip
    ;
