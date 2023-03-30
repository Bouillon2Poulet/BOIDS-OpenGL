#pragma once

#include <p6/p6.h>
#include "DebugUiParameters.h"
#include "DebugUiVariable.h"
#include "MovementVariables.h"
#include "behaviorVariables.h"

class DebugUi {
private:
    DebugUiParameters _parameters;
    DebugUiVariables  _variables;

public:
    DebugUi() = default;
    DebugUi(MovementVariables& mvtToCopy, BehaviorVariables& bhvToCopy)
        : _variables(mvtToCopy, bhvToCopy){};

    DebugUi(MovementVariables& mvtToCopy, BehaviorVariables& bhvToCopy, DebugUi& debugUitoCopy)
        : _variables(mvtToCopy, bhvToCopy), _parameters(debugUitoCopy._parameters){};

    DebugUi(const DebugUi& toCopy) = default;

    inline void operator()(DebugUi& toCopy)
    {
        _parameters = toCopy._parameters;
        _variables(toCopy._variables);
    }
    inline void copy(DebugUi& toCopy)
    {
        _parameters(toCopy._parameters);
        _variables(toCopy._variables);
    }
    inline void copyParameters(DebugUi* toCopy)
    {
        _parameters = toCopy->_parameters;
    };
    inline void              copyVariables(){};
    inline DebugUiParameters parameters() const { return _parameters; };

    void drawProtectedCircle(p6::Context& ctx) const;
    void drawVisibleCircle(p6::Context& ctx) const;
    void drawVelocityVector(p6::Context& ctx) const;
    void drawProximityNbr(unsigned int neighboringFishes, p6::Context& ctx) const;

    inline DebugUiVariables variables() { return _variables; };
    // DebugUi debugUi();
    // DebugUi* debugUiPtr();
    DebugUiParameters* parametersPtr()
    {
        return &_parameters;
    }
};
