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
    sf::RectangleShape tabShape;
    std::function<void(int)> onRemoveCallback;
    std::function<void(int)> onClickCallback;

public:
    TabHeader(Tab* tab, std::function<void(int)> onClickCallback);

    void draw(sf::RenderWindow& window) const override;
    void startup() override;
    void onClick(float x, float y) override;
    void teardown() override;

    int setIndex(int index) { this->index = index; }
    int getIndex() const { return this->index; }
    sf::RectangleShape getShape() const { return this->tabShape; }
};
