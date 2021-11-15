//
// Created by deal_with on 19/10/2021.
//

#include "sync/rw_latch_mutex.h"

rw_latch_mutex::rw_latch_mutex() : _reader_count(0), _writer_count(0), _writer_wait(0) {}

void rw_latch_mutex::lock_shared() {
    std::unique_lock<std::mutex> latch(_mutex);
    while (_writer_count > 0 || _writer_wait > 0) {
        _reader.wait(latch);
    }
    _reader_count++;
}

void rw_latch_mutex::lock() {
    std::unique_lock<std::mutex> latch(_mutex);
    _writer_wait++;
    while (_reader_count > 0 || _writer_count > 0) {
        _writer.wait(latch);
    }
    _writer_wait--, _writer_count++;
}

void rw_latch_mutex::unlock_shared() {
    std::unique_lock<std::mutex> latch(_mutex);
    _reader_count--;
    if (_reader_count == 0 && _writer_wait > 0) {
        _writer.notify_one();
    }
}

void rw_latch_mutex::unlock() {
    std::unique_lock<std::mutex> latch(_mutex);
    _writer_count--;
    if (_writer_wait > 0) {
        _writer.notify_one();
    } else {
        _reader.notify_one();
    }
}