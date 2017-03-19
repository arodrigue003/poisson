//
// Created by clejacquet on 18/03/17.
//

#include "RequestConnection.h"

RequestConnection::RequestConnection(const std::string &address, unsigned short port) :
    Connection(address, port)
{

}


void RequestConnection::onReceive(const std::string &message) {
    std::unordered_map<unsigned int, Context>::iterator it = _pending_requests.find(_response_counter);
    if (it != _pending_requests.end()) {
        it->second.onResponse(message);

        _pending_request_write_lock.lock();
        _pending_requests.erase(_response_counter);
        _pending_request_write_lock.unlock();
    }
    _response_counter++;
}

void RequestConnection::collectMessages() {
    _checkNextRequest();
    Connection::collectMessages();
}

void RequestConnection::_checkNextRequest() {
    std::chrono::system_clock::time_point now = std::chrono::system_clock::now();

    if (_response_counter == _request_counter) {
        return;
    }

    Context next_context = _pending_requests.at(_response_counter);
    if (next_context.elapsedTime(now) > std::chrono::seconds(5)) {
        for (std::pair<unsigned int, Context> pair : _pending_requests) {
            Context context = pair.second;
            context.onCancel();
        }

        _pending_request_write_lock.lock();
        _pending_requests.clear();
        _pending_request_write_lock.unlock();

        _response_counter = _request_counter;
    }
}
