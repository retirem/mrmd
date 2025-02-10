#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <filesystem>
#include <iomanip>
#include <cstring>
#include <openssl/evp.h>

#define ERROR(message)                     \
    do                                     \
    {                                      \
        std::cerr << message << std::endl; \
        return -1;                         \
    } while (0)

const std::size_t chunk_size = 4096;
const std::size_t sha256_md_length = 32;

std::string sha256_local(const std::string& input) {
    EVP_MD_CTX* ctx = EVP_MD_CTX_new();
    if (!ctx) {
        throw std::runtime_error("Failed to create OpenSSL context");
    }

    const EVP_MD* md = EVP_sha256();
    unsigned char hash[EVP_MAX_MD_SIZE];
    unsigned int length = 0;

    if (!EVP_DigestInit_ex(ctx, md, nullptr) ||
        !EVP_DigestUpdate(ctx, input.c_str(), input.size()) ||
        !EVP_DigestFinal_ex(ctx, hash, &length)) {
        EVP_MD_CTX_free(ctx);
        throw std::runtime_error("Error computing SHA-256 hash");
    }

    EVP_MD_CTX_free(ctx);

    std::stringstream ss;
    for (unsigned int i = 0; i < length; i++) {
        ss << std::hex << std::setw(2) << std::setfill('0') << (int)hash[i];
    }
    return ss.str();
}

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

    char initial_buffer[chunk_size] = {0};
    char malicious_buffer[chunk_size] = {0};
    std::vector<char> dedup_memory; 

    while (
        (initial_memdump_file.read(initial_buffer, chunk_size) && malicious_memdump_file.read(malicious_buffer, chunk_size)) ||
        (initial_memdump_file.gcount() > 0 && malicious_memdump_file.gcount() > 0))
    {
        if (memcmp(sha256_local(initial_buffer).c_str(), sha256_local(malicious_buffer).c_str(), sha256_md_length) == 0) {
            std::vector<char> maliciour_part(malicious_buffer, malicious_buffer + malicious_memdump_file.gcount());
            dedup_memory.insert(dedup_memory.end(), maliciour_part.begin(), maliciour_part.begin() + malicious_memdump_file.gcount());
        }

        initial_buffer[chunk_size] = {0};
        malicious_buffer[chunk_size] = {0};
    }

    initial_memdump_file.close();
    malicious_memdump_file.close();

    return 0;
}
