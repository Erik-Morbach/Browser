#pragma once
#include "TabDfn.hpp"
#include "Browser.hpp"
#include "RenderElement.hpp"
#include "TabHeader.hpp"
#include <SFML/Graphics.hpp>
#include <SFML/Graphics/Font.hpp>
#include <functional>

class Tab : public RenderElement {
private:
    TabHeader header;
    sf::RectangleShape content;
    sf::Text text;
    sf::Font& font;
    std::string title;
    bool activeFlag;
    std::function<void(int)> onSelectTabCallback;
    void onClickCallback(int id);

public:
    Tab(const std::string& title);

    void draw(sf::RenderWindow& window) const override;

    void startup() override;
    void onClick(float x, float y) override;
    void teardown() override;

	void setOnSelectTabCallback(std::function<void(int)> callback) {
		this->onSelectTabCallback = callback;
	}
	void setIndex(int index);
	int getIndex() {return this->header.getIndex(); }
    void setActiveFlag(bool value) {
		this->activeFlag = value;
		header.startup();
	}
    bool getActiveFlag() const { return this->activeFlag; }
};
