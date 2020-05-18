#pragma once

#include "move_strategy.h"

namespace corsim
{
    class RegularMovement: public MoveStrategy {
        public:
        virtual int move(int dt, std::vector<corsim::Subject> &subjects, int week);
    };

    class LockdownMovement: public MoveStrategy {
        public:
        virtual int move(int dt, std::vector<corsim::Subject> &subjects, int week);
        private:
        bool run;
    };

    class SlowdownMovement: public MoveStrategy {
        public:
        int move(int dt, std::vector<Subject> &subjects, int week);
        private:
        bool run;
    };
} 