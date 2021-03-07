// #include <Arduino.h>
// #include "FS.h"
// #include "SD.h"
// #include "SPI.h"
// #include <iostream>
// #include <stdio.h>  /* printf, NULL */
// #include <stdlib.h> /* srand, rand */
// #include <time.h>   /* time */
// #include <string>
// using namespace std;
// // /** SPI chip select pin */
// // uint8_t const SD_CHIP_SELECT_PIN = 5;
// // /** SPI Master Out Slave In pin */
// // uint8_t const SPI_MOSI_PIN = 23;
// // /** SPI Master In Slave Out pin */
// // uint8_t const SPI_MISO_PIN = 19; // 12;
// // /** SPI Clock pin */
// // uint8_t const SPI_SCK_PIN = 18; // 13;
// void initSerial();
// void initSD();
// void fileOps(bool open);
// void storeTwentyFiveToMemory(string (&randoStrings)[25]);
// string heckingMakeRandoString();
// void writeToSD(string (&randoStrings)[25]);
// void readFromSD(string (&randoStrings)[25]);
// void failureState();
// // here is the file object for writing to and from the SD card
// File myFile;
// void setup()
// {
//   string randoStrings[25];
//   // init srand
//   srand(time(NULL));
//   initSerial();
//   initSD();
//   fileOps(true);
//   storeTwentyFiveToMemory(randoStrings);
//   writeToSD(randoStrings);
//   readFromSD(randoStrings);
// }
// // makes serial communication possible
// void initSerial()
// {
//   Serial.begin(115200);
//   Serial.println("Step 1/N ✅: Serial initialization complete\n\n");
// }
// // Initializes the SD card to allow read/write access
// void initSD()
// {
//   Serial.println("Step 2/N 🎬: Starting SD card initialization");
//   if (!SD.begin(5))
//   {
//     Serial.printf("error: %s\n", strerror(errno));
//     Serial.println("Step 2/N ❌: SD card initialization failed");
//     Serial.println("Step 2/N ❌: Aborting");
//     failureState();
//   }
//   Serial.println("Step 2/N ✅: SD card initialization complete\n\n");
// }
// // Opens the file with R/W access or closes it
// // May need to pass by reference ???
// void fileOps(bool open)
// {
//   Serial.printf("Step 3/N 🎬: Starting to %s the SD card\n", open ? "open" : "close");
//   if (open)
//   {
//     myFile = SD.open("/test.txt");
//     myFile = SD.open("/test.txt");
//     Serial.printf("Step 3/N ✅: File successfully %s\n\n\n", open ? "opened" : "closed");
//   }
//   else
//   {
//     myFile.close();
//     Serial.printf("Step 3/N ✅: File successfully %s\n\n\n", open ? "opened" : "closed");
//   }
// }
// // take the array and generate 25 random strings, one for each index
// void storeTwentyFiveToMemory(string (&randoStrings)[25])
// {
//   Serial.println("Step 4/N 🎬: Storing 25 random strings into memory\n");
//   for (int i = 0; i < 25; i++)
//   {
//     randoStrings[i] = heckingMakeRandoString();
//   }
//   Serial.println("Step 4/N ✅: All 25 strings have been generated & stored in memory!\n\n");
// }
// // make a random string of length 34
// string heckingMakeRandoString()
// {
//   Serial.println("Step 5/N 🎬: Generating random string of length 34");
//   string buffer = "**********************************";
//   int size = 34;
//   const char charset[] = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ1234567890";
//   for (size_t n = 0; n < size; n++)
//   {
//     int key = rand() % (int)(sizeof charset - 1);
//     buffer[n] = charset[key];
//   }
//   buffer[size] = '\0';
//   Serial.printf("Step 5/N 👍: Thar she be -> \"%s\"\n", buffer.c_str());
//   Serial.println("Step 5/N ✅: Random string successfully generated\n");
//   return buffer;
// }
// void writeToSD(string (&randoStrings)[25])
// {
//   Serial.println("Step 6/N 🎬: Starting to write 250,000 strings!\n");
//   int i, j, count = 0;
//   // write this sequence of 25 string to the card 10,000 times hehe
//   for (i = 0; i < 10000; i -= -1)
//   {
//     for (j = 0; j < 25; j -= -1)
//     {
//       if (myFile)
//       {
//         myFile.println("stuff");
//         count -= -1;
//       }
//       else
//       {
//         Serial.println("Step 6/N ❌: Writing to the SD card failed");
//         if (i != 0 && j != 0)
//         {
//           Serial.printf("Step 6/N ❌: Only %d random strings got written", count);
//         }
//         else
//         {
//           Serial.println("Step 6/N ❌: File may be broken since no strings were written");
//         }
//         Serial.println("Step 6/N ❌: Aborting");
//         failureState();
//       }
//     }
//   }
//   // close the file
//   fileOps(false);
//   Serial.println("Step 6/N ✅: Finished writing the 250,000 strings!\n\n");
// }
// void readFromSD(string (&randoStrings)[25])
// {
//   Serial.println("Step 7/N 🎬: Starting to read back the 250,000 strings!");
//   // open the file
//   fileOps(true);
//   int i, j = 0;
//   string compareMe;
//   if (myFile)
//   {
//     while (myFile.available())
//     {
//       compareMe = myFile.readString().c_str();
//       Serial.printf("%s vs %s \n", compareMe, randoStrings[i]);
//       if (compareMe != randoStrings[i])
//       {
//         failureState();
//       }
//       i = (i == 24) ? 0 : i++;
//       j -= -1;
//     }
//     if (j != 250000)
//     {
//       Serial.println("failing");
//       failureState();
//     }
//     fileOps(false);
//   }
// }
// // end destination for when stuff hits the fan
// void failureState()
// {
//   Serial.println("☠️☠️☠️ Something went terribly wrong ☠️☠️☠️");
//   Serial.println("Program aborted");
// }
// void loop()
// {
// }

