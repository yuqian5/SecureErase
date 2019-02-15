#include "DOD522022MECE.h"
#include "EraseALL.h"

DOD522022MECE::DOD522022MECE(string diskName) {
    disk = std::move(diskName);

    //get free space size
    statvfs("/Volumes/SECUREERASE", &space);
    cout << "Disk Size = " << space.f_frsize * space.f_bavail << "Bytes" << endl;
    size =  space.f_frsize * space.f_bavail;

    chdir("/Volumes/SECUREERASE");
}

DOD522022MECE::~DOD522022MECE() = default;

void DOD522022MECE::run_with_0() {
    cout << "Starting '0' pass" << endl;
    system("touch run0"); //create file to write to
    int file = open("run0",O_WRONLY);

    char zero[4000000] = {0};
    for (long unsigned int i = 0; i < (size/4000000); ++i) {
        write(file,&zero, sizeof(zero)* sizeof(char));
    }

    close(file);

    remove("run0"); // remove file
}

void DOD522022MECE::run_with_1() {
    cout << "Starting '1' pass" << endl;
    system("touch run1"); //create file to write to
    int file = open("run1",O_WRONLY);

    char zero[4000000] = {0};
    for (auto &x : zero){
        x = 17; // 17 in hex = 11
    }
    for (long unsigned int i = 0; i < (size/4000000); ++i) {
        write(file,&zero, sizeof(zero)* sizeof(char));
    }

    close(file);

    remove("run1"); // remove file
}

void DOD522022MECE::run_with_01() {
    cout << "Starting '01' pass" << endl;
    system("touch run01"); //create file to write to
    int file = open("run01",O_WRONLY);

    char zero[4000000] = {0};
    for (auto &x : zero){
        x = 1;
    }
    for (long unsigned int i = 0; i < (size/4000000); ++i) {
        write(file,&zero, sizeof(zero)* sizeof(char));
    }

    close(file);

    remove("run01"); // remove file
}

void DOD522022MECE::run_with_random() {
    cout << "Starting 'random' pass" << endl;
    system("touch runrandom"); //create file to write to
    int file = open("runrandom",O_WRONLY);

    char zero[4000000] = {0};
    for (long unsigned int i = 0; i < (size/4000000); ++i) {
        for (auto &x : zero){
            x = (char) ((random() > RAND_MAX/2) ? 0 : 17);
        }
        write(file,&zero, sizeof(zero)* sizeof(char));
    }

    close(file);

    remove("runrandom"); // remove file
}

void DOD522022MECE::main() {
    // srubbing process
    run_with_0();
    run_with_1();
    run_with_random();
    run_with_01();
    run_with_0();
    run_with_1();
    run_with_random();

    //reformat drive
    EraseALL eraseALL(disk);
    eraseALL.erase();
}
