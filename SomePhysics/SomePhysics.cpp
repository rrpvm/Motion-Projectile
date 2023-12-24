// SomePhysics.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include <iostream>
#include <SFML/Graphics.hpp>
#include "Platform.hpp"
#include <chrono>
#include "BaseRigidBody.hpp"
#define SCREEN_W 1920
#define SCREEN_H 1080
#define IMPULSE 150.0f
#define WORLD_GRAVITY 10.0f
void handleKeyboard(Platform* platform, BaseRigidBody* brb, bool* keys, float elapsedMs) {
    if (keys[sf::Keyboard::Key::Up]) {
        platform->onMoveUp(elapsedMs);
        brb->revalidate(platform->angle, IMPULSE);
    }
    else if (keys[sf::Keyboard::Key::Down]) {
        platform->onMoveDown(elapsedMs);
        brb->revalidate(platform->angle, IMPULSE);
    }
}
int main()
{
    sf::ContextSettings settings;
    settings.antialiasingLevel = 8;
    sf::RenderWindow window(sf::VideoMode(SCREEN_W, SCREEN_H), "Physycs", 7u, settings);
    Platform plaform(SCREEN_W, SCREEN_H);
    BaseRigidBody baseRigidBody = BaseRigidBody(WORLD_GRAVITY,1,plaform.getCenter());
    window.setVerticalSyncEnabled(true);

    auto start = std::chrono::high_resolution_clock::now();
    bool bPressedArrays[256] = { false };

    while (window.isOpen())
    {

        auto elapsed = std::chrono::high_resolution_clock::now() - start;
        long long microseconds = std::chrono::duration_cast<std::chrono::microseconds>(elapsed).count();
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
            if (event.type == sf::Event::KeyPressed) {     
                bPressedArrays[event.key.code] = true;           
            }
            else if (event.type == sf::Event::KeyReleased) {
                bPressedArrays[event.key.code] = false;
            }
        }
        handleKeyboard(&plaform, &baseRigidBody, bPressedArrays, microseconds * 0.001f);
        
        window.clear();
        window.draw(plaform);
        window.draw(baseRigidBody);
        window.display();
        start += elapsed;
    }

    return 0;
}
