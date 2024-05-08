#include "../include/Track.h"

// Constructor
Track::Track(const std::string &name)
{
    this->name = name;
    this->car = Car();
}

void Track::addTrackPoint(double x, double y)
{
    this->trackPoints.push_back({x, y});
}

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

Car &Track::getCar()
{
    return this->car;
}

Point Track::getTrackCurvePoint(float t, bool looped = false) const
{
    int p0, p1, p2, p3;

    if (!looped)
    {
        p1 = (int)t + 1;
        p2 = p1 + 1;
        p3 = p2 + 1;
        p0 = p1 - 1;
    }
    else
    {
        p1 = (int)t;
        p2 = (p1 + 1) % this->trackPoints.size();
        p3 = (p2 + 1) % this->trackPoints.size();
        p0 = p1 >= 1 ? p1 - 1 : this->trackPoints.size() - 1;
    }

    t = t - (int)t;

    // Ensure p1, p2, and p3 are within bounds
    p1 = std::min(std::max(p1, 0), static_cast<int>(trackPoints.size()) - 1);
    p2 = std::min(std::max(p2, 0), static_cast<int>(trackPoints.size()) - 1);
    p3 = std::min(std::max(p3, 0), static_cast<int>(trackPoints.size()) - 1);

    // Calculate the curve using Catmull-Rom interpolation
    float tt = t * t;
    float ttt = tt * t;

    float q1 = -ttt + 2.0f * tt - t;
    float q2 = 3.0f * ttt - 5.0f * tt + 2.0f;
    float q3 = -3.0f * ttt + 4.0f * tt + t;
    float q4 = ttt - tt;

    float tx = 0.5f * (trackPoints[p0].x * q1 + trackPoints[p1].x * q2 + trackPoints[p2].x * q3 + trackPoints[p3].x * q4);
    float ty = 0.5f * (trackPoints[p0].y * q1 + trackPoints[p1].y * q2 + trackPoints[p2].y * q3 + trackPoints[p3].y * q4);

    return {tx, ty};
}

Point Track::getTrackCurveGradient(float t, bool looped) const
{
    int p0, p1, p2, p3;

    if (!looped)
    {
        p1 = (int)t + 1;
        p2 = p1 + 1;
        p3 = p2 + 1;
        p0 = p1 - 1;
    }
    else
    {
        p1 = (int)t;
        p2 = (p1 + 1) % this->trackPoints.size();
        p3 = (p2 + 1) % this->trackPoints.size();
        p0 = p1 >= 1 ? p1 - 1 : this->trackPoints.size() - 1;
    }

    t = t - (int)t;

    // Ensure p1, p2, and p3 are within bounds
    p1 = std::min(std::max(p1, 0), static_cast<int>(trackPoints.size()) - 1);
    p2 = std::min(std::max(p2, 0), static_cast<int>(trackPoints.size()) - 1);
    p3 = std::min(std::max(p3, 0), static_cast<int>(trackPoints.size()) - 1);

    // Calculate the curve using Catmull-Rom interpolation
    float tt = t * t;

    float q1 = -3.0f * tt + 4 * t - 1.0f;
    float q2 = 9.0f * tt - 10.0f * t;
    float q3 = -9.0f * tt + 8.0f * t + 1.0f;
    float q4 = 3.0f * tt - 2.0f * t;

    float tx = 0.5f * (trackPoints[p0].x * q1 + trackPoints[p1].x * q2 + trackPoints[p2].x * q3 + trackPoints[p3].x * q4);
    float ty = 0.5f * (trackPoints[p0].y * q1 + trackPoints[p1].y * q2 + trackPoints[p2].y * q3 + trackPoints[p3].y * q4);

    return {tx, ty};
}

void Track::setCar(Car &car)
{
    this->car = car;
}

void Track::setTrackPointValues(std::string dir, int num)
{
    if (dir == "w")
    {
        this->trackPoints[num].y += -10;
    }
    else if (dir == "s")
    {
        this->trackPoints[num].y += 10;
    }
    else if (dir == "a")
    {
        this->trackPoints[num].x += -10;
    }
    else
    {
        this->trackPoints[num].x += 10;
    }
}