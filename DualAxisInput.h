#ifndef _DUALAXISINPUT_H_
#define _DUALAXISINPUT_H_

#include <Arduino.h>
// #include <millis_utils.h>

#ifndef AXIS_INPUT_DEAD_MIN
#define AXIS_INPUT_DEAD_MIN 30
#endif
#ifndef AXIS_INPUT_DEAD_MAX
#define AXIS_INPUT_DEAD_MAX 70
#endif
#ifndef AXIS_INPUT_MAP_MAX
#define AXIS_INPUT_MAP_MAX 100
#endif

class DualAxisInput
{
private:
    //pins
    byte _pinX;
    byte _pinY;

    //
    int _x;
    int _y;

    // rotation setting
    byte _rotation;

    // last read position
    byte _pos;
    // previous position
    byte _prev;
    // last time position changed in millis
    unsigned long _lastChangeMS;

    // position according to
    byte rawMovement()
    {

        if (_x < AXIS_INPUT_DEAD_MIN)
            return RIGHT;
        if (_x > AXIS_INPUT_DEAD_MAX)
            return LEFT;
        if (_y < AXIS_INPUT_DEAD_MIN)
            return DOWN;
        if (_y > AXIS_INPUT_DEAD_MAX)
            return UP;

        return NONE;
    }

    byte movement()
    {

        byte b = rawMovement();
        if (b)
        {
            return 1 + (b - 1 + _rotation) % 4;
        }

        return b;
    }

public:
    // POSITION CONSTANTS

    static const byte NONE = 0;
    static const byte RIGHT = 1;
    static const byte DOWN = 2;
    static const byte LEFT = 3;
    static const byte UP = 4;

    // ROTATION SETTING CONSTANTS

    // PINS LEFT
    static const byte ROTATION_0 = 0;
    // PINS UP
    static const byte ROTATION_90 = 1;
    // PINS RIGHT
    static const byte ROTATION_180 = 2;
    // PINS DOWN
    static const byte ROTATION_270 = 3;

    DualAxisInput(byte x, byte y, byte rotation = ROTATION_0) : _pinX(x), _pinY(y), _rotation(rotation) {}

    ~DualAxisInput() {}

    /** Reads inputs to calculate current position.
     *  Must always be used before any other method.
     *  If position changed, millis timestamp will be recorded.
     *  @return Current position NONE,UP,DOWN,LEFT,RIGHT
     **/
    byte read()
    {

        _x = map(analogRead(_pinX), 0, 1023, 0, AXIS_INPUT_MAP_MAX);
        _y = map(analogRead(_pinY), 0, 1023, 0, AXIS_INPUT_MAP_MAX);
        _prev = _pos;
        _pos = movement();
        if (changed())
            _lastChangeMS = millis();
        return _pos;
    }

    /** Gets last read x axis value mapped from 0 to \c AXIS_INPUT_MAP_MAX which is 100 if not modified*/
    int x() { return _x; }
    /** Gets last read y axis value mapped from 0 to \c AXIS_INPUT_MAP_MAX which is 100 if not modified*/
    int y() { return _y; }

    /** Get last read position */
    byte position() { return _pos; }

    /** Check if axis changed when last read*/
    bool changed()
    {
        return _prev != _pos;
    }


    bool isNone() { return _pos == NONE; }
    bool isRight() { return _pos == RIGHT; }
    bool isDown() { return _pos == DOWN; }
    bool isLeft() { return _pos == LEFT; }
    bool isUp() { return _pos == UP; }

    /** returns millis in same position */
    unsigned long timeOnPosition()
    {
        return millis() - _lastChangeMS;
       
    }
};

#endif