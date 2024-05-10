#include "../include/Car.h"

// Default constructor
Car::Car() : carPos({100, 100}), carDirection(0.0f) {}

// Parameterized constructor
Car::Car(const std::string &carName, float base, float diameter, double fuel, CarPoint pos, float direction)
    : name(carName), wheelBase(base), tireDiameter(diameter), fuelLevel(fuel), carPos(pos), carDirection(direction) {}

// Accessors
std::string Car::getName() const
{
    return this->name;
}

double Car::getWheelBase() const
{
    return this->wheelBase;
}

double Car::getTireDiameter() const
{
    return this->tireDiameter;
}

double Car::getFuelLevel() const
{
    return this->fuelLevel;
}

CarPoint Car::getPosition() const
{
    return this->carPos;
}

float Car::getDirection() const
{
    return this->carDirection;
}

// Mutators
void Car::setName(const std::string str)
{
    this->name = str;
}

void Car::setWheelBase(double num)
{
    this->wheelBase = num;
}

void Car::setTireDiameter(double num)
{
    this->tireDiameter = num;
}

void Car::setFuelLevel(double num)
{
    this->fuelLevel = num;
}

void Car::setPosition(CarPoint num)
{
    this->carPos = num;
}

void Car::setDirection(float num)
{
    this->carDirection = num;
}