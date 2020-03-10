#ifdef _WIN32
#include "pch.h"
#endif

#include "VoiceIt2.hpp"
#include "json.hpp"
#include <fstream>
#include <iostream>
#include <string>
#include <stdio.h>
#include <cstdio>
#include <curl/curl.h>
#include <curl/easy.h>
#include <string>

using json = nlohmann::json;

void AssertEquals(std::string arg1, std::string arg2, std::string line, std::string message)
{
	if (arg1 != arg2)
  {
		std::cerr << arg1 + " does not equal " + arg2 + " on line " + line << std::endl;
		std::cerr << "message: " << message << std::endl;
		exit(1);
	}
}

void AssertEquals(int arg1, int arg2, std::string line, std::string message)
{
	if (arg1 != arg2)
  {
		std::cerr << std::to_string(arg1) + " does not equal " + std::to_string(arg2) + " on line " + line << std::endl;
		std::cerr << "message: " << message << std::endl;
		exit(1);
	}
}

size_t write_data(void *ptr, size_t size, size_t nmemb, FILE *stream)
{
	size_t written;
	written = fwrite(ptr, size, nmemb, stream);
	return written;
}


void DownloadFile(std::string destination, std::string source)
{

	CURL *curl;
	curl_global_init(CURL_GLOBAL_ALL);
	FILE *fp;
	CURLcode res;
	curl = curl_easy_init();
	if (curl)
  {
#ifndef _WIN32
		fp = fopen(destination.c_str(), "wb");
#else
		fopen_s(&fp, destination.c_str(), "wb");
#endif
		curl_easy_setopt(curl, CURLOPT_URL, source.c_str());
		curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, write_data);
		curl_easy_setopt(curl, CURLOPT_WRITEDATA, fp);
		res = curl_easy_perform(curl);
		curl_easy_cleanup(curl);
		fclose(fp);
	}

}

