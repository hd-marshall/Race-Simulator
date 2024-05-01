#ifndef TRACK_H
#define TRACK_H

#include <vector>
#include <cmath>
#include <string>

struct Point
{
    double x;
    double y;
};

class Track
{
private:
    std::string name;
    std::vector<Point> trackPoints; // Points defining the track boundary
    int selectedTrackPoint = 0;

public:
    // Constructor
    Track(const std::string &name);

    // Accessors
    const std::string& getTrackName() const;

    const Point& getSpecificTrackPoint(int num) const;

    const std::vector<Point>& getTrackPoints() const;

    // Setters
    void addTrackPoint(double x, double y);
};

#endif // TRACK_H