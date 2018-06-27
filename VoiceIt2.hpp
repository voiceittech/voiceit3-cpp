#include <string>
#include <iostream>
#include <cpr/cpr.h>

#include "json.hpp"

using json = nlohmann::json;

class VoiceIt2
{
  private:
    cpr::Authentication *auth;
    const std::string baseUrl = "https://api.voiceit.io";

  public:

    VoiceIt2(std::string key, std::string token)
    {
      auth = new cpr::Authentication(key, token);
    }

    json GetAllUsers()
    {
      const auto reqResponse = cpr::Get(cpr::Url{baseUrl + "/users"}, *auth);
      return json::parse(reqResponse.text);
    }

    json CreateUser()
    {
      const auto reqResponse = cpr::Post(cpr::Url{ baseUrl + "/users"}, *auth);
      return json::parse(reqResponse.text);
    }

    json CheckUserExists(std::string userId)
    {
      const auto reqResponse = cpr::Get(cpr::Url{baseUrl + "/users/" + userId}, *auth);
      return json::parse(reqResponse.text);
    }

    json GetAllGroups()
    {
      const auto reqResponse = cpr::Get(cpr::Url{baseUrl + "/groups"}, *auth);
      return json::parse(reqResponse.text);
    }

    json GetGroup(std::string groupId)
    {
      const auto reqResponse = cpr::Get(cpr::Url{baseUrl + "/groups/" + groupId}, *auth);
      return json::parse(reqResponse.text);
    }

    json CheckGroupExists(std::string groupId)
    {
      const auto reqResponse = cpr::Get(cpr::Url{baseUrl + "/groups/" + groupId + "/exists"}, *auth);
      return json::parse(reqResponse.text);
    }

    json CreateGroup(std::string description="")
    {
      const auto reqResponse = cpr::Post(cpr::Url{baseUrl + "/groups"}, *auth, cpr::Parameters{{"description", description}});
      return json::parse(reqResponse.text);
    }

    json AddUserToGroup(std::string groupId, std::string userId)
    {
      const auto reqResponse = cpr::Put(cpr::Url{baseUrl + "/groups/addUser"}, *auth, cpr::Parameters{{"groupId", groupId}, {"userId", userId}});
      return json::parse(reqResponse.text);
    }

    json RemoveUserFromGroup(std::string groupId, std::string userId)
    {
      const auto reqResponse = cpr::Put(cpr::Url{baseUrl + "/groups/removeUser"}, *auth, cpr::Parameters{{"groupId", groupId}, {"userId", userId}});
      return json::parse(reqResponse.text);
    }

    json DeleteGroup(std::string groupId)
    {
      const auto reqResponse = cpr::Delete(cpr::Url{baseUrl + "/groups/" + groupId}, *auth);
      return json::parse(reqResponse.text);
    }

    json GetAllEnrollmentsForUser(std::string userId)
    {
      const auto reqResponse = cpr::Get(cpr::Url{baseUrl + "/enrollments/" + userId}, *auth);
      return json::parse(reqResponse.text);
    }

    json GetFaceEnrollmentsForUser(std::string userId)
    {
      const auto reqResponse = cpr::Get(cpr::Url{baseUrl + "/enrollments/face/" + userId}, *auth);
      return json::parse(reqResponse.text);
    }

    json CreateVoiceEnrollment(std::string userId, std::string contentLanguage, std::string filePath)
    {
      const auto reqResponse = cpr::Post(cpr::Url{baseUrl + "/enrollments"}, *auth, cpr::Multipart{{"userId", userId}, {"contentLanguage", contentLanguage}, {"recording", cpr::File{filePath}}});
      return json::parse(reqResponse.text);
    }

    json CreateVoiceEnrollmentByUrl(std::string userId, std::string contentLanguage, std::string fileUrl)
    {
      const auto reqResponse = cpr::Post(cpr::Url{baseUrl + "/enrollments/byUrl"}, *auth, cpr::Multipart{{"userId", userId}, {"contentLanguage", contentLanguage}, {"fileUrl", fileUrl}});
      return json::parse(reqResponse.text);
    }

    json CreateFaceEnrollment(std::string userId, std::string filePath, bool doBlinkDetection = false)
    {
      const auto reqResponse = cpr::Post(cpr::Url{baseUrl + "/enrollments/face"}, *auth, cpr::Multipart{{"userId", userId}, {"doBlinkDetection", doBlinkDetection}, {"video", cpr::File{filePath}}});
      return json::parse(reqResponse.text);
    }

    json CreateVideoEnrollment(std::string userId, std::string contentLanguage, std::string filePath, bool doBlinkDetection = false)
    {
      const auto reqResponse = cpr::Post(cpr::Url{baseUrl + "/enrollments/video"}, *auth, cpr::Multipart{{"userId", userId}, {"contentLanguage", contentLanguage}, {"doBlinkDetection", doBlinkDetection}, {"video", cpr::File{filePath}}});
      return json::parse(reqResponse.text);
    }

