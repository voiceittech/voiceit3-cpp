#include <string>
#include <iostream>
#include <fstream>
#include <cpr/cpr.h>
#include "json.hpp"

using json = nlohmann::json;

class VoiceIt2
{
  private:
    cpr::Authentication *auth;
    const std::string baseUrl = "https://api.voiceit.io";
    cpr::Header *platformHeader;

    void FileExists(std::string path) {
      std::ifstream file(path);
      if(file.fail()) {
        throw std::string("No such file: " + path);
      }
    }

  public:

    VoiceIt2(std::string key, std::string token)
    {
      auth = new cpr::Authentication(key, token);
      platformHeader = new cpr::Header{{"platformId", "34"}};
    }

    json GetAllUsers()
    {
      const auto reqResponse = cpr::Get(cpr::Url{baseUrl + "/users"}, *auth, *platformHeader);
      return json::parse(reqResponse.text);
    }

    json CreateUser()
    {
      const auto reqResponse = cpr::Post(cpr::Url{ baseUrl + "/users"}, *auth, *platformHeader);
      return json::parse(reqResponse.text);
    }

    json DeleteUser(std::string userId)
    {
      const auto reqResponse = cpr::Delete(cpr::Url{ baseUrl + "/users/" + userId}, *auth, *platformHeader);
      return json::parse(reqResponse.text);
    }

    json GetGroupsForUser(std::string userId)
    {
      const auto reqResponse = cpr::Get(cpr::Url{ baseUrl + "/users/" + userId + "/groups"}, *auth, *platformHeader);
      return json::parse(reqResponse.text);
    }

    json CheckUserExists(std::string userId)
    {
      const auto reqResponse = cpr::Get(cpr::Url{baseUrl + "/users/" + userId}, *auth, *platformHeader);
      return json::parse(reqResponse.text);
    }

    json GetAllGroups()
    {
      const auto reqResponse = cpr::Get(cpr::Url{baseUrl + "/groups"}, *auth, *platformHeader);
      return json::parse(reqResponse.text);
    }

    json GetGroup(std::string groupId)
    {
      const auto reqResponse = cpr::Get(cpr::Url{baseUrl + "/groups/" + groupId}, *auth, *platformHeader);
      return json::parse(reqResponse.text);
    }

    json CheckGroupExists(std::string groupId)
    {
      const auto reqResponse = cpr::Get(cpr::Url{baseUrl + "/groups/" + groupId + "/exists"}, *auth, *platformHeader);
      return json::parse(reqResponse.text);
    }

    json CreateGroup(std::string description="")
    {
      const auto reqResponse = cpr::Post(cpr::Url{baseUrl + "/groups"}, *auth, *platformHeader, cpr::Parameters{{"description", description}});
      return json::parse(reqResponse.text);
    }

    json AddUserToGroup(std::string groupId, std::string userId)
    {
      const auto reqResponse = cpr::Put(cpr::Url{baseUrl + "/groups/addUser"}, *auth, *platformHeader, cpr::Parameters{{"groupId", groupId}, {"userId", userId}});
      return json::parse(reqResponse.text);
    }

    json RemoveUserFromGroup(std::string groupId, std::string userId)
    {
      const auto reqResponse = cpr::Put(cpr::Url{baseUrl + "/groups/removeUser"}, *auth, *platformHeader, cpr::Parameters{{"groupId", groupId}, {"userId", userId}});
      return json::parse(reqResponse.text);
    }

    json DeleteGroup(std::string groupId)
    {
      const auto reqResponse = cpr::Delete(cpr::Url{baseUrl + "/groups/" + groupId}, *auth, *platformHeader);
      return json::parse(reqResponse.text);
    }

    json GetAllVideoEnrollments(std::string userId)
    {
      const auto reqResponse = cpr::Get(cpr::Url{baseUrl + "/enrollments/video/" + userId}, *auth, *platformHeader);
      return json::parse(reqResponse.text);
    }

    json GetAllVoiceEnrollments(std::string userId)
    {
      const auto reqResponse = cpr::Get(cpr::Url{baseUrl + "/enrollments/voice/" + userId}, *auth, *platformHeader);
      return json::parse(reqResponse.text);
    }

    json GetAllFaceEnrollments(std::string userId)
    {
      const auto reqResponse = cpr::Get(cpr::Url{baseUrl + "/enrollments/face/" + userId}, *auth, *platformHeader);
      return json::parse(reqResponse.text);
    }

    json CreateVoiceEnrollment(std::string userId, std::string contentLanguage, std::string phrase, std::string filePath)
    {
      FileExists(filePath);
      const auto reqResponse = cpr::Post(cpr::Url{baseUrl + "/enrollments/voice"}, *auth, *platformHeader, cpr::Multipart{{"userId", userId}, {"contentLanguage", contentLanguage}, {"phrase", phrase}, {"recording", cpr::File{filePath}}});
      return json::parse(reqResponse.text);
    }

