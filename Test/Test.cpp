#include "VoiceIt2.hpp"
#include <iostream>
#include <string>
#include <stdio.h>
#include <cstdio>
#include <curl/curl.h>
#include <curl/easy.h>
#include <string>

void AssertEquals(std::string arg1, std::string arg2, std::string line) {
  if (arg1 != arg2) {
    std::cout << arg1 + " does not equal " + arg2 + " on line " + line << std::endl;
    exit(1);
  }
}

void AssertEquals(int arg1, int arg2, std::string line) {
  if (arg1 != arg2) {
    std::cout << std::to_string(arg1) + " does not equal " + std::to_string(arg2) + " on line " + line << std::endl;
    exit(1);
  }
}

size_t write_data(void *ptr, size_t size, size_t nmemb, FILE *stream) {
    size_t written;
    written = fwrite(ptr, size, nmemb, stream);
    return written;
}

void DownloadFile(std::string destination, std::string source) {

    CURL *curl;
    FILE *fp;
    CURLcode res;
    std::string url = source;
    // char outfilename[FILENAME_MAX] = destination;
    char outfilename[destination.length()];
    strcpy(outfilename, destination.c_str());
    curl = curl_easy_init();
    if (curl) {
        fp = fopen(outfilename,"wb");
        curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, write_data);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, fp);
        res = curl_easy_perform(curl);
        curl_easy_cleanup(curl);
        fclose(fp);
    }

}

