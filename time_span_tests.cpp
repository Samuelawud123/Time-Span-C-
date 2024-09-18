#include <iostream>
#include <sstream>
#include "time_span.h"
using namespace std;

/**
 * This file contains the implementation for testing the TimeSpan class. It includes 
 * functions for performing various unit tests on TimeSpan operations such as addition, 
 * subtraction, and comparison. Each test function evaluates different scenarios 
 * involving time calculations to ensure the correctness and robustness of the TimeSpan class.
 * Author: Samuel Awud
 * Sources: https://en.cppreference.com/w/cpp/io/strstream - for std::stringstream
 */


/**
 * Helper function to check the time values against expected values.
 * Outputs detailed information if the test fails.
 *
 * @param time The TimeSpan object to check.
 * @param expectedHours Expected hours.
 * @param expectedMinutes Expected minutes.
 * @param expectedSeconds Expected seconds.
 * @param testName Name of the test for output.
 * @return True if the test passes, false otherwise.
 */
bool CheckValues(TimeSpan time, int hours, int minutes, int seconds){
    if ((time.hours() != hours) || (time.minutes() != minutes) || (time.seconds()
        != seconds)){
        return false;
    }
    return true;
}

// Tests initialization to zero.
bool TestZeros(){
    TimeSpan ts(0, 0, 0);
    return CheckValues(ts, 0, 0, 0);
}

// Tests rounding behavior with floating-point seconds.
bool TestFloatSeconds(){
    TimeSpan ts(127.86);
    return CheckValues(ts, 0, 2, 8);
}

// Tests adjustment with negative minutes.
bool TestNegativeMinute(){
    TimeSpan ts(8, -23, 0);
    return CheckValues(ts, 7, 37, 0);
}

// Tests adjustment with negative hours.
bool TestNegativeHour(){
    TimeSpan ts(-3, 73, 2);
    return CheckValues(ts, -1, -46, -58);
}

// Tests addition of multiple TimeSpan objects.
bool TestAdd(){
    TimeSpan ts1, ts2(5), ts3(7, 0), ts4(4, 0, 0);
    TimeSpan add_it_up = ts1 + ts2 + ts3 + ts4;
    return CheckValues(add_it_up, 4, 7, 5);
}

// Tests in-place addition (operator+=).
bool TestAddInPlace(){
    TimeSpan ts1(5, 6, 7);
    TimeSpan ts2(1, 1, 1);
    if ((!CheckValues(ts1, 5, 6, 7)) || (!CheckValues(ts2, 1, 1, 1))){
        return false;
    }
    ts1 += ts2;
    if ((!CheckValues(ts1, 6, 7, 8)) || (!CheckValues(ts2, 1, 1, 1))){
        return false;
    }
    return true;
}

// Tests subtraction of TimeSpan objects.
bool TestSubtraction() {
    TimeSpan ts1(2, 0, 0);  // 2 hours
    TimeSpan ts2(1, 30, 0);  // 1 hour 30 minutes
    TimeSpan result = ts1 - ts2;
    return CheckValues(result, 0, 30, 0);
}

// Tests in-place subtraction (operator-=).
bool TestSubtractInPlace() {
    TimeSpan ts1(3, 15, 0);  // 3 hours 15 minutes
    TimeSpan ts2(1, 20, 0);  // 1 hour 20 minutes
    ts1 -= ts2;
    return CheckValues(ts1, 1, 55, 0);
}

// Tests unary negation of TimeSpan.
bool TestUnaryNegation() {
    TimeSpan ts(1, 30, 0);  // 1 hour 30 minutes
    ts = -ts;
    return CheckValues(ts, -1, -30, 0);
}

// Tests the less than operator between TimeSpan objects.
bool TestLessThan() {
    TimeSpan ts1(1, 30, 0);
    TimeSpan ts2(2, 0, 0);
    return ts1 < ts2;
}

// Tests the less than or equal operator between TimeSpan objects.
bool TestLessThanOrEqual() {
    TimeSpan ts1(1, 30, 0);  // 1 hour 30 minutes
    TimeSpan ts2(1, 30, 0);  // Same as ts1
    TimeSpan ts3(2, 0, 0);   // 2 hours
    return (ts1 <= ts2) && (ts1 <= ts3);
}

// Tests the greater than operator between TimeSpan objects.
bool TestGreaterThan() {
    TimeSpan ts1(3, 45, 0);  // 3 hours 45 minutes
    TimeSpan ts2(3, 30, 0);  // 3 hours 30 minutes
    return ts1 > ts2;
}

// Tests the greater than or equal operator between TimeSpan objects.
bool TestGreaterThanOrEqual() {
    TimeSpan ts1(4, 0, 0);   // 4 hours
    TimeSpan ts2(4, 0, 0);   // Same as ts1
    TimeSpan ts3(3, 59, 59); // Just one second less
    return (ts1 >= ts2) && (ts1 >= ts3);
}

// Tests input stream handling for TimeSpan.
bool TestInputStream() {
    std::stringstream ss("2 45 30");
    TimeSpan ts;
    ss >> ts;
    return CheckValues(ts, 2, 45, 30);
}

// Tests output stream formatting for TimeSpan.
bool TestOutputStream() {
    std::stringstream ss;
    TimeSpan duration1(1, 2, 3);
    ss << duration1;
    return ss.str() == "Hours: 1, Minutes: 2, Seconds: 3";
}

// Tests the Normalization function
bool TestNormalization() {
    TimeSpan ts(1, 150, 120);
    return CheckValues(ts, 3, 32, 0);
}


int main(){
    cout << "Testing TimeSpan Class" << endl;
    if (!TestZeros()) cout << "Failed: TestZeros" << endl;
    if (!TestFloatSeconds()) cout << "Failed: TestFloatSeconds" << endl;
    if (!TestNegativeMinute()) cout << "Failed: TestNegativeMinute" << endl;
    if (!TestNegativeHour()) cout << "Failed: TestNegativeHour" << endl;
    if (!TestAdd()) cout << "Failed: TestAdd" << endl;
    if (!TestAddInPlace) cout << "Failed: TestAddInPlace" << endl;
    if (!TestSubtraction()) cout << "Failed: TestSubtraction" << endl;
    if (!TestSubtractInPlace()) cout << "Failed: TestSubtractInPlace" << endl;
    if (!TestUnaryNegation()) cout << "Failed: TestUnaryNegation" << endl;
    if (!TestLessThan()) cout << "Failed: TestLessThan" << endl;
    if (!TestLessThanOrEqual()) cout << "Failed: TestLessThanOrEqual" << endl;
    if (!TestGreaterThan()) cout << "Failed: TestGreaterThan" << endl;
    if (!TestGreaterThanOrEqual()) cout << "Failed: TestGreaterThanOrEqual" << endl;
    if (!TestInputStream()) cout << "Failed: TestInputStream" << endl;
    if (!TestOutputStream()) cout << "Failed: TestOutputStream" << endl;
    if (!TestNormalization()) cout << "Failed: TestNormalization" << endl;
    cout << "Testing Complete" << endl;
}