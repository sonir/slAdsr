#include "slAdsr.h"
float limit(float f); //limitter function prototype

using namespace std;

void slAdsr::setup(adsr_t a){

    ms = a;
    calcRatio(&a);
    
    
    init = true;
    
}

float slAdsr::update(){
    
    if(!init)return 0.0f; //Ignore involing before init.
    
    float now = chrono.elapsed_ms()/(double)total_duration;
    adsr_posi_t position = distributer(now);
    float point, fval;
    
    //Exponential
    if(exponential==true){
        
        if(position.region==ATK){
            point = position.point*position.point;
        }else{
            
            //Exponential curve is modified when sustain and release.
            point = sin(position.point*(M_PI/2.0f));
            
            
        }
    }else{
        point = position.point;
    }
    
    switch(position.region){
            
        case ATK:
            return point;
            break;

        case DCY:
            // ((1-S) * (1-Dratio)) + S
            fval = ((1.0f-duration)*(1-point))+ms.sustain;
            return limit(fval);
            break;

        case SUS:
            return ms.sustain;
            break;

        case REL:
            // S * (1-release)
            fval =  ms.sustain * (1-point);
            return limit(fval);
            break;
            
        case FINISHED:
            return 0.0;
            break;
            
        default:
            break;
            
    }
    
}

void slAdsr::bang(){
    
    if(!init){
        cout << "[bang] adsr was not init" << endl;
        return;
    }
    
    chrono.setup();
    
}

void slAdsr::stop(){
    
    
}

void slAdsr::calcRatio(adsr_t *a){
    
    total_duration = a->attack + a->decay + a->duration + a->release;
    attack = (float)a->attack/total_duration;
    decay = (float)a->decay/total_duration;
    duration = (float)a->duration/total_duration;
    release = (float)a->release/total_duration;
    
}


adsr_posi_t slAdsr::distributer(float t){

        adsr_posi_t ap;
    
        if(t<attack){ //ATK
            ap.region = ATK;
            ap.point = t/attack;
            
        }else if(t<(attack+decay)){ //DCY

            ap.region = DCY;
            ap.point = (t-(attack))/decay;
            
        }else if(t<(attack+decay+duration)){ //SUS

            ap.region = SUS;
            ap.point = (t-(attack+decay))/duration;

        }else if(t<(attack+decay+duration+release)){ //REL

            ap.region = REL;
            ap.point = (t-(attack+decay+duration))/release;
            
        }else if(t>(attack+decay+duration+release)){
            
            ap.region = FINISHED;
            ap.point = t - (attack+decay+duration+release) + 1.0;
            
        }
    
        return ap;
    
}


float limit(float f){
    
    if(f>1.0f) return 1.0f;
    else if(f<0.0f)return 0.0f;
    else return f;
    
}