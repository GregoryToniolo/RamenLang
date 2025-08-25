#pragma once
#include <vector>
#include <string>
#include <fstream>
#include <iostream>
#include "tokenizer.hpp"

//cpp syntax that has been implemented
const std::vector<std::string> cppKeywords = { 
    //built in types
    "int", "unsigned int", "short", "unsigned short", "long", "unsigned long", "float", "double", "char", "bool", "void", "nullptr", "size_t", "auto",
    /*
    * add new types here
    */
    //other keywords
    "new", "delete", "private", "public", "protected", "virtual", "static", "extern", "inline", "volatile", "friend", "const", "constexpr", "constinit", "consteval", "dynamic_cast", "static_cast", "reinterpret_cast", "const_cast",
    //user defined types
    "class", "union", "struct", "enum", "enum class", "template", "typedef", "typename", "namespace", "using",
    //macros
    "#include", "#define", "#undef", "#ifndef", "#ifdef", "#if", "#endif", "#pragma",
    //libraries
    "<iostream>", "<algorithm>", "<fstream>", "<vector>", "<string>", "<exception>", "<memory>", "<array>", 
    //loops and logic
    "switch", "if", "else", "else if", "case", "default", "continue", "break", "while", "for", "return", "true", "false",
};
//ramen syntax (add modifications here and in tokenizer.hpp/tokenType)
const std::vector<std::string> ramenKeywords = {
    //built in types
    "i32", "u32", "i16", "u16", "i64", "u64", "f32", "f64", "char", "bool", "void", "nullptr", "size", "let", 
    /*
    * add new types here
    */
    //other keywords
    "alloc", "dealloc", "priv", "pub", "protect", "virt", "static", "extern", "inline", "volatile", "companion", "immut", "compexpr", "compinit", "compeval", "cast_d", "cast_s", "cast_r", "cast_c",
    //user defined types
    "class", "union", "struct", "enumeration", "algebraic", "template", "type", "name", "namespace", "using",
    //macros
    "use", "define", "undefine", "ifnotdef", "ifdef", "if_P", "endif", "pragma",
    //libraries
    "stdio", "stdalg", "stdfile", "stdvector", "stdexcept", "stdmem", "stdarray", "stdstring",
    //loops and logic
    "match", "if", "else", "elif", "case", "default", "continue", "end", "while", "for", "return", "true", "false",
};

tokenType type(const Token& token)
{
    for (int i = 0; i < ramenKeywords.size(); i++)
    {
        if (token.tokenString == ramenKeywords[i])
        {
            return static_cast<tokenType>(i);
        }
    }

    if(token.tokenString == "VoidString") return tokenType::NULL_TOKEN;
    if(token.tokenString == "//") return tokenType::LINE_COMMENT;
    if(token.tokenString == "{") return tokenType::LEFT_CURLY_BRACKET;
    if(token.tokenString == "}") return tokenType::RIGHT_CURLY_BRACKET;
    if(token.tokenString == "[") return tokenType::LEFT_SQUARE_BRACKET;
    if(token.tokenString == "]") return tokenType::RIGHT_SQUARE_BRACKET;
    if(token.tokenString == "<") return tokenType::LEFT_ANGLED_BRACKET;
    if(token.tokenString == ">") return tokenType::RIGHT_ANGLED_BRACKET;
    if(token.tokenString == "(") return tokenType::LEFT_PARENTHESIS;
    if(token.tokenString == ")") return tokenType::RIGHT_PARENTHESIS;
    if(token.tokenString == ";") return tokenType::SEMICOLON;
    if(token.tokenString == ":") return tokenType::COLON;
    if(token.tokenString == "::") return tokenType::DOUBLE_COLON;
    if(token.tokenString == ".") return tokenType::PERIOD;
    if(token.tokenString == ",") return tokenType::COMMA;
    if(token.tokenString == "\'") return tokenType::APOSTROPHE;
    if(token.tokenString == "\"") return tokenType::QUOTAION_MARK;
    if(token.tokenString == "!") return tokenType::EXCLAMATION_MARK;
    if(token.tokenString == "?") return tokenType::QUESTION_MARK;
    if(token.tokenString == "\\") return tokenType::BACK_SLASH;
    if(token.tokenString == "#") return tokenType::HASHTAG;
    if(token.tokenString == "<<") return tokenType::BITSHIFT_LEFT;
    if(token.tokenString == ">>") return tokenType::BITSHIFT_RIGHT;
    if(token.tokenString == "&") return tokenType::BITWISE_AND;
    if(token.tokenString == "|") return tokenType::BITWISE_OR;
    if(token.tokenString == "^") return tokenType::BITWISE_XOR;
    if(token.tokenString == "~") return tokenType::BITWISE_NOT;
    if(token.tokenString == "+") return tokenType::PLUS;
    if(token.tokenString == "-") return tokenType::MINUS;
    if(token.tokenString == "/") return tokenType::FORWARD_SLASH;
    if(token.tokenString == "*") return tokenType::ASTERISK;
    if(token.tokenString == "%") return tokenType::PERCENT_SIGN;
    if(token.tokenString == "&&") return tokenType::LOGICAL_AND;
    if(token.tokenString == "||") return tokenType::LOGICAL_OR;
    if(token.tokenString == "!=") return tokenType::LOGICAL_NOT;
    if(token.tokenString == "=") return tokenType::EQUAL_SIGN;
    if(token.tokenString == "==") return tokenType::LOGICAL_EQUALS;
    if(token.tokenString == ">=") return tokenType::LARGER_OR_EQUAL;
    if(token.tokenString == "<=") return tokenType::SMALLER_OR_EQUAL;
    if(token.tokenString == "->") return tokenType::POINTER_ELEMENT;
    if(token.tokenString == "/*") return tokenType::COMMENT_START;
    if(token.tokenString == "*/") return tokenType::COMMENT_END;

    return tokenType::GENERIC;
}

