#include "PlatformMonkeWatchView.hpp"
#include "config.hpp"
#include "monkecomputer/shared/ViewLib/MonkeWatch.hpp"
#include "beatsaber-hook/shared/utils/il2cpp-functions.hpp"
#include "UnityEngine/Vector3.hpp"

DEFINE_TYPE(PlatformMonke::PlatformMonkeWatchView);

using namespace GorillaUI;
using namespace UnityEngine;

extern bool moddedRoom;
extern void leftSizeCheck();
extern void rightSizeCheck();
extern void leftColorCheck();
extern void rightColorCheck();

namespace PlatformMonke
{
    void PlatformMonkeWatchView::Awake()
    {
        toggleHandler = new UIToggleInputHandler(EKeyboardKey::Enter, EKeyboardKey::Enter, true);
        settingSelector = new UISelectionHandler(EKeyboardKey::Up, EKeyboardKey::Down, EKeyboardKey::Enter, true, false);
        leftPlatSizeSelector = new UISelectionHandler(EKeyboardKey::Left, EKeyboardKey::Right, EKeyboardKey::Enter, false, true);
        rightPlatSizeSelector = new UISelectionHandler(EKeyboardKey::Left, EKeyboardKey::Right, EKeyboardKey::Enter, false, true);
        leftColorSelector = new UISelectionHandler(EKeyboardKey::Left, EKeyboardKey::Right, EKeyboardKey::Enter, false, true);
        rightColorSelector = new UISelectionHandler(EKeyboardKey::Left, EKeyboardKey::Right, EKeyboardKey::Enter, false, true);

        settingSelector->max = 5;
        leftPlatSizeSelector->max = 8;
        rightPlatSizeSelector->max = 8;
        leftColorSelector->max = 10;
        rightColorSelector->max = 10;

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
        if (index == 0) config.enabled ^= 1;
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
        text += "<b><i><color=#FFE65C>Platform Monke:</color></i></b>\n";
    }

    void PlatformMonkeWatchView::DrawBody()
    {
        text += settingSelector->currentSelectionIndex == 0 ? "<color=#fd0000>></color>" : " ";
        text += config.enabled ? "<color=#00ff00> Enabled</color>" : "<color=#ff0000> Disabled</color>";

        text += "\n\n";
        text += "<b><i>Left Platform Size:</i></b>\n";
        text += settingSelector->currentSelectionIndex == 1 ? "<color=#ff0000>></color> " : " ";
        text += "<color=#AADDAA><</color> ";
        switch (leftPlatSizeSelector->currentSelectionIndex)
        {
            case 0:
                text += "Default";
                break;
            case 1:
                text += "1";
                break;
            case 2:
                text += "2";
                break;
            case 3:
                text += "3";
                break;
            case 4:
                text += "4";
                break;
            case 5:
                text += "5";
                break;
            case 6:
                text += "Vertical Plank";
                break;
            case 7:
                text += "Horizontal Plank";
                break;
            default:
                break;
        }
        text += " <color=#AADDAA>></color>";

        text += "\n\n";
        text += "<b><i>Right Platform Size:</i></b>\n";
        text += settingSelector->currentSelectionIndex == 2 ? "<color=#ff0000>></color> " : " ";
        text += "<color=#AADDAA><</color> ";
        switch (rightPlatSizeSelector->currentSelectionIndex)
        {
            case 0:
                text += "Default";
                break;
            case 1:
                text += "1";
                break;
            case 2:
                text += "2";
                break;
            case 3:
                text += "3";
                break;
            case 4:
                text += "4";
                break;
            case 5:
                text += "5";
                break;
            case 6:
                text += "Vertical Plank";
                break;
            case 7:
                text += "Horizontal Plank";
                break;
            default:
                break;
        }
        text += " <color=#AADDAA>></color>";
        text += "\n\n";
        
        text += "<b><i>Left Platform Color:</i></b>\n";
        text += settingSelector->currentSelectionIndex == 3 ? "<color=#ff0000>></color> " : " ";
        text += "<color=#AADDAA><</color> ";
        switch (leftColorSelector->currentSelectionIndex)
        {
            case 0:
                text += "Black";
                break;
            case 1:
                text += "Gray";
                break;
            case 2:
                text += "White";
                break;
            case 3:
                text += "Red";
                break;
            case 4:
                text += "Green";
                break;
            case 5:
                text += "Blue";
                break;
            case 6:
                text += "Yellow";
                break;
            case 7:
                text += "Pink";
                break;
            case 8:
                text += "Purple";
                break;
            case 9:
                text += "Cyan";
                break;
            default:
                break;
        }
        text += " <color=#AADDAA>></color>";
        text += "\n\n";
        text += "<b><i>Right Platform Color:</i></b>\n";
        text += settingSelector->currentSelectionIndex == 4 ? "<color=#ff0000>></color> " : " ";
        text += "<color=#AADDAA><</color> ";
        switch (rightColorSelector->currentSelectionIndex)
        {
            case 0:
                text += "Black";
                break;
            case 1:
                text += "Gray";
                break;
            case 2:
                text += "White";
                break;
            case 3:
                text += "Red";
                break;
            case 4:
                text += "Green";
                break;
            case 5:
                text += "Blue";
                break;
            case 6:
                text += "Yellow";
                break;
            case 7:
                text += "Pink";
                break;
            case 8:
                text += "Purple";
                break;
            case 9:
                text += "Cyan";
                break;
            default:
                break;
        }
        text += " <color=#AADDAA>></color>";
        text += "\n\n";
        if (config.enabled && !moddedRoom)
        {
            text += "<size=50>\n\n<color=FF7C7C>This mod is disabled</color>\n<color=FF7C7C>due to not being in</color>\n<color=FF7C7C>a private room</color>\n</size>";
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