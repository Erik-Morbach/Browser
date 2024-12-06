#include "HtmlTag.hpp"
#include "Position.hpp"
#include "RenderElement.hpp"
#include "Text.hpp"
#include <SFML/Window/Keyboard.hpp>
#include <memory>

namespace HtmlTag{
std::shared_ptr<RenderElement> DocType::renderContent(const std::string &content) {
	return std::make_shared<Text>(content);
}

std::shared_ptr<RenderElement> Html::renderContent(const std::string &content) {
	return std::make_shared<Text>(content);
}

std::shared_ptr<RenderElement> Title::renderContent(const std::string &content) {
	return std::make_shared<Text>(content);
}

std::shared_ptr<RenderElement> Body::renderContent(const std::string &content) {
	return std::make_shared<Text>(content);
}
void Body::setStyle(const StyleContext &ctx) {
	this->style = ctx;
	this->style.marginTop = 20;
	this->style.marginLeft = 20;
	this->style.fontSize = 14;
}
StyleContext Body::getStyle() {
	return this->style;
}

std::shared_ptr<RenderElement> H1::renderContent(const std::string &content) {
	return std::make_shared<Text>(content);
}
void H1::setStyle(const StyleContext &ctx) {
	this->style = ctx;
	this->style.fontSize = 20;
}
StyleContext H1::getStyle() {
	return this->style;
}

std::shared_ptr<RenderElement> H2::renderContent(const std::string &content) {
	return std::make_shared<Text>(content, this->style, pos);
}
void H2::setStyle(const StyleContext &ctx) {
	this->style = ctx;
	this->style.fontSize = 16;
}
StyleContext H2::getStyle() {
	return this->style;
}

std::shared_ptr<RenderElement> P::renderContent(const std::string &content) {
	auto textElement = std::make_shared<Text>(content);
	textElement->startup();
	return textElement;
}
void P::setStyle(const StyleContext &ctx) {
	this->style = ctx;
}
StyleContext P::getStyle() {
	return this->style;
}

}
