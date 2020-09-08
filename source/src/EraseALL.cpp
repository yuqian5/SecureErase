#pragma once

#include "../include/EraseALL.h"

EraseALL::EraseALL(string diskName){
    disk = std::move(diskName);
}

EraseALL::~EraseALL() = default;

void EraseALL::erase() {
    string command = "diskutil eraseDisk APFS SECUREERASE /dev/" + disk;
    system(command.c_str());
}
