#include "DebugUiParameters.h"

void DebugUiParameters::operator()(DebugUiParameters& toCopy)
{
    _displayProtectedRange = toCopy._displayProtectedRange;
    _displayVisibleRange   = toCopy._displayVisibleRange;
    _displayVelocityVector = toCopy._displayVelocityVector;
    _displayProximityNbr   = toCopy._displayProximityNbr;
}

void DebugUiParameters::displayVisibleRange(bool input)
{
    _displayVisibleRange = input;
}
bool DebugUiParameters::displayVisibleRange() const
{
    return _displayVisibleRange;
}
bool* DebugUiParameters::displayVisibleRangePtr()
{
    return &_displayVisibleRange;
}

void DebugUiParameters::displayProtectedRange(bool input)
{
    _displayProtectedRange = input;
}
bool DebugUiParameters::displayProtectedRange() const
{
    return _displayProtectedRange;
}
bool* DebugUiParameters::displayProtectedRangePtr()
{
    return &_displayProtectedRange;
}

void DebugUiParameters::displayVelocityVector(bool input)
{
    _displayVelocityVector = input;
}
bool DebugUiParameters::displayVelocityVector() const
{
    return _displayVelocityVector;
}
bool* DebugUiParameters::displayVelocityVectorPtr()
{
    return &_displayVelocityVector;
}

void DebugUiParameters::displayProximityNbr(bool input)
{
    _displayProximityNbr = input;
}
bool DebugUiParameters::displayProximityNbr() const
{
    return _displayProximityNbr;
}
bool* DebugUiParameters::displayProximityNbrPtr()
{
    return &_displayProximityNbr;
}

void DebugUiParameters::displayLinkToNearestFood(bool input)
{
    _displayLinkToNearestFood = input;
}
bool DebugUiParameters::displayLinkToNearestFood() const
{
    return _displayLinkToNearestFood;
}
bool* DebugUiParameters::displayLinkToNearestFoodPtr()
{
    return &_displayLinkToNearestFood;
}
