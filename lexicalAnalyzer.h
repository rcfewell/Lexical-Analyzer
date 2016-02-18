#ifndef LEXICALANALYZER_H
#define LEXICALANALYZER_H
#include <iostream>
#include <string>
#include <vector>

using namespace std;

enum tokenType{ERROR, IDENT, INTTYPE, DBLTYPE, NUMLIT, PLUS, MINUS, MULT,
	       DIV, MOD, EXP, NOT, AND, OR, XOR, ASSIGN, LT, GT, SHIFTL,
	       SHIFTR, PLUSPLUS, PLUSEQ, MINUSMINUS, MINUSEQ, MULTEQ,
	       DIVEQ, MODEQ, EXPEQ, NOTEQ, LOGAND, ANDEQ, LOGOR, OREQ,
	       XOREQ, EQUALTO, SHIFTLEQ, LTE, SHIFTREQ, GTE, TILDA, RPAREN,
	       LPAREN, SEMI, QUEST, COLON, COMMA, EOFT};

class lexicalAnalyzer
{
 public:
  lexicalAnalyzer();
  lexicalAnalyzer(char * file);
  enum tokenType getToken ();
  string getLexeme ();
  void errorMessage( string msg );
  void endLex ();
  
 private:
  
  string line;
  int errorCount, lineCount, pos;
  vector<string> lines;
  vector<string> lexeme;
  
};

#endif
