#include "Tokenizer.hpp"
#include "StringUtils.hpp"
#include "Token.hpp"

Tokenizer::Tokenizer(const std::string &_text): text(_text){
};

std::vector<Token> Tokenizer::parse(){
	std::vector<Token> tokens;
	std::string buff = "";
	bool insideTag;
	for(char c: this->text){
		if(c=='\r' or c=='\n') continue;
		if(c == '<'){
			buff = StringUtils::trim(buff);
			if(buff.size()){
				tokens.push_back({buff, TokenType::content});
				buff = "";
			}
			insideTag = true;
			continue;
		}
		if(c == '>'){
			buff = StringUtils::trim(buff);
			tokens.push_back({buff, TokenType::tag});
			insideTag = false;
			buff = "";
			continue;
		}
		buff += c;
	}
	return tokens;
}
