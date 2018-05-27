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


// Anything that can make up a meaningful line or lines (If, While etc) are called statement.

stat
    :   block                                                   #BlockStatement
    |   varDecl ';'                                             #VarDeclStatement
    |   'if' '(' expr ')' stat ('else' stat)?                   #IfStatement
    |   forStatement                                            #Ignore
    |   'return' expr? ';'                                      #ReturnStatement
    |   'continue' ';'                                          #Continue
    |   assignment ';'                                          #Ignore
    |   expr ';'                                                #FuncCallStatement
    ;

// Expressions are part of statements. Anything that can be reduced to a value is called expression.

expr
    :   ID '(' exprList? ')'                        #FuncCallExpr           // Func call like f(), f(x), f(1,2)
    |   ('float' | 'int' | 'bool') '(' expr ')'     #ExplicitTypeConversion
//    |   ID '[' expr ']'                           #ArrayIndexExpr         // Array index like a[i]
    |   ('-' | '+') expr                            #UnaryExpr
    |   '!' expr                                    #LogicalNotExpr
    |   expr ('*'|'/') expr                         #AOPExpr
    |   expr ('+'|'-') expr                         #AOPExpr
    |   expr ('=='|'!='|'<='|'>='|'<'|'>') expr     #CompExpr
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
