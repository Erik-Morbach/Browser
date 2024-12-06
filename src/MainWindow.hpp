#pragma once

#include "Button.hpp"
#include "HtmlParser.hpp"
#include "RenderElement.hpp"
#include "Tab.hpp"
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/System/Vector2.hpp>
#include <fstream>
#include <list>
#include <iostream>
class MainWindow : public RenderElement {
private:
    std::list<std::shared_ptr<Tab>> tabs;
    Button newTabButton;
    Button openHtmlButton;
	std::list<std::shared_ptr<RenderElement>> elements;

	void setupLastAddedTab(){
		std::shared_ptr<Tab> newTab = tabs.back();
        newTab->setOnSelectTabCallback([this](int id) {
            this->onSelectTab(id);
        });
        newTab->startup();
        if (tabs.size() == 1)
            onSelectTab(newTab->getId());
        reorderTabs();
        reloadTabs();
	}
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
            this->addBasicTab();
        });
        newTabButton.startup();
        openHtmlButton.setPosition(300, 10);
        openHtmlButton.setSize(100, 30);
        openHtmlButton.setBackgroundColor(sf::Color(244, 162, 97));
        openHtmlButton.setTextColor(sf::Color::Black);
        openHtmlButton.setText("Open Html");
        openHtmlButton.setOnClickCallback([this](int id) {
			this->addHtmlTab();
        });
        openHtmlButton.startup();
    }
    void teardown() override {
    }

    void onClick(float x, float y) override {
        newTabButton.onClick(x, y);
        openHtmlButton.onClick(x, y);
        std::list<std::shared_ptr<Tab>> tabsCopy;
        for (auto tab : this->tabs) {
            tabsCopy.push_back(tab);
        }
        for (auto tab : tabsCopy) {
            tab->onClick(x, y);
        }
    }
    void draw(sf::RenderWindow& window) const override {
        this->newTabButton.draw(window);
        this->openHtmlButton.draw(window);
        for (auto tab : this->tabs)
            tab->draw(window);
    }

	void addHtmlTab(){
        if (tabs.size() >= 4) return;
        tabs.push_back(std::make_shared<HtmlTab>("Html Tab"));
		this->setupLastAddedTab();
	}

    void addBasicTab() {
        if (tabs.size() >= 4) return;
        tabs.push_back(std::make_shared<BasicTab>("Basic Tab"));
		this->setupLastAddedTab();
    }

    void onSelectTab(int id) {
        for (auto& tab : this->tabs) {
            tab->setActiveFlag(tab->getId() == id);
        }
    }
    void reorderTabs() {
        int index = 0;
        for (auto& tab : this->tabs) {
            tab->setIndex(index++);
        }
    }
    void reloadTabs() {
        for (auto& tab : this->tabs) {
            tab->startup();
        }
    }
    void onRemoveTab(int id) {
        auto it = tabs.begin();
        while (it != tabs.end()) {
            if (it->get()->getId()== id) {
                it->get()->teardown();
                tabs.erase(it);
                break;
            } else {
                ++it;
            }
        }
    }
};
