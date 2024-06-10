#ifndef CONTROLLERS_H
#define CONTROLLERS_H

// from
// https://github.com/libsdl-org/SDL/blob/main/src/joystick/controller_list.h

/*
  Copyright (C) Valve Corporation

  This software is provided 'as-is', without any express or implied
  warranty.  In no event will the authors be held liable for any damages
  arising from the use of this software.

  Permission is granted to anyone to use this software for any purpose,
  including commercial applications, and to alter it and redistribute it
  freely, subject to the following restrictions:

  1. The origin of this software must not be misrepresented; you must not
     claim that you wrote the original software. If you use this software
     in a product, an acknowledgment in the product documentation would be
     appreciated but is not required.
  2. Altered source versions must be plainly marked as such, and must not be
     misrepresented as being the original software.
  3. This notice may not be removed or altered from any source distribution.
*/

#include <stdint.h>

enum ControllerType {
  ControllerType_Unknown,

  // Steam Controllers
  ControllerType_SteamController,
  ControllerType_SteamControllerV2,
  ControllerType_SteamControllerNeptune,

  // Other Controllers
  ControllerType_UnknownNonSteamController,
  ControllerType_XBox360Controller,
  ControllerType_XBoxOneController,
  ControllerType_PS3Controller,
  ControllerType_PS4Controller,
  ControllerType_WiiController,
  ControllerType_AppleController,
  ControllerType_AndroidController,
  ControllerType_SwitchProController,
  ControllerType_SwitchJoyConLeft,
  ControllerType_SwitchJoyConRight,
  ControllerType_SwitchJoyConPair,
  ControllerType_SwitchInputOnlyController,
  ControllerType_MobileTouch,
  ControllerType_XInputSwitchController,
  // Client-side only, used to mark Nintendo Switch style controllers as
  // using XInput instead of the Nintendo Switch protocol
  ControllerType_PS5Controller,
  ControllerType_XInputPS4Controller,
  // Client-side only, used to mark DualShock 4 style controllers using
  // XInput instead of the DualShock 4 controller protocol
  ControllerTypeCount, // Don't add game controllers below this
                       // enumeration - this enumeration can
                       // change value

};

struct ControllerDescription {
  enum ControllerType type : 5;
  uint32_t id;
  const char *name;
};

#define MAKE_CONTROLLER_ID(vendorId, productId)                                \
  (uint32_t)((uint32_t)vendorId << 0x10 | (uint32_t)productId)

