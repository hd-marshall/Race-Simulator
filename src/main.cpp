#include <SFML/Graphics.hpp>
#include "../include/Track.h" // Include the header file for the Track class

Track createTrackObject()
{
    // Create a track object for Monaco track
    Track monacoTrack("Monaco", 200.0); // Assuming constructor takes name and width

    // Add track points to define the Monaco track's shape
    // You can manually add points based on the Monaco track layout
    // For simplicity, we'll add some arbitrary points here
    monacoTrack.addTrackPoint(100, 100);
    monacoTrack.addTrackPoint(300, 100);
    monacoTrack.addTrackPoint(400, 200);
    monacoTrack.addTrackPoint(300, 300);
    monacoTrack.addTrackPoint(100, 300);
    monacoTrack.addTrackPoint(0, 200);

    return monacoTrack;
}

sf::RectangleShape createTrackVisual(const std::vector<Point> &trackPoints)
{
    sf::RectangleShape road;

    double sizeX = trackPoints[0].x - trackPoints[1].x;
    double sizeY = trackPoints[0].y - trackPoints[1].y + 200;

    road.setSize(sf::Vector2f(sizeX, sizeY)); // Set the size of the rectangle
    road.setPosition(600, 400);               // Set the position of the rectangle
    road.setFillColor(sf::Color::White);      // Set the fill color of the rectangle
    road.setOutlineThickness(5);              // Set the thickness of the outline

    return road;
}

int main()
{
    // Create SFML window
    Track track = createTrackObject();

    sf::RenderWindow window(sf::VideoMode(1200, 800), track.getTrackName());

    // Main loop
    while (window.isOpen())
    {
        // Handle events
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        // Clear the window
        window.clear();

        window.draw(createTrackVisual(track.getTrackPoints()));

        // Display the window
        window.display();
    }

    return 0;
}