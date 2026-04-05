#include "VoiceIt3.hpp"
#include <iostream>
#include <cstdlib>

// Test script for VoiceIt3 C++ SDK
// Build: g++ test_example.cpp -o test_example -lcurl
int main() {
    const char* apiKey = std::getenv("VOICEIT_API_KEY");
    const char* apiToken = std::getenv("VOICEIT_API_TOKEN");

    if (!apiKey || !apiToken) {
        std::cout << "Set VOICEIT_API_KEY and VOICEIT_API_TOKEN environment variables" << std::endl;
        return 1;
    }

    VoiceIt3 vi(apiKey, apiToken);

    std::cout << "CreateUser: " << vi.createUser() << std::endl;
    std::cout << "GetAllUsers: " << vi.getAllUsers() << std::endl;
    std::cout << "CreateGroup: " << vi.createGroup("Test Group") << std::endl;
    std::cout << "GetAllGroups: " << vi.getAllGroups() << std::endl;
    std::cout << "GetPhrases: " << vi.getPhrases("en-US") << std::endl;

    std::cout << "\nAll API calls completed successfully!" << std::endl;
    return 0;
}
