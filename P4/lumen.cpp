/*
Benjamin Philipose, 5/18/2023
Version P1 - Created Lumen Class
Version P2 - Implemented public function Recharge()
Version P4 - Reset is maxed out and maximum amount of reset varies per object
Lumen Class Implementation File
*/
#include "lumen.h"
#include <cstdlib>
    lumen operator+(int inputInt, const lumen& x)    {
        lumen temp(x);
        return temp + inputInt;
    }
    lumen::lumen(int initBrightness, double initSize, double initPower) {
        if (initBrightness > MAX_BRIGHTNESS)
        {
            brightness = MAX_BRIGHTNESS;
        }
        else
        {
            brightness = initBrightness;
        }
        if (initSize > MAX_SIZE)
        {
            size = MAX_SIZE;
        }
        else
        {
            size = initSize;
        }
        if (initPower < MINIMUM_POWER)
        {
            power = MINIMUM_POWER;
        }
        else
        {
            power = initPower;
        }

        dimness = 100 - brightness;

        defaultBrightness = brightness;
        defaultDimness = dimness;
        defaultPower = initPower;

        totalGlowRequest = 0;

        double sizePowerPerc = (size / 100) / 2;
        powerThreshold = sizePowerPerc * power;
        powerDeincrement = powerThreshold / 10;
        glowRequestThreshold = (int)(power / 30);
        brightnessDeincrement = (int)(power / brightness);
        resetCntThresh = size/2 + 10;
        resetCnt = 0;
        updateActive();
        updateStable();
    }
    bool lumen::operator>(const lumen& src) const {
        return power > src.power;
    }
    bool lumen::operator<(const lumen& src) const {
        return power < src.power;
    }
    bool lumen::operator>=(const lumen& src) const {
        return power >= src.power;
    }
    bool lumen::operator<=(const lumen& src) const {
        return power <= src.power;
    }
    bool lumen::operator==(const lumen& src) const {
        return power == src.power;
    }
    bool lumen::operator!=(const lumen& src) const {
        return power != src.power;
    } 
    lumen lumen::operator+(const lumen& src) const {
        lumen tempLumen = *this;
        tempLumen.add(src.brightness, src.power);
        return tempLumen;
    }
    lumen& lumen::operator+=(const lumen& src) {
        add(src.brightness, src.power);
        return *this;
    }
    lumen lumen::operator+(int inputInt) const {
        lumen tempLumen = *this;
        tempLumen.add(inputInt, inputInt);
        return tempLumen;
    }
    lumen& lumen::operator+=(int inputInt) {
        add(inputInt, inputInt);
        return *this;
    }
    lumen& lumen::operator++() {
        add(1, 10);
        return *this;
    }
    lumen& lumen::operator++(int) {
        lumen tempLumen(*this);
        add(1, 10);
        return *this;
    }
    void lumen::add(int inpBrig, int inpPow)  {
        if((brightness + inpBrig) > MAX_BRIGHTNESS)    {
            brightness = MAX_BRIGHTNESS;
        }
        else    {
            brightness += inpBrig;
        }
        power += inpPow;
        dimness = 100-brightness;
        updateActive();
        updateStable();
    }
    double lumen::glow()    {
        totalGlowRequest++;
        double retVal = getGlowStateResponse();
        power -= powerDeincrement;
        updateStable();
        updateActive();
        return retVal;
    }
    bool lumen::isStable()  {
        return stable;
    }
    bool lumen::isActive()  {
        return active;
    }
    bool lumen::reset() {
        if ((totalGlowRequest > glowRequestThreshold) && (power > 0) && (resetCnt < resetCntThresh))
        {
            initiateReset();
            return true;
        }
        if ((brightness - brightnessDeincrement) >= 0)
        {
            failedReset();
        }
        return false;
    }
    bool lumen::recharge()  {
        if(isStable())  {
            power = defaultPower;
            return true;
        }
        return false;
    }
    void lumen::updateStable()  {
        if (brightness%BRIGHTNESS_THRESHOLD_DIVISIILITY != 0)
        {
            stable = true;
        }
        else
        {
            stable = false;
        }
    }
    void lumen::updateActive()  {
        if (power >= powerThreshold)
        {
            active = true;
        }
        else
        {
            active = false;
        }
    }
    void lumen::initiateReset() {
        brightness = defaultBrightness;
        dimness = defaultDimness;
        power = defaultPower;
        totalGlowRequest = 0;
        updateStable();
        updateActive();
        resetCnt++;
    }
    void lumen::failedReset()   {
        if (brightness - brightnessDeincrement >= 0)
        {
            brightness -= brightnessDeincrement;
            dimness += brightnessDeincrement;
            updateStable();
        }
    }
    double lumen::getGlowStateResponse()    {
        double powerPercent = abs(power / powerThreshold);
        double retVal = brightness * (powerPercent);
        if (stable && active)
        {
            retVal = brightness * size;
        }
        if (stable && !active)
        {
            retVal = dimness;
        }
        
        return retVal;
    }
