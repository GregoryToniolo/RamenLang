#pragma once
#include <vector>
#include <string>

enum class tokenType
{
    //built in types
    INT, UINT, SHORT, USHORT, LONG, ULONG, FLOAT32, FLOAT64, CHAR, BOOL, VOID, NULLPTR, SIZE_T, AUTO,
    /*
    * add new types here
    */ 
    //other keywords
    NEW, DELETE, PRIVATE, PUBLIC, PROTECTED, VIRTUAL, STATIC, EXTERN, INLINE, VOLATILE, FRIEND, CONST, CONSTEXPR, CONSTINIT, CONSTEVAL, DYNAMIC_CAST, STATIC_CAST, REINTERPRET_CAST, CONST_CAST,
    //user defined types
    CLASS, UNION, STRUCT, ENUM, ENUM_CLASS, TEMPLATE, TYPEDEF, TYPENAME, NAMESPACE, USING,
    //macros
    MACRO_INCLUDE, MACRO_DEFINE, MACRO_UNDEFINE, MACRO_IF_NOT_DEF, MACRO_IF_DEF, MACRO_IF, MACRO_ENDIF, MACRO_PRAGMA,
    //libraries
    IOSTREAM, STDALGORITHM, FSTREAM, STDVECTOR, STDSTRING, STDEXCEPTION, STDMEMORY, STDARRAY,
    //loops and logic
    SWITCH, IF, ELSE, ELSE_IF, CASE, DEFAULT, CONTINUE, BREAK, WHILE, FOR, RETURN, TRUE, FALSE,
    //delimiters
    LEFT_CURLY_BRACKET, RIGHT_CURLY_BRACKET, LEFT_SQUARE_BRACKET, RIGHT_SQUARE_BRACKET, LEFT_PARENTHESIS, RIGHT_PARENTHESIS, RIGHT_ANGLED_BRACKET, LEFT_ANGLED_BRACKET, SEMICOLON, COLON, DOUBLE_COLON, PERIOD, COMMA, APOSTROPHE, QUOTAION_MARK,
    EXCLAMATION_MARK, BACK_SLASH, HASHTAG, QUESTION_MARK, POINTER_ELEMENT, COMMENT_START, COMMENT_END,
    //operators
    BITSHIFT_LEFT, BITSHIFT_RIGHT, BITWISE_AND, BITWISE_OR, BITWISE_XOR, BITWISE_NOT, PLUS, MINUS, FORWARD_SLASH, ASTERISK, PERCENT_SIGN, LOGICAL_AND, LOGICAL_OR, LOGICAL_NOT, EQUAL_SIGN, LOGICAL_EQUALS, LARGER_OR_EQUAL, SMALLER_OR_EQUAL, 
    //other token types
    GENERIC, LINE_COMMENT, NULL_TOKEN
};

struct Token
{
    tokenType type;
    std::string tokenString;
};


bool isSpace(const char& character)
{
    switch (character) 
    {
        case ' ':
        case '\n':
        case '\t':
        case '\r':
        return true;
        break;

        default:
        return false;
        break;
    }
}

bool isEmpty(const std::string& inputString)
{
    return inputString == "";
}

bool isDelimiter(const char& character)
{
    switch(character)
    {
        case '<':
        case '>':
        case '&':
        case '*':
        case '+':
        case '-':
        case '%':
        case '/':
        case '\\':
        case '{':
        case '}':
        case '[':
        case ']':
        case '(':
        case ':':
        case ';':
        case '.':
        case ',':
        case '\'':
        case '\"':
        case '?':
        case '!':
        case '=':
        case '~':
        case '#':
        case '|':
        case '^':
        return true;
        break;

        default:
        return false;
        break;
    }
}

