#include "Game.h"

//============= PRIVATE =================//
// Game save files
void Game::createSaveFile()
{
    /**
        @return void

        - Creates a save file
        - Saves the most recent player score
    */

    std::string filename("gamesave.txt");
    std::fstream output_fstream;

    std::cout << "\nSaving game..." << std::endl;

    output_fstream.open(filename, std::ios_base::out);
    if (output_fstream.is_open())
    {
        output_fstream << this->points << std::endl;
        std::cout << "√ Success\n" << std::endl;
    }
    else std::cerr << "x Error saving game!" << std::endl;
}

void Game::loadSaveFile()
{
    /**
        @return void

        - Loads a save file
        - Loads the most recent player score
    */
    std::string line;
    std::ifstream saveFile("gamesave.txt");
    
    std::cout << "Loading save file..." << std::endl;
    
    if (saveFile.is_open())
    {
        while (std::getline(saveFile, line))
            this->lastScore = line;
        
        saveFile.close();
        std::cout << "√ Success"<< std::endl;
    }
    else std::cerr << "x No save file found...will create" << std::endl;
    
}

// Initialization
void Game::initVariables()
{
    std::cout << "Initializing values..." << std::endl;

    this->window             = nullptr;
    this->endGame            = false;
    this->mouseHeld          = false;
    this->points             = 0;
    this->shots              = 0;
    this->maxEnemies         = 10;
    this->enemiesDestroyed   = 0;
    this->health             = 100;
    this->accuracy           = 0.0f;
    this->enemySpawnTimerMax = 20.f;
    this->enemySpawnTimer    = this->enemySpawnTimerMax;

    std::cout << "√ Success" << std::endl;
}

void Game::initWindow()
{
    std::cout << "Initializing window..." << std::endl;

    this->videoMode.width    = WINDOW_WIDTH;
    this->videoMode.height   = WINDOW_HEIGHT;
    this->windowTitle        = WINDOW_TITLE;
    this->window             = new sf::RenderWindow(this->videoMode, this->windowTitle);

    this->window->setFramerateLimit(60);

    std::cout << "√ Success" << std::endl;
}

void Game::initFonts()
{
    std::cout << "Initializing fonts..." << std::endl;

    if (!this->font.loadFromFile("./assets/fonts/press-start.ttf"))
        std::cout << "x Failed to load font!" << std::endl;

    std::cout << "√ Success" << std::endl;
}

void Game::initText()
{
    std::cout << "Initializing interface..." << std::endl;

    this->uiText.setFont(this->font);
    this->uiText.setCharacterSize(24);
    this->uiText.setLineSpacing(1.5);
    this->uiText.setFillColor(sf::Color(255, 255, 255, 225));
    this->uiText.setOutlineThickness(4.f);
    this->uiText.setOutlineColor(sf::Color(0, 0, 0, 200));
    this->uiText.setString("NONE");
    this->uiText.setPosition(10.f, 15.f);

    std::cout << "√ Success" << std::endl;
}

void Game::initEnemies()
{
    std::cout << "\nStarting " << WINDOW_TITLE << "..." << std::endl;

    this->enemy.setPosition(10.f, 10.f);
    this->enemy.setOutlineThickness(3.5f);
    this->enemy.setOutlineColor(sf::Color(0, 0, 0, 240));
}

//============= CONSTRUCTOR =============//
Game::Game()
{
    // Clear terminal
    system("clear");

    this->loadSaveFile();
    this->initVariables();
    this->initWindow();
    this->initFonts();
    this->initText();
    this->initEnemies();
}

//============= DESTRUCTOR ==============//
Game::~Game()
{
    delete this->window;
}

//============= PUBLIC ==================//
// Conditions
const bool Game::running() const
{
    /**
        @return bool

        - Checks if the game is running
    */
    return this->window->isOpen();
}

const bool Game::getEndGame() const
{
    /**
        @return bool

        - Ends the game
    */
    return this->endGame;
}

// Utilities
void Game::spawnEnemy()
{
    /**
        @return void

        - Sets a random position
        - Sets a random color
        - Adds enemies to the vector
    */

    this->enemy.setPosition(
        static_cast<float>(rand() % static_cast<int>(this->window->getSize().x - this->enemy.getSize().x)),
        0.f
    );

    // Randomize enemy types
    int type = rand() % 5;

    switch (type)
    {
    case 0:
        this->enemy.setSize(sf::Vector2f(35.f, 35.f));
        this->enemy.setFillColor(sf::Color::Red);
        break;
    case 1:
        this->enemy.setSize(sf::Vector2f(45.f, 45.f));
        this->enemy.setFillColor(sf::Color::Magenta);
        break;
    case 2:
        this->enemy.setSize(sf::Vector2f(65.f, 65.f));
        this->enemy.setFillColor(sf::Color::Blue);
        break;
    case 3:
        this->enemy.setSize(sf::Vector2f(85.f, 85.f));
        this->enemy.setFillColor(sf::Color::Cyan);
        break;
    case 4:
        this->enemy.setSize(sf::Vector2f(105.f, 105.f));
        this->enemy.setFillColor(sf::Color::Green);
        break;
    default:
        this->enemy.setSize(sf::Vector2f(125.f, 125.f));
        this->enemy.setFillColor(sf::Color::Yellow);
        break;
    }

    // Spawn enemy
    this->enemies.push_back(this->enemy);
}

