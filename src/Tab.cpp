#include "Tab.hpp"
#include "HtmlParser.hpp"
#include <fstream>
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
void Tab::onRemoveCallback(int id) {
    onRemoveTabCallback(this->id);
}
void Tab::draw(sf::RenderWindow& window) const {
    header.draw(window);
    if (!this->activeFlag) return;
    window.draw(content);
}
void Tab::startup() {
    content.setSize(sf::Vector2f(600, 400));
    content.setFillColor(sf::Color::White);
    content.setPosition(100, 150);

    header.setOnClickCallback([this](int id) {
        this->onClickCallback(id);
    });
    header.setOnRemoveCallback([this](int id) {
        this->onRemoveTabCallback(this->id);
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


void BasicTab::startup(){
	Tab::startup();
    std::string contentText = this->title + " is the title of tab " + std::to_string(this->getIndex()+1);
    // Configuração do título da aba
    text.setFont(font);
    text.setString(contentText);
    text.setCharacterSize(24);
    text.setFillColor(sf::Color::Black);
    text.setPosition(content.getPosition().x + 10, content.getPosition().y + 10);
}
void BasicTab::draw(sf::RenderWindow& window) const {
	Tab::draw(window);
	if(!this->getActiveFlag()) return;
	window.draw(text);
}

void HtmlTab::startup(){
	Tab::startup();
	std::fstream file("resources/input.html", std::ios::in);
	std::string text;
	while(!file.eof()) text += file.get();
	HtmlParser parser;
	for(auto element: parser.parse({int(content.getPosition().x), int(content.getPosition().y)}, text)){
		this->elements.push_back(element);
	}
}
void HtmlTab::draw(sf::RenderWindow& window) const {
	Tab::draw(window);
	if(!this->getActiveFlag()) return;
	for(auto &element: this->elements){
		element->draw(window);
	}
}
