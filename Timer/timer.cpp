//
// Created by Smile on 2023/12/30.
//
#include "timer.h"
using  namespace hanjr::core;

Timer::Timer():m_active(false),m_period(0),m_repeate(-1) {
    //
}

Timer::Timer(int repeate): m_active(false),m_period(0),m_repeate(repeate){

}

Timer::~Timer(){
    stop();
}

void Timer::stop() {
    m_active.store(false);
}

