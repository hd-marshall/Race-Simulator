#ifndef CAR_H
#define CAR_H

#include <string>

struct CarPoint
{
    double x;
    double y;
};

class Car
{
private:
    std::string name;
    float wheelBase;
    float tireDiameter;
    double fuelLevel;
    CarPoint carPos;
    float carDirection;

public:
    // Constructors
    Car();
    Car(const std::string &carName, float base, float diameter, double fuel, CarPoint pos, float direction);

    // Accessors
    std::string getName() const;
    double getWheelBase() const;
    double getTireDiameter() const;
    double getFuelLevel() const;
    CarPoint getCarPos() const;
    float getCarDirection() const;

    // Mutators
    void setName(const std::string str);
    void setWheelBase(double num);
    void setTireDiameter(double num);
    void setFuelLevel(double num);
    void setCarPos(CarPoint num);
    void setCarDirection(float num);
};

#endif // CAR_H