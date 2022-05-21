#ifndef SIMULATION
#define SIMULATION

class Simulation {
    private:
        int runCount;
    protected:
        double time;    //length of simulation in seconds
        int resolution; //number of times per second to calculate
        double currentTime;
        //char* fileName;
    public:
        Simulation(double time, int resolution);
        ~Simulation();
    public:
        virtual void periodic() = 0;
        void run();
        virtual bool finished() = 0;
};

Simulation::Simulation(double time, int resolution){
    this->time = time;
    this->resolution = resolution;
    runCount = 0;
}

void Simulation::run() {
    //freopen(fileName, "w", stdout);
    do {
        periodic();
        currentTime += 1.0/resolution;
    }while(!finished() && currentTime<time);
}

Simulation::~Simulation() {
    //free(fileName);
}

#endif