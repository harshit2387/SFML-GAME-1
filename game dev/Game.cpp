#include "Game.h"

// Private functions
void Game::initVariables() {
    this->window = nullptr;
    // Game logic
    this->points = 0;
    this->enemySpawnTimerMax = 10.f;
    this->enemySpawnTimer = this->enemySpawnTimerMax;
    this->maxEnemies = 10;
    this->mouseHeld = false;
    this->health=10;
    this->endGame=false;
    
}

void Game::initWindow() {
    this->videoMode.height = 600;
    this->videoMode.width = 800;
    this->window = new sf::RenderWindow(this->videoMode, "Game 1", sf::Style::Titlebar | sf::Style::Close);
    this->window->setFramerateLimit(25);
}

void Game::initFonts() {
    if (!this->font.loadFromFile("fonts/Poppins-Black.ttf")) {
        std::cout << "ERR: Not able to open font file" << "\n";
    }
}

void Game::initText(){
	this->uiText.setFont(this->font);
	this->uiText.setCharacterSize(12);
	this->uiText.setFillColor(sf::Color::Red);
	this->uiText.setString("NONE ");
}
void Game::initEnemies() {
    this->enemy.setPosition(10.f, 10.f);
    this->enemy.setSize(sf::Vector2f(100.f, 100.f));
   // this->enemy.setScale(sf::Vector2f(0.5f, 0.5f));
    this->enemy.setFillColor(sf::Color::Cyan);
}

Game::Game() {
    this->initVariables();
    this->initWindow();
    this->initEnemies();
    this->initFonts();
    this->initText();
}

Game::~Game() {
    delete this->window;
}

const bool Game::running() const {
    return this->window->isOpen();
}
const bool Game::getEndGame() const {
	return this->endGame;
}
void Game::spawnEnemy() {
    this->enemy.setPosition(
        static_cast<float>(rand() % static_cast<int>(this->window->getSize().x - this->enemy.getSize().x)),
        static_cast<float>(rand() % static_cast<int>(this->window->getSize().y - this->enemy.getSize().y))
    );
    int type=rand()%5;
    switch(type)
    {	
    	case 0:
    		this->enemy.setSize(sf::Vector2f(10.f, 10.f));
    		this->enemy.setFillColor(sf::Color::Magenta);
    		break;
    	case 1:
    		this->enemy.setSize(sf::Vector2f(30.f, 30.f));
    		this->enemy.setFillColor(sf::Color::Blue);
    		break;
    	case 2:
    		this->enemy.setSize(sf::Vector2f(50.f, 50.f));
    		this->enemy.setFillColor(sf::Color::Cyan);
    		break;
    	case 3:
    		this->enemy.setSize(sf::Vector2f(70.f, 70.f));
    		this->enemy.setFillColor(sf::Color::Red);
    		break;
    	case 4:
    		this->enemy.setSize(sf::Vector2f(100.f, 100.f));
    		this->enemy.setFillColor(sf::Color::Yellow);
    		break;
    	default:
    		this->enemy.setSize(sf::Vector2f(10.f, 10.f));
    		this->enemy.setFillColor(sf::Color::Red);
    		break;
    	
    		
	}
    this->enemy.setFillColor(sf::Color::Green);
    this->enemies.push_back(this->enemy);
}

void Game::pollEvents() {
    while (this->window->pollEvent(this->ev)) {
        switch (this->ev.type) {
            case sf::Event::Closed:
                this->window->close();
                break;
            case sf::Event::KeyPressed:
                if (this->ev.key.code == sf::Keyboard::Escape)
                    this->window->close();
                break;
        }
    }
}

void Game::updateMousePosition() {
    // Update the mouse position in window (pixel) coordinates
    sf::Vector2i pixelPos = sf::Mouse::getPosition(*this->window);

    // Update the mouse position in view (world) coordinates
    this->mousePosWindow = static_cast<sf::Vector2f>(pixelPos);
    this->mousePosView = this->window->mapPixelToCoords(pixelPos);
}


void Game::updateEnemies() {
    if (this->enemies.size() < this->maxEnemies) {
        if (this->enemySpawnTimer >= this->enemySpawnTimerMax) {
            this->spawnEnemy();
            this->enemySpawnTimer = 0.f;
        } else {
            this->enemySpawnTimer += 1.f;
        }
    }

    for (int i = 0; i < this->enemies.size(); ++i) {
    	bool deleted = false;
        this->enemies[i].move(0.f, 5.f);
        if(this->enemies[i].getPosition().y> this->window->getSize().y){
        	
        	this->enemies.erase(this->enemies.begin()+i);
        	this->health-=1;
        	std::cout<<"Health: "<<this->health<<"\n";
        }
	}
	if(sf::Mouse::isButtonPressed(sf::Mouse::Left)){
		if(this->mouseHeld==false){
			this->mouseHeld=true;
		bool deleted=false;
		for(size_t i=0;i<this->enemies.size() && deleted == false;i++){
			if(this->enemies[i].getGlobalBounds().contains(this->mousePosView)){
		
			if(this->enemies[i].getFillColor() == sf::Color::Magenta){
					this->points+=10;
			}
			else if(this->enemies[i].getFillColor() == sf::Color::Blue){
				this->points+=7;
			}
			else if(this->enemies[i].getFillColor() == sf::Color::Green){
				this->points+=4;
			}
				std::cout<<"Points: "<<this->points<<"\n";
			
					deleted=true;
					this->enemies.erase(this->enemies.begin()+i);
			
			
		
		}
	}
}
	}
	else{
		this->mouseHeld=false;
	}
}
void Game::updateText(){
	std::stringstream ss;
	ss  << "Points" << this->points<<"\n"
	<<"Health"<<this->health<<"\n";
	this->uiText.setString(ss.str());
	
}

void Game::update() {
    this->pollEvents();
    if (!this->endGame) {
        this->updateMousePosition();
        this->updateText();  // Update this line
        this->updateEnemies();
    }
    if (this->health <= 0) {
        this->endGame = true;
    }
}


void Game::renderEnemies(sf::RenderTarget& target) {
    for (auto &e : this->enemies) {
        target.draw(e);
    }
}

void Game::render() {
    this->window->clear();
    this->renderEnemies(*this->window);
    
    this->renderText(*this->window);
    this->window->display();
}
void Game::renderText(sf::RenderTarget& target){
	target.draw(this->uiText);
}

