#include "GameOver.hpp"
#include "GamePlay.hpp"
#include "GamePlay1.hpp"
#include  "GameLevel.hpp"
#include <iostream>
#include<fstream>
#include <SFML/Window/Event.hpp>

GameOver::GameOver(std::shared_ptr<Context> context)
    : m_context(context), m_isRetryButtonSelected(true),
      m_isRetryButtonPressed(false), m_isExitButtonSelected(false),
      m_isExitButtonPressed(false)
{
}

GameOver::~GameOver()
{
}

void GameOver::Init()

{
    //Back
      m_context->m_assets->AddTexture(Over, "assets/textures/Start.jpg", true);
    m_background.setTexture(m_context->m_assets->GetTexture(Over));
     m_background.setTextureRect(m_context->m_window->getViewport(m_context->m_window->getDefaultView()));

    // Title
    m_gameOverTitle.setFont(m_context->m_assets->GetFont(MAIN_FONT));
    m_gameOverTitle.setString("Game Over");
    m_gameOverTitle.setOrigin(m_gameOverTitle.getLocalBounds().width / 2,
                              m_gameOverTitle.getLocalBounds().height / 2);
    m_gameOverTitle.setPosition(m_context->m_window->getSize().x / 2,
                                m_context->m_window->getSize().y / 2 - 180.f);

//high
FILE *file1;
    file1=fopen("assets/max.txt","r");
    if (file1==NULL)
    {
       printf("File doesn't exists");
    }
    else{
        fscanf(file1,"%d",&highscore);
    }
    m_highScore.setFont(m_context->m_assets->GetFont(MAIN_FONT));
    m_highScore.setString("  High Score : " + std::to_string(highscore));

    
    m_highScore.setOrigin(m_highScore.getLocalBounds().width / 2.f, m_highScore.getLocalBounds().height / 2.f);
    m_highScore.setPosition(m_context->m_window->getSize().x / 2.f, m_context->m_window->getSize().y / 2.f-120.f);
    m_highScore.setCharacterSize(25);









// Game Score
    FILE *file;
    file=fopen("assets/score.txt","r");
    if (file==NULL)
    {
       printf("File doesn't exists");
    }
    else{
        fscanf(file,"%d",&score);
    }
    
    m_scoreText.setFont(m_context->m_assets->GetFont(MAIN_FONT));
    m_scoreText.setString("    Score : " + std::to_string(score));

    
    m_scoreText.setOrigin(m_scoreText.getLocalBounds().width / 2.f, m_scoreText.getLocalBounds().height / 2.f);
    m_scoreText.setPosition(m_context->m_window->getSize().x / 2.f, m_context->m_window->getSize().y / 2.f-90.f);
    m_scoreText.setCharacterSize(25);

    // Play Button
    m_retryButton.setFont(m_context->m_assets->GetFont(MAIN_FONT));
    m_retryButton.setString("  Retry");
    m_retryButton.setOrigin(m_retryButton.getLocalBounds().width / 2,
                            m_retryButton.getLocalBounds().height / 2);
    m_retryButton.setPosition(m_context->m_window->getSize().x / 2,
                              m_context->m_window->getSize().y / 2 - 25.f);
    m_retryButton.setCharacterSize(20);

    // Exit Button
    m_exitButton.setFont(m_context->m_assets->GetFont(MAIN_FONT));
    m_exitButton.setString("Exit");
    m_exitButton.setOrigin(m_exitButton.getLocalBounds().width / 2,
                           m_exitButton.getLocalBounds().height / 2);
    m_exitButton.setPosition(m_context->m_window->getSize().x / 2,
                             m_context->m_window->getSize().y / 2 + 25.f);
    m_exitButton.setCharacterSize(20);
}

void GameOver::ProcessInput()
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
            switch (event.key.code)
            {
            case sf::Keyboard::Up:
            {
                if (!m_isRetryButtonSelected)
                {
                    m_isRetryButtonSelected = true;
                    m_isExitButtonSelected = false;
                }
                break;
            }
            case sf::Keyboard::Down:
            {
                if (!m_isExitButtonSelected)
                {
                    m_isRetryButtonSelected = false;
                    m_isExitButtonSelected = true;
                }
                break;
            }
            case sf::Keyboard::Return:
            {
                m_isRetryButtonPressed = false;
                m_isExitButtonPressed = false;

                if (m_isRetryButtonSelected)
                {
                    m_isRetryButtonPressed = true;
                }
                else
                {
                    m_isExitButtonPressed = true;
                }

                break;
            }
            default:
            {
                break;
            }
            }
        }
    }
}

void GameOver::Update(const sf::Time &deltaTime)
{
    if (m_isRetryButtonSelected)
    {
        m_retryButton.setFillColor(sf::Color::Black);
        m_exitButton.setFillColor(sf::Color::White);
    }
    else
    {
        m_exitButton.setFillColor(sf::Color::Black);
        m_retryButton.setFillColor(sf::Color::White);
    }

    if (m_isRetryButtonPressed)
    {
        m_context->m_states->Add(std::make_unique<GameLevel>(m_context), true);
    }
    else if (m_isExitButtonPressed)
    {
        m_context->m_states->PopAll();
    }
}

void GameOver::Draw()
{
    m_context->m_window->clear(sf::Color::Blue);
    m_context->m_window->draw(m_background);
    m_context->m_window->draw(m_gameOverTitle);
    m_context->m_window->draw(m_highScore);
    m_context->m_window->draw(m_scoreText);
   
    m_context->m_window->draw(m_retryButton);
    m_context->m_window->draw(m_exitButton);
    m_context->m_window->display();
}
