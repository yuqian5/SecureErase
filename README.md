# DiskScrubber

Only work on MacOS since I'm using the disk_ulti to format the drive before secure earse.
May add Linux & Windows Support later.


## Compile using make
   
Require GNU g++, not clang. So make sure you links are set right.

    To change compiler, complete the following change in makefile:
    CHANGE CC := g++-8 TO CC := [compiler you want]

## Command from terminal
    ./scrub [drive] -op [option]

    [drive] ex: disk1 or disk2

    -op 1 = standard DOD 5220.22-M
        run1:0 run2:1 run3:random
    -op 2 = DOD 5220.22-M ECE
        standard DOD 5220.22-M done twice with the middle run writing 01
    -op 3 = 14 pass erase
        DOD 5220.22-M ECE done twice
    -op 4 = double pass eases
        run1: 0 run2: 1
    -op 5 single pass random eases
        run1: random

## Error Codes
Code 100 : commandline argument error

Code 101 : User Aborted

Code 102 : commandline argument op invalid, must be 1,2,3,4,5

Code 103 : diskutil erase could not erase and reformat drive, maybe some process is using it
