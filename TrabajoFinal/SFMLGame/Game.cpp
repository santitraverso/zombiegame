#include "Game.h"
#include "HealthBar.h"
#include <cmath>
#include <random>


const static int gameWidth = 1280;
const static int gameHeight = 720;
const int entitySize = 80;
const float radius = gameWidth + 50.0f; 
const float center_x = gameWidth / 2;
const float center_y = gameHeight /2 ;

void Game::_Update(float deltaTime)
{
    EntityManager::GetInstance()->UpdateEntities(deltaTime);
    CollisionManager::GetInstance()->UpdateCollisions();
}

void Game::_Draw()
{
    window->clear(Color::Color(128, 128, 128, 255));
    for (Entity* entity : EntityManager::GetInstance()->GetEntities())
    {
        window->draw(*entity);
    }
    for (Text* textEntity : EntityManager::GetInstance()->GetTextEntities())
    {
        if (textEntity != nullptr)
            window->draw(*textEntity);
    }
    window->display();
}

Game::Game() {
    window = new RenderWindow(sf::VideoMode(gameWidth, gameHeight), "My window");

    player = new Player(gameWidth, gameHeight);
    player->Init(window);
    HealthBar* healthBar = new HealthBar(player);
    healthBar->Init();
    player->setPosition(gameWidth/2, gameHeight/2);
    player->SetSpriteSize(entitySize, entitySize); 
    CollisionManager::GetInstance()->AddEntity(player);
    CreateEnemies();
    isRunning = true;
}

void Game::CreateEnemies()
{
    std::mt19937 rng(std::random_device{}());

    std::uniform_real_distribution<float> dist(10.0f, 100.0f);

    for (int i = 0; i <= maxEnemies; i++)
    {
        float randomRadius = dist(rng);
        float angle = (2 * pi / maxEnemies) * i; 
        float x = center_x + (radius + randomRadius) * cos(angle);
        float y = center_y + (radius + randomRadius)* sin(angle);

        Enemy* enemy = new Enemy(gameWidth, gameHeight);
        enemy->Init(player,x , y);
        enemy->SetSpriteSize(entitySize, entitySize);
        CollisionManager::GetInstance()->AddEntity(enemy);
        enemies.push_back(enemy);
    }
}

Game::~Game() {
    if (window)
    {
        delete window;
        window = nullptr;
    }
    if (EntityManager::GetInstance())
    {
        delete EntityManager::GetInstance();
    }
    if (CollisionManager::GetInstance())
    {
        delete CollisionManager::GetInstance();
    }
}

void Game::Run() {

    Clock clockDelta;
    float deltaTime = clockDelta.restart().asSeconds();

    while (window->isOpen() || isRunning)
    {
        deltaTime = clockDelta.restart().asSeconds();
     
        Event event;
        while (window->pollEvent(event))
        {
            if (event.type == sf::Event::MouseButtonPressed)
            {
                if (event.mouseButton.button == sf::Mouse::Left)
                {
                    int x = event.mouseButton.x;
                    int y = event.mouseButton.y;
                    EntityManager::GetInstance()->OnMouseClick(x, y);
                }
            }

            if (event.type == sf::Event::Closed)
                window->close();
        }

        _Update(deltaTime);
        _Draw();
    }
}