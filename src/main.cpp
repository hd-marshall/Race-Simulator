#include <SFML/Graphics.hpp>
#include "../include/Track.h"

#include <iostream>
#include <cmath>

Track createTrackObject()
{
    Track track("test");

    // Circle Track
    for (int i = 0; i < 10; ++i)
    {
        double angle = 2 * M_PI * i / 10;
        int x = static_cast<int>(570 + 200 * cos(angle));
        int y = static_cast<int>(400 + 200 * sin(angle));
        track.addTrackPoint(x, y);
    }

    // Line Track
    // for (int i = 400; i <= 900; i += 100)
    // {
    //     monacoTrack.addTrackPoint(i, 400);
    // }

    return track;
}

sf::RectangleShape createTrackVertexVisuals(Point &trackVector, int currentVector, int selectedVector)
{
    sf::RectangleShape road;
    road.setSize(sf::Vector2f(25, 25));             // Set the size of the rectangle
    road.setPosition(trackVector.x, trackVector.y); // Set the position of the rectangle
    if (selectedVector != currentVector)
    {
        road.setFillColor(sf::Color::Black); // Set the fill color of the rectangle
    }
    else
    {
        road.setFillColor(sf::Color::Red); // Set the fill color of the rectangle
    }
    road.setOutlineThickness(5); // Set the thickness of the outline
    road.setOutlineColor(sf::Color(128, 128, 128));
    return road;
}

int main()
{
    Track track = createTrackObject();
    int selectedVertex = -1;

    // Create SFML window
    sf::RenderWindow window(sf::VideoMode(1200, 800), track.getTrackName());
    sf::Vector2i *mousePosPtr = new sf::Vector2i(sf::Mouse::getPosition(window));

    while (window.isOpen())
    {
        std::vector<Point> raceTrackVectors = track.getTrackPoints();
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
            {
                window.close();
            }

            if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left)
            {
                *mousePosPtr = sf::Mouse::getPosition(window);
                for (size_t i = 0; i < raceTrackVectors.size(); i++)
                {
                    Point &point = raceTrackVectors[i];
                    int dx = mousePosPtr->x - point.x;
                    int dy = mousePosPtr->y - point.y;

                    if (dx * dx + dy * dy <= 30 * 30)
                    {
                        selectedVertex = i;
                    }
                }
            }

            if (selectedVertex != -1 && event.type == sf::Event::KeyPressed)
            {
                if (event.key.code == sf::Keyboard::W)
                {
                    track.changeTrackPointValues("w", selectedVertex);
                }
                else if (event.key.code == sf::Keyboard::S)
                {
                    track.changeTrackPointValues("s", selectedVertex);
                }
                else if (event.key.code == sf::Keyboard::A)
                {
                    track.changeTrackPointValues("a", selectedVertex);
                }
                else if (event.key.code == sf::Keyboard::D)
                {
                    track.changeTrackPointValues("d", selectedVertex);
                }
            }
        }

        window.clear(sf::Color::Green);

        // Draw track vertices
        for (size_t i = 0; i < raceTrackVectors.size(); i++)
        {
            std::vector<Point> newTrack = track.getTrackPoints();
            window.draw(createTrackVertexVisuals(newTrack[i], i, selectedVertex));
        }

        // Draw track curve
        for (float t = 0.0f; t < (float)(track.getTrackPoints().size() - 3); t += 0.05f)
        {
            Point currentRoad = track.getTrackCurve(t);
            sf::RectangleShape pixel(sf::Vector2f(5, 5));
            pixel.setPosition(currentRoad.x, currentRoad.y);
            pixel.setFillColor(sf::Color::Red);
            window.draw(pixel);
        }

        window.display();
    }

    return 0;
}