/*
Benjamin Philipose, 3/30/2023, Version 1
Driver
*/
using System;

namespace Client    {
    class Driver
    {
        static void Main(string[] args)
        {
            int totalNumTestObj = 10;
            Random random = new Random();
            int [] brightnessArr = generateBrightnesses(totalNumTestObj, random);
            double [] sizeArr = generateSizes(totalNumTestObj, random);
            double [] powerArr = generatePowers(totalNumTestObj, random);
            Lumen[] lumenList = new Lumen[totalNumTestObj];

            using (StreamWriter logger = new StreamWriter("Driverlog.txt", true)) {
                for (int i = 0; i < lumenList.Length; i++)  {
                    lumenList[i] = new Lumen(brightnessArr[i], sizeArr[i], powerArr[i]);
                    logger.WriteLine("Creating Lumen#" + i + " | Brightness: " + brightnessArr[i] + " | Size: " + sizeArr[i] + " | Power: " + powerArr[i]);


                }
                for(int i = 0; i < totalNumTestObj; i++) {
                    logger.WriteLine("");
                    logger.WriteLine("---------------------Testing Lumen#" + i + "---------------------------");
                    bool testReset = random.Next(2) == 0;
                    bool testStates = random.Next(2) == 0;
                    bool toggle1 = random.Next(2) == 0;
                    bool toggle2 = random.Next(2) == 0;
                    if(testReset)   {
                        if(toggle1) {
                            logger.WriteLine("Toggling... isActive: " + lumenList[i].toggleActive());
                        }
                        resetTest(lumenList[i], logger);
                    }
                    if(testStates)   {
                        if(toggle2) {
                            logger.WriteLine("Toggling... isActive: " + lumenList[i].toggleActive());
                        }
                        stateTest(lumenList[i], logger);
                    }
                }   
            }
        }

        /*Create an array of random brightness values (int) ranging from 1-100*/
        static int[] generateBrightnesses(int totalAmnt, Random random)   {
            int[] brightnessArr = new int[totalAmnt];
            for (int i = 0; i < brightnessArr.Length; i++)  {
                brightnessArr[i] = random.Next(1, 101);
            }
            return brightnessArr;
        }
        /*Create an array of random size values (double) ranging from 1-100*/
        static double[] generateSizes(int totalAmnt, Random random)   {
            double[] sizeArr = new double[totalAmnt];
            for (int i = 0; i < sizeArr.Length; i++)    {
                sizeArr[i] = random.NextDouble() * 100;
            }
            return sizeArr;
        }
        /*Create an array of random Power values (double) ranging from 30-300*/
        static double[] generatePowers(int totalAmnt, Random random)   {
            double[] powerArr = new double[totalAmnt];
            for (int i = 0; i < powerArr.Length; i++)   {
                powerArr[i] = random.Next(30, 301);
            }
            return powerArr;
        }
        static void resetTest(Lumen testObject, StreamWriter writer) {
            //test Reset
            bool stop = false;
            int loopCount = 0;
            double glowRet = 0;
            writer.WriteLine("Starting Reset Test...");
            while(!stop)    {
                loopCount++;
                glowRet = testObject.glow();
                writer.Write("glow #" + loopCount + " | Returned: " + glowRet + " | Battery? " + testObject.checkBattery() + "% | Stablility? " + testObject.getIsStable());
                stop = testObject.reset();
                writer.WriteLine(" | Reset? " + stop);
                if(glowRet <= 0 || loopCount > 40) {
                    stop = true;
                }    
                if(stop)    {
                    glowRet = testObject.glow();
                    writer.WriteLine("glow #" + loopCount + " | Returned: " + glowRet + " | Battery? " + testObject.checkBattery() + "% | Stablility? " + testObject.getIsStable());
                }           
            }
        }
        static void getLowBattery(Lumen testObject) { 
            while(testObject.checkBattery() != 0)   {
                testObject.glow();
            }
        }
        static void stateTest(Lumen testObject, StreamWriter writer) {
            writer.WriteLine("Initiating State Testing...");
            writer.WriteLine("State 1: Object is now Stable and isActive? " + testObject.toggleActive() + " | Glow? " + testObject.glow());
            writer.WriteLine("State 2: Object is now Stable and isActive? " + testObject.toggleActive() + " | Glow? " + testObject.glow());
            getLowBattery(testObject);
            writer.WriteLine("State 3: Object is now Unstable and isActive? " + testObject.toggleActive() + " | Glow? " + testObject.glow());
            writer.WriteLine("State 4: Object is now Unstable and isActive? " + testObject.toggleActive() + " | Glow? " + testObject.glow());
        }
    }
}