void Game::showGameLog()
{
    /**
        @return void

        - Shows game stats
    */
    this->accuracy = (static_cast<float>(this->enemiesDestroyed) / static_cast<float>(this->shots) * 100.f);

    system("clear");
    std::cout << "\n*********** GAME OVER ***********"               << std::endl;
    std::cout << "*"                                                 << std::endl;
    std::cout << "*      Previous score: " << this->lastScore        << std::endl;
    std::cout << "*          Your score: " << this->points           << std::endl;
    std::cout << "*"                                                 << std::endl;
    std::cout << "*   Enemies destroyed: " << this->enemiesDestroyed << std::endl;
    std::cout << "*         Shots fired: " << this->shots            << std::endl;
    std::cout << "*            Accuracy: " << this->accuracy << "%"  << std::endl;
    std::cout << "*"                                                 << std::endl;
    std::cout << "*********************************"                 << std::endl;
}

void Game::pollEvents()
{
    while (this->window->pollEvent(this->event))
    {
        switch (this->event.type)
        {
        case sf::Event::Closed:
            std::cout << "\nQuitting..." << std::endl;
            this->window->close();
            break;

        case sf::Event::KeyPressed:
            if (this->event.key.code == sf::Keyboard::Escape)
                {
                    std::cout << "\nQuitting..." << std::endl;
                    this->window->close();
                }
            break;

        default:
            break;
        }
    }
}

// Updates
void Game::updateMousePositions()
{
    /**
        @return void

        - Mouse position relative to window
        - Mouse position relative to view
    */

    this->mousePosWindow = sf::Mouse::getPosition(*this->window);
    this->mousePosView   = this->window->mapPixelToCoords(this->mousePosWindow);
}

void Game::updateText()
{
    /**
        @return void

        - Set text string
        - Mouse position relative to view
    */
    std::stringstream ss;

    ss  << "Latest score : " << this->lastScore << "\n"
        << "Current score: " << this->points    << "\n"
        << "Health: "        << this->health    << "%";

    this->uiText.setString(ss.str());
}

void Game::updateEnemies()
{
    /**
        @return void

        - Updates the spawn timer
        - Spawns enemies when total enemies is less than the max
        - Moves the enemies downwards
        - Removes the enemies at the edge of the screen
    */

    // Updating the timer for enemy spawns
    if (this->enemies.size() < this->maxEnemies)
    {
        if (this->enemySpawnTimer >= this->enemySpawnTimerMax)
        {
            // Spawn enemy and reset the timer
            this->spawnEnemy();
            this->enemySpawnTimer = 0.f;
        }
        else
            this->enemySpawnTimer += 1.f;
    }

    // Moving && updating enemies
    for (int i = 0; i < this->enemies.size(); i++)
    {
        bool deleted = false;
       
        if (this->points == 0.f)
            this->enemies[i].move(0.f, 0.35f); // Movement speed(xf, yf)   
        else
            {
            if (this->enemies[i].getFillColor() == sf::Color::Red)
                this->enemies[i].move(0.f, 0.35f + (0.0001f * this->points));
            else if (this->enemies[i].getFillColor() == sf::Color::Magenta)
                this->enemies[i].move(0.f, 0.35f + (0.00011f * this->points));
            else if (this->enemies[i].getFillColor() == sf::Color::Blue)
                this->enemies[i].move(0.f, 0.35f + (0.000115f * this->points));
            else if (this->enemies[i].getFillColor() == sf::Color::Cyan)
                this->enemies[i].move(0.f, 0.35f + (0.00012f * this->points));
            else if (this->enemies[i].getFillColor() == sf::Color::Green)
                this->enemies[i].move(0.f, 0.35f + (0.000125f * this->points));
            else
                this->enemies[i].move(0.f, 0.35f + (0.00005f * this->points));
            }
        
        // If enemy is past the bottom of the screen
        if (this->enemies[i].getPosition().y > this->window->getSize().y)
        {
            this->enemies.erase(this->enemies.begin() + i);
            this->health -= 10;
        }
    }

    // Check if clicked on
    if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
    {
        if (this->mouseHeld == false)
        {
            this->shots += 1;
            this->mouseHeld = true;
            bool deleted = false;

            for (size_t i = 0; i < enemies.size() && deleted == false; i++)
            {
                if (this->enemies[i].getGlobalBounds().contains(this->mousePosView))
                {
                    // Get points
                    if (this->enemies[i].getFillColor() == sf::Color::Red)
                        this->points += 1000;
                    else if (this->enemies[i].getFillColor() == sf::Color::Magenta)
                        this->points += 750;
                    else if (this->enemies[i].getFillColor() == sf::Color::Blue)
                        this->points += 500;
                    else if (this->enemies[i].getFillColor() == sf::Color::Cyan)
                        this->points += 250;
                    else if (this->enemies[i].getFillColor() == sf::Color::Green)
                        this->points += 100;

                    // Increment the destroyed enemies counter
                    this->enemiesDestroyed += 1;

                    // Delete the enemy
                    deleted = true;
                    this->enemies.erase(this->enemies.begin() + i);
                }
            }
        }
    }
    else
    {
        this->mouseHeld = false;
    }
}

void Game::update()
{
    /**
        @return void

        - Listen for events
        - Update mouse positions
        - End the game
    */

    this->pollEvents();

    if (!this->endGame)
    {
        this->updateMousePositions();

        this->updateText();

        this->updateEnemies();
    }

    // End game condition
    if (this->health <= 0)
    {
        this->showGameLog();

        this->createSaveFile();

        this->endGame = true;
    }
}

// Rendering
void Game::renderText(sf::RenderTarget &target)
{
    target.draw(this->uiText);
}

void Game::renderEnemies(sf::RenderTarget &target)
{
    for (int i = 0; i < this->enemies.size(); i++)
        target.draw(this->enemies[i]);
}

void Game::render()
{
    /**
        @return void

        - Clear old frame
        - Render new objects
        - Display frame in window
    */

    this->window->clear();

    // Draw game objects
    this->renderEnemies(*this->window);
    this->renderText(*this->window);

    this->window->display();
}