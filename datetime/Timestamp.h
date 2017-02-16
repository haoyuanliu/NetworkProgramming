#ifndef MUDUO_BASE_TIMESTAMP_H
#define MUDUO_BASE_TIMESTAMP_H

#include "copyable.h"

#include <stdint.h>
#include <string>

namespace muduo
{
    class Timestamp : public muduo::copyable
    {
        public:
            Timestamp();
            explicit Timestamp(int64_t microSecondsSinceEpoch);

            void swap(Timestamp& that)
            {
                std::swap(microSecondsSinceEpoch_, that.microSecondsSinceEpoch_);
            }

            std::string toString() const;
            std::string toFormattedString() const;

            int64_t microSecondsSinceEpoch() const { return microSecondsSinceEpoch_; }

            static Timestamp now();

            static Timestamp invalid();
            static const int kMicroSecondsPerSecond = 1000 * 1000;

        private:
        int64_t microSecondsSinceEpoch_;
    }
    };

    inline bool operator<(Timestamp lhs, Timestamp rhs)
    {
        return lhs.microSecondsSinceEpoch() < rhs.microSecondsSinceEpoch();
    }

    inline bool operator==(Timestamp lhs, Timestamp rhs)
    {
        return lhs.microSecondsSinceEpoch() == rhs.microSecondsSinceEpoch();
    }

    inline double timeDifference(Timestamp high, Timestamp low)
    {
        int64_t diff = high.microSecondsSinceEpoch() - low.microSecondsSinceEpoch();
        return static_cast<double>(diff) / Timestamp::kMicroSecondsPerSecond;
    }

    inline Timestamp addTime(Timestamp timestamp, double seconds)
    {
        int64_t delta = static_cast<int64_t>(seconds * TImestamp::kMicroSecondsPerSecond);
        return Timestamp(timestamp.microSecondsSinceEpoch() + delta);
    }

#endif
}