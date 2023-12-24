#pragma once

#include <memory>
#include <array>

#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Text.hpp>
#include <SFML/Audio.hpp>

#include "Game.hpp"
#include "State.hpp"
#include "Snake.hpp"

class GamePlay : public Engine::State
{
public:
    GamePlay(std::shared_ptr<Context> &context);
    ~GamePlay();

    void Init() override;
    void ProcessInput() override;
    void Update(const sf::Time& deltaTime) override;
    void Draw() override;
    void Pause() override;
    void Start() override;

private:
    std::shared_ptr<Context> m_context;
    sf::Sprite m_grass;
    sf::Sprite m_food;
    sf::Sprite m_food2;
    sf::Sprite m_food3;
    std::array<sf::Sprite, 4> m_walls;
    Snake m_snake;
    sf::Music m_music; 
    sf::Text m_scoreText;
    int m_score;
    int max;

    sf::Vector2f m_snakeDirection;
    sf::Time m_elapsedTime;

    bool m_isPaused;
};
