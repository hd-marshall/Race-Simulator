#include <SFML/Graphics.hpp>
#include "../include/Track.h"

#include <iostream>

Track createTrackObject()
{
    Track monacoTrack("Monaco");

    monacoTrack.addTrackPoint(100, 100);
    monacoTrack.addTrackPoint(300, 100);
    monacoTrack.addTrackPoint(400, 200);
    monacoTrack.addTrackPoint(300, 300);
    monacoTrack.addTrackPoint(100, 300);
    monacoTrack.addTrackPoint(0, 200);

    return monacoTrack;
}

sf::RectangleShape createTrackVectorVisuals(Point trackVector)
{
    sf::RectangleShape road;

    road.setSize(sf::Vector2f(30, 30));             // Set the size of the rectangle
    road.setPosition(trackVector.x, trackVector.y); // Set the position of the rectangle
    road.setFillColor(sf::Color::Black);            // Set the fill color of the rectangle
    road.setOutlineThickness(5);                    // Set the thickness of the outline
    road.setOutlineColor(sf::Color(128, 128, 128));

    return road;
}

void moveTrackVectorVisuals(Point &selectedVector)
{
    selectedVector.y += 30;
}

int main()
{
    // Create SFML window
    Track track = createTrackObject();
    std::vector<Point> raceTrackVectors = track.getTrackPoints();

    sf::RenderWindow window(sf::VideoMode(1200, 800), track.getTrackName());

    // Main loop
    while (window.isOpen())
    {
        // Handle events
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
            {
                window.close();
            }

            if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left)
            {
                std::cout << "Click Registered" << std::endl;
                // Call the handleClick function
                moveTrackVectorVisuals(raceTrackVectors[0]);
            }
        }

        // Clear the window
        window.clear(sf::Color::Green);

        for (std::vector<Point>::size_type i = 0; i < raceTrackVectors.size(); i++)
        {
            window.draw(createTrackVectorVisuals(raceTrackVectors[i]));
        }

        // Display the window
        window.display();
    }

    return 0;
}