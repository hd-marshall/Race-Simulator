#include "../include/Car.h"
#include <iostream>

// Default constructor
Car::Car() : name(""), fuelLevel(0.0) {}

// Parameterized constructor
Car::Car(const std::string &name, double fuelLevel)
    : name(name), fuelLevel(fuelLevel) {}

// Accessors
std::string Car::getName() const
{
    return name;
}

double Car::getFuelLevel() const
{
    return fuelLevel;
}

// Mutators
void Car::setName(const std::string &name)
{
    this->name = name;
}

void Car::setFuelLevel(double fuelLevel)
{
    this->fuelLevel = fuelLevel;
}

// Functions
