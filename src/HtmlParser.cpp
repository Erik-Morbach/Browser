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
            if (htmlStack.top()->isClosingTag(t.value)) {
                htmlStack.pop();
                continue;
            }
            auto tag = this->nameToTag[t.value]();
            tag->setStyle(style);
            tag->setPosition(pos);
            std::cout << tag->getTagName() << std::endl;
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
