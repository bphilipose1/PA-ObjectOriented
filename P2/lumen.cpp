/*
Benjamin Philipose, 4/13/2023
Version P1 - Created Lumen Class
Version P2 - Implemented public function Recharge()
Lumen Class Implementation File
*/
#include "lumen.h"
#include <cstdlib>

    lumen::lumen(int initBrightness, double initSize, double initPower): MAX_BRIGHTNESS(100), MAX_SIZE(100.0), MINIMUM_POWER(30.0), BRIGHTNESS_THRESHOLD_DIVISIILITY(5)
    {
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
        updateActive();
        updateStable();
    }
    double lumen::glow()
    {
        totalGlowRequest++;
        double retVal = getGlowStateResponse();
        power -= powerDeincrement;
        updateStable();
        updateActive();
        return retVal;
    }
    bool lumen::isStable()
    {
        return stable;
    }
    bool lumen::isActive()
    {
        return active;
    }
    bool lumen::reset()
    {
        if ((totalGlowRequest > glowRequestThreshold) && (power > 0))
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
    bool lumen::recharge() 
    {
        if(isStable())  {
            power = defaultPower;
            return true;
        }
        return false;
    }
    void lumen::updateStable()
    {
        if (brightness%BRIGHTNESS_THRESHOLD_DIVISIILITY != 0)
        {
            stable = true;
        }
        else
        {
            stable = false;
        }
    }
    void lumen::updateActive()
    {
        if (power >= powerThreshold)
        {
            active = true;
        }
        else
        {
            active = false;
        }
    }
    void lumen::initiateReset()
    {
        brightness = defaultBrightness;
        dimness = defaultDimness;
        power = defaultPower;
        totalGlowRequest = 0;
        updateStable();
        updateActive();
    }
    void lumen::failedReset()
    {
        if (brightness - brightnessDeincrement >= 0)
        {
            brightness -= brightnessDeincrement;
            dimness += brightnessDeincrement;
            updateStable();
        }
    }

    double lumen::getGlowStateResponse()
    {
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
