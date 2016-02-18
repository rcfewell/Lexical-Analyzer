#include <iostream>
#include <fstream>
#include <string>
#include "lexicalAnalyzer.h"




lexicalAnalyzer::lexicalAnalyzer()
{
  errorCount = 0;
  lineCount = 0;
  pos = 0;
  line = " ";

}

lexicalAnalyzer:: lexicalAnalyzer( char * file )
{

  ifstream fin; 
  fin.open( file );

  while( getline( fin, line ) )
    {
      lines.push_back(line + '\n');
    }
  getLexeme();
  
}


tokenType lexicalAnalyzer::getToken(int s, string c)
{

  if (c == "int") return INTTYPE;
  if (c == "double") return DBLTYPE;
  switch(s) {
  case -1 : return ERROR;
  case 2 : return IDENT;
  case 4 : return NUMLIT;
  case 62 : return NUMLIT;
  case 63 : return NUMLIT;
  case 6 : return PLUSPLUS;
  case 7 : return PLUSEQ;
  case 8 : return PLUS;
  case 10 : return MINUSMINUS;
  case 11 : return MINUSEQ;
  case 12 : return MINUS;
  case 14 : return DIVEQ;
  case 15 : return DIV;
  case 17 : return MULTEQ;
  case 18 : return MULT;
  case 20 : return MODEQ;
  case 21 : return MOD;
  case 23 : return EQUALTO;
  case 24 : return ASSIGN;
  case 26 : return LTE;
  case 28 : return LT;
  case 29 : return SHIFTLEQ;
  case 30 : return SHIFTL;
  case 32 : return GTE;
  case 34 : return GT;
  case 35 : return SHIFTREQ;
  case 36 : return SHIFTR;
  case 38 : return ANDEQ;
  case 39 : return LOGAND;
  case 40 : return AND;
  case 42 : return XOREQ;
  case 43 : return XOR;
  case 45 : return OREQ;
  case 46 : return LOGOR;
  case 47 : return OR;
  case 49 : return NOTEQ;
  case 50 : return NOT;
  case 51 : return TILDA;
  case 52 : return LPAREN;
  case 53 : return RPAREN;
  case 54 : return SEMI;
  case 55 : return QUEST;
  case 56 : return COLON;
  case 57 : return COMMA;
  }
  return ERROR;
}

string lexicalAnalyzer::getLexeme()
{
  char currentChar;
  string lex = "";
  errorCount = 0;
  int cs = 0; //currentState
  string newLexemeValue;
  tokenType newLexemeType;

  for( int i = 0; i < lines.size(); i++ )
    {
      lineCount = i;
      cout << lineCount + 1 << ": " << lines[i];

      for( int j = 0; j < lines[i].length(); j++ )
	{
	  pos = j;
	  
	  currentChar = lines[i][j];
	  cs = state( cs, currentChar );
	  //cout << "\nTHIS IS THE CURRENT STATE " << cs << "\n";
	  if( !( isspace( currentChar ) ) && !newLex(cs) )
	    lex += currentChar;
	  if(isAccepting( cs ) ){
	    if( cs == -1 )
	      {
		lex = currentChar;
		cout << "Error at " << lineCount + 1 << ", " << pos + 1 << ": invalid character found: " << currentChar <<
		  endl;
		errorCount++;
	      }


	    newLexemeValue = lex;
	    newLexemeType = getToken( cs, lex);
	    

	    cout << "\t" << setToken(newLexemeType) << "\t" << newLexemeValue << endl;
	    
	    lex = "";

	    if(newLex(cs) && j < lines[i].size() -1 )
	      j--;

	    cs = 0;
	  }

	}

    }	
  
  cout << errorCount << " errors found in the input file." << endl;
}
int lexicalAnalyzer::state( int s, char c )
{
  if( c == '$' || c == '@' )
    return -1;

  switch( s )
    {
    case 0:
      if( isspace( c ) )
	return 0;
      else if( isalpha( c ) || c == '_' )
	return 1;
      else if( isdigit(c) )
	return 3;
      else if( c == '+' )
	return 5;
      else if( c == '-' )
	return 9;
      else if( c == '/' )
	return 13;
      else if( c == '*' )
	return 16;
      else if( c == '%' )
	return 19;
      else if( c == '=') 
	return 22;
      else if( c == '<' )
	return 25;
      else if( c == '>' )
	return 31;
      else if(c == '&')
	return 37;
      else if( c == '^' )
	return 41;
      else if( c == '|' )
	return 44;
      else if( c == '!' )
	return 48;
      else if( c == '~' )
	return 51;
      else if( c == '(' )
	return 52;
      else if( c == ')' )
	return 53;
      else if( c == ';' )
	return 54;
      else if( c == '.' )
	return 58;
    
    case 1:
      if( isalpha( c ) || c == '_' )
	return 1;
      else return 2;
    case 3:
      if( isdigit( c ) )
	return 3;
      else if( c == '.' )
	return 61;
      else return 4;
    case 5:
      if( c == '+' )
	return 6;
      else if( c == '+' )
	return 7;
      else return 8;
    case 9:
      if( c == '-' )
	return 10;
      else if( c == '=' )
	return 11;
      else return 12;
    case 13:
      if( c == '=' )
	return 14;
      else return 15;
    case 16:
      if( c == '=' )
	return 17;
      else return 18;
    case 19:
      if( c == '=' )
	return 20;
      else return 21;
    case 22:
      if( c == '=' )
	return 23;
      else return 24;
    case 25:
      if( c == '=' )
	return 26;
      else if( c == '<' )
	return 27;
      else return 28;
    case 27:
      if( c == '=' )
	return 29;
      else return 30;
    case 31:
      if( c == '=' )
	return 32;
      else if( c == '>' )
	return 33;
      else return 34;
    case 33:
      if( c == '=' )
	return 35;
      else return 36;
    case 37:
      if( c == '=' )
	return 38;
      else if( c == '&' )
	return 39;
      else return 40;
    case 41:
      if( c == '=' )
	return 42;
      else return 43;
    case 44:
      if( c == '=' )
	return 45;
      else if( c == '|' )
	return 46;
      else return 47;
    case 48:
      if( c == '=' )
	return 49;
      else return 50;
    case 58:
      if( isdigit( c ) )
	return 59;
      else return -1;
    case 59:
      if( isdigit( c ) )
	return 59;
      else return -1;
    case 61:
      if( isdigit( c ) )
	return 61;
      else return 62;

	     
    }
  
  return -1;
}

