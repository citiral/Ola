#include "lexer.h"
#include <ctype.h>
#include <stdlib.h>
#include <string>

namespace ola {

    Lexer::Lexer():
            _bufferIndex(0),
            _lineNumber(0),
            _charNumber(0)
    {
    }

    Lexer::~Lexer()
    {

    }

    void Lexer::setInput(std::string input)
    {
        _input = input;
        _bufferIndex = 0;
        _lineNumber = 0;
        _charNumber = 0;
    }

    void Lexer::setCallback(std::function<std::string()> inputCallback)
    {
        _inputCallback = std::move(inputCallback);
    }

    bool Lexer::atEndOfBuffer() {
        return _input.c_str()[_bufferIndex] == '\0';
    }

    void Lexer::nextChar() {
        if (_input.c_str()[_bufferIndex] == '\n') {
            _lineNumber++;
            _charNumber = 0;
        }

        if (_input.c_str()[_bufferIndex] != '\0') {
            _bufferIndex++;
            _charNumber++;
        } else {
            //if we are at the end of the buffer, get new input
            fetchInput();
            if (_input.c_str()[_bufferIndex] != '\0') {
                _bufferIndex++;
                _charNumber++;
            }
        }
    }

    char Lexer::curChar() {
        return _input.c_str()[_bufferIndex];
    }

    char Lexer::eatChar() {
        char c = curChar();
        nextChar();
        return c;
    }

    void Lexer::skipWhitespace() {
        while (isspace(curChar())) {
            nextChar();
        }
    }

    Token Lexer::nextToken()
    {
        //and then parse and return the next token
        _lastToken = parseNext();
        return _lastToken;
    }

    Token Lexer::curToken()
    {
        return _lastToken;
    }

    Token Lexer::parseNext() {
        //skip whitespace of the current character
        skipWhitespace();

        //return eof if we are at the end
        if (curChar() == '\0') {
            //because this statement might be ran on the first character of the buffer, peek for new information first
            fetchInput();
            if (curChar() == '\0')
                return Token::Eof;
        }

        Token ret;

        //first check if it is a keyword and return it
        ret = parseKeyword();
        if (ret != Token::None)
            return ret;
        ret = parseSymbol();
        if (ret != Token::None)
            return ret;
        ret = parseIdentifier();
        if (ret != Token::None)
            return ret;
        ret = parseNumeric();
        if (ret != Token::None)
            return ret;

        //if nothing was able to parse it, it must be a character and we return it
        value.character = eatChar();
        return Token::Character;
    }

    Token Lexer::parseIdentifier()
    {
        //identifiers can only start with alphabetic characters, or underscores
        if (!(isalpha(curChar()) || curChar() == '_'))
            return Token::None;

        value.string.clear();

        do {
            if (isalnum(curChar()) || curChar() == '_')
                value.string += eatChar();
            else {
                return Token::Identifier;
            }
        } while (true);
    }

    Token Lexer::parseNumeric()
    {
        bool dotFound = false;

        //first check if we are parsing a number
        if (!(isdigit(curChar()) || curChar() == '.')) {
            return Token::None;
        }

        value.string.clear();

        do {
            if (isdigit(curChar())) {
                value.string += eatChar();
            } else if (!dotFound && curChar() == '.') {
                dotFound = true;
                value.string += eatChar();
            } else {
                return Token::Numeric;
            }
        } while (true);
    }

    Token Lexer::parseKeyword()
    {
        if (tryCompareAndSkipNextKeyword("return"))
            return Token::Return;
        else if (tryCompareAndSkipNextKeyword("i32")) {
            value.string = "i32";
            return Token::Type;
        }
        else if (tryCompareAndSkipNextKeyword("i64")) {
            value.string = "i64";
            return Token::Type;
        }
        else if (tryCompareAndSkipNextKeyword("f32")) {
            value.string = "f32";
            return Token::Type;
        }
        else if (tryCompareAndSkipNextKeyword("f64")) {
            value.string = "f64";
            return Token::Type;
        } else if (tryCompareAndSkipNextKeyword("function")) {
            return Token::Function;
        }
        return Token::None;
    }

    Token Lexer::parseSymbol() {
        if (tryCompareAndSkipNextSymbol(";"))
            return Token::Char_semicolon;
        if (tryCompareAndSkipNextSymbol("->"))
            return Token::Char_arrow;
        if (tryCompareAndSkipNextSymbol("++"))
            return Token::Char_plusplus;
        if (tryCompareAndSkipNextSymbol("--"))
            return Token::Char_minmin;
        if (tryCompareAndSkipNextSymbol("+")) {
            value.character = '+';
            return Token::Operator;
        } if (tryCompareAndSkipNextSymbol("-")) {
            value.character = '-';
            return Token::Operator;
        } if (tryCompareAndSkipNextSymbol("*")) {
            value.character = '*';
            return Token::Operator;
        } if (tryCompareAndSkipNextSymbol("/")) {
            value.character = '/';
            return Token::Operator;
        } if (tryCompareAndSkipNextSymbol("."))
            return Token::Char_dot;
        if (tryCompareAndSkipNextSymbol(","))
            return Token::Char_comma;
        if (tryCompareAndSkipNextSymbol("("))
            return Token::Char_openRoundBracket;
        if (tryCompareAndSkipNextSymbol(")"))
            return Token::Char_closeRoundBracket;
        if (tryCompareAndSkipNextSymbol("{"))
            return Token::Char_openCurlyBracket;
        if (tryCompareAndSkipNextSymbol("}"))
            return Token::Char_closeCurlyBracket;
        return Token::None;
    }

    bool Lexer::tryCompareAndSkipNextKeyword(const char *word)
    {
        int wordindex = 0;

        while(_input.c_str()[_bufferIndex + wordindex] == word[wordindex]) {
            //if we are at the end of the word
            if (word[wordindex] == '\0') {
                //if the buffer's current character is not alfanumeric
                if (!isalnum(_input.c_str()[_bufferIndex+wordindex])) {
                    //success! advance bufferindex and return true
                    _bufferIndex += wordindex;
                    return true;
                } else {
                    return false;
                }
            }

            //if the word is not at the end, but the buffer is, return false
            if (_input.c_str()[_bufferIndex + wordindex] == '\0') {
                return false;
            }

            wordindex++;
        }

        //if we are at the end of the word
        if (word[wordindex] == '\0') {
            //if the buffer's current character is not alfanumeric
            if (!isalnum(_input.c_str()[_bufferIndex+wordindex])) {
                //success! advance bufferindex and return true
                _bufferIndex += wordindex;
                return true;
            }
        }
        return false;
    }

    bool Lexer::tryCompareAndSkipNextSymbol(const char *word)
    {
        int wordindex = 0;

        while(_input.c_str()[_bufferIndex + wordindex] == word[wordindex]) {
            //if we are at the end of the word
            if (word[wordindex] == '\0') {
                _bufferIndex += wordindex;
                return true;
            }

            //if the word is not at the end, but the buffer is, return false
            if (_input.c_str()[_bufferIndex + wordindex] == '\0') {
                return false;
            }

            wordindex++;
        }

        //if we are at the end of the word
        if (word[wordindex] == '\0') {
            _bufferIndex += wordindex;
            return true;
        }
        return false;
    }

    u32 Lexer::getLineNumber() const {
        return _lineNumber;
    }

    u32 Lexer::getCharNumber() const {
        return _charNumber;
    }

    void Lexer::fetchInput() {
        _input += _inputCallback();
    }
}