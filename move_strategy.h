#pragma once

#include <vector>
#include "simulation.h"

namespace corsim{

    class MoveStrategy{

        public:
        virtual int move(int dt, std::vector<corsim::Subject> &subjects, int week) = 0;
    };
}