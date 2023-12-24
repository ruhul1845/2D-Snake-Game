#pragma once
#include <memory>

#include <SFML/Graphics/Text.hpp>
#include <SFML/Graphics/Sprite.hpp>

#include "State.hpp"
#include "Game.hpp"
class PreMenu :  public Engine::State {
private:
 std::shared_ptr<Context> m_context;
  sf::Text  m_authorName;
  sf::Text m_enterButton;
  sf::Sprite m_Pisoner; 

bool is_EnterButtonPressed;

public:
    PreMenu(std::shared_ptr<Context> &context);
    ~PreMenu();
    void Init() override;
    void ProcessInput() override;
    void Update(const sf::Time& deltaTime) override;
    void Draw() override;
};