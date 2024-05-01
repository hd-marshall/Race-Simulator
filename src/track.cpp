#include "../include/Track.h"

// Constructor
Track::Track(const std::string &name)
    : name(name) {}

// Accessors
const std::string &Track::getTrackName() const
{
    return this->name;
}

const std::vector<Point> &Track::getTrackPoints() const
{
    return this->trackPoints;
}

const Point &Track::getSpecificTrackPoint(int num) const
{
    return this->trackPoints[num];
}

// Function to add a point to the track boundary
void Track::addTrackPoint(double x, double y)
{
    this->trackPoints.push_back({x, y});
}