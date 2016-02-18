/*
  Author: Riley Fewell
  Date 10-12-14
  Title: Project 1
*/

#include "SetLimits.h"
#include "lexicalAnalyzer.h"
#include <iostream>
#include <fstream>
#include <cstdlib>
#include <vector>


using namespace std;

int main( int argc, char * argv [] )
{
  
  SetLimits();
  
  enum tokenType t;


  lexicalAnalyzer lex( argv[1] );


  
  return 0;

}
