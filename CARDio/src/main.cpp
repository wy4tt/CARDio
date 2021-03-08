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
        double looper = 10000;
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

        int ridx = 0;
        int howMany = 0;
        double readTotal = 0;

        while (myFile.available())
        {
            char c;
            int idx = 0;
            char word[34];

            // Get starting timepoint
            auto readStart = high_resolution_clock::now();
            while ((c = myFile.read()) != '\n')
            {
                word[idx++] = c;
            }
            // Get ending timepoint
            auto readStop = high_resolution_clock::now();
            auto readDuration = duration_cast<microseconds>(readStop - readStart);
            readTotal += readDuration.count();

            // Serial.printf("\t%s", word);
            howMany++;
            if (strcmp(word, randoStrings[ridx++].c_str()) == 0)
            {
                if (ridx == 25)
                {
                    ridx = 0;
                }
            }
            else
            {
                Serial.printf("\tString number %d or \"%s\" was not a match\n", howMany, word);
                failureState();
            }
        }
        double averageReadTime = readTotal / howMany;

        Serial.printf("\tAll %d strings matched\n", howMany);
        Serial.printf("\tAverage read time per string (microseconds): %f\n", averageReadTime);
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