    json CreateVideoEnrollmentByUrl(std::string userId, std::string contentLanguage, std::string fileUrl, bool doBlinkDetection = false)
    {
      const auto reqResponse = cpr::Post(cpr::Url{baseUrl + "/enrollments/video/byUrl"}, *auth, cpr::Multipart{{"userId", userId}, {"doBlinkDetection", doBlinkDetection}, {"contentLanguage", contentLanguage}, {"fileUrl", fileUrl}});
      return json::parse(reqResponse.text);
    }

    json DeleteFaceEnrollment(std::string userId, int faceEnrollmentId)
    {
      std::string stringFaceEnrollmentId = std::to_string(faceEnrollmentId);
      const auto reqResponse = cpr::Delete(cpr::Url{baseUrl + "/enrollments/face/" + userId + "/" + stringFaceEnrollmentId}, *auth);
      return json::parse(reqResponse.text);
    }

    json DeleteEnrollmentForUser(std::string userId, int enrollmentId)
    {
      std::string stringEnrollmentId = std::to_string(enrollmentId);
      const auto reqResponse = cpr::Delete(cpr::Url{baseUrl + "/enrollments/" + userId + "/" + stringEnrollmentId}, *auth);
      return json::parse(reqResponse.text);
    }

    json DeleteAllEnrollmentsForUser(std::string userId)
    {
      const auto reqResponse = cpr::Delete(cpr::Url{baseUrl + "/enrollments/" + userId + "/all"}, *auth);
      return json::parse(reqResponse.text);
    }

    json VoiceVerification(std::string userId, std::string contentLanguage, std::string filePath)
    {
      const auto reqResponse = cpr::Post(cpr::Url{baseUrl + "/verification"}, *auth, cpr::Multipart{{"userId", userId}, {"contentLanguage", contentLanguage}, {"recording", cpr::File{filePath}}});
      return json::parse(reqResponse.text);
    }


    json VoiceVerificationByUrl(std::string userId, std::string contentLanguage, std::string fileUrl)
    {
      const auto reqResponse = cpr::Post(cpr::Url{baseUrl + "/verification/byUrl"}, *auth, cpr::Multipart{{"userId", userId}, {"contentLanguage", contentLanguage}, {"fileUrl", fileUrl}});
      return json::parse(reqResponse.text);
    }

    json FaceVerification(std::string userId, std::string filePath, bool doBlinkDetection = false)
    {
      const auto reqResponse = cpr::Post(cpr::Url{baseUrl + "/verification/face"}, *auth, cpr::Multipart{{"userId", userId}, {"doBlinkDetection", doBlinkDetection}, {"video", cpr::File{filePath}}});
      return json::parse(reqResponse.text);
    }

    json VideoVerification(std::string userId, std::string contentLanguage, std::string filePath, bool doBlinkDetection = false)
    {
      const auto reqResponse = cpr::Post(cpr::Url{baseUrl + "/verification/video"}, *auth, cpr::Multipart{{"userId", userId}, {"contentLanguage", contentLanguage}, {"doBlinkDetection", doBlinkDetection}, {"video", cpr::File{filePath}}});
      return json::parse(reqResponse.text);
    }

    json VideoVerificationByUrl(std::string userId, std::string contentLanguage, std::string fileUrl, bool doBlinkDetection = false)
    {
      const auto reqResponse = cpr::Post(cpr::Url{baseUrl + "/verification/video/byUrl"}, *auth, cpr::Multipart{{"userId", userId}, {"contentLanguage", contentLanguage}, {"doBlinkDetection", doBlinkDetection}, {"fileUrl", fileUrl}});
      return json::parse(reqResponse.text);
    }

    json VoiceIdentification(std::string groupId, std::string contentLanguage, std::string filePath)
    {
      const auto reqResponse = cpr::Post(cpr::Url{baseUrl + "/identification"}, *auth, cpr::Multipart{{"groupId", groupId}, {"contentLanguage", contentLanguage}, {"recording", cpr::File{filePath}}});
      return json::parse(reqResponse.text);
    }

    json VoiceIdentificationByUrl(std::string groupId, std::string contentLanguage, std::string fileUrl)
    {
      const auto reqResponse = cpr::Post(cpr::Url{baseUrl + "/identification/byUrl"}, *auth, cpr::Multipart{{"groupId", groupId}, {"contentLanguage", contentLanguage}, {"fileUrl", fileUrl}});
      return json::parse(reqResponse.text);
    }

    json VideoIdentification(std::string groupId, std::string contentLanguage, std::string filePath, bool doBlinkDetection = false)
    {
      const auto reqResponse = cpr::Post(cpr::Url{baseUrl + "/identification/video"}, *auth, cpr::Multipart{{"groupId", groupId}, {"contentLanguage", contentLanguage}, {"doBlinkDetection", doBlinkDetection}, {"video", cpr::File{filePath}}});
      return json::parse(reqResponse.text);
    }

    json VideoIdentificationByUrl(std::string groupId, std::string contentLanguage, std::string fileUrl, bool doBlinkDetection = false)
    {
      const auto reqResponse = cpr::Post(cpr::Url{baseUrl + "/identification/video/byUrl"}, *auth, cpr::Multipart{{"groupId", groupId}, {"contentLanguage", contentLanguage}, {"doBlinkDetection", doBlinkDetection}, {"fileUrl", fileUrl}});
      return json::parse(reqResponse.text);
    }

  };
