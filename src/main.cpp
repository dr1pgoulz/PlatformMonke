#include "modloader/shared/modloader.hpp"
#include "beatsaber-hook/shared/utils/hooking.hpp"
#include "main.hpp"
#include "UnityEngine/Color.hpp"
#include "GlobalNamespace/VRRig.hpp"
#include "UnityEngine/Transform.hpp"
#include "UnityEngine/Material.hpp"
#include "UnityEngine/GameObject.hpp"
#include "UnityEngine/Renderer.hpp"
#include "UnityEngine/PrimitiveType.hpp"
#include "GorillaLocomotion/Player.hpp"
#include "config.hpp"
#include "PlatformMonkeWatchView.hpp"
#include "monkecomputer/shared/GorillaUI.hpp"
#include "monkecomputer/shared/Register.hpp"
#include "custom-types/shared/register.hpp"
#include "GlobalNamespace/OVRInput.hpp"
#include "GlobalNamespace/OVRInput_Button.hpp"
#include "UnityEngine/Vector3.hpp"
#include "GlobalNamespace/GorillaTagger.hpp"
#include "UnityEngine/SkinnedMeshRenderer.hpp"
ModInfo modInfo;

#define INFO(value...) getLogger().info(value)
#define ERROR(value...) getLogger().error(value)

using namespace UnityEngine;
using namespace GorillaLocomotion;
using namespace GlobalNamespace;

bool moddedRoom = false;
bool isButton = false;
bool isButton2 = false;
bool leftGrip = false;
bool rightGrip = false;
bool coloronce = false;
bool coloronce2 = false;
GameObject* rightPlatform;
GameObject* leftPlatform;
Transform* leftPlatformT;
Transform* rightPlatformT;
Color matcolor;
Color matcolor2;
Material* mat;
Material* mat2;
Material* defaultmat;
Vector3 out = Vector3(0.0, -1000.0, 0.0);
Vector3 size;
Vector3 size2;
Il2CppObject* currentRoom;
Logger& getLogger() {
    static Logger* logger = new Logger(modInfo, LoggerOptions(false, true));
    return *logger;
}

namespace GorillaUI::BaseGameInterface::PlayerColor {
    UnityEngine::Color get_color();
    Array<Il2CppObject*>* get_colorArray(float r, float g, float b);
}

void leftColorCheck() {
    if (!leftPlatformT) return;
    if (currentRoom) return;
    GorillaTagger* gorillaTagger = GorillaTagger::get_Instance();
    VRRig* myVRRig = gorillaTagger->myVRRig;
    Renderer* renderer1 = leftPlatformT->GetComponentInChildren<Renderer*>();
    if (!coloronce) {
        if (config.leftColor == 11) {
            if (!leftPlatformT) return;
            if (!myVRRig) return;
            Renderer* renderer1 = leftPlatformT->GetComponentInChildren<Renderer*>();
            mat = myVRRig->mainSkin->get_material();
            matcolor = mat->get_color();
            renderer1->set_material(mat);
            coloronce = true;
        }
    }
    if (coloronce) {
        if (config.leftColor < 11) {
            if (!myVRRig) return;
            renderer1->get_material()->set_color(matcolor);
            coloronce = false;
        }
    }
    if (config.leftColor < 11) {
        if (!leftPlatformT) return;
        Renderer* renderer1 = leftPlatformT->GetComponentInChildren<Renderer*>();
        renderer1->set_material(defaultmat);
    }
    switch(config.leftColor) {
        case 0:
            renderer1->get_material()->set_color(Color::get_black());
            break;
        case 1:
            renderer1->get_material()->set_color(Color::get_grey());
            break;
        case 2:
            renderer1->get_material()->set_color(Color::get_white());
            break;
        case 3:
            renderer1->get_material()->set_color(Color::get_red());
            break;
        case 4:
            renderer1->get_material()->set_color(Color::get_green());
            break;
        case 5:
            renderer1->get_material()->set_color(Color::get_blue());
            break;
        case 6:
            renderer1->get_material()->set_color(Color::get_yellow());
            break;
        case 7:
            renderer1->get_material()->set_color(Color(0.9f, 0.0f, 1.0f));
            break;
        case 8:
            renderer1->get_material()->set_color(Color(0.5f, 0.0f, 1.0f));
            break;
        case 9:
            renderer1->get_material()->set_color(Color::get_cyan());
            break;
        case 10:
            renderer1->get_material()->set_color(Color(GorillaUI::BaseGameInterface::PlayerColor::get_color()));
            break;
        case 11:
            break;
        default:
            break;
    }
}

