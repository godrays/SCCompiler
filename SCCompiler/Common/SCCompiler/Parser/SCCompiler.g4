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

// Parser grammer begin rule name should be "program".
// It helps keeping other code chains working without change. For example, AST visualizer requires name 'program'.

program
    :   (varDecl | functionDecl)+
    ;

varDecl
    :   type ID ('=' expr)? ';'
    ;

type
    :   'float' | 'int' | 'void'
    ;

functionDecl
    :   type ID '(' formalParameters? ')' block
    ;

formalParameters
    :   formalParameter (',' formalParameter)*
    ;

formalParameter
    :   type ID
    ;

block
    :  '{' stat* '}'
    ;

stat
    :   block                                   #BlockStatement
    |   varDecl                                 #VarDeclStatement
    |   'if' '(' expr ')' stat ('else' stat)?   #IfStatement
    |   'return' expr? ';'                      #ReturnStatement
    |   expr '=' expr ';'                       #AssignmentStatement    // assignment
    |   expr ';'                                #FuncCallStatement      // func call
    ;


exprList
    :   expr (',' expr)*        // arg list
    ;

expr
    :   ID '(' exprList? ')'    #FuncCallExpr       // func call like f(), f(x), f(1,2)
    |   ID '[' expr ']'         #ArrayIndexExpr     // array index like a[i], a[i][j]
    |   '-' expr                #UnaryNegationExpr
    |   '!' expr                #BoolNotExpr        // boolean not
    |   expr ('*'|'/') expr     #MulDivExpr
    |   expr ('+'|'-') expr     #PlusMinusExpr
    |   expr '==' expr          #CompExpr           // equality comparison (lowest priority op)
    |   ID                      #VarRefExpr         // variable reference
    |   number                  #NumberExpr
    |   '(' expr ')'            #ParanthesisExpr
    ;

number
    :   FLOAT
    |   INT
    ;


// ----------------------------------------------------------
// Lexer Rules
// ----------------------------------------------------------

ID
    :   LETTER (LETTER | [0-9])*
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
    |   '.' DIGIT+
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
