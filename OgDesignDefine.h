#ifndef _OGDESIGNDEFINE_H_
#define _OGDESIGNDEFINE_H_


#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

//#define	 USE_DEF_CAPTION_LEN	1	
/*
#define GS						(BYTE)0x1D	// �������� ���� �ǹ�(Group Separator)
#define US						(BYTE)0x1F	// ������ ��Ҹ� �и��ϴ� ����(Unit Separator)
#define FS						(BYTE)0x1E	// ��Ʈ�� ������ �����ڷ� ��� (Field Separator)
#define PS						(BYTE)0x0D	// ������ KEY Item�� ������ �� �����ڷ� ���.
#define RS						(BYTE)0x0A  // ������ ���ڵ尡 ������ �� ROW�����ڷ� ���.
#define IS						(BYTE)0x7F	// Item�� �Է� ������ ������ �����ڷ� ���.

#define _TCH_US					US
#define _TCH_FS					FS
#define _TCH_PS					PS
#define _TCH_RS					RS
#define _TCH_IS					IS
#define _TCH_PERIOD				_T('.')					// (.)
#define _TCH_COMMA				_T(',')					// (,)

#define _COMM_GS				US
#define _COMM_FS				FS
#define _COMM_RS				RS
#define _COMM_IS				IS
#define _COMM_CS				PS
*/

#define _G_TCH_GS				(BYTE)0x1D	// �������� ���� �ǹ�(Group Separator)
#define _G_TCH_US				(BYTE)0x1F	// ������ ��Ҹ� �и��ϴ� ����(Unit Separator)
#define _G_TCH_FS				(BYTE)0x1E	// ��Ʈ�� ������ �����ڷ� ��� (Field Separator)
#define _G_TCH_PS				(BYTE)0x0D	// ������ KEY Item�� ������ �� �����ڷ� ���.
#define _G_TCH_RS				(BYTE)0x0A  // ������ ���ڵ尡 ������ �� ROW�����ڷ� ���.
#define _G_TCH_IS				(BYTE)0x7F	// Item�� �Է� ������ ������ �����ڷ� ���.
#define _TCH_PERIOD			_T('.')					// (.)
#define _TCH_COMMA			_T(',')					// (,)

#define _COMM_GS				(BYTE)0x1F	// ������ ��Ҹ� �и��ϴ� ����(Unit Separator)
#define _COMM_FS				(BYTE)0x1E	// ��Ʈ�� ������ �����ڷ� ��� (Field Separator)
#define _COMM_RS				(BYTE)0x0A  // ������ ���ڵ尡 ������ �� ROW�����ڷ� ���.
#define _COMM_IS				(BYTE)0x7F	// Item�� �Է� ������ ������ �����ڷ� ���.
#define _COMM_CS				(BYTE)0x0D	// ������ KEY Item�� ������ �� �����ڷ� ���.

#define	MEMO_SYMBOL_SIZE		8

// Designer���� ������ ������ OCX���� �����ϵ��� �˷��ִ� �޼���.
// OCX �Ǵ� Designer�� �ڽ��� Close�ɶ� ����� Window���� Close���θ� �˷��ִ� �޼���.
//UINT m_uNotifyControlMsg = ::RegisterWindowMessage("NOTIFY_CONTROL_MSG");
enum  NOTIFY_CONTROL_MSG { 
						DESIGNE_TO_CONTROL_CHANGE_NOTIFY =1,
						CONTROL_TO_DESIGNE_CHANGE_NOTIFY,	
						DESIGNE_TO_CONTROL_CLOSE_NOTIFY,	
						CONTROL_TO_DESIGNE_CLOSE_NOTIFY,
						GRID_CODEIMAGE_DROP_NOTIFY,	
						GRID_GETCORE_FROM_HANDLE,	
						GRID_CONTINUE_EDIT,	
						};
// Version
/*****************************************************/
// Version 2 : ITEM_LEN���̰��� 20�ڸ����� 30�ڸ��� ���� 
// Version 3 : m_pmapRecordInfo ����
// Version 4 : ParentColor Property�߰� 
// Version 5 : ����Ʈ����� Flag�߰�
// Version 6 : lMaskInfoUnit�߰� 
// Version 7 : m_byMultiMarketUse �߰�
// Version 8 : AutoOrderInfo, NextHeaderUse �߰�
// Version 9 : FixedRowCheck �߰�, CaptionTextArray�߰�
// Version 10 : 52527->52529���� (GX_IDS_CTRL_TEXTFIT->GX_IDS_CTRL_CBS_DROPDOWNLIST)
// Version 11 : �׸��� Row�������� ��Ʈ���� ���� 
// Version 12 : �׸��� RealItem  �߰�
/*****************************************************/
#define	DEF_VERSION					MAKELONG(12,1)


#define ITEM_LEN					30					// Item Name����
#define REAL_ITEM_LEN				20					// Real Item Name����
#define CAPTION_LEN					32					// Caption�ִ����
#define RECORD_NAME_LEN				16					// Record name �ִ����


#define	UNDEFINE_BKCR				-1
#define	MAX_SHOWHIDE_LEN			7
#define	DEF_MAX_DATACOUNT			20					// �ִ� ������ ��ȸ�Ǽ� 

// OgBase Class
#define	DEF_CTRL_SIZE				CSize(500, 400)	
#define	DEF_ROW_COUNT				2
#define	DEF_COLUMN_COUNT			5
#define	DEF_HIDDEN_ROW_COUNT		1
#define	DEF_HIDDEN_COLUMN_COUNT		1
#define	DEF_COLUMN_WIDHT			80
#define	DEF_ROW_HEIGHT				18						// Default Height Row
#define	DEF_TOOLTIP					0

// Grid Class
#define	DEF_HEADER_ROW_COUNT		1
#define	DEF_HEADER_COLUMN_COUNT		0
#define	DEF_FROZEN_ROW_COUNT		1
#define	DEF_FROZEN_COLUMN_COUNT		0
#define	DEF_SUBITEM_COUNT			1
#define	DEF_BLOCK_COUNT				0

#define	TABLE_CELLBORDER_COLORINDEX		4				// ���̺� �⺻����
#define	DEF_TABLE_LINE_COLORINDEX		6				// ���̺� ����������
#define	DEF_TOPUPDATE_CELL_COLORINDEX	72				// �׸��� TopUpDate�ڵ����� 

