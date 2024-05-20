/**
  ******************************************************************************
  * @file           : singleton.h
  * @author         : toastoffee
  * @brief          : None
  * @attention      : None
  * @date           : 2024/5/13
  ******************************************************************************
  */



#ifndef TOASTED_RENDERER_SINGLETON_H
#define TOASTED_RENDERER_SINGLETON_H

template<class T>
class Singleton
{
private:

public:
    Singleton(Singleton &&)                 = delete;
    Singleton(const Singleton &)            = delete;
    void operator = (const Singleton &)     = delete;
    T *operator &()                         = delete;

    static T *Instance(){
        static T *instance;
        if(instance == nullptr){
            instance = new T();
        }
        return instance;
    }

protected:
    Singleton()                            = default;
    virtual ~Singleton()                   = default;
};


#endif //TOASTED_RENDERER_SINGLETON_H
