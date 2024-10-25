// SomePhysics.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//
#include <iostream>
#include <SFML/Graphics.hpp>
#include "Platform.hpp"
#include <chrono>
#include "BaseRigidBody.hpp"
#include "BaseApplicationController.hpp"
#include <memory>
#define SCREEN_W 1920
#define SCREEN_H 1080
#define MOVE_SPEED_UNIT 1000.0f
/*
void handleKeyboard(Platform* platform, BaseRigidBody* brb, bool* keys, float elapsedMs, sf::View * view) {
   
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
}*/
int main()
{   //my objs
    std::unique_ptr<ApplicationKeyController>keyboardController(new BaseApplicationKeyController());
    std::unique_ptr<Platform> plaform(new Platform(SCREEN_W, SCREEN_H));
    keyboardController->subscribe(plaform.get());
    plaform->spawnRigidBody(new BaseRigidBody(1.0,sf::Color(0u,0u,255u,255u)));
    plaform->spawnRigidBody(new BaseRigidBody(1.5, sf::Color(255u, 255u, 255u, 255u)));

    sf::ContextSettings settings;
    settings.antialiasingLevel = 8;
    sf::RenderWindow window(sf::VideoMode(SCREEN_W, SCREEN_H), "Physycs", 7u, settings);
    sf::View view(sf::FloatRect(0.0f, 0.0f, SCREEN_W, SCREEN_H));
    view.setViewport(sf::FloatRect(0.0f,0.0f, 1.f, 1.f));
    window.setVerticalSyncEnabled(true);
    window.setView(view);
    view.setCenter(sf::Vector2f(.0f,.0f));
   
    while (window.isOpen())
    {
        static auto start = std::chrono::high_resolution_clock::now();
        auto elapsed = std::chrono::high_resolution_clock::now() - start;
        long long microseconds = std::chrono::duration_cast<std::chrono::microseconds>(elapsed).count();
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
            else if (event.type == sf::Event::KeyPressed || event.type == sf::Event::KeyReleased) {     
                try {
                    keyboardController->processKeyboard(&event.key, event.type == sf::Event::KeyPressed ? KeyEventType::PRESSED : KeyEventType::RELEASED);
                }
                catch (std::exception& e) {

                }
            }
            else  if (event.type == sf::Event::MouseWheelScrolled) {
                if (event.mouseWheelScroll.delta > 0)
                    view.zoom(0.97);
                else
                    view.zoom(1.03);  
                plaform->onResize(view.getSize().x, view.getSize().y);
            }
            else if (event.type == sf::Event::Resized){
                sf::FloatRect visibleArea(0.f, 0.f, event.size.width, event.size.height);
                view.reset(visibleArea);
                plaform->onResize(event.size.width, event.size.height);   
                window.setView(view);
            }
        }
        //хорошо бы написать фабрику для GameObject's с объектом,который будет знать обо всех Game'Objectaх. Но ограниченное время не позволяет мне это доделать
        plaform->update(microseconds * 0.001f);

        window.setView(view);
        window.clear();
        window.draw(*plaform);
        window.display();
        start += elapsed;
    }

    return 0;
}
