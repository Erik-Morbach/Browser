#pragma once
#include "Browser.hpp"
#include "RenderElement.hpp"
#include "TabDfn.hpp"
#include <SFML/Graphics.hpp>
#include <SFML/Graphics/Font.hpp>
#include <functional>

class TabHeader : public RenderElement {
private:
    const float tabWidth = 200.0f;
    int index;
    Tab* tab;
    sf::Font font;
    sf::Text tabText;
    sf::Text closeText;
    sf::RectangleShape tabShape;
    std::function<void(int)> onRemoveCallback;
    std::function<void(int)> onClickCallback;

public:
    TabHeader(Tab* tab);

    void draw(sf::RenderWindow& window) const override;
    void startup() override;
    void onClick(float x, float y) override;
    void teardown() override;

    void setOnClickCallback(std::function<void(int)> callback) {
        this->onClickCallback = callback;
    }
    void setOnRemoveCallback(std::function<void(int)> callback) {
        this->onRemoveCallback = callback;
    }
    void setIndex(int index) { this->index = index; }
    int getIndex() const { return this->index; }
    sf::RectangleShape getShape() const { return this->tabShape; }
};
