#pragma once

#include <iostream>
#include <sys/statvfs.h>
#include <unistd.h>
#include <fcntl.h>
#include <random>
using namespace std;

class DOD522022MECE {
    private:
        string disk; // name of disk to erase

        unsigned long size; // size of disk
        struct statvfs space;

        void run_with_0();
        void run_with_1();
        void run_with_01();
        void run_with_random();

    public:
        explicit DOD522022MECE(string diskName);
        ~DOD522022MECE();

        void main();
};

