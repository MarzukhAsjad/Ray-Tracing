#ifndef INTERVAL_H
#define INTERVAL_H

class interval {
    public:
        double min, max;

        // Default interval is empty
        interval() : min(+infinity), max(-infinity) {} 

        // Interval between min and max value
        interval(double _min, double _max) : min(_min), max(_max) {}

        // Check if x is contained within the interval
        bool contains(double x) const {
            return min <= x && x <= max;
        }

        // Check if x is surrounded by the interval (exluding the extreme values)
        bool surrounds(double x) const{
            return min < x && x < max;
        }

        static const interval empty, universe;
};

const static interval empty (+infinity, -infinity);
const static interval universe (-infinity, +infinity);

#endif