//
// Created by deal_with on 25/10/2021.
//
#include <thread>

#include "sync/rw_latch_spin.h"

rw_latch_spin::rw_latch_spin() : reader_count(0), write(false) {

}

void rw_latch_spin::lock() {
    while (write.exchange(true)) {
        std::this_thread::yield();
    }
    while (reader_count != 0) {
        std::this_thread::yield();
    }
}

void rw_latch_spin::unlock() {
    write.store(false);
}

void rw_latch_spin::lock_shared() {
    while(true){
        while(write.load()){
            std::this_thread::yield();
        }
        reader_count.fetch_add(1);
        if(write.load()){
            reader_count.fetch_sub(1);
        } else {
            return;
        }
    }
}

void rw_latch_spin::unlock_shared() {
    reader_count.fetch_sub(1);
}