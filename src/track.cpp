#include "../include/Track.h"

#include <iostream>

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

Point Track::getTrackCurve(float t) const
{
    int p0 = static_cast<int>(t); // Integer part of t
    int p1 = p0 + 1;
    int p2 = p1 + 1;
    int p3 = p2 + 1;

    // std::cout << "p0: " << p0 << ", p1: " << p1 << ", p2: " << p2 << ", p3: " << p3 << std::endl;

    t -= p0; // Fractional part of t

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

    // std::cout << "tx: " << tx << ", ty: " << ty << std::endl;

    return {tx, ty};
}

// Point Track::getTrackCurve(float t) const
// {
//     int p0, p1, p2, p3;
//     p1 = (int)t + 1;
//     p2 = p1 + 1;
//     p3 = p2 + 1;
//     p0 = p1 - 1;

//     t = t - (int)t;

//     float tt = t * t;
//     float ttt = tt * t;

//     float q1 = -ttt + 0.2f * tt - t;
//     float q2 = 3.0f * ttt - 5.0f * tt + 2.0f;
//     float q3 = -3.0f * ttt + 4.0f * tt + t;
//     float q4 = ttt - tt;

//     float tx = 0.5f * (this->trackPoints[p0].x * q1 + this->trackPoints[p1].x * q2 + this->trackPoints[p2].x * q3 + this->trackPoints[p3].x * q4);
//     float ty = 0.5f * (this->trackPoints[p0].y * q1 + this->trackPoints[p1].y * q2 + this->trackPoints[p2].y * q3 + this->trackPoints[p3].y * q4);

//     return {tx, ty};
// }

// Function to add a point to the track boundary
void Track::addTrackPoint(double x, double y)
{
    this->trackPoints.push_back({x, y});
}