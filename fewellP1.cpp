#include "lexicalAnalyzer.h"
#include <iostream>
#include <fstream>
#include <cstdlib>
#include <vector>

using namespace std;

int main( int argc, char * argv [] )
{

  enum tokenType t;

  //lexicalAnalyzer();
  lexicalAnalyzer lex( argv[1] );


  
  return 0;

}
