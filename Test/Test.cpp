#include "VoiceIt2.hpp"
#include <iostream>
#include <string>
#include <stdio.h>
#include <cstdio>
#include <curl/curl.h>
#include <curl/easy.h>
#include <string>

void AssertEquals(std::string arg1, std::string arg2, std::string line, std::string message) {
  if (arg1 != arg2) {
    std::cerr << arg1 + " does not equal " + arg2 + " on line " + line << std::endl;
    std::cerr <<"message: " << message << std::endl;
    exit(1);
  }
}

void AssertEquals(int arg1, int arg2, std::string line, std::string message) {
  if (arg1 != arg2) {
    std::cerr << std::to_string(arg1) + " does not equal " + std::to_string(arg2) + " on line " + line << std::endl;
    std::cerr << "message: " << message << std::endl;
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

  // Test Webhooks
  v.AddNotificationUrl("https://voiceit.io");
  AssertEquals("https://voiceit.io", v.GetNotificationUrl(), std::to_string(__LINE__), ret.dump());
  v.RemoveNotificationUrl();
  AssertEquals("", v.GetNotificationUrl(), std::to_string(__LINE__), ret.dump());

  // Test IO Exceptions
  try {
    v.CreateVideoEnrollment("", "", "", "not_a_real_file");
    std::cerr << "File check for CreateVideoEnrollment() failed" << std::endl;
    exit(1);
  } catch(std::string msg) {
    std::cout << "File check for CreateVideoEnrollment() worked" << std::endl;
  }

  try {
    v.CreateVoiceEnrollment("", "", "", "not_a_real_file");
    std::cerr << "File check for CreateVoiceEnrollment() failed" << std::endl;
    exit(1);
  } catch(std::string msg) {
    std::cout << "File check for CreateVoiceEnrollment() worked" << std::endl;
  }

  try {
    v.CreateFaceEnrollment("", "not_a_real_file");
    std::cerr << "File check for CreateFaceEnrollment() failed" << std::endl;
    exit(1);
  } catch(std::string msg) {
    std::cout << "File check for CreateFaceEnrollment() worked" << std::endl;
  }

  try {
    v.VideoVerification("", "", "", "not_a_real_file");
    std::cerr << "File check for VideoVerification() failed" << std::endl;
    exit(1);
  } catch(std::string msg) {
    std::cout << "File check for VideoVerification() worked" << std::endl;
  }

  try {
    v.VoiceVerification("", "", "", "not_a_real_file");
    std::cerr << "File check for VoiceVerification() failed" << std::endl;
    exit(1);
  } catch(std::string msg) {
    std::cout << "File check for VoiceVerification() worked" << std::endl;
  }

  try {
    v.FaceVerification("", "not_a_real_file");
    std::cerr << "File check for FaceVerification() failed" << std::endl;
    exit(1);
  } catch(std::string msg) {
    std::cout << "File check for FaceVerification() worked" << std::endl;
  }

  try {
    v.VideoIdentification("", "", "", "not_a_real_file");
    std::cerr << "File check for VideoIdentification() failed" << std::endl;
    exit(1);
  } catch(std::string msg) {
    std::cout << "File check for VideoIdentification() worked" << std::endl;
  }

  try {
    v.VoiceIdentification("", "", "", "not_a_real_file");
    std::cerr << "File check for VoiceIdentification() failed" << std::endl;
    exit(1);
  } catch(std::string msg) {
    std::cout << "File check for VoiceIdentification() worked" << std::endl;
  }

  try {
    v.FaceIdentification("", "not_a_real_file");
    std::cerr << "File check for FaceIdentification() failed" << std::endl;
    exit(1);
  } catch(std::string msg) {
    std::cout << "File check for FaceIdentification() worked" << std::endl;
  }

  // Test Basics
  ret = v.CreateUser();
  AssertEquals(201, ret["status"], std::to_string(__LINE__), ret.dump());
  AssertEquals("SUCC", ret["responseCode"], std::to_string(__LINE__), ret.dump());
  std::string userId = ret["userId"];

  ret = v.GetAllUsers();
  AssertEquals(200, ret["status"], std::to_string(__LINE__), ret.dump());
  AssertEquals("SUCC", ret["responseCode"], std::to_string(__LINE__), ret.dump());

  ret = v.CheckUserExists(userId);
  AssertEquals(200, ret["status"], std::to_string(__LINE__), ret.dump());
  AssertEquals("SUCC", ret["responseCode"], std::to_string(__LINE__), ret.dump());

  ret = v.CreateGroup("Sample Group Description");
  AssertEquals(201, ret["status"], std::to_string(__LINE__), ret.dump());
  AssertEquals("SUCC", ret["responseCode"], std::to_string(__LINE__), ret.dump());
  std::string groupId = ret["groupId"];

  ret = v.GetAllGroups();
  AssertEquals(200, ret["status"], std::to_string(__LINE__), ret.dump());
  AssertEquals("SUCC", ret["responseCode"], std::to_string(__LINE__), ret.dump());

  ret = v.CheckGroupExists(groupId);
  AssertEquals(200, ret["status"], std::to_string(__LINE__), ret.dump());
  AssertEquals("SUCC", ret["responseCode"], std::to_string(__LINE__), ret.dump());

  ret = v.GetGroup(groupId);
  AssertEquals(200, ret["status"], std::to_string(__LINE__), ret.dump());
  AssertEquals("SUCC", ret["responseCode"], std::to_string(__LINE__), ret.dump());

  ret = v.GetGroup(groupId);
  AssertEquals(200, ret["status"], std::to_string(__LINE__), ret.dump());
  AssertEquals("SUCC", ret["responseCode"], std::to_string(__LINE__), ret.dump());

  ret = v.AddUserToGroup(groupId, userId);
  AssertEquals(200, ret["status"], std::to_string(__LINE__), ret.dump());
  AssertEquals("SUCC", ret["responseCode"], std::to_string(__LINE__), ret.dump());

  ret = v.GetGroupsForUser(userId);
  AssertEquals(200, ret["status"], std::to_string(__LINE__), ret.dump());
  AssertEquals("SUCC", ret["responseCode"], std::to_string(__LINE__), ret.dump());

  ret = v.RemoveUserFromGroup(groupId, userId);
  AssertEquals(200, ret["status"], std::to_string(__LINE__), ret.dump());
  AssertEquals("SUCC", ret["responseCode"], std::to_string(__LINE__), ret.dump());

  ret = v.CreateUserToken(userId, 10);
  AssertEquals(201, ret["status"], std::to_string(__LINE__), ret.dump());
  AssertEquals("SUCC", ret["responseCode"], std::to_string(__LINE__), ret.dump());

  ret = v.DeleteUser(userId);
  AssertEquals(200, ret["status"], std::to_string(__LINE__), ret.dump());
  AssertEquals("SUCC", ret["responseCode"], std::to_string(__LINE__), ret.dump());

  ret = v.DeleteGroup(groupId);
  AssertEquals(200, ret["status"], std::to_string(__LINE__), ret.dump());
  AssertEquals("SUCC", ret["responseCode"], std::to_string(__LINE__), ret.dump());

  ret = v.GetPhrases("en-US");
  AssertEquals(200, ret["status"], std::to_string(__LINE__), ret.dump());
  AssertEquals("SUCC", ret["responseCode"], std::to_string(__LINE__), ret.dump());
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
  
  ret = v.CreateVideoEnrollment(userId1, "en-US", "never forget tomorrow is a new day", "./videoEnrollmentArmaan1.mov");
  AssertEquals(201, ret["status"], std::to_string(__LINE__), ret.dump());
  AssertEquals("SUCC", ret["responseCode"], std::to_string(__LINE__), ret.dump());
  int enrollmentId1 = ret["id"];
  ret = v.CreateVideoEnrollment(userId1, "en-US", "never forget tomorrow is a new day", "./videoEnrollmentArmaan2.mov");
  AssertEquals(201, ret["status"], std::to_string(__LINE__), ret.dump());
  AssertEquals("SUCC", ret["responseCode"], std::to_string(__LINE__), ret.dump());
  int enrollmentId2 = ret["id"];
  ret = v.CreateVideoEnrollment(userId1, "en-US", "never forget tomorrow is a new day", "./videoEnrollmentArmaan3.mov");
  AssertEquals(201, ret["status"], std::to_string(__LINE__), ret.dump());
  AssertEquals("SUCC", ret["responseCode"], std::to_string(__LINE__), ret.dump());
  int enrollmentId3 = ret["id"];


  ret = v.CreateVideoEnrollment(userId2, "en-US", "never forget tomorrow is a new day", "./videoEnrollmentStephen1.mov");
  AssertEquals(201, ret["status"], std::to_string(__LINE__), ret.dump());
  AssertEquals("SUCC", ret["responseCode"], std::to_string(__LINE__), ret.dump());
  ret = v.CreateVideoEnrollment(userId2, "en-US", "never forget tomorrow is a new day", "./videoEnrollmentStephen2.mov");
  AssertEquals(201, ret["status"], std::to_string(__LINE__), ret.dump());
  AssertEquals("SUCC", ret["responseCode"], std::to_string(__LINE__), ret.dump());
  ret = v.CreateVideoEnrollment(userId2, "en-US", "never forget tomorrow is a new day", "./videoEnrollmentStephen3.mov");
  AssertEquals(201, ret["status"], std::to_string(__LINE__), ret.dump());
  AssertEquals("SUCC", ret["responseCode"], std::to_string(__LINE__), ret.dump());

  // Video Verification
  ret = v.VideoVerification(userId1, "en-US", "never forget tomorrow is a new day", "./videoVerificationArmaan1.mov");
  AssertEquals(200, ret["status"], std::to_string(__LINE__), ret.dump());
  AssertEquals("SUCC", ret["responseCode"], std::to_string(__LINE__), ret.dump());

  // Video Identification
  ret = v.VideoIdentification(groupId, "en-US", "never forget tomorrow is a new day", "./videoVerificationArmaan1.mov");
  AssertEquals(200, ret["status"], std::to_string(__LINE__), ret.dump());
  AssertEquals("SUCC", ret["responseCode"], std::to_string(__LINE__), ret.dump());
  AssertEquals(userId1, ret["userId"], std::to_string(__LINE__), ret.dump());

  // Delete All Enrollments
  ret = v.DeleteAllEnrollments(userId1);
  AssertEquals(200, ret["status"], std::to_string(__LINE__), ret.dump());
  AssertEquals("SUCC", ret["responseCode"], std::to_string(__LINE__), ret.dump());
  v.DeleteAllEnrollments(userId2);

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
  ret = v.CreateVideoEnrollmentByUrl(userId1, "en-US", "never forget tomorrow is a new day", "https://s3.amazonaws.com/voiceit-api2-testing-files/test-data/videoEnrollmentArmaan1.mov");
  AssertEquals(201, ret["status"], std::to_string(__LINE__), ret.dump());
  AssertEquals("SUCC", ret["responseCode"], std::to_string(__LINE__), ret.dump());
  ret = v.CreateVideoEnrollmentByUrl(userId1, "en-US", "never forget tomorrow is a new day", "https://s3.amazonaws.com/voiceit-api2-testing-files/test-data/videoEnrollmentArmaan2.mov");
  AssertEquals(201, ret["status"], std::to_string(__LINE__), ret.dump());
  AssertEquals("SUCC", ret["responseCode"], std::to_string(__LINE__), ret.dump());
  ret = v.CreateVideoEnrollmentByUrl(userId1, "en-US", "never forget tomorrow is a new day", "https://s3.amazonaws.com/voiceit-api2-testing-files/test-data/videoEnrollmentArmaan3.mov");
  AssertEquals(201, ret["status"], std::to_string(__LINE__), ret.dump());
  AssertEquals("SUCC", ret["responseCode"], std::to_string(__LINE__), ret.dump());
  ret = v.CreateVideoEnrollmentByUrl(userId2, "en-US", "never forget tomorrow is a new day", "https://s3.amazonaws.com/voiceit-api2-testing-files/test-data/videoEnrollmentStephen1.mov");
  AssertEquals(201, ret["status"], std::to_string(__LINE__), ret.dump());
  AssertEquals("SUCC", ret["responseCode"], std::to_string(__LINE__), ret.dump());
  ret = v.CreateVideoEnrollmentByUrl(userId2, "en-US", "never forget tomorrow is a new day", "https://s3.amazonaws.com/voiceit-api2-testing-files/test-data/videoEnrollmentStephen2.mov");
  AssertEquals(201, ret["status"], std::to_string(__LINE__), ret.dump());
  AssertEquals("SUCC", ret["responseCode"], std::to_string(__LINE__), ret.dump());
  ret = v.CreateVideoEnrollmentByUrl(userId2, "en-US", "never forget tomorrow is a new day", "https://s3.amazonaws.com/voiceit-api2-testing-files/test-data/videoEnrollmentStephen3.mov");
  AssertEquals(201, ret["status"], std::to_string(__LINE__), ret.dump());
  AssertEquals("SUCC", ret["responseCode"], std::to_string(__LINE__), ret.dump());


  // Video Verification By URL
  ret = v.VideoVerificationByUrl(userId1, "en-US", "never forget tomorrow is a new day", "https://s3.amazonaws.com/voiceit-api2-testing-files/test-data/videoVerificationArmaan1.mov");
  AssertEquals(200, ret["status"], std::to_string(__LINE__), ret.dump());
  AssertEquals("SUCC", ret["responseCode"], std::to_string(__LINE__), ret.dump());

  // Video Identification By URL
  ret = v.VideoIdentificationByUrl(groupId, "en-US", "never forget tomorrow is a new day", "https://s3.amazonaws.com/voiceit-api2-testing-files/test-data/videoVerificationArmaan1.mov");
  AssertEquals(200, ret["status"], std::to_string(__LINE__), ret.dump());
  AssertEquals("SUCC", ret["responseCode"], std::to_string(__LINE__), ret.dump());
  AssertEquals(userId1, ret["userId"], std::to_string(__LINE__), ret.dump());

  v.DeleteAllEnrollments(userId1);
  v.DeleteAllEnrollments(userId2);
  v.DeleteUser(userId1);
  v.DeleteUser(userId2);
  v.DeleteGroup(groupId);


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

  DownloadFile("./enrollmentNoel1.wav", "https://s3.amazonaws.com/voiceit-api2-testing-files/test-data/enrollmentNoel1.wav");
  DownloadFile("./enrollmentNoel2.wav", "https://s3.amazonaws.com/voiceit-api2-testing-files/test-data/enrollmentNoel2.wav");
  DownloadFile("./enrollmentNoel3.wav", "https://s3.amazonaws.com/voiceit-api2-testing-files/test-data/enrollmentNoel3.wav");
  DownloadFile("./verificationNoel1.wav", "https://s3.amazonaws.com/voiceit-api2-testing-files/test-data/verificationNoel1.wav");
  DownloadFile("./enrollmentStephen1.wav", "https://s3.amazonaws.com/voiceit-api2-testing-files/test-data/enrollmentStephen1.wav");
  DownloadFile("./enrollmentStephen2.wav", "https://s3.amazonaws.com/voiceit-api2-testing-files/test-data/enrollmentStephen2.wav");
  DownloadFile("./enrollmentStephen3.wav", "https://s3.amazonaws.com/voiceit-api2-testing-files/test-data/enrollmentStephen3.wav");
  
  ret = v.CreateVoiceEnrollment(userId1, "en-US", "never forget tomorrow is a new day", "./enrollmentNoel1.wav");
  AssertEquals(201, ret["status"], std::to_string(__LINE__), ret.dump());
  AssertEquals("SUCC", ret["responseCode"], std::to_string(__LINE__), ret.dump());
  ret = v.CreateVoiceEnrollment(userId1, "en-US", "never forget tomorrow is a new day", "./enrollmentNoel2.wav");
  AssertEquals(201, ret["status"], std::to_string(__LINE__), ret.dump());
  AssertEquals("SUCC", ret["responseCode"], std::to_string(__LINE__), ret.dump());
  ret = v.CreateVoiceEnrollment(userId1, "en-US", "never forget tomorrow is a new day", "./enrollmentNoel3.wav");
  AssertEquals(201, ret["status"], std::to_string(__LINE__), ret.dump());
  AssertEquals("SUCC", ret["responseCode"], std::to_string(__LINE__), ret.dump());


  ret = v.CreateVoiceEnrollment(userId2, "en-US", "never forget tomorrow is a new day", "./enrollmentStephen1.wav");
  AssertEquals(201, ret["status"], std::to_string(__LINE__), ret.dump());
  AssertEquals("SUCC", ret["responseCode"], std::to_string(__LINE__), ret.dump());
  ret = v.CreateVoiceEnrollment(userId2, "en-US", "never forget tomorrow is a new day", "./enrollmentStephen2.wav");
  AssertEquals(201, ret["status"], std::to_string(__LINE__), ret.dump());
  AssertEquals("SUCC", ret["responseCode"], std::to_string(__LINE__), ret.dump());
  ret = v.CreateVoiceEnrollment(userId2, "en-US", "never forget tomorrow is a new day", "./enrollmentStephen3.wav");
  AssertEquals(201, ret["status"], std::to_string(__LINE__), ret.dump());
  AssertEquals("SUCC", ret["responseCode"], std::to_string(__LINE__), ret.dump());

  // Voice Verification
  ret = v.VoiceVerification(userId1, "en-US", "never forget tomorrow is a new day", "./verificationNoel1.wav");
  AssertEquals(200, ret["status"], std::to_string(__LINE__), ret.dump());
  AssertEquals("SUCC", ret["responseCode"], std::to_string(__LINE__), ret.dump());

  // Voice Identification
  ret = v.VoiceIdentification(groupId, "en-US", "never forget tomorrow is a new day", "./verificationNoel1.wav");
  AssertEquals(200, ret["status"], std::to_string(__LINE__), ret.dump());
  AssertEquals("SUCC", ret["responseCode"], std::to_string(__LINE__), ret.dump());
  AssertEquals(userId1, ret["userId"], std::to_string(__LINE__), ret.dump());

  // Reset for ...ByUrl operations
  v.DeleteAllEnrollments(userId1);
  v.DeleteAllEnrollments(userId2);
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
  ret = v.CreateVoiceEnrollmentByUrl(userId1, "en-US", "never forget tomorrow is a new day", "https://s3.amazonaws.com/voiceit-api2-testing-files/test-data/enrollmentNoel1.wav");
  AssertEquals(201, ret["status"], std::to_string(__LINE__), ret.dump());
  AssertEquals("SUCC", ret["responseCode"], std::to_string(__LINE__), ret.dump());
  ret = v.CreateVoiceEnrollmentByUrl(userId1, "en-US", "never forget tomorrow is a new day", "https://s3.amazonaws.com/voiceit-api2-testing-files/test-data/enrollmentNoel2.wav");
  AssertEquals(201, ret["status"], std::to_string(__LINE__), ret.dump());
  AssertEquals("SUCC", ret["responseCode"], std::to_string(__LINE__), ret.dump());
  ret = v.CreateVoiceEnrollmentByUrl(userId1, "en-US", "never forget tomorrow is a new day", "https://s3.amazonaws.com/voiceit-api2-testing-files/test-data/enrollmentNoel3.wav");
  AssertEquals(201, ret["status"], std::to_string(__LINE__), ret.dump());
  AssertEquals("SUCC", ret["responseCode"], std::to_string(__LINE__), ret.dump());
  ret = v.CreateVoiceEnrollmentByUrl(userId2, "en-US", "never forget tomorrow is a new day", "https://s3.amazonaws.com/voiceit-api2-testing-files/test-data/enrollmentStephen1.wav");
  AssertEquals(201, ret["status"], std::to_string(__LINE__), ret.dump());
  AssertEquals("SUCC", ret["responseCode"], std::to_string(__LINE__), ret.dump());
  ret = v.CreateVoiceEnrollmentByUrl(userId2, "en-US", "never forget tomorrow is a new day", "https://s3.amazonaws.com/voiceit-api2-testing-files/test-data/enrollmentStephen2.wav");
  AssertEquals(201, ret["status"], std::to_string(__LINE__), ret.dump());
  AssertEquals("SUCC", ret["responseCode"], std::to_string(__LINE__), ret.dump());
  ret = v.CreateVoiceEnrollmentByUrl(userId2, "en-US", "never forget tomorrow is a new day", "https://s3.amazonaws.com/voiceit-api2-testing-files/test-data/enrollmentStephen3.wav");
  AssertEquals(201, ret["status"], std::to_string(__LINE__), ret.dump());
  AssertEquals("SUCC", ret["responseCode"], std::to_string(__LINE__), ret.dump());


  // Voice Verification By URL
  ret = v.VoiceVerificationByUrl(userId1, "en-US", "never forget tomorrow is a new day", "https://s3.amazonaws.com/voiceit-api2-testing-files/test-data/verificationNoel1.wav");
  AssertEquals(200, ret["status"], std::to_string(__LINE__), ret.dump());
  AssertEquals("SUCC", ret["responseCode"], std::to_string(__LINE__), ret.dump());

  // Voice Identification By URL
  ret = v.VoiceIdentificationByUrl(groupId, "en-US", "never forget tomorrow is a new day", "https://s3.amazonaws.com/voiceit-api2-testing-files/test-data/verificationNoel1.wav");
  AssertEquals(200, ret["status"], std::to_string(__LINE__), ret.dump());
  AssertEquals("SUCC", ret["responseCode"], std::to_string(__LINE__), ret.dump());
  AssertEquals(userId1, ret["userId"], std::to_string(__LINE__), ret.dump());

  v.DeleteAllEnrollments(userId1);
  v.DeleteAllEnrollments(userId2);
  v.DeleteUser(userId1);
  v.DeleteUser(userId2);
  v.DeleteGroup(groupId);


  std::cout << "****Test Voice All Passed****" << std::endl;

  // Test Face


  ret = v.CreateUser();
  userId1 = ret["userId"];
  ret = v.CreateUser();
  userId2 = ret["userId"];
  ret = v.CreateGroup("Sample Group Description");
  groupId = ret["groupId"];
  v.AddUserToGroup(groupId, userId1);
  v.AddUserToGroup(groupId, userId2);

  // Face Enrollments

  DownloadFile("./faceEnrollmentArmaan1.mp4", "https://s3.amazonaws.com/voiceit-api2-testing-files/test-data/faceEnrollmentArmaan1.mp4");
  DownloadFile("./faceEnrollmentArmaan2.mp4", "https://s3.amazonaws.com/voiceit-api2-testing-files/test-data/faceEnrollmentArmaan2.mp4");
  DownloadFile("./faceEnrollmentArmaan3.mp4", "https://s3.amazonaws.com/voiceit-api2-testing-files/test-data/faceEnrollmentArmaan3.mp4");
  DownloadFile("./faceVerificationArmaan1.mp4", "https://s3.amazonaws.com/voiceit-api2-testing-files/test-data/faceVerificationArmaan1.mp4");
  
  ret = v.CreateFaceEnrollment(userId1, "./faceEnrollmentArmaan1.mp4");
  AssertEquals(201, ret["status"], std::to_string(__LINE__), ret.dump());
  AssertEquals("SUCC", ret["responseCode"], std::to_string(__LINE__), ret.dump());
  ret = v.CreateFaceEnrollment(userId1, "./faceEnrollmentArmaan2.mp4");
  AssertEquals(201, ret["status"], std::to_string(__LINE__), ret.dump());
  AssertEquals("SUCC", ret["responseCode"], std::to_string(__LINE__), ret.dump());
  ret = v.CreateFaceEnrollment(userId1, "./faceEnrollmentArmaan3.mp4");
  AssertEquals(201, ret["status"], std::to_string(__LINE__), ret.dump());
  AssertEquals("SUCC", ret["responseCode"], std::to_string(__LINE__), ret.dump());


  ret = v.CreateFaceEnrollment(userId2, "./videoEnrollmentStephen1.mov");
  AssertEquals(201, ret["status"], std::to_string(__LINE__), ret.dump());
  AssertEquals("SUCC", ret["responseCode"], std::to_string(__LINE__), ret.dump());
  ret = v.CreateFaceEnrollment(userId2, "./videoEnrollmentStephen2.mov");
  AssertEquals(201, ret["status"], std::to_string(__LINE__), ret.dump());
  AssertEquals("SUCC", ret["responseCode"], std::to_string(__LINE__), ret.dump());
  ret = v.CreateFaceEnrollment(userId2, "./videoEnrollmentStephen3.mov");
  AssertEquals(201, ret["status"], std::to_string(__LINE__), ret.dump());
  AssertEquals("SUCC", ret["responseCode"], std::to_string(__LINE__), ret.dump());

  // Face Verification
  ret = v.FaceVerification(userId1, "./faceVerificationArmaan1.mp4");
  AssertEquals(200, ret["status"], std::to_string(__LINE__), ret.dump());
  AssertEquals("SUCC", ret["responseCode"], std::to_string(__LINE__), ret.dump());

  // Face Identification
  ret = v.FaceIdentification(groupId, "./faceVerificationArmaan1.mp4");
  AssertEquals(200, ret["status"], std::to_string(__LINE__), ret.dump());
  AssertEquals("SUCC", ret["responseCode"], std::to_string(__LINE__), ret.dump());
  AssertEquals(userId1, ret["userId"], std::to_string(__LINE__), ret.dump());
  

  // Reset for ...ByUrl operations
  v.DeleteAllEnrollments(userId1);
  v.DeleteAllEnrollments(userId2);
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

  // Face Enrollment By URL
  ret = v.CreateFaceEnrollmentByUrl(userId1, "https://s3.amazonaws.com/voiceit-api2-testing-files/test-data/faceEnrollmentArmaan1.mp4");
  AssertEquals(201, ret["status"], std::to_string(__LINE__), ret.dump());
  AssertEquals("SUCC", ret["responseCode"], std::to_string(__LINE__), ret.dump());
  ret = v.CreateFaceEnrollmentByUrl(userId1, "https://s3.amazonaws.com/voiceit-api2-testing-files/test-data/faceEnrollmentArmaan2.mp4");
  AssertEquals(201, ret["status"], std::to_string(__LINE__), ret.dump());
  AssertEquals("SUCC", ret["responseCode"], std::to_string(__LINE__), ret.dump());
  ret = v.CreateFaceEnrollmentByUrl(userId1, "https://s3.amazonaws.com/voiceit-api2-testing-files/test-data/faceEnrollmentArmaan3.mp4");
  AssertEquals(201, ret["status"], std::to_string(__LINE__), ret.dump());
  AssertEquals("SUCC", ret["responseCode"], std::to_string(__LINE__), ret.dump());
  ret = v.CreateFaceEnrollmentByUrl(userId2, "https://s3.amazonaws.com/voiceit-api2-testing-files/test-data/videoEnrollmentStephen1.mov");
  AssertEquals(201, ret["status"], std::to_string(__LINE__), ret.dump());
  AssertEquals("SUCC", ret["responseCode"], std::to_string(__LINE__), ret.dump());
  ret = v.CreateFaceEnrollmentByUrl(userId2, "https://s3.amazonaws.com/voiceit-api2-testing-files/test-data/videoEnrollmentStephen2.mov");
  AssertEquals(201, ret["status"], std::to_string(__LINE__), ret.dump());
  AssertEquals("SUCC", ret["responseCode"], std::to_string(__LINE__), ret.dump());
  ret = v.CreateFaceEnrollmentByUrl(userId2, "https://s3.amazonaws.com/voiceit-api2-testing-files/test-data/videoEnrollmentStephen3.mov");
  AssertEquals(201, ret["status"], std::to_string(__LINE__), ret.dump());
  AssertEquals("SUCC", ret["responseCode"], std::to_string(__LINE__), ret.dump());


  // Face Verification By URL
  ret = v.FaceVerificationByUrl(userId1, "https://s3.amazonaws.com/voiceit-api2-testing-files/test-data/faceVerificationArmaan1.mp4");
  AssertEquals(200, ret["status"], std::to_string(__LINE__), ret.dump());
  AssertEquals("SUCC", ret["responseCode"], std::to_string(__LINE__), ret.dump());

  // Face Identification By URL
  ret = v.FaceIdentificationByUrl(groupId, "https://s3.amazonaws.com/voiceit-api2-testing-files/test-data/faceVerificationArmaan1.mp4");
  AssertEquals(200, ret["status"], std::to_string(__LINE__), ret.dump());
  AssertEquals("SUCC", ret["responseCode"], std::to_string(__LINE__), ret.dump());
  AssertEquals(userId1, ret["userId"], std::to_string(__LINE__), ret.dump());

  v.DeleteAllEnrollments(userId1);
  v.DeleteAllEnrollments(userId2);
  v.DeleteUser(userId1);
  v.DeleteUser(userId2);
  v.DeleteGroup(groupId);


  std::cout << "****Test Face All Passed****" << std::endl;


  // Test Delete Enrollment
  ret = v.CreateUser()["userId"];
  userId = ret;
  int videoEnrollmentId = v.CreateVideoEnrollmentByUrl(userId, "en-US", "never forget tomorrow is a new day", "https://s3.amazonaws.com/voiceit-api2-testing-files/test-data/videoEnrollmentArmaan1.mov")["id"];
  v.CreateVideoEnrollmentByUrl(userId, "en-US", "never forget tomorrow is a new day", "https://s3.amazonaws.com/voiceit-api2-testing-files/test-data/videoEnrollmentArmaan2.mov");
  int voiceEnrollmentId = v.CreateVoiceEnrollmentByUrl(userId, "en-US", "never forget tomorrow is a new day", "https://s3.amazonaws.com/voiceit-api2-testing-files/test-data/enrollmentNoel1.wav")["id"];
  v.CreateVoiceEnrollmentByUrl(userId, "en-US", "never forget tomorrow is a new day", "https://s3.amazonaws.com/voiceit-api2-testing-files/test-data/enrollmentNoel2.wav");
  int faceEnrollmentId = v.CreateFaceEnrollment(userId, "./faceEnrollmentArmaan1.mp4")["faceEnrollmentId"];
  v.CreateFaceEnrollment(userId, "./faceEnrollmentArmaan2.mp4");

  ret = v.DeleteFaceEnrollment(userId, faceEnrollmentId);
  AssertEquals(200, ret["status"], std::to_string(__LINE__), ret.dump());
  AssertEquals("SUCC", ret["responseCode"], std::to_string(__LINE__), ret.dump());
  ret = v.DeleteVideoEnrollment(userId, videoEnrollmentId);
  AssertEquals(200, ret["status"], std::to_string(__LINE__), ret.dump());
  AssertEquals("SUCC", ret["responseCode"], std::to_string(__LINE__), ret.dump());
  ret = v.DeleteVoiceEnrollment(userId, voiceEnrollmentId);
  AssertEquals(200, ret["status"], std::to_string(__LINE__), ret.dump());
  AssertEquals("SUCC", ret["responseCode"], std::to_string(__LINE__), ret.dump());

  ret = v.GetAllVideoEnrollments(userId);
  AssertEquals(200, ret["status"], std::to_string(__LINE__), ret.dump());
  AssertEquals("SUCC", ret["responseCode"], std::to_string(__LINE__), ret.dump());
  AssertEquals(1, ret["count"], std::to_string(__LINE__), ret.dump());
  ret = v.GetAllVoiceEnrollments(userId);
  AssertEquals(200, ret["status"], std::to_string(__LINE__), ret.dump());
  AssertEquals("SUCC", ret["responseCode"], std::to_string(__LINE__), ret.dump());
  AssertEquals(1, ret["count"], std::to_string(__LINE__), ret.dump());
  ret = v.GetAllFaceEnrollments(userId);
  AssertEquals(200, ret["status"], std::to_string(__LINE__), ret.dump());
  AssertEquals("SUCC", ret["responseCode"], std::to_string(__LINE__), ret.dump());
  AssertEquals(1, ret["count"], std::to_string(__LINE__), ret.dump());

  v.DeleteAllEnrollments(userId);
  std::cout << "****Delete Enrollment All Passed****" << std::endl;
    
  // Test Delete Enrollments
  v.CreateVideoEnrollmentByUrl(userId, "en-US", "never forget tomorrow is a new day", "https://s3.amazonaws.com/voiceit-api2-testing-files/test-data/videoEnrollmentArmaan1.mov");
  v.CreateVideoEnrollmentByUrl(userId, "en-US", "never forget tomorrow is a new day", "https://s3.amazonaws.com/voiceit-api2-testing-files/test-data/videoEnrollmentArmaan2.mov");
  v.CreateVoiceEnrollmentByUrl(userId, "en-US", "never forget tomorrow is a new day", "https://s3.amazonaws.com/voiceit-api2-testing-files/test-data/enrollmentNoel1.wav");
  v.CreateVoiceEnrollmentByUrl(userId, "en-US", "never forget tomorrow is a new day", "https://s3.amazonaws.com/voiceit-api2-testing-files/test-data/enrollmentNoel2.wav");
  v.CreateFaceEnrollment(userId, "./faceEnrollmentArmaan1.mp4");
  v.CreateFaceEnrollment(userId, "./faceEnrollmentArmaan2.mp4");

  ret = v.DeleteAllVideoEnrollments(userId);
  AssertEquals(200, ret["status"], std::to_string(__LINE__), ret.dump());
  AssertEquals("SUCC", ret["responseCode"], std::to_string(__LINE__), ret.dump());
  ret = v.DeleteAllVoiceEnrollments(userId);
  AssertEquals(200, ret["status"], std::to_string(__LINE__), ret.dump());
  AssertEquals("SUCC", ret["responseCode"], std::to_string(__LINE__), ret.dump());
  ret = v.DeleteAllFaceEnrollments(userId);
  AssertEquals(200, ret["status"], std::to_string(__LINE__), ret.dump());
  AssertEquals("SUCC", ret["responseCode"], std::to_string(__LINE__), ret.dump());
  AssertEquals(0, v.GetAllVideoEnrollments(userId)["count"], std::to_string(__LINE__), ret.dump());
  AssertEquals(0, v.GetAllVoiceEnrollments(userId)["count"], std::to_string(__LINE__), ret.dump());
  AssertEquals(0, v.GetAllFaceEnrollments(userId)["count"], std::to_string(__LINE__), ret.dump());
  v.DeleteAllEnrollments(userId);
  v.DeleteUser(userId);

  std::cout << "****Delete All Video/Voice/Face Enrollments All Passed****" << std::endl;

  remove("./videoEnrollmentArmaan1.mov");
  remove("./videoEnrollmentArmaan2.mov");
  remove("./videoEnrollmentArmaan3.mov");
  remove("./videoVerificationArmaan1.mov");

  remove("./enrollmentNoel1.wav");
  remove("./enrollmentNoel2.wav");
  remove("./enrollmentNoel3.wav");
  remove("./verificationNoel1.wav");
  remove("./enrollmentStephen1.wav");
  remove("./enrollmentStephen2.wav");
  remove("./enrollmentStephen3.wav");

  remove("./faceEnrollmentArmaan1.mp4");
  remove("./faceEnrollmentArmaan2.mp4");
  remove("./faceEnrollmentArmaan3.mp4");
  remove("./faceVerificationArmaan1.mp4");
  remove("./videoEnrollmentStephen1.mov");
  remove("./videoEnrollmentStephen2.mov");
  remove("./videoEnrollmentStephen3.mov");
}
