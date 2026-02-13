#include <string>
#include <iostream>
#include <fstream>
#include <sstream>
#include <curl/curl.h>
#include <curl/easy.h>
#include <cstring>

static std::string readBuffer;

class VoiceIt3
{
  private:
    std::string baseUrl;
    std::string version = "2.5.1";
    std::string notificationUrl;
    std::string auth;
    std::string platformIdHeader;
    std::string platformVersionHeader;


    static size_t WriteCallback(char *contents, size_t size, size_t nmemb)
    {
        size_t realsize = size * nmemb;
        readBuffer.append(contents, realsize);
        return realsize;
    }

    void FileExists(std::string path)
    {
      FILE *file = fopen(path.c_str(), "r");
      if (file)
        fclose(file);
      else
        throw std::string("No such file: " + path);

    }

  public:

    VoiceIt3(std::string key, std::string token)
    {
      baseUrl = "https://qpi.voiceit.io";
      notificationUrl = "";
      auth = key + ":" + token;
      platformIdHeader = "platformId: 34";
      platformVersionHeader = "platformVersion: " + version;
    }

    VoiceIt3(std::string key, std::string token, std::string customUrl)
    {
      baseUrl = customUrl;
      notificationUrl = "";
      auth = key + ":" + token;
      platformIdHeader = "platformId: 34";
      platformVersionHeader = "platformVersion: " + version;
    }

    std::string GetVersion()
    {
      return version;
    }

    void AddNotificationUrl(std::string url)
    {
      CURL *curl;
      curl_global_init(CURL_GLOBAL_ALL);
      curl = curl_easy_init();
      if (curl)
      {
        char *escaped = curl_easy_escape(curl, url.c_str(), 0);
        notificationUrl = std::string(escaped);
        curl_easy_cleanup(curl);
      } else {
        throw std::string("curl_easy_escape() unable to encode string: " + url);
      }
    }

    void RemoveNotificationUrl()
    {
      notificationUrl = "";
    }

    std::string GetNotificationUrl()
    {
      return notificationUrl;
    }

