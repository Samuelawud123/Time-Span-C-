#include "time_span.h"
#include <cmath>

// Constructs a TimeSpan from hours, minutes, and seconds.
TimeSpan::TimeSpan(double hours, double minutes, double seconds) {
    setTime(static_cast<int>(round(hours)), static_cast<int>(round(minutes)), static_cast<int>(round(seconds)));
    normalize();
}

// Constructs a TimeSpan from minutes and seconds, assuming 0 hours.
TimeSpan::TimeSpan(double minutes, double seconds)
    : TimeSpan(0, minutes, seconds) {}

// Constructs a TimeSpan from seconds only, assuming 0 minutes and 0 hours.
TimeSpan::TimeSpan(double seconds)
    : TimeSpan(0, 0, seconds) {}


// Returns the number of hours in the TimeSpan.
int TimeSpan::hours() const {
    return _hours;
}
// Returns the number of minutes in the TimeSpan.
int TimeSpan::minutes() const {
    return _minutes;
}
// Returns the number of seconds in the TimeSpan.
int TimeSpan::seconds() const {
    return _seconds;
}

// Sets the time, ensuring that all fields are normalized via normalize().
void TimeSpan::setTime(int h, int m, int s) {
    _hours = h;
    _minutes = m;
    _seconds = s;
    normalize();
}

// Adds two TimeSpan objects.
TimeSpan TimeSpan::operator+(const TimeSpan& other) const {
    return TimeSpan(_hours + other._hours, _minutes + other._minutes, _seconds + other._seconds);
}

// Subtracts one TimeSpan object from another.
TimeSpan TimeSpan::operator-(const TimeSpan& other) const {
    return TimeSpan(_hours - other._hours, _minutes - other._minutes, _seconds - other._seconds);
}

// Returns a TimeSpan object that is the negation of the current object.
TimeSpan TimeSpan::operator-() const {
    return TimeSpan(-_hours, -_minutes, -_seconds);
}


// Returns the total number of seconds represented by this TimeSpan.
int TimeSpan::totalSeconds() const {
    return _hours * 3600 + _minutes * 60 + _seconds;
}

// Comparison operators based on total seconds.
bool TimeSpan::operator<(const TimeSpan& other) const {
    return totalSeconds() < other.totalSeconds();
}

bool TimeSpan::operator<=(const TimeSpan& other) const {
    return totalSeconds() <= other.totalSeconds();
}

bool TimeSpan::operator>(const TimeSpan& other) const {
    return totalSeconds() > other.totalSeconds();
}

bool TimeSpan::operator>=(const TimeSpan& other) const {
    return totalSeconds() >= other.totalSeconds();
}

// Updates this TimeSpan by adding another.
TimeSpan& TimeSpan::operator+=(const TimeSpan& other) {
    setTime(_hours + other._hours, _minutes + other._minutes, _seconds + other._seconds);
    return *this;
}

// Updates this TimeSpan by subtracting another.
TimeSpan& TimeSpan::operator-=(const TimeSpan& other) {
    setTime(_hours - other._hours, _minutes - other._minutes, _seconds - other._seconds);
    return *this;
}

// Equality check based on hours, minutes, and seconds.
bool TimeSpan::operator==(const TimeSpan& other) const {
    return (_hours == other._hours && _minutes == other._minutes && _seconds == other._seconds);
}

// Inequality check based on the equality operator.
bool TimeSpan::operator!=(const TimeSpan& other) const {
    return !(*this == other);
}


// Outputs the TimeSpan in a human-readable format.
std::ostream& operator<<(std::ostream& os, const TimeSpan& obj) {
    os << "Hours: " << obj.hours() << ", Minutes: " << obj.minutes() << ", Seconds: " << obj.seconds();
    return os;
}
// Reads TimeSpan values from an input stream.
std::istream& operator>>(std::istream& is, TimeSpan& obj) {
    int hours, minutes, seconds;
    is >> hours >> minutes >> seconds;
    obj.setTime(hours, minutes, seconds);
    obj.normalize();
    return is;
}

// Normalizes time to a standard format
void TimeSpan::normalize() {
    // Convert hours and minutes to seconds
    int totalSeconds = _hours * 3600 + _minutes * 60 + _seconds;

    // Normalize seconds
    _seconds = totalSeconds % 60;
    totalSeconds /= 60;

    // Normalize minutes
    _minutes = totalSeconds % 60;
    totalSeconds /= 60;

    // Normalize hours
    _hours = totalSeconds;
}




