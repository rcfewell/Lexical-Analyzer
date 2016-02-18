
#include <iostream>
#include <vector>
#include <fstream>

using namespace std;

enum token_type {ERROR, IDENT, INTTYPE, DBLTYPE, NUMLIT, PLUS, MINUS, MULT,
		 DIV, MOD, EXP, NOT, AND, OR, XOR, ASSIGN, LT, GT, SHIFTL,
		 SHIFTR, PLUSPLUS, PLUSEQ, MINUSMINUS, MINUSEQ, MULTEQ,
		 DIVEQ, MODEQ, EXPEQ, NOTEQ, LOGAND, ANDEQ, LOGOR, OREQ,
		 XOREQ, EQUALTO, SHIFTLEQ, LTE, SHIFTREQ, GTE, TILDA, RPAREN,
		 LPAREN, SEMI, QUEST, COLON, COMMA, EOFT};

struct lexeme
{
  token_type type;
  string value;
};

void readIn(char *f, vector<string> &lines);
void parseLexemes(vector<string> lines, vector<lexeme> &lexemes);
int newState(int state, char currChar);
bool accepting(int state);
token_type setToken(int state, string value);
string getToken(token_type token);
bool foundNewLexeme(int state);

int main(int argc, char* argv[])
{
  int state;
  vector<string> lines;
  vector<lexeme> lexemes;

  readIn(argv[1], lines);
  parseLexemes(lines, lexemes);
}

void readIn(char *f, vector<string> &lines)
{
  ifstream file;
  file.open(f);
  string line;

  while(getline(file, line)) {
    lines.push_back(line + '\n');
  }
}

void parseLexemes(vector<string> lines, vector<lexeme> &lexemes)
{
  int state = 0;
  char currChar;
  string lexemeValue = "";
  int numErrors = 0;

  for (int i = 0; i < lines.size(); i++) {
    cout << "   " << i + 1 << ": " << lines[i];

    for (int j = 0; j < lines[i].size(); j++) {

      currChar = lines[i][j];
      state = newState(state, currChar);

      if (currChar == '\n') currChar = ' ';
      if (currChar != ' ' && !foundNewLexeme(state))
	lexemeValue += currChar;

      if (accepting(state)) {
	if (state == -1) {
	  lexemeValue = currChar;
	  cout << "Error at " << i + 1 << "," << j + 1 << ": Invalid character found: " << currChar << endl;
	  numErrors++;
	}

	lexeme newLexeme;
	newLexeme.value = lexemeValue;
	newLexeme.type = setToken(state, lexemeValue);
	lexemes.push_back(newLexeme);

	cout << "\t" << getToken(newLexeme.type) << "\t" << newLexeme.value << endl;

	lexemeValue = "";

	if (foundNewLexeme(state) && j < lines[i].size() - 1) {
	  j--;
	}

	state = 0;
      }
    }
  }
  cout << numErrors << " errors found in input file";
}

int newState(int state, char currChar)
{
  if (currChar == '@' || currChar == '$') return -1;

  switch (state) {
  case 0 :
    if (currChar == ' ' || currChar == '\n') return 0;
    if (isalpha(currChar) || currChar == '_') return 1;
    if (isdigit(currChar)) return 3;
    switch(currChar) {
    case '+' : return 5;
    case '-' : return 9;
    case '/' : return 13;
    case '*' : return 16;
    case '%' : return 19;
    case '=' : return 22;
    case '<' : return 25;
    case '>' : return 31;
    case '&' : return 37;
    case '^' : return 41;
    case '|' : return 44;
    case '!' : return 48;
    case '~' : return 51;
    case '(' : return 52;
    case ')' : return 53;
    case ';' : return 54;
    case '?' : return 55;
    case ':' : return 56;
    case ',' : return 57;
    case '.' : return 58;
    }
  case 1 :
    if (isalpha(currChar) || currChar == '_') return 1;
    else return 2;
  case 3 :
    if (isdigit(currChar)) return 3;
    else if (currChar == '.') return 61;
    else return 4;
  case 61 :
    if (isdigit(currChar)) return 61;
    else return 62;
  case 5 :
    if (currChar == '+') return 6;
    else if (currChar == '=') return 7;
    else return 8;
  case 9 :
    if (currChar == '-') return 10;
    else if (currChar == '=') return 11;
    else return 12;
  case 13 :
    if (currChar == '=') return 14;
    else return 15;
  case 16 :
    if (currChar == '=') return 17;
    else return 18;
  case 19 :
    if (currChar == '=') return 20;
    else return 21;
  case 22 :
    if (currChar == '=') return 23;
    else return 24;
  case 25 :
    if (currChar == '=') return 26;
    else if (currChar == '<') return 27;
    else return 28;
  case 27 :
    if (currChar == '=') return 29;
    else 30;
  case 31 :
    if (currChar == '=') return 32;
    else if (currChar == '>') return 33;
    else return 34;
  case 33 :
    if (currChar == '=') return 35;
    else 36;
  case 37 :
    if (currChar == '=') return 38;
    else if (currChar == '&') return 39;
    else return 40;
  case 41 :
    if (currChar == '=') return 42;
    else return 43;
  case 44 :
    if (currChar == '=') return 45;
    else if (currChar == '|') return 46;
    else return 47;
  case 48 :
    if (currChar == '=') return 49;
    else return 50;
  case 58 :
    if (isdigit(currChar)) return 59;
    else return -1;
  case 59 :
    if (isdigit(currChar)) return 59;
    else return 63;
  }
  return -1;
}

bool accepting(int state)
{
  if (state == -1 || state == 2 || state == 4 || state == 6 || state == 7 || state == 8 || state == 10 || state == 11 || state == 12 || state == 14 || state == 15 || state == 17 || state == 18
        || state == 20 || state == 21 || state == 23 || state == 24 || state == 26 || state == 28 || state == 29 || state == 30 || state == 32 || state == 34 || state == 35 || state == 36
        || state == 38 || state == 39 || state == 40 || state == 42 || state == 43 || state == 45 || state == 46 || state == 47 || state == 49 || state == 50 || state == 51 || state == 52
      || state == 53 || state == 54 || state == 55 || state == 56 || state == 57 || state == 62 || state == 63)
    return true;
  else
    return false;
}

token_type setToken(int state, string value)
{
  if (value == "int") return INTTYPE;
  if (value == "double") return DBLTYPE;
  switch(state) {
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

string getToken(token_type token)
{
  switch (token) {
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

bool foundNewLexeme(int state)
{
  if (state == 2 || state == 4 || state == 8 || state == 12 || state == 15 || state == 18 || state == 21 || state == 24 || state == 28 || state == 30 || state == 34 || state == 36
      || state == 40 || state == 43 || state == 47 || state == 50 || state == 62 || state == 63)
    return true;
  else
    return false;
}
