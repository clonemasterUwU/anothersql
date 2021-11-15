#ifndef ANOTHERSQL_RW_LATCH_BASE_H
#define ANOTHERSQL_RW_LATCH_BASE_H

/**
 * This class is designed so the inherited can be used in std::shared_lock and std::unique_lock
 */
class rw_latch_base {
public:
    rw_latch_base() = default;

    ~rw_latch_base() = default;

    rw_latch_base(rw_latch_base const &o) = delete;

    void operator=(rw_latch_base const &o) = delete;

    virtual void lock_shared() = 0;

    virtual void lock() = 0;

    virtual void unlock_shared() = 0;

    virtual void unlock() = 0;
};


#endif //ANOTHERSQL_RW_LATCH_BASE_H
