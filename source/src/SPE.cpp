#include "../include/SPE.h"
#include "../include/EraseALL.h"

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

    // starting random machine
    random_device rng;
    mt19937 gen(rng());
    uniform_int_distribution<int> uniform_dist(1, RAND_MAX);

    char rand[4000000] = {0};
    for (long unsigned int i = 0; i < (size/4000000); ++i) {
        for (auto &x : rand){
            x = (char) ((uniform_dist(gen) > RAND_MAX/2) ? 0 : 255);
        }
        write(file,&rand, sizeof(rand)* sizeof(char));
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