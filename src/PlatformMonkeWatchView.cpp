#include "PlatformMonkeWatchView.hpp"
#include "config.hpp"
#include "monkecomputer/shared/ViewLib/MonkeWatch.hpp"
#include "beatsaber-hook/shared/utils/il2cpp-functions.hpp"
#include "UnityEngine/Vector3.hpp"

DEFINE_TYPE(PlatformMonke, PlatformMonkeWatchView);

using namespace GorillaUI;
using namespace UnityEngine;

extern bool moddedRoom;
extern bool coloronce;
extern bool coloronce2;
extern void leftSizeCheck();
extern void rightSizeCheck();
extern void leftColorCheck();
extern void rightColorCheck();
extern void materialCheck();

namespace PlatformMonke
{
    void PlatformMonkeWatchView::Awake()
    {
        settingSelector = new UISelectionHandler(EKeyboardKey::Up, EKeyboardKey::Down, EKeyboardKey::Enter, true, false);
        leftPlatSizeSelector = new UISelectionHandler(EKeyboardKey::Left, EKeyboardKey::Right, EKeyboardKey::Enter, false, true);
        rightPlatSizeSelector = new UISelectionHandler(EKeyboardKey::Left, EKeyboardKey::Right, EKeyboardKey::Enter, false, true);
        leftColorSelector = new UISelectionHandler(EKeyboardKey::Left, EKeyboardKey::Right, EKeyboardKey::Enter, false, true);
        rightColorSelector = new UISelectionHandler(EKeyboardKey::Left, EKeyboardKey::Right, EKeyboardKey::Enter, false, true);

        settingSelector->max = 7;
        leftPlatSizeSelector->max = 11;
        rightPlatSizeSelector->max = 11;
        leftColorSelector->max = 12;
        rightColorSelector->max = 12;

        leftPlatSizeSelector->currentSelectionIndex = config.leftPlatSize;
        rightPlatSizeSelector->currentSelectionIndex = config.rightPlatSize;
        leftColorSelector->currentSelectionIndex = config.leftColor;
        rightColorSelector->currentSelectionIndex = config.rightColor;
    }

    void PlatformMonkeWatchView::DidActivate(bool firstActivation)
    {
        std::function<void(bool)> fun = std::bind(&PlatformMonkeWatchView::OnEnter, this, std::placeholders::_1);
        settingSelector->selectionCallback = fun;
        Redraw();
    }

    void PlatformMonkeWatchView::OnEnter(int index)
    {
        if (settingSelector->currentSelectionIndex == 0) 
        {
            config.enabled ^= 1;
            SaveConfig();
        }
        else if (settingSelector->currentSelectionIndex == 3)
        {
            coloronce = false;
        }
        else if (settingSelector->currentSelectionIndex == 4)
        {
            coloronce2 = false;
        }
        else if (settingSelector->currentSelectionIndex == 5)
        {
            config.onRelease ^= 1;
            SaveConfig();
        }
        else if (settingSelector->currentSelectionIndex == 6)
        {
            config.stickPlat ^= 1;
            SaveConfig();
        }
    }

    void PlatformMonkeWatchView::Redraw()
    {
        text = "";

        DrawHeader();
        DrawBody();

        MonkeWatch::Redraw();
    }

    void PlatformMonkeWatchView::DrawHeader()
    {
        text += "<size=80><b><color=#FFE65C> Platform Monke:</color></b>\n</size>";
    }

