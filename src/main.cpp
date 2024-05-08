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
    road.setSize(sf::Vector2f(10, 10));
    road.setPosition(trackVector.x, trackVector.y);
    if (selectedVector != currentVector)
    {
        road.setFillColor(sf::Color::Black);
    }
    else
    {
        road.setFillColor(sf::Color::Red);
    }
    road.setOutlineThickness(3);
    road.setOutlineColor(sf::Color(128, 128, 128));
    return road;
}

sf::RectangleShape createTrackRoadVisuals(Point roadPoint)
{
    sf::RectangleShape roadVisual(sf::Vector2f(35, 35));
    roadVisual.setPosition(roadPoint.x - 15, roadPoint.y - 15);
    roadVisual.setFillColor(sf::Color(128, 128, 128));

    return roadVisual;
}

sf::RectangleShape createCarVisuals(Car car)
{
    CarPoint carPos = car.getCarPos();

    sf::RectangleShape carVisual(sf::Vector2f(18, 10));
    carVisual.setPosition(carPos.x, carPos.y);
    carVisual.setFillColor(sf::Color::Blue);
    carVisual.rotate(car.getCarDirection());

    return carVisual;
}

int main()
{
    // Create track object and place the car to the inital point on the circuit
    Track track = createTrackObject();
    std::vector<Point> raceTrackPoints = track.getTrackPoints();
    size_t raceTrackPointSize = raceTrackPoints.size();

    track.getCar().setCarPos({raceTrackPoints[0].x, raceTrackPoints[0].y});
    // Logic for the car movement
    float carCircuitDist = 0.0f;
    // Used for moving the track into different shapes
    int selectedPoint = -1;

    // Create SFML window
    sf::RenderWindow window(sf::VideoMode(1200, 800), track.getTrackName());
    sf::Vector2i *mousePosPtr = new sf::Vector2i(sf::Mouse::getPosition(window));

    while (window.isOpen())
    {
        // Fill vector with updated Points of the track for the visual function
        raceTrackPoints = track.getTrackPoints();

        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
            {
                window.close();
            }

            // * Select a point
            if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left)
            {
                *mousePosPtr = sf::Mouse::getPosition(window);
                for (size_t i = 0; i < raceTrackPointSize; i++)
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

            // * Move selected point
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

            // * Car direction logic
            if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Space)
            {
                if (carCircuitDist > float(raceTrackPointSize))
                {
                    carCircuitDist -= float(raceTrackPointSize);
                }

                Point p1 = track.getTrackCurvePoint(carCircuitDist, true);
                Point g1 = track.getTrackCurveGradient(carCircuitDist, true);

                // Convert the point in radians and then degrees for the visual
                track.getCar().setCarDirection(atan2(g1.y, g1.x) * 180 / M_PI);
                track.getCar().setCarPos({p1.x, p1.y});

                carCircuitDist += 0.15f;
            }
        }

        window.clear(sf::Color::Green);

        // * Draw track curve
        for (float t = 0.0f; t < (float)(raceTrackPointSize); t += 0.01f)
        {
            Point roadPoint = track.getTrackCurvePoint(t, true);
            window.draw(createTrackRoadVisuals(roadPoint));
        }

        // * Draw track points
        for (size_t i = 0; i < raceTrackPointSize; i++)
        {
            window.draw(createTrackPointVisuals(raceTrackPoints[i], i, selectedPoint));
        }

        // * Draw the car
        window.draw(createCarVisuals(track.getCar()));

        window.display();
    }

    return 0;
}