#include <Arduino.h>
#include "FS.h"
#include "SD.h"
#include "SPI.h"
#include <iostream>
#include <stdio.h>  /* printf, NULL */
#include <stdlib.h> /* srand, rand */
#include <time.h>   /* time */
#include <string>

#include <algorithm>
#include <chrono>

using namespace std;
using namespace std::chrono;

File myFile;
string randoStrings[25];

void failureState();
string heckingMakeRandoString();

void setup()
{
    // Open serial communications and wait for port to open:
    Serial.begin(115200);
    Serial.println("\nStep 1: Bringing serial comms online");
    while (Serial.available())
    {
        ;
    }
    Serial.println("Step 1: Done");

    // init srand
    Serial.println("\nStep 2: Initializing randomness factor");
    srand(time(NULL));
    Serial.println("Step 2: Done");

    // init the SD
    Serial.println("\nStep 3: Initializing SD card");
    if (!SD.begin(5))
    {
        Serial.println("\tSD card initialization failed");
        failureState();
    }
    Serial.println("Step 3: Done");

    // store the random strings to local device memory
    Serial.println("\nStep 4: Creating random strings and saving to memory");
    for (int i = 0; i < 25; i++)
    {
        randoStrings[i] = heckingMakeRandoString();
        Serial.printf("\t%s\n", randoStrings[i].c_str());
    }
    Serial.println("Step 4: Done");

    // open a file to be written to
    Serial.println("\nStep 5: Opening a txt file on the SD card");
    myFile = SD.open("/test.txt", FILE_WRITE);

    // if the file opened okay, write to it:
    if (myFile)
    {
        Serial.println("\tFile opened successfully");
        Serial.println("Step 5: Done");

        // start writing to the file
        double looper = 10;
        double writeTotal = 0;
        Serial.printf("\nStep 6: Writing %.0lf strings to file\n", looper * 25);

        for (int j = 0; j < looper; j++)
        {
            for (int i = 0; i < 25; i++)
            {
                // Get starting timepoint
                auto writeStart = high_resolution_clock::now();

                myFile.print(randoStrings[i].c_str());
                myFile.print("\n");

                // Get ending timepoint
                auto writeStop = high_resolution_clock::now();

                auto writeDuration = duration_cast<microseconds>(writeStop - writeStart);
                writeTotal += writeDuration.count();
            }
        }

        double averageWriteTime = writeTotal / (looper * 25.0);

        Serial.printf("\tAll %.0lf strings written\n", looper * 25);
        Serial.printf("\tAverage write time per string (microseconds): %f\n", averageWriteTime);
    }
    else
    {
        // if the file didn't open, print an error:
        Serial.println("\tUnable to open file");
        failureState();
    }
    Serial.println("Step 6: Done");

    // close the file:
    Serial.println("\nStep 7: Closing the file");
    myFile.close();
    Serial.println("Step 7: Done");

    // re-open the file for reading:
    Serial.println("\nStep 8: Re-opening the txt file");
    myFile = SD.open("/test.txt");
    if (myFile)
    {
        Serial.println("Step 8: Done");

        Serial.println("\nStep 9: Reading back all the strings to verify they match");
        while (myFile.available())
        {
            // char c;
            // string word;
            // c = myFile.read();
            //
            // if ((c != '\n') && (c != '\0'))
            // {
            //     // Serial.println(c);
            //     word[i] = c;
            //     i++;
            // }
            // else
            // {
            //     i = 0;
            // }
            // Serial.printf("\t%s\n", word.c_str());
            //
            // for (int i = 0; i < 35; i++)
            // {
            //     word[i] = myFile.read();
            // }
            // c = myFile.read();
            // c = myFile.read();
            // Serial.printf("\t%s\n", word.c_str());
        
            char c;
            int idx = 0;
            char word[34];

            while ((c = myFile.read()) != '\n')
            {
                word[idx++] = c;
            }
            Serial.printf("\t%s\n", word);
        }
    }
    else
    {
        // if the file didn't open, print an error:
        Serial.println("\tUnable to open file");
        failureState();
    }
    Serial.println("Step 9: Done");
}

void failureState()
{
    Serial.println("☠️☠️☠️ Something went terribly wrong ☠️☠️☠️");
    Serial.println("Program aborted");
    while (1)
    {
        ;
    }
}

// make a random string of length 34
string heckingMakeRandoString()
{
    string buffer = "**********************************";
    int size = 34;

    const char charset[] = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ1234567890";

    for (size_t n = 0; n < size; n++)
    {
        int key = rand() % (int)(sizeof charset - 1);
        buffer[n] = charset[key];
    }
    buffer[size] = '\0';

    return buffer;
}

void loop()
{
}