std::vector<Token> parse(const std::string& inputString)
{
    std::vector<std::string> substrings = tokenize(inputString);
    std::vector<Token> tokens(substrings.size());

    for (int i = 0; i < substrings.size(); i++)
    {
        tokens[i].tokenString = substrings[i];
        tokens[i].type = type(tokens[i]);
    }

    return tokens;
}

bool spaceToken(const Token& token)
{
    switch (token.type)
    {
        case tokenType::BITSHIFT_LEFT:
        case tokenType::BITSHIFT_RIGHT:
        case tokenType::BITWISE_OR:
        case tokenType::BITWISE_XOR:
        case tokenType::BITWISE_NOT:
        case tokenType::PLUS:
        case tokenType::MINUS:
        case tokenType::FORWARD_SLASH:
        case tokenType::PERCENT_SIGN:
        case tokenType::LOGICAL_OR:
        case tokenType::LOGICAL_EQUALS:
        case tokenType::LOGICAL_NOT:
        case tokenType::EQUAL_SIGN:
        case tokenType::LARGER_OR_EQUAL:
        case tokenType::SMALLER_OR_EQUAL:
        case tokenType::COMMA:
        case tokenType::COLON:
        case tokenType::QUESTION_MARK:
        case tokenType::RIGHT_CURLY_BRACKET:
        case tokenType::RIGHT_PARENTHESIS:
        case tokenType::RIGHT_SQUARE_BRACKET:
        return true;
        break;

        default:
        return false;
        break;

    }
}

bool fieldSpecifierToken(const Token& token)
{
    switch (token.type)
    {
        case tokenType::DOUBLE_COLON:
        case tokenType::POINTER_ELEMENT:
        return true;
        break;

        default:
        return false;
        break;
    }
}

bool isBitshift(const Token& token)
{
    switch (token.type)
    {
        case tokenType::BITSHIFT_RIGHT:
        case tokenType::BITSHIFT_LEFT:
        return true;
        break;

        default:
        return false;
        break;
    }
}

bool isBuiltin(const Token& token)
{
    return static_cast<int>(token.type) < static_cast<int>(tokenType::NEW);
}

bool isSpecialCase(const Token& token)
{
    switch (token.type)
    {
        case tokenType::RIGHT_ANGLED_BRACKET:
        case tokenType::COMMA:
        return true;
        break;

        default:
        return false;
        break;
    }
}

void printTokens(std::vector<Token>& tokens, std::ofstream& file)
{
    if (tokens[0].type == tokenType::NULL_TOKEN)
    {
        file << '\n';
        return;
    }

    static int indentation = 0;

    if (tokens[0].type == tokenType::RIGHT_CURLY_BRACKET || tokens[tokens.size() - 1].type == tokenType::RIGHT_CURLY_BRACKET)
    {
        indentation--;
    }

    bool newLine = tokens[0].type != tokenType::LINE_COMMENT;

    if (newLine)
    {
        for (int j = 0; j < indentation; j++)
        {
            file << '\t';
        }
    }

    if (tokens[0].type == tokenType::LEFT_CURLY_BRACKET || tokens[tokens.size() - 1].type == tokenType::LEFT_CURLY_BRACKET)
    {
        indentation++;
    }

    static bool isComment = false;

    for (int i = 0; i < tokens.size(); i++)
    {

        if (tokens[i].type == tokenType::COMMENT_END)
        {
            isComment = false;
            newLine = true;
            continue;
        }
        else if (tokens[i].type == tokenType::COMMENT_START && i == 0)
        {
            isComment = true;
            newLine = false;
            continue;
        }
        else if (tokens[i].type == tokenType::COMMENT_START)
        {
            isComment = true;
            continue;
        }
        else if (tokens[i].type == tokenType::LINE_COMMENT && i == 0)
        {
            newLine = false;
            break;
        }
        else if (tokens[i].type == tokenType::LINE_COMMENT)
        {
            break;
        }

        if (isComment)
        {
            continue;
        }

        if (static_cast<int>(tokens[i].type) <= static_cast<int>(tokenType::FALSE))
        {
            file << cppKeywords[static_cast<int>(tokens[i].type)] << ' ';
        }
        else if (i < tokens.size() - 1 && tokens[i].type == tokenType::GENERIC && tokens[i+1].type == tokenType::COMMA)
        {
            file << tokens[i].tokenString;
        }
        else if (i < tokens.size() - 1 && fieldSpecifierToken(tokens[i+1]) && tokens[i].type == tokenType::GENERIC)
        {
            file << tokens[i].tokenString;
        }
        else if (i < tokens.size() - 1 && (tokens[i].type == tokenType::GENERIC || spaceToken(tokens[i])))
        {
            file << tokens[i].tokenString << ' ';
        }
        //> and <special cases
        else if (i > 0 && i < tokens.size() - 1 && tokens[i].type == tokenType::LEFT_ANGLED_BRACKET && tokens[i-1].type == tokenType::GENERIC && tokens[i+1].type == tokenType::GENERIC)
        {
            file << tokens[i].tokenString << ' ';
        }
        else if (i < tokens.size() - 1 && tokens[i].type == tokenType::RIGHT_ANGLED_BRACKET && tokens[i+1].type == tokenType::GENERIC)
        {
            file << tokens[i].tokenString << ' ';
        }
        else
        {
            file << tokens[i].tokenString;
        }
    }

    if (newLine)
    {
        file << '\n';
    }
}
