#pragma once

#include <iostream>
#include <sys/statvfs.h>
#include <unistd.h>
#include <fcntl.h>
#include <random>
using namespace std;

class SPE {
    private:
        string disk; // name of disk to erase

        unsigned long size; // size of disk
        struct statvfs space;

        void run_with_random(); // fill disk with random 0 or 1

    public:
        explicit SPE(string diskName);
        ~SPE();

        void main();
};
