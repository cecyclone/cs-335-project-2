/*
CS 335 Programming Assignment 2
Chloe Cantrell, Miles Crane, Trevor Past

Generative AI was NOT used for this assignment.
*/


#include <string>
#include <iostream>
#include <vector>
#include <fstream>

using namespace std;


// Input stuff
ifstream infile("input.txt"); // input file
vector<string> infileVector = {};
int currentLine;
vector<char> input = {}; // vector to store line from file

void clearInputVector(){
    while (input.empty() == 0){
        input.pop_back();
    }
}

void inputFileToVector(){
    string line = "";
    while (getline (infile, line)) {
        infileVector.push_back(line);
    }
    //cout << "DEBUG:\tImported infile to infileVector!" << endl;
}

void nextLineAsVector(int lineNum){
    string line = infileVector[lineNum];
    const char* cline = line.c_str();

    clearInputVector();
    for (int i = 0; i < line.length(); i++){
        input.push_back(cline[i]);
    }
}



// Recursive descent logic
enum class TokenType
{
    Default,
    Keyword,//Token.specificType values: READ, WRITE
    Identifier,
    Number,
    Operator,//Token.specificType values: ADD, SUB, ASSIGN, DIV, MULT
    Punctuation,//Token.specificType: LPAREN, RPAREN, PERIOD
    Comment,
    End,// CREATE "$$" TOKEN
};
struct Token
{
    TokenType type = TokenType::Default;
    string specificType = "";
};
/*Token token0;
Token token1;
Token token2;
Token token3;

vector<Token> tokenVector = {token0, token1, token2, token3};*/
vector<Token> tokenVector = {};
int n = 0;//tokenVector index
//Parsing Declarations
bool isExpr();
bool isTerm();
bool isFactor();
bool isStatement();

bool isAddOp()
{
    if (tokenVector[n].specificType == "ADD" || tokenVector[n].specificType == "SUB")
    {
        n++;
        return true;
    }
    else
    {
        return false;
    }
}
bool isMultOp()
{
    if (tokenVector[n].specificType == "MULT" || tokenVector[n].specificType == "DIV")
    {
        n++;
        return true;
    }
    else
    {
        return false;
    }
}
bool isFactor()
{
if (tokenVector[n].type == TokenType::Identifier || tokenVector[n].type == TokenType::Number)
{
    n++;
    return true;
}
else if (tokenVector[n].specificType == "LPAREN")
{
    n++;
    if (!isExpr())
    {
        return false;
    }
    if (tokenVector[n].specificType != "RPAREN")
    {
        return false;
    }
    n++;
    return true;
}
return false;
}
bool isFactorTail()
{
    if (isMultOp())
    {
        if (!isFactor())
        {
            return false;
        }
        return (isFactorTail());
    }
    return true;
}
bool isTerm()
{
    if (isFactor())
    {
        return (isFactorTail());
    }
    return false;
}
bool isTermTail()
{
    if (isAddOp())
    {
        if (!isTerm())
        {
            return false;
        }
        return (isTermTail());
    }
    return true;
}
bool isExpr()
{
    if (isTerm())
    {
        return isTermTail();
    }
    return false;
}
bool isStatement()
{
    if (tokenVector[n].type == TokenType::Identifier)
    {
        n++;
        if (tokenVector[n].specificType == "ASSIGN")
        {
            n++;
            return (isExpr());
        }
    }
    else if (tokenVector[n].type == TokenType::Keyword)
    {
        if (tokenVector[n].specificType == "WRITE")
        {
            n++;
            return (isExpr());
        }
        else if (tokenVector[n].specificType == "READ")
        {
            n++;
            if (tokenVector[n].type == TokenType::Identifier)
            {
                n++;
                return true;
            }
            return false;
        }
        return false;
    }
    return false;
}
bool isStatementList()
{
    if (tokenVector[n].type == TokenType::End)
    {
        return true;
    }
    if (!isStatement())
    {
        return false;
    }
    return isStatementList();
}



