#pragma once

#include "Button.hpp"
#include "RenderElement.hpp"
#include "Tab.hpp"
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/System/Vector2.hpp>
#include <list>
class MainWindow : public RenderElement {
private:
    std::list<Tab> tabs;
    Button newTabButton;
    Button openHtmlButton;

public:
    MainWindow();
    void startup() override;
    void teardown() override;

    void onClick(float x, float y) override;
    void draw(sf::RenderWindow& window) const override;
    void addNewHtmlTab();
    void addNewTab();

    void onSelectTab(int id);
    void reorderTabs();
    void reloadTabs();
    void onRemoveTab(int id);
};
