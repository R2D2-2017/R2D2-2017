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
    const char *imagepath = "/home/dorf/mutest.img";
    const char dingen[] = "shite";
    int size = sizeof(dingen);
    char dingen2[7];

    //const char



    MuStore::FileStore image(imagepath, true);
    MuStore::FatFs fileSystem(&image);
    MuStore::FsError err;
    MuStore::FsNode file = fileSystem.get("/data", err);
    if(!file.doesExist()){
        std::cout << "poep" << '\n';
    }
    file.write(dingen, size, err);

    if(err){
        std::cout << "error is " << (int)err << '\n';
    }

    file.rewind();

    file.read(dingen2, size, err);

    std::cout << dingen2 << '\n';



    return 0;
}