    json CreateVoiceEnrollmentByUrl(std::string userId, std::string contentLanguage, std::string phrase, std::string fileUrl)
    {
      const auto reqResponse = cpr::Post(cpr::Url{baseUrl + "/enrollments/voice/byUrl"}, *auth, *platformHeader, cpr::Multipart{{"userId", userId}, {"contentLanguage", contentLanguage}, {"phrase", phrase}, {"fileUrl", fileUrl}});
      return json::parse(reqResponse.text);
    }

    json CreateFaceEnrollment(std::string userId, std::string filePath)
    {
      FileExists(filePath);
      const auto reqResponse = cpr::Post(cpr::Url{baseUrl + "/enrollments/face"}, *auth, *platformHeader, cpr::Multipart{{"userId", userId}, {"video", cpr::File{filePath}}});
      return json::parse(reqResponse.text);
    }

    json CreateFaceEnrollmentByUrl(std::string userId, std::string fileUrl)
    {
      const auto reqResponse = cpr::Post(cpr::Url{baseUrl + "/enrollments/face/byUrl"}, *auth, *platformHeader, cpr::Multipart{{"userId", userId}, {"fileUrl", fileUrl}});
      return json::parse(reqResponse.text);
    }

    json CreateVideoEnrollment(std::string userId, std::string contentLanguage, std::string phrase, std::string filePath)
    {
      FileExists(filePath);
      const auto reqResponse = cpr::Post(cpr::Url{baseUrl + "/enrollments/video"}, *auth, *platformHeader, cpr::Multipart{{"userId", userId}, {"contentLanguage", contentLanguage}, {"phrase", phrase}, {"video", cpr::File{filePath}}});
      return json::parse(reqResponse.text);
    }

    json CreateVideoEnrollmentByUrl(std::string userId, std::string contentLanguage, std::string phrase, std::string fileUrl)
    {
      const auto reqResponse = cpr::Post(cpr::Url{baseUrl + "/enrollments/video/byUrl"}, *auth, *platformHeader, cpr::Multipart{{"userId", userId}, {"contentLanguage", contentLanguage}, {"phrase", phrase}, {"fileUrl", fileUrl}});
      return json::parse(reqResponse.text);
    }

    json DeleteVideoEnrollment(std::string userId, int enrollmentId)
    {
      std::string stringEnrollmentId = std::to_string(enrollmentId);
      const auto reqResponse = cpr::Delete(cpr::Url{baseUrl + "/enrollments/video/" + userId + "/" + stringEnrollmentId}, *auth, *platformHeader);
      return json::parse(reqResponse.text);
    }

    json DeleteAllVideoEnrollments(std::string userId)
    {
      const auto reqResponse = cpr::Delete(cpr::Url{baseUrl + "/enrollments/" + userId + "/video"}, *auth, *platformHeader);
      return json::parse(reqResponse.text);
    }

    json DeleteVoiceEnrollment(std::string userId, int enrollmentId)
    {
      std::string stringEnrollmentId = std::to_string(enrollmentId);
      const auto reqResponse = cpr::Delete(cpr::Url{baseUrl + "/enrollments/voice/" + userId + "/" + stringEnrollmentId}, *auth, *platformHeader);
      return json::parse(reqResponse.text);
    }

    json DeleteAllVoiceEnrollments(std::string userId)
    {
      const auto reqResponse = cpr::Delete(cpr::Url{baseUrl + "/enrollments/" + userId + "/voice"}, *auth, *platformHeader);
      return json::parse(reqResponse.text);
    }

    json DeleteFaceEnrollment(std::string userId, int faceEnrollmentId)
    {
      std::string stringFaceEnrollmentId = std::to_string(faceEnrollmentId);
      const auto reqResponse = cpr::Delete(cpr::Url{baseUrl + "/enrollments/face/" + userId + "/" + stringFaceEnrollmentId}, *auth, *platformHeader);
      return json::parse(reqResponse.text);
    }

    json DeleteAllFaceEnrollments(std::string userId)
    {
      const auto reqResponse = cpr::Delete(cpr::Url{baseUrl + "/enrollments/" + userId + "/face"}, *auth, *platformHeader);
      return json::parse(reqResponse.text);
    }

    json DeleteAllEnrollmentsForUser(std::string userId)
    {
      const auto reqResponse = cpr::Delete(cpr::Url{baseUrl + "/enrollments/" + userId + "/all"}, *auth, *platformHeader);
      return json::parse(reqResponse.text);
    }

    json VoiceVerification(std::string userId, std::string contentLanguage, std::string phrase, std::string filePath)
    {
      FileExists(filePath);
      const auto reqResponse = cpr::Post(cpr::Url{baseUrl + "/verification/voice"}, *auth, *platformHeader, cpr::Multipart{{"userId", userId}, {"contentLanguage", contentLanguage}, {"phrase", phrase}, {"recording", cpr::File{filePath}}});
      return json::parse(reqResponse.text);
    }