bool isValidOperator(const char& first, const char& second)
{
    switch (first)
    {
        case '+':
        case '&':
        case '|':
        case '=':
        case '<':
        case '>':
        return second == first || second == '=';
        break;

        case '-':
        return second == first || second == '=' || second == '>';
        break;

        case ':':
        return second == first;
        break;

        case '.':
        return second == '*';
        break;

        case '%':
        case '!':
        case '~':
        case '^':
        return second == '=';
        break;

        case '/':
        return second == first || second == '=' || second == '*';
        break;

        case '*':
        return second == '/' || second == '=';
        break;
    }

    return false;
}

//splits a string into substrings
std::vector<std::string> tokenize(const std::string& inputString)
{
    if (empty(inputString))
    {
        return {"VoidString"};
    }
    std::vector<std::string> tokenString;
    std::string delimiter;

    int currentToken = 0;

    bool isString = false;

    for (int i = 0; i < inputString.size(); i++)
    {
        if (inputString[i] == '\"' && isString)
        {
            tokenString.push_back(inputString.substr(currentToken, i - (currentToken - 1)));
            currentToken = i + 1;
            isString = false;
            continue;
        }
        else if (isString)
        {
            continue;
        }

        //<<= and >>= special cases
        if (i < inputString.size() - 2 && inputString[i] == '<' && inputString[i+1] == '<' && inputString[i+2] == '=')
        {
            currentToken = i;
            i+= 2;
            tokenString.push_back(inputString.substr(currentToken, i - (currentToken - 1)));
            currentToken = i + 1;
            continue;
        }
        else if (i < inputString.size() - 2 && inputString[i] == '>' && inputString[i+1] == '>' && inputString[i+2] == '=')
        {
            currentToken = i;
            i+= 2;
            tokenString.push_back(inputString.substr(currentToken, i - (currentToken - 1)));
            currentToken = i + 1;
            continue;
        }

        if (isSpace(inputString[i]))
        {
            tokenString.push_back(inputString.substr(currentToken, i - currentToken));
            currentToken = i + 1;
            continue;
        }

        //substring is a single token
        if (i > 0 && inputString[i] == '\"' && inputString[i-1] != '\\' && isString == false)
        {
            currentToken = i;
            isString = true;
            continue;
        }
        //char is a single token
        else if (i > 0  && i < inputString.size() - 3 && inputString[i] == '\'' && inputString[i-1] != '\\' && inputString[i+1] == '\\')
        {
            currentToken = i;
            i+= 3;
            tokenString.push_back(inputString.substr(currentToken, i - (currentToken - 1)));
            currentToken = i + 1;
        }
        else if (i > 0 && i < inputString.size() - 2 && inputString[i] == '\'' && inputString[i-1] != '\\')
        {
            currentToken = i;
            i+= 2;
            tokenString.push_back(inputString.substr(currentToken, i - (currentToken - 1)));
            currentToken = i + 1;
        }
        //checks if string contains an operator that uses 2 chars ex. a *= b
        else if (i < inputString.size() - 1 && isDelimiter(inputString[i]) && isDelimiter(inputString[i + 1]) && isValidOperator(inputString[i], inputString[i+1]))
        {
            tokenString.push_back(inputString.substr(currentToken, i - currentToken));
            currentToken = i + 1;
            delimiter.push_back(inputString[i]);
            delimiter.push_back(inputString[i+1]);
            tokenString.push_back(delimiter);
            currentToken = i + 2;
            delimiter = "";
            i++;
        }
        else if (isDelimiter(inputString[i]))
        {
            tokenString.push_back(inputString.substr(currentToken, i - currentToken));
            currentToken = i + 1;
            delimiter.assign(1, inputString[i]);
            tokenString.push_back(delimiter);
            delimiter = "";
        }

    }

    if (!isSpace(inputString[inputString.size() - 1]) && !isDelimiter(inputString[inputString.size() - 1]))
    {
        tokenString.push_back(inputString.substr(currentToken, inputString.size() - currentToken));
    }

    //weird ass lambda function that removes all elements with string length 0 from the vector
    std::erase_if(tokenString, [](std::string string){return string.size() == 0;});

    return tokenString;
}
