#ifndef TRACK_H
#define TRACK_H

#include <vector>
#include <cmath>

struct Point
{
    double x;
    double y;
};

class Track
{
private:
    std::vector<Point> trackPoints; // Points defining the track boundary
    double trackWidth;              // Width of the track

public:
    // Constructor
    Track(double width);

    // Accessors
    const std::vector<Point>& getTrackPoints() const;


    // Function to add a point to the track boundary
    void addTrackPoint(double x, double y);

    // Function to calculate the distance between two points
    double distanceBetweenPoints(const Point &p1, const Point &p2) const;

    // Function to check if a point is inside the track boundary
    bool isInsideTrack(const Point &point) const;

    // Other functions to manipulate and query the track characteristics can be added here
};

#endif // TRACK_H