#define	DEF_ODD_COLORINDEX				72				// �׸��� Ȧ�� ����
#define	DEF_EVEN_COLORINDEX				73				// �׸��� ¦�� ����
#define	DEF_SELCR_INDEX					77				// �׸��� ���� �� ���� 
#define	DEF_CTRLBORDER_COLORINDEX		78				// �׸��� ������
#define	DEF_LINE_COLORINDEX				62				// �׸��� �⺻����(���ζ���)
#define	DEF_BACKGND_COLORINDEX			61				// �׸��� �޿�������
#define	DEF_HV_LINE_COLORINDEX			66				// �׸������HV����.
#define	DEF_HEADER_LEFT_COLORINDEX		67				// �׸����������(����)���� 

#define	DEF_BKCR_INDEX					70				// �׸��� Body����
#define	DEF_TXCR_INDEX					71				// �׸��� Body���ڻ�

#define GRID_CELLBUTTON_COLOR_INDEX		74				// �׸��� �� ��ư����.
#define GRID_MEMOCELL_COLOR_INDEX		94				// �޸�ǥ��(��) ����.
#define GRID_UP_COLOR_INDEX				88				// ��»� 
#define GRID_DOWN_COLOR_INDEX			89				// �϶��� 
#define GRID_FIXEDROW_LINECOLOR_INDEX	79				// Ʋ������ 

#define	DEF_FONTBOLD_INDEX				13				// ��Ʈ �ε���( ����ü 9 ���� )

// Base Item
#define	DEF_FONT_INDEX					2				// �⺻ ��Ʈ �ε���( ����ü 9 ���� )
#define	DEF_HALIGN						DT_RIGHT
#define	DEF_VALIGN						DT_VCENTER

// Grid Header 
#define	HEADER_FONT_INDEX				2
#define	HEADER_BKCR_INDEX				64				// �׸��� ��� ����
#define	HEADER_TXCR_INDEX				65				// �׸��� ��� ���ڻ�
#define HEADER_3DHILIGHT_INDEX			68				// �׸��� ��� ���̶���Ʈ��
#define HEADER_3DSHADOW_INDEX			69				// �׸��� ��� �������

#define	HEADER_HALIGN					DT_CENTER

// Grid & Table Item
#define	DEF_KEY_INDEX					0
#define	DEF_REAL_BKCR_INDEX				2				// �ڵ��������� ���� 
#define	DEF_REAL_TXCR_INDEX				71				// �׸��� Body���ڻ� 
#define	DEF_SPIN_STEP					1
//#define	DEF_BUTTON_COLORINDEX		71
#define	DEF_CELL_DATATYPE				9				// DT_STRING
#define	DEF_CELL_ATTRINDEX				-1
#define	DEF_CELL_ATTROFFSET				-1

// Table Special Color 
#define	TSC_CAPTION_BACK_INDEX			80				// ���̺� ĸ�� ����  
//#define	TSC_COLOR_START_INDEX		100
#define	TSC_OVER_BT_HIGH_CRINDEX		82				// ���ηѿ�����ư ���϶���Ʈ 
#define	TSC_OVER_BT_SHDW_CRINDEX		83				// ���ηѿ�����ư ������
// ȣ�� �׸��� ȭ�鿡�� ����ϴ� �� ���� 
#define	TSC_HOGA_BUYGRAPH_CRINDEX		141				// �ż� ����
#define	TSC_HOGA_SALEGRAPH_CRINDEX		151				// �ŵ� ����
#define	TSC_OVER_SALEORDER_CRINDEX		84				// ���ηѿ������ŵ�
#define	TSC_OVER_BUYORDER_CRINDEX		85				// ���ηѿ������ż�
#define	TSC_OVER_MID_CRINDEX			86				// ���ηѿ������߰����
#define	TSC_OVER_MIDLINE_CRINDEX		87				// ���ηѿ���������
//#define	TSC_MENUCELL_BACK_CRINDEX	22

// Fire Event(Script Event)
#define FE_REAL_BEFORE				0x0001	// �ǽð������� ����ó�� ��
#define FE_REAL_AFTER       	    0x0002	// �ǽð������� ����ó�� ��
#define FE_IMAGE_DRAG				0x0004	// IMAGE Drag Event
#define FE_IMAGE_DROP				0x0008	// IMAGE Drop Event
#define FE_EDIT_NOCLICK				0x0010	// Edit Cell No Click Event
#define FE_BODYROW_ZERO				0x0020	// �� ���� �׸���Body���� 0���Ѵ�.
#define FE_SELECTLIST_NOMOVE		0x0040	// ����Ʈ ���� ��忡�� �̵����� ��� 

//#define FE_ONERECORD_DATA			0x0040	// ����Row�����ο� �����ʹ� �ϳ��� ó�� 
//#define FE_ONECLICK_IGNORE		0x0040	// ���񿬰��� ����϶� DblClick �߻��� OneClick�̺�Ʈ �����Ѵ�. 
//#define FE_EDIT_DNG_TYPE1			0x0080	// Call ���Ϳ� Edit ��Ʈ�ѿ� 
//#define FE_REALDATA_FILTER		0x0100	// RealData Filter Event
	
//#define FE_CELL_CLICK				0x0010
//#define FE_CELL_SIZING			0x0020	// Tail�� ��Ʈ�ѿ� �̺�Ʈ�� �˷��ֱ� ����.
//#define FE_EDIT_CHANGE			0x0040	// Code Edit Full Event
//#define FE_SPINEDITT_CHANGE		0x0080	// Spin Edit Change
//#define FE_CELL_ENTER				0x0100	// Cell Enter Event
//#define FE_PRESS_DIRECTIONKEY		0x0200	// ����Ű�� ���� ���.
//#define FE_ATM_EVENT				0x0800	// ATM Event
//#define FE_AUTORUN_REAL			0x0800	// AutoRealMode
//#define FE_REALDATA_FILTER		0x1000	// RealData Filter Event
//#define FE_RECV_BEFORE			0x2000	//	
//#define FE_RECV_AFTER             0x4000


// ���� ������ ��� ����.
#define	FIRE_LINKINFO_NONE			0
#define	FIRE_LINKINFO_DBCLICK		1
#define	FIRE_LINKINFO_ONECLICK		2


