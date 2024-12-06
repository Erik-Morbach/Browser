#pragma once

#include "Browser.hpp"
#include "Position.hpp"
#include "RenderElement.hpp"
#include "StyleContext.hpp"
#include <SFML/Graphics/Rect.hpp>
#include <SFML/Graphics/Text.hpp>
struct Text : public RenderElement {
private:
    sf::Text textObj;
    std::string content;
    StyleContext style;
	Position pos;

public:
    Text(std::string _content, StyleContext _style, Position _pos): content(_content), style(_style), pos(_pos){
    }
    void startup() override {
		this->textObj.setFont(Browser::getDefaultFont());
		this->textObj.setCharacterSize(this->style.fontSize);
		this->textObj.setFillColor(sf::Color::Black);
        this->textObj.setString(this->content);
		this->textObj.setPosition(pos.x, pos.y + style.marginTop);
    }
    void draw(sf::RenderWindow& window) const override {
		window.draw(this->textObj);
	}
    void onClick(float x, float y) override { };
    void teardown() override { };
	Position computeNextPosition() {
		sf::FloatRect globalBounds = this->textObj.getGlobalBounds();
		Position nextPos = this->pos;
		nextPos.y += this->style.fontSize + this->style.marginBottom;
		return nextPos;
	}
};
