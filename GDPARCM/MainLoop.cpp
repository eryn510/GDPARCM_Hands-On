#include "MainLoop.h"
#include "TextureManager.h"
#include "BGObject.h"
#include "IconObject.h"
#include "ObjectManager.h"
#include "TextureDisplay.h"
#include "FPSCounter.h"
#include <iostream>

const sf::Time MainLoop::TIME_PER_FRAME = sf::seconds(1.f / 60.f);

MainLoop::MainLoop() : mWindow(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "SFML Application"){
    //mWindow.setFramerateLimit(60);
    TextureManager::getInstance()->loadFromAssetList();

    //load objects
    BGObject* bgObject = new BGObject("BGObject");
    ObjectManager::getInstance()->addObject(bgObject);

    TextureDisplay* display = new TextureDisplay();
    ObjectManager::getInstance()->addObject(display);

    FPSCounter* fpsCounter = new FPSCounter();
    ObjectManager::getInstance()->addObject(fpsCounter);


    //TextureManager::getInstance()->loadSingleStreamAsset(1);
    //std::cout << TextureManager::getInstance()->getNumLoadedStreamTextures() << std::endl;
    
    /*
    for (i = 0; i < 480; i++) 
    {
        TextureManager::getInstance()->loadSingleStreamAsset(i);
    }
    */

    
}

void MainLoop::run()
{
    sf::Clock clock;
    sf::Time timeSinceLastUpdate = sf::Time::Zero;
    while (mWindow.isOpen()) {

        sf::Time deltaTime = clock.restart();
        timeSinceLastUpdate += deltaTime;
        while (timeSinceLastUpdate > TimePerFrame) {
            timeSinceLastUpdate -= TimePerFrame;
            processEvents();
            update(TimePerFrame);
        }

        render();
    }
}


void MainLoop::processEvents() {

    sf::Event event;
    if (this->mWindow.pollEvent(event)) {
        switch (event.type) {

        default: ObjectManager::getInstance()->processInput(event); break;
        case sf::Event::Closed:
            this->mWindow.close();
            break;

        }
    }
}
void MainLoop::handlePlayerInput(sf::Keyboard::Key key, bool isPressed) {
    if (key == sf::Keyboard::W)
        mIsMovingUp = isPressed;
    else if (key == sf::Keyboard::S)
        mIsMovingDown = isPressed;
    else if (key == sf::Keyboard::A)
        mIsMovingLeft = isPressed;
    else if (key == sf::Keyboard::D)
        mIsMovingRight = isPressed;
}

void MainLoop::update(sf::Time deltaTime)
{
    ObjectManager::getInstance()->update(deltaTime);
}

void MainLoop::render() {
    mWindow.clear();
    ObjectManager::getInstance()->draw(&mWindow);
    mWindow.display();
}
