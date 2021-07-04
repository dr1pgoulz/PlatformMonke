#include "modloader/shared/modloader.hpp"
#include "beatsaber-hook/shared/utils/logging.hpp"
#include "main.hpp"
#include "UnityEngine/Vector3.hpp"
#include "custom-types/shared/register.hpp"
#include "UnityEngine/Color.hpp"
#include "UnityEngine/Collider.hpp"
#include "UnityEngine/GameObject.hpp"
#include "UnityEngine/Transform.hpp"
#include "UnityEngine/Mathf.hpp"
#include "UnityEngine/Physics.hpp"
#include "UnityEngine/Material.hpp"
#include "UnityEngine/RaycastHit.hpp"
#include "UnityEngine/Object.hpp"
#include "UnityEngine/GameObject.hpp"
#include "UnityEngine/Renderer.hpp"
#include "UnityEngine/PrimitiveType.hpp"
#include "GorillaLocomotion/Player.hpp"
#include "beatsaber-hook/shared/utils/il2cpp-utils.hpp"
#include "beatsaber-hook/shared/utils/utils-functions.h"
#include "beatsaber-hook/shared/utils/typedefs.h"
#include "config.hpp"
#include "PlatformMonkeWatchView.hpp"
#include "monkecomputer/shared/GorillaUI.hpp"
#include "monkecomputer/shared/Register.hpp"
#include "custom-types/shared/register.hpp"
#include "GlobalNamespace/OVRInput.hpp"
#include "GlobalNamespace/OVRInput_Button.hpp"
#include "GlobalNamespace/OVRManager.hpp"
#include "UnityEngine/Vector3.hpp"

ModInfo modInfo;

#define INFO(value...) getLogger().info(value)
#define ERROR(value...) getLogger().error(value)

using namespace UnityEngine;
using namespace UnityEngine::XR;
using namespace GorillaLocomotion;

bool rightGrip = false;
bool leftGrip = false;
bool isButton = false;
bool isButton2 = false;
Transform* leftPlatformT;
Transform* rightPlatformT;
Vector3 leftHandP;
GameObject* leftPlatform;
GameObject* rightPlatform;
Renderer* renderer2;
Renderer* renderer;
Vector3 out = Vector3(0.0, -1000.0, 0.0);
Vector3 size = Vector3(0.025, 0.25, 0.32);
Vector3 size2 = Vector3(0.025, 0.25, 0.32);
Logger& getLogger()
{
    static Logger* logger = new Logger(modInfo, LoggerOptions(false, true));
    return *logger;
}

bool moddedRoom = false;


void leftColorCheck()
{
    if (config.leftColor == 0)
    {
        if (!leftPlatformT) return;
        Renderer* renderer1 = leftPlatformT->GetComponentInChildren<Renderer*>();
        renderer1->get_material()->set_color(Color::get_black());
    }
    if (config.leftColor == 1)
    {
        if (!leftPlatformT) return;
        Renderer* renderer1 = leftPlatformT->GetComponentInChildren<Renderer*>();
        renderer1->get_material()->set_color(Color::get_grey());
    }
    if (config.leftColor == 2)
    {
        if (!leftPlatformT) return;
        Renderer* renderer1 = leftPlatformT->GetComponentInChildren<Renderer*>();
        renderer1->get_material()->set_color(Color::get_white());
    }
    if (config.leftColor == 3)
    {
        if (!leftPlatformT) return;
        Renderer* renderer1 = leftPlatformT->GetComponentInChildren<Renderer*>();
        renderer1->get_material()->set_color(Color::get_red());
    }
    if (config.leftColor == 4)
    {
        if (!leftPlatformT) return;
        Renderer* renderer1 = leftPlatformT->GetComponentInChildren<Renderer*>();
        renderer1->get_material()->set_color(Color::get_green());
    }
    if (config.leftColor == 5)
    {
        if (!leftPlatformT) return;
        Renderer* renderer1 = leftPlatformT->GetComponentInChildren<Renderer*>();
        renderer1->get_material()->set_color(Color::get_blue());
    }
    if (config.leftColor == 6)
    {
        if (!leftPlatformT) return;
        Renderer* renderer1 = leftPlatformT->GetComponentInChildren<Renderer*>();
        renderer1->get_material()->set_color(Color::get_yellow());
    }
    if (config.leftColor == 7)
    {
        if (!leftPlatformT) return;
        Renderer* renderer1 = leftPlatformT->GetComponentInChildren<Renderer*>();
        renderer1->get_material()->set_color(Color(0.9f, 0.0f, 1.0f));
    }
    if (config.leftColor == 8)
    {
        if (!leftPlatformT) return;
        Renderer* renderer1 = leftPlatformT->GetComponentInChildren<Renderer*>();
        renderer1->get_material()->set_color(Color(0.5f, 0.0f, 1.0f));
    }
    if (config.leftColor == 9)
    {
        if (!leftPlatformT) return;
        Renderer* renderer1 = leftPlatformT->GetComponentInChildren<Renderer*>();
        renderer1->get_material()->set_color(Color::get_cyan());
    }
}

