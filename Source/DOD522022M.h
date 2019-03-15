#pragma once

#include <iostream>
#include <sys/statvfs.h>
#include <unistd.h>
#include <fcntl.h>
#include <random>
using namespace std;

class DOD522022M {
    private:
        string disk; // name of disk to erase

        unsigned long size; // size of disk
        struct statvfs space;

        void run_with_0(); // fill disk with 0
        void run_with_1(); // fill disk with 1
        void run_with_random(); // fill disk with random 0 or 1

    public:
        explicit DOD522022M(string diskName);
        ~DOD522022M();

        void main();
};
