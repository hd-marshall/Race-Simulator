#ifndef TRACK_H
#define TRACK_H

#include "../include/Car.h"

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
    Car car;

public:
    // Constructor
    Track(const std::string &name);
    void addTrackPoint(double x, double y);

    // Accessors
    const std::string &getTrackName() const;
    const Point &getSpecificTrackPoint(int num) const;
    const std::vector<Point> &getTrackPoints() const;
    Car &getCar();

    Point getTrackCurvePoint(float t, bool looped) const;
    Point getTrackCurveGradient(float t, bool looped = false) const;

    // Setters
    void setCar(Car &car);
    void setTrackPointValues(std::string dir, int num);
};

#endif // TRACK_H