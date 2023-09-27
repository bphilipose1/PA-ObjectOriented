/*
Benjamin Philipose, 3/30/2023, Version 1
Unit Tester
*/
using System;

namespace UnitTester    {
    class Tester
    {
        static void Main(string[] args)
        {
            Lumen flashLight1 = new Lumen(90, 160, 250);
            Lumen flashLight2 = new Lumen(90, 160, 250);
            
            using (StreamWriter logger = new StreamWriter("UnitTesterlog.txt", true))
            {            
            resetTest(flashLight1, logger);
            logger.WriteLine("Toggling, isActive: " + flashLight1.toggleActive());
            resetTest(flashLight1, logger);

            stateTest(flashLight2, logger);
            }
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