// Base Bool Bit Info
#define BASE_BBIT_USE_FORMULA		0x00000001
#define BASE_BBIT_USE_CELL_DATACNVT	0x00000002
#define BASE_BBIT_USE_COL_DATACNVT	0x00000004
#define BASE_BBIT_USE_SELECTCOLOR	0x00000008
#define BASE_BBIT_USE_CODELINK		0x00000010
#define BASE_BBIT_USE_ORDERLINK		0x00000020
// --> [Edit]  �Ȱ�ȯ 2010/11/20 // �ڵ����ݸ���ũ�߰�
//#define BASE_BBIT_USE_NUMBERCOL		0x00000040
#define BASE_BBIT_USE_AUTOPRICE		0x00000040		// �ڵ����ݸ���ŷ �� ���翩��
// <-- [Edit]  �Ȱ�ȯ 2010/11/20
#define BASE_BBIT_USE_IMAGEBTN		0x00000080
#define BASE_BBIT_USE_NEXTBTN		0x00000100
#define BASE_BBIT_USE_PREBTN		0x00000200
#define BASE_BBIT_USE_HCHARTBONG	0x00000400		// ���� ��. 
#define BASE_BBIT_USE_VCHARTBONG	0x00000800		// ���� ��.
#define BASE_BBIT_USE_KEY			0x00001000		// MainKey����ϴ� �÷��� ����.
#define BASE_BBIT_USE_SUBKEY		0x00002000		// SubKey����ϴ� �÷��� ����.
#define BASE_BBIT_USE_TOOLTIP		0x00004000		// Tooltip��� �ϴ� �÷� ����. 
#define BASE_BBIT_USE_CELLTIP		0x00008000		// Celltip��� �ϴ� �÷� ����. 
#define BASE_BBIT_USE_AMOUNTGRAPH	0x00010000		// ȣ�� ���̺��� �ܷ� �׷����� ����ϴ����� ����.
#define BASE_BBIT_MMOVE_OVERCHECK	0x00020000		// ���̺��� OverCell ǥ�ø� ���ؼ� ���콺 üũ�� �ʿ������� ����.
#define BASE_BBIT_USE_CODEDRAG		0x00040000		// CodeDrag ��� �ϴ� �÷� ����. 
#define BASE_BBIT_USE_MEMO			0x00080000		// Memo��� �ϴ� �÷� ����. 
#define BASE_BBIT_USE_CELLREF		0x00100000		// ������� �ϴ� �÷� ����. 
#define BASE_BBIT_MMOVE_EPSCHECK	0x00200000		// ȣ�� ���̺��� �� ������ ���ؼ� ���콺 üũ�� �ʿ������� ����.
#define BASE_BBIT_USE_THIRDKEY		0x00400000		// ThirdKey����ϴ� �÷��� ����.
#define BASE_BBIT_NOUSE_HOGAPRICE_FRAME	0x00800000	// ȣ�����ݿ� ���簡 �ܰ��� ǥ������ 
#define BASE_BBIT_NOUSE_HOGAPRICE	0x01000000		// ȣ�� ���̺� ���簡ǥ������. 
#define BASE_BBIT_USE_REG_DATACNVT	0x02000000		// Register Cell. 
#define BASE_BBIT_MULTIREC_USE		0x04000000		// ���� ���ڵ带 ����ϴ� ��� 
#define BASE_BBIT_MULTIMARKET_USE	0x08000000		// ���߽��� ����

//#define BASE_BBIT_USE_DELAYTIMER	0x00400000		// �ǽð� Delay Timer ���.
//#define BASE_BBIT_IS_SPECIALHOGA	0x00100000		// ȣ�� ���̺� Ư���� �׸��� ó���� �ִ� ��� True..
//#define BASE_BBIT_USE_BOTTOM_TAIL	0x10000000		// �ϴ� �հ��� 
//#define BASE_BBIT_USE_TOP_TAIL	0x20000000		// ��� �հ��� 

// Grid Bool Bit Info
#define BBIT_USE_SCLDWRQST			0x00000001				// SCROLL ACTION
#define BBIT_USE_BLOCKCOLOR			0x00000002				// Grid Block Color ��� ����.
#define BBIT_USE_VIRTUAL_STEP1		0x00000004				// Column ��Ÿ�ϰ� Cell ��Ÿ���� �и�.
#define BBIT_USE_VIRTUAL_STEP2		0x00000008				// ��Ÿ���� �������� �ʰ� ���� ����Ÿ�� �״�� ����(��Ʈ, �÷� �̵� ...�� �ȵ�).
#define BBIT_USE_3DHEADER			0x00000010				// Grid 3D Header ��� ����.
#define BBIT_USE_SAMEKEY			0x00000020				// MainKey �ߺ� ����.
#define BBIT_USE_SAMESUBKEY			0x00000040				// SubKey �ߺ� ����.
#define BBIT_USE_HEADERMOVE			0x00000080				// Grid ��� �̵� ��� ����.
#define BBIT_USE_SAVE_COLSIZE		0x00000100				// Grid �÷� ������ ���� ���� ����.
#define BBIT_USE_ROUNDHEADER		0x00000200				// Round Header
#define BBIT_USE_SAMETHIRDKEY		0x00000400				// ThirdKey �ߺ� ����.


// Grid Bool Bit Info
//#define TBL_BBIT_IS_HOGATABLE	0x0001
//#define TBL_BBIT_USE_HOGASELECT	0x0002
//#define TBL_BBIT_USE_VIRTUAL_STEP1    0x0004


/*----------------------------------------------*/
// �������� ���ڿ� �ε����� ����� ���� �ε���.
/*----------------------------------------------*/
// �Ｚ�������� User Link�� ������� �ʴ´�.
// ����ȭ���� ��ﶧ �Ѱ��� ������ ����Ѵ�.
#define USER_LINKTAG_INDEX			1
/*----------------------------------------------*/

// TableLink Item
#define	DEF_LINKROW					0
#define	DEF_LINKCOL					0

// Mask
#define	DEF_MASK_PLACES				0	
#define	IGNORE_MASK_PLACES			15	// 15�� ���� �Ҽ��� ���� ó���� ���Ѵ�.
#define	DEF_MASK_BITINFO			0
#define	MAX_FIX_LEN					4	// Prefix. Postfix�� �ִ� ����.

