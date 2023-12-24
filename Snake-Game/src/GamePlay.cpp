#include "GamePlay.hpp"
#include "GameOver.hpp"
#include "PauseGame.hpp"
#include<iostream>

#include<fstream>
#include <SFML/Window/Event.hpp>

#include <stdlib.h>
#include <time.h>

GamePlay::GamePlay(std::shared_ptr<Context> &context)
    : m_context(context),
      m_score(0),
      
      m_snakeDirection({16.f, 0.f}),
      m_elapsedTime(sf::Time::Zero),
      m_isPaused(false)
{
    srand(time(nullptr));
}

GamePlay::~GamePlay()
{
}

void GamePlay::Init()
{
    m_context->m_assets->AddTexture(GRASS, "assets/textures/grass.png", true);
    m_context->m_assets->AddTexture(FOOD, "assets/textures/food.png");
    m_context->m_assets->AddTexture(FOOD2, "assets/textures/food.png");
    m_context->m_assets->AddTexture(FOOD3, "assets/textures/food3.jpg");
    m_context->m_assets->AddTexture(WALL, "assets/textures/wall.png", true);
    m_context->m_assets->AddTexture(SNAKE, "assets/textures/snake.png");
  
    m_grass.setTexture(m_context->m_assets->GetTexture(GRASS));
    m_grass.setTextureRect(m_context->m_window->getViewport(m_context->m_window->getDefaultView()));
if (!m_music.openFromFile("assets/music/game1.wav")) {
        std::cout << "Error: Failed to load music" << std::endl;
        // Handle error if needed
    } else {
        // Play the music in a loop
        m_music.setLoop(true);
        m_music.setVolume(100); // Adjust volume as needed
        m_music.play();
    }
 
    for (auto &wall : m_walls)
    {
        wall.setTexture(m_context->m_assets->GetTexture(WALL));
    }

    m_walls[0].setTextureRect({0, 0, (int)m_context->m_window->getSize().x, 16});
    m_walls[1].setTextureRect({0, 0, (int)m_context->m_window->getSize().x, 16});
    m_walls[1].setPosition(0, m_context->m_window->getSize().y - 16);

    m_walls[2].setTextureRect({0, 0, 16, (int)m_context->m_window->getSize().y});
    m_walls[3].setTextureRect({0, 0, 16, (int)m_context->m_window->getSize().y});
    m_walls[3].setPosition(m_context->m_window->getSize().x - 16, 0);

    m_food.setTexture(m_context->m_assets->GetTexture(FOOD));
    m_food.setPosition(m_context->m_window->getSize().x / 2, m_context->m_window->getSize().y / 2);

    m_snake.Init(m_context->m_assets->GetTexture(SNAKE));

    m_scoreText.setFont(m_context->m_assets->GetFont(MAIN_FONT));
    m_scoreText.setString("Score : " + std::to_string(m_score));
    m_scoreText.setCharacterSize(15);
}

void GamePlay::ProcessInput()
{
    
    sf::Event event;
    while (m_context->m_window->pollEvent(event))
    {
        if (event.type == sf::Event::Closed)
        {
            m_context->m_window->close();
        }
        else if (event.type == sf::Event::KeyPressed)
        {
            sf::Vector2f newDirection = m_snakeDirection;
            switch (event.key.code)
            {
            case sf::Keyboard::Up:
                newDirection = {0.f, -16.f};
                break;
            case sf::Keyboard::Down:
                newDirection = {0.f, 16.f};
                break;
            case sf::Keyboard::Left:
                newDirection = {-16.f, 0.f};
                break;
            case sf::Keyboard::Right:
                newDirection = {16.f, 0.f};
                break;
            case sf::Keyboard::P:
                 m_music.stop();
                 break;
            case sf::Keyboard::R:
                 m_music.play();
                 break;         
            case sf::Keyboard::Escape:
                m_context->m_states->Add(std::make_unique<PauseGame>(m_context));
                break;

            default:
                break;
            }

            if (std::abs(m_snakeDirection.x) != std::abs(newDirection.x) ||
                std::abs(m_snakeDirection.y) != std::abs(newDirection.y))
            {
                m_snakeDirection = newDirection;
            }
        }
    }
}

