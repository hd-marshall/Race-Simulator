#include <SFML/Graphics.hpp>
#include "../include/Track.h"

#include <iostream>
#include <cmath>

Track createTrackObject()
{
    Track track("Custom Circuit");

    // Circle Track
    for (int i = 0; i < 12; ++i)
    {
        double angle = 2 * M_PI * i / 12;
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

sf::RectangleShape createTrackPointVisuals(Point &trackPoint, int pointIndex, int selectedPointIndex)
{
    sf::RectangleShape roadPointVisual;
    roadPointVisual.setSize(sf::Vector2f(10, 10));
    roadPointVisual.setPosition(trackPoint.x, trackPoint.y);
    roadPointVisual.setOutlineThickness(3);
    roadPointVisual.setOutlineColor(sf::Color(0, 0, 0));

    if (selectedPointIndex != pointIndex)
    {
        roadPointVisual.setFillColor(sf::Color::Black);
    }
    else
    {
        roadPointVisual.setFillColor(sf::Color(255, 255, 255));
    }

    return roadPointVisual;
}

sf::RectangleShape createTrackRoadVisuals(Point roadPoint)
{
    sf::RectangleShape roadVisual;
    roadVisual.setSize(sf::Vector2f(35, 35));
    roadVisual.setPosition(roadPoint.x - 15, roadPoint.y - 15);
    roadVisual.setFillColor(sf::Color(128, 128, 128));

    return roadVisual;
}

sf::RectangleShape createCarVisuals(Car car)
{
    CarPoint carPos = car.getPosition();

    sf::RectangleShape carVisual;
    carVisual.setSize(sf::Vector2f(18, 10));
    carVisual.setPosition(carPos.x, carPos.y);
    carVisual.setFillColor(sf::Color::Blue);
    carVisual.rotate(car.getDirection());

    return carVisual;
}

std::vector<std::unique_ptr<sf::Drawable>> createTimeBoard(Car car, bool status, sf::Font &font)
{
    std::vector<std::unique_ptr<sf::Drawable>> shapes;

    // Create some shapes and add them to the vector
    std::unique_ptr<sf::RectangleShape> header = std::make_unique<sf::RectangleShape>(sf::Vector2f(200, 25));
    header->setPosition(25, 25);
    header->setFillColor(sf::Color::White);
    header->setOutlineThickness(3);
    header->setOutlineColor(sf::Color(0, 0, 0));
    shapes.push_back(std::move(header));

    std::unique_ptr<sf::RectangleShape> closeB = std::make_unique<sf::RectangleShape>(sf::Vector2f(20, 20));
    closeB->setPosition(200, 27);
    closeB->setFillColor(sf::Color::Red);
    shapes.push_back(std::move(closeB));

    sf::Text text;
    text.setString("Menu");
    text.setFont(font);
    text.setCharacterSize(15);
    text.setFillColor(sf::Color::Black);
    text.setPosition(30, 30);
    shapes.push_back(std::make_unique<sf::Text>(text));

    if (status)
    {
        std::unique_ptr<sf::RectangleShape> rectangle = std::make_unique<sf::RectangleShape>(sf::Vector2f(200, 250));
        rectangle->setPosition(25, 53);
        rectangle->setFillColor(sf::Color::White);
        rectangle->setOutlineThickness(3);
        rectangle->setOutlineColor(sf::Color(0, 0, 0));
        shapes.push_back(std::move(rectangle));

        // sf::Text carVar1;
        // carVar1.setString("Wheel Base:");
        // carVar1.setFont(font);
        // carVar1.setCharacterSize(10);
        // carVar1.setFillColor(sf::Color::Black);
        // carVar1.setPosition(28, 55);
        // shapes.push_back(std::make_unique<sf::Text>(carVar1));

        // sf::Text carVar2;
        // carVar2.setString("Fuel Level:");
        // carVar2.setFont(font);
        // carVar2.setCharacterSize(10);
        // carVar2.setFillColor(sf::Color::Black);
        // carVar2.setPosition(28, 75);
        // shapes.push_back(std::make_unique<sf::Text>(carVar2));

        // sf::Text text;
        // text.setString("Tire Diameter:");
        // text.setFont(font);
        // text.setCharacterSize(10);
        // text.setFillColor(sf::Color::Black);
        // text.setPosition(28, 95);
        // shapes.push_back(std::make_unique<sf::Text>(text));
    }

    return shapes;
}

int main()
{
    // Create track object and place the car to the inital point on the circuit
    Track track = createTrackObject();

    // Used for moving the track into different shapes
    int selectedPoint = -1;
    std::vector<Point> raceTrackPoints = track.getTrackPoints();
    size_t raceTrackPointSize = raceTrackPoints.size();

    // Logic for the car movement
    float carCircuitDist = 0.0f;
    track.getCar().setPosition({raceTrackPoints[0].x, raceTrackPoints[0].y});

    // Menu status
    bool menuStatus = true;

    // Create SFML window
    sf::RenderWindow window(sf::VideoMode(1200, 800), track.getTrackName());
    sf::Vector2i *mousePosPtr = new sf::Vector2i(sf::Mouse::getPosition(window));
    sf::Font font;
    font.loadFromFile("../lib/PressStart.ttf");

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
                // Check if the click is on the close button
                sf::Vector2i mousePos = sf::Mouse::getPosition(window);
                sf::FloatRect closeButtonBounds(200, 27, 20, 20);

                if (closeButtonBounds.contains(mousePos.x, mousePos.y))
                {
                    // Toggle the menuStatus
                    menuStatus = !menuStatus;
                }

                // Check for point selection
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
                track.getCar().setDirection(atan2(g1.y, g1.x) * 180 / M_PI);
                track.getCar().setPosition({p1.x, p1.y});

                carCircuitDist += 0.15f;
            }
        }

        window.clear(sf::Color::White);

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

        // * Draw time board
        for (const auto &shape : createTimeBoard(track.getCar(), menuStatus, font))
        {
            window.draw(*shape);
        }

        window.display();
    }

    return 0;
}