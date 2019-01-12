import time
import os

FILENAME = "robot-config.h"
currentFileName = os.path.split(os.path.abspath(__file__))[0]
FILENAME = os.path.join(currentFileName, FILENAME)

trackerNum = 0
objectList = []
with open(FILENAME, "r") as tempFile:
    for line in tempFile:
        if line.startswith("vex::"):
            tempLine = line.split()
            objectList.append((tempLine[0][5:], tempLine[1]))
            
with open(os.path.join(currentFileName,"tempFile.txt"), "a") as outFile:
    outFile.seek(0)
    for obj in objectList:
        print obj
        outFile.write((obj[0]) + " " + obj[1])
        outFile.write("\n")
