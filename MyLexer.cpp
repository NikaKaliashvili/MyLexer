
#define RESET   "\033[0m"
#define RED     "\033[31m"
#define GREEN   "\033[32m"
#define YELLOW  "\033[33m"
#define BLUE    "\033[34m"
#define MAGENTA "\033[35m"
#define CYAN    "\033[36m"

#include <iostream>
#include <string>
#include <vector>



// example: int age = 18;

enum TokenType
{
    Identifier, // int "age" = 18;
    Number, // int age = "18" ;

    Plus,
    Minus,
    Equals,
    Semicolon, // int age = 18 ";"

    Unknown,
    EndOfFile,
};


struct Token
{
    TokenType type;
    std::string text;


};


std::ostream& operator<<(std::ostream& os, Token token) {
    
    std::cout << "--------------------------------------" << std::endl;

    switch (token.type) {
    
    case Identifier: {
        os << RED << "Type: " << GREEN << "Identifier" << RESET << std::endl;
        break;
    }
    
    case Number: {
        os << RED << "Type: " << CYAN << "Number" << RESET << std::endl;

        break;
    }

    case Plus: {
        os << RED << "Type: " << YELLOW << "Plus" << RESET << std::endl;

        break;
    }

    case Minus: {
        os << RED << "Type: " << YELLOW << "Minus" << RESET << std::endl;

        break;
    }

    case Equals: {
        os << RED << "Type: " << MAGENTA << "Equals" << RESET << std::endl;

        break;
    }

    case Semicolon: {
        os << RED << "Type: " << RED << "Semicolon" << RESET << std::endl;

        break;
    }

    }

    os << "Text: " << token.text << std::endl;

    std::cout << "--------------------------------------" << std::endl;
    std::cout << std::endl;



    return os;
}

class Lexer
{
public:
    Lexer(const std::string& source) : source(source) {}


    bool IsIdentifierStart(char c) // gets if char is letter or _
    {
        return std::isalpha(c) || c == '_';
    }

    bool IsNum(char c) { // gets if char is number
        return std::isdigit(c);
    }

    bool IsIdentifierPart(char c)
    {
        return std::isalnum(c) || c == '_'; // gets if char is letter/number or _
    }

    Token ReadNum() {
        size_t start = position;

        while (position < source.length())
        {
            char current = source[position];

            if (IsNum(current))
            {
                position++;
            }
            else
            {
                break;
            }
        }

        return {
            TokenType::Number,
            source.substr(start, position - start)
        };
    }

    Token ReadIdentifier()
    {
        size_t start = position;

        while (position < source.length())
        {
            char current = source[position];

            if (IsIdentifierPart(current))
            {
                position++;
            }
            else
            {
                break;
            }
        }

        return {
            TokenType::Identifier,
            source.substr(start, position - start)
        };
    }

    std::vector<Token> Tokenize() {

        std::vector<Token> tokens;

        while (position < source.length()) {
            char current = source[position];

            if (IsIdentifierStart(current)) {
                Token identifier = ReadIdentifier();
                tokens.push_back(identifier);
                continue;
            }

            if (std::isspace(current)) {
                position++;
                continue;
            }

            if (IsNum(current)) {
                Token identifier = ReadNum();
                tokens.push_back(identifier);
                continue;
            }

            if (current == '=') {
                Token identifier = {
                    TokenType::Equals,
                    "="
                };

                position++;
                tokens.push_back(identifier);
                continue;
            }

            if (current == '+') {
                Token identifier = {
                    TokenType::Plus,
                    "+"
                };

                position++;
                tokens.push_back(identifier);
                continue;
            }

            if (current == '-') {
                Token identifier = {
                    TokenType::Minus,
                    "-"
                };

                position++;
                tokens.push_back(identifier);
                continue;
            }

            if (current == ';') {
                Token identifier = {
                    TokenType::Semicolon,
                    ";"
                };

                position++;
                tokens.push_back(identifier);
                continue;
            }

            position++;
        }

        return tokens;
    }

private:
    std::string source;
    size_t position = 0;
};

int main()
{
    std::string test = "int test = 15; test = test + 4;";
    Lexer lexer(test);

    std::vector<Token> tokens = lexer.Tokenize();


    for (Token token : tokens) {

        std::cout << token;

    }
}