#define MBS_COMMA				0x00000001	// �޸����.
#define MBS_ZERONOTDSP          0x00000002	// 0ǥ�þ���.
#define MBS_SIGNNOT				0x00000004	// ��ȣ ǥ�� ����.
#define MBS_SIGNMINUS           0x00000008	// ��ȣ (-) �� ǥ��.
#define MBS_SIGNALL             0x00000010	// ��ȣ (-, +) �׻� ǥ��.
#define MBS_PREFIX				0x00000020	// Prefix ���.
#define MBS_POSTFIX				0x00000040	// Postfix ���.
#define MBS_ZERO_TRIMLEFT		0x00000080	// �տ� 0����.
//--->	
// ���� �߿��� �ִ� 1���� �����Ͽ� ���(Or) ...���� ������ ���� ���������� ����.
// ��Ʈ�� �Ұ� �ƴ����� ���°��� ���.
//#define MBS_NUMUNIT_10		0x00000100	// ���� ���� 10		: ������ ����Ÿ�� ���� ���ڸ� ����.
//#define MBS_NUMUNIT_100		0x00000200	// ���� ���� 100	: ������ ����Ÿ�� ���� ���ڸ� ����.
//#define MBS_NUMUNIT_1000		0x00000400	// ���� ���� 1000	: ������ ����Ÿ�� ���� ���ڸ� ����.
//<--- 
#define MBS_MAKE_ZEROPLACES		0x00000800	// �Ҽ������� �ڸ��� ó���� �����ÿ� ������Ÿ�� �Ҽ����� ������ ��å.
											// (ex) �Ҽ������� �ڸ��� 2�ΰ�� �Է� ����Ÿ�� 116�϶�.
											// True : 116.00, False : 1.16

#define MBS_ROUND				0x00001000	// �ݿø�.
#define MBS_PARENTHESES			0x00002000	// ��ȣ ���.
#define MBS_REMAIN_LASTZERO		0x00004000	// MBS_ZERO_TRIMLEFT�� ���� ����찡 0�϶� ������ 0�� ���濩��.
#define MBS_POINT_NODSP			0x00008000	// .���� �� ǥ�� ���ϱ�
#define MBS_NUM_CHANGE			0x00010000	// ������ ���������� ��ȯ 
#define MBS_NUM_CHAR_K			0x00020000	// ǥ�ÿ��� ������ �ڵ� 1000���� �����  K ���ڿ� �����̱� 


enum DxFormatIndex			//Mask Format Index
{
	dxFmt_Default = 0,		//	Default
	dxFmt_Num,				// 	Numeric
	dxFmt_HHMMSS,			// 	HH:MM:SS
	dxFmt_HHMM,				// 	HH:MM
	dxFmt_MMSS,				// 	MM:SS
	dxFmt_YYYYMMDD,			// 	YYYY/MM/DD
	dxFmt_YYYYMM,			// 	YYYY/MM
	dxFmt_YYMM,				// 	YY/MM
	dxFmt_YYMMDD,			// 	YY/MM/DD
	dxFmt_MMDD,				// 	MM/DD
	dxFmt_ACC,				//	Account(123-12-12345)
	dxFmt_DDHHMM,			// 	DD/HH:MM
	dxFmt_MMDDHHMM,			// 	MM/DD HH:MM
	dxFmt_YYMMDDHHMM,		// 	YY/MM/DD HH:MM
	dxFmt_YYYYMMDD_YYYYMMDD,// 	YYYY/MM/DD~YYYY/MM/DD
	dxFmt_MASK_FORMAT,		//  Mask Format
	dxFmt_USER_FORMAT,		//  User Format
	dxFmt_SYMBOLNAME,		// 	CodeHelpDll�� ���ؼ� �ɺ� �ڵ忡 �ش��Ѵ� �ɺ����� ��´�.
	dxFmt_POSTNUM,          //  �����ȣ
	dxFmt_TEL_NUM,			// 	��ȭ��ȣ (02-1234-****)
	dxFmt_ADDSTRING,		//  ��Ʈ���� ÷�� ���̱�
//	dxFmt_TextTrim,			//  ������ ���Ž� �¿� Trim
//	dxFmt_CAPTION_TEXT,		// 	ĸ�ǹ��ڿ�
	dxFmt_DecimalToString,  // (�ؿ�)Decimal long data -> string 
	dxFmt_LogToString,	    // (�ؿ�)log long data -> string 
	dxFmt_GLToSpotString,	// (�ؿ�)������ GL �����͸� ������ ����Ͽ� ǥ���Ѵ�( YEN, SWISS... ��ȭ�� ���� )
	dxFmt_SYSDATE,			//	DB ����Ͻú��� (2004/10/10 09:10:10)
	dxFmt_SYSTIMESTEMP,		//	DB ����Ͻú���.1/1000��(2004/10/10 09:10:10.999)
};

// Tail Grid Type Def
#define TG_NOTUSE				0x00	// �հ��� �̻��
#define TG_BOTTOM				0x01	// �ϴ� �հ���(���� �׸���) ,���� �հ���(���� �׸���)  
#define TG_TOP					0x02	// ��� �հ���(���� �׸���) ,���� �հ���(���� �׸���) 

// Cell Border
#define CBDR_LEFT				0x0001
#define CBDR_RIGHT			    0x0002
#define CBDR_TOP				0x0004
#define CBDR_BOTTOM				0x0008

// Popup Menu 
#define PM_CTRL_DEF				0x0001		// ��Ʈ�ѱ⺻
#define PM_COL_SETUP			0x0002		// �÷� ����(�׸�����)
#define PM_HOAG_FONT_CHANGE		0x0004		// ȣ����Ʈ ����
#define PM_MULTI_COL_SORT		0x0008		// �����÷���Ʈ 
#define PM_USER_MENU_SETUP		0x0010		// ����������޴����
#define PM_SCR_INTEREST			0x0020		// ����ȭ�� �˾��� 
#define PM_BATCH_INTEREST		0x0040		// �����ϰ���� 
#define PM_USER_EDIT			0x0080		// ����� ���� (���� �߰������� �޴�)
#define PM_HOGA_ORDER			0x0100		// �ŵ�/�ż�/�������

//#define PM_EXCEL_EDIT			0x0010		// �÷� ������ ����������  
//#define PM_LINK_SCR			0x0080		// ����ȭ������
//#define PM_INIT_SIZE			0x0100		// ó�����̷�


