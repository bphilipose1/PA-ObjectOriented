#include "nova.h"
#include "lumen.h"
#include <cstdlib>
#include <ctime>
#include <iostream>
#include <vector>
#include <random>
#include <memory>
using namespace std;

/*
Benjamin Philipose, 5/18/2023
Version P4 - Driver for Nova&Lumen class
Nova&Lumen Class Driver
*/
/*
Generates random vector of lumen objects
*/
int makeLumenArr(lumen*** temp)   {
    std::random_device rd;
    std::mt19937 ran(rd());
    std::uniform_int_distribution<int> tempSize(5, 100);
    std::uniform_int_distribution<int> tempBright(0, 100);
    std::uniform_int_distribution<int> tempSize1(5, 100);
    std::uniform_int_distribution<int> tempPower(100, 3000);
    int tSize = tempSize(ran);
    int tBright;
    int tSize1;
    int tPower;

    *temp = new lumen*[tSize];
    for(int i = 0; i < tSize; i++)   {
        tSize1 = tempSize1(ran);
        tBright = tempBright(ran);
        tPower = tempPower(ran);
        (*temp)[i] = new lumen(tBright, tSize1, tPower);
    }
    return tSize;
}


/*
Description: Random number generator to get 3 random values and stores them in an array
*/
vector<int> getTestValues() {
    std::vector<int> randValArr;
    
    std::random_device rd;
    std::mt19937 ran(rd());


    std::uniform_int_distribution<int> tempBright(30, 300);
    std::uniform_int_distribution<int> tempPower(30, 300);
    std::uniform_int_distribution<int> tempSize(2, 200);
    int tBright=tempBright(ran);
    int tSize=tempSize(ran);
    int tPower=tempPower(ran);
    randValArr.push_back(tBright);// random number between 30 and 300
    randValArr.push_back(tPower);// random number between 30 and 300
    randValArr.push_back(tSize);// random number between 2 and 20
    
    return randValArr;
}

/*Tests with iteration all public functions in nova class, using random inputs for varied results
loops tests for 8 seperate nova objects*/
std::shared_ptr<std::vector<nova>> iterateLumenTest(int totIteration)    {
    lumen** randLumenArr; //Needs to be raw pointer for dependency Injection

    const int totalObj = 10;
    std::shared_ptr<std::vector<nova>> novaList = std::make_shared<std::vector<nova>>();
  

    // initialize 8 nova objects for tests
    for (int i = 0; i < totalObj; i++) {
        int size = (makeLumenArr(&randLumenArr));
        (*novaList).push_back(nova(size, randLumenArr));
        cout << "Creating Nova#" << i << "(size: " << size << ")" << endl;
    }
    

    //loops each nova object to use multiple public functions with random inputs
    std::vector<int> randArr;
    for(int i = 0; i < totIteration; i++)    {
        cout << "\nIteration: " << i << endl;
        randArr = getTestValues();
        for (int j = 0; j < totalObj; j++) {
            (*novaList)[j].glow(randArr[0]);
            cout << "Nova#" << j << " | Reset Sucess: " << (*novaList)[j].reset(randArr[1]) << " ";
            cout << "| Maximum: " << (*novaList)[j].getMaximum() << " | Minimum: " << (*novaList)[j].getMinimum() << " ";
        }        
    }

    return novaList;
}

/*to attempt to persuade compiler to invoke move constructor/assignment using pass by value*/
nova useMove(nova temp) {
    return temp;
}
int main() {
    srand(time(NULL));
     
    lumen** DI;
    int size = (makeLumenArr(&DI));

    nova ObjA = nova(size, DI);

    //Constructor
    size = (makeLumenArr(&DI));
    nova ObjB = nova(size, DI);
    //Copy Constructor
    nova ObjC = nova(ObjB);
    //Move Constructor - 
    nova ObjD = useMove(ObjC);
    //Copy Assignment
    nova ObjE = ObjD;
    //Move Assignment
    ObjA = useMove(ObjD);
    //Testing Unique Ptr
    lumen** randLumenArr;
    size = (makeLumenArr(&randLumenArr));
    std::unique_ptr<nova> uPtr(new nova(size, randLumenArr));
    uPtr->glow(16);
    cout << "| Maximum: " << uPtr->getMaximum() << " | Minimum: " << uPtr->getMinimum() << endl;


    //run iterative tests with multiple objects utilizing shared ptr    
    std::shared_ptr<std::vector<nova>> myNovaList = iterateLumenTest(30);     
    // replace the last 4 nova objects for tests
    if ((*myNovaList).size() >= 4) {
        (*myNovaList).erase((*myNovaList).end() - 4, (*myNovaList).end());
    }
    for (int i = 0; i < (int)(*myNovaList).size()/2; i++) {
        size = (makeLumenArr(&randLumenArr));
        (*myNovaList).push_back(nova(size, randLumenArr));
        cout << "Creating Nova#" << i << "(size: " << size << ")" << endl;
    }
    //loops each nova object (total of 8) to use multiple public functions with random inputs
    std::vector<int> randArr;
    for(int i = 0; i < 8; i++)    {
        cout << "\nIteration: " << i << endl;
        randArr = getTestValues();
        for (int j = 0; j < (int)(*myNovaList).size(); j++) {
            (*myNovaList)[j].glow(randArr[0]);
        } 
        if(i != 0)  {
                cout << "Is Nova#" << (i-1) << " ___ " << "Nova#" << i << " ? " << endl;
                cout << "> : " << (((*myNovaList)[i-1] > (*myNovaList)[i]) == 1 ? "True" : "False") << endl;
                cout << "< : " << (((*myNovaList)[i-1] < (*myNovaList)[i]) == 1 ? "True" : "False") << endl;
                cout << ">= : " << (((*myNovaList)[i-1] >= (*myNovaList)[i]) == 1 ? "True" : "False") << endl;
                cout << "<= : " << (((*myNovaList)[i-1] <= (*myNovaList)[i]) == 1 ? "True" : "False") << endl;
                cout << "==(post): " << (((*myNovaList)[i-1] == ((*myNovaList)[i])++) == 1 ? "True" : "False") << endl;
                cout << "==(pre): " << (((*myNovaList)[i-1] == (++(*myNovaList)[i])) == 1 ? "True" : "False") << endl;
                cout << "!= : " << (((*myNovaList)[i-1] != (*myNovaList)[i]) == 1 ? "True" : "False") << endl;
        }       
    }
    (*myNovaList)[0]+=(*myNovaList)[1];
    (*myNovaList)[1]+(*myNovaList)[2];
    (*myNovaList)[3]+= ((lumen(30, 21, 2000)++) + (++(20+lumen(30, 21, 2000))));
    (*myNovaList)[4]++;
    lumen t1 = lumen(30, 21, 1000);
    lumen t2 = lumen(30, 24, 1020);
    lumen t3 = lumen(31, 14, 1030);

    cout << "lumens:" << endl;
    cout << "> : " << ((t1 > t2) == 1 ? "True" : "False") << endl;
    cout << "< : " << ((t2 < t3) == 1 ? "True" : "False") << endl;
    cout << ">= : " << ((t1 >= t3) == 1 ? "True" : "False") << endl;
    cout << "<= : " << ((t1 <= t2) == 1 ? "True" : "False") << endl;
    cout << "==(post): " << ((t1 == t2++) == 1 ? "True" : "False") << endl;
    cout << "==(pre): " << ((t3 == t2) == 1 ? "True" : "False") << endl;
    cout << "!= : " << ((t2 != t3) == 1 ? "True" : "False") << endl;
    return 0;
}



