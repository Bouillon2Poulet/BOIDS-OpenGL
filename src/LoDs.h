#pragma once

#include <string>
#include "my3DModel.h"
class LoDs {
private:
    my3DModel _low;
    my3DModel _mid;
    my3DModel _high;

public:
    LoDs(std::string modelName);
    my3DModel& getRightModel(float distance);
};