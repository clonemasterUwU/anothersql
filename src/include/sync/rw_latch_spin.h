#ifndef ANOTHERSQL_RW_LATCH_SPIN_H
#define ANOTHERSQL_RW_LATCH_SPIN_H

#include <atomic>
#include "sync/rw_latch_base.h"

class rw_latch_spin : public rw_latch_base {
private:
    std::atomic_bool write;
    std::atomic_int reader_count;
public:
    rw_latch_spin();

    ~rw_latch_spin() = default;

    void lock() override;

    void unlock() override;

    void lock_shared() override;

    void unlock_shared() override;
};


#endif //ANOTHERSQL_RW_LATCH_SPIN_H
