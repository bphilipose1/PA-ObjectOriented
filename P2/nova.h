/*
Benjamin Philipose, 4/13/2023
Version P2 - Created Nova Class
Nova Class Header File
*/
#include "lumen.h"

#ifndef NOVA_H
#define NOVA_H

class nova {
/*
        -----------------------CLASS INVARIANT-----------------------
        * Constructor Enforces ERROR checking with the above parameters by checking if client input a value greater than 0. If not 
        it will modify the users input
        * Constructor Sets Default Parameters for Users
            * for all 3 input parameters, values are expected to be greater than 0
        
        * Nova Class has implementation of copy assignment and constructor, as well as move assignment and constructor        

        *glow(x) function requests user to input the number of lumen objects to glow, and will glow the first x lumens from the beginning
        of the array called LumenList
            *glow() has error checking that avoids underflow caused by a negative input. program will utilize input value but remove
            the negative sign 
        
        *reset(x) function requests user to input the number of lumen objects to reset, and will reset the first x lumens from the beginning
        of the array called LumenList
            *reset(x) has error checking that avoids underflow caused by a negative input. program will utilize input value but remove
            the negative sign 
            *reset(x) was included to allow for the ability of lumen objects to become unstable, which will allow for helper functions
            to replace the lumen object

        *for both getMinimum and getMaximum functions, client must utilize the glow function  before getter can get a value. If not, 
        function will return -101 which is a high magnitude number that is not a value that can be normally obtained from getMinimum() 
        and getMaximum()

        */
private:
    /*
    DESCRIPTION: Creates and Allocates a new Lumen Object on 
    the heap and returns a lumen object pointer 
    PRE: input values should be positive and not 0
    POST: Creates new dynamic lumen object
    */
    lumen* makeLumen(int x, int y);
        
    /*
    DESCRIPTION: Checks through LumenList and if lumen is unstable, it will replace lumen object
    PRE: NONE
    POST: If a lumen in LumenList is found with unstable state, it will be replaced with a new lumen object of random parameters
    */
    void attemptReplaceLumen();

    /*
    DESCRIPTION: recharges all lumen objects
    PRE: None
    POST: all Lumen objects in LumenList are attempted to be charged to original starting power
    */
    void rechargeLumens();  

    /*
    DESCRIPTION: if 50% of lumen obj are in not active state, call rechargeLumens()
    PRE: None
    POST: calls helper function rechargeLumens() to attempt to recharge lumen objects stored in nova
    */
    bool attemptRecharge();

    /*
    DESCRIPTION: Find minimum and maximum values returned inputted array
    PRE: size should be non negative
    POST: Updates the minimum and maximum class data members
    */
    void findMinMax(double* inputArr, int size);
       
    /*
    DESCRIPTION: private utility for copying
    PRE: Current Nova object must deallocate all memory it holds before using copy
    POST: copies the current objects state from the inputted object
    */
    void copy(const nova& inputNova);

    int size;
    lumen** LumenList;
    double minimumGlow;
    double maximumGlow;
    int randLumenNum;
    static const int MAX_BRIGHTNESS = 100;
    static const int MAX_SIZE = 100;
    static const int MAX_POWER = 300;
    

public:
    /*
    DESCRIPTION:Parameterized with default values Constructor;
    PRE: NONE
    POST: Creates a Nova Object
    */
    nova(int randInput1 = 10, int randInput2 = 20, int totalLumens = 30);

    /*
    DESCRIPTION: Copy Constructor
    PRE: NONE
    POST: Creates object with the same values as the inputed nova object
    */
    nova(const nova& inputNova);

    /*
    DESCRIPTION: Copy Assignment
    PRE: NONE
    POST: Copies state and values of object on right of '=' to the left object
    */
    nova& operator=(const nova& inputNova);
        
    /*
    DESCRIPTION: Move Constructor
    PRE: NONE
    POST: inputNova will be in undefined state after
    */
    nova(nova&& inputNova);

    /*
    DESCRIPTION: Move Assignment 
    PRE: NONE
    POST: inputNova will be in undefined state after
    */
    nova& operator=(nova&& inputNova);

    /*
    DESCRIPTION:Class Destructor
    PRE:NONE
    POST: Deallocates nova objects dynamic memory
    */
    ~nova();

    /*
    DESCRIPTION:glows the first numGlow Lumens in array and obtains 
    the maximum value gained, and the minimum value gained from that set of glows
    PRE: 
    POST: updates minimumGlow and Maximum Glow data members and glows the first numGlow lumens in LumenList
    */
    void glow(int numGlow);

    /*
    DESCRIPTION:resets the first numGlow Lumens in array 
    PRE: 
    POST: resets the first numGlow lumens in LumenList
    */
    double reset(int numGlow);

    /*
    DESCRIPTION:Queries Minimum value from last set of glows, else returns -1;
    PRE: run glow() for nova object
    POST: NONE
    */
    double getMinimum();

    /*
    DESCRIPTION:Queries Maximum value from last set of glows, else returns -1;
    PRE: run glow() for nova object
    POST: NONE
    */
    double getMaximum();

};
/*
 -----------------------Implementation Invariant----------------------- 
    *nova class has a variable amount of Lumen Objects which is set in the constructor
    *The Lumen objects are stored in a 

    *minimumGlow and maximumGlow are data members recording the highest and lowest glow values of the most recent glow. 
    If a glow has not been run for the current nova object, both values are initialized to -1 to represent error.
        *minimumGlow and maximumGlow are only to be viewed but not modified by the client
 
    *Internal Recharge for nova attempts to recharge each lumen to maximum capacity when it detects that less than 50% of the 
    stored lumen objects in nova are inactive

    *If lumens are found to be unstable, they are replaced by a new lumen object, with seemingly variable parameters

    *RandLumenInt is a data member that is calculated and increments values in makeLumen to allow for the creation of unique lumen objects
 
    * Make lumens requires that there is not a 0 or a negative number inputted in order to create an optimal lumen object

     
 */

#endif 

