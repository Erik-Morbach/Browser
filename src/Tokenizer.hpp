#pragma once

#include "Token.hpp"
#include <string>
#include <vector>


class Tokenizer{
	const std::string &text;
public:
	Tokenizer(const std::string &_text);

	std::vector<Token> parse();
};
