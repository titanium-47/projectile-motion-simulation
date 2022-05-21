#include "Simulation.h"
#include <math.h>
#include <string>
#include <vector>

#ifndef DRAG_PROJECTILE_MOTION
#define DRAG_PROJECTILE_MOTION
#define PI 3.1415

const double AIR_DENSITY = 1.225;

class DragProjectileMotion : public Simulation {
    private:
        double xVelocity;
        double yVelocity;
        double xPosition;
        double yPosition;
        double area;
        double dragCoefficient;
        double mass;
        std::vector<double> *xPositions;
        std::vector<double> *yPositions;
    public:
        double maxY;
        DragProjectileMotion(double time, int resolution, double velocity, double angle, double area, double dragCoefficient, double mass, std::vector<double> *xPositions, std::vector<double> *yPositions);
        void periodic();
        bool finished();
        void end();
};

DragProjectileMotion::DragProjectileMotion(double time, int resolution, double velocity, double angle, double area, double dragCoefficient, double mass, std::vector<double> *xPositions, std::vector<double> *yPositions) : Simulation(time, resolution){
    this->xPositions = xPositions;
    this->yPositions = yPositions;
    this->area = area;
    this->dragCoefficient = dragCoefficient;
    this->mass = mass;
    this->xVelocity = velocity * cos(angle/180*PI);
    this->yVelocity = velocity * sin(angle/180*PI);
    this->xPosition = 0;
    this->yPosition = 0;
    (*xPositions).push_back(xPosition);
    (*yPositions).push_back(yPosition);
}

void DragProjectileMotion::periodic() {
    xPosition += xVelocity/resolution;
    yPosition += yVelocity/resolution;
    if(yPosition > maxY) {
        maxY = yPosition;
    } 
    yVelocity -= 9.8/resolution;
    double xAirResistance = 0.5*AIR_DENSITY*xVelocity*xVelocity*dragCoefficient*area;
    double yAirResistance = 0.5*AIR_DENSITY*yVelocity*yVelocity*dragCoefficient*area;
    xVelocity = (abs(xVelocity)/xVelocity)*(abs(xVelocity)-xAirResistance/mass/resolution);
    yVelocity = (abs(yVelocity)/yVelocity)*(abs(yVelocity)-yAirResistance/mass/resolution);
    (*xPositions).push_back(xPosition);
    (*yPositions).push_back(yPosition);
}

bool DragProjectileMotion::finished() {
    return false;
}

void DragProjectileMotion::end() {
    return;
}
#endif