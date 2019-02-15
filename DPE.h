#pragma once

#include <iostream>
#include <sys/statvfs.h>
#include <unistd.h>
#include <fcntl.h>
#include <random>
using namespace std;

class DPE {
    private:
        string disk; // name of disk to erase

        unsigned long size; // size of disk
        struct statvfs space;

        void run_with_0(); // fill disk with 0
        void run_with_1(); // fill disk with 1
    public:
        explicit DPE(string disk);
        ~DPE();

        void main();
};
