#include "strategy.h"

namespace corsim
{
    int RegularMovement::move(int dt, std::vector<Subject> &subjects, int week)
    {
        int numberInfected = 0;
        for(Subject& s : subjects)
        {
            s.set_x(s.x() + s.dx() * dt);
            s.set_y(s.y() + s.dy() * dt);
            if(s.infected())
            {
                numberInfected++;
            }
        }
        return numberInfected;
    }

    int LockdownMovement::move(int dt, std::vector<Subject> &subjects, int week)
    {
        if (run == NULL)
        {
            // Calculate 75% of the subjects that will be stopped
            int num = subjects.size() * 0.75;

            // Stop 75% of the subjects
            for (int i = 0; i < num; i++)
            {
                subjects.at(i).setLocked(true);
            }

            run = true;
        }

        int numberInfected = 0;

        for (Subject& s : subjects)
        {   
            // If the subject is not in the stop group, move them
            if (s.getLocked() != true)
            {
                s.set_x(s.x() + s.dx() * dt);
                s.set_y(s.y() + s.dy() * dt);
            }
            if(s.infected())
            {
                numberInfected++;
            }
        }

        return numberInfected;
    }

    int SlowdownMovement::move(int dt, std::vector<Subject> &subjects, int week)
    {   
        // Calculate half of the subjects
        int halfSub = subjects.size() * 0.5;
        // Calculate 75% of the subjects that will be slowed
        int slowSub = subjects.size() * 0.75;
        // Calculate the speed on which the slow subjects should move. Lowest is 1/3 of the normal speed, any lower will result in subjects standing still
        int dtSlow = dt * 1 / 3;

        int numberInfected = 0;

        for (int i = 0; i < slowSub; i++)
        {
            subjects.at(i).setSlow(true);
        }

        for(Subject& s : subjects)
            {
                if(s.infected())
                {
                    numberInfected++;
                }
                // If less than half of the subjects are infected, move at normal speed
                if (numberInfected < halfSub)
                {
                    s.set_x(s.x() + s.dx() * dt);
                    s.set_y(s.y() + s.dy() * dt);

                }
                // If less than half of the subjects are infected, change speeds
                else if (numberInfected > halfSub)
                {
                    // If the subjects are in the 75% group that will be slowed, get slowed by 2/3rd
                    if (s.slow() == true)
                    {
                        s.set_x(s.x() + s.dx() * dtSlow);
                        s.set_y(s.y() + s.dy() * dtSlow);
                    }
                    // If the subjects are in the 25% group that move at normal speed, nothing happens to them
                    else 
                    {
                        s.set_x(s.x() + s.dx() * dt);
                        s.set_y(s.y() + s.dy() * dt);
                    }
                }
            }
        return numberInfected;
    }

} 