// SomePhysics.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include <iostream>
#include <SFML/Graphics.hpp>
#include "Platform.hpp"
#include <chrono>
#include "BaseRigidBody.hpp"
#define SCREEN_W 1920
#define SCREEN_H 1080
#define IMPULSE 50.0f
#define WORLD_GRAVITY 9.81f
#define MOVE_SPEED_UNIT 1000.0f
sf::Vector2f offset(SCREEN_W / 2, -SCREEN_H / 2);
void handleKeyboard(Platform* platform, BaseRigidBody* brb, bool* keys, float elapsedMs, sf::View * view) {
    if (keys[sf::Keyboard::Key::Up]) {
        platform->onMoveUp(elapsedMs);
        brb->revalidate(platform->angle, IMPULSE);
    }
    else if (keys[sf::Keyboard::Key::Down]) {
        platform->onMoveDown(elapsedMs);
        brb->revalidate(platform->angle, IMPULSE);
    }
    if (keys[sf::Keyboard::Key::W]) {
        view->move(sf::Vector2f(0, -MOVE_SPEED_UNIT * elapsedMs * 0.001f));
        platform->onMoveMap(view->getCenter());
    }
    if (keys[sf::Keyboard::Key::D]) {   
        view->move(sf::Vector2f(MOVE_SPEED_UNIT * elapsedMs * 0.001f, 0));
        platform->onMoveMap(view->getCenter());
    }
    if (keys[sf::Keyboard::Key::A]) {
        view->move(sf::Vector2f(-MOVE_SPEED_UNIT * elapsedMs * 0.001f, 0));
        platform->onMoveMap(view->getCenter());
    }
    if (keys[sf::Keyboard::Key::S]) {
        view->move(sf::Vector2f(0, MOVE_SPEED_UNIT * elapsedMs * 0.001f));
        platform->onMoveMap(view->getCenter());
    }
}
int main()
{
    sf::ContextSettings settings;
    settings.antialiasingLevel = 8;
    sf::RenderWindow window(sf::VideoMode(SCREEN_W, SCREEN_H), "Physycs", 7u, settings);
    sf::View view(sf::FloatRect(0.0f, 0.0f, SCREEN_W, SCREEN_H));
    view.setViewport(sf::FloatRect(0.0f,0.0f, 1.f, 1.f));
    Platform plaform(SCREEN_W, SCREEN_H);
    BaseRigidBody baseRigidBody = BaseRigidBody(WORLD_GRAVITY,1,plaform.getCenter());
    window.setVerticalSyncEnabled(true);
    auto start = std::chrono::high_resolution_clock::now();
    bool bPressedArrays[256] = { false };
   
    window.setView(view);
    view.move(offset);
 
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
            if (event.type == sf::Event::MouseWheelScrolled) {
                if (event.mouseWheelScroll.delta > 0)
                    view.zoom(0.97);
                else
                    view.zoom(1.03);  
                plaform.onChangeWorld(view.getSize().x, view.getSize().y);
            }
            if (event.type == sf::Event::Resized){
                sf::FloatRect visibleArea(0.f, 0.f, event.size.width, event.size.height);
                view.reset(visibleArea);
              
                plaform.onResize(event.size.width, event.size.height);   
                baseRigidBody.onResize(plaform.getCenter());
                window.setView(view);
            }
        }
        handleKeyboard(&plaform, &baseRigidBody, bPressedArrays, microseconds * 0.001f,&view);
        window.setView(view);
        window.clear();
        window.draw(baseRigidBody);
        window.draw(plaform);
       
        window.display();
        start += elapsed;
    }

    return 0;
}
