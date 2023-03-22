#include "displayDebugUiParameters.h"

void displayDebugUiParameters::displayVisibleRange(bool input)
{
    _displayVisibleRange = input;
}
bool displayDebugUiParameters::displayVisibleRange() const
{
    return _displayVisibleRange;
}
bool* displayDebugUiParameters::displayVisibleRangePtr()
{
    return &_displayVisibleRange;
}

void displayDebugUiParameters::displayProtectedRange(bool input)
{
    _displayProtectedRange = input;
}
bool displayDebugUiParameters::displayProtectedRange() const
{
    return _displayProtectedRange;
}
bool* displayDebugUiParameters::displayProtectedRangePtr()
{
    return &_displayProtectedRange;
}

void displayDebugUiParameters::displayVelocityVector(bool input)
{
    _displayVelocityVector = input;
}
bool displayDebugUiParameters::displayVelocityVector() const
{
    return _displayVelocityVector;
}
bool* displayDebugUiParameters::displayVelocityVectorPtr()
{
    return &_displayVelocityVector;
}

void displayDebugUiParameters::displayProximityNbr(bool input)
{
    _displayProximityNbr = input;
}
bool displayDebugUiParameters::displayProximityNbr() const
{
    return _displayProximityNbr;
}
bool* displayDebugUiParameters::displayProximityNbrPtr()
{
    return &_displayProximityNbr;
}
