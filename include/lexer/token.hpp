#pragma once

#include "utility/std.hpp"
#include "lexer/type.hpp"
#include "lexer/value.hpp"


namespace kh {
	struct Token {
		Token(const kh::TokenType _type, const kh::TokenValue _value, const size_t _character, const size_t _line) :
			type(_type), value(_value), character(_character), line(_line) {}

		kh::TokenType type;
		kh::TokenValue value;

		size_t character, line;
	};

	std::ostream& operator<<(std::ostream& out_stream, const kh::Token& token);
	std::wostream& operator<<(std::wostream& wout_stream, const kh::Token& token);

	kh::String repr(const kh::Token& token);
}
