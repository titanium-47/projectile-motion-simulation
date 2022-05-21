#include <emscripten\bind.h>
#include "headers\Simulation.h"
#include "headers\DragProjectileMotion.h"

class Simulator {
    private:
        std::vector<double> xPositions;
        std::vector<double> yPositions;
        double _time;
        int _resolution;
        double coordinates[2];
        double maxHieght;

    public:
        Simulator(double time, int resolution, double velocity, double angle, double area, double dragCoefficient, double mass) {
            _time = time;
            _resolution = resolution;
            DragProjectileMotion* simulation = new DragProjectileMotion(time, resolution, velocity, angle, area, dragCoefficient, mass, &xPositions, &yPositions);
            simulation->run();
            maxHieght = simulation->maxY;
        }

        void getCurrentPosition(int frame) {
            double index = _resolution/60.0*frame;
            double wieghts[2] = {1-(index-(int)index), 1-((int)index+1-index)};
            coordinates[0] = xPositions[(int)index]*wieghts[0] + xPositions[(int)index + 1]*wieghts[1];
            coordinates[1] = yPositions[(int)index]*wieghts[0] + yPositions[(int)index + 1]*wieghts[1];
        }

        double getX(int frame) {
            getCurrentPosition(frame);
            return coordinates[0];
        }

        double getY(int frame) {
            return coordinates[1];
        }

        double getMaxHieght() {
            return maxHieght;
        }

        double getMaxLength() {
            return xPositions[xPositions.size()-1];
        }

        double getXs(int index) {
            return xPositions[index];
        }

};

using namespace emscripten;
EMSCRIPTEN_BINDINGS(projectile_motion) {
    class_<Simulator>("Simulator")
        .constructor<double, int, double, double, double, double, double>()
        .function("getX", &Simulator::getX)
        .function("getY", &Simulator::getY)
        .function("getMaxHieght", &Simulator::getMaxHieght)
        .function("getMaxLength", &Simulator::getMaxLength)
        .function("getXs", &Simulator::getXs);
}

