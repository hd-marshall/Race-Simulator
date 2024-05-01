#include <SFML/Graphics.hpp>
#include "../include/Track.h"

Track createTrackObject()
{
    Track monacoTrack("Monaco");

    for (int i = 0; i < 10; ++i)
    {
        double angle = 2 * M_PI * i / 10;
        int x = static_cast<int>(570 + 200 * cos(angle));
        int y = static_cast<int>(400 + 200 * sin(angle));
        monacoTrack.addTrackPoint(x, y);
    }

    return monacoTrack;
}

sf::RectangleShape createTrackVertexVisuals(Point trackVector, int currentVector, int selectedVector)
{
    sf::RectangleShape road;

    road.setSize(sf::Vector2f(30, 30));             // Set the size of the rectangle
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

void moveTrackVertexVisuals(Point &selectedVector)
{
    selectedVector.y += 30;
}

int main()
{
    Track track = createTrackObject();
    std::vector<Point> raceTrackVectors = track.getTrackPoints();
    int selectedVertex = -1;

    // Create SFML window
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
                sf::Vector2i mousePos = sf::Mouse::getPosition(window);

                for (size_t i = 0; i < raceTrackVectors.size(); i++)
                {
                    Point &point = raceTrackVectors[i];
                    int dx = mousePos.x - point.x;
                    int dy = mousePos.y - point.y;

                    // Check if the mouse position is within a range of 30 pixels from the track point
                    if (dx * dx + dy * dy <= 30 * 30)
                    {
                        // Perform your action for clicking on the point
                        moveTrackVertexVisuals(point);
                        selectedVertex = i;
                    }
                }
            }

            // Draw Background
            window.clear(sf::Color::Green);

            for (size_t i = 0; i < raceTrackVectors.size(); i++)
            {
                // Draw vector of points
                window.draw(createTrackVertexVisuals(raceTrackVectors[i], i, selectedVertex));
            }

            // Display the window
            window.display();
        }
    }

    return 0;
}