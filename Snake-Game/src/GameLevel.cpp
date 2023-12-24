#include "GameLevel.hpp"

#include "GamePlay.hpp"
#include "GamePlay1.hpp"
#include <SFML/Window/Event.hpp>

GameLevel::GameLevel(std::shared_ptr<Context> &context)
    : m_context(context), m_isHardSelected(false),
      m_isHardPressed(false), m_isEasySelected(true),
      m_isEasyPressed(false)
{
}

GameLevel::~GameLevel()
{
}

void GameLevel::Init()
{
    m_context->m_assets->AddFont(MAIN_FONT, "assets/fonts/Pacifico-Regular.ttf");
    //Back
    m_context->m_assets->AddTexture(Back, "assets/textures/mode.jpg", true);
    m_back.setTexture(m_context->m_assets->GetTexture(Back));
     m_back.setTextureRect(m_context->m_window->getViewport(m_context->m_window->getDefaultView()));

    // Title
    m_gameTitle.setFont(m_context->m_assets->GetFont(MAIN_FONT));
    m_gameTitle.setString("Select   Game   Mode");
    m_gameTitle.setOrigin(m_gameTitle.getLocalBounds().width / 2,
                          m_gameTitle.getLocalBounds().height / 2);
    m_gameTitle.setPosition(m_context->m_window->getSize().x / 2,
                            m_context->m_window->getSize().y / 2 - 150.f);

    // Play Button
    m_easy.setFont(m_context->m_assets->GetFont(MAIN_FONT));
    m_easy.setString("Easy");
    m_easy.setOrigin(m_easy.getLocalBounds().width / 2,
                           m_easy.getLocalBounds().height / 2);
    m_easy.setPosition(m_context->m_window->getSize().x / 2,
                             m_context->m_window->getSize().y / 2 - 25.f);
    m_easy.setCharacterSize(20);

    // Exit Button
    m_hard.setFont(m_context->m_assets->GetFont(MAIN_FONT));
    m_hard.setString("Hard");
    m_hard.setOrigin(m_hard.getLocalBounds().width / 2,
                           m_hard.getLocalBounds().height / 2);
    m_hard.setPosition(m_context->m_window->getSize().x / 2,
                             m_context->m_window->getSize().y / 2 + 25.f);
    m_hard.setCharacterSize(20);
}

void GameLevel::ProcessInput()
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
                if (!m_isEasySelected)
                {
                    m_isEasySelected = true;
                    m_isHardSelected = false;
                }
                break;
            }
            case sf::Keyboard::Down:
            {
                if (!m_isHardSelected)
                {
                    m_isEasySelected = false;
                    m_isHardSelected = true;
                }
                break;
            }
            case sf::Keyboard::Return:
            {
                m_isEasyPressed = false;
                m_isHardPressed = false;

                if (m_isEasySelected)
                {
                    m_isEasyPressed = true;
                }
                else
                {
                    m_isHardPressed = true;
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

void GameLevel::Update(const sf::Time &deltaTime)
{
    if (m_isEasySelected)
    {
        m_easy.setFillColor(sf::Color::Black);
        m_hard.setFillColor(sf::Color::White);
    }
    else
    {
        m_hard.setFillColor(sf::Color::Black);
        m_easy.setFillColor(sf::Color::White);
    }

    if (m_isEasyPressed)
    {
        m_context->m_states->Add(std::make_unique<GamePlay>(m_context), true);
    }
    else if (m_isHardPressed)
    {
        m_context->m_states->Add(std::make_unique<GamePlay1>(m_context), true);
    }
}

void GameLevel::Draw()
{
    m_context->m_window->clear(sf::Color::Blue);
    m_context->m_window->draw(m_back);
    m_context->m_window->draw(m_gameTitle);
    m_context->m_window->draw(m_easy);
    m_context->m_window->draw(m_hard);
    m_context->m_window->display();
}
