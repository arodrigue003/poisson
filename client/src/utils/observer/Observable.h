//
// Created by clejacquet on 12/03/17.
//

#ifndef FREEPOISSON_CLIENT_OBSERVABLE_H
#define FREEPOISSON_CLIENT_OBSERVABLE_H

#include <list>
#include <memory>
#include <algorithm>

#include "Observer.h"

template<typename T>
class Observable {
private:
    std::list<std::shared_ptr<Observer<T>>> _observers;
public:
    virtual ~Observable() {}

    void addObserver(std::shared_ptr<Observer<T>> observer);
    void removeObserver(std::shared_ptr<Observer<T>> observer);

protected:
    void notifyAll(T parameter);
};


template<typename T>
void Observable<T>::addObserver(std::shared_ptr<Observer<T>> observer) {
    _observers.push_back(observer);
}

template<typename T>
void Observable<T>::notifyAll(T parameter) {
    for (std::shared_ptr<Observer<T>>& observer : _observers) {
        observer->notify(parameter);
    }
}

template<typename T>
void Observable<T>::removeObserver(std::shared_ptr<Observer<T>> observer) {
    _observers.remove(observer);
}


#endif //FREEPOISSON_CLIENT_OBSERVABLE_H
