#ifndef CAR_H
#define CAR_H

#include <string>

class Car
{
private:
    std::string name;
    double fuelLevel;

public:
    // Constructors
    Car();
    Car(const std::string &name, double fuelLevel);

    // Accessors
    std::string getName() const;
    double getFuelLevel() const;

    // Mutators
    void setName(const std::string &make);
    void setFuelLevel(double fuelLevel);
};

#endif // CAR_H