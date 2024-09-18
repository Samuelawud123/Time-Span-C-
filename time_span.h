#ifndef TIME_SPAN_H
#define TIME_SPAN_H

#include <iostream>

/**
 * Class representing a span of time in hours, minutes, and seconds.
 * Author: Samuel Awud
 * The class provides functionality to set time, modify it and perform
 * arithmetic operations with other TimeSpan instances.
 */

class TimeSpan {
private:
    int _hours;
    int _minutes;
    int _seconds;

    void normalize(); // Normalizes time to a standard format.
    int totalSeconds() const; // Returns the total seconds for comparison.
public:
    // Constructors
    TimeSpan(double seconds = 0);
    TimeSpan(double minutes, double seconds);
    TimeSpan(double hours, double minutes, double seconds);

    // Getters
    int hours() const;
    int minutes() const;
    int seconds() const;

    // Setter
    void setTime(int hours, int minutes, int seconds);

    // Operator overloads
    TimeSpan operator+(const TimeSpan& other) const;
    TimeSpan operator-(const TimeSpan& other) const;
    TimeSpan operator-() const;
    TimeSpan& operator+=(const TimeSpan& other);
    TimeSpan& operator-=(const TimeSpan& other);
    bool operator<(const TimeSpan& other) const;
    bool operator<=(const TimeSpan& other) const;
    bool operator>(const TimeSpan& other) const;
    bool operator>=(const TimeSpan& other) const;

    bool operator==(const TimeSpan& other) const;
    bool operator!=(const TimeSpan& other) const;

    friend std::ostream& operator<<(std::ostream& os, const TimeSpan& obj);
    friend std::istream& operator>>(std::istream& is, TimeSpan& obj);
};

#endif // TIME_SPAN_H
