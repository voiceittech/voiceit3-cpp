#ifdef _WIN32
#include "pch.h"
#endif

#include "VoiceIt2.hpp"
#include "json.h"
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

int main()
{
#ifndef _WIN32
	VoiceIt2 v(getenv("VIAPIKEY"), getenv("VIAPITOKEN"));
	std::string boxfuseenv = getenv("BOXFUSE_ENV");
	if (boxfuseenv == "voiceittest")
  {
		std::string home = getenv("HOME");
		std::ofstream out(home + "/platformVersion");
		out << v.GetVersion();
		out.close();
	}
#else
	VoiceIt2 v("key_00000000000000000000000000000000", "tok_00000000000000000000000000000000");
#endif
	json ret;

	std::string userId;
	std::string userId1;
	std::string userId2;
	std::string groupId;
	int enrollmentId1;

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
	ret = json::parse(v.CreateUser());
	AssertEquals(201, ret["status"], std::to_string(__LINE__), ret.dump());
	AssertEquals("SUCC", ret["responseCode"], std::to_string(__LINE__), ret.dump());
	userId = ret["userId"].get<std::string>();

	ret = json::parse(v.GetAllUsers());
	AssertEquals(200, ret["status"], std::to_string(__LINE__), ret.dump());
	AssertEquals("SUCC", ret["responseCode"], std::to_string(__LINE__), ret.dump());

	ret = json::parse(v.CheckUserExists(userId));
	AssertEquals(200, ret["status"], std::to_string(__LINE__), ret.dump());
	AssertEquals("SUCC", ret["responseCode"], std::to_string(__LINE__), ret.dump());

	ret = json::parse(v.CreateGroup("Sample Group Description"));
	AssertEquals(201, ret["status"], std::to_string(__LINE__), ret.dump());
	AssertEquals("SUCC", ret["responseCode"], std::to_string(__LINE__), ret.dump());
	groupId = ret["groupId"].get<std::string>();

	ret = json::parse(v.GetAllGroups());
	AssertEquals(200, ret["status"], std::to_string(__LINE__), ret.dump());
	AssertEquals("SUCC", ret["responseCode"], std::to_string(__LINE__), ret.dump());

	ret = json::parse(v.CheckGroupExists(groupId));
	AssertEquals(200, ret["status"], std::to_string(__LINE__), ret.dump());
	AssertEquals("SUCC", ret["responseCode"], std::to_string(__LINE__), ret.dump());

	ret = json::parse(v.GetGroup(groupId));
	AssertEquals(200, ret["status"], std::to_string(__LINE__), ret.dump());
	AssertEquals("SUCC", ret["responseCode"], std::to_string(__LINE__), ret.dump());

	ret = json::parse(v.GetGroup(groupId));
	AssertEquals(200, ret["status"], std::to_string(__LINE__), ret.dump());
	AssertEquals("SUCC", ret["responseCode"], std::to_string(__LINE__), ret.dump());

	ret = json::parse(v.AddUserToGroup(groupId, userId));
	AssertEquals(200, ret["status"], std::to_string(__LINE__), ret.dump());
	AssertEquals("SUCC", ret["responseCode"], std::to_string(__LINE__), ret.dump());

	ret = json::parse(v.GetGroupsForUser(userId));
	AssertEquals(200, ret["status"], std::to_string(__LINE__), ret.dump());
	AssertEquals("SUCC", ret["responseCode"], std::to_string(__LINE__), ret.dump());

	ret = json::parse(v.RemoveUserFromGroup(groupId, userId));
	AssertEquals(200, ret["status"], std::to_string(__LINE__), ret.dump());
	AssertEquals("SUCC", ret["responseCode"], std::to_string(__LINE__), ret.dump());

	ret = json::parse(v.CreateUserToken(userId, 10));
	AssertEquals(201, ret["status"], std::to_string(__LINE__), ret.dump());
	AssertEquals("SUCC", ret["responseCode"], std::to_string(__LINE__), ret.dump());

	ret = json::parse(v.DeleteUser(userId));
	AssertEquals(200, ret["status"], std::to_string(__LINE__), ret.dump());
	AssertEquals("SUCC", ret["responseCode"], std::to_string(__LINE__), ret.dump());

	ret = json::parse(v.DeleteGroup(groupId));
	AssertEquals(200, ret["status"], std::to_string(__LINE__), ret.dump());
	AssertEquals("SUCC", ret["responseCode"], std::to_string(__LINE__), ret.dump());

	ret = json::parse(v.GetPhrases("en-US"));
	AssertEquals(200, ret["status"], std::to_string(__LINE__), ret.dump());
	AssertEquals("SUCC", ret["responseCode"], std::to_string(__LINE__), ret.dump());
	std::cout << "****Test Basics All Passed****" << std::endl;

	// Test Video

	ret = json::parse(v.CreateUser());
	userId1 = ret["userId"].get<std::string>();
	ret = json::parse(v.CreateUser());
	userId2 = ret["userId"].get<std::string>();
	ret = json::parse(v.CreateGroup("Sample Group Description"));
	groupId = ret["groupId"].get<std::string>();
	v.AddUserToGroup(groupId, userId1);
	v.AddUserToGroup(groupId, userId2);
	// Video Enrollments


	DownloadFile("./videoEnrollmentB1.mov", "https://s3.amazonaws.com/voiceit-api2-testing-files/test-data/videoEnrollmentB1.mov");
	DownloadFile("./videoEnrollmentB2.mov", "https://s3.amazonaws.com/voiceit-api2-testing-files/test-data/videoEnrollmentB2.mov");
	DownloadFile("./videoEnrollmentB3.mov", "https://s3.amazonaws.com/voiceit-api2-testing-files/test-data/videoEnrollmentB3.mov");
	DownloadFile("./videoVerificationB1.mov", "https://s3.amazonaws.com/voiceit-api2-testing-files/test-data/videoVerificationB1.mov");
	DownloadFile("./videoEnrollmentC1.mov", "https://s3.amazonaws.com/voiceit-api2-testing-files/test-data/videoEnrollmentC1.mov");
	DownloadFile("./videoEnrollmentC2.mov", "https://s3.amazonaws.com/voiceit-api2-testing-files/test-data/videoEnrollmentC2.mov");
	DownloadFile("./videoEnrollmentC3.mov", "https://s3.amazonaws.com/voiceit-api2-testing-files/test-data/videoEnrollmentC3.mov");

	ret = json::parse(v.CreateVideoEnrollment(userId1, "en-US", "never forget tomorrow is a new day", "./videoEnrollmentB1.mov"));
	AssertEquals(201, ret["status"], std::to_string(__LINE__), ret.dump());
	AssertEquals("SUCC", ret["responseCode"], std::to_string(__LINE__), ret.dump());
	enrollmentId1 = ret["id"].get<int>();
	ret = json::parse(v.CreateVideoEnrollment(userId1, "en-US", "never forget tomorrow is a new day", "./videoEnrollmentB2.mov"));
	AssertEquals(201, ret["status"], std::to_string(__LINE__), ret.dump());
	AssertEquals("SUCC", ret["responseCode"], std::to_string(__LINE__), ret.dump());
	ret = json::parse(v.CreateVideoEnrollment(userId1, "en-US", "never forget tomorrow is a new day", "./videoEnrollmentB3.mov"));
	AssertEquals(201, ret["status"], std::to_string(__LINE__), ret.dump());
	AssertEquals("SUCC", ret["responseCode"], std::to_string(__LINE__), ret.dump());


	ret = json::parse(v.CreateVideoEnrollment(userId2, "en-US", "never forget tomorrow is a new day", "./videoEnrollmentC1.mov"));
	AssertEquals(201, ret["status"], std::to_string(__LINE__), ret.dump());
	AssertEquals("SUCC", ret["responseCode"], std::to_string(__LINE__), ret.dump());
	ret = json::parse(v.CreateVideoEnrollment(userId2, "en-US", "never forget tomorrow is a new day", "./videoEnrollmentC2.mov"));
	AssertEquals(201, ret["status"], std::to_string(__LINE__), ret.dump());
	AssertEquals("SUCC", ret["responseCode"], std::to_string(__LINE__), ret.dump());
	ret = json::parse(v.CreateVideoEnrollment(userId2, "en-US", "never forget tomorrow is a new day", "./videoEnrollmentC3.mov"));
	AssertEquals(201, ret["status"], std::to_string(__LINE__), ret.dump());
	AssertEquals("SUCC", ret["responseCode"], std::to_string(__LINE__), ret.dump());

	// Video Verification
	ret = json::parse(v.VideoVerification(userId1, "en-US", "never forget tomorrow is a new day", "./videoVerificationB1.mov"));
	AssertEquals(200, ret["status"], std::to_string(__LINE__), ret.dump());
	AssertEquals("SUCC", ret["responseCode"], std::to_string(__LINE__), ret.dump());

	// Video Identification
	ret = json::parse(v.VideoIdentification(groupId, "en-US", "never forget tomorrow is a new day", "./videoVerificationB1.mov"));
	AssertEquals(200, ret["status"], std::to_string(__LINE__), ret.dump());
	AssertEquals("SUCC", ret["responseCode"], std::to_string(__LINE__), ret.dump());
	AssertEquals(userId1, ret["userId"], std::to_string(__LINE__), ret.dump());

	// Delete Enrollment
	ret = json::parse(v.DeleteVideoEnrollment(userId1, enrollmentId1));
	AssertEquals(200, ret["status"], std::to_string(__LINE__), ret.dump());
	AssertEquals("SUCC", ret["responseCode"], std::to_string(__LINE__), ret.dump());

	// Delete All Enrollments
	ret = json::parse(v.DeleteAllEnrollments(userId1));
	AssertEquals(200, ret["status"], std::to_string(__LINE__), ret.dump());
	AssertEquals("SUCC", ret["responseCode"], std::to_string(__LINE__), ret.dump());
	v.DeleteAllEnrollments(userId2);

	// Reset for ...ByUrl operations
	v.DeleteUser(userId1);
	v.DeleteUser(userId2);
	v.DeleteGroup(groupId);

	ret = json::parse(v.CreateUser());
	userId1 = ret["userId"].get<std::string>();
	ret = json::parse(v.CreateUser());
	userId2 = ret["userId"].get<std::string>();
	ret = json::parse(v.CreateGroup("Sample Group Description"));
	groupId = ret["groupId"].get<std::string>();
	v.AddUserToGroup(groupId, userId1);
	v.AddUserToGroup(groupId, userId2);

	// Video Enrollment By URL
	ret = json::parse(v.CreateVideoEnrollmentByUrl(userId1, "en-US", "never forget tomorrow is a new day", "https://s3.amazonaws.com/voiceit-api2-testing-files/test-data/videoEnrollmentB1.mov"));
	AssertEquals(201, ret["status"], std::to_string(__LINE__), ret.dump());
	AssertEquals("SUCC", ret["responseCode"], std::to_string(__LINE__), ret.dump());
	ret = json::parse(v.CreateVideoEnrollmentByUrl(userId1, "en-US", "never forget tomorrow is a new day", "https://s3.amazonaws.com/voiceit-api2-testing-files/test-data/videoEnrollmentB2.mov"));
	AssertEquals(201, ret["status"], std::to_string(__LINE__), ret.dump());
	AssertEquals("SUCC", ret["responseCode"], std::to_string(__LINE__), ret.dump());
	ret = json::parse(v.CreateVideoEnrollmentByUrl(userId1, "en-US", "never forget tomorrow is a new day", "https://s3.amazonaws.com/voiceit-api2-testing-files/test-data/videoEnrollmentB3.mov"));
	AssertEquals(201, ret["status"], std::to_string(__LINE__), ret.dump());
	AssertEquals("SUCC", ret["responseCode"], std::to_string(__LINE__), ret.dump());
	ret = json::parse(v.CreateVideoEnrollmentByUrl(userId2, "en-US", "never forget tomorrow is a new day", "https://s3.amazonaws.com/voiceit-api2-testing-files/test-data/videoEnrollmentC1.mov"));
	AssertEquals(201, ret["status"], std::to_string(__LINE__), ret.dump());
	AssertEquals("SUCC", ret["responseCode"], std::to_string(__LINE__), ret.dump());
	ret = json::parse(v.CreateVideoEnrollmentByUrl(userId2, "en-US", "never forget tomorrow is a new day", "https://s3.amazonaws.com/voiceit-api2-testing-files/test-data/videoEnrollmentC2.mov"));
	AssertEquals(201, ret["status"], std::to_string(__LINE__), ret.dump());
	AssertEquals("SUCC", ret["responseCode"], std::to_string(__LINE__), ret.dump());
	ret = json::parse(v.CreateVideoEnrollmentByUrl(userId2, "en-US", "never forget tomorrow is a new day", "https://s3.amazonaws.com/voiceit-api2-testing-files/test-data/videoEnrollmentC3.mov"));
	AssertEquals(201, ret["status"], std::to_string(__LINE__), ret.dump());
	AssertEquals("SUCC", ret["responseCode"], std::to_string(__LINE__), ret.dump());


	// Video Verification By URL
	ret = json::parse(v.VideoVerificationByUrl(userId1, "en-US", "never forget tomorrow is a new day", "https://s3.amazonaws.com/voiceit-api2-testing-files/test-data/videoVerificationB1.mov"));
	AssertEquals(200, ret["status"], std::to_string(__LINE__), ret.dump());
	AssertEquals("SUCC", ret["responseCode"], std::to_string(__LINE__), ret.dump());

	// Video Identification By URL
	ret = json::parse(v.VideoIdentificationByUrl(groupId, "en-US", "never forget tomorrow is a new day", "https://s3.amazonaws.com/voiceit-api2-testing-files/test-data/videoVerificationB1.mov"));
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


	ret = json::parse(v.CreateUser());
	userId1 = ret["userId"].get<std::string>();
	ret = json::parse(v.CreateUser());
	userId2 = ret["userId"].get<std::string>();
	ret = json::parse(v.CreateGroup("Sample Group Description"));
	groupId = ret["groupId"].get<std::string>();
	v.AddUserToGroup(groupId, userId1);
	v.AddUserToGroup(groupId, userId2);

	// Voice Enrollments

	DownloadFile("./enrollmentA1.wav", "https://s3.amazonaws.com/voiceit-api2-testing-files/test-data/enrollmentA1.wav");
	DownloadFile("./enrollmentA2.wav", "https://s3.amazonaws.com/voiceit-api2-testing-files/test-data/enrollmentA2.wav");
	DownloadFile("./enrollmentA3.wav", "https://s3.amazonaws.com/voiceit-api2-testing-files/test-data/enrollmentA3.wav");
	DownloadFile("./verificationA1.wav", "https://s3.amazonaws.com/voiceit-api2-testing-files/test-data/verificationA1.wav");
	DownloadFile("./enrollmentC1.wav", "https://s3.amazonaws.com/voiceit-api2-testing-files/test-data/enrollmentC1.wav");
	DownloadFile("./enrollmentC2.wav", "https://s3.amazonaws.com/voiceit-api2-testing-files/test-data/enrollmentC2.wav");
	DownloadFile("./enrollmentC3.wav", "https://s3.amazonaws.com/voiceit-api2-testing-files/test-data/enrollmentC3.wav");

	ret = json::parse(v.CreateVoiceEnrollment(userId1, "en-US", "never forget tomorrow is a new day", "./enrollmentA1.wav"));
	AssertEquals(201, ret["status"], std::to_string(__LINE__), ret.dump());
	AssertEquals("SUCC", ret["responseCode"], std::to_string(__LINE__), ret.dump());
	ret = json::parse(v.CreateVoiceEnrollment(userId1, "en-US", "never forget tomorrow is a new day", "./enrollmentA2.wav"));
	AssertEquals(201, ret["status"], std::to_string(__LINE__), ret.dump());
	AssertEquals("SUCC", ret["responseCode"], std::to_string(__LINE__), ret.dump());
	ret = json::parse(v.CreateVoiceEnrollment(userId1, "en-US", "never forget tomorrow is a new day", "./enrollmentA3.wav"));
	AssertEquals(201, ret["status"], std::to_string(__LINE__), ret.dump());
	AssertEquals("SUCC", ret["responseCode"], std::to_string(__LINE__), ret.dump());


	ret = json::parse(v.CreateVoiceEnrollment(userId2, "en-US", "never forget tomorrow is a new day", "./enrollmentC1.wav"));
	AssertEquals(201, ret["status"], std::to_string(__LINE__), ret.dump());
	AssertEquals("SUCC", ret["responseCode"], std::to_string(__LINE__), ret.dump());
	ret = json::parse(v.CreateVoiceEnrollment(userId2, "en-US", "never forget tomorrow is a new day", "./enrollmentC2.wav"));
	AssertEquals(201, ret["status"], std::to_string(__LINE__), ret.dump());
	AssertEquals("SUCC", ret["responseCode"], std::to_string(__LINE__), ret.dump());
	ret = json::parse(v.CreateVoiceEnrollment(userId2, "en-US", "never forget tomorrow is a new day", "./enrollmentC3.wav"));
	AssertEquals(201, ret["status"], std::to_string(__LINE__), ret.dump());
	AssertEquals("SUCC", ret["responseCode"], std::to_string(__LINE__), ret.dump());

	// Voice Verification
	ret = json::parse(v.VoiceVerification(userId1, "en-US", "never forget tomorrow is a new day", "./verificationA1.wav"));
	AssertEquals(200, ret["status"], std::to_string(__LINE__), ret.dump());
	AssertEquals("SUCC", ret["responseCode"], std::to_string(__LINE__), ret.dump());

	// Voice Identification
	ret = json::parse(v.VoiceIdentification(groupId, "en-US", "never forget tomorrow is a new day", "./verificationA1.wav"));
	AssertEquals(200, ret["status"], std::to_string(__LINE__), ret.dump());
	AssertEquals("SUCC", ret["responseCode"], std::to_string(__LINE__), ret.dump());
	AssertEquals(userId1, ret["userId"], std::to_string(__LINE__), ret.dump());

	// Reset for ...ByUrl operations
	v.DeleteAllEnrollments(userId1);
	v.DeleteAllEnrollments(userId2);
	v.DeleteUser(userId1);
	v.DeleteUser(userId2);
	v.DeleteGroup(groupId);
	ret = json::parse(v.CreateUser());
	userId1 = ret["userId"].get<std::string>();
	ret = json::parse(v.CreateUser());
	userId2 = ret["userId"].get<std::string>();
	ret = json::parse(v.CreateGroup("Sample Group Description"));
	groupId = ret["groupId"].get<std::string>();
	v.AddUserToGroup(groupId, userId1);
	v.AddUserToGroup(groupId, userId2);

	// Voice Enrollment By URL
	ret = json::parse(v.CreateVoiceEnrollmentByUrl(userId1, "en-US", "never forget tomorrow is a new day", "https://s3.amazonaws.com/voiceit-api2-testing-files/test-data/enrollmentA1.wav"));
	AssertEquals(201, ret["status"], std::to_string(__LINE__), ret.dump());
	AssertEquals("SUCC", ret["responseCode"], std::to_string(__LINE__), ret.dump());
	ret = json::parse(v.CreateVoiceEnrollmentByUrl(userId1, "en-US", "never forget tomorrow is a new day", "https://s3.amazonaws.com/voiceit-api2-testing-files/test-data/enrollmentA2.wav"));
	AssertEquals(201, ret["status"], std::to_string(__LINE__), ret.dump());
	AssertEquals("SUCC", ret["responseCode"], std::to_string(__LINE__), ret.dump());
	ret = json::parse(v.CreateVoiceEnrollmentByUrl(userId1, "en-US", "never forget tomorrow is a new day", "https://s3.amazonaws.com/voiceit-api2-testing-files/test-data/enrollmentA3.wav"));
	AssertEquals(201, ret["status"], std::to_string(__LINE__), ret.dump());
	AssertEquals("SUCC", ret["responseCode"], std::to_string(__LINE__), ret.dump());
	ret = json::parse(v.CreateVoiceEnrollmentByUrl(userId2, "en-US", "never forget tomorrow is a new day", "https://s3.amazonaws.com/voiceit-api2-testing-files/test-data/enrollmentC1.wav"));
	AssertEquals(201, ret["status"], std::to_string(__LINE__), ret.dump());
	AssertEquals("SUCC", ret["responseCode"], std::to_string(__LINE__), ret.dump());
	ret = json::parse(v.CreateVoiceEnrollmentByUrl(userId2, "en-US", "never forget tomorrow is a new day", "https://s3.amazonaws.com/voiceit-api2-testing-files/test-data/enrollmentC2.wav"));
	AssertEquals(201, ret["status"], std::to_string(__LINE__), ret.dump());
	AssertEquals("SUCC", ret["responseCode"], std::to_string(__LINE__), ret.dump());
	ret = json::parse(v.CreateVoiceEnrollmentByUrl(userId2, "en-US", "never forget tomorrow is a new day", "https://s3.amazonaws.com/voiceit-api2-testing-files/test-data/enrollmentC3.wav"));
	AssertEquals(201, ret["status"], std::to_string(__LINE__), ret.dump());
	AssertEquals("SUCC", ret["responseCode"], std::to_string(__LINE__), ret.dump());


	// Voice Verification By URL
	ret = json::parse(v.VoiceVerificationByUrl(userId1, "en-US", "never forget tomorrow is a new day", "https://s3.amazonaws.com/voiceit-api2-testing-files/test-data/verificationA1.wav"));
	AssertEquals(200, ret["status"], std::to_string(__LINE__), ret.dump());
	AssertEquals("SUCC", ret["responseCode"], std::to_string(__LINE__), ret.dump());

	// Voice Identification By URL
	ret = json::parse(v.VoiceIdentificationByUrl(groupId, "en-US", "never forget tomorrow is a new day", "https://s3.amazonaws.com/voiceit-api2-testing-files/test-data/verificationA1.wav"));
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


	ret = json::parse(v.CreateUser());
	userId1 = ret["userId"].get<std::string>();
	ret = json::parse(v.CreateUser());
	userId2 = ret["userId"].get<std::string>();
	ret = json::parse(v.CreateGroup("Sample Group Description"));
	groupId = ret["groupId"].get<std::string>();
	v.AddUserToGroup(groupId, userId1);
	v.AddUserToGroup(groupId, userId2);

	// Face Enrollments

	DownloadFile("./faceEnrollmentB1.mp4", "https://s3.amazonaws.com/voiceit-api2-testing-files/test-data/faceEnrollmentB1.mp4");
	DownloadFile("./faceEnrollmentB2.mp4", "https://s3.amazonaws.com/voiceit-api2-testing-files/test-data/faceEnrollmentB2.mp4");
	DownloadFile("./faceEnrollmentB3.mp4", "https://s3.amazonaws.com/voiceit-api2-testing-files/test-data/faceEnrollmentB3.mp4");
	DownloadFile("./faceVerificationB1.mp4", "https://s3.amazonaws.com/voiceit-api2-testing-files/test-data/faceVerificationB1.mp4");

	ret = json::parse(v.CreateFaceEnrollment(userId1, "./faceEnrollmentB1.mp4"));
	AssertEquals(201, ret["status"], std::to_string(__LINE__), ret.dump());
	AssertEquals("SUCC", ret["responseCode"], std::to_string(__LINE__), ret.dump());
	ret = json::parse(v.CreateFaceEnrollment(userId1, "./faceEnrollmentB2.mp4"));
	AssertEquals(201, ret["status"], std::to_string(__LINE__), ret.dump());
	AssertEquals("SUCC", ret["responseCode"], std::to_string(__LINE__), ret.dump());
	ret = json::parse(v.CreateFaceEnrollment(userId1, "./faceEnrollmentB3.mp4"));
	AssertEquals(201, ret["status"], std::to_string(__LINE__), ret.dump());
	AssertEquals("SUCC", ret["responseCode"], std::to_string(__LINE__), ret.dump());


	ret = json::parse(v.CreateFaceEnrollment(userId2, "./videoEnrollmentC1.mov"));
	AssertEquals(201, ret["status"], std::to_string(__LINE__), ret.dump());
	AssertEquals("SUCC", ret["responseCode"], std::to_string(__LINE__), ret.dump());
	ret = json::parse(v.CreateFaceEnrollment(userId2, "./videoEnrollmentC2.mov"));
	AssertEquals(201, ret["status"], std::to_string(__LINE__), ret.dump());
	AssertEquals("SUCC", ret["responseCode"], std::to_string(__LINE__), ret.dump());
	ret = json::parse(v.CreateFaceEnrollment(userId2, "./videoEnrollmentC3.mov"));
	AssertEquals(201, ret["status"], std::to_string(__LINE__), ret.dump());
	AssertEquals("SUCC", ret["responseCode"], std::to_string(__LINE__), ret.dump());

	// Face Verification
	ret = json::parse(v.FaceVerification(userId1, "./faceVerificationB1.mp4"));
	AssertEquals(200, ret["status"], std::to_string(__LINE__), ret.dump());
	AssertEquals("SUCC", ret["responseCode"], std::to_string(__LINE__), ret.dump());

	// Face Identification
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
	ret = json::parse(v.CreateUser());
	userId1 = ret["userId"].get<std::string>();
	ret = json::parse(v.CreateUser());
	userId2 = ret["userId"].get<std::string>();
	ret = json::parse(v.CreateGroup("Sample Group Description"));
	groupId = ret["groupId"].get<std::string>();
	v.AddUserToGroup(groupId, userId1);
	v.AddUserToGroup(groupId, userId2);

	// Face Enrollment By URL
	ret = json::parse(v.CreateFaceEnrollmentByUrl(userId1, "https://s3.amazonaws.com/voiceit-api2-testing-files/test-data/faceEnrollmentB1.mp4"));
	AssertEquals(201, ret["status"], std::to_string(__LINE__), ret.dump());
	AssertEquals("SUCC", ret["responseCode"], std::to_string(__LINE__), ret.dump());
	ret = json::parse(v.CreateFaceEnrollmentByUrl(userId1, "https://s3.amazonaws.com/voiceit-api2-testing-files/test-data/faceEnrollmentB2.mp4"));
	AssertEquals(201, ret["status"], std::to_string(__LINE__), ret.dump());
	AssertEquals("SUCC", ret["responseCode"], std::to_string(__LINE__), ret.dump());
	ret = json::parse(v.CreateFaceEnrollmentByUrl(userId1, "https://s3.amazonaws.com/voiceit-api2-testing-files/test-data/faceEnrollmentB3.mp4"));
	AssertEquals(201, ret["status"], std::to_string(__LINE__), ret.dump());
	AssertEquals("SUCC", ret["responseCode"], std::to_string(__LINE__), ret.dump());
	ret = json::parse(v.CreateFaceEnrollmentByUrl(userId2, "https://s3.amazonaws.com/voiceit-api2-testing-files/test-data/videoEnrollmentC1.mov"));
	AssertEquals(201, ret["status"], std::to_string(__LINE__), ret.dump());
	AssertEquals("SUCC", ret["responseCode"], std::to_string(__LINE__), ret.dump());
	ret = json::parse(v.CreateFaceEnrollmentByUrl(userId2, "https://s3.amazonaws.com/voiceit-api2-testing-files/test-data/videoEnrollmentC2.mov"));
	AssertEquals(201, ret["status"], std::to_string(__LINE__), ret.dump());
	AssertEquals("SUCC", ret["responseCode"], std::to_string(__LINE__), ret.dump());
	ret = json::parse(v.CreateFaceEnrollmentByUrl(userId2, "https://s3.amazonaws.com/voiceit-api2-testing-files/test-data/videoEnrollmentC3.mov"));
	AssertEquals(201, ret["status"], std::to_string(__LINE__), ret.dump());
	AssertEquals("SUCC", ret["responseCode"], std::to_string(__LINE__), ret.dump());


	// Face Verification By URL
	ret = json::parse(v.FaceVerificationByUrl(userId1, "https://s3.amazonaws.com/voiceit-api2-testing-files/test-data/faceVerificationB1.mp4"));
	AssertEquals(200, ret["status"], std::to_string(__LINE__), ret.dump());
	AssertEquals("SUCC", ret["responseCode"], std::to_string(__LINE__), ret.dump());

	// Face Identification By URL
	ret = json::parse(v.FaceIdentificationByUrl(groupId, "https://s3.amazonaws.com/voiceit-api2-testing-files/test-data/faceVerificationB1.mp4"));
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
	ret = json::parse(v.CreateUser());
	userId = ret["userId"].get<std::string>();
	int videoEnrollmentId = json::parse(v.CreateVideoEnrollmentByUrl(userId, "en-US", "never forget tomorrow is a new day", "https://s3.amazonaws.com/voiceit-api2-testing-files/test-data/videoEnrollmentB1.mov"))["id"];
	v.CreateVideoEnrollmentByUrl(userId, "en-US", "never forget tomorrow is a new day", "https://s3.amazonaws.com/voiceit-api2-testing-files/test-data/videoEnrollmentB2.mov");
	int voiceEnrollmentId = json::parse(v.CreateVoiceEnrollmentByUrl(userId, "en-US", "never forget tomorrow is a new day", "https://s3.amazonaws.com/voiceit-api2-testing-files/test-data/enrollmentA1.wav"))["id"];
	v.CreateVoiceEnrollmentByUrl(userId, "en-US", "never forget tomorrow is a new day", "https://s3.amazonaws.com/voiceit-api2-testing-files/test-data/enrollmentA2.wav");
	int faceEnrollmentId = json::parse(v.CreateFaceEnrollment(userId, "./faceEnrollmentB1.mp4"))["faceEnrollmentId"];
	v.CreateFaceEnrollment(userId, "./faceEnrollmentB2.mp4");

	ret = json::parse(v.DeleteFaceEnrollment(userId, faceEnrollmentId));
	AssertEquals(200, ret["status"], std::to_string(__LINE__), ret.dump());
	AssertEquals("SUCC", ret["responseCode"], std::to_string(__LINE__), ret.dump());
	ret = json::parse(v.DeleteVideoEnrollment(userId, videoEnrollmentId));
	AssertEquals(200, ret["status"], std::to_string(__LINE__), ret.dump());
	AssertEquals("SUCC", ret["responseCode"], std::to_string(__LINE__), ret.dump());
	ret = json::parse(v.DeleteVoiceEnrollment(userId, voiceEnrollmentId));
	AssertEquals(200, ret["status"], std::to_string(__LINE__), ret.dump());
	AssertEquals("SUCC", ret["responseCode"], std::to_string(__LINE__), ret.dump());

	ret = json::parse(v.GetAllVideoEnrollments(userId));
	AssertEquals(200, ret["status"], std::to_string(__LINE__), ret.dump());
	AssertEquals("SUCC", ret["responseCode"], std::to_string(__LINE__), ret.dump());
	AssertEquals(1, ret["count"], std::to_string(__LINE__), ret.dump());
	ret = json::parse(v.GetAllVoiceEnrollments(userId));
	AssertEquals(200, ret["status"], std::to_string(__LINE__), ret.dump());
	AssertEquals("SUCC", ret["responseCode"], std::to_string(__LINE__), ret.dump());
	AssertEquals(1, ret["count"], std::to_string(__LINE__), ret.dump());
	ret = json::parse(v.GetAllFaceEnrollments(userId));
	AssertEquals(200, ret["status"], std::to_string(__LINE__), ret.dump());
	AssertEquals("SUCC", ret["responseCode"], std::to_string(__LINE__), ret.dump());
	AssertEquals(1, ret["count"], std::to_string(__LINE__), ret.dump());

	v.DeleteAllEnrollments(userId);
	std::cout << "****Delete Enrollment All Passed****" << std::endl;

	// Test Delete Enrollments
	v.CreateVideoEnrollmentByUrl(userId, "en-US", "never forget tomorrow is a new day", "https://s3.amazonaws.com/voiceit-api2-testing-files/test-data/videoEnrollmentB1.mov");
	v.CreateVideoEnrollmentByUrl(userId, "en-US", "never forget tomorrow is a new day", "https://s3.amazonaws.com/voiceit-api2-testing-files/test-data/videoEnrollmentB2.mov");
	v.CreateVoiceEnrollmentByUrl(userId, "en-US", "never forget tomorrow is a new day", "https://s3.amazonaws.com/voiceit-api2-testing-files/test-data/enrollmentA1.wav");
	v.CreateVoiceEnrollmentByUrl(userId, "en-US", "never forget tomorrow is a new day", "https://s3.amazonaws.com/voiceit-api2-testing-files/test-data/enrollmentA2.wav");
	v.CreateFaceEnrollment(userId, "./faceEnrollmentB1.mp4");
	v.CreateFaceEnrollment(userId, "./faceEnrollmentB2.mp4");

	ret = json::parse(v.DeleteAllVideoEnrollments(userId));
	AssertEquals(200, ret["status"], std::to_string(__LINE__), ret.dump());
	AssertEquals("SUCC", ret["responseCode"], std::to_string(__LINE__), ret.dump());
	ret = json::parse(v.DeleteAllVoiceEnrollments(userId));
	AssertEquals(200, ret["status"], std::to_string(__LINE__), ret.dump());
	AssertEquals("SUCC", ret["responseCode"], std::to_string(__LINE__), ret.dump());
	ret = json::parse(v.DeleteAllFaceEnrollments(userId));
	AssertEquals(200, ret["status"], std::to_string(__LINE__), ret.dump());
	AssertEquals("SUCC", ret["responseCode"], std::to_string(__LINE__), ret.dump());
	AssertEquals(0, json::parse(v.GetAllVideoEnrollments(userId))["count"], std::to_string(__LINE__), ret.dump());
	AssertEquals(0, json::parse(v.GetAllVoiceEnrollments(userId))["count"], std::to_string(__LINE__), ret.dump());
	AssertEquals(0, json::parse(v.GetAllFaceEnrollments(userId))["count"], std::to_string(__LINE__), ret.dump());
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
