/*! \brief Display
 *
 * Implementation of a component
 *
 * File:   Display.cpp
 * Author: Dieter Steuten
 *
 */

#include "Display.hpp"

#include <unistd.h>

sf::RenderWindow window(sf::VideoMode(150, 150), "Display");
sf::RectangleShape shape({(float)1, (float)1});
// sf::VertexArray lines;
sf::VertexArray lines(sf::LinesStrip, 2);

Display::Display() {}

/* --- protected functionality --- */
bool Display::P(bool run) {
    if (data.change_request && run) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        if (popVectorEmpty()) {
            usleep(1000);
        }
        return true;
    }
    return false;
}

/* private processing functions */

bool Display::popVectorEmpty() {
    //  positionABS apoint;
    lineABS aline;
    window.clear();
    /*   while (!inner.flatcontent.empty()) {
           apoint = inner.flatcontent.back();
           inner.flatcontent.pop_back();
           shape.setPosition(apoint.X, apoint.Y);
           window.draw(shape);
       }*/
    while (!data.linecontent.empty()) {
        aline = data.linecontent.back();
        data.linecontent.pop_back();
        if (aline.direction != lineDirection::undefined) {
            shape.setFillColor(sf::Color::Green);
            lines[0].position = sf::Vector2f(aline.line_start.X, aline.line_start.Y);
            lines[1].position = sf::Vector2f(aline.line_end.X, aline.line_end.Y);
        } else {
            shape.setFillColor(sf::Color::Red);
            lines[0].position = sf::Vector2f(aline.line_start.X, aline.line_start.Y);
            lines[1].position = sf::Vector2f(aline.line_end.X, aline.line_end.Y);
        }
        window.draw(lines);
        window.display();
        usleep(1000);
    }

    return true;
}