// Additional Request
//#define AR_PRICE_STATE				0x0001	// ���ݺ� ����(��ü��,�ܰ�,������,�ֹ����ð���)
//#define AR_ORDER_CONCLUSION			0x0002	// ��ü��/ü�� ����Ÿ �䱸.
//#define AR_STOCK_STOPLOSS			0x0004	// �ֽ� Stoploss
//#define AR_STOCK_ORDER_STOPLOSS		0x0008	// �ֽ� �ֹ� Stoploss
//#define AR_FUTURE_STOPLOSS			0x0010	// ���� Stoploss
//#define AR_FUTURE_ORDER_STOPLOSS	0x0020	// ���� �ֹ� Stoploss

// ȣ���ֹ� ����ǥ�� �÷��� HO_TABLE_ORDERDATA
#define DISP_ORDER_SELECT	0x00000001 	// ���ð���
#define DISP_ORDER_WATCH	0x00000002 	// ���ð���
#define DISP_ORDER_JANGO	0x00000004 	// �ܰ�
#define DISP_ORDER_MICHE	0x00000008 	// ��ü��

// Structure Size
#define LEN_ITEMBITS					sizeof(ITEMBITS)
#define LEN_GRIDBITS					sizeof(GRIDBITS)
#define LEN_TABLEBITS					sizeof(TABLEBITS)
#ifdef FIXLEN_USE
#define LEN_TRANBITS					sizeof(TRANBITS)
#endif
#define LEN_BASEBITS					sizeof(BASEBITS)
#define LEN_INITINFO					sizeof(INITINFO)
#define LEN_OGBASEITEM					sizeof(OGBASEITEM)
#define LEN_GRIDHEADER					sizeof(GRIDHEADER)
#define LEN_GRIDHEADERINFO(cnt)			sizeof(DWORD) + sizeof(short) + (cnt * LEN_GRIDHEADER)
#define LEN_GRIDBODY					sizeof(GRIDBODY)
#define LEN_GRIDBODYINFO(subcnt,cnt)	sizeof(DWORD) + (sizeof(short) * 2) + ((subcnt* cnt) * LEN_GRIDBODY)
#define LEN_TABLECELL					sizeof(TABLECELL)
#define LEN_TABLECELLINFO(cnt)			sizeof(DWORD) + sizeof(short) + (cnt * LEN_TABLECELL)
#define LEN_CELLLINK					sizeof(CELLLINK)
#define LEN_CELLLINKINFO(cnt)			sizeof(DWORD) + sizeof(short) + (cnt * LEN_CELLLINK)
#define LEN_ITEMSIZE					sizeof(ITEMSIZE)
#define LEN_ITEMSIZEINFO(cnt)			sizeof(DWORD) + sizeof(short) + (cnt * LEN_ITEMSIZE)
#define LEN_CELLRANGE					sizeof(CELLRANGE)
#define LEN_CELLRANGEINFO(cnt)			sizeof(DWORD) + sizeof(short) + (cnt * LEN_CELLRANGE)
#define LEN_MASKINFO					sizeof(MASKINFO)
#define LEN_REFERINFO					sizeof(REFERINFO)
#define LEN_GRIDLINE					sizeof(GRIDLINE)
#define LEN_TBLBORDER					sizeof(TBLBORDER)
#define LEN_BORDERINFO					sizeof(BORDERINFO)
#define LEN_RECITEM						sizeof(RECITEM)
#define LEN_REALCONBITS					sizeof(REALCONBITS)
#define LEN_REALCONITEM					sizeof(REALCONITEM)
#define LEN_RECTYPEBITS					sizeof(RECTYPEBITS)
#define LEN_REALRECTYPE					sizeof(REALRECTYPE)
#define LEN_REALCONINFO(reccnt, cnt)	sizeof(DWORD) + sizeof(BYTE) + sizeof(BYTE) + (reccnt * LEN_REALRECTYPE) + (cnt * LEN_REALCONITEM)
#define LEN_NEWREFERBITS				sizeof(NEWREFERBITS)
#define LEN_NEWREFERCON					sizeof(NEWREFERCON)
#define LEN_NEWREFERTYPE(cnt)			(ITEM_LEN+1) + (sizeof(BYTE)*2) + (cnt * LEN_NEWREFERCON) + sizeof(long)

#define LEN_HOGAORDER					sizeof(HOGAORDER)
#define LEN_ORDERSRC					sizeof(ORDERSRC)
#define LEN_USERCELL					sizeof(USERCELL)
#define LEN_USERCELLINFO(cnt)			sizeof(DWORD) + sizeof(short)+ (2*sizeof(int)) + (cnt * LEN_USERCELL)
#define LEN_USERCELL_POS				sizeof(DWORD) + sizeof(short)+ (2*sizeof(int))


//////////////////////////////////////////////////////
// ȣ�� �ֹ� ����.
#define	ORDER_NO_LEN					6

#define	HOGA_ORDER_TYPE_SALE			1		//�ŵ��ֹ�.
#define	HOGA_ORDER_TYPE_BUY				2		//�ż��ֹ�.
#define	HOGA_ORDER_TYPE_CORRECT			3		//�����ֹ�.
#define	HOGA_ORDER_TYPE_CANCEL			4		//����ֹ�.
#define	HOGA_TRADE_TYPE_NORMAL			0		//����.

#define	HOGA_TRADE_TYPE_MARKET			3		//���尡.
#define	HOGA_TRADE_TYPE_CONDITION		5		//���Ǻ�������.

// Ocx Control Type
enum DXOcxType
{
	dxHGrid,
	dxVGrid,
	dxTable,
	dxDefault
};

// virtual Mode
enum DXVirtualMode
{
	dxVMNone,
	dxVMStep2,			// ������ 
	dxVMStep1,
};

// Grid Data Type
enum DXGridDataType
{
	dxGDTTopInsert,			//(0)�ð��뺰(��, ��)������ ���� 
	dxGDTTopUpdate,			//(1)�Ϻ� ������ ���� 
	dxGDTUpdate,			//(2)�ü�ǥ������ ����(�����������Ұ�)
	dxGDTPortfolio,			//(3)����������(�����������)
	dxGDTRolling,			//(4)Rolling ������ ���� 
	dxGDTCircular,			//(5)��ȯ ������ ���� 
	dxGDTAppend,			//(6)�ü�ǥ Append ������ ����
	dxGDT_InFixedKey,		//(7)����Ű�� ������ ���̺�����(�ǽð���Ͻ� ����� Ű�� �ٹ��̷� ó���Ǿ� �ִ°��)
	dxGDT_InVariableKey,	//(8)����Ű�� ������ ���̺�����(�ǽð���Ͻ� ����� Ű�� ���ŵ����Ϳ� ���� ó���Ǿ� �ִ°��)
	
