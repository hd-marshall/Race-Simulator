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

sf::RectangleShape createTrackPointVisuals(Point &trackVector, int currentVector, int selectedVector)
{
    sf::RectangleShape road;
    road.setSize(sf::Vector2f(10, 10));             // Set the size of the rectangle
    road.setPosition(trackVector.x, trackVector.y); // Set the position of the rectangle
    if (selectedVector != currentVector)
    {
        road.setFillColor(sf::Color::Black); // Set the fill color of the rectangle
    }
    else
    {
        road.setFillColor(sf::Color::Red); // Set the fill color of the rectangle
    }
    road.setOutlineThickness(3); // Set the thickness of the outline
    road.setOutlineColor(sf::Color(128, 128, 128));
    return road;
}

sf::RectangleShape createTrackRoadVisuals(Point roadPoint)
{
    sf::RectangleShape roadVisual(sf::Vector2f(25, 25));
    roadVisual.setPosition(roadPoint.x - 10, roadPoint.y - 10);
    roadVisual.setFillColor(sf::Color(128, 128, 128));

    return roadVisual;
}

sf::ConvexShape createCarVisuals(Point carPoint)
{
    // sf::RectangleShape roadVisual(sf::Vector2f(25, 25));
    // roadVisual.setPosition(roadPoint.x - 10, roadPoint.y - 10);
    // roadVisual.setFillColor(sf::Color(128, 128, 128));

    // return roadVisual;

    // Define the points of the triangle
    sf::Vector2f point1(carPoint.x + 8, carPoint.y);
    sf::Vector2f point2(carPoint.x + 16, carPoint.y);
    sf::Vector2f point3(carPoint.x + 12, carPoint.y + 12);

    // Create a triangle shape
    sf::ConvexShape carShape;
    carShape.setPointCount(3); // Set the number of points
    carShape.setPoint(0, point1);
    carShape.setPoint(1, point2);
    carShape.setPoint(2, point3);

    // Set the triangle's fill color
    carShape.setFillColor(sf::Color::Red);

    return carShape;
}

int main()
{
    Track track = createTrackObject();
    std::vector<Point> raceTrackPoints = track.getTrackPoints();
    int selectedPoint = -1;

    // Create SFML window
    sf::RenderWindow window(sf::VideoMode(1200, 800), track.getTrackName());
    sf::Vector2i *mousePosPtr = new sf::Vector2i(sf::Mouse::getPosition(window));

    while (window.isOpen())
    {
        raceTrackPoints = track.getTrackPoints();
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
                for (size_t i = 0; i < raceTrackPoints.size(); i++)
                {
                    Point &point = raceTrackPoints[i];
                    int dx = mousePosPtr->x - point.x;
                    int dy = mousePosPtr->y - point.y;

                    if (dx * dx + dy * dy <= 30 * 30)
                    {
                        selectedPoint = i;
                    }
                }
            }

            if (selectedPoint != -1 && event.type == sf::Event::KeyPressed)
            {
                if (event.key.code == sf::Keyboard::W)
                {
                    track.setTrackPointValues("w", selectedPoint);
                }
                else if (event.key.code == sf::Keyboard::S)
                {
                    track.setTrackPointValues("s", selectedPoint);
                }
                else if (event.key.code == sf::Keyboard::A)
                {
                    track.setTrackPointValues("a", selectedPoint);
                }
                else if (event.key.code == sf::Keyboard::D)
                {
                    track.setTrackPointValues("d", selectedPoint);
                }
            }

            if (event.type == sf::Event::KeyPressed)
            {
                if (event.key.code == sf::Keyboard::Space)
                {
                    float currentCarDir = track.getCar().getCarDirection();
                    track.getCar().setCarDirection(currentCarDir + 5.0f);
                }
            }
        }

        window.clear(sf::Color::Green);

        // Draw track curve
        for (float t = 0.0f; t < (float)(raceTrackPoints.size()); t += 0.01f)
        {
            Point roadPoint = track.getTrackCurvePoint(t, true);
            window.draw(createTrackRoadVisuals(roadPoint));
        }

        // Draw track vertices
        for (size_t i = 0; i < raceTrackPoints.size(); i++)
        {
            window.draw(createTrackPointVisuals(raceTrackPoints[i], i, selectedPoint));
        }

        for (float t = 0.0f; t < (float)(raceTrackPoints.size()); t += 0.01f)
        {
            Point roadPoint = track.getTrackCurvePoint(t, true);
            window.draw(createCarVisuals(roadPoint));
        }

        window.display();
    }

    return 0;
}