#include "Tab.hpp"
#include <iostream>

Tab::Tab(const std::string& title)
    : title(title)
    , font(Browser::getDefaultFont())
    , activeFlag(false)
    , header(this, [this](int id) { this->onClickCallback(id); }) {
}
void Tab::onClickCallback(int id) {
    std::cout << "Header "<<id << " clicked; selectTab"<<this->getId()<<std::endl;
    onSelectTabCallback(this->getId());
}
void Tab::draw(sf::RenderWindow& window) const {
    header.draw(window);
    window.draw(content);
    window.draw(text);
}
void Tab::startup() {
    // Um retângulo simples para representar o conteúdo de uma aba
    content.setSize(sf::Vector2f(600, 400));
    content.setFillColor(sf::Color::White);
    content.setPosition(100, 150);

    // Configuração do título da aba
    text.setFont(font);
    text.setString(title);
    text.setCharacterSize(24);
    text.setFillColor(sf::Color::Black);
    text.setPosition(content.getPosition().x + 10, content.getPosition().y + 10);
    header.startup();
}

void Tab::onClick(float x, float y) {
    header.onClick(x, y);
}
void Tab::teardown() { }
void Tab::setIndex(int index) {
    header.setIndex(index);
    header.startup();

}
