#pragma once

#include "Button.hpp"
#include "RenderElement.hpp"
#include "Tab.hpp"
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/System/Vector2.hpp>
#include <list>
#include <iostream>
class MainWindow : public RenderElement {
private:
    std::list<Tab> tabs;
    Button newTabButton;
    Button openHtmlButton;

public:
    MainWindow() {
    }
    void startup() override {
        newTabButton.setPosition(10, 10);
        newTabButton.setSize(100, 30);
        newTabButton.setBackgroundColor(sf::Color(244, 162, 97));
        newTabButton.setTextColor(sf::Color::Black);
        newTabButton.setText("Nova Aba");
        newTabButton.setOnClickCallback([this](int id) {
            this->addNewTab();
        });
        newTabButton.startup();
    }
    void teardown() override {
    }

    void onClick(float x, float y) override {
        newTabButton.onClick(x, y);
        openHtmlButton.onClick(x, y);
        bool isTabClicked;
        std::list<Tab*> tabsCopy;
        for (auto& tab : this->tabs) {
            tabsCopy.push_back(&tab);
        }
        for (auto& tab : tabsCopy) {
            tab->onClick(x, y);
        }
    }
    void draw(sf::RenderWindow& window) const override {
        this->newTabButton.draw(window);
        this->openHtmlButton.draw(window);
        for (auto& tab : this->tabs)
            tab.draw(window);
    }

    void addNewTab() {
        if (tabs.size() >= 4) return;

        tabs.emplace_back("teste");
        Tab& newTab = tabs.back();
        newTab.setOnSelectTabCallback([this](int id) {
            this->onSelectTab(id);
        });
        newTab.setOnRemoveTabCallBack([this](int id) {
            this->onRemoveTab(id);
        });
        newTab.startup();
        if (tabs.size() == 1)
            onSelectTab(newTab.getId());
        reorderTabs();
        reloadTabs();
    }

    void onSelectTab(int id) {
        for (auto& tab : this->tabs) {
            tab.setActiveFlag(tab.getId() == id);
        }
    }
    void reorderTabs() {
        int index = 0;
        for (auto& tab : this->tabs) {
            tab.setIndex(index++);
        }
    }
    void reloadTabs() {
        for (auto& tab : this->tabs) {
            tab.startup();
        }
    }
    void onRemoveTab(int id) {
        auto it = tabs.begin();
        while (it != tabs.end()) {
            if ((it->getId()) == id) {
                std::cout << it->getIndex() << std::endl;
                it->teardown();
                tabs.erase(it);
                break;
            } else {
                ++it;
            }
        }
    }
};
