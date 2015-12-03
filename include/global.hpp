#ifndef GLOBAL_H
#define GLOBAL_H

/**
 *  A global tolerance applied when checking if a form overlaps with another form or the plane borders
 *
 *  If the basic unit is considered to be centimeters, 1E-4 is equal to a micrometer.
 *  We assume this is an irrelevant (or even unmeasureable) error in practical applications.
 */
const float TOLERANCE = 1E-4;

#endif