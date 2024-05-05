#include "../include/Car.h"

// Default constructor
Car::Car() : carDirection(0.0) {}

// Parameterized constructor
Car::Car(const std::string &carName, float base, float diameter, double fuel, double direction)
    : name(carName), wheelBase(base), tireDiameter(diameter), fuelLevel(fuel), carDirection(direction) {}

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

double Car::getCarDirection() const
{
    return this->carDirection;
}

// Mutators
void Car::setName(const std::string str)
{
    this->name = str;
}

void Car::getWheelBase(double num)
{
    this->wheelBase = num;
}

void Car::getTireDiameter(double num)
{
    this->tireDiameter = num;
}

void Car::getFuelLevel(double num)
{
    this->fuelLevel = num;
}

void Car::setFuelLevel(double num)
{
    this->fuelLevel = num;
}

void Car::getCarDirection(double num)
{
    this->carDirection = num;
}