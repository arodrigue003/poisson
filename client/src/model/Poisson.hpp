#ifndef FREEPOISSON_CLIENT_POISSON_HPP
#define FREEPOISSON_CLIENT_POISSON_HPP

#include <utils/concurrency/blockingconcurrentqueue.h>

using namespace moodycamel;

template<typename T>
class Dot {
private:
    T _x, _y;

public:
    Dot() : _x(0), _y(0) {}

    Dot(T x, T y) : _x(x), _y(y) {}

    T x() const { return _x; }

    T y() const { return _y; }

    void x(T x) { _x = x; }

    void y(T y) { _y = y; }
};

class Move {
    Dot<unsigned> _target; //% according to the newtwork exchange parameters
    unsigned _time;    //seconds

public:
    Move(unsigned x, unsigned y, unsigned time) : _target(x, y), _time(time) {}
};

class Poisson {
private:
    BlockingConcurrentQueue<Move> _movementQueue;

    //%
    Dot<float> _currentPosBackup;
    Dot<float> _targetPosBackup;

    //pixel
    Dot<unsigned> _currentPos;
    Dot<unsigned> _targetPos;

    float _remainingTime;

public:
    Poisson();

    void addMove(unsigned x, unsigned y, unsigned time);
};


#endif //FREEPOISSON_CLIENT_POISSON_HPP
