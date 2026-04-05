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

    std::cout << "CreateUser: " << vi.CreateUser() << std::endl;
    std::cout << "GetAllUsers: " << vi.GetAllUsers() << std::endl;
    std::cout << "CreateGroup: " << vi.CreateGroup("Test Group") << std::endl;
    std::cout << "GetAllGroups: " << vi.GetAllGroups() << std::endl;
    std::cout << "GetPhrases: " << vi.GetPhrases("en-US") << std::endl;

    std::cout << "\nAll API calls completed successfully!" << std::endl;
    return 0;
}
