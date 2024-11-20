#include "Button.hpp"
#include <SFML/System/Vector2.hpp>
#include <iostream>

Button::Button() {
}
void Button::startup() {
	std::cout << "Button with bounds at: ";
	std::cout << shape.getGlobalBounds().top << " ";
	std::cout << shape.getGlobalBounds().left << " ";
	std::cout << shape.getGlobalBounds().left + shape.getGlobalBounds().width << " ";
	std::cout << shape.getGlobalBounds().top + shape.getGlobalBounds().height << " ";
	std::cout << std::endl;
}
void Button::draw(sf::RenderWindow &window) const {
	window.draw(shape);
	window.draw(text);
}
void Button::onClick(float x, float y) {
	// TODO: bugfix, this is not calculating correctly, and sometimes it crashes
	if(!shape.getGlobalBounds().contains(x,y)) return;
	callback(this->getId());
}
void Button::teardown() { }
void Button::setPosition(float x, float y) {
	shape.setPosition(x, y);
	text.setPosition(shape.getPosition().x + 10,
		shape.getPosition().y + 5);
}
void Button::setSize(float x, float y) {
	shape.setSize(sf::Vector2f(x, y));
}
void Button::setBackgroundColor(sf::Color color) {
	shape.setFillColor(color);
}
void Button::setTextColor(sf::Color color) {
	text.setFillColor(color);
}
void Button::setText(std::string textStr) {
	text.setFont(font);
	text.setString(textStr);
	text.setCharacterSize(20);
}
void Button::setOnClickCallback(std::function<void(int)> callback) {
	this->callback = callback;
}

