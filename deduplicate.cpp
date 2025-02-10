#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <filesystem>
#include <openssl/sha.h>

#define ERROR(message)                     \
    do                                     \
    {                                      \
        std::cerr << message << std::endl; \
        return -1;                         \
    } while (0)

const std::size_t chunk_size = 4096;

int main(int argc, char *argv[])
{
    if (argc > 3)
    {
        ERROR("Too many arguments provided!");
    }
    else if (argc < 3)
    {
        ERROR("Not enough arguments provided!");
    }

    std::string initial_memdump_path = argv[1];
    std::string malicious_memdump_path = argv[2];

    std::ifstream initial_memdump_file(initial_memdump_path, std::ios::binary);
    if (!initial_memdump_file)
    {
        ERROR("Initial memory file does not exist or path is invalid!");
    }

    std::ifstream malicious_memdump_file(malicious_memdump_path, std::ios::binary);
    if (!malicious_memdump_file)
    {
        ERROR("Malicious memory file does not exists or path is invalid!");
    }

    // We assume memory dump files has the same size, since they are the same memory in different time points
    if (std::filesystem::file_size(initial_memdump_path) != std::filesystem::file_size(malicious_memdump_path))
    {
        ERROR("Size of the two dumps are not equal! Might not be the memory of the same computer!");
    }

    char initial_buffer[chunk_size];
    char malicious_buffer[chunk_size];

    while (
        (initial_memdump_file.read(initial_buffer, chunk_size) && malicious_memdump_file.read(malicious_buffer, chunk_size)) ||
        (initial_memdump_file.gcount() > 0 && malicious_memdump_file.gcount() > 0))
    {

    }

    initial_memdump_file.close();
    malicious_memdump_file.close();

    return 0;
}
