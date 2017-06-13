/**
 * \file
 * \brief     INSERT A DESCRIPTION HERE
 * \author    INSERT YOUR NAME HERE
 * \copyright Copyright (c) 2017, The R2D2 Team
 * \license   See LICENSE
 */
#include <iostream>
#include <store.hh>
#include <filestore.hh>
#include <fatfs.hh>

int main(int argc, char **argv) {
    const char *imagepath = "/dev/mmcblk0p1";
    const char dingen[] = "kekzanzibar";
    int size = sizeof(dingen);
    const char text[] = "testext";
    char input[100] = "\0";



    MuStore::FileStore image(imagepath, true);
    MuStore::FatFs fileSystem(&image);
    MuStore::FsError err;


    MuStore::FsNode dataFile = fileSystem.get("/data.txt", err);
    std::cout << (int)err << '\n';
    MuStore::FsNode confFile = fileSystem.get("/conf.txt", err);
    std::cout << (int)err << '\n';

    if(!confFile.doesExist()){
        std::cout << "conf.txt does not exist" << '\n';
    }
    if(!dataFile.doesExist()){
        std::cout << "data.txt does not exist" << '\n';
    }


    confFile.read(input, 100, err);
    std::cout << input << '\n';
    err = dataFile.seek(dataFile.getSize());
    dataFile.write(dingen, size, err);
    std::cout << (int)err << '\n';
    return 0;
}
