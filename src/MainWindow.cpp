#pragma once
#include "MainWindow.hpp"

MainWindow::MainWindow() {
}
void MainWindow::startup() {
    newTabButton.setPosition(10, 10);
    newTabButton.setSize(100, 30);
    newTabButton.setBackgroundColor(sf::Color(244, 162, 97));
    newTabButton.setTextColor(sf::Color::Black);
    newTabButton.setText("Nova Aba");
    newTabButton.setOnClickCallback([this](int id) {
        this->addNewTab();
    });
    newTabButton.startup();

    openHtmlButton.setPosition(10, 10);
    openHtmlButton.setSize(100, 30);
    openHtmlButton.setBackgroundColor(sf::Color(244, 162, 97));
    openHtmlButton.setTextColor(sf::Color::Black);
    openHtmlButton.setText("Abrir Html");
    openHtmlButton.setOnClickCallback([this](int id) {
        this->addNewHtmlTab();
    });
    openHtmlButton.startup();
}
void MainWindow::teardown() {
}

void MainWindow::onClick(float x, float y) {
    newTabButton.onClick(x, y);
    openHtmlButton.onClick(x, y);
    for (auto tab : this->tabs) {
        tab.onClick(x, y);
    }
}
void MainWindow::draw(sf::RenderWindow& window) const {
    this->newTabButton.draw(window);
    this->openHtmlButton.draw(window);
    for (auto& tab : this->tabs)
        tab.draw(window);
}
void MainWindow::addNewHtmlTab() {
}
void MainWindow::addNewTab() {
    if (tabs.size() >= 4) return;

    tabs.emplace_back("teste");
    Tab& newTab = tabs.back();
    newTab.setOnSelectTabCallback([this](int id) {
        this->onSelectTab(id);
    });
    newTab.startup();
    if (tabs.size() == 1)
        onSelectTab(newTab.getId());
    reorderTabs();
    reloadTabs();
}

void MainWindow::onSelectTab(int id) {
    for (auto& tab : this->tabs) {
        tab.setActiveFlag(tab.getId() == id);
    }
}
void MainWindow::reorderTabs() {
    int index = 0;
    for (auto& tab : this->tabs) {
        tab.setIndex(index++);
    }
}
void MainWindow::reloadTabs() {
    for (auto& tab : this->tabs) {
        tab.startup();
    }
}
void MainWindow::onRemoveTab(int id) {
    auto it = tabs.begin();
    while (it != tabs.end()) {
        if (it->getId() == id) {
            it->teardown();
            tabs.erase(it);
            break;
        }
    }
}
