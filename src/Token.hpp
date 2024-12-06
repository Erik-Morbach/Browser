#pragma once

#include <string>

namespace TokenType{
enum TokenType{
	tag=0,
	content=1,
};
};

struct Token{
	std::string value;
	TokenType::TokenType type;
	std::string str() {
		return value + "("+std::to_string(type)+")";
	}
};
