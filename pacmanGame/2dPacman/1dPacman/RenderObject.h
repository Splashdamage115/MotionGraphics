#ifndef SINGLETON_H
#define SINGLETON_H

#include<SFML/Graphics.hpp>
#include<vector>
#include<iostream>

#include"Globals.h"

class RenderObject
{
public:
    static RenderObject& getInstance()
    {
        static RenderObject instance;
        return instance;
    }

// DELETE FUNCTIONS TO AVOID MORE INSTANCES
    RenderObject(RenderObject const&) = delete;
    void operator=(RenderObject const&) = delete;

    sf::RenderWindow& getWindow() { return m_window; }
    void closeWindow() { m_window.close(); }

    // add a new item to be rendered
    void add(std::shared_ptr<sf::Drawable> t_new);

    // clear list of render objects
    void clear();

    void render();
private:
    RenderObject(); // Constructor

    std::vector<std::weak_ptr< sf::Drawable >> m_assets;

    sf::RenderWindow m_window;
};

#endif // !SINGLETON_H
