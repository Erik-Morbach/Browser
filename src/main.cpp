#include "Browser.hpp"
#include "HtmlTag.hpp"
#include "Tokenizer.hpp"
#include <SFML/Graphics.hpp>
#include <fstream>
#include <functional>
#include <ios>
#include <iostream>
#include <memory>

int main() {
	std::function<std::shared_ptr<HtmlTag::HtmlTag>()> fun;
	std::fstream file("input.html", std::ios::in);
	std::string text;
	while(!file.eof()) text += file.get();
	std::cout << "Parsing text:"<<std::endl;
	std::cout << text;

	Tokenizer tokenizer(text);
	for(auto t: tokenizer.parse()){
		std::cout << "---------------"<<std::endl;
		std::cout << "Tag:"<<t.type << std::endl;
		std::cout << "Value:|"<<t.value << "|"<<std::endl;
	}
    Browser browser;
    browser.run();
    return 0;
}
