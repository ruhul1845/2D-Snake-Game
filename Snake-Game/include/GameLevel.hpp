#pragma once

#include <memory>

#include <SFML/Graphics/Text.hpp>
#include <SFML/Graphics/Sprite.hpp>

#include "State.hpp"
#include "Game.hpp"

class GameLevel : public Engine::State
{
private:
    std::shared_ptr<Context> m_context;
    sf::Text m_gameTitle;
    sf::Text m_hard;
    sf::Text m_easy;
    sf::Sprite m_back;

    bool m_isHardSelected;
    bool m_isHardPressed;

    bool m_isEasySelected;
    bool m_isEasyPressed;

public:
    GameLevel(std::shared_ptr<Context> &context);
    ~GameLevel();

    void Init() override;
    void ProcessInput() override;
    void Update(const sf::Time& deltaTime) override;
    void Draw() override;
};