#include "Tab.hpp"
#include <string>

Tab::Tab(const std::string& title)
    : title(title)
    , font(Browser::getDefaultFont())
    , activeFlag(false)
    , header(this) {
}
void Tab::onClickCallback(int id) {
    onSelectTabCallback(this->id);
}
void Tab::draw(sf::RenderWindow& window) const {
    header.draw(window);
    if (!this->activeFlag) return;
    window.draw(content);
    window.draw(text);
}
void Tab::startup() {
    // Um retângulo simples para representar o conteúdo de uma aba
    content.setSize(sf::Vector2f(600, 400));
    content.setFillColor(sf::Color::White);
    content.setPosition(100, 150);
    std::string contentText = this->title + " is the title of tab " + std::to_string(this->getIndex()+ 1);
    // Configuração do título da aba
    text.setFont(font);
    text.setString(contentText);
    text.setCharacterSize(24);
    text.setFillColor(sf::Color::Black);
    text.setPosition(content.getPosition().x + 10, content.getPosition().y + 10);
    header.setOnClickCallback([this](int id) {
        this->onClickCallback(id);
    });
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
