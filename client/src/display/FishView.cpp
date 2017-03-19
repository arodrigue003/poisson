#include "FishView.hpp"

FishView::FishView() : _movementQueue(), _currentPosBackup(0.f,0.f), _targetPosBackup(0.f,0.f),
                     _currentPos(0,0), _targetPos(0,0), _remainingTime(0.f) {

}

void FishView::addMove(unsigned x, unsigned y, unsigned time) {
    _movementQueue.enqueue(Move(x, y, time));
}