void rightColorCheck() {
    if (!rightPlatformT) return;
    if (currentRoom) return;
    GorillaTagger* gorillaTagger = GorillaTagger::get_Instance();
    VRRig* myVRRig = gorillaTagger->myVRRig;
    Renderer* renderer2 = rightPlatformT->GetComponentInChildren<Renderer*>();
    if (!coloronce2) {
        if (config.rightColor == 11) {
            if (!rightPlatformT) return;
            if (!myVRRig) return;
            mat = myVRRig->mainSkin->get_material();
            matcolor = mat->get_color();
            renderer2->set_material(mat);
            coloronce2 = true;
        }
    }
    if (coloronce2) {
        if (config.rightColor < 11) {
            if (!myVRRig) return;
            renderer2->get_material()->set_color(matcolor);
            coloronce2 = false;
        }
    }
    if (config.rightColor < 11) {
        if (!rightPlatformT) return;
        renderer2->set_material(defaultmat);
    }
    switch(config.rightColor) {
        case 0:
            renderer2->get_material()->set_color(Color::get_black());
            break;
        case 1:
            renderer2->get_material()->set_color(Color::get_grey());
            break;
        case 2:
            renderer2->get_material()->set_color(Color::get_white());
            break;
        case 3:
            renderer2->get_material()->set_color(Color::get_red());
            break;
        case 4:
            renderer2->get_material()->set_color(Color::get_green());
            break;
        case 5:
            renderer2->get_material()->set_color(Color::get_blue());
            break;
        case 6:
            renderer2->get_material()->set_color(Color::get_yellow());
            break;
        case 7:
            renderer2->get_material()->set_color(Color(0.9f, 0.0f, 1.0f));
            break;
        case 8:
            renderer2->get_material()->set_color(Color(0.5f, 0.0f, 1.0f));
            break;
        case 9:
            renderer2->get_material()->set_color(Color::get_cyan());
            break;
        case 10:
            renderer2->get_material()->set_color(Color(GorillaUI::BaseGameInterface::PlayerColor::get_color()));
            break;
        case 11:
            break;
        default:
            break;
    }
}

void leftSizeCheck() {
    if (!leftPlatformT) return;
    switch(config.leftPlatSize) {
        case 0:
            size = Vector3(0.025, 0.25, 0.32);
            break;
        case 1:
            size = Vector3(0.025, 0.08, 0.12);
            break;
        case 2:
            size = Vector3(0.025, 0.15, 0.25);
            break;
        case 3:
            size = Vector3(0.025, 0.30, 0.40);
            break;
        case 4:
            size = Vector3(0.025, 0.45, 0.55);
            break;
        case 5:
            size = Vector3(0.025, 0.60, 0.70);
            break;
        case 6:
            size = Vector3(0.025, 0.40, 1.4);
            break;
        case 7:
            size = Vector3(0.025, 1.4, 0.40);
            break;
        case 8:
            size = Vector3(0.025, 5.0, 10.0);
            break;
        case 9:
            size = Vector3(0.025, 12.5, 40.0);
            break;
        case 10:
            size = Vector3(0.025, 20.0, 70.0);
            break;
    }
    leftPlatformT->set_localScale(size);
}
void rightSizeCheck() {
    if (!rightPlatformT) return;
    switch(config.rightPlatSize) {
        case 0:
            size2 = Vector3(0.025, 0.25, 0.32);
            break;
        case 1:
            size2 = Vector3(0.025, 0.08, 0.12);
            break;
        case 2:
            size2 = Vector3(0.025, 0.15, 0.25);
            break;
        case 3:
            size2 = Vector3(0.025, 0.30, 0.40);
            break;
        case 4:
            size2 = Vector3(0.025, 0.45, 0.55);
            break;
        case 5:
            size2 = Vector3(0.025, 0.60, 0.70);
            break;
        case 6:
            size2 = Vector3(0.025, 0.40, 1.4);
            break;
        case 7:
            size2 = Vector3(0.025, 1.4, 0.40);
            break;
        case 8:
            size2 = Vector3(0.025, 5.0, 10.0);
            break;
        case 9:
            size2 = Vector3(0.025, 12.5, 40.0);
            break;
        case 10:
            size2 = Vector3(0.025, 20.0, 70.0);
            break;
    }
    rightPlatformT->set_localScale(size2);
}

void spawnLeftPlatform() {
    bool leftGrip = OVRInput::Get(OVRInput::Button::PrimaryHandTrigger, OVRInput::Controller::LTouch);
    Player* playerInstance = Player::get_Instance();
    bool disabled = true;
    if(playerInstance == nullptr) return;
    GameObject* go = playerInstance->get_gameObject();
    auto* player = go->GetComponent<GorillaLocomotion::Player*>();
    if (leftGrip && !leftPlatformT) {
        GameObject* leftPlatform = GameObject::CreatePrimitive(PrimitiveType::Cube);
        leftPlatformT = leftPlatform->get_transform();
        leftColorCheck();
        leftSizeCheck();
        rightColorCheck();
        rightSizeCheck();
    }
    if (!defaultmat) {
        if (leftPlatformT) {
            Renderer* renderer1 = leftPlatformT->GetComponentInChildren<Renderer*>();  
            auto defaultmat = renderer1->get_material();
        }
    }
    if (leftGrip) {
        if (!leftPlatformT) return;
        Transform* leftHandT = player->leftHandTransform;
        Vector3 leftHandP = leftHandT->get_position();
        Quaternion leftHandR = leftHandT->get_rotation();
        leftPlatformT->set_localScale(size);
        leftPlatformT->set_position(leftHandP);
        leftPlatformT->set_rotation(leftHandR);
    }
    if (!leftGrip && config.onRelease) {
        if (!leftPlatformT) return;
        leftPlatformT->set_position(out);
    }
}