void rightColorCheck()
{
    if (config.rightColor == 0)
    {
        if (!rightPlatformT) return;
        Renderer* renderer2 = rightPlatformT->GetComponentInChildren<Renderer*>();
        renderer2->get_material()->set_color(Color::get_black());
    }
    if (config.rightColor == 1)
    {
        if (!rightPlatformT) return;
        Renderer* renderer2 = rightPlatformT->GetComponentInChildren<Renderer*>();
        renderer2->get_material()->set_color(Color::get_grey());
    }
    if (config.rightColor == 2)
    {
        if (!rightPlatformT) return;
        Renderer* renderer2 = rightPlatformT->GetComponentInChildren<Renderer*>();
        renderer2->get_material()->set_color(Color::get_white());
    }
    if (config.rightColor == 3)
    {
        if (!rightPlatformT) return;
        Renderer* renderer2 = rightPlatformT->GetComponentInChildren<Renderer*>();
        renderer2->get_material()->set_color(Color::get_red());
    }
    if (config.rightColor == 4)
    {
        if (!rightPlatformT) return;
        Renderer* renderer2 = rightPlatformT->GetComponentInChildren<Renderer*>();
        renderer2->get_material()->set_color(Color::get_green());
    }
    if (config.rightColor == 5)
    {
        if (!rightPlatformT) return;
        Renderer* renderer2 = rightPlatformT->GetComponentInChildren<Renderer*>();
        renderer2->get_material()->set_color(Color::get_blue());
    }
    if (config.rightColor == 6)
    {
        if (!rightPlatformT) return;
         Renderer* renderer2 = rightPlatformT->GetComponentInChildren<Renderer*>();
        renderer2->get_material()->set_color(Color::get_yellow());
    }
    if (config.rightColor == 7)
    {
        if (!rightPlatformT) return;
        Renderer* renderer2 = rightPlatformT->GetComponentInChildren<Renderer*>();
        renderer2->get_material()->set_color(Color(0.9f, 0.0f, 1.0f));
    }
    if (config.rightColor == 8)
    {
        if (!rightPlatformT) return;
        Renderer* renderer2 = rightPlatformT->GetComponentInChildren<Renderer*>();
        renderer2->get_material()->set_color(Color(0.5f, 0.0f, 1.0f));
    }
    if (config.rightColor == 9)
    {
        if (!rightPlatformT) return;
        Renderer* renderer2 = rightPlatformT->GetComponentInChildren<Renderer*>();
        renderer2->get_material()->set_color(Color::get_cyan());
    }
}

