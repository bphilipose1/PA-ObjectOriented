/*
Benjamin Philipose, 4/13/2023
Version P1 - Created Lumen Class
Version P2 - Implemented public function Recharge()
Lumen Class Header File
*/
#ifndef LUMEN_H
#define LUMEN_H
class lumen
{
        /*
        -----------------------CLASS INVARIANT-----------------------
        * Brightness: is type integer representing Percentage of illumination (Input between 0-100)
            - For optimal use, values above 50% allow for more availability to enter all possible object states (specifically)
        * Size: in Cm (Input between 0-100cm)
        * Power: in Watts (Input at least 30 Watts)

        * Constructor Enforces ERROR checking with the above parameters by checking if client input a values higher or lower than the bound, and
        editing such value so it is set to the nearest bound allowed.
        * Constructor Sets Default Parameters for Users
            - Brightness: is type integer representing Percentage of illumination (Input between 0-100)
                - For optimal use, values above 50% allow for more availability to enter all possible object states (specifically)
            - Size: in Cm (Input between 0-100cm)
            - Power: in Watts (Input at least 30 Watts)
                
        * There are 2 main states in Lumen, Active, and Stable  
        * Client can query Active and Stable states utilizing the functions isActive() and isStable() 

        * glow()
        - Glow has 3 different ways to calculate return values depending on Active and Stable states
        - First is if the Lumen Object is Stable and Active
        - If Lumen object is Stable but NOT Active
        - If Lumen object is Not stable. 

        * reset()
            - Will ATTEMPT to reset object back to its original state. will return a boolean related to its success or failure
        
        * recharge()
            - If lumen object is stable it will allow power to be reset back to the value when initialized originally
        */

    private:
        /*
        * Description: checks if brightness is divisible by 5 and set state accordigly
        * PRE: NONE
        * POST: if brightness is changed to being divisible by 5 or to being not divisible, 
            Stable state will change accordingly
        */
        void updateStable();
        
        /*
        * Description: checks if power threshold to keep Lumen active is met
        * PRE: NONE
        * POST: if power is altered to change from either below or above preset power threshold, 
            active state will change accordingly
        */
        void updateActive();

        /*
        * Description: Resets Lumen Object back to default values
        * POST: sets objects paramaters back to values set when first initialized in constructor
        */
        void initiateReset();
        
        /*
        * Description: Function that causes deincrement in Brightness from a failed Reset
        * POST: will Deincrement brightness unless it is 0
        */
        void failedReset();
        
        /*
        * Description: Checks the two State responses and returns appropriate response value
        */
        double getGlowStateResponse();
        
        const int MAX_BRIGHTNESS = 100;
        const double MAX_SIZE = 100.0;
        const double MINIMUM_POWER = 30.0;
        const int BRIGHTNESS_THRESHOLD_DIVISIILITY = 5;
        
        int brightness;
        int dimness;
        double power;
        int totalGlowRequest;
        bool active;
        bool stable;

        int brightnessDeincrement;
        double powerDeincrement;
        int glowRequestThreshold;
        int defaultBrightness;
        int defaultDimness;
        double defaultPower;
        double size;
        double powerThreshold;
    public:
        /*
        Parameterized Constructor
        PRE: NONE
        POST: Creates Lumen Object Initialized to Active state.
        */
        lumen(int initBrightness = 100, double initSize = 50.0, double initPower = 200);
        
        /*
        * Description: checks for the 3 combination of the 2 states, isActive and isStable
            * returns based on combinations: 
            * Lumen is Stable and On - Return Brightness*Size
            * Lumen is Stable and Off - Return Dimness
            * Lumen is Unstable - Return Brightness affected by powersPercentage (power/powerThreshold)
        PRE: NONE
        POST: Deincrements Power
        */
        double glow();
        
        /*
        * Description: Tells user if Lumen object is stable or not
        */
        bool isStable();
        
        /*
        * Description: Tells user if Lumen object is active or not
        */
        bool isActive();
        
        /*
        * Description: resets IF reset conditions are met
        * PRE: NONE
        * POST: Deincrements Brightness if Reset doesnt occur, else will alter objects main parameters 
        * to those initially set in constructor
        */
        bool reset();

        /*
        * Description: sets power back to initial value IF object is stable
        * PRE: NONE
        * POST: Sets objects power to originally initialized value, 
        * returns true or false depending on if power change was sucessful
        */
        bool recharge();
        

};
/*
 -----------------------Implementation Invariant----------------------- 
 * Active and Stable are not directly modified by client
     
 * Active: State of Lumen if there is enough power for consistent output
    - If power dips below the preset battery percentage (power threshold) Active becomes false to represent 
      the idea of a low battery that wont give consistent power.    
 * Stable: State of Lumen if there is a brightness value not divisible by 5
 * States are initially calculated in constructor. Active is always garunteed to be on becaues
    power will always start greater than the threshold. Stable initial value is dependent on client input brightness

 * Dimness value is the 'anti' percentage of brightness
 * All Deincrement is scaled based on calculations done in the constructor
 * Glow's Return Response is based on the combination of Stable and Active states
 * There is forced ERROR handling/correction in constructor, to ensure that client's input values 
    do stay within the reccomended ranges


 */


#endif 