	dxGDTRealCondition,		//(9)�ǽð��ܰ� ����
	dxGDTOrderConclusion,	//(10)�ǽð���ü�� ����
	dxGDTVertInvestor=20,	//(20)������ ����������
	dxGDTHerzInvestor,		//(21)������ ����������
	dxGDTVH_Spread,			//(22)���μ��� ������������  
	dxGDTVH_Matrix,			//(23)���μ��� �������  
	dxGDTVH_VertData,		//(24) ���̺��� ���� ������ ǥ��
	dxGDTVH_HerzData,		//(25) ���̺��� ���� ������ ǥ��

#if FALSE
	/*---------------------------*/
	// �����Ѵ�.
	dxGDTTopUpdateInsert,	//�Ϻ� ������ ���� 
	dxGDTMemoryData,	//�Է� ��ȸ �޸� ������.
	dxGDTFixPortfolio,	//Fixed ����������.
	dxGDTExpPortfolio,	//Expand ����������.
	dxGDTSymmetry,		//��Ī��.
	dxGDTInvestor,		//������ Type
	dxGDNewsTitle,      //���� Ÿ��Ʋ.
	dxGDTNewsContent,   //���� ����.
	/*---------------------------*/
#endif
};

// Grid Special Content
enum DXGridSpecialContent
{
	dxSCNotUse,			// ������. 
	dxSCInvestor,		// ������.
	dxSCIntraKeyUpdate,	// �ð��뺰 Ű�и��� �׻� TopUpdate
	dxSCIntraKeyInsert,	// �ð��뺰 Ű�и��� �׻� TopInsert
	dxReverse,			// ���ŵ����� ���� ǥ��

	/*---------------------------*/
//	// �����Ѵ�.
//	dxSCPowerNews,		// �Ŀ� ����.
//	dxSCMultiTrade,		// ��Ƽ �ŷ���(��������) 
//	dxSCNewsTitle,      // ����/��Ȳ Ÿ��Ʋ.
//	dxSCSpecialNews,    // ����� ȭ��. 
	/*---------------------------*/
};

// Option Calculation Cell
// Max 5bit = 30���� ���� ->6bit = 60����.
enum DXOpCalcCell
{
	dxOPNone,				//[ 0] ������
	dxOPTimeCol,			//[ 1] �ð��÷� ����
	dxOPStart,				//[ 2] �ð�
	dxOPHigh,				//[ 3] ��
	dxOPLow,				//[ 4] ����
	dxOPEnd,				//[ 5] (���簡)����
	dxOPBasis,				//[ 6] ���ذ�(��������)
	dxOPMaxPrice,			//[ 7] ���Ѱ�
	dxOPMinPrice,			//[ 8] ���Ѱ�
	dxOPTheory,				//[ 9] OP�̷а�
	dxOPDelta,				//[10] OP��Ÿ
	dxOPGamma,				//[11] OP����
	dxOPTheta,				//[12] OP��Ÿ
	dxOPVega,				//[13] OP����
	dxOPRho,				//[14] OP��
	dxOPExpPayoff,			//[15] OP�������
	dxOPTheoryPayoff,		//[16] OP�̷м���
	dxOPEvalPayoff,			//[17] OP�򰡼���
	dxOPIV,					//[18] OP���������� �÷�
	dxOPTimeVal,			//[19] OP�ð���ġ �÷�
	dxOPIVVaule,			//[20] OP������ġ �÷�
	dxOPDiffRate,			//[21] OP ������
	dxOpCalcHoga,			//[22] ȣ��(������������ ����ݿ���)
	dxGrphMtlColMaxLeft,	//[23] �׷��� (N���� �÷� �ִ밪 ����) N���� �÷� ���� �ִ밪 �������� ���� ������ ������ �׷����� ǥ���Ѵ�.
	dxGrphMtlColMaxRight,	//[24] �׷��� (N���� �÷� �ִ밪 ����) N���� �÷� ���� �ִ밪 �������� ���� ������ ������ �׷����� ǥ���Ѵ�.
	dxGrphSnglColMaxLeft,	//[25] �׷��� (1���� �÷� �ִ밪 ����) 1���� �÷� ���� �ִ밪 �������� ���� ������ ������ �׷����� ǥ���Ѵ�.
	dxGrphSnglColMaxRight,	//[26] �׷��� (1���� �÷� �ִ밪 ����) 1���� �÷� ���� �ִ밪 �������� ���� ������ ������ �׷����� ǥ���Ѵ�.
	dxOPResist2,			//[27] �Ǻ�2������")	
	dxOPResist1,			//[28] �Ǻ�1������")	
	dxOPPivot,				//[29] �Ǻ�")			
	dxOPSupport1,			//[30] �Ǻ�1������")	
	dxOPSupport2,			//[31] �Ǻ�2������")	
	dxGraphTotRem,			//[32] ���ܷ� ���� �׷���")	
	dxOpCellQtyTrend,		//[33] ü������(TREND)")	
	
	

	

//	dxOPMaxData,		//[21] Progress �ִ밪����(Col)
//	dxOPRowMaxData,		//[22] Progress �ִ밪����(Row)
//	dxOPCellMaxData,	//[23] Progress One Cell 100%����
//	dxOpRefAttribute3,	//[25] Attribute3 Refer��(1262 �����Ϳ� �������� �ִ°��)	
//	dxOpCellQtyTrend,	//[26] ü������(Trend)������
//	dxOpCellQtyBlink,	//[27] ü�����̱�����������
//	dxOpCellForceMinus,	//[28] ������ȣ����������
//	dxRealAccumulateData,//[29] Real ���Ž� ������ ������(���������Ϳ� ���ŵ����͸� �����Ѵ�.)
//	dxOPRealVolume,		  //[35] �ǽð������� ���� ������ �ŷ��� ������


//	dxOPHogaPayoff,		//[24] ȣ������-�򰡼���"
//	dxOPHogaPayoffRate,	//[25] ȣ������-���ͷ�
//	dxOPHogaReversAttr,	//[26] ȣ�����̺�Attribute�ݴ뼿" 
/*
	dxOPATMDataCell,	//[21] ATM������ �÷� ����.  
	dxOPHangSaCell,		//[22] ��簡 �÷� ����. 
	dxOPRealMinus,		//[23] �ǽð� ������Ʈ�� �ڽ��� ���� �ǽð� ���� ������ ������. 
	dxOPRealPlus,		//[24] �ǽð� ������Ʈ�� �ڽ��� ���� �ǽð� ���� ���Ѱ��� ������.
	dxOPDate,			//[26] �����÷�����. 
	dxOPMaxData,		//[27] �ִ밪�÷�����. 
	dxOPTreeSum,		//[28] Ʈ�� ��ü �հ谪 (+)�÷�����. 
	dxOPTreeAvg,		//[29] Ʈ�� ��ü ��հ�  �÷�����. 
	dxOPMaedoCol,		//[30] �ŵ��� ����(�򰡼��͵�����)
	dxOPCurPrice,		//[31] ���簡 �÷�(�򰡼��͵�����)
	dxOPOrderQty,		//[32] �ֹ����� �÷�(�򰡼��͵�����)
	dxOPAvePrice,		//[33] ��մܰ� �÷�(�򰡼��͵�����)
	dxOPValue,			//[34] �ɼǰ�ġ�÷�(�ɼ������ش�)
	dxOPProfitrate,		//[35] ���ͷ��÷�.
*/

};