void leftSizeCheck()
{
    if (config.leftPlatSize == 0)
    {
        if (!leftPlatformT) return;
        size = Vector3(0.025, 0.25, 0.32);
        leftPlatformT->set_localScale(size);
    }
    if (config.leftPlatSize == 1)
    {
        if (!leftPlatformT) return;
        size = Vector3(0.025, 0.08, 0.12);
        leftPlatformT->set_localScale(size);
    }
    if (config.leftPlatSize == 2)
    {
        if (!leftPlatformT) return;
        size = Vector3(0.025, 0.15, 0.25);
        leftPlatformT->set_localScale(size);
    }
    if (config.leftPlatSize == 3)
    {
        if (!leftPlatformT) return;
         size = Vector3(0.025, 0.30, 0.40);
        leftPlatformT->set_localScale(size);
    }
    if (config.leftPlatSize == 4)
    {
        if (!leftPlatformT) return;
        size = Vector3(0.025, 0.45, 0.55);
        leftPlatformT->set_localScale(size);
    }
    if (config.leftPlatSize == 5)
    {
        if (!leftPlatformT) return;
        size = Vector3(0.025, 0.60, 0.70);
        leftPlatformT->set_localScale(size);
    }
    if (config.leftPlatSize == 6)
    {
        if (!leftPlatformT) return;
        size = Vector3(0.025, 0.40, 1.4);
        leftPlatformT->set_localScale(size);
    }
    if (config.leftPlatSize == 7)
    {
        if (!leftPlatformT) return;
        size = Vector3(0.025, 1.4, 0.40);
        leftPlatformT->set_localScale(size);
    }
}
void rightSizeCheck()
{
    if (config.rightPlatSize == 0)
    {
        if (!rightPlatformT) return;
        size2 = Vector3(0.025, 0.25, 0.32);
        rightPlatformT->set_localScale(size2);
    }
    if (config.rightPlatSize == 1)
    {
        if (!rightPlatformT) return;
        size2 = Vector3(0.025, 0.08, 0.12);
        rightPlatformT->set_localScale(size2);
    }
    if (config.rightPlatSize == 2)
    {
        if (!rightPlatformT) return;
        size2 = Vector3(0.025, 0.15, 0.25);
        rightPlatformT->set_localScale(size2);
    }
    if (config.rightPlatSize == 3)
    {
        if (!rightPlatformT) return;
        size2 = Vector3(0.025, 0.30, 0.40);
        rightPlatformT->set_localScale(size2);
    }
    if (config.rightPlatSize == 4)
    {
        if (!rightPlatformT) return;   
        size2 = Vector3(0.025, 0.45, 0.55);
        rightPlatformT->set_localScale(size2);
    }
    if (config.rightPlatSize == 5)
    {
        if (!rightPlatformT) return;
        size2 = Vector3(0.025, 0.60, 0.70);
        rightPlatformT->set_localScale(size2);
    }
    if (config.rightPlatSize == 6)
    {
        if (!rightPlatformT) return;   
        size2 = Vector3(0.025, 0.40, 1.4);
        rightPlatformT->set_localScale(size2);
    }
    if (config.rightPlatSize == 7)
    {
        if (!rightPlatformT) return;
        size2 = Vector3(0.025, 1.4, 0.40);
        rightPlatformT->set_localScale(size2);
    }
}

void spawnLeftPlatform()
{
    using namespace GlobalNamespace;
    leftGrip = OVRInput::Get(OVRInput::Button::PrimaryHandTrigger, OVRInput::Controller::LTouch);
    Player* playerInstance = Player::get_Instance();
    bool disabled = true;
    if(playerInstance == nullptr) return;
    GameObject* go = playerInstance->get_gameObject();
    auto* player = go->GetComponent<GorillaLocomotion::Player*>();
    Vector3 out2 = Vector3(0.0, -1000.0, 0.0);
    if (leftGrip && !leftPlatformT)
    {
        GameObject* leftPlatform = GameObject::CreatePrimitive(PrimitiveType::Cube);
        leftPlatformT = leftPlatform->get_transform();
        leftColorCheck();
        leftSizeCheck();
        rightColorCheck();
        rightSizeCheck();
    }
    if (leftGrip)
    {
        if (!leftPlatformT) return;
        Transform* leftHandT = player->leftHandTransform;
        Vector3 leftHandP = leftHandT->get_position();
        Quaternion leftHandR = leftHandT->get_rotation();
        leftPlatformT->set_localScale(size);
        leftPlatformT->set_position(leftHandP);
        leftPlatformT->set_rotation(leftHandR);
        disabled = false;
    }
    if (!leftGrip)
    {
        if (!leftPlatformT) return;
        leftPlatformT->set_position(out2);
        disabled = true;
    }
}

