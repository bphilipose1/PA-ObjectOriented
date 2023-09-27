/*
Benjamin Philipose, 5/18/2023
Version P4 - Update Nova Class to have Dependency Injection
Nova Class Header File
*/
#include "lumen.h"

#ifndef NOVA_H
#define NOVA_H

class nova {
/*
        -----------------------CLASS INVARIANT-----------------------
        * Constructor Enforces ERROR checking with the above parameters by implementing a gaurd clause for the dependency injected array of Lumen Objects.
        If gaurd clause detects an issue it will throw an invalid_argument exception. Nova assumes ownership of array lumen objects. Expects Clients to input the correct size with respect to the injected array of lumen objects
        Client must pass in an array of lumen pointers when constructing object
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

        * Comparison Overloading Operators: this operator compares the number of lumen objects from both Nova Objects

        * Addition Overloading Operators: allow for additions of lumen objects to Nova list of lumens

        * Subtraction Overloading Operators: Was decided to be not needed because due to abstraction the user is not reliably able to track if two 
        Novas have the same values which if a subtraction opeartor was implemented, would remove the same lumens from Both novas when making the new
        temporary. Due to this rare occurance and lack of reliability to the client, it was not included.

        *Multiplication Overloading Operators: Was decided to be not needed as the user already is able to increment the number of lumens and the
        types of lumens inputted into the nova object. Therefore it was found to be redundant to implement a multiplication overload.

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
    nova(int totalLumens, lumen** inputArr);

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
    DESCRIPTION: Overload the == Comparison operator. Compares Nova's Number of lumen objects.
    */
    bool operator==(const nova& src) const;

    /*
    DESCRIPTION: Overload the != Comparison operator. Compares Nova's Number of lumen objects.
    */ 
    bool operator!=(const nova& src) const;

    /*
    DESCRIPTION: Overload the > Comparison operator. Compares Nova's Number of lumen objects. 
    */
    bool operator>(const nova& src) const;

    /*
    DESCRIPTION: Overload the < Comparison operator. Compares Nova's Number of lumen objects.
    */ 
    bool operator<(const nova& src) const;

    /*
    DESCRIPTION:  Overload the >= Comparison operator. Compares Nova's Number of lumen objects.
    */
    bool operator>=(const nova& src) const;

    /*
    DESCRIPTION: Overload the <= Comparison operator. Compares Nova's Number of lumen objects.
    */ 
    bool operator<=(const nova& src) const;

    /*
    DESCRIPTION: Overload the + operator, combines both list of lumens to one.
    */
    nova operator+(const nova& src) const;

    /*
    DESCRIPTION: Overload the += operator, increases current list of lumens to include right operator nova's
    PRE: NONE
    POST: Updates Novas array of lumens left of the operator
    */
    nova& operator+=(const nova& src);

    /*
    DESCRIPTION: Overload the + operator, combines novas LumenList with lumen object
    PRE: None
    POST: returns a temporary with the combination of nova and lumen
    */
    nova operator+(const lumen& src) const;

    /*
    DESCRIPTION: Overload the += operator, combines novas LumenList with lumen object
    PRE: NONE
    POST: Updates Novas array of lumens left of the operator
    */
    nova& operator+=(const lumen& src);

    /*
    DESCRIPTION: Overload the prefix ++ operator. Increases by 1, the number of lumens in nova object by 1
    PRE: NONE
    POST: Updates Novas array of lumens 
    */
    nova& operator++();

    /*
    DESCRIPTION: Overload the postfix ++ operator. Increases the number of lumens in nova object by 1 
    PRE: NONE
    POST: Updates Novas array of lumens 
    */
    nova operator++(int);

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

nova operator+(lumen x, nova y);
#endif 

