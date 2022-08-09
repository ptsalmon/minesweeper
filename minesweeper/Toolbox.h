#include <SFML/Graphics.hpp>
#include "GameState.h"
#include "Button.h"

// Toolbox Class
class Toolbox {

    // Load testboard1, 2, and 3 to dynamic memory
    // so they don't have to be deleted and loaded
    // again every time
    GameState* testboard1 = new GameState("boards/testboard1.brd");
    GameState* testboard2 = new GameState("boards/testboard2.brd");
    GameState* testboard3 = new GameState("boards/testboard3.brd");

    // Private constructor and static attribute
    // for singleton pattern
    Toolbox();
    static Toolbox tb;

public:

    // Public attributes for windows and buttons
    sf::RenderWindow window;
    GameState* gameState;
    Button* debugButton;
    Button* newGameButton;
    Button* testButton1;
    Button* testButton2;
    Button* testButton3;

    // Singleton get instance returns static toolbox
    static Toolbox* getInstance() { return &tb; };

    // Destructor
    ~Toolbox();

    // My additional attributes
    // debugMode stores whether or not debugMode is active
    bool debugMode = false;

    // boardDimensions stores the dimensions of the board
    // loaded when GameState constructor is called
    sf::Vector2f boardDimensions;

    // textureMap stores textures so they can be accessed
    // easily and quickly without loading every time
    std::map<std::string, sf::Texture> textureMap;
};
