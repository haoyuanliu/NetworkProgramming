#ifndef MUDUO_BASE_TIMESTAMP_H
#define MUDUO_BASE_TIMESTAMP_H

#include <boost/noncopyable.hpp>
#include <stdint.h>

namespace muduo
{
    namespace detail
    {
        template<typename T>
        class AtomicIntergerT : boost::noncopyable
        {
        public:
                AtomicIntergerT() : value_(0) {}

            T get() const
            {
                return __sync_val_compare_and_swap(const_cast<volatile T*>(&value_), 0, 0);
            }

            T getAndAdd(T x)
            {
                return __sync_fetch_and_add(&value_, x);
            }

            T addAndGet(T x)
            {
                return getAndAdd(x) + x;
            }

            T incrementAndGet(T x)
            {
                return addAndGet(1);
            }

            void add(T x)
            {
                getAndAdd(x);
            }

            void increment()
            {
                incrementAndGet();
            }

            void decrement()
            {
                getAndAdd(-1);
            }

            T getAndSet(T newValue)
            {
                return __sync_lock_test_and_set(&value_, newValue);
            }
        private:
            volatile T value_;
        };
    }

typedef detail::AtomicIntergerT<int32_t> AtomicInt32;
typedef detail::AtomicIntergerT<int64_t> AtomicInt64;

}
#endif
