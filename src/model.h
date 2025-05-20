#ifndef MODEL_H
#define MODEL_H

#include "cJSON.h"


double dummy_val = .1234;

class JsonWrapper {
private:
    cJSON* root;

    void cleanup() {
        if(root) {
            cJSON_Delete(root);
            root = nullptr;
        }
    }

public:
    JsonWrapper() : root(nullptr) {}
    JsonWrapper(const char* filename) : root(nullptr) {
      loadFromFile(filename);
    }

    ~JsonWrapper() {
        cleanup();
    }

    bool loadFromFile(const char* filename) {
        FILE* fp = fopen(filename, "r");
        if (!fp) return false;

        fseek(fp, 0L, SEEK_END);
        size_t fileSize = ftell(fp);
        fseek(fp, 0L, SEEK_SET);

        char* buffer = (char*)malloc(sizeof(char) * (fileSize + 1));
        if (!buffer) {
            fclose(fp);
            return false;
        }

        size_t bytesRead = fread(buffer, sizeof(char), fileSize, fp);
        buffer[bytesRead] = '\0';
        fclose(fp);

        root = cJSON_Parse(buffer);
        free(buffer);
        return root != nullptr;
    }

    const char* getValue(const char* key, double &value) {
        if(!root) return RET_NO_CONFIG_LOADED;
        cJSON* item = cJSON_GetObjectItem(root, key);
        if(item && cJSON_IsNumber(item)) {
          value = item->valuedouble;
          return NULL;
        } else {
          return RET_KEY_NOT_FOUND;
        }
    }
private:
    static const char* RET_NO_CONFIG_LOADED;
    static const char* RET_KEY_NOT_FOUND;
};

const char* JsonWrapper::RET_NO_CONFIG_LOADED = "No config file loaded";
const char* JsonWrapper::RET_KEY_NOT_FOUND = "Config value key not found";


class Model : public IModel {
    // Class definition...
private:
    double processedData;
    JsonWrapper *json = NULL;
public:
    void processData( void ) override {
        // Simulate data processing
        processedData = dummy_val;
        if( dummy_val <= 1234 )
          dummy_val *=10.0;
        else
          dummy_val = .1234;
    }

    Model() {
      json = new JsonWrapper("config.json");
    }

    void onDataProcessed(std::function<void(const double&)> callback) override {
        // Simulate async processing
        callback(processedData);
    }

    const char* requestConfig(const std::string &id, double &value) override {
      return json->getValue((const char*)id.c_str(), value);
    }
};

#endif  // MODEL_H

