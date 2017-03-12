//
// Created by clejacquet on 12/03/17.
//

#ifndef FREEPOISSON_CLIENT_OBSERVER_H
#define FREEPOISSON_CLIENT_OBSERVER_H


template<typename T>
class Observer {
public:
    virtual ~Observer() {}
    virtual void notify(T parameter) = 0;
};


#endif //FREEPOISSON_CLIENT_OBSERVER_H
