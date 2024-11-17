#include <SFML/Graphics.hpp>
#include <list>
#include <string>
#include <iostream>

class Tab {
public:
    Tab(const std::string& title, sf::Font& font) : title(title), font(font) {
        // Um retângulo simples para representar o conteúdo de uma aba
        content.setSize(sf::Vector2f(600, 400));
        content.setFillColor(sf::Color::White);
        content.setPosition(100, 150);

        // Configuração do título da aba
        text.setFont(font);
        text.setString(title);
        text.setCharacterSize(24);
        text.setFillColor(sf::Color::Black);
        text.setPosition(content.getPosition().x + 10, content.getPosition().y + 10);
    }

    void draw(sf::RenderWindow& window) {
        window.draw(content);
        window.draw(text);
    }

private:
    sf::RectangleShape content;
    sf::Text text;
    sf::Font& font;
    std::string title;

};

class BrowserWindow {
public:
    BrowserWindow() : window(sf::VideoMode(800, 600), "Simulador de Navegador - SFML") {
        if (!font.loadFromFile("resources/tuffy.ttf")) {
            std::cerr << "Erro ao carregar a fonte!" << std::endl;
        }

        addTab("Aba Inicial");
        selectedTab = tabs.begin();  // Apontar para a primeira aba

        // Inicializar o botão "Nova Aba" na parte superior da janela
        newTabButton.setSize(sf::Vector2f(100, 30));
        newTabButton.setPosition(10, 10); // Posição no topo da janela
        newTabButton.setFillColor(sf::Color(100, 200, 100));

        newTabButtonText.setFont(font);
        newTabButtonText.setString("Nova Aba");
        newTabButtonText.setCharacterSize(20);
        newTabButtonText.setFillColor(sf::Color::Black);
        newTabButtonText.setPosition(newTabButton.getPosition().x + 10, newTabButton.getPosition().y + 5);

        tabWidth = 200.0f; // Largura das abas
    }

    void run() {
        while (window.isOpen()) {
            processEvents();
            render();
        }
    }

private:
    sf::RenderWindow window;
    std::list<Tab> tabs;
    std::list<Tab>::iterator selectedTab;
    sf::Font font;
    sf::Text tabText;

    sf::RectangleShape newTabButton;
    sf::Text newTabButtonText;

    float tabWidth;

    void addTab(const std::string& title) {
        Tab newTab(title, font);  // Construímos o objeto `Tab`
        tabs.push_back(newTab);   // Adicionamos o objeto `Tab` na lista
        if (tabs.size() == 1) {
            selectedTab = tabs.begin();  // Seleciona a aba recém-criada se for a única
        }
    }

    void processEvents() {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }

            // Verificar cliques do mouse
            if (event.type == sf::Event::MouseButtonPressed) {
                if (event.mouseButton.button == sf::Mouse::Left) {
                    sf::Vector2f mousePos(event.mouseButton.x, event.mouseButton.y);

                    // Verificar se o clique está dentro dos limites da janela
                    if (window.getViewport(window.getView()).contains(event.mouseButton.x, event.mouseButton.y)) {

                        // Verificar se o botão "Nova Aba" foi clicado
                        if (newTabButton.getGlobalBounds().contains(mousePos)) {
                            addTab("Nova Aba " + std::to_string(tabs.size() + 1));
                        }

                        // Verificar se alguma aba foi clicada para selecioná-la
                        int index = 0;
                        for (auto it = tabs.begin(); it != tabs.end(); ++it, ++index) {
                            sf::FloatRect tabRect(index * tabWidth, 50, tabWidth, 30);
                            if (tabRect.contains(mousePos)) {
                                selectedTab = it;
                                break;
                            }
                        }
                    }
                }
            }

            // Navegação pelas abas usando as setas do teclado
            if (event.type == sf::Event::KeyPressed) {
                if (event.key.code == sf::Keyboard::Right) {
                    if (selectedTab != std::prev(tabs.end())) {
                        ++selectedTab;
                    } else {
                        selectedTab = tabs.begin();  // Voltar para a primeira aba
                    }
                }
                if (event.key.code == sf::Keyboard::Left) {
                    if (selectedTab != tabs.begin()) {
                        --selectedTab;
                    } else {
                        selectedTab = std::prev(tabs.end());  // Ir para a última aba
                    }
                }
            }
        }
    }

    void render() {
        window.clear(sf::Color(50, 50, 50));

        // Renderizar o botão "Nova Aba" na parte superior
        window.draw(newTabButton);
        window.draw(newTabButtonText);

        // Renderizar as abas logo abaixo do botão
        int index = 0;
        for (auto it = tabs.begin(); it != tabs.end(); ++it, ++index) {
            sf::RectangleShape tabShape(sf::Vector2f(tabWidth, 30));
            tabShape.setPosition(index * tabWidth, 50); // Posição ajustada abaixo do botão
            tabShape.setFillColor((it == selectedTab) ? sf::Color(100, 100, 250) : sf::Color(200, 200, 200));
            window.draw(tabShape);

            // Desenhar o título da aba
            tabText.setFont(font);
            tabText.setString("Aba " + std::to_string(index + 1));
            tabText.setCharacterSize(20);
            tabText.setFillColor(sf::Color::Black);
            tabText.setPosition(index * tabWidth + 10, 52); // Ajuste de posição do texto
            window.draw(tabText);
        }

        // Renderizar o conteúdo da aba selecionada, se houver abas disponíveis
        if (!tabs.empty() && selectedTab != tabs.end()) {
            selectedTab->draw(window);
        }

        window.display();
    }
};

int main() {
    BrowserWindow browser;
    browser.run();
    return 0;
}
