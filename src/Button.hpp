#pragma once

#include "Browser.hpp"
#include "RenderElement.hpp"
#include <SFML/Graphics/Color.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Text.hpp>
#include <functional>
class Button : public RenderElement {
private:
    sf::RectangleShape shape;
    sf::Text text;
    sf::Font font = Browser::getDefaultFont();
    std::function<void(int)> callback;

public:
    Button();

    void startup() override;
    void draw(sf::RenderWindow& window) const override;
    void onClick(float x, float y) override;
    void teardown() override;

    void setPosition(float x, float y);
    void setSize(float x, float y);
    void setBackgroundColor(sf::Color color);
    void setTextColor(sf::Color color);
    void setText(std::string textStr);
    void setOnClickCallback(std::function<void(int)> callback);
};
