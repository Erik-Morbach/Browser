#pragma once
#include "RenderElement.hpp"
#include <SFML/Graphics.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Window/Window.hpp>
#include <unordered_set>
#include <memory>

class Browser {
    sf::RenderWindow window;
    std::unordered_set<std::shared_ptr<RenderElement>> elements;

public:
    inline static sf::Font& getDefaultFont() {
        static bool firstExecution = true;
        static sf::Font defaultFont;
        if (firstExecution and !defaultFont.loadFromFile("resources/tuffy.ttf")) {
            throw std::runtime_error("Error while loading font");
        }
        firstExecution = false;
        return defaultFont;
    }
    Browser();
    void run();

private:
    void processEvents();
    void processClick(sf::Event event);
    void onClick(float x, float y);
    void render();
};
