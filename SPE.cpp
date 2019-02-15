#include "SPE.h"
#include "EraseALL.h"

SPE::SPE(string diskName) {
    disk = std::move(diskName);

    //get free space size
    statvfs("/Volumes/SECUREERASE", &space);
    cout << "Disk Size = " << space.f_frsize * space.f_bavail << "Bytes" << endl;
    size =  space.f_frsize * space.f_bavail;

    chdir("/Volumes/SECUREERASE");
}

SPE::~SPE() = default;

void SPE::run_with_random() {
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

    remove("runrandom"); // remove the file
}

void SPE::main() {
    // srubbing process
    run_with_random();

    //reformat drive
    EraseALL eraseALL(disk);
    eraseALL.erase();
}