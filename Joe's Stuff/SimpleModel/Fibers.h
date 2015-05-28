#ifndef FIBERS_H
#define FIBERS_H


//Properties of fiber elements
class Fibers{

    public:
        double stress, time;       // Stress and failure time of the fiber
        bool alive;                // True when the fiber is intact and holds stress.  False after if breaks.

};

#endif
