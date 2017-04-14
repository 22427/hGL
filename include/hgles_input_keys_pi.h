#pragma once
#include <linux/input.h>
namespace hgles
{

#define BTN_MISC		0x100
#define BTN_0			0x100
#define BTN_1			0x101
#define BTN_2			0x102
#define BTN_3			0x103
#define BTN_4			0x104
#define BTN_5			0x105
#define BTN_6			0x106
#define BTN_7			0x107
#define BTN_8			0x108
#define BTN_9			0x109

#define BTN_MOUSE		0x110
#define BTN_LEFT		0x110
#define BTN_RIGHT		0x111
#define BTN_MIDDLE		0x112
#define BTN_SIDE		0x113
#define BTN_EXTRA		0x114
#define BTN_FORWARD		0x115
#define BTN_BACK		0x116
#define BTN_TASK		0x117

enum Button
{
	BUTTON_0   = BTN_0 & 0xFF,
	BUTTON_1   = BTN_1 & 0xFF,
	BUTTON_2   = BTN_2 & 0xFF,
	BUTTON_3   = BTN_3 & 0xFF,
	BUTTON_4   = BTN_4 & 0xFF,
	BUTTON_5   = BTN_5 & 0xFF,
	BUTTON_6   = BTN_6 & 0xFF,
	BUTTON_7   = BTN_7 & 0xFF,
	BUTTON_LEFT     = BTN_LEFT & 0xFF,
	BUTTON_RIGHT    = BTN_RIGHT& 0xFF,
	BUTTON_MIDDLE   = BTN_MIDDLE & 0xFF,
	BUTTON_LAST      = BTN_MIDDLE & 0xFF,
};
enum Key
{
	K_UNKNOWN       =KEY_UNKNOWN       ,
	K_SPACE         =KEY_SPACE           ,
	K_APOSTROPHE    =KEY_APOSTROPHE      /* ' */,
	K_COMMA         =KEY_COMMA           /* , */,
	K_MINUS         =KEY_MINUS           /* - */,
	K_PERIOD        =KEY_DOT             /* . */,
	K_SLASH         =KEY_SLASH           /* / */,
	K_0             =KEY_0               ,
	K_1             =KEY_1               ,
	K_2             =KEY_2               ,
	K_3             =KEY_3               ,
	K_4             =KEY_4               ,
	K_5             =KEY_5               ,
	K_6             =KEY_6               ,
	K_7             =KEY_7               ,
	K_8             =KEY_8               ,
	K_9             =KEY_9               ,
	K_SEMICOLON     =KEY_SEMICOLON       /* ; */,
	K_EQUAL         =KEY_EQUAL           /* = */,
	K_A             =KEY_A               ,
	K_B             =KEY_B               ,
	K_C             =KEY_C               ,
	K_D             =KEY_D               ,
	K_E             =KEY_E               ,
	K_F             =KEY_F               ,
	K_G             =KEY_G               ,
	K_H             =KEY_H               ,
	K_I             =KEY_I               ,
	K_J             =KEY_J               ,
	K_K             =KEY_K               ,
	K_L             =KEY_L               ,
	K_M             =KEY_M               ,
	K_N             =KEY_N               ,
	K_O             =KEY_O               ,
	K_P             =KEY_P               ,
	K_Q             =KEY_Q               ,
	K_R             =KEY_R               ,
	K_S             =KEY_S               ,
	K_T             =KEY_T               ,
	K_U             =KEY_U               ,
	K_V             =KEY_V               ,
	K_W             =KEY_W               ,
	K_X             =KEY_X               ,
	K_Y             =KEY_Y               ,
	K_Z             =KEY_Z               ,
	K_LEFT_BRACKET  =KEY_LEFTBRACE       /* [ */,
	K_BACKSLASH     =KEY_BACKSLASH       /* \ */,
	K_RIGHT_BRACKET =KEY_RIGHTBRACE      /* ] */,
	K_GRAVE_ACCENT  =KEY_GRAVE           /* ` */,
	K_WORLD_1       =K_UNKNOWN           /* non-US #1 */,
	K_WORLD_2       =K_UNKNOWN			 /* non-US #2 */,
	K_ESCAPE        =KEY_ESC             ,
	K_ENTER         =KEY_ENTER           ,
	K_TAB           =KEY_TAB             ,
	K_BACKSPACE     =KEY_BACKSPACE       ,
	K_INSERT        =KEY_INSERT          ,
	K_DELETE        =KEY_DELETE          ,
	K_RIGHT         =KEY_RIGHT           ,
	K_LEFT          =KEY_LEFT            ,
	K_DOWN          =KEY_DOWN            ,
	K_UP            =KEY_UP              ,
	K_PAGE_UP       =KEY_PAGEUP          ,
	K_PAGE_DOWN     =KEY_PAGEDOWN        ,
	K_HOME          =KEY_HOME            ,
	K_END           =KEY_END             ,
	K_CAPS_LOCK     =KEY_CAPSLOCK        ,
	K_SCROLL_LOCK   =KEY_SCROLLLOCK      ,
	K_NUM_LOCK      =KEY_NUMLOCK         ,
	K_PRINT_SCREEN  =KEY_PRINT           ,
	K_PAUSE         =KEY_PAUSE           ,
	K_F1            =KEY_F1              ,
	K_F2            =KEY_F2              ,
	K_F3            =KEY_F3              ,
	K_F4            =KEY_F4              ,
	K_F5            =KEY_F5              ,
	K_F6            =KEY_F6              ,
	K_F7            =KEY_F7              ,
	K_F8            =KEY_F8              ,
	K_F9            =KEY_F9              ,
	K_F10           =KEY_F10             ,
	K_F11           =KEY_F11             ,
	K_F12           =KEY_F12             ,
	K_F13           =KEY_F13             ,
	K_F14           =KEY_F14             ,
	K_F15           =KEY_F15             ,
	K_F16           =KEY_F16             ,
	K_F17           =KEY_F17             ,
	K_F18           =KEY_F18             ,
	K_F19           =KEY_F19             ,
	K_F20           =KEY_F20             ,
	K_F21           =KEY_F21             ,
	K_F22           =KEY_F22             ,
	K_F23           =KEY_F23             ,
	K_F24           =KEY_F24             ,
	K_F25           =KEY_UNKNOWN         ,
	K_KP_0          =KEY_KP0             ,
	K_KP_1          =KEY_KP1             ,
	K_KP_2          =KEY_KP2             ,
	K_KP_3          =KEY_KP3             ,
	K_KP_4          =KEY_KP4             ,
	K_KP_5          =KEY_KP5             ,
	K_KP_6          =KEY_KP6             ,
	K_KP_7          =KEY_KP7             ,
	K_KP_8          =KEY_KP8             ,
	K_KP_9          =KEY_KP9             ,
	K_KP_DECIMAL    =KEY_KPDOT           ,
	K_KP_DIVIDE     =KEY_KPSLASH         ,
	K_KP_MULTIPLY   =KEY_KPASTERISK      ,
	K_KP_SUBTRACT   =KEY_KPMINUS         ,
	K_KP_ADD        =KEY_KPPLUS          ,
	K_KP_ENTER      =KEY_KPENTER         ,
	K_KP_EQUAL      =KEY_KPEQUAL         ,
	K_LEFT_SHIFT    =KEY_LEFTSHIFT       ,
	K_LEFT_CONTROL  =KEY_LEFTCTRL        ,
	K_LEFT_ALT      =KEY_LEFTALT         ,
	K_LEFT_SUPER    =KEY_LEFTMETA        ,
	K_RIGHT_SHIFT   =KEY_RIGHTSHIFT      ,
	K_RIGHT_CONTROL =KEY_RIGHTCTRL       ,
	K_RIGHT_ALT     =KEY_RIGHTALT        ,
	K_RIGHT_SUPER   =KEY_RIGHTMETA       ,
	K_MENU          =KEY_MENU            ,
	K_LAST          =255
};
}

