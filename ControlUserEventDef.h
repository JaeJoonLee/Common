#if !defined(_USEREVENTDEF_H_)
#define _USEREVENTDEF_H_

// 1 Byte Allignment
#pragma pack(push, 1)

#define USER_EVENT_EDITCHANGE		1
#define USER_EVENT_EDITFULL			2
#define USER_EVENT_EDITENTER		3
#define USER_EVENT_KILLFOCUS		4
#define USER_EVENT_TAB				5
#define USER_EVENT_SETFOCUS			6
#define USER_EVENT_DROPDOWN			7
#define USER_EVENT_LISTSELCHANGED	8
#define USER_EVENT_LISTCANCEL		9
#define USER_EVENT_SHOWLIST			10
#define USER_EVENT_HIDELIST			11
#define USER_EVENT_SELCHANGED		12
#define USER_EVENT_CODEERROR		13
#define USER_EVENT_DRAW				14
#define USER_EVENT_GETLINKINFO		15
#define USER_EVENT_KEYDOWN			16
#define USER_EVENT_KEYPRESS			17
#define USER_EVENT_KEYUP			18
#define USER_EVENT_CHANGE			19
#define USER_EVENT_HSCROLL			20
#define USER_EVENT_VSCROLL			21
#define USER_EVENT_LEFTCLICK		22
#define USER_EVENT_RIGHTCLICK		23
#define USER_EVENT_CAPTIONCHANGE	24
#define USER_EVENT_CHANGEPOS		25
#define USER_EVENT_USERACTION		26
#define USER_EVENT_SELCHANGE		27
#define USER_EVENT_SELSELECTED		28
#define USER_EVENT_CHANGECHECKSTATE	29

#pragma pack(pop)

#endif // !defined(_USEREVENTDEF_H_)
