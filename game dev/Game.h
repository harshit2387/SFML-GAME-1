
#include <SFML/Graphics.hpp>
#include<vector>
#include<iostream>
#include <SFML/Window.hpp>
#include<SFML/System.hpp>
#include<SFML/Network.hpp>
#include<SFML/Audio.hpp>
#include<ctime>
#include<sstream>
//#include <SFML/Graphics.hpp>
//#include <vector>

class Game {
private:
    // Private variables
    sf::RenderWindow* window;
    sf::VideoMode videoMode;
    sf::Event ev;
    //Mouse posotion
    sf::Vector2f mousePosWindow;
	sf::Vector2f mousePosView;
	
	//Resourses
	sf::Font font;
	
	//text
	sf::Text uiText;
	
    // Game logic
    bool endGame;
    unsigned points;
    int health;
    float enemySpawnTimerMax;
    float enemySpawnTimer;
    int maxEnemies;
	bool mouseHeld;
    // Game objects
    std::vector<sf::RectangleShape> enemies;
    sf::RectangleShape enemy;

    // Private functions
    void initVariables();
    void initWindow();
    void initFonts();
    void initText();
    void initEnemies();

public:
    Game();
    virtual ~Game();

    // Accessor
    const bool running() const;
	const bool getEndGame() const;
    // Functions
    void spawnEnemy();
    void updateMousePosition();
    void updateText();
    void updateEnemies();
    void pollEvents();
    void update();
    void renderEnemies(sf::RenderTarget& target);
    void renderText(sf::RenderTarget& target);
    void render();
};

