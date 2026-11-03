#include <string>
#include <iostream>
#include <vector>
#include <fstream>

using namespace std;

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


    // grammar 
    enum class GrammarType {
        Default,
        program,
        stmtlist,
        stmt,
        expr,
        termtail,
        term,
        facttail,
        factor,
        addop,
        multop,
    };
    struct Grammar {
        GrammarType type = GrammarType::Default;
        Token token;
        vector<Grammar> children;
    };
    


vector<Token> tokenVector = {};


int main(){

// sample tokens
Token token0;
    token0.type = TokenType::Identifier;
    token0.specificType = "sum";
    tokenVector.push_back(token0);
Token token1;
    token1.type = TokenType::Operator;
    token1.specificType = "ASSIGN";
    tokenVector.push_back(token1);
Token token2;
    token2.type = TokenType::Punctuation;
    token2.specificType = "LPAREN";
    tokenVector.push_back(token2);
Token token3;
    token3.type = TokenType::Number;
    token3.specificType = "2";
    tokenVector.push_back(token3);
Token token4;
    token4.type = TokenType::Operator;
    token4.specificType = "ADD";
    tokenVector.push_back(token4);
Token token5;
    token5.type = TokenType::Number;
    token5.specificType = "3";
    tokenVector.push_back(token5);
Token token6;
    token6.type = TokenType::Punctuation;
    token6.specificType = "RPAREN";
    tokenVector.push_back(token6);



Grammar program; // create program
program.type = GrammarType::program;
cout << "Executing:\tprogram() ";

Grammar newStmtlist; // create new stmt_list
newStmtlist.type = GrammarType::stmtlist;
program.children.push_back(newStmtlist); // put it in program
cout << "stmt_list() ";

Grammar newStmt; // create new stmt
newStmt.type = GrammarType::stmt;
program.children[0].children.push_back(newStmt); // put it in stmt_list

for (int i = 0; i < tokenVector.size(); i++){

    switch (tokenVector[i].type){

        case (TokenType::Keyword):
            if (tokenVector[i].specificType == "read"){ // read keyword
                cout << "\tToken:\tread consumed" << endl;
                if ( (i > tokenVector.size() - 1) && (tokenVector[i+1].type == TokenType::Identifier) ){ // next token is an id
                    cout << "\tToken:\t" << tokenVector[i+1].specificType << " consumed" << endl;
                    // end stmt

                    break;
                }
            }
            else if (tokenVector[i].specificType == "write"){ // write keyword
                if (i > tokenVector.size() - 1){ // next token is an expression
                    // expression

                    break;
                }
            }

            cout << "ERROR" << endl;

            break;

        case (TokenType::Identifier):
            if ( (i > tokenVector.size() - 1) && ( (tokenVector[i+1].type == TokenType::Operator) && (tokenVector[i+1].specificType == "ASSIGN") ) ){
                // expression

                break;
            }

            cout << "ERROR" << endl;

            break;

        case (TokenType::End):
            // end ($$)    

            break;

        default:
            cout << "ERROR" << endl;

    }

}



}