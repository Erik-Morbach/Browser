#include "Browser.hpp"
#include "MainWindow.hpp"

Browser::Browser()
    : window(sf::VideoMode(800, 600), "Browser window") {
    this->elements.insert(std::make_shared<MainWindow>());
}
void Browser::run() {
    for (auto element : this->elements) {
        element->startup();
    }
    while (window.isOpen()) {
        if (processEvents())
            render();
    }
    for (auto element : this->elements) {
        element->teardown();
        element.reset();
    }
}

bool Browser::processEvents() {
    sf::Event event;
    bool haveEvent = false;
    while (window.pollEvent(event)) {
        haveEvent = true;
        if (event.type == sf::Event::Closed) {
            window.close();
        }

        processClick(event);

        // Navegação pelas abas usando as setas do teclado
        if (event.type == sf::Event::KeyPressed) {
            if (event.key.code == sf::Keyboard::Right) {
            }
            if (event.key.code == sf::Keyboard::Left) {
            }
        }
    }
    return haveEvent;
}

void Browser::processClick(sf::Event event) {
    if (event.type != sf::Event::MouseButtonPressed) return;
    if (event.mouseButton.button != sf::Mouse::Left) return;
    sf::Vector2f mousePos(event.mouseButton.x, event.mouseButton.y);
    // Verificar se o clique está dentro dos limites da janela
    if (!window.getViewport(window.getView())
            .contains(event.mouseButton.x, event.mouseButton.y))
        return;
    this->onClick(mousePos.x, mousePos.y);
}
void Browser::onClick(float x, float y) {
    for (auto element : this->elements) {
        element->onClick(x, y);
    }
}
void Browser::render() {
    window.clear(sf::Color(30, 70, 83));
    for (auto element : this->elements) {
        element->draw(window);
    }
    window.display();
}
