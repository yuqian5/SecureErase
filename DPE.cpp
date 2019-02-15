#include "DPE.h"
#include "EraseALL.h"

DPE::DPE(string diskName) {
    disk = std::move(diskName);

    //get free space size
    statvfs("/Volumes/SECUREERASE", &space);
    cout << "Disk Size = " << space.f_frsize * space.f_bavail << "Bytes" << endl;
    size =  space.f_frsize * space.f_bavail;

    chdir("/Volumes/SECUREERASE");
}

DPE::~DPE() = default;

void DPE::run_with_0() {
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

void DPE::run_with_1() {
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

void DPE::main() {
    // srubbing process
    run_with_0();
    run_with_1();

    //reformat drive
    EraseALL eraseALL(disk);
    eraseALL.erase();
}