void spawnRightPlatform() {
    bool rightGrip = OVRInput::Get(OVRInput::Button::PrimaryHandTrigger, OVRInput::Controller::RTouch);
    Player* playerInstance = Player::get_Instance();
    if(playerInstance == nullptr) return;
    GameObject* go = playerInstance->get_gameObject();
    auto* player = go->GetComponent<GorillaLocomotion::Player*>();
    if (rightGrip && !rightPlatformT) {
        GameObject* rightPlatform = GameObject::CreatePrimitive(PrimitiveType::Cube);
        rightPlatformT = rightPlatform->get_transform();
        leftColorCheck();
        leftSizeCheck();
        rightColorCheck();
        rightSizeCheck();
    }
    if (rightGrip) {
        if (!rightPlatformT) return;
        Transform* rightHandT = player->rightHandTransform;
        Vector3 rightHandP = rightHandT->get_position();
        Quaternion rightHandR = rightHandT->get_rotation();
        rightPlatformT->set_localScale(size2);
        rightPlatformT->set_position(rightHandP);
        rightPlatformT->set_rotation(rightHandR);
    }
    if (!rightGrip && config.onRelease) {
        if (!rightPlatformT) return;
        rightPlatformT->set_position(out);
    }
}

void Buttn() {
    if (moddedRoom && config.enabled) {
        bool leftGrip = OVRInput::Get(OVRInput::Button::PrimaryHandTrigger, OVRInput::Controller::LTouch);
        bool rightGrip = OVRInput::Get(OVRInput::Button::PrimaryHandTrigger, OVRInput::Controller::RTouch);
        if (config.leftColor == 11|| config.rightColor == 11) {
            leftColorCheck();
            rightColorCheck();
        }
        if (config.stickPlat) {
            spawnLeftPlatform();
            spawnRightPlatform();
        }
        if (!config.stickPlat) {   
            if (!isButton) {
                spawnLeftPlatform();
                isButton = true; 
            }
            if (isButton) {
                if (!leftGrip) {
                    isButton = false;
                }
            }
            if (!isButton2) {
                spawnRightPlatform();
                isButton2 = true;
            }
            if (isButton2) {
                if (!rightGrip) {
                    isButton2 = false;
                }
            }
        }
    }
}
MAKE_HOOK_FIND_CLASS_UNSAFE_INSTANCE(PhotonNetworkController_OnJoinedRoom, "", "PhotonNetworkController", "OnJoinedRoom", void, Il2CppObject* self) {
    PhotonNetworkController_OnJoinedRoom(self);
    Il2CppObject* currentRoom = CRASH_UNLESS(il2cpp_utils::RunMethod("Photon.Pun", "PhotonNetwork", "get_CurrentRoom"));
    if (currentRoom) {
        moddedRoom = !CRASH_UNLESS(il2cpp_utils::RunMethod<bool>(currentRoom, "get_IsVisible"));
    }
    else moddedRoom = true;
}

MAKE_HOOK_FIND_CLASS_UNSAFE_INSTANCE(Player_Update, "GorillaLocomotion", "Player", "Update", void, Il2CppObject* self) {
    Player_Update(self);
    Il2CppObject* currentRoom = CRASH_UNLESS(il2cpp_utils::RunMethod("Photon.Pun", "PhotonNetwork", "get_CurrentRoom"));
    if (moddedRoom || currentRoom) {
        Buttn();
    }
    if (!moddedRoom || !currentRoom) {
        config.enabled = false;
    }
    if (!config.enabled && rightPlatformT) {
        rightPlatformT->set_position(out);
    }
    if (!config.enabled && leftPlatformT) {
        leftPlatformT->set_position(out);
    }
}

extern "C" void setup(ModInfo& info) {
    info.id = ID;
    info.version = VERSION;
    modInfo = info;
}

extern "C" void load() {
    getLogger().info("Loading mod...");
    GorillaUI::Init();
    INSTALL_HOOK(getLogger(), PhotonNetworkController_OnJoinedRoom);
	INSTALL_HOOK(getLogger(), Player_Update);
    custom_types::Register::AutoRegister();
    GorillaUI::Register::RegisterWatchView<PlatformMonke::PlatformMonkeWatchView*>("<b><i><color=#FFE65C>Platform Monke</color></i></b>", VERSION);
    LoadConfig();
    getLogger().info("Mod loaded!");
}