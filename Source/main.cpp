#include <iostream>
#include <unistd.h>
#include <filesystem>

#include "DOD522022M.h"
#include "DOD522022MECE.h"
#include "DPE.h"
#include "SPE.h"

#include "EraseALL.h"

using namespace std;

/*
    command from terminal
    ./securewipe [drive] -op [option]

    [drive] = disk1

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
*/

int main(int argc, char * argv[]) {
    // clear the screen
    system("clear");

    //command line variables
    string disk;
    string option;

    //check and fill commandline argument
    if(argc == 4){
        if(stoi(argv[3]) > 5 || stoi(argv[3]) < 0){ // check if op is invalid
            cout << "Please see README.md for commandline options\n";
            cout << "ERROR : commandline argument op invalid, must be 1,2,3,4,5\n";
            exit(102);
        }
        disk = argv[1];
        option = argv[3];
    }else if(argc == 2){
        disk = argv[1];
        option = argv[0];
    }else{
        cout << "Please see README.md for commandline options\n";
        cout << "ERROR : commandline argument error\n";
        exit(100);
    }

    //confirming erasing, 3 times
    for (int i = 0; i < 3; ++i) {
        string confirm;
        cout << "You are about to erase " << disk << ", this operation will completely erase your Drive." << endl;
        cout << "Do you wish to continue? [Y/n] :";
        cin >> confirm;
        if (confirm != "Y" && confirm != "y") {
            cout << "***ABORTED***" << endl; // user abort program
            cout << "ERROR : User Aborted\n";
            exit(101);
        } else {
            // continue
            system("clear");
        }
    }


    // erase the drive
    EraseALL *eraseALL = new EraseALL(disk);
    eraseALL->erase();
    delete eraseALL;

    /* TODO: check if directory is empty, if not, exit, current implementation using filesystem is not working
    string path = "/dev/" + disk;
    std::filesystem::path p1 = path.c_str();
    if(std::filesystem::is_empty(p1)){
        //continue
    }else{ // not empty == exit
        cout << "ERROR : diskutil erase could not erase and reformat drive, maybe some process is using it";
        exit(103);
    }
     */


    //start erasing
    if(stoi(option) == 1){
        DOD522022M *srubber = new DOD522022M(disk);
        cout << "Start erasing " << disk << " with standard DOD5220.22-M protocol..." << endl;
        srubber->main();
        delete srubber;
    }else if(stoi(option) == 2){
        DOD522022MECE *srubber = new DOD522022MECE(disk);
        cout << "Start erasing " << disk << " with standard DOD5220.22-M ECE protocol..." << endl;
        srubber->main();
        delete srubber;
    }else if(stoi(option) == 3) {
        DOD522022M *srubber = new DOD522022M(disk);
        cout << "Start erasing " << disk << " with standard DOD5220.22-M ECE protocol running twice..." << endl;
        cout << "Run 1 started...";
        srubber->main();
        cout << "Run 2 started...";
        srubber->main();
        delete srubber;
    }else if(stoi(option) == 4){
        DPE *srubber = new DPE(disk);
        cout << "Start erasing " << disk << " with Double Pass Erasing..." << endl;
        srubber->main();
        delete srubber;
    }else if(stoi(option) == 5){
        SPE *srubber = new SPE(disk);
        cout << "Start erasing " << disk << " with Single Pass Erasing..." << endl;
        srubber->main();
        delete srubber;
    }else{
        DOD522022M *srubber = new DOD522022M(disk);
        cout << "Start erasing " << disk << " with standard DOD5220.22-M protocol..." << endl;
        srubber->main();
        delete srubber;
    }

    //done
    return 0;
}