    std::string GetAllUsers()
    {
      CURL *curl;
      curl_global_init(CURL_GLOBAL_ALL);
      curl = curl_easy_init();
      if (curl)
      {
        readBuffer.clear();
        CURLcode res;
        std::stringstream url;
        if (notificationUrl == "")
        {
          url << baseUrl << "/users";
        } else {
          url << baseUrl << "/users?notificationUrl=" << notificationUrl;
        }

        curl_easy_setopt(curl, CURLOPT_URL, url.str().c_str());
        curl_easy_setopt(curl, CURLOPT_HTTPAUTH, CURLAUTH_ANY);
        curl_easy_setopt(curl, CURLOPT_USERPWD, auth.c_str());
        curl_easy_setopt(curl, CURLOPT_CUSTOMREQUEST, "GET");
        struct curl_slist *chunk = NULL;
        chunk = curl_slist_append(chunk, platformVersionHeader.c_str());
        chunk = curl_slist_append(chunk, platformIdHeader.c_str());
        curl_easy_setopt(curl, CURLOPT_HTTPHEADER, chunk);
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &readBuffer);
        res = curl_easy_perform(curl);

        curl_easy_cleanup(curl);
        curl_slist_free_all(chunk);
        return readBuffer;

      } else {
        throw std::string("Cannot initialize curl object. Please ensure you have a working installation of the libcurl Library with the appropriate compile flag.");
      }

    }

    std::string CreateUser()
    {
      CURL *curl;
      curl_global_init(CURL_GLOBAL_ALL);
      curl = curl_easy_init();
      if (curl)
      {
        readBuffer.clear();
        CURLcode res;
        std::stringstream url;
        if (notificationUrl == "")
        {
          url << baseUrl << "/users";
        } else {
          url << baseUrl << "/users?notificationUrl=" << notificationUrl;
        }

        curl_easy_setopt(curl, CURLOPT_URL, url.str().c_str());
        curl_easy_setopt(curl, CURLOPT_HTTPAUTH, CURLAUTH_ANY);
        curl_easy_setopt(curl, CURLOPT_USERPWD, auth.c_str());
        curl_easy_setopt(curl, CURLOPT_CUSTOMREQUEST, "POST");
        struct curl_slist *chunk = NULL;
        chunk = curl_slist_append(chunk, platformVersionHeader.c_str());
        chunk = curl_slist_append(chunk, platformIdHeader.c_str());
        curl_easy_setopt(curl, CURLOPT_HTTPHEADER, chunk);
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &readBuffer);
        res = curl_easy_perform(curl);

        curl_easy_cleanup(curl);
        curl_slist_free_all(chunk);
        return readBuffer;

      } else {
        throw std::string("Cannot initialize curl object. Please ensure you have a working installation of the libcurl Library with the appropriate compile flag.");
      }
    }


    std::string CheckUserExists(std::string userId)
    {
      CURL *curl;
      curl_global_init(CURL_GLOBAL_ALL);
      curl = curl_easy_init();
      if (curl)
      {
        readBuffer.clear();
        CURLcode res;
        std::stringstream url;
        if (notificationUrl == "")
        {
          url << baseUrl << "/users/" << userId;
        } else {
          url << baseUrl << "/users/" << userId << "?notificationUrl=" << notificationUrl;
        }

        curl_easy_setopt(curl, CURLOPT_URL, url.str().c_str());
        curl_easy_setopt(curl, CURLOPT_HTTPAUTH, CURLAUTH_ANY);
        curl_easy_setopt(curl, CURLOPT_USERPWD, auth.c_str());
        curl_easy_setopt(curl, CURLOPT_CUSTOMREQUEST, "GET");
        struct curl_slist *chunk = NULL;
        chunk = curl_slist_append(chunk, platformVersionHeader.c_str());
        chunk = curl_slist_append(chunk, platformIdHeader.c_str());
        curl_easy_setopt(curl, CURLOPT_HTTPHEADER, chunk);
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &readBuffer);
        res = curl_easy_perform(curl);

        curl_easy_cleanup(curl);
        curl_slist_free_all(chunk);
        return readBuffer;

      } else {
        throw std::string("Cannot initialize curl object. Please ensure you have a working installation of the libcurl Library with the appropriate compile flag.");
      }
    }

    std::string DeleteUser(std::string userId)
    {
      CURL *curl;
      curl_global_init(CURL_GLOBAL_ALL);
      curl = curl_easy_init();
      if (curl)
      {
        readBuffer.clear();
        CURLcode res;
        std::stringstream url;
        if (notificationUrl == "")
        {
          url << baseUrl << "/users/" << userId;
        } else {
          url << baseUrl << "/users/" << userId << "?notificationUrl=" << notificationUrl;
        }

        curl_easy_setopt(curl, CURLOPT_URL, url.str().c_str());
        curl_easy_setopt(curl, CURLOPT_HTTPAUTH, CURLAUTH_ANY);
        curl_easy_setopt(curl, CURLOPT_USERPWD, auth.c_str());
        curl_easy_setopt(curl, CURLOPT_CUSTOMREQUEST, "DELETE");
        struct curl_slist *chunk = NULL;
        chunk = curl_slist_append(chunk, platformVersionHeader.c_str());
        chunk = curl_slist_append(chunk, platformIdHeader.c_str());
        curl_easy_setopt(curl, CURLOPT_HTTPHEADER, chunk);
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &readBuffer);
        res = curl_easy_perform(curl);

        curl_easy_cleanup(curl);
        curl_slist_free_all(chunk);
        return readBuffer;

      } else {
        throw std::string("Cannot initialize curl object. Please ensure you have a working installation of the libcurl Library with the appropriate compile flag.");
      }
    }

    std::string GetGroupsForUser(std::string userId)
    {
      CURL *curl;
      curl_global_init(CURL_GLOBAL_ALL);
      curl = curl_easy_init();
      if (curl)
      {
        readBuffer.clear();
        CURLcode res;
        std::stringstream url;
        if (notificationUrl == "")
        {
          url << baseUrl << "/users/" << userId << "/groups";
        } else {
          url << baseUrl << "/users/" << userId << "/groups?notificationUrl=" << notificationUrl;
        }

        curl_easy_setopt(curl, CURLOPT_URL, url.str().c_str());
        curl_easy_setopt(curl, CURLOPT_HTTPAUTH, CURLAUTH_ANY);
        curl_easy_setopt(curl, CURLOPT_USERPWD, auth.c_str());
        curl_easy_setopt(curl, CURLOPT_CUSTOMREQUEST, "GET");
        struct curl_slist *chunk = NULL;
        chunk = curl_slist_append(chunk, platformVersionHeader.c_str());
        chunk = curl_slist_append(chunk, platformIdHeader.c_str());
        curl_easy_setopt(curl, CURLOPT_HTTPHEADER, chunk);
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &readBuffer);
        res = curl_easy_perform(curl);

        curl_easy_cleanup(curl);
        curl_slist_free_all(chunk);
        return readBuffer;

      } else {
        throw std::string("Cannot initialize curl object. Please ensure you have a working installation of the libcurl Library with the appropriate compile flag.");
      }
    }

    std::string CreateUserToken(std::string userId, int secondsToTimeout)
    {
      CURL *curl;
      curl_global_init(CURL_GLOBAL_ALL);
      curl = curl_easy_init();
      if (curl)
      {
        readBuffer.clear();
        CURLcode res;
        std::stringstream url;
        if (notificationUrl == "")
        {
          url << baseUrl << "/users/" << userId << "/token?timeOut=" << secondsToTimeout;
        } else {
          url << baseUrl << "/users/" << userId << "/token?notificationUrl=" << notificationUrl << "t&imeOut=" << secondsToTimeout;
        }

        curl_easy_setopt(curl, CURLOPT_URL, url.str().c_str());
        curl_easy_setopt(curl, CURLOPT_HTTPAUTH, CURLAUTH_ANY);
        curl_easy_setopt(curl, CURLOPT_USERPWD, auth.c_str());
        curl_easy_setopt(curl, CURLOPT_CUSTOMREQUEST, "POST");
        struct curl_slist *chunk = NULL;
        chunk = curl_slist_append(chunk, platformVersionHeader.c_str());
        chunk = curl_slist_append(chunk, platformIdHeader.c_str());
        curl_easy_setopt(curl, CURLOPT_HTTPHEADER, chunk);
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &readBuffer);
        res = curl_easy_perform(curl);

        curl_easy_cleanup(curl);
        curl_slist_free_all(chunk);
        return readBuffer;

      } else {
        throw std::string("Cannot initialize curl object. Please ensure you have a working installation of the libcurl Library with the appropriate compile flag.");
      }
    }

    std::string GetAllGroups()
    {
      CURL *curl;
      curl_global_init(CURL_GLOBAL_ALL);
      curl = curl_easy_init();
      if (curl)
      {
        readBuffer.clear();
        CURLcode res;
        std::stringstream url;
        if (notificationUrl == "")
        {
          url << baseUrl << "/groups";
        } else {
          url << baseUrl << "/groups" << "?notificationUrl=" << notificationUrl;
        }

        curl_easy_setopt(curl, CURLOPT_URL, url.str().c_str());
        curl_easy_setopt(curl, CURLOPT_HTTPAUTH, CURLAUTH_ANY);
        curl_easy_setopt(curl, CURLOPT_USERPWD, auth.c_str());
        curl_easy_setopt(curl, CURLOPT_CUSTOMREQUEST, "GET");
        struct curl_slist *chunk = NULL;
        chunk = curl_slist_append(chunk, platformVersionHeader.c_str());
        chunk = curl_slist_append(chunk, platformIdHeader.c_str());
        curl_easy_setopt(curl, CURLOPT_HTTPHEADER, chunk);
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &readBuffer);
        res = curl_easy_perform(curl);

        curl_easy_cleanup(curl);
        curl_slist_free_all(chunk);
        return readBuffer;

      } else {
        throw std::string("Cannot initialize curl object. Please ensure you have a working installation of the libcurl Library with the appropriate compile flag.");
      }
    }

    std::string GetGroup(std::string groupId)
    {
      CURL *curl;
      curl_global_init(CURL_GLOBAL_ALL);
      curl = curl_easy_init();
      if (curl)
      {
        readBuffer.clear();
        CURLcode res;
        std::stringstream url;
        if (notificationUrl == "")
        {
          url << baseUrl << "/groups/" << groupId;
        } else {
          url << baseUrl << "/groups/" << groupId << "?notificationUrl=" << notificationUrl;
        }

        curl_easy_setopt(curl, CURLOPT_URL, url.str().c_str());
        curl_easy_setopt(curl, CURLOPT_HTTPAUTH, CURLAUTH_ANY);
        curl_easy_setopt(curl, CURLOPT_USERPWD, auth.c_str());
        curl_easy_setopt(curl, CURLOPT_CUSTOMREQUEST, "GET");
        struct curl_slist *chunk = NULL;
        chunk = curl_slist_append(chunk, platformVersionHeader.c_str());
        chunk = curl_slist_append(chunk, platformIdHeader.c_str());
        curl_easy_setopt(curl, CURLOPT_HTTPHEADER, chunk);
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &readBuffer);
        res = curl_easy_perform(curl);

        curl_easy_cleanup(curl);
        curl_slist_free_all(chunk);
        return readBuffer;

      } else {
        throw std::string("Cannot initialize curl object. Please ensure you have a working installation of the libcurl Library with the appropriate compile flag.");
      }
    }

    std::string CheckGroupExists(std::string groupId)
    {
      CURL *curl;
      curl_global_init(CURL_GLOBAL_ALL);
      curl = curl_easy_init();
      if (curl)
      {
        readBuffer.clear();
        CURLcode res;
        std::stringstream url;
        if (notificationUrl == "")
        {
          url << baseUrl << "/groups/" << groupId << "/exists";
        } else {
          url << baseUrl << "/groups/" << groupId << "/exists?notificationUrl=" << notificationUrl;
        }

        curl_easy_setopt(curl, CURLOPT_URL, url.str().c_str());
        curl_easy_setopt(curl, CURLOPT_HTTPAUTH, CURLAUTH_ANY);
        curl_easy_setopt(curl, CURLOPT_USERPWD, auth.c_str());
        curl_easy_setopt(curl, CURLOPT_CUSTOMREQUEST, "GET");
        struct curl_slist *chunk = NULL;
        chunk = curl_slist_append(chunk, platformVersionHeader.c_str());
        chunk = curl_slist_append(chunk, platformIdHeader.c_str());
        curl_easy_setopt(curl, CURLOPT_HTTPHEADER, chunk);
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &readBuffer);
        res = curl_easy_perform(curl);

        curl_easy_cleanup(curl);
        curl_slist_free_all(chunk);
        return readBuffer;

      } else {
        throw std::string("Cannot initialize curl object. Please ensure you have a working installation of the libcurl Library with the appropriate compile flag.");
      }
    }

    std::string CreateManagedSubAccount(std::string firstName, std::string lastName,std::string email,std::string password, std::string contentLanguage )
    {
      CURL *curl;
      curl_global_init(CURL_GLOBAL_ALL);
      curl = curl_easy_init();
      if (curl)
      {
        readBuffer.clear();
        CURLcode res;
        std::stringstream url;
        if (notificationUrl == "")
        {
          url << baseUrl << "/subaccount/managed";
        } else {
          url << baseUrl << "/subaccount/managed" << "?notificationUrl=" << notificationUrl;
        }

        curl_easy_setopt(curl, CURLOPT_URL, url.str().c_str());
        curl_easy_setopt(curl, CURLOPT_HTTPAUTH, CURLAUTH_ANY);
        curl_easy_setopt(curl, CURLOPT_USERPWD, auth.c_str());
        curl_easy_setopt(curl, CURLOPT_CUSTOMREQUEST, "POST");

        struct curl_slist *chunk = NULL;
        chunk = curl_slist_append(chunk, platformVersionHeader.c_str());
        chunk = curl_slist_append(chunk, platformIdHeader.c_str());
        // chunk = curl_slist_append(chunk, "Content-Type: multipart/form-data");
        curl_easy_setopt(curl, CURLOPT_HTTPHEADER, chunk);

        struct curl_httppost *formpost = NULL;
        struct curl_httppost *lastptr = NULL;

        if(firstName != "")
        curl_formadd(&formpost,
             &lastptr,
             CURLFORM_COPYNAME, "firstName",
             CURLFORM_COPYCONTENTS, firstName.c_str(),
             CURLFORM_END);
        if(lastName != "")
        curl_formadd(&formpost,
             &lastptr,
             CURLFORM_COPYNAME, "lastName",
             CURLFORM_COPYCONTENTS, lastName.c_str(),
             CURLFORM_END);

        if(email != "")
        curl_formadd(&formpost,
             &lastptr,
             CURLFORM_COPYNAME, "email",
             CURLFORM_COPYCONTENTS, email.c_str(),
             CURLFORM_END);

        if(password != "")
        curl_formadd(&formpost,
             &lastptr,
             CURLFORM_COPYNAME, "password",
             CURLFORM_FILE, password.c_str(),
             CURLFORM_END);

        if(contentLanguage != "")
        curl_formadd(&formpost,
             &lastptr,
             CURLFORM_COPYNAME, "contentLanguage",
             CURLFORM_FILE, contentLanguage.c_str(),
             CURLFORM_END);


        curl_easy_setopt(curl, CURLOPT_HTTPPOST, formpost);
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &readBuffer);
        res = curl_easy_perform(curl);

        curl_easy_cleanup(curl);
        curl_formfree(formpost);
        curl_slist_free_all(chunk);
        return readBuffer;

      } else {
        throw std::string("Cannot initialize curl object. Please ensure you have a working installation of the libcurl Library with the appropriate compile flag.");
      }
    }



    std::string CreateUnmanagedSubAccount(){
      CURL *curl;
      curl_global_init(CURL_GLOBAL_ALL);
      curl = curl_easy_init();
      if (curl)
      {
        readBuffer.clear();
        CURLcode res;
        std::stringstream url;
        if (notificationUrl == "")
        {
          url << baseUrl << "/subaccount/unmanaged";
        } else {
          url << baseUrl << "/subaccount/unmanaged" << "?notificationUrl=" << notificationUrl;
        }

        curl_easy_setopt(curl, CURLOPT_URL, url.str().c_str());
        curl_easy_setopt(curl, CURLOPT_HTTPAUTH, CURLAUTH_ANY);
        curl_easy_setopt(curl, CURLOPT_USERPWD, auth.c_str());
        curl_easy_setopt(curl, CURLOPT_CUSTOMREQUEST, "POST");

        struct curl_slist *chunk = NULL;
        chunk = curl_slist_append(chunk, platformVersionHeader.c_str());
        chunk = curl_slist_append(chunk, platformIdHeader.c_str());
        chunk = curl_slist_append(chunk, "Content-Type: multipart/form-data");
        curl_easy_setopt(curl, CURLOPT_HTTPHEADER, chunk);

        struct curl_httppost *formpost = NULL;
        struct curl_httppost *lastptr = NULL;
        curl_formadd(&formpost,
             &lastptr,
             CURLFORM_COPYNAME, "description",
             CURLFORM_COPYCONTENTS, "",
             CURLFORM_END);

        curl_easy_setopt(curl, CURLOPT_HTTPPOST, formpost);
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &readBuffer);
        res = curl_easy_perform(curl);

        curl_easy_cleanup(curl);
        curl_formfree(formpost);
        curl_slist_free_all(chunk);
        return readBuffer;

      } else {
        throw std::string("Cannot initialize curl object. Please ensure you have a working installation of the libcurl Library with the appropriate compile flag.");
      }
    }

    std::string RegenerateSubAccountAPIToken(std::string subAccountAPIKey){
       CURL *curl;
      curl_global_init(CURL_GLOBAL_ALL);
      curl = curl_easy_init();
      if (curl)
      {
        readBuffer.clear();
        CURLcode res;
        std::stringstream url;
        if (notificationUrl == "")
        {
          url << baseUrl << "/subaccount/" << subAccountAPIKey;
        } else {
          url << baseUrl << "/subaccount/" << subAccountAPIKey << "?notificationUrl=" << notificationUrl;
        }

        curl_easy_setopt(curl, CURLOPT_URL, url.str().c_str());
        curl_easy_setopt(curl, CURLOPT_HTTPAUTH, CURLAUTH_ANY);
        curl_easy_setopt(curl, CURLOPT_USERPWD, auth.c_str());
        curl_easy_setopt(curl, CURLOPT_CUSTOMREQUEST, "POST");

        struct curl_slist *chunk = NULL;
        chunk = curl_slist_append(chunk, platformVersionHeader.c_str());
        chunk = curl_slist_append(chunk, platformIdHeader.c_str());
        chunk = curl_slist_append(chunk, "Content-Type: multipart/form-data");
        curl_easy_setopt(curl, CURLOPT_HTTPHEADER, chunk);

        struct curl_httppost *formpost = NULL;
        struct curl_httppost *lastptr = NULL;
        curl_formadd(&formpost,
             &lastptr,
             CURLFORM_COPYNAME, "description",
             CURLFORM_COPYCONTENTS, "",
             CURLFORM_END);

        curl_easy_setopt(curl, CURLOPT_HTTPPOST, formpost);
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &readBuffer);
        res = curl_easy_perform(curl);

        curl_easy_cleanup(curl);
        curl_formfree(formpost);
        curl_slist_free_all(chunk);
        return readBuffer;

      } else {
        throw std::string("Cannot initialize curl object. Please ensure you have a working installation of the libcurl Library with the appropriate compile flag.");
      }

    }

    std::string DeleteSubAccount(std::string subAccountAPIKey){
      CURL *curl;
      curl_global_init(CURL_GLOBAL_ALL);
      curl = curl_easy_init();
      if (curl)
      {
        readBuffer.clear();
        CURLcode res;
        std::stringstream url;
        if (notificationUrl == "")
        {
          url << baseUrl << "/subaccount/" << subAccountAPIKey;
        } else {
          url << baseUrl << "/subaccount/" << subAccountAPIKey << "?notificationUrl=" << notificationUrl;
        }

        curl_easy_setopt(curl, CURLOPT_URL, url.str().c_str());
        curl_easy_setopt(curl, CURLOPT_HTTPAUTH, CURLAUTH_ANY);
        curl_easy_setopt(curl, CURLOPT_USERPWD, auth.c_str());
        curl_easy_setopt(curl, CURLOPT_CUSTOMREQUEST, "DELETE");
        struct curl_slist *chunk = NULL;
        chunk = curl_slist_append(chunk, platformVersionHeader.c_str());
        chunk = curl_slist_append(chunk, platformIdHeader.c_str());
        curl_easy_setopt(curl, CURLOPT_HTTPHEADER, chunk);
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &readBuffer);
        res = curl_easy_perform(curl);

        curl_easy_cleanup(curl);
        curl_slist_free_all(chunk);
        return readBuffer;

      } else {
        throw std::string("Cannot initialize curl object. Please ensure you have a working installation of the libcurl Library with the appropriate compile flag.");
      }
    }

    std::string CreateGroup(std::string description="")
    {
      CURL *curl;
      curl_global_init(CURL_GLOBAL_ALL);
      curl = curl_easy_init();
      if (curl)
      {
        readBuffer.clear();
        CURLcode res;
        std::stringstream url;
        if (notificationUrl == "")
        {
          url << baseUrl << "/groups";
        } else {
          url << baseUrl << "/groups?notificationUrl=" << notificationUrl;
        }

        curl_easy_setopt(curl, CURLOPT_URL, url.str().c_str());
        curl_easy_setopt(curl, CURLOPT_HTTPAUTH, CURLAUTH_ANY);
        curl_easy_setopt(curl, CURLOPT_USERPWD, auth.c_str());
        curl_easy_setopt(curl, CURLOPT_CUSTOMREQUEST, "POST");

        struct curl_slist *chunk = NULL;
        chunk = curl_slist_append(chunk, platformVersionHeader.c_str());
        chunk = curl_slist_append(chunk, platformIdHeader.c_str());
        chunk = curl_slist_append(chunk, "Content-Type: multipart/form-data");
        curl_easy_setopt(curl, CURLOPT_HTTPHEADER, chunk);

        struct curl_httppost *formpost = NULL;
        struct curl_httppost *lastptr = NULL;

        curl_formadd(&formpost,
             &lastptr,
             CURLFORM_COPYNAME, "description",
             CURLFORM_COPYCONTENTS, description.c_str(),
             CURLFORM_END);

        curl_easy_setopt(curl, CURLOPT_HTTPPOST, formpost);
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &readBuffer);
        res = curl_easy_perform(curl);

        curl_easy_cleanup(curl);
        curl_formfree(formpost);
        curl_slist_free_all(chunk);
        return readBuffer;

      } else {
        throw std::string("Cannot initialize curl object. Please ensure you have a working installation of the libcurl Library with the appropriate compile flag.");
      }
    }

    std::string AddUserToGroup(std::string groupId, std::string userId)
    {
      CURL *curl;
      curl_global_init(CURL_GLOBAL_ALL);
      curl = curl_easy_init();
      if (curl)
      {
        readBuffer.clear();
        CURLcode res;
        std::stringstream url;
        if (notificationUrl == "")
        {
          url << baseUrl << "/groups/addUser";
        } else {
          url << baseUrl << "/groups/addUser?notificationUrl=" << notificationUrl;
        }

        curl_easy_setopt(curl, CURLOPT_URL, url.str().c_str());
        curl_easy_setopt(curl, CURLOPT_HTTPAUTH, CURLAUTH_ANY);
        curl_easy_setopt(curl, CURLOPT_USERPWD, auth.c_str());
        curl_easy_setopt(curl, CURLOPT_CUSTOMREQUEST, "PUT");

        struct curl_slist *chunk = NULL;
        chunk = curl_slist_append(chunk, platformVersionHeader.c_str());
        chunk = curl_slist_append(chunk, platformIdHeader.c_str());
        chunk = curl_slist_append(chunk, "Content-Type: multipart/form-data");
        curl_easy_setopt(curl, CURLOPT_HTTPHEADER, chunk);

        struct curl_httppost *formpost = NULL;
        struct curl_httppost *lastptr = NULL;

        curl_formadd(&formpost,
             &lastptr,
             CURLFORM_COPYNAME, "groupId",
             CURLFORM_COPYCONTENTS, groupId.c_str(),
             CURLFORM_END);

        curl_formadd(&formpost,
             &lastptr,
             CURLFORM_COPYNAME, "userId",
             CURLFORM_COPYCONTENTS, userId.c_str(),
             CURLFORM_END);

        curl_easy_setopt(curl, CURLOPT_HTTPPOST, formpost);
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &readBuffer);
        res = curl_easy_perform(curl);

        curl_easy_cleanup(curl);
        curl_formfree(formpost);
        curl_slist_free_all(chunk);
        return readBuffer;

      } else {
        throw std::string("Cannot initialize curl object. Please ensure you have a working installation of the libcurl Library with the appropriate compile flag.");
      }
    }

    std::string RemoveUserFromGroup(std::string groupId, std::string userId)
    {
      CURL *curl;
      curl_global_init(CURL_GLOBAL_ALL);
      curl = curl_easy_init();
      if (curl)
      {
        readBuffer.clear();
        CURLcode res;
        std::stringstream url;
        if (notificationUrl == "")
        {
          url << baseUrl << "/groups/removeUser";
        } else {
          url << baseUrl << "/groups/removeUser?notificationUrl=" << notificationUrl;
        }

        curl_easy_setopt(curl, CURLOPT_URL, url.str().c_str());
        curl_easy_setopt(curl, CURLOPT_HTTPAUTH, CURLAUTH_ANY);
        curl_easy_setopt(curl, CURLOPT_USERPWD, auth.c_str());
        curl_easy_setopt(curl, CURLOPT_CUSTOMREQUEST, "PUT");

        struct curl_slist *chunk = NULL;
        chunk = curl_slist_append(chunk, platformVersionHeader.c_str());
        chunk = curl_slist_append(chunk, platformIdHeader.c_str());
        chunk = curl_slist_append(chunk, "Content-Type: multipart/form-data");
        curl_easy_setopt(curl, CURLOPT_HTTPHEADER, chunk);

        struct curl_httppost *formpost = NULL;
        struct curl_httppost *lastptr = NULL;

        curl_formadd(&formpost,
             &lastptr,
             CURLFORM_COPYNAME, "groupId",
             CURLFORM_COPYCONTENTS, groupId.c_str(),
             CURLFORM_END);

        curl_formadd(&formpost,
             &lastptr,
             CURLFORM_COPYNAME, "userId",
             CURLFORM_COPYCONTENTS, userId.c_str(),
             CURLFORM_END);

        curl_easy_setopt(curl, CURLOPT_HTTPPOST, formpost);
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &readBuffer);
        res = curl_easy_perform(curl);

        curl_easy_cleanup(curl);
        curl_formfree(formpost);
        curl_slist_free_all(chunk);
        return readBuffer;

      } else {
        throw std::string("Cannot initialize curl object. Please ensure you have a working installation of the libcurl Library with the appropriate compile flag.");
      }
    }

    std::string DeleteGroup(std::string groupId)
    {
      CURL *curl;
      curl_global_init(CURL_GLOBAL_ALL);
      curl = curl_easy_init();
      if (curl)
      {
        readBuffer.clear();
        CURLcode res;
        std::stringstream url;
        if (notificationUrl == "")
        {
          url << baseUrl << "/groups/" << groupId;
        } else {
          url << baseUrl << "/groups/" << groupId << "?notificationUrl=" << notificationUrl;
        }

        curl_easy_setopt(curl, CURLOPT_URL, url.str().c_str());
        curl_easy_setopt(curl, CURLOPT_HTTPAUTH, CURLAUTH_ANY);
        curl_easy_setopt(curl, CURLOPT_USERPWD, auth.c_str());
        curl_easy_setopt(curl, CURLOPT_CUSTOMREQUEST, "DELETE");

        struct curl_slist *chunk = NULL;
        chunk = curl_slist_append(chunk, platformVersionHeader.c_str());
        chunk = curl_slist_append(chunk, platformIdHeader.c_str());
        curl_easy_setopt(curl, CURLOPT_HTTPHEADER, chunk);

        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &readBuffer);
        res = curl_easy_perform(curl);

        curl_easy_cleanup(curl);
        curl_slist_free_all(chunk);
        return readBuffer;

      } else {
        throw std::string("Cannot initialize curl object. Please ensure you have a working installation of the libcurl Library with the appropriate compile flag.");
      }
    }

    std::string GetAllVoiceEnrollments(std::string userId)
    {
      CURL *curl;
      curl_global_init(CURL_GLOBAL_ALL);
      curl = curl_easy_init();
      if (curl)
      {
        readBuffer.clear();
        CURLcode res;
        std::stringstream url;
        if (notificationUrl == "")
        {
          url << baseUrl << "/enrollments/voice/" << userId;
        } else {
          url << baseUrl << "/enrollments/voice/" << userId << "?notificationUrl=" << notificationUrl;
        }

        curl_easy_setopt(curl, CURLOPT_URL, url.str().c_str());
        curl_easy_setopt(curl, CURLOPT_HTTPAUTH, CURLAUTH_ANY);
        curl_easy_setopt(curl, CURLOPT_USERPWD, auth.c_str());
        curl_easy_setopt(curl, CURLOPT_CUSTOMREQUEST, "GET");

        struct curl_slist *chunk = NULL;
        chunk = curl_slist_append(chunk, platformVersionHeader.c_str());
        chunk = curl_slist_append(chunk, platformIdHeader.c_str());
        curl_easy_setopt(curl, CURLOPT_HTTPHEADER, chunk);

        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &readBuffer);
        res = curl_easy_perform(curl);

        curl_easy_cleanup(curl);
        curl_slist_free_all(chunk);
        return readBuffer;

      } else {
        throw std::string("Cannot initialize curl object. Please ensure you have a working installation of the libcurl Library with the appropriate compile flag.");
      }
    }

    std::string GetAllFaceEnrollments(std::string userId)
    {
      CURL *curl;
      curl_global_init(CURL_GLOBAL_ALL);
      curl = curl_easy_init();
      if (curl)
      {
        readBuffer.clear();
        CURLcode res;
        std::stringstream url;
        if (notificationUrl == "")
        {
          url << baseUrl << "/enrollments/face/" << userId;
        } else {
          url << baseUrl << "/enrollments/face/" << userId << "?notificationUrl=" << notificationUrl;
        }

        curl_easy_setopt(curl, CURLOPT_URL, url.str().c_str());
        curl_easy_setopt(curl, CURLOPT_HTTPAUTH, CURLAUTH_ANY);
        curl_easy_setopt(curl, CURLOPT_USERPWD, auth.c_str());
        curl_easy_setopt(curl, CURLOPT_CUSTOMREQUEST, "GET");

        struct curl_slist *chunk = NULL;
        chunk = curl_slist_append(chunk, platformVersionHeader.c_str());
        chunk = curl_slist_append(chunk, platformIdHeader.c_str());
        curl_easy_setopt(curl, CURLOPT_HTTPHEADER, chunk);

        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &readBuffer);
        res = curl_easy_perform(curl);

        curl_easy_cleanup(curl);
        curl_slist_free_all(chunk);
        return readBuffer;

      } else {
        throw std::string("Cannot initialize curl object. Please ensure you have a working installation of the libcurl Library with the appropriate compile flag.");
      }
    }

    std::string GetAllVideoEnrollments(std::string userId)
    {
      CURL *curl;
      curl_global_init(CURL_GLOBAL_ALL);
      curl = curl_easy_init();
      if (curl)
      {
        readBuffer.clear();
        CURLcode res;
        std::stringstream url;
        if (notificationUrl == "")
        {
          url << baseUrl << "/enrollments/video/" << userId;
        } else {
          url << baseUrl << "/enrollments/video/" << userId << "?notificationUrl=" << notificationUrl;
        }

        curl_easy_setopt(curl, CURLOPT_URL, url.str().c_str());
        curl_easy_setopt(curl, CURLOPT_HTTPAUTH, CURLAUTH_ANY);
        curl_easy_setopt(curl, CURLOPT_USERPWD, auth.c_str());
        curl_easy_setopt(curl, CURLOPT_CUSTOMREQUEST, "GET");

        struct curl_slist *chunk = NULL;
        chunk = curl_slist_append(chunk, platformVersionHeader.c_str());
        chunk = curl_slist_append(chunk, platformIdHeader.c_str());
        curl_easy_setopt(curl, CURLOPT_HTTPHEADER, chunk);

        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &readBuffer);
        res = curl_easy_perform(curl);

        curl_easy_cleanup(curl);
        curl_slist_free_all(chunk);
        return readBuffer;

      } else {
        throw std::string("Cannot initialize curl object. Please ensure you have a working installation of the libcurl Library with the appropriate compile flag.");
      }
    }

    std::string CreateVoiceEnrollment(std::string userId, std::string contentLanguage, std::string phrase, std::string filePath)
    {
      FileExists(filePath);
      CURL *curl;
      curl_global_init(CURL_GLOBAL_ALL);
      curl = curl_easy_init();
      if (curl)
      {
        readBuffer.clear();
        CURLcode res;
        std::stringstream url;
        if (notificationUrl == "")
        {
          url << baseUrl << "/enrollments/voice";
        } else {
          url << baseUrl << "/enrollments/voice?notificationUrl=" << notificationUrl;
        }

        curl_easy_setopt(curl, CURLOPT_URL, url.str().c_str());
        curl_easy_setopt(curl, CURLOPT_HTTPAUTH, CURLAUTH_ANY);
        curl_easy_setopt(curl, CURLOPT_USERPWD, auth.c_str());
        curl_easy_setopt(curl, CURLOPT_CUSTOMREQUEST, "POST");

        struct curl_slist *chunk = NULL;
        chunk = curl_slist_append(chunk, platformVersionHeader.c_str());
        chunk = curl_slist_append(chunk, platformIdHeader.c_str());
        chunk = curl_slist_append(chunk, "Content-Type: multipart/form-data");
        curl_easy_setopt(curl, CURLOPT_HTTPHEADER, chunk);

        struct curl_httppost *formpost = NULL;
        struct curl_httppost *lastptr = NULL;

        curl_formadd(&formpost,
             &lastptr,
             CURLFORM_COPYNAME, "userId",
             CURLFORM_COPYCONTENTS, userId.c_str(),
             CURLFORM_END);

        curl_formadd(&formpost,
             &lastptr,
             CURLFORM_COPYNAME, "contentLanguage",
             CURLFORM_COPYCONTENTS, contentLanguage.c_str(),
             CURLFORM_END);

        curl_formadd(&formpost,
             &lastptr,
             CURLFORM_COPYNAME, "phrase",
             CURLFORM_COPYCONTENTS, phrase.c_str(),
             CURLFORM_END);


        curl_formadd(&formpost,
             &lastptr,
             CURLFORM_COPYNAME, "recording",
             CURLFORM_FILE, filePath.c_str(),
             CURLFORM_END);

        curl_easy_setopt(curl, CURLOPT_HTTPPOST, formpost);
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &readBuffer);
        res = curl_easy_perform(curl);

        curl_easy_cleanup(curl);
        curl_formfree(formpost);
        curl_slist_free_all(chunk);
        return readBuffer;

      } else {
        throw std::string("Cannot initialize curl object. Please ensure you have a working installation of the libcurl Library with the appropriate compile flag.");
      }
    }

    std::string CreateVoiceEnrollmentByUrl(std::string userId, std::string contentLanguage, std::string phrase, std::string fileUrl)
    {
      CURL *curl;
      curl_global_init(CURL_GLOBAL_ALL);
      curl = curl_easy_init();
      if (curl)
      {
        readBuffer.clear();
        CURLcode res;
        std::stringstream url;
        if (notificationUrl == "")
        {
          url << baseUrl << "/enrollments/voice/byUrl";
        } else {
          url << baseUrl << "/enrollments/voice/byUrl?notificationUrl=" << notificationUrl;
        }

        curl_easy_setopt(curl, CURLOPT_URL, url.str().c_str());
        curl_easy_setopt(curl, CURLOPT_HTTPAUTH, CURLAUTH_ANY);
        curl_easy_setopt(curl, CURLOPT_USERPWD, auth.c_str());
        curl_easy_setopt(curl, CURLOPT_CUSTOMREQUEST, "POST");

        struct curl_slist *chunk = NULL;
        chunk = curl_slist_append(chunk, platformVersionHeader.c_str());
        chunk = curl_slist_append(chunk, platformIdHeader.c_str());
        chunk = curl_slist_append(chunk, "Content-Type: multipart/form-data");
        curl_easy_setopt(curl, CURLOPT_HTTPHEADER, chunk);

        struct curl_httppost *formpost = NULL;
        struct curl_httppost *lastptr = NULL;

        curl_formadd(&formpost,
             &lastptr,
             CURLFORM_COPYNAME, "userId",
             CURLFORM_COPYCONTENTS, userId.c_str(),
             CURLFORM_END);

        curl_formadd(&formpost,
             &lastptr,
             CURLFORM_COPYNAME, "contentLanguage",
             CURLFORM_COPYCONTENTS, contentLanguage.c_str(),
             CURLFORM_END);

        curl_formadd(&formpost,
             &lastptr,
             CURLFORM_COPYNAME, "phrase",
             CURLFORM_COPYCONTENTS, phrase.c_str(),
             CURLFORM_END);


        curl_formadd(&formpost,
             &lastptr,
             CURLFORM_COPYNAME, "fileUrl",
             CURLFORM_COPYCONTENTS, fileUrl.c_str(),
             CURLFORM_END);

        curl_easy_setopt(curl, CURLOPT_HTTPPOST, formpost);
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &readBuffer);
        res = curl_easy_perform(curl);

        curl_easy_cleanup(curl);
        curl_formfree(formpost);
        curl_slist_free_all(chunk);
        return readBuffer;

      } else {
        throw std::string("Cannot initialize curl object. Please ensure you have a working installation of the libcurl Library with the appropriate compile flag.");
      }
    }

    std::string CreateFaceEnrollment(std::string userId, std::string filePath)
    {
      FileExists(filePath);
      CURL *curl;
      curl_global_init(CURL_GLOBAL_ALL);
      curl = curl_easy_init();
      if (curl)
      {
        readBuffer.clear();
        CURLcode res;
        std::stringstream url;
        if (notificationUrl == "")
        {
          url << baseUrl << "/enrollments/face";
        } else {
          url << baseUrl << "/enrollments/face?notificationUrl=" << notificationUrl;
        }

        curl_easy_setopt(curl, CURLOPT_URL, url.str().c_str());
        curl_easy_setopt(curl, CURLOPT_HTTPAUTH, CURLAUTH_ANY);
        curl_easy_setopt(curl, CURLOPT_USERPWD, auth.c_str());
        curl_easy_setopt(curl, CURLOPT_CUSTOMREQUEST, "POST");

        struct curl_slist *chunk = NULL;
        chunk = curl_slist_append(chunk, platformVersionHeader.c_str());
        chunk = curl_slist_append(chunk, platformIdHeader.c_str());
        chunk = curl_slist_append(chunk, "Content-Type: multipart/form-data");
        curl_easy_setopt(curl, CURLOPT_HTTPHEADER, chunk);

        struct curl_httppost *formpost = NULL;
        struct curl_httppost *lastptr = NULL;

        curl_formadd(&formpost,
             &lastptr,
             CURLFORM_COPYNAME, "userId",
             CURLFORM_COPYCONTENTS, userId.c_str(),
             CURLFORM_END);

        curl_formadd(&formpost,
             &lastptr,
             CURLFORM_COPYNAME, "video",
             CURLFORM_FILE, filePath.c_str(),
             CURLFORM_END);

        curl_easy_setopt(curl, CURLOPT_HTTPPOST, formpost);
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &readBuffer);
        res = curl_easy_perform(curl);

        curl_easy_cleanup(curl);
        curl_formfree(formpost);
        curl_slist_free_all(chunk);
        return readBuffer;

      } else {
        throw std::string("Cannot initialize curl object. Please ensure you have a working installation of the libcurl Library with the appropriate compile flag.");
      }
    }

    std::string CreateFaceEnrollmentByUrl(std::string userId, std::string fileUrl)
    {
      CURL *curl;
      curl_global_init(CURL_GLOBAL_ALL);
      curl = curl_easy_init();
      if (curl)
      {
        readBuffer.clear();
        CURLcode res;
        std::stringstream url;
        if (notificationUrl == "")
        {
          url << baseUrl << "/enrollments/face/byUrl";
        } else {
          url << baseUrl << "/enrollments/face/byUrl?notificationUrl=" << notificationUrl;
        }

        curl_easy_setopt(curl, CURLOPT_URL, url.str().c_str());
        curl_easy_setopt(curl, CURLOPT_HTTPAUTH, CURLAUTH_ANY);
        curl_easy_setopt(curl, CURLOPT_USERPWD, auth.c_str());
        curl_easy_setopt(curl, CURLOPT_CUSTOMREQUEST, "POST");

        struct curl_slist *chunk = NULL;
        chunk = curl_slist_append(chunk, platformVersionHeader.c_str());
        chunk = curl_slist_append(chunk, platformIdHeader.c_str());
        chunk = curl_slist_append(chunk, "Content-Type: multipart/form-data");
        curl_easy_setopt(curl, CURLOPT_HTTPHEADER, chunk);

        struct curl_httppost *formpost = NULL;
        struct curl_httppost *lastptr = NULL;

        curl_formadd(&formpost,
             &lastptr,
             CURLFORM_COPYNAME, "userId",
             CURLFORM_COPYCONTENTS, userId.c_str(),
             CURLFORM_END);

        curl_formadd(&formpost,
             &lastptr,
             CURLFORM_COPYNAME, "fileUrl",
             CURLFORM_COPYCONTENTS, fileUrl.c_str(),
             CURLFORM_END);

        curl_easy_setopt(curl, CURLOPT_HTTPPOST, formpost);
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &readBuffer);
        res = curl_easy_perform(curl);

        curl_easy_cleanup(curl);
        curl_formfree(formpost);
        curl_slist_free_all(chunk);
        return readBuffer;

      } else {
        throw std::string("Cannot initialize curl object. Please ensure you have a working installation of the libcurl Library with the appropriate compile flag.");
      }
    }

    std::string CreateVideoEnrollment(std::string userId, std::string contentLanguage, std::string phrase, std::string filePath)
    {
      FileExists(filePath);
      CURL *curl;
      curl_global_init(CURL_GLOBAL_ALL);
      curl = curl_easy_init();
      if (curl)
      {
        readBuffer.clear();
        CURLcode res;
        std::stringstream url;
        if (notificationUrl == "")
        {
          url << baseUrl << "/enrollments/video";
        } else {
          url << baseUrl << "/enrollments/video?notificationUrl=" << notificationUrl;
        }

        curl_easy_setopt(curl, CURLOPT_URL, url.str().c_str());
        curl_easy_setopt(curl, CURLOPT_HTTPAUTH, CURLAUTH_ANY);
        curl_easy_setopt(curl, CURLOPT_USERPWD, auth.c_str());
        curl_easy_setopt(curl, CURLOPT_CUSTOMREQUEST, "POST");

        struct curl_slist *chunk = NULL;
        chunk = curl_slist_append(chunk, platformVersionHeader.c_str());
        chunk = curl_slist_append(chunk, platformIdHeader.c_str());
        chunk = curl_slist_append(chunk, "Content-Type: multipart/form-data");
        curl_easy_setopt(curl, CURLOPT_HTTPHEADER, chunk);

        struct curl_httppost *formpost = NULL;
        struct curl_httppost *lastptr = NULL;

        curl_formadd(&formpost,
             &lastptr,
             CURLFORM_COPYNAME, "userId",
             CURLFORM_COPYCONTENTS, userId.c_str(),
             CURLFORM_END);

        curl_formadd(&formpost,
             &lastptr,
             CURLFORM_COPYNAME, "contentLanguage",
             CURLFORM_COPYCONTENTS, contentLanguage.c_str(),
             CURLFORM_END);

        curl_formadd(&formpost,
             &lastptr,
             CURLFORM_COPYNAME, "phrase",
             CURLFORM_COPYCONTENTS, phrase.c_str(),
             CURLFORM_END);


        curl_formadd(&formpost,
             &lastptr,
             CURLFORM_COPYNAME, "video",
             CURLFORM_FILE, filePath.c_str(),
             CURLFORM_END);

        curl_easy_setopt(curl, CURLOPT_HTTPPOST, formpost);
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &readBuffer);
        res = curl_easy_perform(curl);

        curl_easy_cleanup(curl);
        curl_formfree(formpost);
        curl_slist_free_all(chunk);
        return readBuffer;

      } else {
        throw std::string("Cannot initialize curl object. Please ensure you have a working installation of the libcurl Library with the appropriate compile flag.");
      }
    }

    std::string CreateVideoEnrollmentByUrl(std::string userId, std::string contentLanguage, std::string phrase, std::string fileUrl)
    {
      CURL *curl;
      curl_global_init(CURL_GLOBAL_ALL);
      curl = curl_easy_init();
      if (curl)
      {
        readBuffer.clear();
        CURLcode res;
        std::stringstream url;
        if (notificationUrl == "")
        {
          url << baseUrl << "/enrollments/video/byUrl";
        } else {
          url << baseUrl << "/enrollments/video/byUrl?notificationUrl=" << notificationUrl;
        }

        curl_easy_setopt(curl, CURLOPT_URL, url.str().c_str());
        curl_easy_setopt(curl, CURLOPT_HTTPAUTH, CURLAUTH_ANY);
        curl_easy_setopt(curl, CURLOPT_USERPWD, auth.c_str());
        curl_easy_setopt(curl, CURLOPT_CUSTOMREQUEST, "POST");

        struct curl_slist *chunk = NULL;
        chunk = curl_slist_append(chunk, platformVersionHeader.c_str());
        chunk = curl_slist_append(chunk, platformIdHeader.c_str());
        chunk = curl_slist_append(chunk, "Content-Type: multipart/form-data");
        curl_easy_setopt(curl, CURLOPT_HTTPHEADER, chunk);

        struct curl_httppost *formpost = NULL;
        struct curl_httppost *lastptr = NULL;

        curl_formadd(&formpost,
             &lastptr,
             CURLFORM_COPYNAME, "userId",
             CURLFORM_COPYCONTENTS, userId.c_str(),
             CURLFORM_END);

        curl_formadd(&formpost,
             &lastptr,
             CURLFORM_COPYNAME, "contentLanguage",
             CURLFORM_COPYCONTENTS, contentLanguage.c_str(),
             CURLFORM_END);

        curl_formadd(&formpost,
             &lastptr,
             CURLFORM_COPYNAME, "phrase",
             CURLFORM_COPYCONTENTS, phrase.c_str(),
             CURLFORM_END);


        curl_formadd(&formpost,
             &lastptr,
             CURLFORM_COPYNAME, "fileUrl",
             CURLFORM_COPYCONTENTS, fileUrl.c_str(),
             CURLFORM_END);

        curl_easy_setopt(curl, CURLOPT_HTTPPOST, formpost);
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &readBuffer);
        res = curl_easy_perform(curl);

        curl_easy_cleanup(curl);
        curl_formfree(formpost);
        curl_slist_free_all(chunk);
        return readBuffer;

      } else {
        throw std::string("Cannot initialize curl object. Please ensure you have a working installation of the libcurl Library with the appropriate compile flag.");
      }
    }

    std::string DeleteAllEnrollments(std::string userId)
    {
      CURL *curl;
      curl_global_init(CURL_GLOBAL_ALL);
      curl = curl_easy_init();
      if (curl)
      {
        readBuffer.clear();
        CURLcode res;
        std::stringstream url;
        if (notificationUrl == "")
        {
          url << baseUrl << "/enrollments/" << userId << "/all";
        } else {
          url << baseUrl << "/enrollments/" << userId << "/all?notificationUrl=" << notificationUrl;
        }

        curl_easy_setopt(curl, CURLOPT_URL, url.str().c_str());
        curl_easy_setopt(curl, CURLOPT_HTTPAUTH, CURLAUTH_ANY);
        curl_easy_setopt(curl, CURLOPT_USERPWD, auth.c_str());
        curl_easy_setopt(curl, CURLOPT_CUSTOMREQUEST, "DELETE");

        struct curl_slist *chunk = NULL;
        chunk = curl_slist_append(chunk, platformVersionHeader.c_str());
        chunk = curl_slist_append(chunk, platformIdHeader.c_str());
        curl_easy_setopt(curl, CURLOPT_HTTPHEADER, chunk);

        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &readBuffer);
        res = curl_easy_perform(curl);

        curl_easy_cleanup(curl);
        curl_slist_free_all(chunk);
        return readBuffer;

      } else {
        throw std::string("Cannot initialize curl object. Please ensure you have a working installation of the libcurl Library with the appropriate compile flag.");
      }
    }

    std::string VoiceVerification(std::string userId, std::string contentLanguage, std::string phrase, std::string filePath)
    {
      FileExists(filePath);
      CURL *curl;
      curl_global_init(CURL_GLOBAL_ALL);
      curl = curl_easy_init();
      if (curl)
      {
        readBuffer.clear();
        CURLcode res;
        std::stringstream url;
        if (notificationUrl == "")
        {
          url << baseUrl << "/verification/voice";
        } else {
          url << baseUrl << "/verification/voice?notificationUrl=" << notificationUrl;
        }

        curl_easy_setopt(curl, CURLOPT_URL, url.str().c_str());
        curl_easy_setopt(curl, CURLOPT_HTTPAUTH, CURLAUTH_ANY);
        curl_easy_setopt(curl, CURLOPT_USERPWD, auth.c_str());
        curl_easy_setopt(curl, CURLOPT_CUSTOMREQUEST, "POST");

        struct curl_slist *chunk = NULL;
        chunk = curl_slist_append(chunk, platformVersionHeader.c_str());
        chunk = curl_slist_append(chunk, platformIdHeader.c_str());
        chunk = curl_slist_append(chunk, "Content-Type: multipart/form-data");
        curl_easy_setopt(curl, CURLOPT_HTTPHEADER, chunk);

        struct curl_httppost *formpost = NULL;
        struct curl_httppost *lastptr = NULL;

        curl_formadd(&formpost,
             &lastptr,
             CURLFORM_COPYNAME, "userId",
             CURLFORM_COPYCONTENTS, userId.c_str(),
             CURLFORM_END);

        curl_formadd(&formpost,
             &lastptr,
             CURLFORM_COPYNAME, "contentLanguage",
             CURLFORM_COPYCONTENTS, contentLanguage.c_str(),
             CURLFORM_END);

        curl_formadd(&formpost,
             &lastptr,
             CURLFORM_COPYNAME, "phrase",
             CURLFORM_COPYCONTENTS, phrase.c_str(),
             CURLFORM_END);


        curl_formadd(&formpost,
             &lastptr,
             CURLFORM_COPYNAME, "recording",
             CURLFORM_FILE, filePath.c_str(),
             CURLFORM_END);

        curl_easy_setopt(curl, CURLOPT_HTTPPOST, formpost);
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &readBuffer);
        res = curl_easy_perform(curl);

        curl_easy_cleanup(curl);
        curl_formfree(formpost);
        curl_slist_free_all(chunk);
        return readBuffer;

      } else {
        throw std::string("Cannot initialize curl object. Please ensure you have a working installation of the libcurl Library with the appropriate compile flag.");
      }
    }


    std::string VoiceVerificationByUrl(std::string userId, std::string contentLanguage, std::string phrase, std::string fileUrl)
    {
      CURL *curl;
      curl_global_init(CURL_GLOBAL_ALL);
      curl = curl_easy_init();
      if (curl)
      {
        readBuffer.clear();
        CURLcode res;
        std::stringstream url;
        if (notificationUrl == "")
        {
          url << baseUrl << "/verification/voice/byUrl";
        } else {
          url << baseUrl << "/verification/voice/byUrl?notificationUrl=" << notificationUrl;
        }

        curl_easy_setopt(curl, CURLOPT_URL, url.str().c_str());
        curl_easy_setopt(curl, CURLOPT_HTTPAUTH, CURLAUTH_ANY);
        curl_easy_setopt(curl, CURLOPT_USERPWD, auth.c_str());
        curl_easy_setopt(curl, CURLOPT_CUSTOMREQUEST, "POST");

        struct curl_slist *chunk = NULL;
        chunk = curl_slist_append(chunk, platformVersionHeader.c_str());
        chunk = curl_slist_append(chunk, platformIdHeader.c_str());
        chunk = curl_slist_append(chunk, "Content-Type: multipart/form-data");
        curl_easy_setopt(curl, CURLOPT_HTTPHEADER, chunk);

        struct curl_httppost *formpost = NULL;
        struct curl_httppost *lastptr = NULL;

        curl_formadd(&formpost,
             &lastptr,
             CURLFORM_COPYNAME, "userId",
             CURLFORM_COPYCONTENTS, userId.c_str(),
             CURLFORM_END);

        curl_formadd(&formpost,
             &lastptr,
             CURLFORM_COPYNAME, "contentLanguage",
             CURLFORM_COPYCONTENTS, contentLanguage.c_str(),
             CURLFORM_END);

        curl_formadd(&formpost,
             &lastptr,
             CURLFORM_COPYNAME, "phrase",
             CURLFORM_COPYCONTENTS, phrase.c_str(),
             CURLFORM_END);


        curl_formadd(&formpost,
             &lastptr,
             CURLFORM_COPYNAME, "fileUrl",
             CURLFORM_COPYCONTENTS, fileUrl.c_str(),
             CURLFORM_END);

        curl_easy_setopt(curl, CURLOPT_HTTPPOST, formpost);
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &readBuffer);
        res = curl_easy_perform(curl);

        curl_easy_cleanup(curl);
        curl_formfree(formpost);
        curl_slist_free_all(chunk);
        return readBuffer;

      } else {
        throw std::string("Cannot initialize curl object. Please ensure you have a working installation of the libcurl Library with the appropriate compile flag.");
      }
    }

    std::string FaceVerification(std::string userId, std::string filePath)
    {
      FileExists(filePath);
      CURL *curl;
      curl_global_init(CURL_GLOBAL_ALL);
      curl = curl_easy_init();
      if (curl)
      {
        readBuffer.clear();
        CURLcode res;
        std::stringstream url;
        if (notificationUrl == "")
        {
          url << baseUrl << "/verification/face";
        } else {
          url << baseUrl << "/verification/face?notificationUrl=" << notificationUrl;
        }

        curl_easy_setopt(curl, CURLOPT_URL, url.str().c_str());
        curl_easy_setopt(curl, CURLOPT_HTTPAUTH, CURLAUTH_ANY);
        curl_easy_setopt(curl, CURLOPT_USERPWD, auth.c_str());
        curl_easy_setopt(curl, CURLOPT_CUSTOMREQUEST, "POST");

        struct curl_slist *chunk = NULL;
        chunk = curl_slist_append(chunk, platformVersionHeader.c_str());
        chunk = curl_slist_append(chunk, platformIdHeader.c_str());
        chunk = curl_slist_append(chunk, "Content-Type: multipart/form-data");
        curl_easy_setopt(curl, CURLOPT_HTTPHEADER, chunk);

        struct curl_httppost *formpost = NULL;
        struct curl_httppost *lastptr = NULL;

        curl_formadd(&formpost,
             &lastptr,
             CURLFORM_COPYNAME, "userId",
             CURLFORM_COPYCONTENTS, userId.c_str(),
             CURLFORM_END);

        curl_formadd(&formpost,
             &lastptr,
             CURLFORM_COPYNAME, "video",
             CURLFORM_FILE, filePath.c_str(),
             CURLFORM_END);

        curl_easy_setopt(curl, CURLOPT_HTTPPOST, formpost);
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &readBuffer);
        res = curl_easy_perform(curl);

        curl_easy_cleanup(curl);
        curl_formfree(formpost);
        curl_slist_free_all(chunk);
        return readBuffer;

      } else {
        throw std::string("Cannot initialize curl object. Please ensure you have a working installation of the libcurl Library with the appropriate compile flag.");
      }
    }

    std::string FaceVerificationByUrl(std::string userId, std::string fileUrl)
    {
      CURL *curl;
      curl_global_init(CURL_GLOBAL_ALL);
      curl = curl_easy_init();
      if (curl)
      {
        readBuffer.clear();
        CURLcode res;
        std::stringstream url;
        if (notificationUrl == "")
        {
          url << baseUrl << "/verification/face/byUrl";
        } else {
          url << baseUrl << "/verification/face/byUrl?notificationUrl=" << notificationUrl;
        }

        curl_easy_setopt(curl, CURLOPT_URL, url.str().c_str());
        curl_easy_setopt(curl, CURLOPT_HTTPAUTH, CURLAUTH_ANY);
        curl_easy_setopt(curl, CURLOPT_USERPWD, auth.c_str());
        curl_easy_setopt(curl, CURLOPT_CUSTOMREQUEST, "POST");

        struct curl_slist *chunk = NULL;
        chunk = curl_slist_append(chunk, platformVersionHeader.c_str());
        chunk = curl_slist_append(chunk, platformIdHeader.c_str());
        chunk = curl_slist_append(chunk, "Content-Type: multipart/form-data");
        curl_easy_setopt(curl, CURLOPT_HTTPHEADER, chunk);

        struct curl_httppost *formpost = NULL;
        struct curl_httppost *lastptr = NULL;

        curl_formadd(&formpost,
             &lastptr,
             CURLFORM_COPYNAME, "userId",
             CURLFORM_COPYCONTENTS, userId.c_str(),
             CURLFORM_END);

        curl_formadd(&formpost,
             &lastptr,
             CURLFORM_COPYNAME, "fileUrl",
             CURLFORM_COPYCONTENTS, fileUrl.c_str(),
             CURLFORM_END);

        curl_easy_setopt(curl, CURLOPT_HTTPPOST, formpost);
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &readBuffer);
        res = curl_easy_perform(curl);

        curl_easy_cleanup(curl);
        curl_formfree(formpost);
        curl_slist_free_all(chunk);
        return readBuffer;

      } else {
        throw std::string("Cannot initialize curl object. Please ensure you have a working installation of the libcurl Library with the appropriate compile flag.");
      }
    }

    std::string VideoVerification(std::string userId, std::string contentLanguage, std::string phrase, std::string filePath)
    {
      FileExists(filePath);
      CURL *curl;
      curl_global_init(CURL_GLOBAL_ALL);
      curl = curl_easy_init();
      if (curl)
      {
        readBuffer.clear();
        CURLcode res;
        std::stringstream url;
        if (notificationUrl == "")
        {
          url << baseUrl << "/verification/video";
        } else {
          url << baseUrl << "/verification/video?notificationUrl=" << notificationUrl;
        }

        curl_easy_setopt(curl, CURLOPT_URL, url.str().c_str());
        curl_easy_setopt(curl, CURLOPT_HTTPAUTH, CURLAUTH_ANY);
        curl_easy_setopt(curl, CURLOPT_USERPWD, auth.c_str());
        curl_easy_setopt(curl, CURLOPT_CUSTOMREQUEST, "POST");

        struct curl_slist *chunk = NULL;
        chunk = curl_slist_append(chunk, platformVersionHeader.c_str());
        chunk = curl_slist_append(chunk, platformIdHeader.c_str());
        chunk = curl_slist_append(chunk, "Content-Type: multipart/form-data");
        curl_easy_setopt(curl, CURLOPT_HTTPHEADER, chunk);

        struct curl_httppost *formpost = NULL;
        struct curl_httppost *lastptr = NULL;

        curl_formadd(&formpost,
             &lastptr,
             CURLFORM_COPYNAME, "userId",
             CURLFORM_COPYCONTENTS, userId.c_str(),
             CURLFORM_END);

        curl_formadd(&formpost,
             &lastptr,
             CURLFORM_COPYNAME, "contentLanguage",
             CURLFORM_COPYCONTENTS, contentLanguage.c_str(),
             CURLFORM_END);

        curl_formadd(&formpost,
             &lastptr,
             CURLFORM_COPYNAME, "phrase",
             CURLFORM_COPYCONTENTS, phrase.c_str(),
             CURLFORM_END);


        curl_formadd(&formpost,
             &lastptr,
             CURLFORM_COPYNAME, "video",
             CURLFORM_FILE, filePath.c_str(),
             CURLFORM_END);

        curl_easy_setopt(curl, CURLOPT_HTTPPOST, formpost);
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &readBuffer);
        res = curl_easy_perform(curl);

        curl_easy_cleanup(curl);
        curl_formfree(formpost);
        curl_slist_free_all(chunk);
        return readBuffer;

      } else {
        throw std::string("Cannot initialize curl object. Please ensure you have a working installation of the libcurl Library with the appropriate compile flag.");
      }
    }

    std::string VideoVerificationByUrl(std::string userId, std::string contentLanguage, std::string phrase, std::string fileUrl)
    {
      CURL *curl;
      curl_global_init(CURL_GLOBAL_ALL);
      curl = curl_easy_init();
      if (curl)
      {
        readBuffer.clear();
        CURLcode res;
        std::stringstream url;
        if (notificationUrl == "")
        {
          url << baseUrl << "/verification/video/byUrl";
        } else {
          url << baseUrl << "/verification/video/byUrl?notificationUrl=" << notificationUrl;
        }

        curl_easy_setopt(curl, CURLOPT_URL, url.str().c_str());
        curl_easy_setopt(curl, CURLOPT_HTTPAUTH, CURLAUTH_ANY);
        curl_easy_setopt(curl, CURLOPT_USERPWD, auth.c_str());
        curl_easy_setopt(curl, CURLOPT_CUSTOMREQUEST, "POST");

        struct curl_slist *chunk = NULL;
        chunk = curl_slist_append(chunk, platformVersionHeader.c_str());
        chunk = curl_slist_append(chunk, platformIdHeader.c_str());
        chunk = curl_slist_append(chunk, "Content-Type: multipart/form-data");
        curl_easy_setopt(curl, CURLOPT_HTTPHEADER, chunk);

        struct curl_httppost *formpost = NULL;
        struct curl_httppost *lastptr = NULL;

        curl_formadd(&formpost,
             &lastptr,
             CURLFORM_COPYNAME, "userId",
             CURLFORM_COPYCONTENTS, userId.c_str(),
             CURLFORM_END);

        curl_formadd(&formpost,
             &lastptr,
             CURLFORM_COPYNAME, "contentLanguage",
             CURLFORM_COPYCONTENTS, contentLanguage.c_str(),
             CURLFORM_END);

        curl_formadd(&formpost,
             &lastptr,
             CURLFORM_COPYNAME, "phrase",
             CURLFORM_COPYCONTENTS, phrase.c_str(),
             CURLFORM_END);


        curl_formadd(&formpost,
             &lastptr,
             CURLFORM_COPYNAME, "fileUrl",
             CURLFORM_COPYCONTENTS, fileUrl.c_str(),
             CURLFORM_END);

        curl_easy_setopt(curl, CURLOPT_HTTPPOST, formpost);
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &readBuffer);
        res = curl_easy_perform(curl);

        curl_easy_cleanup(curl);
        curl_formfree(formpost);
        curl_slist_free_all(chunk);
        return readBuffer;

      } else {
        throw std::string("Cannot initialize curl object. Please ensure you have a working installation of the libcurl Library with the appropriate compile flag.");
      }
    }

    std::string VoiceIdentification(std::string groupId, std::string contentLanguage, std::string phrase, std::string filePath)
    {
      FileExists(filePath);
      CURL *curl;
      curl_global_init(CURL_GLOBAL_ALL);
      curl = curl_easy_init();
      if (curl)
      {
        readBuffer.clear();
        CURLcode res;
        std::stringstream url;
        if (notificationUrl == "")
        {
          url << baseUrl << "/identification/voice";
        } else {
          url << baseUrl << "/identification/voice?notificationUrl=" << notificationUrl;
        }

        curl_easy_setopt(curl, CURLOPT_URL, url.str().c_str());
        curl_easy_setopt(curl, CURLOPT_HTTPAUTH, CURLAUTH_ANY);
        curl_easy_setopt(curl, CURLOPT_USERPWD, auth.c_str());
        curl_easy_setopt(curl, CURLOPT_CUSTOMREQUEST, "POST");

        struct curl_slist *chunk = NULL;
        chunk = curl_slist_append(chunk, platformVersionHeader.c_str());
        chunk = curl_slist_append(chunk, platformIdHeader.c_str());
        chunk = curl_slist_append(chunk, "Content-Type: multipart/form-data");
        curl_easy_setopt(curl, CURLOPT_HTTPHEADER, chunk);

        struct curl_httppost *formpost = NULL;
        struct curl_httppost *lastptr = NULL;

        curl_formadd(&formpost,
             &lastptr,
             CURLFORM_COPYNAME, "groupId",
             CURLFORM_COPYCONTENTS, groupId.c_str(),
             CURLFORM_END);

        curl_formadd(&formpost,
             &lastptr,
             CURLFORM_COPYNAME, "contentLanguage",
             CURLFORM_COPYCONTENTS, contentLanguage.c_str(),
             CURLFORM_END);

        curl_formadd(&formpost,
             &lastptr,
             CURLFORM_COPYNAME, "phrase",
             CURLFORM_COPYCONTENTS, phrase.c_str(),
             CURLFORM_END);


        curl_formadd(&formpost,
             &lastptr,
             CURLFORM_COPYNAME, "recording",
             CURLFORM_FILE, filePath.c_str(),
             CURLFORM_END);

        curl_easy_setopt(curl, CURLOPT_HTTPPOST, formpost);
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &readBuffer);
        res = curl_easy_perform(curl);

        curl_easy_cleanup(curl);
        curl_formfree(formpost);
        curl_slist_free_all(chunk);
        return readBuffer;

      } else {
        throw std::string("Cannot initialize curl object. Please ensure you have a working installation of the libcurl Library with the appropriate compile flag.");
      }
    }

    std::string VoiceIdentificationByUrl(std::string groupId, std::string contentLanguage, std::string phrase, std::string fileUrl)
    {
      CURL *curl;
      curl_global_init(CURL_GLOBAL_ALL);
      curl = curl_easy_init();
      if (curl)
      {
        readBuffer.clear();
        CURLcode res;
        std::stringstream url;
        if (notificationUrl == "")
        {
          url << baseUrl << "/identification/voice/byUrl";
        } else {
          url << baseUrl << "/identification/voice/byUrl?notificationUrl=" << notificationUrl;
        }

        curl_easy_setopt(curl, CURLOPT_URL, url.str().c_str());
        curl_easy_setopt(curl, CURLOPT_HTTPAUTH, CURLAUTH_ANY);
        curl_easy_setopt(curl, CURLOPT_USERPWD, auth.c_str());
        curl_easy_setopt(curl, CURLOPT_CUSTOMREQUEST, "POST");

        struct curl_slist *chunk = NULL;
        chunk = curl_slist_append(chunk, platformVersionHeader.c_str());
        chunk = curl_slist_append(chunk, platformIdHeader.c_str());
        chunk = curl_slist_append(chunk, "Content-Type: multipart/form-data");
        curl_easy_setopt(curl, CURLOPT_HTTPHEADER, chunk);

        struct curl_httppost *formpost = NULL;
        struct curl_httppost *lastptr = NULL;

        curl_formadd(&formpost,
             &lastptr,
             CURLFORM_COPYNAME, "groupId",
             CURLFORM_COPYCONTENTS, groupId.c_str(),
             CURLFORM_END);

        curl_formadd(&formpost,
             &lastptr,
             CURLFORM_COPYNAME, "contentLanguage",
             CURLFORM_COPYCONTENTS, contentLanguage.c_str(),
             CURLFORM_END);

        curl_formadd(&formpost,
             &lastptr,
             CURLFORM_COPYNAME, "phrase",
             CURLFORM_COPYCONTENTS, phrase.c_str(),
             CURLFORM_END);


        curl_formadd(&formpost,
             &lastptr,
             CURLFORM_COPYNAME, "fileUrl",
             CURLFORM_COPYCONTENTS, fileUrl.c_str(),
             CURLFORM_END);

        curl_easy_setopt(curl, CURLOPT_HTTPPOST, formpost);
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &readBuffer);
        res = curl_easy_perform(curl);

        curl_easy_cleanup(curl);
        curl_formfree(formpost);
        curl_slist_free_all(chunk);
        return readBuffer;

      } else {
        throw std::string("Cannot initialize curl object. Please ensure you have a working installation of the libcurl Library with the appropriate compile flag.");
      }
    }

    std::string VideoIdentification(std::string groupId, std::string contentLanguage, std::string phrase, std::string filePath)
    {
      FileExists(filePath);
      CURL *curl;
      curl_global_init(CURL_GLOBAL_ALL);
      curl = curl_easy_init();
      if (curl)
      {
        readBuffer.clear();
        CURLcode res;
        std::stringstream url;
        if (notificationUrl == "")
        {
          url << baseUrl << "/identification/video";
        } else {
          url << baseUrl << "/identification/video?notificationUrl=" << notificationUrl;
        }

        curl_easy_setopt(curl, CURLOPT_URL, url.str().c_str());
        curl_easy_setopt(curl, CURLOPT_HTTPAUTH, CURLAUTH_ANY);
        curl_easy_setopt(curl, CURLOPT_USERPWD, auth.c_str());
        curl_easy_setopt(curl, CURLOPT_CUSTOMREQUEST, "POST");

        struct curl_slist *chunk = NULL;
        chunk = curl_slist_append(chunk, platformVersionHeader.c_str());
        chunk = curl_slist_append(chunk, platformIdHeader.c_str());
        chunk = curl_slist_append(chunk, "Content-Type: multipart/form-data");
        curl_easy_setopt(curl, CURLOPT_HTTPHEADER, chunk);

        struct curl_httppost *formpost = NULL;
        struct curl_httppost *lastptr = NULL;

        curl_formadd(&formpost,
             &lastptr,
             CURLFORM_COPYNAME, "groupId",
             CURLFORM_COPYCONTENTS, groupId.c_str(),
             CURLFORM_END);

        curl_formadd(&formpost,
             &lastptr,
             CURLFORM_COPYNAME, "contentLanguage",
             CURLFORM_COPYCONTENTS, contentLanguage.c_str(),
             CURLFORM_END);

        curl_formadd(&formpost,
             &lastptr,
             CURLFORM_COPYNAME, "phrase",
             CURLFORM_COPYCONTENTS, phrase.c_str(),
             CURLFORM_END);


        curl_formadd(&formpost,
             &lastptr,
             CURLFORM_COPYNAME, "video",
             CURLFORM_FILE, filePath.c_str(),
             CURLFORM_END);

        curl_easy_setopt(curl, CURLOPT_HTTPPOST, formpost);
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &readBuffer);
        res = curl_easy_perform(curl);

        curl_easy_cleanup(curl);
        curl_formfree(formpost);
        curl_slist_free_all(chunk);
        return readBuffer;

      } else {
        throw std::string("Cannot initialize curl object. Please ensure you have a working installation of the libcurl Library with the appropriate compile flag.");
      }
    }

    std::string VideoIdentificationByUrl(std::string groupId, std::string contentLanguage, std::string phrase, std::string fileUrl)
    {
      CURL *curl;
      curl_global_init(CURL_GLOBAL_ALL);
      curl = curl_easy_init();
      if (curl)
      {
        readBuffer.clear();
        CURLcode res;
        std::stringstream url;
        if (notificationUrl == "")
        {
          url << baseUrl << "/identification/video/byUrl";
        } else {
          url << baseUrl << "/identification/video/byUrl?notificationUrl=" << notificationUrl;
        }

        curl_easy_setopt(curl, CURLOPT_URL, url.str().c_str());
        curl_easy_setopt(curl, CURLOPT_HTTPAUTH, CURLAUTH_ANY);
        curl_easy_setopt(curl, CURLOPT_USERPWD, auth.c_str());
        curl_easy_setopt(curl, CURLOPT_CUSTOMREQUEST, "POST");

        struct curl_slist *chunk = NULL;
        chunk = curl_slist_append(chunk, platformVersionHeader.c_str());
        chunk = curl_slist_append(chunk, platformIdHeader.c_str());
        chunk = curl_slist_append(chunk, "Content-Type: multipart/form-data");
        curl_easy_setopt(curl, CURLOPT_HTTPHEADER, chunk);

        struct curl_httppost *formpost = NULL;
        struct curl_httppost *lastptr = NULL;

        curl_formadd(&formpost,
             &lastptr,
             CURLFORM_COPYNAME, "groupId",
             CURLFORM_COPYCONTENTS, groupId.c_str(),
             CURLFORM_END);

        curl_formadd(&formpost,
             &lastptr,
             CURLFORM_COPYNAME, "contentLanguage",
             CURLFORM_COPYCONTENTS, contentLanguage.c_str(),
             CURLFORM_END);

        curl_formadd(&formpost,
             &lastptr,
             CURLFORM_COPYNAME, "phrase",
             CURLFORM_COPYCONTENTS, phrase.c_str(),
             CURLFORM_END);


        curl_formadd(&formpost,
             &lastptr,
             CURLFORM_COPYNAME, "fileUrl",
             CURLFORM_COPYCONTENTS, fileUrl.c_str(),
             CURLFORM_END);

        curl_easy_setopt(curl, CURLOPT_HTTPPOST, formpost);
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &readBuffer);
        res = curl_easy_perform(curl);

        curl_easy_cleanup(curl);
        curl_formfree(formpost);
        curl_slist_free_all(chunk);
        return readBuffer;

      } else {
        throw std::string("Cannot initialize curl object. Please ensure you have a working installation of the libcurl Library with the appropriate compile flag.");
      }
    }

    std::string FaceIdentification(std::string groupId, std::string filePath)
    {
      FileExists(filePath);
      CURL *curl;
      curl_global_init(CURL_GLOBAL_ALL);
      curl = curl_easy_init();
      if (curl)
      {
        readBuffer.clear();
        CURLcode res;
        std::stringstream url;
        if (notificationUrl == "")
        {
          url << baseUrl << "/identification/face";
        } else {
          url << baseUrl << "/identification/face?notificationUrl=" << notificationUrl;
        }

        curl_easy_setopt(curl, CURLOPT_URL, url.str().c_str());
        curl_easy_setopt(curl, CURLOPT_HTTPAUTH, CURLAUTH_ANY);
        curl_easy_setopt(curl, CURLOPT_USERPWD, auth.c_str());
        curl_easy_setopt(curl, CURLOPT_CUSTOMREQUEST, "POST");

        struct curl_slist *chunk = NULL;
        chunk = curl_slist_append(chunk, platformVersionHeader.c_str());
        chunk = curl_slist_append(chunk, platformIdHeader.c_str());
        chunk = curl_slist_append(chunk, "Content-Type: multipart/form-data");
        curl_easy_setopt(curl, CURLOPT_HTTPHEADER, chunk);

        struct curl_httppost *formpost = NULL;
        struct curl_httppost *lastptr = NULL;

        curl_formadd(&formpost,
             &lastptr,
             CURLFORM_COPYNAME, "groupId",
             CURLFORM_COPYCONTENTS, groupId.c_str(),
             CURLFORM_END);

        curl_formadd(&formpost,
             &lastptr,
             CURLFORM_COPYNAME, "video",
             CURLFORM_FILE, filePath.c_str(),
             CURLFORM_END);

        curl_easy_setopt(curl, CURLOPT_HTTPPOST, formpost);
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &readBuffer);
        res = curl_easy_perform(curl);

        curl_easy_cleanup(curl);
        curl_formfree(formpost);
        curl_slist_free_all(chunk);
        return readBuffer;

      } else {
        throw std::string("Cannot initialize curl object. Please ensure you have a working installation of the libcurl Library with the appropriate compile flag.");
      }
    }

    std::string FaceIdentificationByUrl(std::string groupId, std::string fileUrl)
    {
      CURL *curl;
      curl_global_init(CURL_GLOBAL_ALL);
      curl = curl_easy_init();
      if (curl)
      {
        readBuffer.clear();
        CURLcode res;
        std::stringstream url;
        if (notificationUrl == "")
        {
          url << baseUrl << "/identification/face/byUrl";
        } else {
          url << baseUrl << "/identification/face/byUrl?notificationUrl=" << notificationUrl;
        }

        curl_easy_setopt(curl, CURLOPT_URL, url.str().c_str());
        curl_easy_setopt(curl, CURLOPT_HTTPAUTH, CURLAUTH_ANY);
        curl_easy_setopt(curl, CURLOPT_USERPWD, auth.c_str());
        curl_easy_setopt(curl, CURLOPT_CUSTOMREQUEST, "POST");

        struct curl_slist *chunk = NULL;
        chunk = curl_slist_append(chunk, platformVersionHeader.c_str());
        chunk = curl_slist_append(chunk, platformIdHeader.c_str());
        chunk = curl_slist_append(chunk, "Content-Type: multipart/form-data");
        curl_easy_setopt(curl, CURLOPT_HTTPHEADER, chunk);

        struct curl_httppost *formpost = NULL;
        struct curl_httppost *lastptr = NULL;

        curl_formadd(&formpost,
             &lastptr,
             CURLFORM_COPYNAME, "groupId",
             CURLFORM_COPYCONTENTS, groupId.c_str(),
             CURLFORM_END);

        curl_formadd(&formpost,
             &lastptr,
             CURLFORM_COPYNAME, "fileUrl",
             CURLFORM_COPYCONTENTS, fileUrl.c_str(),
             CURLFORM_END);

        curl_easy_setopt(curl, CURLOPT_HTTPPOST, formpost);
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &readBuffer);
        res = curl_easy_perform(curl);

        curl_easy_cleanup(curl);
        curl_formfree(formpost);
        curl_slist_free_all(chunk);
        return readBuffer;

      } else {
        throw std::string("Cannot initialize curl object. Please ensure you have a working installation of the libcurl Library with the appropriate compile flag.");
      }
    }

    std::string GetPhrases(std::string contentLanguage)
    {
      CURL *curl;
      curl_global_init(CURL_GLOBAL_ALL);
      curl = curl_easy_init();
      if (curl)
      {
        readBuffer.clear();
        CURLcode res;
        std::stringstream url;
        if (notificationUrl == "")
        {
          url << baseUrl << "/phrases/" << contentLanguage;
        } else {
          url << baseUrl << "/phrases/" << contentLanguage << "?notificationUrl=" << notificationUrl;
        }

        curl_easy_setopt(curl, CURLOPT_URL, url.str().c_str());
        curl_easy_setopt(curl, CURLOPT_HTTPAUTH, CURLAUTH_ANY);
        curl_easy_setopt(curl, CURLOPT_USERPWD, auth.c_str());
        curl_easy_setopt(curl, CURLOPT_CUSTOMREQUEST, "GET");
        struct curl_slist *chunk = NULL;
        chunk = curl_slist_append(chunk, platformVersionHeader.c_str());
        chunk = curl_slist_append(chunk, platformIdHeader.c_str());
        curl_easy_setopt(curl, CURLOPT_HTTPHEADER, chunk);
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &readBuffer);
        res = curl_easy_perform(curl);

        curl_easy_cleanup(curl);
        curl_slist_free_all(chunk);
        return readBuffer;

      } else {
        throw std::string("Cannot initialize curl object. Please ensure you have a working installation of the libcurl Library with the appropriate compile flag.");
      }
    }


    std::string ExpireUserTokens(std::string userId)
    {
      CURL *curl;
      curl_global_init(CURL_GLOBAL_ALL);
      curl = curl_easy_init();
      if (curl)
      {
        readBuffer.clear();
        CURLcode res;
        std::stringstream url;
        if (notificationUrl == "")
        {
          url << baseUrl << "/users/" << userId << "/expireTokens";
        } else {
          url << baseUrl << "/users/" <<  userId << "/expireTokens?notificationUrl=" << notificationUrl;
        }

        curl_easy_setopt(curl, CURLOPT_URL, url.str().c_str());
        curl_easy_setopt(curl, CURLOPT_HTTPAUTH, CURLAUTH_ANY);
        curl_easy_setopt(curl, CURLOPT_USERPWD, auth.c_str());
        curl_easy_setopt(curl, CURLOPT_CUSTOMREQUEST, "POST");
        struct curl_slist *chunk = NULL;
        chunk = curl_slist_append(chunk, platformVersionHeader.c_str());
        chunk = curl_slist_append(chunk, platformIdHeader.c_str());
        curl_easy_setopt(curl, CURLOPT_HTTPHEADER, chunk);
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &readBuffer);
        res = curl_easy_perform(curl);

        curl_easy_cleanup(curl);
        curl_slist_free_all(chunk);
        return readBuffer;

      } else {
        throw std::string("Cannot initialize curl object. Please ensure you have a working installation of the libcurl Library with the appropriate compile flag.");
      }
    }

  };
