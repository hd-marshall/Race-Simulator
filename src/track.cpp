#include "../include/Track.h"

// Constructor
Track::Track(double width) : trackWidth(width) {}

// Accessors
const std::vector<Point> &Track::getTrackPoints() const
{
    return this->trackPoints;
}

// Function to add a point to the track boundary
void Track::addTrackPoint(double x, double y)
{
    trackPoints.push_back({x, y});
}

// Function to calculate the distance between two points
double Track::distanceBetweenPoints(const Point &p1, const Point &p2) const
{
    return std::hypot(p2.x - p1.x, p2.y - p1.y);
}

// Function to check if a point is inside the track boundary
bool Track::isInsideTrack(const Point &point) const
{
    if (trackPoints.size() < 3)
    {
        return false;
    }

    // Use ray casting algorithm to check if the point is inside the track
    int intersections = 0;
    int numPoints = trackPoints.size();
    for (int i = 0; i < numPoints; ++i)
    {
        const Point &p1 = trackPoints[i];
        const Point &p2 = trackPoints[(i + 1) % numPoints];
        if ((p1.y <= point.y && point.y < p2.y) || (p2.y <= point.y && point.y < p1.y))
        {
            double intersectionX = (point.y - p1.y) * (p2.x - p1.x) / (p2.y - p1.y) + p1.x;
            if (point.x < intersectionX)
            {
                ++intersections;
            }
        }
    }
    return (intersections % 2 != 0);
}