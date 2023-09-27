/*
Benjamin Philipose, 3/30/2023, Version 1
Lumen Class
*/

class Lumen
{
    /*
    Brightness: is type integer representing Percentage (Input between 0-100)
    Size: in Cm (Input between 0-100cm)
    Power: in Watts (Input at least 30+ Watts)
    
    isActive: State of Lumen if there is enough power for consistent output
    - Active State can be toggled to active or not active utilizing toggleActive, which represents an on an off button
    
    isStable: State of Lumen if there is not enough power for consistent output
    - Stability state occurs to be true when the 'battery' (power) stays above
        a precalculated percentage (power threshold) determined by Lumens size. 
    - If power dips below the preset battery percentage (power threshold) Stability becomes false to represent 
        the idea of a low battery that wont give consistent power.
    
    totalGlowRequest: count total number of glow() calls before reset

    glow()
    - Glow has 3 states that were requested by design specification.
      - First is if the Lumen Object is both Active and Stable, this represents a flashlight thats adequetly charged and on. 
        It will return, as a requested design, brightness magnified by size which is implemented as brightness*size
      - If Lumen object is Stable but NOT active, I have designed it under the idea of a adequetly charged flashlight that is off.
        Therefore, as a requested design, it returns a dimness value, which is the opposite percentage of brightness ranging from 0-100.
      - If Lumen object is Not stable but is active, I have designed it with the idea of a low charge that doesnt have enough power
        for consistent preformance. By requested design, this situaton would return an 'erradic' value which is portrayed by combining a few 
        power variables and brightness variables to get a small but seemingly noPattern set of values that is always positive or 0.
    */

    /*
    Parameterized Constructor
    PRE: NONE
    POST: Creates Lumen Object Initialized to Active and Stable States.
    */
    public Lumen(int initBrightness = 100, double initSize = (MAX_SIZE / 2), double initPower = 200)
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

        active = true;
        stable = true;

        totalGlowRequest = 0;

        double sizePowerPerc = (size / 100) / 2;
        powerThreshold = sizePowerPerc * power;
        powerDeincrement = powerThreshold / 10;
        glowRequestThreshold = (int)(power / 30);
        brightnessDeincrement = (int)(power / brightness);
    }
    /*
    checks for the 4 combination of the 2 states, isActive and isStable
    returns based on combinations: 
    Lumen is Stable and On - Return Brightness*Size
    Lumen is Stable and Off - Return Dimness
    Lumen is Unstable and On - Return Brightness affected by powersPercentage (power/powerThreshold)
    Error: If Lumen is Unstable and NOT Active - Return -1

    PRE: NONE
    POST: Deincrements Power
    */
    public double glow()
    {
        totalGlowRequest++;
        double retVal = getGlowStateResponse();
        power -= powerDeincrement;
        updateStable();
        updateActive();
        return retVal;
    }
    /*
    Tells user if Lumen object is stable or not
    */
    public bool isStable()
    {
        return stable;
    }
    /*
    Tells user if Lumen object is active or not
    */
    public bool isActive()
    {
        return active;
    }
    /*
    resets IF reset conditions met
    PRE: NONE
    POST: Updates Deincrements Brightness if Reset doesnt occur, else no change
    */
    public bool reset()
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

    /*
     * Gives User a rough ratio of the amount of power dropped from initial value in the Lumen Object
    public double checkBattery()
    {
        double retPerc = ((int)((power / defaultPower) * 1000)) / 10;
        if (retPerc > 0)
        {
            return retPerc;
        }
        return 0;
    }

    */

    /*
    checks if power threshold to keep bulb fully stable is met
    PRE: NONE
    POST: if power is altered to change from either below or above preset power threshold, 
    isStable state will change accordingly
    */
    private void updateStable()
    {
        if (power >= powerThreshold)
        {
            stable = true;
        }
        else
        {
            stable = false;
        }
    }

    private void updateActive()
    {
        if (brightness >= BRIGHTNESS_THRESHOLD)
        {
            active = true;
        }
        else
        {
            active = false;
        }
    }



    /*Resets Lumen Object back to default values
    POST: sets main original paramaters back to values set when initialized in constructor*/
    private void initiateReset()
    {
        brightness = defaultBrightness;
        dimness = defaultDimness;
        power = defaultPower;
        totalGlowRequest = 0;
    }
    /*Function that causes deincrement in Brightness from a failed Reset
    POST: will Deincrement brightness untill it is 0*/
    private void failedReset()
    {
        if (brightness - brightnessDeincrement >= 0)
        {
            brightness -= brightnessDeincrement;
            dimness += brightnessDeincrement;
        }
    }
    /*Checks the two State responses and returns appropriate response value*/
    private double getGlowStateResponse()
    {
        double retVal = -1;
        if (stable && active)
        {
            retVal = brightness * size;
        }
        if (stable && !active)
        {
            retVal = dimness;
        }
        if (!stable && active)
        {
            double powerPercent = Math.Abs(power / powerThreshold);
            retVal = brightness * (powerPercent);
        }
        return retVal;
    }
    private const int MAX_BRIGHTNESS = 100;
    private const double MAX_SIZE = 100.0;
    private const double MINIMUM_POWER = 10.0;
    private const int BRIGHTNESS_THRESHOLD = 50;
    private int brightness;
    private int dimness;
    private double power;
    private int totalGlowRequest;
    private bool active;
    private bool stable;

    private readonly int brightnessDeincrement;
    private readonly double powerDeincrement;
    private readonly int glowRequestThreshold;
    private readonly int defaultBrightness;
    private readonly int defaultDimness;
    private readonly double defaultPower;
    private readonly double size;
    private readonly double powerThreshold;

}
