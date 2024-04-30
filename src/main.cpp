#include <SFML/Graphics.hpp>
#include "../include/Track.h" // Include the Track header file

int main()
{
    // Create a window
    sf::RenderWindow window(sf::VideoMode(800, 600), "SFML Track Example");

    // Specify the track width
    double trackWidth = 100.0; // Change this to your desired track width

    // Create a Track object with the specified width
    Track track(trackWidth);

    // Add points to define a circular track
    const int numPoints = 50;
    const double centerX = 400.0;
    const double centerY = 300.0;
    const double radius = 300.0; // Adjust this radius based on track width

    for (int i = 0; i < numPoints; ++i)
    {
        double angle = 2 * M_PI * i / numPoints;
        double x = centerX + radius * cos(angle);
        double y = centerY + radius * sin(angle);
        track.addTrackPoint(x, y);
    }

    // Calculate track boundary points with offset for track width
    std::vector<Point> trackBoundary = track.getTrackPoints();
    for (size_t i = 0; i < trackBoundary.size() - 1; ++i)
    {
        double dx = trackBoundary[i + 1].x - trackBoundary[i].x;
        double dy = trackBoundary[i + 1].y - trackBoundary[i].y;
        double length = sqrt(dx * dx + dy * dy);
        double offsetX = (trackWidth / 2.0) * (dy / length);
        double offsetY = (trackWidth / 2.0) * (-dx / length);
        trackBoundary[i].x += offsetX;
        trackBoundary[i].y += offsetY;
    }

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

        // Draw the track
        sf::VertexArray trackLines(sf::Quads, trackBoundary.size() * 2);
        for (size_t i = 0; i < trackBoundary.size(); ++i)
        {
            int next = (i + 1) % trackBoundary.size();
            sf::Vector2f dir(trackBoundary[next].x - trackBoundary[i].x, trackBoundary[next].y - trackBoundary[i].y);
            sf::Vector2f perp(-dir.y, dir.x);
            perp /= sqrt(perp.x * perp.x + perp.y * perp.y);
            perp *= static_cast<float>(trackWidth / 2.0);

            trackLines[i * 2].position = sf::Vector2f(trackBoundary[i].x + perp.x, trackBoundary[i].y + perp.y);
            trackLines[i * 2 + 1].position = sf::Vector2f(trackBoundary[i].x - perp.x, trackBoundary[i].y - perp.y);

            trackLines[i * 2].color = sf::Color::White;
            trackLines[i * 2 + 1].color = sf::Color::White;
        }
        window.draw(trackLines);

        // Display the content of the window
        window.display();
    }

    return 0;
}