#pragma once
#include <string>
#include <iostream>
enum TokenType {
	AbstractTokenType,
    ConstantIntegerTokenType,
    UnknownSymbolTokenType,
};

enum class Token {
	Character = 1,
	Numeric = 2,
	String = 3,
	Unknown = 4,
	Identifier = 5,
	Return = 6,
	Type = 7,
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

		//sets the buffer to parse to the buffer* and resets the buffer index. The buffer should be null terminated
		void loadBuffer(const char* buffer);

		TokenValues value;

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
        //continues to the next character in the buffer
        void nextChar();
		//returns the current character in the buffer
		char curChar();
		//returns the current character in the buffer and eats it
		char eatChar();
		//returns true if the next word is exual to `word` and if so, skips it in the buffer.
		bool tryCompareAndSkipNext(const char* word);

        std::string _currentToken;
        const char* _buffer;
		unsigned int _bufferIndex;
	};
}