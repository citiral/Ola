#include "lexer.h"
#include <ctype.h>
#include <stdlib.h>

namespace ola {

    Lexer::Lexer()
        : _buffer(0),
        _bufferIndex(0)
    {
    }

    Lexer::~Lexer()
    {

    }

    void Lexer::loadBuffer(const char* buffer)
    {
        _buffer = buffer;
        _bufferIndex = 0;
    }

    void Lexer::nextChar() {
        if (_buffer[_bufferIndex] != '\0')
            _bufferIndex++;
    }

    char Lexer::curChar() {
        return _buffer[_bufferIndex];
    }

    char Lexer::eatChar() {
        char c = curChar();
        nextChar();
        return c;
    }

    void Lexer::skipWhitespace() {
        while (isspace(curChar()))
            nextChar();
    }

    Token Lexer::nextToken()
    {
        //and then parse and return the next token
        return parseNext();
    }

    Token Lexer::parseNext() {
        //skip whitespace of the current character
        skipWhitespace();

        //if we are at the end, return end of buffer
        if (curChar() == '\0')
            return Token::Eob;

        Token ret;

        //first check if it is a keyword and return it
        ret = parseKeyword();
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
            else if (isspace(curChar()) || curChar() == '\0')
                return Token::Identifier;
            else {
                //reset the bufferindex
                _bufferIndex -= value.string.length();
                return Token::None;
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
            } else if (isspace(curChar()) || curChar() == '\0'){
                return Token::Numeric;
            } else {
                //reset the bufferindex
                _bufferIndex -= value.string.length();
                return Token::None;
            }
        } while (true);
    }

    Token Lexer::parseKeyword()
    {
        if (tryCompareAndSkipNext("function"))
            return Token::Function;
        return Token::None;
    }

    bool Lexer::tryCompareAndSkipNext(const char* word)
    {
        int wordindex = 0;

        while(_buffer[_bufferIndex + wordindex] == word[wordindex]) {
            //if we are at the end of the word
            if (word[wordindex] == '\0') {
                //if the buffer's current character is not alfanumeric
                if (!isalnum(_buffer[_bufferIndex+wordindex])) {
                    //success! advance bufferindex and return true
                    _bufferIndex += wordindex;
                    return true;
                } else {
                    return false;
                }
            }

            //if the word is not at the end, but the buffer is, return false
            if (_buffer[_bufferIndex + wordindex] == '\0') {
                return false;
            }

            wordindex++;
        }

        //if we are at the end of the word
        if (word[wordindex] == '\0') {
            //if the buffer's current character is not alfanumeric
            if (!isalnum(_buffer[_bufferIndex+wordindex])) {
                //success! advance bufferindex and return true
                _bufferIndex += wordindex;
                return true;
            }
        }
        return false;
    }

}