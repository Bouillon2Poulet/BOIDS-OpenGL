#pragma once

class DebugUiParameters { // TODO struct
private:
    bool _displayProtectedRange    = false;
    bool _displayVisibleRange      = false;
    bool _displayVelocityVector    = false;
    bool _displayProximityNbr      = false;
    bool _displayLinkToNearestFood = false;

public:
    void
        operator()(DebugUiParameters& toCopy); // TODO use a copy assignment

    void  displayProtectedRange(bool input);
    bool  displayProtectedRange() const;
    bool* displayProtectedRangePtr();

    void  displayVisibleRange(bool input);
    bool  displayVisibleRange() const;
    bool* displayVisibleRangePtr();

    void  displayVelocityVector(bool input);
    bool  displayVelocityVector() const;
    bool* displayVelocityVectorPtr();

    void  displayProximityNbr(bool input);
    bool  displayProximityNbr() const;
    bool* displayProximityNbrPtr();

    void  displayLinkToNearestFood(bool input);
    bool  displayLinkToNearestFood() const;
    bool* displayLinkToNearestFoodPtr();
};
