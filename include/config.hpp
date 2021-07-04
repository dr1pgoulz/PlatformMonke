#pragma once

struct config_t {
    int leftPlatSize = 0;
    int rightPlatSize = 0;
    int leftColor = 0;
    int rightColor = 0;
    bool enabled = false;
};

extern config_t config;

void SaveConfig();
bool LoadConfig();