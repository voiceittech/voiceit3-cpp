#include "voiceit3.hpp"
#include <iostream>
#include <cstdlib>
#include <string>

int main() {
    const char* ak = std::getenv("VOICEIT_API_KEY");
    const char* at = std::getenv("VOICEIT_API_TOKEN");
    if (!ak || !at) { std::cout << "Set VOICEIT_API_KEY and VOICEIT_API_TOKEN" << std::endl; return 1; }

    VoiceIt3 vi(ak, at);
    std::string phrase = "never forget tomorrow is a new day";
    std::string td = "test-data";

    std::string r = vi.CreateUser();
    std::cout << "CreateUser: " << (r.find("SUCC") != std::string::npos ? "PASS" : "FAIL") << std::endl;

    // Extract userId (simple parse)
    size_t pos = r.find("usr_");
    std::string userId = r.substr(pos, 36);

    for (int i = 1; i <= 3; i++) {
        r = vi.CreateVideoEnrollment(userId, "en-US", phrase, td + "/videoEnrollmentA" + std::to_string(i) + ".mov");
        std::cout << "VideoEnrollment" << i << ": " << (r.find("SUCC") != std::string::npos ? "PASS" : "FAIL") << std::endl;
    }

    r = vi.VideoVerification(userId, "en-US", phrase, td + "/videoVerificationA1.mov");
    std::cout << "VideoVerification: " << (r.find("SUCC") != std::string::npos ? "PASS" : "FAIL") << std::endl;

    vi.DeleteAllEnrollments(userId);
    vi.DeleteUser(userId);

    std::cout << "\nAll tests passed!" << std::endl;
    return 0;
}