// Grid Scroll Mode
enum DXScrollMode
{
	dxScrollAuto,
	dxScrollNotUse,
	dxScrollOnlyH,
	dxScrollOnlyV,
	dxScrollAlways,
	dxScrollAutoH,
	dxScrollAutoV,
	dxScrollAwsV_AtH,
	dxScrollAtV_AwsH, 
};

// Grid Line Mode
enum DXLineMode
{
	dxLineBoth,
	dxLineOnlyH,
	dxLineOnlyV,
	dxLineNotUse,
	dxLineBothEx,
};

// Selection Mode
enum DXSelMode
{
	dxSelTable,
	dxSelListSingle,
	dxSelListMulti,
	dxSelOneCell,
	dxSelNone,
	dxSelTableNoneCell,
	dxSelSelOneCell,	
};

// Resize Header Mode
enum DXRszHdrMode
{
	dxRszHdrNotUse,
	dxRszHdrOnlyRow,
	dxRszHdrOnlyCol,
	dxRszHdrBoth,
	dxRszHdrTblResize,
};

// Tooltip Mode
enum DXTooltipMode
{
	dxTtipNotUse,
	dxTtipOnlyTtip,
	dxTtipOnlyMemo,
	dxTtipBoth,
};

// Tooltip Mode
enum DXGridLineStyle
{
	dxLSSolid		= PS_SOLID,
	dxLSDash		= PS_DASH,		/* -------  */	
	dxLSDot			= PS_DOT,		/* .......  */
	dxLSDashDot		= PS_DASHDOT,	/* _._._._  */
};


// 3D Effect (Only Table)
enum DX3DEffect
{
	dx3DNormal,
	dx3DInsert,
	dx3DRaised,
};

// Sort Mode (Only Grid)
enum DXSortMode
{
	dxSortNotUse,
	dxSortNormal,
	dxSortLooping,
};

// FID Flag
enum DXItemFlag
{
	dxItemNotUse,
	dxItemIn,
	dxItemOut,
	dxItemInOut,
};

enum DXResize
{
//	dxResize,
//	dxMove,
	dxRszNone,
	dxRszHOnly,
	dxRszVOnly,
	dxRszBoth,
	
};

// Scroll Action
enum DXSclAct
{
	dxSActDefault,			//������.
	dxSActDwRqst,			//����ȸ.
};

// HeaderType
enum DXHeaderType
{
	dxHNormal       = 0,				// Normal
	dxH3DStyle		= 1,				// 3D Style
	dxHRoundStyle   = 2,				// Round Style
};

/////////////////////////////////////////////////////////////////
// Sign Format
#define SF_USE_SALEBUY_COLOR		0x01		// �ŵ�/�ż� ���ڻ� ���..
#define SF_USE_BIT_SIGNCOLOR		0x02		// ��� ������ , ���� ������ sign Color�� ����.
#define SF_USE_NEGTIV_SIGNCOLOR		0x04		// Sign Bit���� ���� ����Ÿ�� ����/���/0 ���η� Sign Color�� �����Ѵ�.
#define SF_USE_SYMBOL				0x08		// ��� ��ȣ ���.
#define SF_USE_ATTR_COLOR			0x10		// ���ϴ�� ��ȣ�� Attribute�� ���
#define SF_USE_ATTR_COLOR2			0x20		// ü�ᷮ  Attribute�� ���
//#define SF_USE_TEXTNOTTRIM			0x40		// ���� ��ȸ����� Trim���� 
#define SF_USE_TEXTTRIM				0x40		// ���� ��ȸ����� Trim��
#define SF_USE_TEXTCONVERT			0x80		// Text Convert


// Old Sign Format
// ���� ó���� ���ؼ� ���ܵд�.
enum DXSign
{
	dxSFmtDefault	= 0,		//������.
	dxSFmtSign		= 1,		//Sign Color(���� ���ڸ��� ��ȣ�� ����� ����� ��ȣ�� ó��)(++/--)
	dxSFmtSymbol	= 2,		//Bitmap Symbol
	dxSFmtSignalMng	= 3,		//Signal Manager
	dxSFmtNtvSign	= 4,		//Sign Color(���� ���ڸ��� ��ȣ�� ������ �ʴ� ����� ��ȣ�� ó��)(-)
};
/////////////////////////////////////////////////////////////////

// Control Border Style
enum DXCtrlBorder
{
	dxCBdrNone,
	dxCBdrBorder,
	dxCBdr3D,
	dxCBdrBorder3D,
};

// Drag & Drop Mode
enum DXDnDMode
{
	dxDnDNone,				// ������.
	dxImageDrag_Drop,		// �̹��� Drag&Drop�� �ڽ��� ��Ʈ�ѿ��� �����̵� ��� 
	dxDnDAll,				// Drag & Drop (Drag�� ���� ����)
	dxDnDDrag,				// Drag
	dxDnDDrop,				// Drop
	dxDnDExcel,
	dxDnDAll_Del,			// Drag & Drop (Drag�� ����)
	dxDnDDrag_Del,			// Drag (Drag�� ����)
};

