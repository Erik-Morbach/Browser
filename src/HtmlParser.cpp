#include "HtmlParser.hpp"
#include "HtmlTag.hpp"
#include "Position.hpp"
#include "RenderElement.hpp"
#include "StyleContext.hpp"
#include "Token.hpp"
#include "Tokenizer.hpp"
#include <iostream>
#include <memory>
#include <stack>
#include <string>

std::vector<std::shared_ptr<RenderElement>> HtmlParser::parse(Position basePos, const std::string& input) {
    std::vector<std::shared_ptr<RenderElement>> elements;
    std::vector<Token> tokens = Tokenizer(input).parse();
    StyleContext style;
    std::stack<std::shared_ptr<HtmlTag::HtmlTag>> htmlStack;
    Position pos = basePos;
    for (int i = 0; i < tokens.size(); i++) {
        if (htmlStack.size()){
            style = htmlStack.top()->getStyle();
            htmlStack.top()->setPosition(pos);
        }
        else{
            style = StyleContext();
            pos = basePos;
        }

        Token& t = tokens[i];
        if (t.type == TokenType::tag) {
			std::string tagName = t.value.substr(0, t.value.find_first_of(' '));
            if (htmlStack.size()>0 and htmlStack.top()->isClosingTag(tagName)) {
                htmlStack.pop();
                continue;
            }
			if(this->nameToTag.count(tagName) == 0){
				std::cout << "Tag name "<< tagName << " has no implementation" << std::endl;
				continue;
			}
            auto tag = this->nameToTag[tagName]();
            tag->setStyle(style);
            tag->setPosition(pos);
            htmlStack.push(tag);
            continue;
        } else {
            if(htmlStack.size()){
                elements.push_back(htmlStack.top()->renderContent(t.value));
                pos = htmlStack.top()->computeNextPosition();
            } else{
            }
        }
    }

    return elements;
}
