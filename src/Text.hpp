#pragma once

#include "RenderElement.hpp"
#include "StyleContext.hpp"
#include <SFML/Graphics/Text.hpp>
struct Text : public RenderElement {
private:
    sf::Text textObj;
    std::string content;
    StyleContext style;

public:
    Text(std::string _content, StyleContext _style): content(_content), style(_style){
    }
    void startup() override {
        this->textObj.setString(this->content);
    }
    void draw(sf::RenderWindow&) const override { }
    void onClick(float x, float y) override { };
    void teardown() override { };
};
