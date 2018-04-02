grammar DemoCompiler;

// ----------------------------------------------------------
// Parser Rules
// ----------------------------------------------------------

// Parser grammer begin rule name should be "program".
// It helps keeping other code chains working without change. For example, AST visualizer requires begin name.

program             : line+ EOF ;

line                : (name)+ NEWLINE ;

name                : WORD ;


// ----------------------------------------------------------
// Lexer Rules
// ----------------------------------------------------------

fragment LOWERCASE  : [a-z] ;
fragment UPPERCASE  : [A-Z] ;

WORD                : (LOWERCASE | UPPERCASE | '_')+ ;

WHITESPACE          : (' ' | '\t')+ -> skip;

NEWLINE             : ('\r'? '\n' | '\r')+ ;
