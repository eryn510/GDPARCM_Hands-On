#include <SFML/Graphics.hpp>

class MainLoop {
public:
    MainLoop();
    void run();

public:
    static const int WINDOW_WIDTH = 1920;
    static const int WINDOW_HEIGHT = 1080;
    static const sf::Time	TIME_PER_FRAME;

private:
    void processEvents();
    void update(sf::Time);
    void render();
    void handlePlayerInput(sf::Keyboard::Key, bool);

private:
    const float PlayerSpeed = 300.0f;
    const sf::Time TimePerFrame = sf::seconds(1.f / 60.f);

    sf::RenderWindow mWindow;
    sf::Font mFont;
    sf::Text mStatisticsText;
    sf::Time mStatisticsUpdateTime;

    unsigned int numFrames;
    bool mIsMovingUp = false;
    bool mIsMovingDown = false;
    bool mIsMovingLeft = false;
    bool mIsMovingRight = false;

    float elapsedTime = 0;
    float maxTime = 0.25;

    int total = 1;
    int i = 0;
    int j = 0;
};