    void PlatformMonkeWatchView::DrawBody()
    {
        text += settingSelector->currentSelectionIndex == 0 ? "<size=60><color=#FF5115>></color></size>" : "<size=60> </size>";
        text += config.enabled ? "<size=60><color=#00ff00> Enabled</color></size>" : "<size=60><color=#ff0000> Disabled</color></size>";
        
        text += "<size=60>\n\n</size>";
        text += "<size=70><b><i><color=#FFFF99> Left Platform Size:</color></i></b>\n</size>";
        text += settingSelector->currentSelectionIndex == 1 ? "<size=60><color=#FF5115>></color></size>" : "<size=60> </size>";
        text += "<size=60><color=#AADDAA> <</color> </size>";
        switch (leftPlatSizeSelector->currentSelectionIndex)
        {
            case 0:
                text += "<size=60>Default</size>";
                break;
            case 1:
                text += "<size=60>1</size>";
                break;
            case 2:
                text += "<size=60>2</size>";
                break;
            case 3:
                text += "<size=60>3</size>";
                break;
            case 4:
                text += "<size=60>4</size>";
                break;
            case 5:
                text += "<size=60>5</size>";
                break;
            case 6:
                text += "<size=60>Vertical Plank</size>";
                break;
            case 7:
                text += "<size=60>Horizontal Plank</size>";
                break;
            case 8:
                text += "<size=60><color=#FFFF00>CHOMNKY BOI</color></size>";
                break;
            case 9:
                text += "<size=60><color=#FD6E17>HEFTY CHONK</color></size>";
                break;
            case 10:
                text += "<size=60><color=#ff0000>MEGA CHONKER</color></size>";
                break;
            default:
                break;
        }
        text += "<size=60> <color=#AADDAA>></color></size>";

        text += "<size=60>\n\n</size>";
        text += "<size=70><b><i><color=#FFFF99> Right Platform Size:</color></i></b>\n</size>";
        text += settingSelector->currentSelectionIndex == 2 ? "<size=60><color=#FF5115>></color></size>" : "<size=60> </size>";
        text += "<size=60><color=#AADDAA> <</color> </size>";
        switch (rightPlatSizeSelector->currentSelectionIndex)
        {
            case 0:
                text += "<size=60>Default</size>";
                break;
            case 1:
                text += "<size=60>1</size>";
                break;
            case 2:
                text += "<size=60>2</size>";
                break;
            case 3:
                text += "<size=60>3</size>";
                break;
            case 4:
                text += "<size=60>4</size>";
                break;
            case 5:
                text += "<size=60>5</size>";
                break;
            case 6:
                text += "<size=60>Vertical Plank</size>";
                break;
            case 7:
                text += "<size=60>Horizontal Plank</size>";
                break;
            case 8:
                text += "<size=60><color=#FFFF00>CHOMNKY BOI</color></size>";
                break;
            case 9:
                text += "<size=60><color=#FD6E17>HEFTY CHONK</color></size>";
                break;
            case 10:
                text += "<size=60><color=#ff0000>MEGA CHONKER</color></size>";
                break;
            default:
                break;
        }
        text += "<size=60> <color=#AADDAA>></color></size>";
        text += "<size=60>\n\n</size>";
        
        text += "<size=70><b><i><color=#FFFF99> Left Platform Color:</color></i></b>\n</size>";
        text += settingSelector->currentSelectionIndex == 3 ? "<size=60><color=#FF5115>></color></size>" : "<size=60> </size>";
        text += "<size=60><color=#AADDAA> <</color> </size>";
        switch (leftColorSelector->currentSelectionIndex)
        {
            case 0:
                text += "<size=60>Black</size>";
                break;
            case 1:
                text += "<size=60>Gray</size>";
                break;
            case 2:
                text += "<size=60>White</size>";
                break;
            case 3:
                text += "<size=60>Red</size>";
                break;
            case 4:
                text += "<size=60>Green</size>";
                break;
            case 5:
                text += "<size=60>Blue</size>";
                break;
            case 6:
                text += "<size=60>Yellow</size>";
                break;
            case 7:
                text += "<size=60>Pink</size>";
                break;
            case 8:
                text += "<size=60>Purple</size>";
                break;
            case 9:
                text += "<size=60>Cyan</size>";
                break;
            case 10:
                text += "<size=60>Monke Color</size>";
                break;
            case 11:
                text += "<size=60>Monke Material</size>";
                break;
            default:
                break;
        }
        text += "<size=60> <color=#AADDAA>></color></size>";
        text += "<size=60>\n\n</size>";
        text += "<size=70><b><i><color=#FFFF99> Right Platform Color:</color></i></b>\n</size>";
        text += settingSelector->currentSelectionIndex == 4 ? "<size=60><color=#FF5115>></color></size>" : "<size=60> </size>";
        text += "<size=60><color=#AADDAA> <</color> </size>";
        switch (rightColorSelector->currentSelectionIndex)
        {
            case 0:
                text += "<size=60>Black</size>";
                break;
            case 1:
                text += "<size=60>Gray</size>";
                break;
            case 2:
                text += "<size=60>White</size>";
                break;
            case 3:
                text += "<size=60>Red</size>";
                break;
            case 4:
                text += "<size=60>Green</size>";
                break;
            case 5:
                text += "<size=60>Blue</size>";
                break;
            case 6:
                text += "<size=60>Yellow</size>";
                break;
            case 7:
                text += "<size=60>Pink</size>";
                break;
            case 8:
                text += "<size=60>Purple</size>";
                break;
            case 9:
                text += "<size=60>Cyan</size>";
                break;
            case 10:
                text += "<size=60>Monke Color</size>";
                break;
            case 11:
                text += "<size=60>Monke Material</size>";
                break;
            default:
                break;
        }
        text += "<size=60> <color=#AADDAA>></color></size>";
        text += "<size=60>\n\n</size>";
        text += "<size=70><b><i><color=#FFFF99> Remove Platform\n on Release:</color></i></b></size>";
        text += config.onRelease ? "<size=60><color=#00ff00> Enabled </color></size>" : "<size=60><color=#ff0000> Disabled </color></size>";
        text += settingSelector->currentSelectionIndex == 5 ? "<size=60><color=#FF5115><</color></size>" : "<size=60> </size>";
        
        text += "<size=60>\n\n</size>";
        text += "<size=70><b><i><color=#FFFF99> Stick Platform\n to Hand:</color></i></b></size>";
        text += config.stickPlat ? "<size=60><color=#00ff00> Enabled </color></size>" : "<size=60><color=#ff0000> Disabled </color></size>";
        text += settingSelector->currentSelectionIndex == 6 ? "<size=60><color=#FF5115><</color></size>" : "<size=60> </size>";
        
        text += "<size=30>\n</size><size=30>\n</size>";

        if (config.enabled && !moddedRoom)
        {
            text += "<size=50><color=#FF6D49>\n               This mod is disabled\n               due to player not \n               being in a private room.\n</color></size>";
        }
    }

    void PlatformMonkeWatchView::OnKeyPressed(int value)
    {
        EKeyboardKey key = (EKeyboardKey)value;
        if (!settingSelector->HandleKey(key)) // if it was not up/down/enter
        {
            switch (settingSelector->currentSelectionIndex)
            {
                case 0:
                    break;
                case 1:
                    leftPlatSizeSelector->HandleKey(key);
                    break;
                case 2:
                    rightPlatSizeSelector->HandleKey(key);
                    break;
                case 3:
                    leftColorSelector->HandleKey(key);
                    break;
                case 4:
                    rightColorSelector->HandleKey(key);
                    break;
                default:
                    break;
            }

            config.rightPlatSize = rightPlatSizeSelector->currentSelectionIndex;
            config.leftPlatSize = leftPlatSizeSelector->currentSelectionIndex;
            config.rightColor = rightColorSelector->currentSelectionIndex;
            config.leftColor = leftColorSelector->currentSelectionIndex;

            leftColorCheck();
            leftSizeCheck();
            rightColorCheck();
            rightSizeCheck();
            SaveConfig();
        }
        Redraw();
    }
}