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
  getToken();
  
}


tokenType lexicalAnalyzer::getToken()
{
  int spaces = 0;
  char currentChar;
  string lex = "";
  for( int i = 0; i < lines.size(); i++ )
    {
      lex = "";
      spaces = 0;
      lineCount = i;
      //cout << lineCount + 1 << ": " << lines[i];

      for( int j = 0; j < lines[i].length(); j++ )
	{
	  pos = j;
	  currentChar = lines[lineCount][pos];
	  
	  if( !(isspace( currentChar ) ) )
	    //lexeme.push_back( string( 1, currentChar) );
	    lex += currentChar;
	  else
	    //lexeme.push_back( " " );
	    lex += " ";
	}
      //getLexeme();
      //cout << lex << endl;
      //
      //lexeme.push_back( lex );
      //getLexeme();
    }
  //string currentLex = getLexeme();
}

string lexicalAnalyzer::getLexeme()
{
  for( int i = 0; i < lexeme.size(); i++ )
    //cout << lexeme[i] << endl;
    //return lexeme[i];
  return "yes";
}