int main(int argc, char *argv[])
{
#ifndef _WIN32
	VoiceIt2 v(argv[1], argv[2]);
  if (getenv("BOXFUSE_ENV") != NULL) {
    std::string boxfuseenv = getenv("BOXFUSE_ENV");
    if (boxfuseenv == "voiceittest")
    {
      std::string home = getenv("HOME");
      std::ofstream out(home + "/platformVersion");
      out << v.GetVersion();
      out.close();
    }
  }
#else
	VoiceIt2 v("key_00000000000000000000000000000000", "tok_00000000000000000000000000000000");
#endif
	json ret;

	std::string userId;
	std::string userId1;
	std::string userId2;
	std::string groupId;
	std::string subAccountUnmanagedAPIKey;
	std::string subAccountManagedAPIKey;
	int enrollmentId1;
  std::string str;

	// Test Webhooks
	v.AddNotificationUrl("https://voiceit.io");
	AssertEquals("https%3A%2F%2Fvoiceit.io", v.GetNotificationUrl(), std::to_string(__LINE__), ret.dump());
	v.RemoveNotificationUrl();
	AssertEquals("", v.GetNotificationUrl(), std::to_string(__LINE__), ret.dump());

	// Test IO Exceptions
	try {
		v.CreateVideoEnrollment("", "", "", "not_a_real_file");
		std::cerr << "File check for CreateVideoEnrollment() failed" << std::endl;
		exit(1);
	}
	catch (std::string msg)
  {
		std::cout << "File check for CreateVideoEnrollment() worked" << std::endl;
	}

	try {
		v.CreateVoiceEnrollment("", "", "", "not_a_real_file");
		std::cerr << "File check for CreateVoiceEnrollment() failed" << std::endl;
		exit(1);
	}
	catch (std::string msg)
  {
		std::cout << "File check for CreateVoiceEnrollment() worked" << std::endl;
	}

	try {
		v.CreateFaceEnrollment("", "not_a_real_file");
		std::cerr << "File check for CreateFaceEnrollment() failed" << std::endl;
		exit(1);
	}
	catch (std::string msg)
  {
		std::cout << "File check for CreateFaceEnrollment() worked" << std::endl;
	}

	try {
		v.VideoVerification("", "", "", "not_a_real_file");
		std::cerr << "File check for VideoVerification() failed" << std::endl;
		exit(1);
	}
	catch (std::string msg)
  {
		std::cout << "File check for VideoVerification() worked" << std::endl;
	}

	try {
		v.VoiceVerification("", "", "", "not_a_real_file");
		std::cerr << "File check for VoiceVerification() failed" << std::endl;
		exit(1);
	}
	catch (std::string msg)
  {
		std::cout << "File check for VoiceVerification() worked" << std::endl;
	}

	try {
		v.FaceVerification("", "not_a_real_file");
		std::cerr << "File check for FaceVerification() failed" << std::endl;
		exit(1);
	}
	catch (std::string msg)
  {
		std::cout << "File check for FaceVerification() worked" << std::endl;
	}

	try {
		v.VideoIdentification("", "", "", "not_a_real_file");
		std::cerr << "File check for VideoIdentification() failed" << std::endl;
		exit(1);
	}
	catch (std::string msg)
  {
		std::cout << "File check for VideoIdentification() worked" << std::endl;
	}

	try {
		v.VoiceIdentification("", "", "", "not_a_real_file");
		std::cerr << "File check for VoiceIdentification() failed" << std::endl;
		exit(1);
	}
	catch (std::string msg)
  {
		std::cout << "File check for VoiceIdentification() worked" << std::endl;
	}

	try {
		v.FaceIdentification("", "not_a_real_file");
		std::cerr << "File check for FaceIdentification() failed" << std::endl;
		exit(1);
	}
	catch (std::string msg)
  {
		std::cout << "File check for FaceIdentification() worked" << std::endl;
	}

	// Test Basics
  str = v.CreateUser();
  // std::cout << "str: " << str << std::endl;
	ret = json::parse(str);
	AssertEquals(201, ret["status"], std::to_string(__LINE__), ret.dump());
	AssertEquals("SUCC", ret["responseCode"], std::to_string(__LINE__), ret.dump());
	userId = ret["userId"].get<std::string>();

  str = v.GetAllUsers();
  // std::cout << "str: " << str << std::endl;
	ret = json::parse(str);
	AssertEquals(200, ret["status"], std::to_string(__LINE__), ret.dump());
	AssertEquals("SUCC", ret["responseCode"], std::to_string(__LINE__), ret.dump());

  str = v.CheckUserExists(userId);
  // std::cout << "str: " << str << std::endl;
	ret = json::parse(str);
	AssertEquals(200, ret["status"], std::to_string(__LINE__), ret.dump());
	AssertEquals("SUCC", ret["responseCode"], std::to_string(__LINE__), ret.dump());

  str = v.CreateGroup("Sample Group Description");
  // std::cout << "str: " << str << std::endl;
	ret = json::parse(str);
	AssertEquals(201, ret["status"], std::to_string(__LINE__), ret.dump());
	AssertEquals("SUCC", ret["responseCode"], std::to_string(__LINE__), ret.dump());
	groupId = ret["groupId"].get<std::string>();

  str = v.GetAllGroups();
  // std::cout << "str: " << str << std::endl;
	ret = json::parse(str);
	AssertEquals(200, ret["status"], std::to_string(__LINE__), ret.dump());
	AssertEquals("SUCC", ret["responseCode"], std::to_string(__LINE__), ret.dump());

  str = v.CheckGroupExists(groupId);
  // std::cout << "str: " << str << std::endl;
	ret = json::parse(str);
	AssertEquals(200, ret["status"], std::to_string(__LINE__), ret.dump());
	AssertEquals("SUCC", ret["responseCode"], std::to_string(__LINE__), ret.dump());

  str = v.GetGroup(groupId);
  // std::cout << "str: " << str << std::endl;
	ret = json::parse(str);
	AssertEquals(200, ret["status"], std::to_string(__LINE__), ret.dump());
	AssertEquals("SUCC", ret["responseCode"], std::to_string(__LINE__), ret.dump());

  str = v.GetGroup(groupId);
  // std::cout << "str: " << str << std::endl;
	ret = json::parse(str);
	AssertEquals(200, ret["status"], std::to_string(__LINE__), ret.dump());
	AssertEquals("SUCC", ret["responseCode"], std::to_string(__LINE__), ret.dump());

  str = v.AddUserToGroup(groupId, userId);
  // std::cout << "str: " << str << std::endl;
	ret = json::parse(str);
	AssertEquals(200, ret["status"], std::to_string(__LINE__), ret.dump());
	AssertEquals("SUCC", ret["responseCode"], std::to_string(__LINE__), ret.dump());

  str = v.GetGroupsForUser(userId);
  // std::cout << "str: " << str << std::endl;
	ret = json::parse(str);
	AssertEquals(200, ret["status"], std::to_string(__LINE__), ret.dump());
	AssertEquals("SUCC", ret["responseCode"], std::to_string(__LINE__), ret.dump());

  str = v.RemoveUserFromGroup(groupId, userId);
  // std::cout << "str: " << str << std::endl;
	ret = json::parse(str);
	AssertEquals(200, ret["status"], std::to_string(__LINE__), ret.dump());
	AssertEquals("SUCC", ret["responseCode"], std::to_string(__LINE__), ret.dump());

  str = v.CreateUserToken(userId, 10);
  // std::cout << "str: " << str << std::endl;
	ret = json::parse(str);
	AssertEquals(201, ret["status"], std::to_string(__LINE__), ret.dump());
	AssertEquals("SUCC", ret["responseCode"], std::to_string(__LINE__), ret.dump());

  str = v.ExpireUserTokens(userId);
  // std::cout << "str: " << str << std::endl;
	ret = json::parse(str);
	AssertEquals(201, ret["status"], std::to_string(__LINE__), ret.dump());
	AssertEquals("SUCC", ret["responseCode"], std::to_string(__LINE__), ret.dump());

  str = v.DeleteUser(userId);
  // std::cout << "str: " << str << std::endl;
	ret = json::parse(str);
	AssertEquals(200, ret["status"], std::to_string(__LINE__), ret.dump());
	AssertEquals("SUCC", ret["responseCode"], std::to_string(__LINE__), ret.dump());

  str = v.DeleteGroup(groupId);
  // std::cout << "str: " << str << std::endl;
	ret = json::parse(str);
	AssertEquals(200, ret["status"], std::to_string(__LINE__), ret.dump());
	AssertEquals("SUCC", ret["responseCode"], std::to_string(__LINE__), ret.dump());

  str = v.GetPhrases("en-US");
  // std::cout << "str: " << str << std::endl;
	ret = json::parse(str);
	AssertEquals(200, ret["status"], std::to_string(__LINE__), ret.dump());
	AssertEquals("SUCC", ret["responseCode"], std::to_string(__LINE__), ret.dump());
	std::cout << "****Test Basics All Passed****" << std::endl;

  str = v.CreateManagedSubAccount("Testy","","","","");
    // std::cout << "str: " << str << std::endl;
    ret = json::parse(str);
    AssertEquals(201, ret["status"], std::to_string(__LINE__), ret.dump());
	AssertEquals("SUCC", ret["responseCode"], std::to_string(__LINE__), ret.dump());
    subAccountManagedAPIKey = ret["apiKey"];

  str = v.CreateUnmanagedSubAccount();
    // std::cout << "str: " << str << std::endl;
    ret = json::parse(str);
    AssertEquals(201, ret["status"], std::to_string(__LINE__), ret.dump());
	AssertEquals("SUCC", ret["responseCode"], std::to_string(__LINE__), ret.dump());
	subAccountUnmanagedAPIKey = ret["apiKey"];

  str = v.RegenerateSubAccountAPIToken(subAccountManagedAPIKey);
    // std::cout << "str: " << str << std::endl;
    ret = json::parse(str);
    AssertEquals(200, ret["status"], std::to_string(__LINE__), ret.dump());
	AssertEquals("SUCC", ret["responseCode"], std::to_string(__LINE__), ret.dump());

  str = v.DeleteSubAccount(subAccountManagedAPIKey);
    // std::cout << "str: " << str << std::endl;
    ret = json::parse(str);
    AssertEquals(200, ret["status"], std::to_string(__LINE__), ret.dump());
	AssertEquals("SUCC", ret["responseCode"], std::to_string(__LINE__), ret.dump());

  str = v.DeleteSubAccount(subAccountUnmanagedAPIKey);
    // std::cout << "str: " << str << std::endl;
    ret = json::parse(str);
    AssertEquals(200, ret["status"], std::to_string(__LINE__), ret.dump());
	AssertEquals("SUCC", ret["responseCode"], std::to_string(__LINE__), ret.dump());

	std::cout << "****Test Subaccounts All Passed****" << std::endl;
	// Test Video

  str = v.CreateUser();
  // std::cout << "str: " << str << std::endl;
	ret = json::parse(str);
	userId1 = ret["userId"].get<std::string>();
  str = v.CreateUser();
  // std::cout << "str: " << str << std::endl;
	ret = json::parse(str);
	userId2 = ret["userId"].get<std::string>();
  str = v.CreateGroup("Sample Group Description");
  // std::cout << "str: " << str << std::endl;
	ret = json::parse(str);
	groupId = ret["groupId"].get<std::string>();
	v.AddUserToGroup(groupId, userId1);
	v.AddUserToGroup(groupId, userId2);
	// Video Enrollments


	DownloadFile("./videoEnrollmentB1.mov", "https://drive.voiceit.io/files/videoEnrollmentB1.mov");
	DownloadFile("./videoEnrollmentB2.mov", "https://drive.voiceit.io/files/videoEnrollmentB2.mov");
	DownloadFile("./videoEnrollmentB3.mov", "https://drive.voiceit.io/files/videoEnrollmentB3.mov");
	DownloadFile("./videoVerificationB1.mov", "https://drive.voiceit.io/files/videoVerificationB1.mov");
	DownloadFile("./videoEnrollmentC1.mov", "https://drive.voiceit.io/files/videoEnrollmentC1.mov");
	DownloadFile("./videoEnrollmentC2.mov", "https://drive.voiceit.io/files/videoEnrollmentC2.mov");
	DownloadFile("./videoEnrollmentC3.mov", "https://drive.voiceit.io/files/videoEnrollmentC3.mov");

  str = v.CreateVideoEnrollment(userId1, "en-US", "never forget tomorrow is a new day", "./videoEnrollmentB1.mov");
  // std::cout << "str: " << str << std::endl;
	ret = json::parse(str);
	AssertEquals(201, ret["status"], std::to_string(__LINE__), ret.dump());
	AssertEquals("SUCC", ret["responseCode"], std::to_string(__LINE__), ret.dump());
	enrollmentId1 = ret["id"].get<int>();
  str = v.CreateVideoEnrollment(userId1, "en-US", "never forget tomorrow is a new day", "./videoEnrollmentB2.mov");
  // std::cout << "str: " << str << std::endl;
	ret = json::parse(str);
	AssertEquals(201, ret["status"], std::to_string(__LINE__), ret.dump());
	AssertEquals("SUCC", ret["responseCode"], std::to_string(__LINE__), ret.dump());
  str = v.CreateVideoEnrollment(userId1, "en-US", "never forget tomorrow is a new day", "./videoEnrollmentB3.mov");
  // std::cout << "str: " << str << std::endl;
	ret = json::parse(str);
	AssertEquals(201, ret["status"], std::to_string(__LINE__), ret.dump());
	AssertEquals("SUCC", ret["responseCode"], std::to_string(__LINE__), ret.dump());


  str = v.CreateVideoEnrollment(userId2, "en-US", "never forget tomorrow is a new day", "./videoEnrollmentC1.mov");
  // std::cout << "str: " << str << std::endl;
	ret = json::parse(str);
	AssertEquals(201, ret["status"], std::to_string(__LINE__), ret.dump());
	AssertEquals("SUCC", ret["responseCode"], std::to_string(__LINE__), ret.dump());
  str = v.CreateVideoEnrollment(userId2, "en-US", "never forget tomorrow is a new day", "./videoEnrollmentC2.mov");
  // std::cout << "str: " << str << std::endl;
	ret = json::parse(str);
	AssertEquals(201, ret["status"], std::to_string(__LINE__), ret.dump());
	AssertEquals("SUCC", ret["responseCode"], std::to_string(__LINE__), ret.dump());
  str = v.CreateVideoEnrollment(userId2, "en-US", "never forget tomorrow is a new day", "./videoEnrollmentC3.mov");
  // std::cout << "str: " << str << std::endl;
	ret = json::parse(str);
	AssertEquals(201, ret["status"], std::to_string(__LINE__), ret.dump());
	AssertEquals("SUCC", ret["responseCode"], std::to_string(__LINE__), ret.dump());

	// Video Verification
  str = v.VideoVerification(userId1, "en-US", "never forget tomorrow is a new day", "./videoVerificationB1.mov");
  // std::cout << "str: " << str << std::endl;
	ret = json::parse(str);
	AssertEquals(200, ret["status"], std::to_string(__LINE__), ret.dump());
	AssertEquals("SUCC", ret["responseCode"], std::to_string(__LINE__), ret.dump());

	// Video Identification
  str = v.VideoIdentification(groupId, "en-US", "never forget tomorrow is a new day", "./videoVerificationB1.mov");
  // std::cout << "str: " << str << std::endl;
	ret = json::parse(str);
	AssertEquals(200, ret["status"], std::to_string(__LINE__), ret.dump());
	AssertEquals("SUCC", ret["responseCode"], std::to_string(__LINE__), ret.dump());
	AssertEquals(userId1, ret["userId"], std::to_string(__LINE__), ret.dump());

	// Delete All Enrollments
  str = v.DeleteAllEnrollments(userId1);
  // std::cout << "str: " << str << std::endl;
	ret = json::parse(str);
	AssertEquals(200, ret["status"], std::to_string(__LINE__), ret.dump());
	AssertEquals("SUCC", ret["responseCode"], std::to_string(__LINE__), ret.dump());
	v.DeleteAllEnrollments(userId2);

	// Reset for ...ByUrl operations
	v.DeleteUser(userId1);
	v.DeleteUser(userId2);
	v.DeleteGroup(groupId);

  str = v.CreateUser();
  // std::cout << "str: " << str << std::endl;
	ret = json::parse(str);
	userId1 = ret["userId"].get<std::string>();
  str = v.CreateUser();
  // std::cout << "str: " << str << std::endl;
	ret = json::parse(str);
	userId2 = ret["userId"].get<std::string>();
  str = v.CreateGroup("Sample Group Description");
  // std::cout << "str: " << str << std::endl;
	ret = json::parse(str);
	groupId = ret["groupId"].get<std::string>();
	v.AddUserToGroup(groupId, userId1);
	v.AddUserToGroup(groupId, userId2);

	// Video Enrollment By URL
  str = v.CreateVideoEnrollmentByUrl(userId1, "en-US", "never forget tomorrow is a new day", "https://drive.voiceit.io/files/videoEnrollmentB1.mov");
  // std::cout << "str: " << str << std::endl;
	ret = json::parse(str);
	AssertEquals(201, ret["status"], std::to_string(__LINE__), ret.dump());
	AssertEquals("SUCC", ret["responseCode"], std::to_string(__LINE__), ret.dump());
  str = v.CreateVideoEnrollmentByUrl(userId1, "en-US", "never forget tomorrow is a new day", "https://drive.voiceit.io/files/videoEnrollmentB2.mov");
  // std::cout << "str: " << str << std::endl;
	ret = json::parse(str);
	AssertEquals(201, ret["status"], std::to_string(__LINE__), ret.dump());
	AssertEquals("SUCC", ret["responseCode"], std::to_string(__LINE__), ret.dump());
  str = v.CreateVideoEnrollmentByUrl(userId1, "en-US", "never forget tomorrow is a new day", "https://drive.voiceit.io/files/videoEnrollmentB3.mov");
  // std::cout << "str: " << str << std::endl;
	ret = json::parse(str);
	AssertEquals(201, ret["status"], std::to_string(__LINE__), ret.dump());
	AssertEquals("SUCC", ret["responseCode"], std::to_string(__LINE__), ret.dump());
  str = v.CreateVideoEnrollmentByUrl(userId2, "en-US", "never forget tomorrow is a new day", "https://drive.voiceit.io/files/videoEnrollmentC1.mov");
  // std::cout << "str: " << str << std::endl;
	ret = json::parse(str);
	AssertEquals(201, ret["status"], std::to_string(__LINE__), ret.dump());
	AssertEquals("SUCC", ret["responseCode"], std::to_string(__LINE__), ret.dump());
  str = v.CreateVideoEnrollmentByUrl(userId2, "en-US", "never forget tomorrow is a new day", "https://drive.voiceit.io/files/videoEnrollmentC2.mov");
  // std::cout << "str: " << str << std::endl;
	ret = json::parse(str);
	AssertEquals(201, ret["status"], std::to_string(__LINE__), ret.dump());
	AssertEquals("SUCC", ret["responseCode"], std::to_string(__LINE__), ret.dump());
  str = v.CreateVideoEnrollmentByUrl(userId2, "en-US", "never forget tomorrow is a new day", "https://drive.voiceit.io/files/videoEnrollmentC3.mov");
  // std::cout << "str: " << str << std::endl;
	ret = json::parse(str);
	AssertEquals(201, ret["status"], std::to_string(__LINE__), ret.dump());
	AssertEquals("SUCC", ret["responseCode"], std::to_string(__LINE__), ret.dump());


	// Video Verification By URL
  str = v.VideoVerificationByUrl(userId1, "en-US", "never forget tomorrow is a new day", "https://drive.voiceit.io/files/videoVerificationB1.mov");
  // std::cout << "str: " << str << std::endl;
	ret = json::parse(str);
	AssertEquals(200, ret["status"], std::to_string(__LINE__), ret.dump());
	AssertEquals("SUCC", ret["responseCode"], std::to_string(__LINE__), ret.dump());

	// Video Identification By URL
  str = v.VideoIdentificationByUrl(groupId, "en-US", "never forget tomorrow is a new day", "https://drive.voiceit.io/files/videoVerificationB1.mov");
  // std::cout << "str: " << str << std::endl;
	ret = json::parse(str);
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


  str = v.CreateUser();
  // std::cout << "str: " << str << std::endl;
	ret = json::parse(str);
	userId1 = ret["userId"].get<std::string>();
  str = v.CreateUser();
  // std::cout << "str: " << str << std::endl;
	ret = json::parse(str);
	userId2 = ret["userId"].get<std::string>();
  str = v.CreateGroup("Sample Group Description");
  // std::cout << "str: " << str << std::endl;
	ret = json::parse(str);
	groupId = ret["groupId"].get<std::string>();
	v.AddUserToGroup(groupId, userId1);
	v.AddUserToGroup(groupId, userId2);

	// Voice Enrollments

	DownloadFile("./enrollmentA1.wav", "https://drive.voiceit.io/files/enrollmentA1.wav");
	DownloadFile("./enrollmentA2.wav", "https://drive.voiceit.io/files/enrollmentA2.wav");
	DownloadFile("./enrollmentA3.wav", "https://drive.voiceit.io/files/enrollmentA3.wav");
	DownloadFile("./verificationA1.wav", "https://drive.voiceit.io/files/verificationA1.wav");
	DownloadFile("./enrollmentC1.wav", "https://drive.voiceit.io/files/enrollmentC1.wav");
	DownloadFile("./enrollmentC2.wav", "https://drive.voiceit.io/files/enrollmentC2.wav");
	DownloadFile("./enrollmentC3.wav", "https://drive.voiceit.io/files/enrollmentC3.wav");

  str = v.CreateVoiceEnrollment(userId1, "en-US", "never forget tomorrow is a new day", "./enrollmentA1.wav");
  // std::cout << "str: " << str << std::endl;
	ret = json::parse(str);
	AssertEquals(201, ret["status"], std::to_string(__LINE__), ret.dump());
	AssertEquals("SUCC", ret["responseCode"], std::to_string(__LINE__), ret.dump());
  str = v.CreateVoiceEnrollment(userId1, "en-US", "never forget tomorrow is a new day", "./enrollmentA2.wav");
  // std::cout << "str: " << str << std::endl;
	ret = json::parse(str);
	AssertEquals(201, ret["status"], std::to_string(__LINE__), ret.dump());
	AssertEquals("SUCC", ret["responseCode"], std::to_string(__LINE__), ret.dump());
  str = v.CreateVoiceEnrollment(userId1, "en-US", "never forget tomorrow is a new day", "./enrollmentA3.wav");
  // std::cout << "str: " << str << std::endl;
	ret = json::parse(str);
	AssertEquals(201, ret["status"], std::to_string(__LINE__), ret.dump());
	AssertEquals("SUCC", ret["responseCode"], std::to_string(__LINE__), ret.dump());


  str = v.CreateVoiceEnrollment(userId2, "en-US", "never forget tomorrow is a new day", "./enrollmentC1.wav");
  // std::cout << "str: " << str << std::endl;
	ret = json::parse(str);
	AssertEquals(201, ret["status"], std::to_string(__LINE__), ret.dump());
	AssertEquals("SUCC", ret["responseCode"], std::to_string(__LINE__), ret.dump());
  str = v.CreateVoiceEnrollment(userId2, "en-US", "never forget tomorrow is a new day", "./enrollmentC2.wav");
  // std::cout << "str: " << str << std::endl;
	ret = json::parse(str);
	AssertEquals(201, ret["status"], std::to_string(__LINE__), ret.dump());
	AssertEquals("SUCC", ret["responseCode"], std::to_string(__LINE__), ret.dump());
  str = v.CreateVoiceEnrollment(userId2, "en-US", "never forget tomorrow is a new day", "./enrollmentC3.wav");
  // std::cout << "str: " << str << std::endl;
	ret = json::parse(str);
	AssertEquals(201, ret["status"], std::to_string(__LINE__), ret.dump());
	AssertEquals("SUCC", ret["responseCode"], std::to_string(__LINE__), ret.dump());

	// Voice Verification
  str = v.VoiceVerification(userId1, "en-US", "never forget tomorrow is a new day", "./verificationA1.wav");
  // std::cout << "str: " << str << std::endl;
	ret = json::parse(str);
	AssertEquals(200, ret["status"], std::to_string(__LINE__), ret.dump());
	AssertEquals("SUCC", ret["responseCode"], std::to_string(__LINE__), ret.dump());

	// Voice Identification
  str = v.VoiceIdentification(groupId, "en-US", "never forget tomorrow is a new day", "./verificationA1.wav");
  // std::cout << "str: " << str << std::endl;
	ret = json::parse(str);
	AssertEquals(200, ret["status"], std::to_string(__LINE__), ret.dump());
	AssertEquals("SUCC", ret["responseCode"], std::to_string(__LINE__), ret.dump());
	AssertEquals(userId1, ret["userId"], std::to_string(__LINE__), ret.dump());

	// Reset for ...ByUrl operations
	v.DeleteAllEnrollments(userId1);
	v.DeleteAllEnrollments(userId2);
	v.DeleteUser(userId1);
	v.DeleteUser(userId2);
	v.DeleteGroup(groupId);
  str = v.CreateUser();
  // std::cout << "str: " << str << std::endl;
	ret = json::parse(str);
	userId1 = ret["userId"].get<std::string>();
  str = v.CreateUser();
  // std::cout << "str: " << str << std::endl;
	ret = json::parse(str);
	userId2 = ret["userId"].get<std::string>();
  str = v.CreateGroup("Sample Group Description");
  // std::cout << "str: " << str << std::endl;
	ret = json::parse(str);
	groupId = ret["groupId"].get<std::string>();
	v.AddUserToGroup(groupId, userId1);
	v.AddUserToGroup(groupId, userId2);

	// Voice Enrollment By URL
  str = v.CreateVoiceEnrollmentByUrl(userId1, "en-US", "never forget tomorrow is a new day", "https://drive.voiceit.io/files/enrollmentA1.wav");
  // std::cout << "str: " << str << std::endl;
	ret = json::parse(str);
	AssertEquals(201, ret["status"], std::to_string(__LINE__), ret.dump());
	AssertEquals("SUCC", ret["responseCode"], std::to_string(__LINE__), ret.dump());
  str = v.CreateVoiceEnrollmentByUrl(userId1, "en-US", "never forget tomorrow is a new day", "https://drive.voiceit.io/files/enrollmentA2.wav");
  // std::cout << "str: " << str << std::endl;
	ret = json::parse(str);
	AssertEquals(201, ret["status"], std::to_string(__LINE__), ret.dump());
	AssertEquals("SUCC", ret["responseCode"], std::to_string(__LINE__), ret.dump());
  str = v.CreateVoiceEnrollmentByUrl(userId1, "en-US", "never forget tomorrow is a new day", "https://drive.voiceit.io/files/enrollmentA3.wav");
  // std::cout << "str: " << str << std::endl;
	ret = json::parse(str);
	AssertEquals(201, ret["status"], std::to_string(__LINE__), ret.dump());
	AssertEquals("SUCC", ret["responseCode"], std::to_string(__LINE__), ret.dump());
  str = v.CreateVoiceEnrollmentByUrl(userId2, "en-US", "never forget tomorrow is a new day", "https://drive.voiceit.io/files/enrollmentC1.wav");
  // std::cout << "str: " << str << std::endl;
	ret = json::parse(str);
	AssertEquals(201, ret["status"], std::to_string(__LINE__), ret.dump());
	AssertEquals("SUCC", ret["responseCode"], std::to_string(__LINE__), ret.dump());
  str = v.CreateVoiceEnrollmentByUrl(userId2, "en-US", "never forget tomorrow is a new day", "https://drive.voiceit.io/files/enrollmentC2.wav");
  // std::cout << "str: " << str << std::endl;
	ret = json::parse(str);
	AssertEquals(201, ret["status"], std::to_string(__LINE__), ret.dump());
	AssertEquals("SUCC", ret["responseCode"], std::to_string(__LINE__), ret.dump());
  str = v.CreateVoiceEnrollmentByUrl(userId2, "en-US", "never forget tomorrow is a new day", "https://drive.voiceit.io/files/enrollmentC3.wav");
  // std::cout << "str: " << str << std::endl;
	ret = json::parse(str);
	AssertEquals(201, ret["status"], std::to_string(__LINE__), ret.dump());
	AssertEquals("SUCC", ret["responseCode"], std::to_string(__LINE__), ret.dump());


	// Voice Verification By URL
  str = v.VoiceVerificationByUrl(userId1, "en-US", "never forget tomorrow is a new day", "https://drive.voiceit.io/files/verificationA1.wav");
  // std::cout << "str: " << str << std::endl;
	ret = json::parse(str);
	AssertEquals(200, ret["status"], std::to_string(__LINE__), ret.dump());
	AssertEquals("SUCC", ret["responseCode"], std::to_string(__LINE__), ret.dump());

	// Voice Identification By URL
  str = v.VoiceIdentificationByUrl(groupId, "en-US", "never forget tomorrow is a new day", "https://drive.voiceit.io/files/verificationA1.wav");
  // std::cout << "str: " << str << std::endl;
	ret = json::parse(str);
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


  str = v.CreateUser();
  // std::cout << "str: " << str << std::endl;
	ret = json::parse(str);
	userId1 = ret["userId"].get<std::string>();
  str = v.CreateUser();
  // std::cout << "str: " << str << std::endl;
	ret = json::parse(str);
	userId2 = ret["userId"].get<std::string>();
  str = v.CreateGroup("Sample Group Description");
  // std::cout << "str: " << str << std::endl;
	ret = json::parse(str);
	groupId = ret["groupId"].get<std::string>();
	v.AddUserToGroup(groupId, userId1);
	v.AddUserToGroup(groupId, userId2);

	// Face Enrollments

	DownloadFile("./faceEnrollmentB1.mp4", "https://drive.voiceit.io/files/faceEnrollmentB1.mp4");
	DownloadFile("./faceEnrollmentB2.mp4", "https://drive.voiceit.io/files/faceEnrollmentB2.mp4");
	DownloadFile("./faceEnrollmentB3.mp4", "https://drive.voiceit.io/files/faceEnrollmentB3.mp4");
	DownloadFile("./faceVerificationB1.mp4", "https://drive.voiceit.io/files/faceVerificationB1.mp4");

  str = v.CreateFaceEnrollment(userId1, "./faceEnrollmentB1.mp4");
  // std::cout << "str: " << str << std::endl;
	ret = json::parse(str);
	AssertEquals(201, ret["status"], std::to_string(__LINE__), ret.dump());
	AssertEquals("SUCC", ret["responseCode"], std::to_string(__LINE__), ret.dump());
  str = v.CreateFaceEnrollment(userId1, "./faceEnrollmentB2.mp4");
  // std::cout << "str: " << str << std::endl;
	ret = json::parse(str);
	AssertEquals(201, ret["status"], std::to_string(__LINE__), ret.dump());
	AssertEquals("SUCC", ret["responseCode"], std::to_string(__LINE__), ret.dump());
  str = v.CreateFaceEnrollment(userId1, "./faceEnrollmentB3.mp4");
  // std::cout << "str: " << str << std::endl;
	ret = json::parse(str);
	AssertEquals(201, ret["status"], std::to_string(__LINE__), ret.dump());
	AssertEquals("SUCC", ret["responseCode"], std::to_string(__LINE__), ret.dump());


  str = v.CreateFaceEnrollment(userId2, "./videoEnrollmentC1.mov");
  // std::cout << "str: " << str << std::endl;
	ret = json::parse(str);
	AssertEquals(201, ret["status"], std::to_string(__LINE__), ret.dump());
	AssertEquals("SUCC", ret["responseCode"], std::to_string(__LINE__), ret.dump());
  str = v.CreateFaceEnrollment(userId2, "./videoEnrollmentC2.mov");
  // std::cout << "str: " << str << std::endl;
	ret = json::parse(str);
	AssertEquals(201, ret["status"], std::to_string(__LINE__), ret.dump());
	AssertEquals("SUCC", ret["responseCode"], std::to_string(__LINE__), ret.dump());
  str = v.CreateFaceEnrollment(userId2, "./videoEnrollmentC3.mov");
  // std::cout << "str: " << str << std::endl;
	ret = json::parse(str);
	AssertEquals(201, ret["status"], std::to_string(__LINE__), ret.dump());
	AssertEquals("SUCC", ret["responseCode"], std::to_string(__LINE__), ret.dump());

	// Face Verification
  str = v.FaceVerification(userId1, "./faceVerificationB1.mp4");
  // std::cout << "str: " << str << std::endl;
	ret = json::parse(str);
	AssertEquals(200, ret["status"], std::to_string(__LINE__), ret.dump());
	AssertEquals("SUCC", ret["responseCode"], std::to_string(__LINE__), ret.dump());

	// Face Identification
  str = v.FaceIdentification(groupId, "./faceVerificationB1.mp4");
  // std::cout << "str: " << str << std::endl;
	ret = json::parse(v.FaceIdentification(groupId, "./faceVerificationB1.mp4"));
	AssertEquals(200, ret["status"], std::to_string(__LINE__), ret.dump());
	AssertEquals("SUCC", ret["responseCode"], std::to_string(__LINE__), ret.dump());
	AssertEquals(userId1, ret["userId"], std::to_string(__LINE__), ret.dump());


	// Reset for ...ByUrl operations
	v.DeleteAllEnrollments(userId1);
	v.DeleteAllEnrollments(userId2);
	v.DeleteUser(userId1);
	v.DeleteUser(userId2);
	v.DeleteGroup(groupId);
  str = v.CreateUser();
  // std::cout << "str: " << str << std::endl;
	ret = json::parse(str);
	userId1 = ret["userId"].get<std::string>();
  str = v.CreateUser();
  // std::cout << "str: " << str << std::endl;
	ret = json::parse(str);
	userId2 = ret["userId"].get<std::string>();
  str = v.CreateGroup("Sample Group Description");
  // std::cout << "str: " << str << std::endl;
	ret = json::parse(str);
	groupId = ret["groupId"].get<std::string>();
	v.AddUserToGroup(groupId, userId1);
	v.AddUserToGroup(groupId, userId2);

	// Face Enrollment By URL
  str = v.CreateFaceEnrollmentByUrl(userId1, "https://drive.voiceit.io/files/faceEnrollmentB1.mp4");
  // std::cout << "str: " << str << std::endl;
	ret = json::parse(str);
	AssertEquals(201, ret["status"], std::to_string(__LINE__), ret.dump());
	AssertEquals("SUCC", ret["responseCode"], std::to_string(__LINE__), ret.dump());
  str = v.CreateFaceEnrollmentByUrl(userId1, "https://drive.voiceit.io/files/faceEnrollmentB2.mp4");
  // std::cout << "str: " << str << std::endl;
	ret = json::parse(str);
	AssertEquals(201, ret["status"], std::to_string(__LINE__), ret.dump());
	AssertEquals("SUCC", ret["responseCode"], std::to_string(__LINE__), ret.dump());
  str = v.CreateFaceEnrollmentByUrl(userId1, "https://drive.voiceit.io/files/faceEnrollmentB3.mp4");
  // std::cout << "str: " << str << std::endl;
	ret = json::parse(str);
	AssertEquals(201, ret["status"], std::to_string(__LINE__), ret.dump());
	AssertEquals("SUCC", ret["responseCode"], std::to_string(__LINE__), ret.dump());
  str = v.CreateFaceEnrollmentByUrl(userId2, "https://drive.voiceit.io/files/videoEnrollmentC1.mov");
  // std::cout << "str: " << str << std::endl;
	ret = json::parse(str);
	AssertEquals(201, ret["status"], std::to_string(__LINE__), ret.dump());
	AssertEquals("SUCC", ret["responseCode"], std::to_string(__LINE__), ret.dump());
  str = v.CreateFaceEnrollmentByUrl(userId2, "https://drive.voiceit.io/files/videoEnrollmentC2.mov");
  // std::cout << "str: " << str << std::endl;
	ret = json::parse(str);
	AssertEquals(201, ret["status"], std::to_string(__LINE__), ret.dump());
	AssertEquals("SUCC", ret["responseCode"], std::to_string(__LINE__), ret.dump());
  str = v.CreateFaceEnrollmentByUrl(userId2, "https://drive.voiceit.io/files/videoEnrollmentC3.mov");
  // std::cout << "str: " << str << std::endl;
	ret = json::parse(str);
	AssertEquals(201, ret["status"], std::to_string(__LINE__), ret.dump());
	AssertEquals("SUCC", ret["responseCode"], std::to_string(__LINE__), ret.dump());


	// Face Verification By URL
  str = v.FaceVerificationByUrl(userId1, "https://drive.voiceit.io/files/faceVerificationB1.mp4");
  // std::cout << "str: " << str << std::endl;
	ret = json::parse(str);
	AssertEquals(200, ret["status"], std::to_string(__LINE__), ret.dump());
	AssertEquals("SUCC", ret["responseCode"], std::to_string(__LINE__), ret.dump());

	// Face Identification By URL
  str = v.FaceIdentificationByUrl(groupId, "https://drive.voiceit.io/files/faceVerificationB1.mp4");
  // std::cout << "str: " << str << std::endl;
	ret = json::parse(str);
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
  str = v.CreateUser();
  // std::cout << "str: " << str << std::endl;
	ret = json::parse(str);
	userId = ret["userId"].get<std::string>();
	int videoEnrollmentId = json::parse(v.CreateVideoEnrollmentByUrl(userId, "en-US", "never forget tomorrow is a new day", "https://drive.voiceit.io/files/videoEnrollmentB1.mov"))["id"];
	v.CreateVideoEnrollmentByUrl(userId, "en-US", "never forget tomorrow is a new day", "https://drive.voiceit.io/files/videoEnrollmentB2.mov");
	int voiceEnrollmentId = json::parse(v.CreateVoiceEnrollmentByUrl(userId, "en-US", "never forget tomorrow is a new day", "https://drive.voiceit.io/files/enrollmentA1.wav"))["id"];
	v.CreateVoiceEnrollmentByUrl(userId, "en-US", "never forget tomorrow is a new day", "https://drive.voiceit.io/files/enrollmentA2.wav");
	int faceEnrollmentId = json::parse(v.CreateFaceEnrollment(userId, "./faceEnrollmentB1.mp4"))["faceEnrollmentId"];
	v.CreateFaceEnrollment(userId, "./faceEnrollmentB2.mp4");

  str = v.DeleteAllEnrollments(userId);
  // std::cout << "str: " << str << std::endl;
	ret = json::parse(str);
	AssertEquals(200, ret["status"], std::to_string(__LINE__), ret.dump());
	AssertEquals("SUCC", ret["responseCode"], std::to_string(__LINE__), ret.dump());

  str = v.GetAllVideoEnrollments(userId);
  // std::cout << "str: " << str << std::endl;
	ret = json::parse(str);
	AssertEquals(200, ret["status"], std::to_string(__LINE__), ret.dump());
	AssertEquals("SUCC", ret["responseCode"], std::to_string(__LINE__), ret.dump());
	AssertEquals(0, ret["count"], std::to_string(__LINE__), ret.dump());
  str = v.GetAllVoiceEnrollments(userId);
  // std::cout << "str: " << str << std::endl;
	ret = json::parse(str);
	AssertEquals(200, ret["status"], std::to_string(__LINE__), ret.dump());
	AssertEquals("SUCC", ret["responseCode"], std::to_string(__LINE__), ret.dump());
	AssertEquals(0, ret["count"], std::to_string(__LINE__), ret.dump());
  str = v.GetAllFaceEnrollments(userId);
  // std::cout << "str: " << str << std::endl;
	ret = json::parse(str);
	AssertEquals(200, ret["status"], std::to_string(__LINE__), ret.dump());
	AssertEquals("SUCC", ret["responseCode"], std::to_string(__LINE__), ret.dump());
	AssertEquals(0, ret["count"], std::to_string(__LINE__), ret.dump());

	v.DeleteAllEnrollments(userId);
	std::cout << "****Delete Enrollment All Passed****" << std::endl;

	// Test Delete Enrollments
	v.CreateVideoEnrollmentByUrl(userId, "en-US", "never forget tomorrow is a new day", "https://drive.voiceit.io/files/videoEnrollmentB1.mov");
	v.CreateVideoEnrollmentByUrl(userId, "en-US", "never forget tomorrow is a new day", "https://drive.voiceit.io/files/videoEnrollmentB2.mov");
	v.CreateVoiceEnrollmentByUrl(userId, "en-US", "never forget tomorrow is a new day", "https://drive.voiceit.io/files/enrollmentA1.wav");
	v.CreateVoiceEnrollmentByUrl(userId, "en-US", "never forget tomorrow is a new day", "https://drive.voiceit.io/files/enrollmentA2.wav");
	v.CreateFaceEnrollment(userId, "./faceEnrollmentB1.mp4");
	v.CreateFaceEnrollment(userId, "./faceEnrollmentB2.mp4");

	v.DeleteAllEnrollments(userId);
	v.DeleteUser(userId);

	std::cout << "****Delete All Video/Voice/Face Enrollments All Passed****" << std::endl;

	remove("./videoEnrollmentB1.mov");
	remove("./videoEnrollmentB2.mov");
	remove("./videoEnrollmentB3.mov");
	remove("./videoVerificationB1.mov");

	remove("./enrollmentA1.wav");
	remove("./enrollmentA2.wav");
	remove("./enrollmentA3.wav");
	remove("./verificationA1.wav");
	remove("./enrollmentC1.wav");
	remove("./enrollmentC2.wav");
	remove("./enrollmentC3.wav");

	remove("./faceEnrollmentB1.mp4");
	remove("./faceEnrollmentB2.mp4");
	remove("./faceEnrollmentB3.mp4");
	remove("./faceVerificationB1.mp4");
	remove("./videoEnrollmentC1.mov");
	remove("./videoEnrollmentC2.mov");
	remove("./videoEnrollmentC3.mov");
}
