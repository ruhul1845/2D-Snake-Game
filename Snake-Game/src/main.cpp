#include "Game.hpp"
#include "SFML/Graphics.hpp"
#include  "SFML/Audio.hpp"
#include  <iostream>
int main()
{
    // sf::Music music;
    
    // // Load and play the music
    // if (!music.openFromFile("assets/music/game.wav"))
    // {
    //     // Error loading the music file
    //     // Handle the error if needed
    //     return 1; // Exit with an error status
    // }

    // music.play();
    // music.setVolume(100);
    
    Game game;
    game.Run();

    return 0;
}
