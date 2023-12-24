#include "PreMenu.hpp"
#include "MainMenu.hpp"

#include <SFML/Window/Event.hpp>

PreMenu::PreMenu(std::shared_ptr<Context> &context)
    : m_context(context), is_EnterButtonPressed(false)
{
}

PreMenu::~PreMenu()
{
}

void PreMenu::Init()
{
    m_context->m_assets->AddFont(MAIN_FONT, "assets/fonts/Pacifico-Regular.ttf");
    //Back
    m_context->m_assets->AddTexture(Owner, "assets/textures/First.jpg", true);
    m_Pisoner.setTexture(m_context->m_assets->GetTexture(Owner));
     m_Pisoner.setTextureRect(m_context->m_window->getViewport(m_context->m_window->getDefaultView()));


    // Game Author Name
    m_authorName.setFont(m_context->m_assets->GetFont(MAIN_FONT));
    m_authorName.setString("Game  Made  By\n   Ruhul  Amin & \n     Al Habib");
    m_authorName.setOrigin(m_authorName.getLocalBounds().width / 2,
                           m_authorName.getLocalBounds().height / 2);
    m_authorName.setPosition(m_context->m_window->getSize().x / 2,
                             m_context->m_window->getSize().y / 2 - 150.f);
    m_authorName.setFillColor(sf::Color::Black);
    m_authorName.setCharacterSize(50);                         

    // Enter Game Button
    m_enterButton.setFont(m_context->m_assets->GetFont(MAIN_FONT));
    m_enterButton.setString("      Enter Game");
    m_enterButton.setOrigin(m_enterButton.getLocalBounds().width / 2,
                            m_enterButton.getLocalBounds().height / 2);
    m_enterButton.setPosition(m_context->m_window->getSize().x / 2,
                              m_context->m_window->getSize().y / 2 + 90.f);
    m_enterButton.setCharacterSize(38);
    m_enterButton.setFillColor(sf::Color::Red);
}

void PreMenu::ProcessInput()
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
            case sf::Keyboard::Return:
                is_EnterButtonPressed = true;
                break;
            default:
                break;
            }
        }
    }
}

void PreMenu::Update(const sf::Time &deltaTime)
{
    if (is_EnterButtonPressed)
    {
        m_context->m_states->Add(std::make_unique<MainMenu>(m_context), true);
    }
}

void PreMenu::Draw()
{
    m_context->m_window->clear(sf::Color::Blue);
    m_context->m_window->draw(m_Pisoner);
    m_context->m_window->draw(m_authorName);
    m_context->m_window->draw(m_enterButton);
    m_context->m_window->display();
}
