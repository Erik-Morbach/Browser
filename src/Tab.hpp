#pragma once
#include "RenderElement.hpp"
#include "TabDfn.hpp"
#include "TabHeader.hpp"
#include <SFML/Graphics.hpp>
#include <SFML/Graphics/Font.hpp>
#include <SFML/Graphics/Text.hpp>
#include <functional>

class Tab : public RenderElement {
private:
    TabHeader header;
    bool activeFlag;
    std::function<void(int)> onSelectTabCallback;
    void onClickCallback(int id);
protected:
    sf::RectangleShape content;
    sf::Font& font;
    std::string title;
public:
    Tab(const std::string& title);

    virtual void draw(sf::RenderWindow& window) const override;

    virtual void startup() override;
    void onClick(float x, float y) override;
    void teardown() override;

    void setOnSelectTabCallback(std::function<void(int)> callback) {
        this->onSelectTabCallback = callback;
    }
    void setIndex(int index);
    int getIndex() { return this->header.getIndex(); }
    void setActiveFlag(bool value) {
        this->activeFlag = value;
        header.startup();
    }
    bool getActiveFlag() const { return this->activeFlag; }
};
class BasicTab : public Tab{
	sf::Text text;
public:
	BasicTab(const std::string &title): Tab(title){}
    void startup() override;
	void draw(sf::RenderWindow& window) const override;
};

class HtmlTab : public Tab{
private:
	std::vector<std::shared_ptr<RenderElement>> elements;
public:
	HtmlTab(const std::string& title) :Tab(title){}
    void startup() override;
	void draw(sf::RenderWindow& window) const override;
};
