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
Token token0;
Token token1;
Token token2;
Token token3;

vector<Token> tokenVector = {token0, token1, token2, token3};
int n = 0;//tokenVector index
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
            return (isExpr());
        }
        else if (tokenVector[n].specificType == "READ")
        {
            n++;
            if (tokenVector[n].type == TokenType::Identifier)
            {
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

int main(){
//Add input file
ifstream infile("input.txt"); // input file
//reading from input


}