int main() {

    // Input Stuff
    class LexAnalyzer
    {
        private:
            int position;

        public:
            LexAnalyzer(const vector<char>& inputVector)
            {
                position = 0;
            }
            void advance()
            {
                position++;
            }
            int getPosition()
            {
                return position;
            }
            void resetPosition()
            {
                position = 0;
            }

            char peek()
            {
                if (position + 1 < input.size())
                    return input[position + 1];

                return '\0';
            }

            char current()
            {
                if (position < input.size())
                    return input[position];

                return '\0';
            }

            void ignoreWhiteSpace()
            {
                while (inputRemaining() && current() == ' ')
                {
                    advance();
                }
            }
            bool isDigit(char input)
            {
                if (input == '0')
                    return true;
                else if (input == '1')
                    return true;
                else if (input == '2')
                    return true;
                else if (input == '3')
                    return true;
                else if (input == '4')
                    return true;
                else if (input == '5')
                    return true;
                else if (input == '6')
                    return true;
                else if (input == '7')
                    return true;
                else if (input == '8')
                    return true;
                else if (input == '9')
                    return true;
                else
                    return false;
            }
            bool isLetter(char input)
            {
                return (input >= 'a' && input <= 'z') ||
                    (input >= 'A' && input <= 'Z');
            }
            bool isKeyword(string input)
            {
                return (input == "read" || input == "write");
            }

            bool inputRemaining()
            {
                return position < input.size();
            }
    };

    // Load input file and store each line as a token in "tokens" vector. Logic mostly reused from Project 1
    cout << "LOADING TOKENS FROM INPUT FILE..." << endl << endl;
    inputFileToVector();
    currentLine = 0;
    while (currentLine < infileVector.size()){
        nextLineAsVector(currentLine);
        //cout << endl << "STARTING AT NEW LINE: " << currentLine << endl;
            
        string number = "";
        string word = "";
        
        LexAnalyzer lexer(input);
        Token tkn;

        //Loop processes 1 line from input file
        char currentChar = lexer.current();
        switch (currentChar)
        {
        case ('+'):
            tkn.type = TokenType::Operator;
            tkn.specificType = "ADD";
            cout << "add token stored!" << endl;
            tokenVector.push_back(tkn); // push token onto vector
            lexer.advance();
            break;
        case ('-'):
            tkn.type = TokenType::Operator;
            tkn.specificType = "SUB";
            cout << "sub token stored!" << endl;
            tokenVector.push_back(tkn); // push token onto vector
            lexer.advance();
            break;

        case ('*'):
            tkn.type = TokenType::Operator;
            tkn.specificType = "MULT";
            cout << "mult token stored!" << endl;
            tokenVector.push_back(tkn); // push token onto vector
            lexer.advance();;
            break;
        case ('/'):
            tkn.type = TokenType::Operator;
            tkn.specificType = "DIV";
            cout << "div token stored!" << endl;
            tokenVector.push_back(tkn); // push token onto vector
            lexer.advance();
            break;

        case (':'):
            if (lexer.peek() == '=')
            {
                tkn.type = TokenType::Operator;
                tkn.specificType = "ASSIGN";
                cout << "assign token stored!" << endl;
                tokenVector.push_back(tkn); // push token onto vector
                lexer.advance();
                lexer.advance();
            }
            else
            {
                cout << "unhandled case" << endl;
                lexer.advance();
            }
            break;
        case ('('):
            tkn.type = TokenType::Punctuation;
            tkn.specificType = "LPAREN";
            cout << "lparen token stored!" << endl;
            tokenVector.push_back(tkn); // push token onto vector
            lexer.advance();
            break;
        case (')'):
            tkn.type = TokenType::Punctuation;
            tkn.specificType = "RPAREN";
            cout << "rparen token stored!" << endl;
            tokenVector.push_back(tkn); // push token onto vector
            lexer.advance();
            break;
        case ('.'):
            if (lexer.isDigit(lexer.peek()))
            {
                number = ".";

                lexer.advance();

                while (lexer.isDigit(lexer.current()))
                {
                    number += lexer.current();
                    lexer.advance();
                }

                tkn.type = TokenType::Number;
                cout << number << " stored as token!" << endl;
                tokenVector.push_back(tkn); // push token onto vector
                number = "";
                cout << " number cleared!";
            }
            else
            {
                tkn.type = TokenType::Punctuation;
                tkn.specificType = "PERIOD";
                cout << "period stored!" << endl;
                tokenVector.push_back(tkn); // push token onto vector
                lexer.advance();
            }
            break;
        case ('$'):
            if (lexer.peek() == '$')
            {
                tkn.type = TokenType::End;
                tokenVector.push_back(tkn); // push token onto vector
                lexer.advance();
                lexer.advance();
            }
            else
            {
                cout << "Error, $ is not a valid input";
            }
            break;
        case (' '):
            lexer.ignoreWhiteSpace();
            break;
        default:
            if (lexer.isDigit(currentChar))
            {
                bool hasDecimal = false;
                while (lexer.isDigit(lexer.current()) ||
                    (lexer.current() == '.' && !hasDecimal))
                {
                    if (lexer.current() == '.')
                    {
                        hasDecimal = true;
                    }
                    number += lexer.current();
                    lexer.advance();
                }
                tkn.type = TokenType::Number;
                cout << number << " stored as token!\t";
                tokenVector.push_back(tkn); // push token onto vector
                number = "";
                cout << "number cleared!" << endl;
            }
            else if (lexer.isLetter(currentChar))
            {
                while (lexer.isLetter(lexer.current()) || lexer.isDigit(lexer.current()))
                {
                    word += lexer.current();
                    lexer.advance();
                }
                if (lexer.isKeyword(word))
                {
                    tkn.type = TokenType::Keyword;
                    if (word == "read")
                    {
                        tkn.specificType = "READ";
                        cout << "keyword read stored\t";
                        tokenVector.push_back(tkn); // push token onto vector

                    }
                    else if (word == "write")
                    {
                        tkn.specificType = "WRITE";
                        cout << "keyword write stored\t";
                        tokenVector.push_back(tkn); // push token onto vector
                    }
                    else
                    {
                        cout << "how did we get here\t";
                    }
                }
                else
                {
                    tkn.type = TokenType::Identifier;
                    tkn.specificType = word;
                    cout << "identifier \"" << word << "\" stored!\t";
                    tokenVector.push_back(tkn); // push token onto vector
                }
                word = "";
                cout << " word cleared!" << endl;
            }
        }
        currentLine++;
    }
    cout << endl << "LOADING TOKENS COMPLETE!" << endl << endl;

    

    // "Write main, which entails using the recursive descent logic PLUS conditionals that will determine the output"

    

    // Creating the actual Output file



    return 0;
}
