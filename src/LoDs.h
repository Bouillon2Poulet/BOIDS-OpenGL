#pragma once

#include <string>
#include "my3DModel.h"
class LoDs {
private:
    my3DModel _low;
    my3DModel _mid;
    my3DModel _high;

public:
    LoDs(std::string modelName)
        : _low(modelName, "low"), _mid(modelName, "mid"), _high(modelName, "high") {}

    inline my3DModel& getRightModel(float distance)
    {
        if (distance < 3.f)
        {
            std::cout << "high" << std::endl;
            return _high;
        }

        if (distance < 6.f)
        {
            std::cout << "mid" << std::endl;
            return _mid;
        }

        std::cout << "low" << std::endl;

        return _low;
    }
};