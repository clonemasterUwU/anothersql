//
// Created by deal_with on 11/11/2021.
//

#ifndef ANOTHERSQL_PINLOCK_H
#define ANOTHERSQL_PINLOCK_H

template<class T>
class PinLock {
    T& mutex;
public:
    PinLock(T& mutex):mutex(mutex){
        mutex.pin();
    }
    ~PinLock(){
        mutex.unpin();
    }
    PinLock(PinLock&)=delete;
    PinLock& operator=(PinLock&)=delete;
};


#endif //ANOTHERSQL_PINLOCK_H