static const struct ControllerDescription ControllerDescriptions[] = {
    {ControllerType_PS3Controller, MAKE_CONTROLLER_ID(0x0079, 0x181a),
     0}, // Venom Arcade Stick
    {ControllerType_PS3Controller, MAKE_CONTROLLER_ID(0x0079, 0x1844),
     0}, // From SDL
    {ControllerType_PS3Controller, MAKE_CONTROLLER_ID(0x044f, 0xb315),
     0}, // Firestorm Dual Analog 3
    {ControllerType_PS3Controller, MAKE_CONTROLLER_ID(0x044f, 0xd007),
     0}, // Thrustmaster wireless 3-1
    {ControllerType_PS3Controller, MAKE_CONTROLLER_ID(0x046d, 0xcad1),
     0}, // Logitech Chillstream
    {ControllerType_PS3Controller, MAKE_CONTROLLER_ID(0x046d, 0xc24f),
     0}, // Logitech G29 (PS3)
    {ControllerType_PS3Controller, MAKE_CONTROLLER_ID(0x054c, 0x0268),
     0}, // Sony PS3 Controller
    {ControllerType_PS3Controller, MAKE_CONTROLLER_ID(0x056e, 0x200f),
     0}, // From SDL
    {ControllerType_PS3Controller, MAKE_CONTROLLER_ID(0x056e, 0x2013),
     0}, // JC-U4113SBK
    {ControllerType_PS3Controller, MAKE_CONTROLLER_ID(0x05b8, 0x1004),
     0}, // From SDL
    {ControllerType_PS3Controller, MAKE_CONTROLLER_ID(0x05b8, 0x1006),
     0}, // JC-U3412SBK
    {ControllerType_PS3Controller, MAKE_CONTROLLER_ID(0x06a3, 0xf622),
     0}, // Cyborg V3
    {ControllerType_PS3Controller, MAKE_CONTROLLER_ID(0x0738, 0x3180),
     0}, // Mad Catz Alpha PS3 mode
    {ControllerType_PS3Controller, MAKE_CONTROLLER_ID(0x0738, 0x3250),
     0}, // madcats fightpad pro ps3
    {ControllerType_PS3Controller, MAKE_CONTROLLER_ID(0x0738, 0x3481),
     0}, // Mad Catz FightStick TE 2+ PS3
    {ControllerType_PS3Controller, MAKE_CONTROLLER_ID(0x0738, 0x8180),
     0}, // Mad Catz Alpha PS4 mode (no touchpad on device)
    {ControllerType_PS3Controller, MAKE_CONTROLLER_ID(0x0738, 0x8838),
     0}, // Madcatz Fightstick Pro
    {ControllerType_PS3Controller, MAKE_CONTROLLER_ID(0x0810, 0x0001),
     0}, // actually ps2 - maybe break out later
    {ControllerType_PS3Controller, MAKE_CONTROLLER_ID(0x0810, 0x0003),
     0}, // actually ps2 - maybe break out later
    {ControllerType_PS3Controller, MAKE_CONTROLLER_ID(0x0925, 0x0005),
     0}, // Sony PS3 Controller
    {ControllerType_PS3Controller, MAKE_CONTROLLER_ID(0x0925, 0x8866),
     0}, // PS2 maybe break out later
    {ControllerType_PS3Controller, MAKE_CONTROLLER_ID(0x0925, 0x8888),
     0}, // Actually ps2 -maybe break out later Lakeview Research WiseGroup
         // Ltd, MP-8866 Dual Joypad
    {ControllerType_PS3Controller, MAKE_CONTROLLER_ID(0x0e6f, 0x0109),
     0}, // PDP Versus Fighting Pad
    {ControllerType_PS3Controller, MAKE_CONTROLLER_ID(0x0e6f, 0x011e),
     0}, // Rock Candy PS4
    {ControllerType_PS3Controller, MAKE_CONTROLLER_ID(0x0e6f, 0x0128),
     0}, // Rock Candy PS3
    {ControllerType_PS3Controller, MAKE_CONTROLLER_ID(0x0e6f, 0x0214),
     0}, // afterglow ps3
    {ControllerType_PS3Controller, MAKE_CONTROLLER_ID(0x0e6f, 0x1314),
     0}, // PDP Afterglow Wireless PS3 controller
    {ControllerType_PS3Controller, MAKE_CONTROLLER_ID(0x0e6f, 0x6302),
     0}, // From SDL
    {ControllerType_PS3Controller, MAKE_CONTROLLER_ID(0x0e8f, 0x0008),
     0}, // Green Asia
    {ControllerType_PS3Controller, MAKE_CONTROLLER_ID(0x0e8f, 0x3075),
     0}, // SpeedLink Strike FX
    {ControllerType_PS3Controller, MAKE_CONTROLLER_ID(0x0e8f, 0x310d),
     0}, // From SDL
    {ControllerType_PS3Controller, MAKE_CONTROLLER_ID(0x0f0d, 0x0009),
     0}, // HORI BDA GP1
    {ControllerType_PS3Controller, MAKE_CONTROLLER_ID(0x0f0d, 0x004d),
     0}, // Horipad 3
    {ControllerType_PS3Controller, MAKE_CONTROLLER_ID(0x0f0d, 0x005f),
     0}, // HORI Fighting Commander 4 PS3
    {ControllerType_PS3Controller, MAKE_CONTROLLER_ID(0x0f0d, 0x006a),
     0}, // Real Arcade Pro 4
    {ControllerType_PS3Controller, MAKE_CONTROLLER_ID(0x0f0d, 0x006e),
     0}, // HORI horipad4 ps3
    {ControllerType_PS3Controller, MAKE_CONTROLLER_ID(0x0f0d, 0x0085),
     0}, // HORI Fighting Commander PS3
    {ControllerType_PS3Controller, MAKE_CONTROLLER_ID(0x0f0d, 0x0086),
     0}, // HORI Fighting Commander PC (Uses the Xbox 360 protocol, but has
         // PS3 buttons)
    {ControllerType_PS3Controller, MAKE_CONTROLLER_ID(0x0f0d, 0x0088),
     0}, // HORI Fighting Stick mini 4
    {ControllerType_PS3Controller, MAKE_CONTROLLER_ID(0x0f30, 0x1100),
     0}, // Qanba Q1 fight stick
    {ControllerType_PS3Controller, MAKE_CONTROLLER_ID(0x11ff, 0x3331),
     0}, // SRXJ-PH2400
    {ControllerType_PS3Controller, MAKE_CONTROLLER_ID(0x1345, 0x1000),
     0}, // PS2 ACME GA-D5
    {ControllerType_PS3Controller, MAKE_CONTROLLER_ID(0x1345, 0x6005),
     0}, // ps2 maybe break out later
    {ControllerType_PS3Controller, MAKE_CONTROLLER_ID(0x146b, 0x5500),
     0}, // From SDL
    {ControllerType_PS3Controller, MAKE_CONTROLLER_ID(0x1a34, 0x0836),
     0}, // Afterglow PS3
    {ControllerType_PS3Controller, MAKE_CONTROLLER_ID(0x20bc, 0x5500),
     0}, // ShanWan PS3
    {ControllerType_PS3Controller, MAKE_CONTROLLER_ID(0x20d6, 0x576d),
     0}, // Power A PS3
    {ControllerType_PS3Controller, MAKE_CONTROLLER_ID(0x20d6, 0xca6d),
     0}, // BDA Pro Ex
    {ControllerType_PS3Controller, MAKE_CONTROLLER_ID(0x2563, 0x0523),
     0}, // Digiflip GP006
    {ControllerType_PS3Controller, MAKE_CONTROLLER_ID(0x2563, 0x0575),
     0}, // From SDL
    {ControllerType_PS3Controller, MAKE_CONTROLLER_ID(0x25f0, 0x83c3),
     0}, // gioteck vx2
    {ControllerType_PS3Controller, MAKE_CONTROLLER_ID(0x25f0, 0xc121), 0}, //
    {ControllerType_PS3Controller, MAKE_CONTROLLER_ID(0x2c22, 0x2003),
     0}, // Qanba Drone
    {ControllerType_PS3Controller, MAKE_CONTROLLER_ID(0x2c22, 0x2302),
     0}, // Qanba Obsidian
    {ControllerType_PS3Controller, MAKE_CONTROLLER_ID(0x2c22, 0x2502),
     0}, // Qanba Dragon
    {ControllerType_PS3Controller, MAKE_CONTROLLER_ID(0x8380, 0x0003),
     0}, // BTP 2163
    {ControllerType_PS3Controller, MAKE_CONTROLLER_ID(0x8888, 0x0308),
     0}, // Sony PS3 Controller

    {ControllerType_PS4Controller, MAKE_CONTROLLER_ID(0x0079, 0x181b),
     0}, // Venom Arcade Stick - XXX:this may not work and may need to be
         // called a ps3 controller
    //{ ControllerType_PS4Controller, MAKE_CONTROLLER_ID( 0x046d, 0xc260 ),
    // 0 },	// Logitech G29 (PS4)
    {ControllerType_PS4Controller, MAKE_CONTROLLER_ID(0x044f, 0xd00e),
     0}, // Thrustmaster Eswap Pro - No gyro and lightbar doesn't change
         // color. Works otherwise
    {ControllerType_PS4Controller, MAKE_CONTROLLER_ID(0x054c, 0x05c4),
     0}, // Sony PS4 Controller
    {ControllerType_PS4Controller, MAKE_CONTROLLER_ID(0x054c, 0x05c5),
     0}, // STRIKEPAD PS4 Grip Add-on
    {ControllerType_PS4Controller, MAKE_CONTROLLER_ID(0x054c, 0x09cc),
     0}, // Sony PS4 Slim Controller
    {ControllerType_PS4Controller, MAKE_CONTROLLER_ID(0x054c, 0x0ba0),
     0}, // Sony PS4 Controller (Wireless dongle)
    {ControllerType_PS4Controller, MAKE_CONTROLLER_ID(0x0738, 0x8250),
     0}, // Mad Catz FightPad Pro PS4
    {ControllerType_PS4Controller, MAKE_CONTROLLER_ID(0x0738, 0x8384),
     0}, // Mad Catz FightStick TE S+ PS4
    {ControllerType_PS4Controller, MAKE_CONTROLLER_ID(0x0738, 0x8480),
     0}, // Mad Catz FightStick TE 2 PS4
    {ControllerType_PS4Controller, MAKE_CONTROLLER_ID(0x0738, 0x8481),
     0}, // Mad Catz FightStick TE 2+ PS4
    {ControllerType_PS4Controller, MAKE_CONTROLLER_ID(0x0c12, 0x0e10),
     0}, // Armor Armor 3 Pad PS4
    {ControllerType_PS4Controller, MAKE_CONTROLLER_ID(0x0c12, 0x0e13),
     0}, // ZEROPLUS P4 Wired Gamepad
    {ControllerType_PS4Controller, MAKE_CONTROLLER_ID(0x0c12, 0x0e15),
     0}, // Game:Pad 4
    {ControllerType_PS4Controller, MAKE_CONTROLLER_ID(0x0c12, 0x0e20),
     0}, // Brook Mars Controller - needs FW update to show up as Ps4
         // controller on PC. Has Gyro but touchpad is a single button.
    {ControllerType_PS4Controller, MAKE_CONTROLLER_ID(0x0c12, 0x0ef6),
     0}, // Hitbox Arcade Stick
    {ControllerType_PS4Controller, MAKE_CONTROLLER_ID(0x0c12, 0x1cf6),
     0}, // EMIO PS4 Elite Controller
    {ControllerType_PS4Controller, MAKE_CONTROLLER_ID(0x0c12, 0x1e10),
     0}, // P4 Wired Gamepad generic knock off - lightbar but not trackpad or
         // gyro
    {ControllerType_PS4Controller, MAKE_CONTROLLER_ID(0x0e6f, 0x0203),
     0}, // Victrix Pro FS (PS4 peripheral but no trackpad/lightbar)
    {ControllerType_PS4Controller, MAKE_CONTROLLER_ID(0x0e6f, 0x0207),
     0}, // Victrix Pro FS V2 w/ Touchpad for PS4
    {ControllerType_PS4Controller, MAKE_CONTROLLER_ID(0x0e6f, 0x020a),
     0}, // Victrix Pro FS PS4/PS5 (PS4 mode)
    {ControllerType_PS4Controller, MAKE_CONTROLLER_ID(0x0f0d, 0x0055),
     0}, // HORIPAD 4 FPS
    {ControllerType_PS4Controller, MAKE_CONTROLLER_ID(0x0f0d, 0x005e),
     0}, // HORI Fighting Commander 4 PS4
    {ControllerType_PS4Controller, MAKE_CONTROLLER_ID(0x0f0d, 0x0066),
     0}, // HORIPAD 4 FPS Plus
    {ControllerType_PS4Controller, MAKE_CONTROLLER_ID(0x0f0d, 0x0084),
     0}, // HORI Fighting Commander PS4
    {ControllerType_PS4Controller, MAKE_CONTROLLER_ID(0x0f0d, 0x0087),
     0}, // HORI Fighting Stick mini 4
    {ControllerType_PS4Controller, MAKE_CONTROLLER_ID(0x0f0d, 0x008a),
     0}, // HORI Real Arcade Pro 4
    {ControllerType_PS4Controller, MAKE_CONTROLLER_ID(0x0f0d, 0x009c),
     0}, // HORI TAC PRO mousething
    {ControllerType_PS4Controller, MAKE_CONTROLLER_ID(0x0f0d, 0x00a0),
     0}, // HORI TAC4 mousething
    {ControllerType_XInputPS4Controller, MAKE_CONTROLLER_ID(0x0f0d, 0x00ed),
     0}, // Hori Fighting Stick mini 4 kai - becomes an Xbox 360 controller
         // on PC
    {ControllerType_PS4Controller, MAKE_CONTROLLER_ID(0x0f0d, 0x00ee),
     0}, // Hori mini wired
         // https://www.playstation.com/en-us/explore/accessories/gaming-controllers/mini-wired-gamepad/
    {ControllerType_PS4Controller, MAKE_CONTROLLER_ID(0x0f0d, 0x011c),
     0}, // Hori Fighting Stick α
    {ControllerType_PS4Controller, MAKE_CONTROLLER_ID(0x0f0d, 0x0123),
     0}, // HORI Wireless Controller Light (Japan only) - only over bt- over
         // usb is xbox and pid 0x0124
    {ControllerType_PS4Controller, MAKE_CONTROLLER_ID(0x0f0d, 0x0162),
     0}, // HORI Fighting Commander OCTA
    {ControllerType_XInputPS4Controller, MAKE_CONTROLLER_ID(0x0f0d, 0x0164),
     0}, // HORI Fighting Commander OCTA
    {ControllerType_PS4Controller, MAKE_CONTROLLER_ID(0x11c0, 0x4001),
     0}, // "PS4 Fun Controller" added from user log
    {ControllerType_XInputPS4Controller, MAKE_CONTROLLER_ID(0x146b, 0x0603),
     0}, // Nacon PS4 Compact Controller
    {ControllerType_XInputPS4Controller, MAKE_CONTROLLER_ID(0x146b, 0x0604),
     0}, // NACON Daija Arcade Stick
    {ControllerType_XInputPS4Controller, MAKE_CONTROLLER_ID(0x146b, 0x0605),
     0}, // NACON PS4 controller in Xbox mode - might also be other bigben
         // brand xbox controllers
    {ControllerType_XInputPS4Controller, MAKE_CONTROLLER_ID(0x146b, 0x0606),
     0}, // NACON Unknown Controller
    {ControllerType_XInputPS4Controller, MAKE_CONTROLLER_ID(0x146b, 0x0609),
     0}, // NACON Wireless Controller for PS4
    {ControllerType_PS4Controller, MAKE_CONTROLLER_ID(0x146b, 0x0d01),
     0}, // Nacon Revolution Pro Controller - has gyro
    {ControllerType_PS4Controller, MAKE_CONTROLLER_ID(0x146b, 0x0d02),
     0}, // Nacon Revolution Pro Controller v2 - has gyro
    {ControllerType_PS4Controller, MAKE_CONTROLLER_ID(0x146b, 0x0d06),
     0}, // NACON Asymmetric Controller Wireless Dongle -- show up as ps4
         // until you connect controller to it then it reboots into Xbox
         // controller with different vvid/pid
    {ControllerType_PS4Controller, MAKE_CONTROLLER_ID(0x146b, 0x0d08),
     0}, // NACON Revolution Unlimited Wireless Dongle
    {ControllerType_PS4Controller, MAKE_CONTROLLER_ID(0x146b, 0x0d09),
     0}, // NACON Daija Fight Stick - touchpad but no gyro/rumble
    {ControllerType_PS4Controller, MAKE_CONTROLLER_ID(0x146b, 0x0d10),
     0}, // NACON Revolution Infinite - has gyro
    {ControllerType_PS4Controller, MAKE_CONTROLLER_ID(0x146b, 0x0d10),
     0}, // NACON Revolution Unlimited
    {ControllerType_PS4Controller, MAKE_CONTROLLER_ID(0x146b, 0x0d13),
     0}, // NACON Revolution Pro Controller 3
    {ControllerType_PS4Controller, MAKE_CONTROLLER_ID(0x146b, 0x1103),
     0}, // NACON Asymmetric Controller -- on windows this doesn't enumerate
    {ControllerType_PS4Controller, MAKE_CONTROLLER_ID(0x1532, 0X0401),
     0}, // Razer Panthera PS4 Controller
    {ControllerType_PS4Controller, MAKE_CONTROLLER_ID(0x1532, 0x1000),
     0}, // Razer Raiju PS4 Controller
    {ControllerType_PS4Controller, MAKE_CONTROLLER_ID(0x1532, 0x1004),
     0}, // Razer Raiju 2 Ultimate USB
    {ControllerType_PS4Controller, MAKE_CONTROLLER_ID(0x1532, 0x1007),
     0}, // Razer Raiju 2 Tournament edition USB
    {ControllerType_PS4Controller, MAKE_CONTROLLER_ID(0x1532, 0x1008),
     0}, // Razer Panthera Evo Fightstick
    {ControllerType_PS4Controller, MAKE_CONTROLLER_ID(0x1532, 0x1009),
     0}, // Razer Raiju 2 Ultimate BT
    {ControllerType_PS4Controller, MAKE_CONTROLLER_ID(0x1532, 0x100A),
     0}, // Razer Raiju 2 Tournament edition BT
    {ControllerType_PS4Controller, MAKE_CONTROLLER_ID(0x1532, 0x1100),
     0}, // Razer RAION Fightpad - Trackpad, no gyro, lightbar hardcoded to
         // green
    {ControllerType_PS4Controller, MAKE_CONTROLLER_ID(0x20d6, 0x792a),
     0}, // PowerA Fusion Fight Pad
    {ControllerType_PS4Controller, MAKE_CONTROLLER_ID(0x2c22, 0x2000),
     0}, // Qanba Drone
    {ControllerType_PS4Controller, MAKE_CONTROLLER_ID(0x2c22, 0x2300),
     0}, // Qanba Obsidian
    {ControllerType_XInputPS4Controller, MAKE_CONTROLLER_ID(0x2c22, 0x2303),
     0}, // Qanba Obsidian Arcade Joystick
    {ControllerType_PS4Controller, MAKE_CONTROLLER_ID(0x2c22, 0x2500),
     0}, // Qanba Dragon
    {ControllerType_XInputPS4Controller, MAKE_CONTROLLER_ID(0x2c22, 0x2503),
     0}, // Qanba Dragon Arcade Joystick
    {ControllerType_PS4Controller, MAKE_CONTROLLER_ID(0x3285, 0x0d16),
     0}, // NACON Revolution 5 Pro (PS4 mode with dongle)
    {ControllerType_PS4Controller, MAKE_CONTROLLER_ID(0x3285, 0x0d17),
     0}, // NACON Revolution 5 Pro (PS4 mode wired)
    {ControllerType_PS4Controller, MAKE_CONTROLLER_ID(0x7545, 0x0104),
     0}, // Armor 3 or Level Up Cobra - At least one variant has gyro
    {ControllerType_XInputPS4Controller, MAKE_CONTROLLER_ID(0x9886, 0x0024),
     0}, // Astro C40 in Xbox 360 mode
    {ControllerType_PS4Controller, MAKE_CONTROLLER_ID(0x9886, 0x0025),
     0}, // Astro C40
    // Removing the Giotek because there were a bunch of help tickets from users
    // w/ issues including from non-PS4 controller users. This VID/PID is
    // probably used in different FW's
    //	{ ControllerType_PS4Controller, MAKE_CONTROLLER_ID( 0x7545, 0x1122 ),
    // 0 },	// Giotek VX4 - trackpad/gyro don't work. Had to not filter on
    // interface info. Light bar is flaky, but works.

    {ControllerType_PS5Controller, MAKE_CONTROLLER_ID(0x054c, 0x0ce6),
     0}, // Sony DualSense Controller
    {ControllerType_PS5Controller, MAKE_CONTROLLER_ID(0x054c, 0x0df2),
     0}, // Sony DualSense Edge Controller
    {ControllerType_PS5Controller, MAKE_CONTROLLER_ID(0x054c, 0x0e5f),
     0}, // Access Controller for PS5
    {ControllerType_PS5Controller, MAKE_CONTROLLER_ID(0x0e6f, 0x0209),
     0}, // Victrix Pro FS PS4/PS5 (PS5 mode)
    {ControllerType_PS5Controller, MAKE_CONTROLLER_ID(0x0f0d, 0x0163),
     0}, // HORI Fighting Commander OCTA
    {ControllerType_PS5Controller, MAKE_CONTROLLER_ID(0x0f0d, 0x0184),
     0}, // Hori Fighting Stick α
    {ControllerType_PS5Controller, MAKE_CONTROLLER_ID(0x1532, 0x100b),
     0}, // Razer Wolverine V2 Pro (Wired)
    {ControllerType_PS5Controller, MAKE_CONTROLLER_ID(0x1532, 0x100c),
     0}, // Razer Wolverine V2 Pro (Wireless)
    {ControllerType_PS5Controller, MAKE_CONTROLLER_ID(0x1532, 0x1012),
     0}, // Razer Kitsune
    {ControllerType_PS5Controller, MAKE_CONTROLLER_ID(0x3285, 0x0d18),
     0}, // NACON Revolution 5 Pro (PS5 mode with dongle)
    {ControllerType_PS5Controller, MAKE_CONTROLLER_ID(0x3285, 0x0d19),
     0}, // NACON Revolution 5 Pro (PS5 mode wired)
    {ControllerType_PS5Controller, MAKE_CONTROLLER_ID(0x358a, 0x0104),
     0}, // Backbone One PlayStation Edition for iOS

    {ControllerType_UnknownNonSteamController,
     MAKE_CONTROLLER_ID(0x0079, 0x0006),
     0}, // DragonRise Generic USB PCB, sometimes configured as a PC Twin
         // Shock Controller - looks like a DS3 but the face buttons are 1-4
         // instead of symbols

    {ControllerType_XBox360Controller, MAKE_CONTROLLER_ID(0x0079, 0x18d4),
     0}, // GPD Win 2 X-Box Controller
    {ControllerType_XBox360Controller, MAKE_CONTROLLER_ID(0x03eb, 0xff02),
     0}, // Wooting Two
    {ControllerType_XBox360Controller, MAKE_CONTROLLER_ID(0x044f, 0xb326),
     0}, // Thrustmaster Gamepad GP XID
    {ControllerType_XBox360Controller, MAKE_CONTROLLER_ID(0x045e, 0x028e),
     "Xbox 360 Controller"}, // Microsoft Xbox 360 Wired Controller
    {ControllerType_XBox360Controller, MAKE_CONTROLLER_ID(0x045e, 0x028f),
     "Xbox 360 Controller"}, // Microsoft Xbox 360 Play and Charge Cable
    {ControllerType_XBox360Controller, MAKE_CONTROLLER_ID(0x045e, 0x0291),
     "Xbox 360 Wireless Controller"}, // X-box 360 Wireless Receiver (third
                                      // party knockoff)
    {ControllerType_XBox360Controller, MAKE_CONTROLLER_ID(0x045e, 0x02a0),
     0}, // Microsoft Xbox 360 Big Button IR
    {ControllerType_XBox360Controller, MAKE_CONTROLLER_ID(0x045e, 0x02a1),
     "Xbox 360 Wireless Controller"}, // Microsoft Xbox 360 Wireless Controller
                                      // with XUSB driver on Windows
    {ControllerType_XBox360Controller, MAKE_CONTROLLER_ID(0x045e, 0x02a9),
     "Xbox 360 Wireless Controller"}, // X-box 360 Wireless Receiver (third
                                      // party knockoff)
    {ControllerType_XBox360Controller, MAKE_CONTROLLER_ID(0x045e, 0x0719),
     "Xbox 360 Wireless Controller"}, // Microsoft Xbox 360 Wireless Receiver
    {ControllerType_XBox360Controller, MAKE_CONTROLLER_ID(0x046d, 0xc21d),
     0}, // Logitech Gamepad F310
    {ControllerType_XBox360Controller, MAKE_CONTROLLER_ID(0x046d, 0xc21e),
     0}, // Logitech Gamepad F510
    {ControllerType_XBox360Controller, MAKE_CONTROLLER_ID(0x046d, 0xc21f),
     0}, // Logitech Gamepad F710
    {ControllerType_XBox360Controller, MAKE_CONTROLLER_ID(0x046d, 0xc242),
     0}, // Logitech Chillstream Controller
    {ControllerType_XBox360Controller, MAKE_CONTROLLER_ID(0x056e, 0x2004),
     0}, // Elecom JC-U3613M
    // This isn't actually an Xbox 360 controller, it just looks like one
    //	{ ControllerType_XBox360Controller, MAKE_CONTROLLER_ID( 0x06a3, 0xf51a
    //),
    // 0 },	// Saitek P3600
    {ControllerType_XBox360Controller, MAKE_CONTROLLER_ID(0x0738, 0x4716),
     0}, // Mad Catz Wired Xbox 360 Controller
    {ControllerType_XBox360Controller, MAKE_CONTROLLER_ID(0x0738, 0x4718),
     0}, // Mad Catz Street Fighter IV FightStick SE
    {ControllerType_XBox360Controller, MAKE_CONTROLLER_ID(0x0738, 0x4726),
     0}, // Mad Catz Xbox 360 Controller
    {ControllerType_XBox360Controller, MAKE_CONTROLLER_ID(0x0738, 0x4728),
     0}, // Mad Catz Street Fighter IV FightPad
    {ControllerType_XBox360Controller, MAKE_CONTROLLER_ID(0x0738, 0x4736),
     0}, // Mad Catz MicroCon Gamepad
    {ControllerType_XBox360Controller, MAKE_CONTROLLER_ID(0x0738, 0x4738),
     0}, // Mad Catz Wired Xbox 360 Controller (SFIV)
    {ControllerType_XBox360Controller, MAKE_CONTROLLER_ID(0x0738, 0x4740),
     0}, // Mad Catz Beat Pad
    {ControllerType_XBox360Controller, MAKE_CONTROLLER_ID(0x0738, 0xb726),
     0}, // Mad Catz Xbox controller - MW2
    {ControllerType_XBox360Controller, MAKE_CONTROLLER_ID(0x0738, 0xbeef),
     0}, // Mad Catz JOYTECH NEO SE Advanced GamePad
    {ControllerType_XBox360Controller, MAKE_CONTROLLER_ID(0x0738, 0xcb02),
     0}, // Saitek Cyborg Rumble Pad - PC/Xbox 360
    {ControllerType_XBox360Controller, MAKE_CONTROLLER_ID(0x0738, 0xcb03),
     0}, // Saitek P3200 Rumble Pad - PC/Xbox 360
    {ControllerType_XBox360Controller, MAKE_CONTROLLER_ID(0x0738, 0xf738),
     0}, // Super SFIV FightStick TE S
    {ControllerType_XBox360Controller, MAKE_CONTROLLER_ID(0x0955, 0x7210),
     0}, // Nvidia Shield local controller
    {ControllerType_XBox360Controller, MAKE_CONTROLLER_ID(0x0955, 0xb400),
     0}, // NVIDIA Shield streaming controller
    {ControllerType_XBox360Controller, MAKE_CONTROLLER_ID(0x0e6f, 0x0105),
     0}, // HSM3 Xbox360 dancepad
    {ControllerType_XBox360Controller, MAKE_CONTROLLER_ID(0x0e6f, 0x0113),
     "PDP Xbox 360 Afterglow"}, // PDP Afterglow Gamepad for Xbox 360
    {ControllerType_XBox360Controller, MAKE_CONTROLLER_ID(0x0e6f, 0x011f),
     "PDP Xbox 360 Rock Candy"}, // PDP Rock Candy Gamepad for Xbox 360
    {ControllerType_XBox360Controller, MAKE_CONTROLLER_ID(0x0e6f, 0x0125),
     "PDP INJUSTICE FightStick"}, // PDP INJUSTICE FightStick for Xbox 360
    {ControllerType_XBox360Controller, MAKE_CONTROLLER_ID(0x0e6f, 0x0127),
     "PDP INJUSTICE FightPad"}, // PDP INJUSTICE FightPad for Xbox 360
    {ControllerType_XBox360Controller, MAKE_CONTROLLER_ID(0x0e6f, 0x0131),
     "PDP EA Soccer Controller"}, // PDP EA Soccer Gamepad
    {ControllerType_XBox360Controller, MAKE_CONTROLLER_ID(0x0e6f, 0x0133),
     "PDP Battlefield 4 Controller"}, // PDP Battlefield 4 Gamepad
    {ControllerType_XBox360Controller, MAKE_CONTROLLER_ID(0x0e6f, 0x0143),
     "PDP MK X Fight Stick"}, // PDP MK X Fight Stick for Xbox 360
    {ControllerType_XBox360Controller, MAKE_CONTROLLER_ID(0x0e6f, 0x0147),
     "PDP Xbox 360 Marvel Controller"}, // PDP Marvel Controller for Xbox 360
    {ControllerType_XBox360Controller, MAKE_CONTROLLER_ID(0x0e6f, 0x0201),
     "PDP Xbox 360 Controller"}, // PDP Gamepad for Xbox 360
    {ControllerType_XBox360Controller, MAKE_CONTROLLER_ID(0x0e6f, 0x0213),
     "PDP Xbox 360 Afterglow"}, // PDP Afterglow Gamepad for Xbox 360
    {ControllerType_XBox360Controller, MAKE_CONTROLLER_ID(0x0e6f, 0x021f),
     "PDP Xbox 360 Rock Candy"}, // PDP Rock Candy Gamepad for Xbox 360
    {ControllerType_XBox360Controller, MAKE_CONTROLLER_ID(0x0e6f, 0x0301),
     "PDP Xbox 360 Controller"}, // PDP Gamepad for Xbox 360
    {ControllerType_XBox360Controller, MAKE_CONTROLLER_ID(0x0e6f, 0x0313),
     "PDP Xbox 360 Afterglow"}, // PDP Afterglow Gamepad for Xbox 360
    {ControllerType_XBox360Controller, MAKE_CONTROLLER_ID(0x0e6f, 0x0314),
     "PDP Xbox 360 Afterglow"}, // PDP Afterglow Gamepad for Xbox 360
    {ControllerType_XBox360Controller, MAKE_CONTROLLER_ID(0x0e6f, 0x0401),
     "PDP Xbox 360 Controller"}, // PDP Gamepad for Xbox 360
    {ControllerType_XBox360Controller, MAKE_CONTROLLER_ID(0x0e6f, 0x0413),
     0}, // PDP Afterglow AX.1 (unlisted)
    {ControllerType_XBox360Controller, MAKE_CONTROLLER_ID(0x0e6f, 0x0501),
     0}, // PDP Xbox 360 Controller (unlisted)
    {ControllerType_XBox360Controller, MAKE_CONTROLLER_ID(0x0e6f, 0xf900),
     0}, // PDP Afterglow AX.1 (unlisted)
    {ControllerType_XBox360Controller, MAKE_CONTROLLER_ID(0x0f0d, 0x000a),
     0}, // Hori Co. DOA4 FightStick
    {ControllerType_XBox360Controller, MAKE_CONTROLLER_ID(0x0f0d, 0x000c),
     0}, // Hori PadEX Turbo
    {ControllerType_XBox360Controller, MAKE_CONTROLLER_ID(0x0f0d, 0x000d),
     0}, // Hori Fighting Stick EX2
    {ControllerType_XBox360Controller, MAKE_CONTROLLER_ID(0x0f0d, 0x0016),
     0}, // Hori Real Arcade Pro.EX
    {ControllerType_XBox360Controller, MAKE_CONTROLLER_ID(0x0f0d, 0x001b),
     0}, // Hori Real Arcade Pro VX
    {ControllerType_XBox360Controller, MAKE_CONTROLLER_ID(0x0f0d, 0x008c),
     0}, // Hori Real Arcade Pro 4
    {ControllerType_XBox360Controller, MAKE_CONTROLLER_ID(0x0f0d, 0x00db),
     "HORI Slime Controller"}, // Hori Dragon Quest Slime Controller
    {ControllerType_XBox360Controller, MAKE_CONTROLLER_ID(0x0f0d, 0x011e),
     0}, // Hori Fighting Stick α
    {ControllerType_XBox360Controller, MAKE_CONTROLLER_ID(0x1038, 0x1430),
     "SteelSeries Stratus Duo"}, // SteelSeries Stratus Duo
    {ControllerType_XBox360Controller, MAKE_CONTROLLER_ID(0x1038, 0x1431),
     "SteelSeries Stratus Duo"}, // SteelSeries Stratus Duo
    {ControllerType_XBox360Controller, MAKE_CONTROLLER_ID(0x1038, 0xb360),
     0}, // SteelSeries Nimbus/Stratus XL
    {ControllerType_XBox360Controller, MAKE_CONTROLLER_ID(0x11c9, 0x55f0),
     0}, // Nacon GC-100XF
    {ControllerType_XBox360Controller, MAKE_CONTROLLER_ID(0x12ab, 0x0004),
     0}, // Honey Bee Xbox360 dancepad
    {ControllerType_XBox360Controller, MAKE_CONTROLLER_ID(0x12ab, 0x0301),
     0}, // PDP AFTERGLOW AX.1
    {ControllerType_XBox360Controller, MAKE_CONTROLLER_ID(0x12ab, 0x0303),
     0}, // Mortal Kombat Klassic FightStick
    {ControllerType_XBox360Controller, MAKE_CONTROLLER_ID(0x1430, 0x02a0),
     0}, // RedOctane Controller Adapter
    {ControllerType_XBox360Controller, MAKE_CONTROLLER_ID(0x1430, 0x4748),
     0}, // RedOctane Guitar Hero X-plorer
    {ControllerType_XBox360Controller, MAKE_CONTROLLER_ID(0x1430, 0xf801),
     0}, // RedOctane Controller
    {ControllerType_XBox360Controller, MAKE_CONTROLLER_ID(0x146b, 0x0601),
     0}, // BigBen Interactive XBOX 360 Controller
         //	{ ControllerType_XBox360Controller, MAKE_CONTROLLER_ID( 0x1532,
         // 0x0037 ),
         // 0 },	// Razer
         // Sabertooth
    {ControllerType_XBox360Controller, MAKE_CONTROLLER_ID(0x15e4, 0x3f00),
     0}, // Power A Mini Pro Elite
    {ControllerType_XBox360Controller, MAKE_CONTROLLER_ID(0x15e4, 0x3f0a),
     0}, // Xbox Airflo wired controller
    {ControllerType_XBox360Controller, MAKE_CONTROLLER_ID(0x15e4, 0x3f10),
     0}, // Batarang Xbox 360 controller
    {ControllerType_XBox360Controller, MAKE_CONTROLLER_ID(0x162e, 0xbeef),
     0}, // Joytech Neo-Se Take2
    {ControllerType_XBox360Controller, MAKE_CONTROLLER_ID(0x1689, 0xfd00),
     0}, // Razer Onza Tournament Edition
    {ControllerType_XBox360Controller, MAKE_CONTROLLER_ID(0x1689, 0xfd01),
     0}, // Razer Onza Classic Edition
    {ControllerType_XBox360Controller, MAKE_CONTROLLER_ID(0x1689, 0xfe00),
     0}, // Razer Sabertooth
    {ControllerType_XBox360Controller, MAKE_CONTROLLER_ID(0x1949, 0x041a),
     "Amazon Luna Controller"}, // Amazon Luna Controller
    {ControllerType_XBox360Controller, MAKE_CONTROLLER_ID(0x1bad, 0x0002),
     0}, // Harmonix Rock Band Guitar
    {ControllerType_XBox360Controller, MAKE_CONTROLLER_ID(0x1bad, 0x0003),
     0}, // Harmonix Rock Band Drumkit
    {ControllerType_XBox360Controller, MAKE_CONTROLLER_ID(0x1bad, 0xf016),
     0}, // Mad Catz Xbox 360 Controller
    {ControllerType_XBox360Controller, MAKE_CONTROLLER_ID(0x1bad, 0xf018),
     0}, // Mad Catz Street Fighter IV SE Fighting Stick
    {ControllerType_XBox360Controller, MAKE_CONTROLLER_ID(0x1bad, 0xf019),
     0}, // Mad Catz Brawlstick for Xbox 360
    {ControllerType_XBox360Controller, MAKE_CONTROLLER_ID(0x1bad, 0xf021),
     0}, // Mad Cats Ghost Recon FS GamePad
    {ControllerType_XBox360Controller, MAKE_CONTROLLER_ID(0x1bad, 0xf023),
     0}, // MLG Pro Circuit Controller (Xbox)
    {ControllerType_XBox360Controller, MAKE_CONTROLLER_ID(0x1bad, 0xf025),
     0}, // Mad Catz Call Of Duty
    {ControllerType_XBox360Controller, MAKE_CONTROLLER_ID(0x1bad, 0xf027),
     0}, // Mad Catz FPS Pro
    {ControllerType_XBox360Controller, MAKE_CONTROLLER_ID(0x1bad, 0xf028),
     0}, // Street Fighter IV FightPad
    {ControllerType_XBox360Controller, MAKE_CONTROLLER_ID(0x1bad, 0xf02e),
     0}, // Mad Catz Fightpad
    {ControllerType_XBox360Controller, MAKE_CONTROLLER_ID(0x1bad, 0xf036),
     0}, // Mad Catz MicroCon GamePad Pro
    {ControllerType_XBox360Controller, MAKE_CONTROLLER_ID(0x1bad, 0xf038),
     0}, // Street Fighter IV FightStick TE
    {ControllerType_XBox360Controller, MAKE_CONTROLLER_ID(0x1bad, 0xf039),
     0}, // Mad Catz MvC2 TE
    {ControllerType_XBox360Controller, MAKE_CONTROLLER_ID(0x1bad, 0xf03a),
     0}, // Mad Catz SFxT Fightstick Pro
    {ControllerType_XBox360Controller, MAKE_CONTROLLER_ID(0x1bad, 0xf03d),
     0}, // Street Fighter IV Arcade Stick TE - Chun Li
    {ControllerType_XBox360Controller, MAKE_CONTROLLER_ID(0x1bad, 0xf03e),
     0}, // Mad Catz MLG FightStick TE
    {ControllerType_XBox360Controller, MAKE_CONTROLLER_ID(0x1bad, 0xf03f),
     0}, // Mad Catz FightStick SoulCaliber
    {ControllerType_XBox360Controller, MAKE_CONTROLLER_ID(0x1bad, 0xf042),
     0}, // Mad Catz FightStick TES+
    {ControllerType_XBox360Controller, MAKE_CONTROLLER_ID(0x1bad, 0xf080),
     0}, // Mad Catz FightStick TE2
    {ControllerType_XBox360Controller, MAKE_CONTROLLER_ID(0x1bad, 0xf501),
     0}, // HoriPad EX2 Turbo
    {ControllerType_XBox360Controller, MAKE_CONTROLLER_ID(0x1bad, 0xf502),
     0}, // Hori Real Arcade Pro.VX SA
    {ControllerType_XBox360Controller, MAKE_CONTROLLER_ID(0x1bad, 0xf503),
     0}, // Hori Fighting Stick VX
    {ControllerType_XBox360Controller, MAKE_CONTROLLER_ID(0x1bad, 0xf504),
     0}, // Hori Real Arcade Pro. EX
    {ControllerType_XBox360Controller, MAKE_CONTROLLER_ID(0x1bad, 0xf505),
     0}, // Hori Fighting Stick EX2B
    {ControllerType_XBox360Controller, MAKE_CONTROLLER_ID(0x1bad, 0xf506),
     0}, // Hori Real Arcade Pro.EX Premium VLX
    {ControllerType_XBox360Controller, MAKE_CONTROLLER_ID(0x1bad, 0xf900),
     0}, // Harmonix Xbox 360 Controller
    {ControllerType_XBox360Controller, MAKE_CONTROLLER_ID(0x1bad, 0xf901),
     0}, // Gamestop Xbox 360 Controller
    {ControllerType_XBox360Controller, MAKE_CONTROLLER_ID(0x1bad, 0xf902),
     0}, // Mad Catz Gamepad2
    {ControllerType_XBox360Controller, MAKE_CONTROLLER_ID(0x1bad, 0xf903),
     0}, // Tron Xbox 360 controller
    {ControllerType_XBox360Controller, MAKE_CONTROLLER_ID(0x1bad, 0xf904),
     0}, // PDP Versus Fighting Pad
    {ControllerType_XBox360Controller, MAKE_CONTROLLER_ID(0x1bad, 0xf906),
     0}, // MortalKombat FightStick
    {ControllerType_XBox360Controller, MAKE_CONTROLLER_ID(0x1bad, 0xfa01),
     0}, // MadCatz GamePad
    {ControllerType_XBox360Controller, MAKE_CONTROLLER_ID(0x1bad, 0xfd00),
     0}, // Razer Onza TE
    {ControllerType_XBox360Controller, MAKE_CONTROLLER_ID(0x1bad, 0xfd01),
     0}, // Razer Onza
    {ControllerType_XBox360Controller, MAKE_CONTROLLER_ID(0x24c6, 0x5000),
     0}, // Razer Atrox Arcade Stick
    {ControllerType_XBox360Controller, MAKE_CONTROLLER_ID(0x24c6, 0x5300),
     0}, // PowerA MINI PROEX Controller
    {ControllerType_XBox360Controller, MAKE_CONTROLLER_ID(0x24c6, 0x5303),
     0}, // Xbox Airflo wired controller
    {ControllerType_XBox360Controller, MAKE_CONTROLLER_ID(0x24c6, 0x530a),
     0}, // Xbox 360 Pro EX Controller
    {ControllerType_XBox360Controller, MAKE_CONTROLLER_ID(0x24c6, 0x531a),
     0}, // PowerA Pro Ex
    {ControllerType_XBox360Controller, MAKE_CONTROLLER_ID(0x24c6, 0x5397),
     0}, // FUS1ON Tournament Controller
    {ControllerType_XBox360Controller, MAKE_CONTROLLER_ID(0x24c6, 0x5500),
     0}, // Hori XBOX 360 EX 2 with Turbo
    {ControllerType_XBox360Controller, MAKE_CONTROLLER_ID(0x24c6, 0x5501),
     0}, // Hori Real Arcade Pro VX-SA
    {ControllerType_XBox360Controller, MAKE_CONTROLLER_ID(0x24c6, 0x5502),
     0}, // Hori Fighting Stick VX Alt
    {ControllerType_XBox360Controller, MAKE_CONTROLLER_ID(0x24c6, 0x5503),
     0}, // Hori Fighting Edge
    {ControllerType_XBox360Controller, MAKE_CONTROLLER_ID(0x24c6, 0x5506),
     0}, // Hori SOULCALIBUR V Stick
    {ControllerType_XBox360Controller, MAKE_CONTROLLER_ID(0x24c6, 0x550d),
     0}, // Hori GEM Xbox controller
    {ControllerType_XBox360Controller, MAKE_CONTROLLER_ID(0x24c6, 0x550e),
     0}, // Hori Real Arcade Pro V Kai 360
    {ControllerType_XBox360Controller, MAKE_CONTROLLER_ID(0x24c6, 0x5508),
     0}, // Hori PAD A
    {ControllerType_XBox360Controller, MAKE_CONTROLLER_ID(0x24c6, 0x5510),
     0}, // Hori Fighting Commander ONE
    {ControllerType_XBox360Controller, MAKE_CONTROLLER_ID(0x24c6, 0x5b00),
     0}, // ThrustMaster Ferrari Italia 458 Racing Wheel
    {ControllerType_XBox360Controller, MAKE_CONTROLLER_ID(0x24c6, 0x5b02),
     0}, // Thrustmaster, Inc. GPX Controller
    {ControllerType_XBox360Controller, MAKE_CONTROLLER_ID(0x24c6, 0x5b03),
     0}, // Thrustmaster Ferrari 458 Racing Wheel
    {ControllerType_XBox360Controller, MAKE_CONTROLLER_ID(0x24c6, 0x5d04),
     0}, // Razer Sabertooth
    {ControllerType_XBox360Controller, MAKE_CONTROLLER_ID(0x24c6, 0xfafa),
     0}, // Aplay Controller
    {ControllerType_XBox360Controller, MAKE_CONTROLLER_ID(0x24c6, 0xfafb),
     0}, // Aplay Controller
    {ControllerType_XBox360Controller, MAKE_CONTROLLER_ID(0x24c6, 0xfafc),
     0}, // Afterglow Gamepad 1
    {ControllerType_XBox360Controller, MAKE_CONTROLLER_ID(0x24c6, 0xfafd),
     0}, // Afterglow Gamepad 3
    {ControllerType_XBox360Controller, MAKE_CONTROLLER_ID(0x24c6, 0xfafe),
     0}, // Rock Candy Gamepad for Xbox 360

    {ControllerType_XBoxOneController, MAKE_CONTROLLER_ID(0x03f0, 0x0495),
     0}, // HP HyperX Clutch Gladiate
    {ControllerType_XBoxOneController, MAKE_CONTROLLER_ID(0x044f, 0xd012),
     0}, // ThrustMaster eSwap PRO Controller Xbox
    {ControllerType_XBoxOneController, MAKE_CONTROLLER_ID(0x045e, 0x02d1),
     "Xbox One Controller"}, // Microsoft Xbox One Controller
    {ControllerType_XBoxOneController, MAKE_CONTROLLER_ID(0x045e, 0x02dd),
     "Xbox One Controller"}, // Microsoft Xbox One Controller (Firmware 2015)
    {ControllerType_XBoxOneController, MAKE_CONTROLLER_ID(0x045e, 0x02e0),
     "Xbox One S Controller"}, // Microsoft Xbox One S Controller (Bluetooth)
    {ControllerType_XBoxOneController, MAKE_CONTROLLER_ID(0x045e, 0x02e3),
     "Xbox One Elite Controller"}, // Microsoft Xbox One Elite Controller
    {ControllerType_XBoxOneController, MAKE_CONTROLLER_ID(0x045e, 0x02ea),
     "Xbox One S Controller"}, // Microsoft Xbox One S Controller
    {ControllerType_XBoxOneController, MAKE_CONTROLLER_ID(0x045e, 0x02fd),
     "Xbox One S Controller"}, // Microsoft Xbox One S Controller (Bluetooth)
    {ControllerType_XBoxOneController, MAKE_CONTROLLER_ID(0x045e, 0x02ff),
     "Xbox One Controller"}, // Microsoft Xbox One Controller with XBOXGIP
                             // driver on Windows
    {ControllerType_XBoxOneController, MAKE_CONTROLLER_ID(0x045e, 0x0b00),
     "Xbox One Elite 2 Controller"}, // Microsoft Xbox One Elite Series 2
                                     // Controller
    {ControllerType_XBoxOneController, MAKE_CONTROLLER_ID(0x045e, 0x0b05),
     "Xbox One Elite 2 Controller"}, // Microsoft Xbox One Elite Series 2
                                     // Controller (Bluetooth)
    {ControllerType_XBoxOneController, MAKE_CONTROLLER_ID(0x045e, 0x0b0a),
     "Xbox Adaptive Controller"}, // Microsoft Xbox Adaptive Controller
    {ControllerType_XBoxOneController, MAKE_CONTROLLER_ID(0x045e, 0x0b0c),
     "Xbox Adaptive Controller"}, // Microsoft Xbox Adaptive Controller
                                  // (Bluetooth)
    {ControllerType_XBoxOneController, MAKE_CONTROLLER_ID(0x045e, 0x0b12),
     "Xbox Series X Controller"}, // Microsoft Xbox Series X Controller
    {ControllerType_XBoxOneController, MAKE_CONTROLLER_ID(0x045e, 0x0b13),
     "Xbox Series X Controller"}, // Microsoft Xbox Series X Controller (BLE)
    {ControllerType_XBoxOneController, MAKE_CONTROLLER_ID(0x045e, 0x0b20),
     "Xbox One S Controller"}, // Microsoft Xbox One S Controller (BLE)
    {ControllerType_XBoxOneController, MAKE_CONTROLLER_ID(0x045e, 0x0b21),
     "Xbox Adaptive Controller"}, // Microsoft Xbox Adaptive Controller (BLE)
    {ControllerType_XBoxOneController, MAKE_CONTROLLER_ID(0x045e, 0x0b22),
     "Xbox One Elite 2 Controller"}, // Microsoft Xbox One Elite Series 2
                                     // Controller (BLE)
    {ControllerType_XBoxOneController, MAKE_CONTROLLER_ID(0x0738, 0x4a01),
     0}, // Mad Catz FightStick TE 2
    {ControllerType_XBoxOneController, MAKE_CONTROLLER_ID(0x0e6f, 0x0139),
     "PDP Xbox One Afterglow"}, // PDP Afterglow Wired Controller for Xbox One
    {ControllerType_XBoxOneController, MAKE_CONTROLLER_ID(0x0e6f, 0x013B),
     "PDP Xbox One Face-Off Controller"}, // PDP Face-Off Gamepad for Xbox One
    {ControllerType_XBoxOneController, MAKE_CONTROLLER_ID(0x0e6f, 0x013a),
     0}, // PDP Xbox One Controller (unlisted)
    {ControllerType_XBoxOneController, MAKE_CONTROLLER_ID(0x0e6f, 0x0145),
     "PDP MK X Fight Pad"}, // PDP MK X Fight Pad for Xbox One
    {ControllerType_XBoxOneController, MAKE_CONTROLLER_ID(0x0e6f, 0x0146),
     "PDP Xbox One Rock Candy"}, // PDP Rock Candy Wired Controller for Xbox One
    {ControllerType_XBoxOneController, MAKE_CONTROLLER_ID(0x0e6f, 0x015b),
     "PDP Fallout 4 Vault Boy Controller"}, // PDP Fallout 4 Vault Boy Wired
                                            // Controller for Xbox One
    {ControllerType_XBoxOneController, MAKE_CONTROLLER_ID(0x0e6f, 0x015c),
     "PDP Xbox One @Play Controller"}, // PDP @Play Wired Controller for Xbox
                                       // One
    {ControllerType_XBoxOneController, MAKE_CONTROLLER_ID(0x0e6f, 0x015d),
     "PDP Mirror's Edge Controller"}, // PDP Mirror's Edge Wired Controller for
                                      // Xbox One
    {ControllerType_XBoxOneController, MAKE_CONTROLLER_ID(0x0e6f, 0x015f),
     "PDP Metallic Controller"}, // PDP Metallic Wired Controller for Xbox One
    {ControllerType_XBoxOneController, MAKE_CONTROLLER_ID(0x0e6f, 0x0160),
     "PDP NFL Face-Off Controller"}, // PDP NFL Official Face-Off Wired
                                     // Controller for Xbox One
    {ControllerType_XBoxOneController, MAKE_CONTROLLER_ID(0x0e6f, 0x0161),
     "PDP Xbox One Camo"}, // PDP Camo Wired Controller for Xbox One
    {ControllerType_XBoxOneController, MAKE_CONTROLLER_ID(0x0e6f, 0x0162),
     "PDP Xbox One Controller"}, // PDP Wired Controller for Xbox One
    {ControllerType_XBoxOneController, MAKE_CONTROLLER_ID(0x0e6f, 0x0163),
     "PDP Deliverer of Truth"}, // PDP Legendary Collection: Deliverer of Truth
    {ControllerType_XBoxOneController, MAKE_CONTROLLER_ID(0x0e6f, 0x0164),
     "PDP Battlefield 1 Controller"}, // PDP Battlefield 1 Official Wired
                                      // Controller for Xbox One
    {ControllerType_XBoxOneController, MAKE_CONTROLLER_ID(0x0e6f, 0x0165),
     "PDP Titanfall 2 Controller"}, // PDP Titanfall 2 Official Wired Controller
                                    // for Xbox One
    {ControllerType_XBoxOneController, MAKE_CONTROLLER_ID(0x0e6f, 0x0166),
     "PDP Mass Effect: Andromeda Controller"}, // PDP Mass Effect: Andromeda
                                               // Official Wired Controller for
                                               // Xbox One
    {ControllerType_XBoxOneController, MAKE_CONTROLLER_ID(0x0e6f, 0x0167),
     "PDP Halo Wars 2 Face-Off Controller"}, // PDP Halo Wars 2 Official
                                             // Face-Off Wired Controller for
                                             // Xbox One
    {ControllerType_XBoxOneController, MAKE_CONTROLLER_ID(0x0e6f, 0x0205),
     "PDP Victrix Pro Fight Stick"}, // PDP Victrix Pro Fight Stick
    {ControllerType_XBoxOneController, MAKE_CONTROLLER_ID(0x0e6f, 0x0206),
     "PDP Mortal Kombat Controller"}, // PDP Mortal Kombat 25 Anniversary
                                      // Edition Stick (Xbox One)
    {ControllerType_XBoxOneController, MAKE_CONTROLLER_ID(0x0e6f, 0x0246),
     "PDP Xbox One Rock Candy"}, // PDP Rock Candy Wired Controller for Xbox One
    {ControllerType_XBoxOneController, MAKE_CONTROLLER_ID(0x0e6f, 0x0261),
     "PDP Xbox One Camo"}, // PDP Camo Wired Controller
    {ControllerType_XBoxOneController, MAKE_CONTROLLER_ID(0x0e6f, 0x0262),
     "PP Xbox One Controller"}, // PDP Wired Controller
    {ControllerType_XBoxOneController, MAKE_CONTROLLER_ID(0x0e6f, 0x02a0),
     "PDP Xbox One Midnight Blue"}, // PDP Wired Controller for Xbox One -
                                    // Midnight Blue
    {ControllerType_XBoxOneController, MAKE_CONTROLLER_ID(0x0e6f, 0x02a1),
     "PDP Xbox One Verdant Green"}, // PDP Wired Controller for Xbox One -
                                    // Verdant Green
    {ControllerType_XBoxOneController, MAKE_CONTROLLER_ID(0x0e6f, 0x02a2),
     "PDP Xbox One Crimson Red"}, // PDP Wired Controller for Xbox One - Crimson
                                  // Red
    {ControllerType_XBoxOneController, MAKE_CONTROLLER_ID(0x0e6f, 0x02a3),
     "PDP Xbox One Arctic White"}, // PDP Wired Controller for Xbox One - Arctic
                                   // White
    {ControllerType_XBoxOneController, MAKE_CONTROLLER_ID(0x0e6f, 0x02a4),
     "PDP Xbox One Phantom Black"}, // PDP Wired Controller for Xbox One -
                                    // Stealth Series | Phantom Black
    {ControllerType_XBoxOneController, MAKE_CONTROLLER_ID(0x0e6f, 0x02a5),
     "PDP Xbox One Ghost White"}, // PDP Wired Controller for Xbox One - Stealth
                                  // Series | Ghost White
    {ControllerType_XBoxOneController, MAKE_CONTROLLER_ID(0x0e6f, 0x02a6),
     "PDP Xbox One Revenant Blue"}, // PDP Wired Controller for Xbox One -
                                    // Stealth Series | Revenant Blue
    {ControllerType_XBoxOneController, MAKE_CONTROLLER_ID(0x0e6f, 0x02a7),
     "PDP Xbox One Raven Black"}, // PDP Wired Controller for Xbox One - Raven
                                  // Black
    {ControllerType_XBoxOneController, MAKE_CONTROLLER_ID(0x0e6f, 0x02a8),
     "PDP Xbox One Arctic White"}, // PDP Wired Controller for Xbox One - Arctic
                                   // White
    {ControllerType_XBoxOneController, MAKE_CONTROLLER_ID(0x0e6f, 0x02a9),
     "PDP Xbox One Midnight Blue"}, // PDP Wired Controller for Xbox One -
                                    // Midnight Blue
    {ControllerType_XBoxOneController, MAKE_CONTROLLER_ID(0x0e6f, 0x02aa),
     "PDP Xbox One Verdant Green"}, // PDP Wired Controller for Xbox One -
                                    // Verdant Green
    {ControllerType_XBoxOneController, MAKE_CONTROLLER_ID(0x0e6f, 0x02ab),
     "PDP Xbox One Crimson Red"}, // PDP Wired Controller for Xbox One - Crimson
                                  // Red
    {ControllerType_XBoxOneController, MAKE_CONTROLLER_ID(0x0e6f, 0x02ac),
     "PDP Xbox One Ember Orange"}, // PDP Wired Controller for Xbox One - Ember
                                   // Orange
    {ControllerType_XBoxOneController, MAKE_CONTROLLER_ID(0x0e6f, 0x02ad),
     "PDP Xbox One Phantom Black"}, // PDP Wired Controller for Xbox One -
                                    // Stealth Series | Phantom Black
    {ControllerType_XBoxOneController, MAKE_CONTROLLER_ID(0x0e6f, 0x02ae),
     "PDP Xbox One Ghost White"}, // PDP Wired Controller for Xbox One - Stealth
                                  // Series | Ghost White
    {ControllerType_XBoxOneController, MAKE_CONTROLLER_ID(0x0e6f, 0x02af),
     "PDP Xbox One Revenant Blue"}, // PDP Wired Controller for Xbox One -
                                    // Stealth Series | Revenant Blue
    {ControllerType_XBoxOneController, MAKE_CONTROLLER_ID(0x0e6f, 0x02b0),
     "PDP Xbox One Raven Black"}, // PDP Wired Controller for Xbox One - Raven
                                  // Black
    {ControllerType_XBoxOneController, MAKE_CONTROLLER_ID(0x0e6f, 0x02b1),
     "PDP Xbox One Arctic White"}, // PDP Wired Controller for Xbox One - Arctic
                                   // White
    {ControllerType_XBoxOneController, MAKE_CONTROLLER_ID(0x0e6f, 0x02b3),
     "PDP Xbox One Afterglow"}, // PDP Afterglow Prismatic Wired Controller
    {ControllerType_XBoxOneController, MAKE_CONTROLLER_ID(0x0e6f, 0x02b5),
     "PDP Xbox One GAMEware Controller"}, // PDP GAMEware Wired Controller Xbox
                                          // One
    {ControllerType_XBoxOneController, MAKE_CONTROLLER_ID(0x0e6f, 0x02b6),
     0}, // PDP One-Handed Joystick Adaptive Controller
    {ControllerType_XBoxOneController, MAKE_CONTROLLER_ID(0x0e6f, 0x02bd),
     "PDP Xbox One Royal Purple"}, // PDP Wired Controller for Xbox One - Royal
                                   // Purple
    {ControllerType_XBoxOneController, MAKE_CONTROLLER_ID(0x0e6f, 0x02be),
     "PDP Xbox One Raven Black"}, // PDP Deluxe Wired Controller for Xbox One -
                                  // Raven Black
    {ControllerType_XBoxOneController, MAKE_CONTROLLER_ID(0x0e6f, 0x02bf),
     "PDP Xbox One Midnight Blue"}, // PDP Deluxe Wired Controller for Xbox One
                                    // - Midnight Blue
    {ControllerType_XBoxOneController, MAKE_CONTROLLER_ID(0x0e6f, 0x02c0),
     "PDP Xbox One Phantom Black"}, // PDP Deluxe Wired Controller for Xbox One
                                    // - Stealth Series | Phantom Black
    {ControllerType_XBoxOneController, MAKE_CONTROLLER_ID(0x0e6f, 0x02c1),
     "PDP Xbox One Ghost White"}, // PDP Deluxe Wired Controller for Xbox One -
                                  // Stealth Series | Ghost White
    {ControllerType_XBoxOneController, MAKE_CONTROLLER_ID(0x0e6f, 0x02c2),
     "PDP Xbox One Revenant Blue"}, // PDP Deluxe Wired Controller for Xbox One
                                    // - Stealth Series | Revenant Blue
    {ControllerType_XBoxOneController, MAKE_CONTROLLER_ID(0x0e6f, 0x02c3),
     "PDP Xbox One Verdant Green"}, // PDP Deluxe Wired Controller for Xbox One
                                    // - Verdant Green
    {ControllerType_XBoxOneController, MAKE_CONTROLLER_ID(0x0e6f, 0x02c4),
     "PDP Xbox One Ember Orange"}, // PDP Deluxe Wired Controller for Xbox One -
                                   // Ember Orange
    {ControllerType_XBoxOneController, MAKE_CONTROLLER_ID(0x0e6f, 0x02c5),
     "PDP Xbox One Royal Purple"}, // PDP Deluxe Wired Controller for Xbox One -
                                   // Royal Purple
    {ControllerType_XBoxOneController, MAKE_CONTROLLER_ID(0x0e6f, 0x02c6),
     "PDP Xbox One Crimson Red"}, // PDP Deluxe Wired Controller for Xbox One -
                                  // Crimson Red
    {ControllerType_XBoxOneController, MAKE_CONTROLLER_ID(0x0e6f, 0x02c7),
     "PDP Xbox One Arctic White"}, // PDP Deluxe Wired Controller for Xbox One -
                                   // Arctic White
    {ControllerType_XBoxOneController, MAKE_CONTROLLER_ID(0x0e6f, 0x02c8),
     "PDP Kingdom Hearts Controller"}, // PDP Kingdom Hearts Wired Controller
    {ControllerType_XBoxOneController, MAKE_CONTROLLER_ID(0x0e6f, 0x02c9),
     "PDP Xbox One Phantasm Red"}, // PDP Deluxe Wired Controller for Xbox One -
                                   // Stealth Series | Phantasm Red
    {ControllerType_XBoxOneController, MAKE_CONTROLLER_ID(0x0e6f, 0x02ca),
     "PDP Xbox One Specter Violet"}, // PDP Deluxe Wired Controller for Xbox One
                                     // - Stealth Series | Specter Violet
    {ControllerType_XBoxOneController, MAKE_CONTROLLER_ID(0x0e6f, 0x02cb),
     "PDP Xbox One Specter Violet"}, // PDP Wired Controller for Xbox One -
                                     // Stealth Series | Specter Violet
    {ControllerType_XBoxOneController, MAKE_CONTROLLER_ID(0x0e6f, 0x02cd),
     "PDP Xbox One Blu-merang"}, // PDP Rock Candy Wired Controller for Xbox One
                                 // - Blu-merang
    {ControllerType_XBoxOneController, MAKE_CONTROLLER_ID(0x0e6f, 0x02ce),
     "PDP Xbox One Cranblast"}, // PDP Rock Candy Wired Controller for Xbox One
                                // - Cranblast
    {ControllerType_XBoxOneController, MAKE_CONTROLLER_ID(0x0e6f, 0x02cf),
     "PDP Xbox One Aqualime"}, // PDP Rock Candy Wired Controller for Xbox One -
                               // Aqualime
    {ControllerType_XBoxOneController, MAKE_CONTROLLER_ID(0x0e6f, 0x02d5),
     "PDP Xbox One Red Camo"}, // PDP Wired Controller for Xbox One - Red Camo
    {ControllerType_XBoxOneController, MAKE_CONTROLLER_ID(0x0e6f, 0x0346),
     "PDP Xbox One RC Gamepad"}, // PDP RC Gamepad for Xbox One
    {ControllerType_XBoxOneController, MAKE_CONTROLLER_ID(0x0e6f, 0x0446),
     "PDP Xbox One RC Gamepad"}, // PDP RC Gamepad for Xbox One
    {ControllerType_XBoxOneController, MAKE_CONTROLLER_ID(0x0e6f, 0x02da),
     "PDP Xbox Series X Afterglow"}, // PDP Xbox Series X Afterglow
    {ControllerType_XBoxOneController, MAKE_CONTROLLER_ID(0x0e6f, 0x02d6),
     "Victrix Gambit Tournament Controller"}, // Victrix Gambit Tournament
                                              // Controller
    {ControllerType_XBoxOneController, MAKE_CONTROLLER_ID(0x0e6f, 0x02d9),
     "PDP Xbox Series X Midnight Blue"}, // PDP Xbox Series X Midnight Blue
    {ControllerType_XBoxOneController, MAKE_CONTROLLER_ID(0x0f0d, 0x0063),
     0}, // Hori Real Arcade Pro Hayabusa (USA) Xbox One
    {ControllerType_XBoxOneController, MAKE_CONTROLLER_ID(0x0f0d, 0x0067),
     0}, // HORIPAD ONE
    {ControllerType_XBoxOneController, MAKE_CONTROLLER_ID(0x0f0d, 0x0078),
     0}, // Hori Real Arcade Pro V Kai Xbox One
    {ControllerType_XBoxOneController, MAKE_CONTROLLER_ID(0x0f0d, 0x00c5),
     0}, // HORI Fighting Commander
    {ControllerType_XBoxOneController, MAKE_CONTROLLER_ID(0x0f0d, 0x0150),
     0}, // HORI Fighting Commander OCTA for Xbox Series X
    {ControllerType_XBoxOneController, MAKE_CONTROLLER_ID(0x10f5, 0x7009),
     0}, // Turtle Beach Recon Controller
    {ControllerType_XBoxOneController, MAKE_CONTROLLER_ID(0x10f5, 0x7013),
     0}, // Turtle Beach REACT-R
    {ControllerType_XBoxOneController, MAKE_CONTROLLER_ID(0x1532, 0x0a00),
     0}, // Razer Atrox Arcade Stick
    {ControllerType_XBoxOneController, MAKE_CONTROLLER_ID(0x1532, 0x0a03),
     0}, // Razer Wildcat
    {ControllerType_XBoxOneController, MAKE_CONTROLLER_ID(0x1532, 0x0a14),
     0}, // Razer Wolverine Ultimate
    {ControllerType_XBoxOneController, MAKE_CONTROLLER_ID(0x1532, 0x0a15),
     0}, // Razer Wolverine Tournament Edition
    {ControllerType_XBoxOneController, MAKE_CONTROLLER_ID(0x20d6, 0x2001),
     "PowerA Xbox Series X Controller"}, // PowerA Xbox Series X EnWired
                                         // Controller - Black Inline
    {ControllerType_XBoxOneController, MAKE_CONTROLLER_ID(0x20d6, 0x2002),
     "PowerA Xbox Series X Controller"}, // PowerA Xbox Series X EnWired
                                         // Controller Gray/White Inline
    {ControllerType_XBoxOneController, MAKE_CONTROLLER_ID(0x20d6, 0x2003),
     "PowerA Xbox Series X Controller"}, // PowerA Xbox Series X EnWired
                                         // Controller Green Inline
    {ControllerType_XBoxOneController, MAKE_CONTROLLER_ID(0x20d6, 0x2004),
     "PowerA Xbox Series X Controller"}, // PowerA Xbox Series X EnWired
                                         // Controller Pink inline
    {ControllerType_XBoxOneController, MAKE_CONTROLLER_ID(0x20d6, 0x2005),
     "PowerA Xbox Series X Controller"}, // PowerA Xbox Series X Wired
                                         // Controller Core - Black
    {ControllerType_XBoxOneController, MAKE_CONTROLLER_ID(0x20d6, 0x2006),
     "PowerA Xbox Series X Controller"}, // PowerA Xbox Series X Wired
                                         // Controller Core - White
    {ControllerType_XBoxOneController, MAKE_CONTROLLER_ID(0x20d6, 0x2009),
     "PowerA Xbox Series X Controller"}, // PowerA Xbox Series X EnWired
                                         // Controller Red inline
    {ControllerType_XBoxOneController, MAKE_CONTROLLER_ID(0x20d6, 0x200a),
     "PowerA Xbox Series X Controller"}, // PowerA Xbox Series X EnWired
                                         // Controller Blue inline
    {ControllerType_XBoxOneController, MAKE_CONTROLLER_ID(0x20d6, 0x200b),
     "PowerA Xbox Series X Controller"}, // PowerA Xbox Series X EnWired
                                         // Controller Camo Metallic Red
    {ControllerType_XBoxOneController, MAKE_CONTROLLER_ID(0x20d6, 0x200c),
     "PowerA Xbox Series X Controller"}, // PowerA Xbox Series X EnWired
                                         // Controller Camo Metallic Blue
    {ControllerType_XBoxOneController, MAKE_CONTROLLER_ID(0x20d6, 0x200d),
     "PowerA Xbox Series X Controller"}, // PowerA Xbox Series X EnWired
                                         // Controller Seafoam Fade
    {ControllerType_XBoxOneController, MAKE_CONTROLLER_ID(0x20d6, 0x200e),
     "PowerA Xbox Series X Controller"}, // PowerA Xbox Series X EnWired
                                         // Controller Midnight Blue
    {ControllerType_XBoxOneController, MAKE_CONTROLLER_ID(0x20d6, 0x200f),
     "PowerA Xbox Series X Controller"}, // PowerA Xbox Series X EnWired Soldier
                                         // Green
    {ControllerType_XBoxOneController, MAKE_CONTROLLER_ID(0x20d6, 0x2011),
     "PowerA Xbox Series X Controller"}, // PowerA Xbox Series X EnWired -
                                         // Metallic Ice
    {ControllerType_XBoxOneController, MAKE_CONTROLLER_ID(0x20d6, 0x2012),
     "PowerA Xbox Series X Controller"}, // PowerA Xbox Series X Cuphead EnWired
                                         // Controller - Mugman
    {ControllerType_XBoxOneController, MAKE_CONTROLLER_ID(0x20d6, 0x2015),
     "PowerA Xbox Series X Controller"}, // PowerA Xbox Series X EnWired
                                         // Controller - Blue Hint
    {ControllerType_XBoxOneController, MAKE_CONTROLLER_ID(0x20d6, 0x2016),
     "PowerA Xbox Series X Controller"}, // PowerA Xbox Series X EnWired
                                         // Controller - Green Hint
    {ControllerType_XBoxOneController, MAKE_CONTROLLER_ID(0x20d6, 0x2017),
     "PowerA Xbox Series X Controller"}, // PowerA Xbox Series X EnWired
                                         // Cntroller - Arctic Camo
    {ControllerType_XBoxOneController, MAKE_CONTROLLER_ID(0x20d6, 0x2018),
     "PowerA Xbox Series X Controller"}, // PowerA Xbox Series X EnWired
                                         // Controller Arc Lightning
    {ControllerType_XBoxOneController, MAKE_CONTROLLER_ID(0x20d6, 0x2019),
     "PowerA Xbox Series X Controller"}, // PowerA Xbox Series X EnWired
                                         // Controller Royal Purple
    {ControllerType_XBoxOneController, MAKE_CONTROLLER_ID(0x20d6, 0x201a),
     "PowerA Xbox Series X Controller"}, // PowerA Xbox Series X EnWired
                                         // Controller Nebula
    {ControllerType_XBoxOneController, MAKE_CONTROLLER_ID(0x20d6, 0x4001),
     "PowerA Fusion Pro 2 Controller"}, // PowerA Fusion Pro 2 Wired Controller
                                        // (Xbox Series X style)
    {ControllerType_XBoxOneController, MAKE_CONTROLLER_ID(0x20d6, 0x4002),
     "PowerA Spectra Infinity Controller"}, // PowerA Spectra Infinity Wired
                                            // Controller (Xbox Series X style)
    {ControllerType_XBoxOneController, MAKE_CONTROLLER_ID(0x20d6, 0x890b),
     0}, // PowerA MOGA XP-Ultra Controller (Xbox Series X style)
    {ControllerType_XBoxOneController, MAKE_CONTROLLER_ID(0x24c6, 0x541a),
     0}, // PowerA Xbox One Mini Wired Controller
    {ControllerType_XBoxOneController, MAKE_CONTROLLER_ID(0x24c6, 0x542a),
     0}, // Xbox ONE spectra
    {ControllerType_XBoxOneController, MAKE_CONTROLLER_ID(0x24c6, 0x543a),
     "PowerA Xbox One Controller"}, // PowerA Xbox ONE liquid metal controller
    {ControllerType_XBoxOneController, MAKE_CONTROLLER_ID(0x24c6, 0x551a),
     0}, // PowerA FUSION Pro Controller
    {ControllerType_XBoxOneController, MAKE_CONTROLLER_ID(0x24c6, 0x561a),
     0}, // PowerA FUSION Controller
    {ControllerType_XBoxOneController, MAKE_CONTROLLER_ID(0x24c6, 0x581a),
     0}, // BDA XB1 Classic Controller
    {ControllerType_XBoxOneController, MAKE_CONTROLLER_ID(0x24c6, 0x591a),
     0}, // PowerA FUSION Pro Controller
    {ControllerType_XBoxOneController, MAKE_CONTROLLER_ID(0x24c6, 0x592a),
     0}, // BDA XB1 Spectra Pro
    {ControllerType_XBoxOneController, MAKE_CONTROLLER_ID(0x24c6, 0x791a),
     0}, // PowerA Fusion Fight Pad
    {ControllerType_XBoxOneController, MAKE_CONTROLLER_ID(0x2dc8, 0x2002),
     0}, // 8BitDo Ultimate Wired Controller for Xbox
    {ControllerType_XBoxOneController, MAKE_CONTROLLER_ID(0x2dc8, 0x3106),
     0}, // 8Bitdo Ultimate Wired Controller. Windows, Android, Switch.
    {ControllerType_XBoxOneController, MAKE_CONTROLLER_ID(0x2e24, 0x0652),
     0}, // Hyperkin Duke
    {ControllerType_XBoxOneController, MAKE_CONTROLLER_ID(0x2e24, 0x1618),
     0}, // Hyperkin Duke
    {ControllerType_XBoxOneController, MAKE_CONTROLLER_ID(0x2e24, 0x1688),
     0}, // Hyperkin X91
    {ControllerType_XBoxOneController, MAKE_CONTROLLER_ID(0x146b, 0x0611),
     0}, // Xbox Controller Mode for NACON Revolution 3

    // These have been added via Minidump for unrecognized Xinput controller
    // assert
    {ControllerType_XBox360Controller, MAKE_CONTROLLER_ID(0x0000, 0x0000),
     0}, // Unknown Controller
    {ControllerType_XBox360Controller, MAKE_CONTROLLER_ID(0x045e, 0x02a2),
     0}, // Unknown Controller - Microsoft VID
    {ControllerType_XBox360Controller, MAKE_CONTROLLER_ID(0x0e6f, 0x1414),
     0}, // Unknown Controller
    {ControllerType_XBox360Controller, MAKE_CONTROLLER_ID(0x0e6f, 0x0159),
     0}, // Unknown Controller
    {ControllerType_XBox360Controller, MAKE_CONTROLLER_ID(0x24c6, 0xfaff),
     0}, // Unknown Controller
    {ControllerType_XBox360Controller, MAKE_CONTROLLER_ID(0x0f0d, 0x006d),
     0}, // Unknown Controller
    {ControllerType_XBox360Controller, MAKE_CONTROLLER_ID(0x0f0d, 0x00a4),
     0}, // Unknown Controller
    {ControllerType_XBox360Controller, MAKE_CONTROLLER_ID(0x0079, 0x1832),
     0}, // Unknown Controller
    {ControllerType_XBox360Controller, MAKE_CONTROLLER_ID(0x0079, 0x187f),
     0}, // Unknown Controller
    {ControllerType_XBox360Controller, MAKE_CONTROLLER_ID(0x0079, 0x1883),
     0}, // Unknown Controller
    {ControllerType_XBox360Controller, MAKE_CONTROLLER_ID(0x03eb, 0xff01),
     0}, // Unknown Controller
    {ControllerType_XBox360Controller, MAKE_CONTROLLER_ID(0x0c12, 0x0ef8),
     0}, // Homemade fightstick based on brook pcb (with XInput driver??)
    {ControllerType_XBox360Controller, MAKE_CONTROLLER_ID(0x046d, 0x1000),
     0}, // Unknown Controller
    {ControllerType_XBox360Controller, MAKE_CONTROLLER_ID(0x1345, 0x6006),
     0}, // Unknown Controller

    {ControllerType_XBox360Controller, MAKE_CONTROLLER_ID(0x056e, 0x2012),
     0}, // Unknown Controller
    {ControllerType_XBox360Controller, MAKE_CONTROLLER_ID(0x146b, 0x0602),
     0}, // Unknown Controller
    {ControllerType_XBox360Controller, MAKE_CONTROLLER_ID(0x0f0d, 0x00ae),
     0}, // Unknown Controller
    {ControllerType_XBox360Controller, MAKE_CONTROLLER_ID(0x046d, 0x0401),
     0}, // logitech xinput
    {ControllerType_XBox360Controller, MAKE_CONTROLLER_ID(0x046d, 0x0301),
     0}, // logitech xinput
    {ControllerType_XBox360Controller, MAKE_CONTROLLER_ID(0x046d, 0xcaa3),
     0}, // logitech xinput
    {ControllerType_XBox360Controller, MAKE_CONTROLLER_ID(0x046d, 0xc261),
     0}, // logitech xinput
    {ControllerType_XBox360Controller, MAKE_CONTROLLER_ID(0x046d, 0x0291),
     0}, // logitech xinput
    {ControllerType_XBox360Controller, MAKE_CONTROLLER_ID(0x0079, 0x18d3),
     0}, // Unknown Controller
    {ControllerType_XBox360Controller, MAKE_CONTROLLER_ID(0x0f0d, 0x00b1),
     0}, // Unknown Controller
    {ControllerType_XBox360Controller, MAKE_CONTROLLER_ID(0x0001, 0x0001),
     0}, // Unknown Controller
    {ControllerType_XBox360Controller, MAKE_CONTROLLER_ID(0x0079, 0x188e),
     0}, // Unknown Controller
    {ControllerType_XBox360Controller, MAKE_CONTROLLER_ID(0x0079, 0x187c),
     0}, // Unknown Controller
    {ControllerType_XBox360Controller, MAKE_CONTROLLER_ID(0x0079, 0x189c),
     0}, // Unknown Controller
    {ControllerType_XBox360Controller, MAKE_CONTROLLER_ID(0x0079, 0x1874),
     0}, // Unknown Controller

    {ControllerType_XBoxOneController, MAKE_CONTROLLER_ID(0x2f24, 0x0050),
     0}, // Unknown Controller
    {ControllerType_XBoxOneController, MAKE_CONTROLLER_ID(0x2f24, 0x2e),
     0}, // Unknown Controller
    {ControllerType_XBoxOneController, MAKE_CONTROLLER_ID(0x2f24, 0x91),
     0}, // Unknown Controller
    {ControllerType_XBoxOneController, MAKE_CONTROLLER_ID(0x1430, 0x719),
     0}, // Unknown Controller
    {ControllerType_XBoxOneController, MAKE_CONTROLLER_ID(0xf0d, 0xed),
     0}, // Unknown Controller
    {ControllerType_XBoxOneController, MAKE_CONTROLLER_ID(0xf0d, 0xc0),
     0}, // Unknown Controller
    {ControllerType_XBoxOneController, MAKE_CONTROLLER_ID(0xe6f, 0x152),
     0}, // Unknown Controller
    {ControllerType_XBoxOneController, MAKE_CONTROLLER_ID(0xe6f, 0x2a7),
     0}, // Unknown Controller
    {ControllerType_XBoxOneController, MAKE_CONTROLLER_ID(0x46d, 0x1007),
     0}, // Unknown Controller
    {ControllerType_XBoxOneController, MAKE_CONTROLLER_ID(0xe6f, 0x2b8),
     0}, // Unknown Controller
    {ControllerType_XBoxOneController, MAKE_CONTROLLER_ID(0xe6f, 0x2a8),
     0}, // Unknown Controller
    {ControllerType_XBoxOneController, MAKE_CONTROLLER_ID(0x79, 0x18a1),
     0}, // Unknown Controller

    /* Added from Minidumps 10-9-19 */
    {ControllerType_XBoxOneController, MAKE_CONTROLLER_ID(0x0, 0x6686),
     0}, // Unknown Controller
    {ControllerType_XBoxOneController, MAKE_CONTROLLER_ID(0x11ff, 0x511),
     0}, // Unknown Controller
    {ControllerType_XBoxOneController, MAKE_CONTROLLER_ID(0x12ab, 0x304),
     0}, // Unknown Controller
    {ControllerType_XBoxOneController, MAKE_CONTROLLER_ID(0x1430, 0x291),
     0}, // Unknown Controller
    {ControllerType_XBoxOneController, MAKE_CONTROLLER_ID(0x1430, 0x2a9),
     0}, // Unknown Controller
    {ControllerType_XBoxOneController, MAKE_CONTROLLER_ID(0x1430, 0x70b),
     0}, // Unknown Controller
    {ControllerType_XBoxOneController, MAKE_CONTROLLER_ID(0x1bad, 0x28e),
     0}, // Unknown Controller
    {ControllerType_XBoxOneController, MAKE_CONTROLLER_ID(0x1bad, 0x2a0),
     0}, // Unknown Controller
    {ControllerType_XBoxOneController, MAKE_CONTROLLER_ID(0x1bad, 0x5500),
     0}, // Unknown Controller
    {ControllerType_XBoxOneController, MAKE_CONTROLLER_ID(0x20ab, 0x55ef),
     0}, // Unknown Controller
    {ControllerType_XBoxOneController, MAKE_CONTROLLER_ID(0x24c6, 0x5509),
     0}, // Unknown Controller
    {ControllerType_XBoxOneController, MAKE_CONTROLLER_ID(0x2516, 0x69),
     0}, // Unknown Controller
    {ControllerType_XBoxOneController, MAKE_CONTROLLER_ID(0x25b1, 0x360),
     0}, // Unknown Controller
    {ControllerType_XBoxOneController, MAKE_CONTROLLER_ID(0x2c22, 0x2203),
     0}, // Unknown Controller
    {ControllerType_XBoxOneController, MAKE_CONTROLLER_ID(0x2f24, 0x11),
     0}, // Unknown Controller
    {ControllerType_XBoxOneController, MAKE_CONTROLLER_ID(0x2f24, 0x53),
     0}, // Unknown Controller
    {ControllerType_XBoxOneController, MAKE_CONTROLLER_ID(0x2f24, 0xb7),
     0}, // Unknown Controller
    {ControllerType_XBoxOneController, MAKE_CONTROLLER_ID(0x46d, 0x0),
     0}, // Unknown Controller
    {ControllerType_XBoxOneController, MAKE_CONTROLLER_ID(0x46d, 0x1004),
     0}, // Unknown Controller
    {ControllerType_XBoxOneController, MAKE_CONTROLLER_ID(0x46d, 0x1008),
     0}, // Unknown Controller
    {ControllerType_XBoxOneController, MAKE_CONTROLLER_ID(0x46d, 0xf301),
     0}, // Unknown Controller
    {ControllerType_XBoxOneController, MAKE_CONTROLLER_ID(0x738, 0x2a0),
     0}, // Unknown Controller
    {ControllerType_XBoxOneController, MAKE_CONTROLLER_ID(0x738, 0x7263),
     0}, // Unknown Controller
    {ControllerType_XBoxOneController, MAKE_CONTROLLER_ID(0x738, 0xb738),
     0}, // Unknown Controller
    {ControllerType_XBoxOneController, MAKE_CONTROLLER_ID(0x738, 0xcb29),
     0}, // Unknown Controller
    {ControllerType_XBoxOneController, MAKE_CONTROLLER_ID(0x738, 0xf401),
     0}, // Unknown Controller
    {ControllerType_XBoxOneController, MAKE_CONTROLLER_ID(0x79, 0x18c2),
     0}, // Unknown Controller
    {ControllerType_XBoxOneController, MAKE_CONTROLLER_ID(0x79, 0x18c8),
     0}, // Unknown Controller
    {ControllerType_XBoxOneController, MAKE_CONTROLLER_ID(0x79, 0x18cf),
     0}, // Unknown Controller
    {ControllerType_XBoxOneController, MAKE_CONTROLLER_ID(0xc12, 0xe17),
     0}, // Unknown Controller
    {ControllerType_XBoxOneController, MAKE_CONTROLLER_ID(0xc12, 0xe1c),
     0}, // Unknown Controller
    {ControllerType_XBoxOneController, MAKE_CONTROLLER_ID(0xc12, 0xe22),
     0}, // Unknown Controller
    {ControllerType_XBoxOneController, MAKE_CONTROLLER_ID(0xc12, 0xe30),
     0}, // Unknown Controller
    {ControllerType_XBoxOneController, MAKE_CONTROLLER_ID(0xd2d2, 0xd2d2),
     0}, // Unknown Controller
    {ControllerType_XBoxOneController, MAKE_CONTROLLER_ID(0xd62, 0x9a1a),
     0}, // Unknown Controller
    {ControllerType_XBoxOneController, MAKE_CONTROLLER_ID(0xd62, 0x9a1b),
     0}, // Unknown Controller
    {ControllerType_XBoxOneController, MAKE_CONTROLLER_ID(0xe00, 0xe00),
     0}, // Unknown Controller
    {ControllerType_XBoxOneController, MAKE_CONTROLLER_ID(0xe6f, 0x12a),
     0}, // Unknown Controller
    {ControllerType_XBoxOneController, MAKE_CONTROLLER_ID(0xe6f, 0x2a1),
     0}, // Unknown Controller
    {ControllerType_XBoxOneController, MAKE_CONTROLLER_ID(0xe6f, 0x2a2),
     0}, // Unknown Controller
    {ControllerType_XBoxOneController, MAKE_CONTROLLER_ID(0xe6f, 0x2a5),
     0}, // Unknown Controller
    {ControllerType_XBoxOneController, MAKE_CONTROLLER_ID(0xe6f, 0x2b2),
     0}, // Unknown Controller
    {ControllerType_XBoxOneController, MAKE_CONTROLLER_ID(0xe6f, 0x2bd),
     0}, // Unknown Controller
    {ControllerType_XBoxOneController, MAKE_CONTROLLER_ID(0xe6f, 0x2bf),
     0}, // Unknown Controller
    {ControllerType_XBoxOneController, MAKE_CONTROLLER_ID(0xe6f, 0x2c0),
     0}, // Unknown Controller
    {ControllerType_XBoxOneController, MAKE_CONTROLLER_ID(0xe6f, 0x2c6),
     0}, // Unknown Controller
    {ControllerType_XBoxOneController, MAKE_CONTROLLER_ID(0xf0d, 0x97),
     0}, // Unknown Controller
    {ControllerType_XBoxOneController, MAKE_CONTROLLER_ID(0xf0d, 0xba),
     0}, // Unknown Controller
    {ControllerType_XBoxOneController, MAKE_CONTROLLER_ID(0xf0d, 0xd8),
     0}, // Unknown Controller
    {ControllerType_XBoxOneController, MAKE_CONTROLLER_ID(0xfff, 0x2a1),
     0}, // Unknown Controller
    {ControllerType_XBoxOneController, MAKE_CONTROLLER_ID(0x45e, 0x867),
     0}, // Unknown Controller
    // Added 12-17-2020
    {ControllerType_XBoxOneController, MAKE_CONTROLLER_ID(0x16d0, 0xf3f),
     0}, // Unknown Controller
    {ControllerType_XBoxOneController, MAKE_CONTROLLER_ID(0x2f24, 0x8f),
     0}, // Unknown Controller
    {ControllerType_XBoxOneController, MAKE_CONTROLLER_ID(0xe6f, 0xf501),
     0}, // Unknown Controller

    //{ MAKE_CONTROLLER_ID( 0x1949, 0x0402 ), /*android*/, 0 },
    // Unknown Controller

    {ControllerType_AppleController, MAKE_CONTROLLER_ID(0x05ac, 0x0001),
     0}, // MFI Extended Gamepad (generic entry for iOS/tvOS)
    {ControllerType_AppleController, MAKE_CONTROLLER_ID(0x05ac, 0x0002),
     0}, // MFI Standard Gamepad (generic entry for iOS/tvOS)

    {ControllerType_SwitchJoyConLeft, MAKE_CONTROLLER_ID(0x057e, 0x2006),
     0}, // Nintendo Switch Joy-Con (Left)
    {ControllerType_SwitchJoyConRight, MAKE_CONTROLLER_ID(0x057e, 0x2007),
     0}, // Nintendo Switch Joy-Con (Right)
    {ControllerType_SwitchJoyConPair, MAKE_CONTROLLER_ID(0x057e, 0x2008),
     0}, // Nintendo Switch Joy-Con (Left+Right Combined)

    // This same controller ID is spoofed by many 3rd-party Switch controllers.
    // The ones we currently know of are:
    // * Any 8bitdo controller with Switch support
    // * ORTZ Gaming Wireless Pro Controller
    // * ZhiXu Gamepad Wireless
    // * Sunwaytek Wireless Motion Controller for Nintendo Switch
    {ControllerType_SwitchProController, MAKE_CONTROLLER_ID(0x057e, 0x2009),
     0}, // Nintendo Switch Pro Controller

    //{ ControllerType_SwitchProController, MAKE_CONTROLLER_ID(0x057e, 0x2017),
    // 0 },        // Nintendo Online SNES Controller

    // { ControllerType_SwitchProController, MAKE_CONTROLLER_ID(0x057e, 0x2019),
    // 0 },        // Nintendo Online N64 Controller
    //
    // { ControllerType_SwitchProController, MAKE_CONTROLLER_ID(0x057e, 0x201e),
    // 0 },        // Nintendo Online SEGA Genesis Controller

    {ControllerType_SwitchInputOnlyController,
     MAKE_CONTROLLER_ID(0x0f0d, 0x00c1), 0}, // HORIPAD for Nintendo Switch
    {ControllerType_SwitchInputOnlyController,
     MAKE_CONTROLLER_ID(0x0f0d, 0x0092),
     0}, // HORI Pokken Tournament DX Pro Pad
    {ControllerType_SwitchProController, MAKE_CONTROLLER_ID(0x0f0d, 0x00f6),
     0}, // HORI Wireless Switch Pad
    // The HORIPAD S, which comes in multiple styles:
    // - NSW-108, classic GameCube controller
    // - NSW-244, Fighting Commander arcade pad
    // - NSW-278, Hori Pad Mini gamepad
    // - NSW-326, HORIPAD FPS for Nintendo Switch
    //
    // The first two, at least, shouldn't have their buttons remapped, and since
    // we can't tell which model we're actually using, we won't do any button
    // remapping for any of them.
    {ControllerType_XInputSwitchController, MAKE_CONTROLLER_ID(0x0f0d, 0x00dc),
     0}, // HORIPAD S - Looks like a Switch controller but uses the Xbox 360
         // controller protocol, there is also a version of this that looks
         // like a GameCube controller
    {ControllerType_SwitchInputOnlyController,
     MAKE_CONTROLLER_ID(0x0e6f, 0x0180),
     0}, // PDP Faceoff Wired Pro Controller for Nintendo Switch
    {ControllerType_SwitchInputOnlyController,
     MAKE_CONTROLLER_ID(0x0e6f, 0x0181),
     0}, // PDP Faceoff Deluxe Wired Pro Controller for Nintendo Switch
    {ControllerType_SwitchInputOnlyController,
     MAKE_CONTROLLER_ID(0x0e6f, 0x0184),
     0}, // PDP Faceoff Wired Deluxe+ Audio Controller
    {ControllerType_SwitchInputOnlyController,
     MAKE_CONTROLLER_ID(0x0e6f, 0x0185),
     0}, // PDP Wired Fight Pad Pro for Nintendo Switch
    {ControllerType_SwitchProController, MAKE_CONTROLLER_ID(0x0e6f, 0x0186),
     0}, // PDP Afterglow Wireless Switch Controller - working gyro. USB is
         // for charging only. Many later "Wireless" line devices w/ gyro
         // also use this vid/pid
    {ControllerType_SwitchInputOnlyController,
     MAKE_CONTROLLER_ID(0x0e6f, 0x0187), 0}, // PDP Rockcandy Wired Controller
    {ControllerType_SwitchInputOnlyController,
     MAKE_CONTROLLER_ID(0x0e6f, 0x0188),
     0}, // PDP Afterglow Wired Deluxe+ Audio Controller
    {ControllerType_SwitchInputOnlyController,
     MAKE_CONTROLLER_ID(0x0f0d, 0x00aa),
     0}, // HORI Real Arcade Pro V Hayabusa in Switch Mode
    {ControllerType_SwitchInputOnlyController,
     MAKE_CONTROLLER_ID(0x20d6, 0xa711),
     0}, // PowerA Wired Controller Plus/PowerA Wired Controller Nintendo
         // GameCube Style
    {ControllerType_SwitchInputOnlyController,
     MAKE_CONTROLLER_ID(0x20d6, 0xa712),
     0}, // PowerA Nintendo Switch Fusion Fight Pad
    {ControllerType_SwitchInputOnlyController,
     MAKE_CONTROLLER_ID(0x20d6, 0xa713), 0}, // PowerA Super Mario Controller
    {ControllerType_SwitchInputOnlyController,
     MAKE_CONTROLLER_ID(0x20d6, 0xa714),
     0}, // PowerA Nintendo Switch Spectra Controller
    {ControllerType_SwitchInputOnlyController,
     MAKE_CONTROLLER_ID(0x20d6, 0xa715),
     0}, // Power A Fusion Wireless Arcade Stick (USB Mode) Over BT is shows
         // up as 057e 2009
    {ControllerType_SwitchInputOnlyController,
     MAKE_CONTROLLER_ID(0x20d6, 0xa716),
     0}, // PowerA Nintendo Switch Fusion Pro Controller - USB requires
         // toggling switch on back of device
    {ControllerType_SwitchInputOnlyController,
     MAKE_CONTROLLER_ID(0x20d6, 0xa718),
     0}, // PowerA Nintendo Switch Nano Wired Controller

    // Valve products
    {ControllerType_MobileTouch, MAKE_CONTROLLER_ID(0x0000, 0x11fb),
     0}, // Streaming mobile touch virtual controls
    {ControllerType_SteamController, MAKE_CONTROLLER_ID(0x28de, 0x1101),
     0}, // Valve Legacy Steam Controller (CHELL)
    {ControllerType_SteamController, MAKE_CONTROLLER_ID(0x28de, 0x1102),
     0}, // Valve wired Steam Controller (D0G)
    {ControllerType_SteamController, MAKE_CONTROLLER_ID(0x28de, 0x1105),
     0}, // Valve Bluetooth Steam Controller (D0G)
    {ControllerType_SteamController, MAKE_CONTROLLER_ID(0x28de, 0x1106),
     0}, // Valve Bluetooth Steam Controller (D0G)
    {ControllerType_UnknownNonSteamController,
     MAKE_CONTROLLER_ID(0x28de, 0x11ff),
     "Steam Virtual Gamepad"}, // Steam virtual gamepad
    {ControllerType_SteamController, MAKE_CONTROLLER_ID(0x28de, 0x1142),
     0}, // Valve wireless Steam Controller
    {ControllerType_SteamControllerV2, MAKE_CONTROLLER_ID(0x28de, 0x1201),
     0}, // Valve wired Steam Controller (HEADCRAB)
    {ControllerType_SteamControllerV2, MAKE_CONTROLLER_ID(0x28de, 0x1202),
     0}, // Valve Bluetooth Steam Controller (HEADCRAB)
    {ControllerType_SteamControllerNeptune, MAKE_CONTROLLER_ID(0x28de, 0x1205),
     0}, // Valve Steam Deck Builtin Controller
};

static inline enum ControllerType GuessControllerType(int vendorId,
                                                      int productId) {
  uint32_t controllerId = MAKE_CONTROLLER_ID(vendorId, productId);

  for (uint32_t index = 0;
       index < sizeof(ControllerDescriptions) / sizeof(*ControllerDescriptions);
       index++) {
    const struct ControllerDescription *controllerDescription =
        ControllerDescriptions + index;
    if (controllerDescription->id == controllerId)
      return controllerDescription->type;
  }

  return ControllerType_Unknown;
}

#undef MAKE_CONTROLLER_ID

#endif /* CONTROLLERS_H */
