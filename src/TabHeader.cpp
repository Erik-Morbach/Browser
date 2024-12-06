#include "TabHeader.hpp"
#include "Tab.hpp"

TabHeader::TabHeader(Tab* tab)
    : tab(tab)
    , font(Browser::getDefaultFont()) {
}
void TabHeader::draw(sf::RenderWindow& window) const {
    window.draw(tabShape);
    window.draw(tabText);
    window.draw(closeText);
}
void TabHeader::startup() {
    tabShape = sf::RectangleShape(sf::Vector2f(tabWidth, 30));
    tabShape.setPosition(index * tabWidth, 50);
    tabShape.setFillColor(tab->getActiveFlag() ? sf::Color(100, 100, 250)
                                               : sf::Color(200, 200, 200));

    tabText.setFont(font);
    tabText.setString("Aba " + std::to_string(this->index + 1));
    tabText.setCharacterSize(20);
    tabText.setFillColor(sf::Color::Black);
    tabText.setPosition(index * tabWidth + 10, 52);

    // Configura o "X" no final da aba
    closeText.setFont(font);
    closeText.setString("X");
    closeText.setCharacterSize(20);
    closeText.setFillColor(sf::Color::Red);
    closeText.setPosition((index + 1) * tabWidth - 20, 52);
}
void TabHeader::onClick(float x, float y) {
    if (!tabShape.getGlobalBounds().contains(x, y)) return;

    if (closeText.getGlobalBounds().contains(x, y)) {
        onRemoveCallback(this->id);
        return;
    }

    onClickCallback(this->id);
}
void TabHeader::teardown() { }
