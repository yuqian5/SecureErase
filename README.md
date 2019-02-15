Only work on MacOS, may add a Linux or windows version later.

Compile using make

command from terminal
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