void spawnRightPlatform()
{
    using namespace GlobalNamespace;
    rightGrip = OVRInput::Get(OVRInput::Button::PrimaryHandTrigger, OVRInput::Controller::RTouch);
    Player* playerInstance = Player::get_Instance();
    bool disabled2 = true;
    if(playerInstance == nullptr) return;
    Vector3 out = Vector3(0.0, -1000.0, 0.0);
    GameObject* go = playerInstance->get_gameObject();
    auto* player = go->GetComponent<GorillaLocomotion::Player*>();
    if (rightGrip && !rightPlatformT)
    {
        GameObject* rightPlatform = GameObject::CreatePrimitive(PrimitiveType::Cube);
        rightPlatformT = rightPlatform->get_transform();
        leftColorCheck();
        leftSizeCheck();
        rightColorCheck();
        rightSizeCheck();
    }
    if (rightGrip)
    {
        if (!rightPlatformT) return;
        Transform* rightHandT = player->rightHandTransform;
        Vector3 rightHandP = rightHandT->get_position();
        Quaternion rightHandR = rightHandT->get_rotation();
        rightPlatformT->set_localScale(size2);
        rightPlatformT->set_position(rightHandP);
        rightPlatformT->set_rotation(rightHandR);
        disabled2 = false;
    }
    if (!rightGrip)
    {
        if (!rightPlatformT) return;
        rightPlatformT->set_position(out);
        disabled2 = true;
    }
}


void Buttn()
{
    using namespace GlobalNamespace;	
    if (moddedRoom && config.enabled)
	{
        leftGrip = OVRInput::Get(OVRInput::Button::PrimaryHandTrigger, OVRInput::Controller::LTouch);
        rightGrip = OVRInput::Get(OVRInput::Button::PrimaryHandTrigger, OVRInput::Controller::RTouch);
        
        if (!isButton)
        {
            spawnLeftPlatform();
            isButton = true; 
        }
        if (isButton)
        {
            if (!leftGrip)
            {
                isButton = false;
            }
        }
        
        if (!isButton2)
        {
            spawnRightPlatform();
            isButton2 = true;

        }
        if (isButton2)
        {
            if (!rightGrip)
            {
                isButton2 = false;
            }
        }
    }
}

MAKE_HOOK_OFFSETLESS(Player_Update, void, Il2CppObject* self)
{
    using namespace UnityEngine;
    using namespace GlobalNamespace;
    Player_Update(self);
    Il2CppObject* currentRoom2 = CRASH_UNLESS(il2cpp_utils::RunMethod("Photon.Pun", "PhotonNetwork", "get_CurrentRoom"));
    if (moddedRoom)
    {
        Buttn();
    }
    if (!moddedRoom || !currentRoom2)
    {
        if (!rightPlatformT) return;
        if (!leftPlatformT) return;
        rightPlatformT->set_position(out);
        leftPlatformT->set_position(out);
    }
    if (!config.enabled)
    {
        if (!rightPlatformT) return;
        if (!leftPlatformT) return;
        rightPlatformT->set_position(out);
        leftPlatformT->set_position(out);
    }
}

MAKE_HOOK_OFFSETLESS(PhotonNetworkController_OnJoinedRoom, void, Il2CppObject* self)
{
    PhotonNetworkController_OnJoinedRoom(self);

    Il2CppObject* currentRoom = CRASH_UNLESS(il2cpp_utils::RunMethod("Photon.Pun", "PhotonNetwork", "get_CurrentRoom"));

    if (currentRoom)
    {
        moddedRoom = !CRASH_UNLESS(il2cpp_utils::RunMethod<bool>(currentRoom, "get_IsVisible"));
    }
    else moddedRoom = true;
}

extern "C" void setup(ModInfo& info)
{
    info.id = ID;
    info.version = VERSION;

    modInfo = info;
}

extern "C" void load()
{
    getLogger().info("Loading mod...");

    GorillaUI::Init();

    INSTALL_HOOK_OFFSETLESS(getLogger(), PhotonNetworkController_OnJoinedRoom, il2cpp_utils::FindMethodUnsafe("", "PhotonNetworkController", "OnJoinedRoom", 0));
	INSTALL_HOOK_OFFSETLESS(getLogger(), Player_Update, il2cpp_utils::FindMethodUnsafe("GorillaLocomotion", "Player", "Update", 0));
    
    custom_types::Register::RegisterType<PlatformMonke::PlatformMonkeWatchView>(); 
    GorillaUI::Register::RegisterWatchView<PlatformMonke::PlatformMonkeWatchView*>("<b><i><color=#FFE65C>Platform Monke</color></i></b>", VERSION);
    LoadConfig();
    getLogger().info("Mod loaded!");
}