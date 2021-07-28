#include "config.hpp"
#include "beatsaber-hook/shared/config/config-utils.hpp"
#include "modloader/shared/modloader.hpp"
#include "beatsaber-hook/shared/rapidjson/include/rapidjson/document.h"

static ModInfo modInfo = {ID, VERSION};
extern Logger& getLogger();

#define INFO(value...) getLogger().info(value)
#define ERROR(value...) getLogger().error(value)
config_t config;
Configuration& getConfig()
{
    static Configuration config(modInfo);
    config.Load();
    return config;
}

void SaveConfig()
{
    INFO("Saving Configuration...");
    getConfig().config.RemoveAllMembers();
    getConfig().config.SetObject();
    rapidjson::Document::AllocatorType& allocator = getConfig().config.GetAllocator();
    
    getConfig().config.AddMember("leftPlatSize", config.leftPlatSize, allocator);
    getConfig().config.AddMember("rightPlatSize", config.rightPlatSize, allocator);
    if (config.leftColor != 11) {
        getConfig().config.AddMember("leftColor", config.leftColor, allocator);
    }
    if (config.rightColor != 11) {
        getConfig().config.AddMember("rightColor", config.rightColor, allocator);
    }
    getConfig().config.AddMember("enabled", config.enabled, allocator);
    getConfig().config.AddMember("onRelease", config.onRelease, allocator);
    getConfig().config.AddMember("stickPlat", config.stickPlat, allocator);
    getConfig().Write();
    INFO("Saved Configuration!");
}

bool LoadConfig()
{
    INFO("Loading config...");
    bool foundEverything = true;
    rapidjson::Document& doc = getConfig().config;
    if (doc.HasMember("leftColor")) {
        config.leftColor = doc["leftColor"].GetInt();
    } else {
        foundEverything = false;
    }
    if (doc.HasMember("rightColor")) {
        config.rightColor = doc["rightColor"].GetInt();
    } else {
        foundEverything = false;
    }
    if (doc.HasMember("leftPlatSize")) {
        config.leftPlatSize = doc["leftPlatSize"].GetInt();
    } else {
        foundEverything = false;
    }
    if (doc.HasMember("rightPlatSize")) {
        config.rightPlatSize = doc["rightPlatSize"].GetInt();
    } else {
        foundEverything = false;
    }
    if(doc.HasMember("enabled") && doc["enabled"].IsBool()) {
        config.enabled = doc["enabled"].GetBool();
    } else {
        foundEverything = false;
    }
    if(doc.HasMember("onRelease") && doc["onRelease"].IsBool()) {
        config.onRelease = doc["onRelease"].GetBool();
    } else {
        foundEverything = false;
    }
    if(doc.HasMember("stickPlat") && doc["stickPlat"].IsBool()) {
        config.stickPlat = doc["stickPlat"].GetBool();
    } else {
        foundEverything = false;
    }
    if (foundEverything) INFO("Config Loaded Succesfully!");
    return foundEverything;
}