    json VoiceVerificationByUrl(std::string userId, std::string contentLanguage, std::string phrase, std::string fileUrl)
    {
      const auto reqResponse = cpr::Post(cpr::Url{baseUrl + "/verification/voice/byUrl"}, *auth, *platformHeader, cpr::Multipart{{"userId", userId}, {"contentLanguage", contentLanguage}, {"phrase", phrase}, {"fileUrl", fileUrl}});
      return json::parse(reqResponse.text);
    }

    json FaceVerification(std::string userId, std::string filePath)
    {
      FileExists(filePath);
      const auto reqResponse = cpr::Post(cpr::Url{baseUrl + "/verification/face"}, *auth, *platformHeader, cpr::Multipart{{"userId", userId}, {"video", cpr::File{filePath}}});
      return json::parse(reqResponse.text);
    }

    json FaceVerificationByUrl(std::string userId, std::string fileUrl)
    {
      const auto reqResponse = cpr::Post(cpr::Url{baseUrl + "/verification/face/byUrl"}, *auth, *platformHeader, cpr::Multipart{{"userId", userId}, {"fileUrl", fileUrl}});
      return json::parse(reqResponse.text);
    }

    json VideoVerification(std::string userId, std::string contentLanguage, std::string phrase, std::string filePath)
    {
      FileExists(filePath);
      const auto reqResponse = cpr::Post(cpr::Url{baseUrl + "/verification/video"}, *auth, *platformHeader, cpr::Multipart{{"userId", userId}, {"contentLanguage", contentLanguage}, {"phrase", phrase}, {"video", cpr::File{filePath}}});
      return json::parse(reqResponse.text);
    }

    json VideoVerificationByUrl(std::string userId, std::string contentLanguage, std::string phrase, std::string fileUrl)
    {
      const auto reqResponse = cpr::Post(cpr::Url{baseUrl + "/verification/video/byUrl"}, *auth, *platformHeader, cpr::Multipart{{"userId", userId}, {"contentLanguage", contentLanguage}, {"phrase", phrase}, {"fileUrl", fileUrl}});
      return json::parse(reqResponse.text);
    }

    json VoiceIdentification(std::string groupId, std::string contentLanguage, std::string phrase, std::string filePath)
    {
      FileExists(filePath);
      const auto reqResponse = cpr::Post(cpr::Url{baseUrl + "/identification/voice"}, *auth, *platformHeader, cpr::Multipart{{"groupId", groupId}, {"contentLanguage", contentLanguage}, {"phrase", phrase}, {"recording", cpr::File{filePath}}});
      return json::parse(reqResponse.text);
    }

    json VoiceIdentificationByUrl(std::string groupId, std::string contentLanguage, std::string phrase, std::string fileUrl)
    {
      const auto reqResponse = cpr::Post(cpr::Url{baseUrl + "/identification/voice/byUrl"}, *auth, *platformHeader, cpr::Multipart{{"groupId", groupId}, {"contentLanguage", contentLanguage}, {"phrase", phrase}, {"fileUrl", fileUrl}});
      return json::parse(reqResponse.text);
    }

    json VideoIdentification(std::string groupId, std::string contentLanguage, std::string phrase, std::string filePath)
    {
      FileExists(filePath);
      const auto reqResponse = cpr::Post(cpr::Url{baseUrl + "/identification/video"}, *auth, *platformHeader, cpr::Multipart{{"groupId", groupId}, {"contentLanguage", contentLanguage}, {"phrase", phrase}, {"video", cpr::File{filePath}}});
      return json::parse(reqResponse.text);
    }

    json VideoIdentificationByUrl(std::string groupId, std::string contentLanguage, std::string phrase, std::string fileUrl)
    {
      const auto reqResponse = cpr::Post(cpr::Url{baseUrl + "/identification/video/byUrl"}, *auth, *platformHeader, cpr::Multipart{{"groupId", groupId}, {"contentLanguage", contentLanguage}, {"phrase", phrase}, {"fileUrl", fileUrl}});
      return json::parse(reqResponse.text);
    }

    json FaceIdentification(std::string groupId, std::string filePath)
    {
      FileExists(filePath);
      const auto reqResponse = cpr::Post(cpr::Url{baseUrl + "/identification/face"}, *auth, *platformHeader, cpr::Multipart{{"groupId", groupId}, {"video", cpr::File{filePath}}});
      return json::parse(reqResponse.text);
    }

    json FaceIdentificationByUrl(std::string groupId, std::string fileUrl)
    {
      const auto reqResponse = cpr::Post(cpr::Url{baseUrl + "/identification/face/byUrl"}, *auth, *platformHeader, cpr::Multipart{{"groupId", groupId}, {"fileUrl", fileUrl}});
      return json::parse(reqResponse.text);
    }

    json GetPhrases(std::string contentLanguage)
    {
      const auto reqResponse = cpr::Get(cpr::Url{baseUrl + "/phrases/" + contentLanguage}, *auth, *platformHeader);
      return json::parse(reqResponse.text);
    }
  };
