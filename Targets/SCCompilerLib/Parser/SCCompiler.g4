//
//  Simple C Compiler Grammar File
//
//  Created by Arkin Terli on 3/31/18.
//  Copyright © 2018-Present, Arkin Terli. All rights reserved.
//

grammar SCCompiler;


// ----------------------------------------------------------
// Parser Rules
// ----------------------------------------------------------

// Parser grammar begin rule name must be "program".

program
    :   (varDecl ';' | functionDecl)+ EOF
    ;

varDecl
    :   type varInit (',' varInit)*
    ;

varInit
    :   ID ('=' expr)?
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


// Anything that can make up a meaningful line or lines (if, while, etc.) is called a statement.

stat
    :   block                                                   #BlockStatement
    |   varDecl ';'                                             #VarDeclStatement
    |   'if' '(' expr ')' stat ('else' stat)?                   #IfStatement
    |   forStatement                                            #Ignore
    |   'while' '(' expr ')' stat                               #WhileStatement
    |   'do' stat 'while' '(' expr ')' ';'                      #DoWhileStatement
    |   'return' expr? ';'                                      #ReturnStatement
    |   'continue' ';'                                          #Continue
    |   'break' ';'                                             #Break
    |   assignment ';'                                          #Ignore
    |   expr ';'                                                #FuncCallStatement
    ;

// Expressions are parts of statements. Anything that can be reduced to a value is called an expression.

expr
    :   ID '(' exprList? ')'                        #FuncCallExpr
    |   ('float' | 'int' | 'bool') '(' expr ')'     #ExplicitTypeConversion
//    |   ID '[' expr ']'                           #ArrayIndexExpr
    |   ('++'|'--') ID                              #PrefixAOPExpr
    |   ('-' | '+') expr                            #UnaryExpr
    |   '!' expr                                    #LogicalNotOPExpr
    |   expr ('*'|'/') expr                         #AOPExpr
    |   expr ('+'|'-') expr                         #AOPExpr
    |   expr ('<'|'<='|'>'|'>=') expr               #CompExpr
    |   expr ('=='|'!=') expr                       #CompExpr
    |   expr '&&' expr                              #LogicalOPExpr
    |   expr '||' expr                              #LogicalOPExpr
    |   (ID | FLOAT | INT | BOOL)                   #LiteralExpr
    |   '(' expr ')'                                #ParenthesisExpr
    ;

exprList
    :   expr (',' expr)*        // Argument list
    ;

assignment
    :   expr '=' expr
    ;

forStatement
    :   'for' '(' forVarDecl ';' forCondition ';' forIncrements ')'  stat
    ;

forVarDecl
    :   varDecl?
    ;

forCondition
    : expr?
    ;

forIncrements
    :   (forInc (',' forInc)*)?
    ;

forInc
    :   expr
    |   assignment
    ;


// ----------------------------------------------------------
// Lexer Rules
// ----------------------------------------------------------

// Reserved language words must be defined first in lexer.
BOOL
    :   ('true' | 'false')
    ;

fragment UNDERSCORE
    :   '_'
    ;

fragment DIGIT
    :   [0-9]
    ;

fragment LETTER
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
    :   UNDERSCORE* LETTER (LETTER | [0-9] | UNDERSCORE)*
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