void GamePlay::Update(const sf::Time& deltaTime)
{
   
    if (!m_isPaused)
    {
        m_elapsedTime += deltaTime;

        if (m_elapsedTime.asSeconds() > 0.1)
        {
            for (auto &wall : m_walls)
            {
                if (m_snake.IsOn(wall))
                {
                    m_context->m_states->Add(std::make_unique<GameOver>(m_context), true);
                    break;
                }
            }

            if (m_snake.IsOn(m_food))
            {
                m_snake.Grow(m_snakeDirection);

                int x = 0, y = 0;
                x = std::clamp<int>(rand() % m_context->m_window->getSize().x, 16, m_context->m_window->getSize().x - 2 * 16);
                y = std::clamp<int>(rand() % m_context->m_window->getSize().y, 16, m_context->m_window->getSize().y - 2 * 16);

                m_food.setPosition(x, y);
                m_score += 1;
                m_scoreText.setString("Score : " + std::to_string(m_score));
                 if (m_score >= 2) {  
                   
                    int x2 = std::clamp<int>(rand() % m_context->m_window->getSize().x, 16, m_context->m_window->getSize().x - 2 * 16);
                    int y2 = std::clamp<int>(rand() % m_context->m_window->getSize().y, 16, m_context->m_window->getSize().y - 2 * 16);

                    m_food2.setTexture(m_context->m_assets->GetTexture(FOOD2)); 
                    m_food2.setPosition(x2, y2);

                    
                    m_context->m_window->draw(m_food2);
                }
                if (m_score>=3)
                {
                    int x3 = std::clamp<int>(rand() % m_context->m_window->getSize().x, 16, m_context->m_window->getSize().x - 2 * 16);
                    int y3 = std::clamp<int>(rand() % m_context->m_window->getSize().y, 16, m_context->m_window->getSize().y - 2 * 16);

                    m_food3.setTexture(m_context->m_assets->GetTexture(FOOD3)); 
                    m_food3.setPosition(x3, y3);

                    
                    m_context->m_window->draw(m_food3);
                }
                
            }
            if (m_snake.IsOn(m_food2)) {
        
        m_snake.Grow(m_snakeDirection);

        int x2 = std::clamp<int>(rand() % m_context->m_window->getSize().x, 16, m_context->m_window->getSize().x - 2 * 16);
        int y2 = std::clamp<int>(rand() % m_context->m_window->getSize().y, 16, m_context->m_window->getSize().y - 2 * 16);

        m_food2.setPosition(x2, y2);
        m_score += 1;
        m_scoreText.setString("Score : " + std::to_string(m_score));
         if (m_score>=3)
                {
                    int x3= std::clamp<int>(rand() % m_context->m_window->getSize().x, 16, m_context->m_window->getSize().x - 2 * 16);
                    int y3 = std::clamp<int>(rand() % m_context->m_window->getSize().y, 16, m_context->m_window->getSize().y - 2 * 16);

                    m_food3.setTexture(m_context->m_assets->GetTexture(FOOD3)); 
                    m_food3.setPosition(x3, y3);

                    
                    m_context->m_window->draw(m_food3);
                }

       
    }
     if (m_snake.IsOn(m_food3)) {
        
        m_snake.Grow(m_snakeDirection);

        int x3 = std::clamp<int>(rand() % m_context->m_window->getSize().x, 16, m_context->m_window->getSize().x - 2 * 16);
        int y3 = std::clamp<int>(rand() % m_context->m_window->getSize().y, 16, m_context->m_window->getSize().y - 2 * 16);

        m_food3.setPosition(x3, y3);
        m_score += 1;
        m_scoreText.setString("Score : " + std::to_string(m_score));
     }
            else
            {

                 FILE *file;
                 FILE *file1;
                   FILE *file3;
                file3=fopen("assets/max.txt","r");
                if (file3==NULL)
                {
                     printf("File dosen't exists");
                }
                else{
                    fscanf(file3,"%d",&max);
                }
                fclose(file3);
                 if (max<m_score)
                 {
                     file1=fopen("assets/max.txt","w");
                     if (file1==NULL)
                              {
                              printf("File dosen't exists");
                               }
                    else{
                        fprintf(file1,"%d",m_score);
                        }
                        fclose(file1);
                 }
                 
               file=fopen("assets/score.txt","w");
               if (file==NULL)
               {
                printf("File dosen't exists");
               }
               else{
                fprintf(file,"%d",m_score);
               }
               fclose(file);
                
                m_snake.Move(m_snakeDirection);
            }
       
              if (m_snake.IsSelfIntersecting())
            {
                m_music.stop();
            }
            if (m_snake.IsSelfIntersecting())
            {
                m_context->m_states->Add(std::make_unique<GameOver>(m_context), true);
            }

            m_elapsedTime = sf::Time::Zero;
        }
    }
}

void GamePlay::Draw()
{
    m_context->m_window->clear();
    m_context->m_window->draw(m_grass);

    for (auto &wall : m_walls)
    {
        m_context->m_window->draw(wall);
    }
    m_context->m_window->draw(m_food);
      if (m_score >= 2) {  
        m_context->m_window->draw(m_food2);
    }
    if (m_score >= 3) {  
        m_context->m_window->draw(m_food3);
    }
    m_context->m_window->draw(m_snake);
    m_context->m_window->draw(m_scoreText);

    m_context->m_window->display();
}

void GamePlay::Pause()
{
    m_isPaused = true;
     if (m_isPaused){
        m_music.stop();
    }
   
}

void GamePlay::Start()
{
    m_isPaused = false;
     if (!m_isPaused)
    {
       m_music.play();
    }
   
}
