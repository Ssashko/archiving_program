#include <iostream>
#include <memory>
#include "archive.hpp"

int main(int argc, char* argv[])
{
    if(argc != 4)
    {
        std::cerr << "invalid arguments, expected operation flag (-c | -d), location and destination)\n";
        return -1;
    }
    std::string location(argv[2]);
    std::string destination(argv[3]);
    std::string op(argv[1]);

    try {
        std::unique_ptr<IArchive> arh = std::make_unique<ZlibArchive>(location);

        if(op == "-compress" || op == "-c")
            arh->Compress();
        else if(op == "-decompress" | op == "-d")
            arh->Decompress();
        else
            {
                std::cerr << "invalid operation: " << op;
                return -2;
            }
        arh->SaveTo(destination);
    }
    catch(const std::exception &ex)
    {
        std::cerr << ex.what();
        return -3;
    }
    return 0;
}