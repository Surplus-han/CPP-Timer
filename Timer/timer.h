//
// Created by Smile on 2023/12/30.
//
#pragma onceonce
#ifndef TIMER_TIMER_H
#define TIMER_TIMER_H
#include <thread>
#include <atomic>
#include <functional>


namespace hanjr{
    namespace core{
        class Timer{
        public:
            Timer();
            Timer(int repeate);
            ~Timer();

            template<typename F,typename... Args>
            void start(int millsecond,F && func,Args&&... args);
            //关闭定时
            void stop();
        private:
            std::thread m_thread;
            std::atomic<bool> m_active;
            std::function<void()> m_func;
            int m_period;
            int m_repeate;//触发的次数，-1表示无限周期
        };
        // 启动定时任务

        /*
         * 表示一个函数模板的声明或定义，允许你使用模板参数 F 和模板包扩展 Args... 来创建一个通用的函数
            在这里，F 是一个模板参数，代表可调用对象（函数、函数指针、成员函数指针、函数对象等），
         而 Args... 是一个模板包扩展，允许你传递零个或多个参数给函数模板。
         * */
        template<typename F,typename... Args>
        void Timer::start(int millsecond,F && func,Args&&... args){
            if(m_active.load()){
                return;
            }
            m_period  = millsecond;
            m_func = std::bind(std::forward<F>(func),std::forward<Args>(args)...);
            m_active.store(true);
            m_thread = std::thread([&](){
                if(m_repeate < 0){
                    while(m_active.load()){
                        std::this_thread::sleep_for(std::chrono::milliseconds (m_period));
                        if(!m_active.load()){
                            return;
                        }
                        m_func();
                    }
                }else{
                    while(m_repeate > 0 ){
                        if(!m_active.load()){
                            return;
                        }
                        std::this_thread::sleep_for(std::chrono::microseconds(m_period));
                        if(!m_active.load()){
                            return;
                        }
                        m_func();
                        m_repeate--;
                    }
                }

            });
            m_thread.detach();
        }
    }
}
#endif //TIMER_TIMER_H
