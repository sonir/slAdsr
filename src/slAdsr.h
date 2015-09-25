#pragma once

#include <iostream>
#include <math.h>
#include "slChrono.h"

typedef enum { ATK, DCY, SUS, REL, FINISHED } region_e;

typedef struct adsr_t {
    
    int attack;
    int decay;
    float sustain;
    int duration;
    int release;
    
} adsr_t;

typedef struct adsr_posi_t{
    
    region_e region;
    float point;
    
} adsr_posi_t;


class slAdsr {
    
    public:
    
        slAdsr(){
            
            
        }
    
        void setup(adsr_t a);
        float update();
        void bang();
        void stop();
        void calcRatio(adsr_t *a);
        float current();
        adsr_posi_t distributer(float t);

        bool exponential = false;
    
    private:
        slChrono chrono;
        adsr_t ms;
        bool init = false;
        float attack;
        float decay;
        float duration;
        float release;
        int total_duration;
        float current;

    
};

