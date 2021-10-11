grammar HGameAutoWired;
auto_wired : 'AUTO_WIRED' LeftParen Identifier ',' Identifier  RightParen;
auto_config : 'AUTO_CONFIG' LeftParen Identifier ',' Identifier  RightParen;

LeftParen: '(';
RightParen: ')';
Comma: ',';
WS : [ \t\r\n]+ -> skip ; // skip spaces, tabs, newlines, \r (Windows)

fragment NONZERODIGIT: [1-9];

fragment OCTALDIGIT: [0-7];

fragment HEXADECIMALDIGIT: [0-9a-fA-F];

fragment BINARYDIGIT: [01];

fragment Hexquad:
	HEXADECIMALDIGIT HEXADECIMALDIGIT HEXADECIMALDIGIT HEXADECIMALDIGIT;

fragment Universalcharactername:
	'\\u' Hexquad
	| '\\U' Hexquad Hexquad;

Identifier:
	Identifiernondigit (Identifiernondigit | DIGIT)*;

fragment Identifiernondigit: NONDIGIT | Universalcharactername;

fragment NONDIGIT: [a-zA-Z_];

fragment DIGIT: [0-9];
