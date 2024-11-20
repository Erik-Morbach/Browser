#pragma once

#include "IdUtils.hpp"
#include <SFML/Graphics/RenderWindow.hpp>
class RenderElement {
	int id = IdUtils::getUniqueId();
public:
	int getId() const { return this->id; }
	virtual void startup() = 0;
	virtual void draw(sf::RenderWindow&) const = 0;
	virtual void onClick(float x, float y) = 0;
	virtual void teardown() = 0;
};