bool lexicalAnalyzer::newLex( int s )
{
  if( s == 2 || s == 4 || s == 8 || s == 12 || s == 15 || s == 18 || s == 21 || s == 24 || s == 28 || s == 30
      || s == 34 || s == 36 || s == 40 || s == 43 || s == 47 || s == 50 || s == 62 || s == 63 )
    return true;
  else return false;

}

bool lexicalAnalyzer::isAccepting( int s )
{
  if( s == -1 || s == 2 || s == 4 || s == 6 || s == 6 || s == 7 || s == 8 || s == 10 || s == 11 || s == 12 ||
      s == 14 || s == 15 || s == 17 || s == 18 || s == 20 || s == 21 || s == 23 || s == 24 || s == 26 ||
      s == 28 || s == 29 || s == 30 || s == 32 || s == 34 || s == 35 || s == 36 || s == 38 || s == 39 ||
      s == 40 || s == 42 || s == 43 || s == 45 || s == 46 || s == 47 || s == 49 || s == 50 || s == 51 ||
      s == 52 || s == 53 || s == 54 || s == 55 || s == 56 || s == 57 || s == 62 || s == 63 )
    return true;
  else return false;
}

string lexicalAnalyzer:: setToken( tokenType t )
{
  switch (t) {
  case ERROR : return "ERROR";
  case INTTYPE : return "INTTYPE";
  case DBLTYPE : return "DBLTYPE";
  case IDENT : return "IDENT";
  case NUMLIT : return "NUMLIT";
  case PLUSPLUS : return "PLUSPLUS";
  case PLUSEQ : return "PLUSEQ";
  case PLUS : return "PLUS";
  case MINUSMINUS : return "MINUSMINUS";
  case MINUSEQ : return "MINUSEQ";
  case MINUS : return "MINUS";
  case DIVEQ : return "DIVEQ";
  case DIV : return "DIV";
  case MULTEQ : return "MULTEQ";
  case MULT : return "MULT";
  case MODEQ : return "MODEQ";
  case MOD : return "MOD";
  case EQUALTO : return "EQUALTO";
  case ASSIGN : return "ASSIGN";
  case LTE : return "LTE";
  case LT : return "LT";
  case SHIFTLEQ : return "SHIFTLEQ";
  case SHIFTL : return "SHIFTL";
  case GTE : return "GTE";
  case GT : return "GT";
  case SHIFTREQ : return "SHIFTREQ";
  case SHIFTR : return "SHIFTR";
  case ANDEQ : return "ANDEQ";
  case AND : return "AND";
  case LOGAND : return "LOGAND";
  case XOREQ : return "XOREQ";
  case XOR : return "XOR";
  case OREQ : return "OREQ";
  case OR : return "OR";
  case LOGOR : return "LOGOR";
  case NOTEQ : return "NOTEQ";
  case NOT : return "NOT";
  case TILDA : return "TILDA";
  case LPAREN : return "LPAREN";
  case RPAREN : return "RPAREN";
  case SEMI : return "SEMI";
  case QUEST : return "QUEST";
  case COLON : return "COLON";
  case COMMA : return "COMMA";
  }
}
