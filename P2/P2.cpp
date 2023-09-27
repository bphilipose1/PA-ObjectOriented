#include "nova.h"
#include <cstdlib>
#include <ctime>
#include <iostream>
using namespace std;

/*
Benjamin Philipose, 4/13/2023
Version P2 - Driver for Nova class
Nova Class Driver
*/

/*
Description: Random number generator to get 3 random values and stores them in an array
*/
void getTestValues(int parameterNum[]) {
    
    parameterNum[0] = (rand() % 271) + 30; // random number between 30 and 300
    parameterNum[1] = (rand() % 271) + 30; // random number between 30 and 300
    parameterNum[2] = (rand() % 19) + 2; // random number between 2 and 20

}

/*Tests with iteration all public functions in nova class, using random inputs for varied results
loops tests for 8 seperate nova objects*/
void iterateLumenTest(int totIteration)    {
    int randArr[3];
    const int totalObj = 8;
    nova novaList[totalObj];
     

    // initialize 8 nova objects for tests
    for (int i = 0; i < totalObj; i++) {
        getTestValues(randArr);
        novaList[i] = nova(randArr[0], randArr[1], randArr[2]);
        cout << "Creating Nova#" << i << "(" << randArr[0] << "," << randArr[1] << "," << randArr[2]  << ")" << endl;
    }
    

    //loops each nova object to use multiple public functions with random inputs
    for(int i = 0; i < totIteration; i++)    {
        cout << "\nIteration: " << i << endl;
        getTestValues(randArr);
        for (int j = 0; j < totalObj; j++) {
            novaList[j].glow(randArr[0]);
            cout << "Creating Nova#" << j << " | Reset Sucess: " << novaList[j].reset(randArr[1]) << " ";
            cout << "| Maximum: " << novaList[j].getMaximum() << " | Minimum: " << novaList[j].getMinimum() << endl;
        }        
    }


}

/*to attempt to persuade compiler to invoke move constructor/assignment using pass by value*/
nova useMove(nova temp) {
    return temp;
}

int main() {
    srand(time(NULL)); 
    int testParam[3];
    nova ObjA;

    //Constructor
    getTestValues(testParam);
    nova ObjB = nova(testParam[0], testParam[1], testParam[2]);

    //Copy Constructor
    nova ObjC = nova(ObjB);

    //Move Constructor - 
    nova ObjD = useMove(ObjC);

    //Copy Assignment
    nova ObjE;
    ObjE = ObjD;

    //Move Assignment
    ObjA = useMove(ObjD);

    //run iterative tests with multiple objects

    iterateLumenTest(30);  
    
    return 0;
}



