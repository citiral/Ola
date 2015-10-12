#pragma once
#include <string>
#include <iostream>
#include "types.h"

enum class Token {
	Character = 1,
	Numeric = 2,
	String = 3,
	Unknown = 4,
	Identifier = 5,
	Return = 6,
	Type = 7,
	Function = 8,
	Operator = 9,
	Char_plusplus = 102,
	Char_minmin = 103,
	Char_arrow = 106,
	Char_dot = 107,
	Char_comma = 108,
	Char_openRoundBracket = 109,
	Char_closeRoundBracket = 110,
	Char_openCurlyBracket = 111,
	Char_closeCurlyBracket = 112,
	Char_semicolon = 113,

	Eob = 254,
	Eof = 255,
	None = 0,
};

namespace ola {


	/////////////////////////////////////////////
	// The lexer itself			               //
	/////////////////////////////////////////////
	class Lexer {
	private:
		class TokenValues {
		public:
			char character;
			std::string string;
		};

	public:
		Lexer();
		~Lexer();

		Token nextToken();
		Token curToken();

		bool atEndOfBuffer();

		//sets the buffer to parse to the buffer* and resets the buffer index. The buffer should be null terminated
		void loadBuffer(const char* buffer);

		TokenValues value;

		u32 getLineNumber() const;
		u32 getCharNumber() const;

	private:
		//parses and returns the next token
		Token parseNext();
        //gets the first character that isn't whitespace
        void skipWhitespace();

		/**
		 * Every parsing function should, when eating something, make sure curChar points to the first non-eaten character
		 */

		//parses an identifier
		Token parseIdentifier();
		//parses a numeric token
		Token parseNumeric();
		//parses a keyword
		Token parseKeyword();
		//parses a special symbol
		Token parseSymbol();
        //continues to the next character in the buffer
        void nextChar();
		//returns the current character in the buffer
		char curChar();
		//returns the current character in the buffer and eats it
		char eatChar();
		//returns true if the next word is equal to `word` and if so, skips it in the buffer. it stops at non ascii characters
		bool tryCompareAndSkipNextKeyword(const char *word);
		//returns true if the next word is equal to `word` and if so, skips it in the buffer. it stops at any non matching character
		bool tryCompareAndSkipNextSymbol(const char *word);

        const char* _buffer;
		unsigned int _bufferIndex;
		Token _lastToken;
		unsigned int _lineNumber;
		unsigned int _charNumber;
	};
}