// ����Ÿ ��ȯ ����
enum DXRealHLMode
{
	dxRealHLCell,			// ������ ��ȯ.
	dxRealHLCol,			// Row���� ��ȯ.
	dxRealHLNone,			// ��ȯ ���� ����.
	dxRealHLRegCell,		// Register Cell.
};

// Code Input Control���� ��� ���� ���̾�α��� Catalog Mode
enum DXCodeCatalog
{
	dxCatalogFuture,		// ����.
	dxCatalogOption,		// �ɼ�.
	dxCatalogStock,			// �ֽ�.
};

////////////////////////
//ȣ�� ���̺� ����.
// �ż�/�ŵ� �ֹ� ��.
enum DXHogaOrder
{
	dxHGOdrNone,		// None
	dxHGOdrSale,		// Sale Order
	dxHGOdrBuy,			// Buy Order
};

// ȣ�� ���� �׷���.
enum DXHogaGraph
{
	dxHGGrpNone,		// None
	dxHGGrpOwner,		// Graph Start Cell
	dxHGGrpSlave,		// Graph End Cell
	dxHGGrpInOneCell,	// Graph In One Cell
};
/*

// �ż�/�ŵ� ���� ��.
enum DXHogaEmphasis
{
	dxHGEpsNone,		// None
	dxHGEpsSale,		// Sale Emphasis
	dxHGEpsBuy,			// Buy Emphasis
	dxHGEpsBoth,		// Both
};
*/

enum GridCellType
{
	Header = 0,
	TgtBody,
	Body,
	Error,
};	

// �÷������ ����. 
enum DXColumnHide
{
	dxColShow			= 0,		// ���̱�. 
	dxColSystemHide,				// �ý��� �����. 
	dxColUserHide,					// ����� Show/Hide
};

/*****************************************************************************/
// �ǽð� ���� ����.
#define RC_CONDITION_MAX				30
#define RC_VALUE_MAX					10

enum RCOperator
{
	RCOP_EQUAL = 0,
	RCOP_NOT_EQUAL,
	RCOP_DATA_CMP,
	RCOP_AWS_TRUE,
};	

enum RCDefAction
{
	RCDEFAC_INSERT = 0,
	RCDEFAC_ADD,
	RCDEFAC_IGNORE,
};

enum RCAction
{
	RCAC_TOPINSERT = 0,
	RCAC_INSERT,
	RCAC_ADD,
	RCAC_BTMADD,
	RCAC_UPDATE,
	RCAC_DELETE,
	RCAC_IGNORE,
	RCAC_NEXTCON,
	RCAC_UPDATE_INSERT,
};	
/*****************************************************************************/

/*****************************************************************************/
// New ���� ����
#define NR_CONDITION_MAX				50
#define NR_SYMBOL_MAX					20

enum NRCmpType
{
	NRCT_CONSTANT = 0,			//0:��� ��.
	NRCT_ITEM,					//1:�������� ����.
	NRCT_CR_COPY,				//2:Target Item�� ���� ����(��ü���ڴ� �ش� �ȵ�)
};	

enum NROperator
{
	NROP_GREAT = 0,				// >
	NROP_LESS,					// <
	NROP_EQUAL,					// =
	NROP_GREAT_EQUAL,			// >=
	NROP_LESS_EQUAL,			// <=
	NROP_NOT_EQUAL,				// !=
};	
/*****************************************************************************/
////////////////////////
// Cell Control ID
enum DXCellCtrl
{
	dxCtrlEdit		 = 52512,	//GX_IDS_CTRL_EDIT					(Edit Control)
	dxCtrlStatic	 = 52513,	//GX_IDS_CTRL_STATIC				(Static Text)
	dxCtrlPushBtn	 = 52514,	//GX_IDS_CTRL_PUSHBTN				(Push Button)
	dxCtrlSpin		 = 52519,	//GX_IDS_CTRL_SPINEDIT				(Spin Edit)
	dxCtrlHeader	 = 52520,	//GX_IDS_CTRL_HEADER				(Header)
	dxCtrlCheck		 = 52523,	//GX_IDS_CTRL_CHECKBOX3D			(Checkbox, 3d-Effect)
//	dxCtrlCombo		 = 52527,	//GX_IDS_CTRL_TEXTFIT				(combobox only allows text input which fits the choice list)
	dxCtrlCombo		 = 52529,	//GX_IDS_CTRL_CBS_DROPDOWNLIST		
	dxCtrlProgress	 = 52536,	//GX_IDS_CTRL_PROGRESS				(Progress Control)
	dxCtrlPWEdit	 = 52537,	//GX_IDS_CTRL_PASSWORD				(Password Edit Control)
	dxCtrlJMCombo	 = 61448,	//GX_IDS_CTRL_JMCOMBO				(JMCombo(���������))
	dxCtrlCodeInput  = 61449,	//GX_IDS_CTRL_CELLCODEINPUT			(Code Input Control(����/�ɼǿ�))
	dxCtrlAmountPrgs = 61450,	//GX_IDS_CTRL_AMOUNTPROGRESS		(ȣ�� ���̺��� �ܷ� �� ���α׷���)
	dxCtrlHBongChart = 61451,	//GX_IDS_CTRL_HBONGCHART			(���� Bong íƮ.)
	dxCtrlBMPBtn	 = 61452,	//GX_IDS_CTRL_NEWBTMBUTTON			(Bitmap Button.)
	dxCtrlVBongChart = 61453,	//GX_IDS_CTRL_VBONGCHART			(���� Bong íƮ.)
	dxCtrlComboBoxEx  = 61454,	//GX_IDS_CTRL_COMBOX_EX				(ComboBox_Ex Control)
	dxCtrlDateTime    = 52543,	//GX_IDS_CTRL_DATETIME 
};

//#define BASIC_CTRLCNT	3	// static, edit, header 
static int ControlID[] ={ 
							dxCtrlStatic,
							dxCtrlEdit,
							dxCtrlHeader,
							dxCtrlCombo,
							dxCtrlCheck,
							dxCtrlSpin,
							dxCtrlPushBtn,
							dxCtrlProgress,
							dxCtrlPWEdit,
							/*dxCtrlJMCombo,*/
							dxCtrlCodeInput,
							/*dxCtrlAmountPrgs,*/
							dxCtrlHBongChart,
							dxCtrlBMPBtn,
							dxCtrlVBongChart,
							dxCtrlComboBoxEx,
							dxCtrlDateTime,
						};


#endif//_OGDESIGNDEFINE_H_
