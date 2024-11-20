#pragma once

#include "Browser.hpp"
#include "Button.hpp"
#include "RenderElement.hpp"
#include "Tab.hpp"
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/System/Vector2.hpp>
#include <iostream>
#include <list>
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
				std::cout << "Chegou no newTabCallback()"<<std::endl;
				this->addNewTab();
			});
		newTabButton.startup();

        openHtmlButton.setPosition(150, 10);
        openHtmlButton.setSize(100, 30);
        openHtmlButton.setBackgroundColor(sf::Color(244, 162, 97));
        openHtmlButton.setTextColor(sf::Color::Black);
        openHtmlButton.setText("Nova Aba");
        openHtmlButton.setOnClickCallback([this](int id) { });
		openHtmlButton.startup();
    }
    void teardown() override {
    }

    void onClick(float x, float y) override {
        newTabButton.onClick(x, y);
        openHtmlButton.onClick(x, y);
        for (auto tab : this->tabs) {
            tab.onClick(x, y);
        }
    }
    void draw(sf::RenderWindow& window) const override {
        this->newTabButton.draw(window);
        this->openHtmlButton.draw(window);
        for (auto tab : this->tabs)
            tab.draw(window);
    }

    void addNewTab() {
        if(tabs.size()>=4) return;

        Tab newTab("teste");
        newTab.startup();
        newTab.setOnSelectTabCallback([this](int id){this->onSelectTab(id);});

        tabs.push_back(newTab);
        if (tabs.size() == 1)
            onSelectTab(newTab.getId());

        reorderTabs();
    }

    void onSelectTab(int id) {
        std::cout << "Selecionando tab "<<id<<std::endl;
        for (auto &tab : this->tabs) {
            tab.setActiveFlag(tab.getId() == id);
        }
    }
    void reorderTabs(){
        int index = 0;
        for(auto &tab: this->tabs){
            tab.setIndex(index++);
        }
    }
    void onRemoveTab(int id) {
        auto it = tabs.begin();
        while (it != tabs.end()) {
            if (it->getId() == id) {
                it->teardown();
                tabs.erase(it);
                break;
            }
        }
    }
};
