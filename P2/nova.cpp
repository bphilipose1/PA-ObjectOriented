/*
Benjamin Philipose, 4/13/2023
Version P2 - Created Nova Class
Nova Class Implementation File
*/
#include "nova.h"
#include <algorithm>
using namespace std;
nova::nova(int randInput1, int randInput2, int totalLumens) : size(totalLumens) {
    maximumGlow = -101;
    minimumGlow = -101;

    if(randInput1 <= 0) {
        randInput1 = randInput1*-1 + 1;
    }
    if(randInput2 <= 0) {
        randInput2 = randInput2*-1 + 1;
    }

    randLumenNum = randInput1 + randInput2;
    LumenList = new lumen*[size];
    for(int i = 0; i < size; i++)  {
        LumenList[i] = makeLumen(randInput1, randInput2);
    }
}

nova::nova(const nova& inputNova)    {
    copy(inputNova);
}

nova& nova::operator=(const nova& inputNova)  {
    if(this == &inputNova)    {
        return *this;
    }

    for (int i = 0; i < size; i++) {
        delete LumenList[i];
    }
    delete[] LumenList;

    copy(inputNova);
    return *this;

}

nova::nova(nova&& inputNova)    {
    size = inputNova.size;
    minimumGlow = inputNova.minimumGlow;
    maximumGlow = inputNova.maximumGlow;
    randLumenNum = inputNova.randLumenNum;
    LumenList = inputNova.LumenList;

    inputNova.size = 0;
    inputNova.LumenList = nullptr;  
}

nova& nova::operator=(nova&& inputNova) {
    minimumGlow = inputNova.minimumGlow;
    maximumGlow = inputNova.maximumGlow;
    randLumenNum = inputNova.randLumenNum;
    swap(size, inputNova.size);
    swap(LumenList, inputNova.LumenList);

    return *this;
}
      
nova::~nova()   {
    for (int i = 0; i < size; i++) {
        delete LumenList[i];
    }
    delete[] LumenList;
}

void nova::glow(int numGlow)  {
    if(numGlow < 0) {
        numGlow*=-1;
    }
    if(numGlow == 0)    {
        return;
    }

    attemptReplaceLumen();
    int glowAmnt =  ((numGlow) % size) + 1;
    double* glowResp = new double[glowAmnt];
    for(int i = 0; i < glowAmnt; i++)   {
        glowResp[i] = LumenList[i]->glow();
    }
    findMinMax(glowResp, glowAmnt);

    delete[] glowResp;
    
}

double nova::reset(int numGlow) {
    if(numGlow < 0) {
        numGlow*=-1;
    }

    double glowAmnt =  ((numGlow) % size) + 1;
    if(glowAmnt == 0)   {
        return 0;
    }
    int successCount = 0;
    for(int i = 0; i < glowAmnt; i++)   {
        if(LumenList[i]->reset())   {
            successCount++;
        }
    }
    
    double retVal = successCount/glowAmnt;
    return retVal;
}

double nova::getMinimum()   {
    return minimumGlow;
}

double nova::getMaximum()   {
    return maximumGlow;
}

lumen* nova::makeLumen(int x, int y)   {
    int minVal = 10;
    randLumenNum += (x + y + minVal);
    int incre1 = x * randLumenNum;
    int incre2 = (x + y) * randLumenNum;
    int incre3 = y * randLumenNum;
    int tempBright = minVal + incre1 % MAX_BRIGHTNESS;
    int tempsize = minVal + incre2 % MAX_SIZE;
    int tempPower = (minVal*minVal) + (incre3 % MAX_POWER);
    lumen* tempLum = new lumen(tempBright, tempsize, tempPower);
    randLumenNum += minVal;

    return tempLum;
}
 
void nova::attemptReplaceLumen()   {
    int x = 55;
    int y = 77;
    int randInc = x + y;
    for(int i = 0; i < size; i++)   {
        if(!(LumenList[i]->isStable())) {
            x += randInc;
            y += randInc/2;
            delete LumenList[i];
            LumenList[i] = makeLumen(x, y);
        }
    }
}

void nova::rechargeLumens() {
    for(int i = 0; i < size; i++)  {
        LumenList[i]->recharge();
    }
}

bool nova::attemptRecharge() {
    int activeCount = 0;
    attemptReplaceLumen();
    for(int i = 0; i < size; i++)   {
        if(LumenList[i]->isActive()) {
            activeCount++;
        }
    }

    if(activeCount < (size/2.0)) {
        rechargeLumens();
        return true;
    }
    return false;
}

void nova::findMinMax(double* inputArr, int size)    {
    int minVal = 0;
    int maxVal = 0;
    for (int i = 0; i < size; i++) {
        if(i == 0)  {
            minVal = inputArr[i];
            maxVal = inputArr[i];
        }
        if (inputArr[i] < minVal) {
            minVal = inputArr[i];
        }
        if (inputArr[i] > maxVal) {
            maxVal = inputArr[i];
        }
    }
    minimumGlow = minVal;
    maximumGlow = maxVal;

}

void nova::copy(const nova& inputNova)  {
    size = inputNova.size;
    minimumGlow = inputNova.minimumGlow;
    maximumGlow = inputNova.maximumGlow;
    randLumenNum = inputNova.randLumenNum; 
    LumenList = new lumen*[inputNova.size];
    for(int k = 0; k < size; k++)   {
        LumenList[k] = new lumen(*inputNova.LumenList[k]);
    }

}