int main() {
  VoiceIt2 v(getenv("VIAPIKEY"), getenv("VIAPITOKEN"));
  json ret;

  // Test Basics
  ret = v.CreateUser();
  AssertEquals(201, ret["status"], std::to_string(__LINE__));
  AssertEquals("SUCC", ret["responseCode"], std::to_string(__LINE__));
  std::string userId = ret["userId"];

  ret = v.GetAllUsers();
  AssertEquals(200, ret["status"], std::to_string(__LINE__));
  AssertEquals("SUCC", ret["responseCode"], std::to_string(__LINE__));

  ret = v.CheckUserExists(userId);
  AssertEquals(200, ret["status"], std::to_string(__LINE__));
  AssertEquals("SUCC", ret["responseCode"], std::to_string(__LINE__));

  ret = v.CreateGroup("Sample Group Description");
  AssertEquals(201, ret["status"], std::to_string(__LINE__));
  AssertEquals("SUCC", ret["responseCode"], std::to_string(__LINE__));
  std::string groupId = ret["groupId"];

  ret = v.GetAllGroups();
  AssertEquals(200, ret["status"], std::to_string(__LINE__));
  AssertEquals("SUCC", ret["responseCode"], std::to_string(__LINE__));

  ret = v.CheckGroupExists(groupId);
  AssertEquals(200, ret["status"], std::to_string(__LINE__));
  AssertEquals("SUCC", ret["responseCode"], std::to_string(__LINE__));

  ret = v.GetGroup(groupId);
  AssertEquals(200, ret["status"], std::to_string(__LINE__));
  AssertEquals("SUCC", ret["responseCode"], std::to_string(__LINE__));

  ret = v.GetGroup(groupId);
  AssertEquals(200, ret["status"], std::to_string(__LINE__));
  AssertEquals("SUCC", ret["responseCode"], std::to_string(__LINE__));

  ret = v.AddUserToGroup(groupId, userId);
  AssertEquals(200, ret["status"], std::to_string(__LINE__));
  AssertEquals("SUCC", ret["responseCode"], std::to_string(__LINE__));

  ret = v.GetGroupsForUser(userId);
  AssertEquals(200, ret["status"], std::to_string(__LINE__));
  AssertEquals("SUCC", ret["responseCode"], std::to_string(__LINE__));

  ret = v.RemoveUserFromGroup(groupId, userId);
  AssertEquals(200, ret["status"], std::to_string(__LINE__));
  AssertEquals("SUCC", ret["responseCode"], std::to_string(__LINE__));

  ret = v.DeleteUser(userId);
  AssertEquals(200, ret["status"], std::to_string(__LINE__));
  AssertEquals("SUCC", ret["responseCode"], std::to_string(__LINE__));

  ret = v.DeleteGroup(groupId);
  AssertEquals(200, ret["status"], std::to_string(__LINE__));
  AssertEquals("SUCC", ret["responseCode"], std::to_string(__LINE__));
  std::cout << "****Test Basics All Passed****" << std::endl;


  // Test Video
  ret = v.CreateUser();
  std::string userId1 = ret["userId"];
  ret = v.CreateUser();
  std::string userId2 = ret["userId"];
  ret = v.CreateGroup("Sample Group Description");
  groupId = ret["groupId"];
  v.AddUserToGroup(groupId, userId1);
  v.AddUserToGroup(groupId, userId2);

  // Video Enrollments

  DownloadFile("./videoEnrollmentArmaan1.mov", "https://s3.amazonaws.com/voiceit-api2-testing-files/test-data/videoEnrollmentArmaan1.mov");
  DownloadFile("./videoEnrollmentArmaan2.mov", "https://s3.amazonaws.com/voiceit-api2-testing-files/test-data/videoEnrollmentArmaan2.mov");
  DownloadFile("./videoEnrollmentArmaan3.mov", "https://s3.amazonaws.com/voiceit-api2-testing-files/test-data/videoEnrollmentArmaan3.mov");
  DownloadFile("./videoVerificationArmaan1.mov", "https://s3.amazonaws.com/voiceit-api2-testing-files/test-data/videoVerificationArmaan1.mov");
  DownloadFile("./videoEnrollmentStephen1.mov", "https://s3.amazonaws.com/voiceit-api2-testing-files/test-data/videoEnrollmentStephen1.mov");
  DownloadFile("./videoEnrollmentStephen2.mov", "https://s3.amazonaws.com/voiceit-api2-testing-files/test-data/videoEnrollmentStephen2.mov");
  DownloadFile("./videoEnrollmentStephen3.mov", "https://s3.amazonaws.com/voiceit-api2-testing-files/test-data/videoEnrollmentStephen3.mov");
  
  ret = v.CreateVideoEnrollment(userId1, "en-US", "./videoEnrollmentArmaan1.mov");
  AssertEquals(201, ret["status"], std::to_string(__LINE__));
  AssertEquals("SUCC", ret["responseCode"], std::to_string(__LINE__));
  int enrollmentId1 = ret["id"];
  ret = v.CreateVideoEnrollment(userId1, "en-US", "./videoEnrollmentArmaan2.mov");
  AssertEquals(201, ret["status"], std::to_string(__LINE__));
  AssertEquals("SUCC", ret["responseCode"], std::to_string(__LINE__));
  int enrollmentId2 = ret["id"];
  ret = v.CreateVideoEnrollment(userId1, "en-US", "./videoEnrollmentArmaan3.mov");
  AssertEquals(201, ret["status"], std::to_string(__LINE__));
  AssertEquals("SUCC", ret["responseCode"], std::to_string(__LINE__));
  int enrollmentId3 = ret["id"];


  ret = v.CreateVideoEnrollment(userId2, "en-US", "./videoEnrollmentStephen1.mov");
  AssertEquals(201, ret["status"], std::to_string(__LINE__));
  AssertEquals("SUCC", ret["responseCode"], std::to_string(__LINE__));
  ret = v.CreateVideoEnrollment(userId2, "en-US", "./videoEnrollmentStephen2.mov");
  AssertEquals(201, ret["status"], std::to_string(__LINE__));
  AssertEquals("SUCC", ret["responseCode"], std::to_string(__LINE__));
  ret = v.CreateVideoEnrollment(userId2, "en-US", "./videoEnrollmentStephen3.mov");
  AssertEquals(201, ret["status"], std::to_string(__LINE__));
  AssertEquals("SUCC", ret["responseCode"], std::to_string(__LINE__));

  // Video Verification
  ret = v.VideoVerification(userId1, "en-US", "./videoVerificationArmaan1.mov");
  AssertEquals(200, ret["status"], std::to_string(__LINE__));
  AssertEquals("SUCC", ret["responseCode"], std::to_string(__LINE__));

  // Video Identification
  ret = v.VideoIdentification(groupId, "en-US", "./videoVerificationArmaan1.mov");
  AssertEquals(200, ret["status"], std::to_string(__LINE__));
  AssertEquals("SUCC", ret["responseCode"], std::to_string(__LINE__));
  AssertEquals(userId1, ret["userId"], std::to_string(__LINE__));

  // Get All Enrollments for User
  ret = v.GetAllEnrollmentsForUser(userId1);
  AssertEquals(200, ret["status"], std::to_string(__LINE__));
  AssertEquals("SUCC", ret["responseCode"], std::to_string(__LINE__));

  // Delete Enrollment for User
  ret = v.DeleteEnrollmentForUser(userId1, enrollmentId1);
  AssertEquals(200, ret["status"], std::to_string(__LINE__));
  AssertEquals("SUCC", ret["responseCode"], std::to_string(__LINE__));

  ret = v.DeleteEnrollmentForUser(userId1, enrollmentId2);
  AssertEquals(200, ret["status"], std::to_string(__LINE__));
  AssertEquals("SUCC", ret["responseCode"], std::to_string(__LINE__));

  ret = v.DeleteEnrollmentForUser(userId1, enrollmentId3);
  AssertEquals(200, ret["status"], std::to_string(__LINE__));
  AssertEquals("SUCC", ret["responseCode"], std::to_string(__LINE__));

  // Delete All Enrollments for User
  ret = v.DeleteAllEnrollmentsForUser(userId2);
  AssertEquals(200, ret["status"], std::to_string(__LINE__));
  AssertEquals("SUCC", ret["responseCode"], std::to_string(__LINE__));

  // Reset for ...ByUrl operations
  v.DeleteUser(userId1);
  v.DeleteUser(userId2);
  v.DeleteGroup(groupId);
  ret = v.CreateUser();
  userId1 = ret["userId"];
  ret = v.CreateUser();
  userId2 = ret["userId"];
  ret = v.CreateGroup("Sample Group Description");
  groupId = ret["groupId"];
  v.AddUserToGroup(groupId, userId1);
  v.AddUserToGroup(groupId, userId2);

  // Video Enrollment By URL
  ret = v.CreateVideoEnrollmentByUrl(userId1, "en-US", "https://s3.amazonaws.com/voiceit-api2-testing-files/test-data/videoEnrollmentArmaan1.mov");
  AssertEquals(201, ret["status"], std::to_string(__LINE__));
  AssertEquals("SUCC", ret["responseCode"], std::to_string(__LINE__));
  ret = v.CreateVideoEnrollmentByUrl(userId1, "en-US", "https://s3.amazonaws.com/voiceit-api2-testing-files/test-data/videoEnrollmentArmaan2.mov");
  AssertEquals(201, ret["status"], std::to_string(__LINE__));
  AssertEquals("SUCC", ret["responseCode"], std::to_string(__LINE__));
  ret = v.CreateVideoEnrollmentByUrl(userId1, "en-US", "https://s3.amazonaws.com/voiceit-api2-testing-files/test-data/videoEnrollmentArmaan3.mov");
  AssertEquals(201, ret["status"], std::to_string(__LINE__));
  AssertEquals("SUCC", ret["responseCode"], std::to_string(__LINE__));
  ret = v.CreateVideoEnrollmentByUrl(userId2, "en-US", "https://s3.amazonaws.com/voiceit-api2-testing-files/test-data/videoEnrollmentStephen1.mov");
  AssertEquals(201, ret["status"], std::to_string(__LINE__));
  AssertEquals("SUCC", ret["responseCode"], std::to_string(__LINE__));
  ret = v.CreateVideoEnrollmentByUrl(userId2, "en-US", "https://s3.amazonaws.com/voiceit-api2-testing-files/test-data/videoEnrollmentStephen2.mov");
  AssertEquals(201, ret["status"], std::to_string(__LINE__));
  AssertEquals("SUCC", ret["responseCode"], std::to_string(__LINE__));
  ret = v.CreateVideoEnrollmentByUrl(userId2, "en-US", "https://s3.amazonaws.com/voiceit-api2-testing-files/test-data/videoEnrollmentStephen3.mov");
  AssertEquals(201, ret["status"], std::to_string(__LINE__));
  AssertEquals("SUCC", ret["responseCode"], std::to_string(__LINE__));


  // Video Verification By URL
  ret = v.VideoVerificationByUrl(userId1, "en-US", "https://s3.amazonaws.com/voiceit-api2-testing-files/test-data/videoVerificationArmaan1.mov");
  AssertEquals(200, ret["status"], std::to_string(__LINE__));
  AssertEquals("SUCC", ret["responseCode"], std::to_string(__LINE__));

  // Video Identification By URL
  ret = v.VideoIdentificationByUrl(groupId, "en-US", "https://s3.amazonaws.com/voiceit-api2-testing-files/test-data/videoVerificationArmaan1.mov");
  AssertEquals(200, ret["status"], std::to_string(__LINE__));
  AssertEquals("SUCC", ret["responseCode"], std::to_string(__LINE__));
  AssertEquals(userId1, ret["userId"], std::to_string(__LINE__));

  v.DeleteAllEnrollmentsForUser(userId1);
  v.DeleteAllEnrollmentsForUser(userId2);
  v.DeleteUser(userId1);
  v.DeleteUser(userId2);
  v.DeleteGroup(groupId);

  remove("./videoEnrollmentArmaan1.mov");
  remove("./videoEnrollmentArmaan2.mov");
  remove("./videoEnrollmentArmaan3.mov");
  remove("./videoVerificationArmaan1.mov");
  remove("./videoEnrollmentStephen1.mov");
  remove("./videoEnrollmentStephen2.mov");
  remove("./videoEnrollmentStephen3.mov");

  std::cout << "****Test Video All Passed****" << std::endl;


  // Test Voice


  ret = v.CreateUser();
  userId1 = ret["userId"];
  ret = v.CreateUser();
  userId2 = ret["userId"];
  ret = v.CreateGroup("Sample Group Description");
  groupId = ret["groupId"];
  v.AddUserToGroup(groupId, userId1);
  v.AddUserToGroup(groupId, userId2);

  // Voice Enrollments

  DownloadFile("./enrollmentArmaan1.wav", "https://s3.amazonaws.com/voiceit-api2-testing-files/test-data/enrollmentArmaan1.wav");
  DownloadFile("./enrollmentArmaan2.wav", "https://s3.amazonaws.com/voiceit-api2-testing-files/test-data/enrollmentArmaan2.wav");
  DownloadFile("./enrollmentArmaan3.wav", "https://s3.amazonaws.com/voiceit-api2-testing-files/test-data/enrollmentArmaan3.wav");
  DownloadFile("./verificationArmaan1.wav", "https://s3.amazonaws.com/voiceit-api2-testing-files/test-data/verificationArmaan1.wav");
  DownloadFile("./enrollmentStephen1.wav", "https://s3.amazonaws.com/voiceit-api2-testing-files/test-data/enrollmentStephen1.wav");
  DownloadFile("./enrollmentStephen2.wav", "https://s3.amazonaws.com/voiceit-api2-testing-files/test-data/enrollmentStephen2.wav");
  DownloadFile("./enrollmentStephen3.wav", "https://s3.amazonaws.com/voiceit-api2-testing-files/test-data/enrollmentStephen3.wav");
  
  ret = v.CreateVoiceEnrollment(userId1, "en-US", "./enrollmentArmaan1.wav");
  AssertEquals(201, ret["status"], std::to_string(__LINE__));
  AssertEquals("SUCC", ret["responseCode"], std::to_string(__LINE__));
  ret = v.CreateVoiceEnrollment(userId1, "en-US", "./enrollmentArmaan2.wav");
  AssertEquals(201, ret["status"], std::to_string(__LINE__));
  AssertEquals("SUCC", ret["responseCode"], std::to_string(__LINE__));
  ret = v.CreateVoiceEnrollment(userId1, "en-US", "./enrollmentArmaan3.wav");
  AssertEquals(201, ret["status"], std::to_string(__LINE__));
  AssertEquals("SUCC", ret["responseCode"], std::to_string(__LINE__));


  ret = v.CreateVoiceEnrollment(userId2, "en-US", "./enrollmentStephen1.wav");
  AssertEquals(201, ret["status"], std::to_string(__LINE__));
  AssertEquals("SUCC", ret["responseCode"], std::to_string(__LINE__));
  ret = v.CreateVoiceEnrollment(userId2, "en-US", "./enrollmentStephen2.wav");
  AssertEquals(201, ret["status"], std::to_string(__LINE__));
  AssertEquals("SUCC", ret["responseCode"], std::to_string(__LINE__));
  ret = v.CreateVoiceEnrollment(userId2, "en-US", "./enrollmentStephen3.wav");
  AssertEquals(201, ret["status"], std::to_string(__LINE__));
  AssertEquals("SUCC", ret["responseCode"], std::to_string(__LINE__));

  // Voice Verification
  ret = v.VoiceVerification(userId1, "en-US", "./verificationArmaan1.wav");
  AssertEquals(200, ret["status"], std::to_string(__LINE__));
  AssertEquals("SUCC", ret["responseCode"], std::to_string(__LINE__));

  // Voice Identification
  ret = v.VoiceIdentification(groupId, "en-US", "./verificationArmaan1.wav");
  AssertEquals(200, ret["status"], std::to_string(__LINE__));
  AssertEquals("SUCC", ret["responseCode"], std::to_string(__LINE__));
  AssertEquals(userId1, ret["userId"], std::to_string(__LINE__));

  // Get All Enrollments for User
  ret = v.GetAllEnrollmentsForUser(userId1);
  AssertEquals(200, ret["status"], std::to_string(__LINE__));
  AssertEquals("SUCC", ret["responseCode"], std::to_string(__LINE__));

  // Reset for ...ByUrl operations
  v.DeleteAllEnrollmentsForUser(userId1);
  v.DeleteAllEnrollmentsForUser(userId2);
  v.DeleteUser(userId1);
  v.DeleteUser(userId2);
  v.DeleteGroup(groupId);
  ret = v.CreateUser();
  userId1 = ret["userId"];
  ret = v.CreateUser();
  userId2 = ret["userId"];
  ret = v.CreateGroup("Sample Group Description");
  groupId = ret["groupId"];
  v.AddUserToGroup(groupId, userId1);
  v.AddUserToGroup(groupId, userId2);

  // Voice Enrollment By URL
  ret = v.CreateVoiceEnrollmentByUrl(userId1, "en-US", "https://s3.amazonaws.com/voiceit-api2-testing-files/test-data/enrollmentArmaan1.wav");
  AssertEquals(201, ret["status"], std::to_string(__LINE__));
  AssertEquals("SUCC", ret["responseCode"], std::to_string(__LINE__));
  ret = v.CreateVoiceEnrollmentByUrl(userId1, "en-US", "https://s3.amazonaws.com/voiceit-api2-testing-files/test-data/enrollmentArmaan2.wav");
  AssertEquals(201, ret["status"], std::to_string(__LINE__));
  AssertEquals("SUCC", ret["responseCode"], std::to_string(__LINE__));
  ret = v.CreateVoiceEnrollmentByUrl(userId1, "en-US", "https://s3.amazonaws.com/voiceit-api2-testing-files/test-data/enrollmentArmaan3.wav");
  AssertEquals(201, ret["status"], std::to_string(__LINE__));
  AssertEquals("SUCC", ret["responseCode"], std::to_string(__LINE__));
  ret = v.CreateVoiceEnrollmentByUrl(userId2, "en-US", "https://s3.amazonaws.com/voiceit-api2-testing-files/test-data/enrollmentStephen1.wav");
  AssertEquals(201, ret["status"], std::to_string(__LINE__));
  AssertEquals("SUCC", ret["responseCode"], std::to_string(__LINE__));
  ret = v.CreateVoiceEnrollmentByUrl(userId2, "en-US", "https://s3.amazonaws.com/voiceit-api2-testing-files/test-data/enrollmentStephen2.wav");
  AssertEquals(201, ret["status"], std::to_string(__LINE__));
  AssertEquals("SUCC", ret["responseCode"], std::to_string(__LINE__));
  ret = v.CreateVoiceEnrollmentByUrl(userId2, "en-US", "https://s3.amazonaws.com/voiceit-api2-testing-files/test-data/enrollmentStephen3.wav");
  AssertEquals(201, ret["status"], std::to_string(__LINE__));
  AssertEquals("SUCC", ret["responseCode"], std::to_string(__LINE__));


  // Voice Verification By URL
  ret = v.VoiceVerificationByUrl(userId1, "en-US", "https://s3.amazonaws.com/voiceit-api2-testing-files/test-data/verificationArmaan1.wav");
  AssertEquals(200, ret["status"], std::to_string(__LINE__));
  AssertEquals("SUCC", ret["responseCode"], std::to_string(__LINE__));

  // Voice Identification By URL
  ret = v.VoiceIdentificationByUrl(groupId, "en-US", "https://s3.amazonaws.com/voiceit-api2-testing-files/test-data/verificationArmaan1.wav");
  AssertEquals(200, ret["status"], std::to_string(__LINE__));
  AssertEquals("SUCC", ret["responseCode"], std::to_string(__LINE__));
  AssertEquals(userId1, ret["userId"], std::to_string(__LINE__));

  v.DeleteAllEnrollmentsForUser(userId1);
  v.DeleteAllEnrollmentsForUser(userId2);
  v.DeleteUser(userId1);
  v.DeleteUser(userId2);
  v.DeleteGroup(groupId);

  remove("./enrollmentArmaan1.wav");
  remove("./enrollmentArmaan2.wav");
  remove("./enrollmentArmaan3.wav");
  remove("./verificationArmaan1.wav");
  remove("./enrollmentStephen1.wav");
  remove("./enrollmentStephen2.wav");
  remove("./enrollmentStephen3.wav");

  std::cout << "****Test Voice All Passed****" << std::endl;


  // Test Face

  ret = v.CreateUser();
  userId = ret["userId"];


  // Face Enrollments
  DownloadFile("./faceEnrollmentArmaan1.mp4", "https://s3.amazonaws.com/voiceit-api2-testing-files/test-data/faceEnrollmentArmaan1.mp4");
  DownloadFile("./faceEnrollmentArmaan2.mp4", "https://s3.amazonaws.com/voiceit-api2-testing-files/test-data/faceEnrollmentArmaan2.mp4");
  DownloadFile("./faceEnrollmentArmaan3.mp4", "https://s3.amazonaws.com/voiceit-api2-testing-files/test-data/faceEnrollmentArmaan3.mp4");
  DownloadFile("./faceVerificationArmaan1.mp4", "https://s3.amazonaws.com/voiceit-api2-testing-files/test-data/faceVerificationArmaan1.mp4");

  
  ret = v.CreateFaceEnrollment(userId, "./faceEnrollmentArmaan1.mp4");
  AssertEquals(201, ret["status"], std::to_string(__LINE__));
  AssertEquals("SUCC", ret["responseCode"], std::to_string(__LINE__));
  int faceEnrollmentId1 = ret["faceEnrollmentId"];
  ret = v.CreateFaceEnrollment(userId, "./faceEnrollmentArmaan2.mp4");
  AssertEquals(201, ret["status"], std::to_string(__LINE__));
  AssertEquals("SUCC", ret["responseCode"], std::to_string(__LINE__));
  int faceEnrollmentId2 = ret["faceEnrollmentId"];
  ret = v.CreateFaceEnrollment(userId, "./faceEnrollmentArmaan3.mp4");
  AssertEquals(201, ret["status"], std::to_string(__LINE__));
  AssertEquals("SUCC", ret["responseCode"], std::to_string(__LINE__));
  int faceEnrollmentId3 = ret["faceEnrollmentId"];

  // Get All Face Enrollments for User
  ret = v.GetFaceEnrollmentsForUser(userId);
  AssertEquals(200, ret["status"], std::to_string(__LINE__));
  AssertEquals("SUCC", ret["responseCode"], std::to_string(__LINE__));

  // Face Verification
  ret = v.FaceVerification(userId, "./faceVerificationArmaan1.mp4");
  AssertEquals(200, ret["status"], std::to_string(__LINE__));
  AssertEquals("SUCC", ret["responseCode"], std::to_string(__LINE__));

  // Delete Face Enrollment
  ret = v.DeleteFaceEnrollment(userId, faceEnrollmentId1);
  AssertEquals(200, ret["status"], std::to_string(__LINE__));
  AssertEquals("SUCC", ret["responseCode"], std::to_string(__LINE__));

  ret = v.DeleteFaceEnrollment(userId, faceEnrollmentId2);
  AssertEquals(200, ret["status"], std::to_string(__LINE__));
  AssertEquals("SUCC", ret["responseCode"], std::to_string(__LINE__));

  ret = v.DeleteFaceEnrollment(userId, faceEnrollmentId3);
  AssertEquals(200, ret["status"], std::to_string(__LINE__));
  AssertEquals("SUCC", ret["responseCode"], std::to_string(__LINE__));

  v.DeleteUser(userId);

  remove("./faceEnrollmentArmaan1.mp4");
  remove("./faceEnrollmentArmaan2.mp4");
  remove("./faceEnrollmentArmaan3.mp4");
  remove("./faceVerificationArmaan1.mp4");
  std::cout << "****Test Face All Passed****" << std::endl;
}

