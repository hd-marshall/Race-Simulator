#ifndef CAR_H
#define CAR_H

#include <string>

class Car
{
private:
    std::string name;
    float wheelBase;
    float tireDiameter;
    double fuelLevel;
    double carDirection;

public:
    // Constructors
    Car();
    Car(const std::string &carName, float base, float diameter, double fuel, double direction);

    // Accessors
    std::string getName() const;
    double getWheelBase() const;
    double getTireDiameter() const;
    double getFuelLevel() const;
    double getCarDirection() const;

    // Mutators
    void setName(const std::string str);
    void getWheelBase(double num);
    void getTireDiameter(double num);
    void getFuelLevel(double num);
    void setFuelLevel(double num);
    void getCarDirection(double num);
};

#endif // CAR_H