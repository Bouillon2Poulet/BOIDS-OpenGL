#include "LoDs.h"

LoDs::LoDs(std::string modelName)
    : _low(modelName, "low"), _mid(modelName, "mid"), _high(modelName, "high") {}

my3DModel& LoDs::getRightModel(float distance)
{
    if (distance < 1.f)
    {
        return _high;
    }

    if (distance < 9.f)
    {
        return _mid;
    }

    return _low;
}