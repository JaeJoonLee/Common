// HardDiskSerial.h: interface for the CHardDiskSerial class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_HARDDISKSERIAL_H__59E897DE_9034_4502_B3DC_EEB3D3725434__INCLUDED_)
#define AFX_HARDDISKSERIAL_H__59E897DE_9034_4502_B3DC_EEB3D3725434__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include <winioctl.h>

// Max number of drives assuming primary/secondary, master/slave topology
#define  MAX_IDE_DRIVES  4
#define  IDENTIFY_BUFFER_SIZE  512

// IOCTL commands
#define  DFP_GET_VERSION          0x00074080
#define  DFP_SEND_DRIVE_COMMAND   0x0007c084
#define  DFP_RECEIVE_DRIVE_DATA   0x0007c088

#define  FILE_DEVICE_SCSI              0x0000001b
#define  IOCTL_SCSI_MINIPORT_IDENTIFY  ((FILE_DEVICE_SCSI << 16) + 0x0501)
#define  IOCTL_SCSI_MINIPORT 0x0004D008  //  see NTDDSCSI.H for definition

#pragma pack(push, 1)
// GETVERSIONOUTPARAMS contains the data returned from the 
// Get Driver Version function.
typedef struct _GETVERSIONOUTPARAMS
{
   BYTE bVersion;      // Binary driver version.
   BYTE bRevision;     // Binary driver revision.
   BYTE bReserved;     // Not used.
   BYTE bIDEDeviceMap; // Bit map of IDE devices.
   DWORD fCapabilities; // Bit mask of driver capabilities.
   DWORD dwReserved[4]; // For future use.
} GETVERSIONOUTPARAMS, *PGETVERSIONOUTPARAMS, *LPGETVERSIONOUTPARAMS;

// Bits returned in the fCapabilities member of GETVERSIONOUTPARAMS 
#define  CAP_IDE_ID_FUNCTION             1  // ATA ID command supported
#define  CAP_IDE_ATAPI_ID                2  // ATAPI ID command supported
#define  CAP_IDE_EXECUTE_SMART_FUNCTION  4  // SMART commannds supported


// IDE registers
//typedef struct _IDEREGS
//{
//   BYTE bFeaturesReg;       // Used for specifying SMART "commands".
//   BYTE bSectorCountReg;    // IDE sector count register
//   BYTE bSectorNumberReg;   // IDE sector number register
//   BYTE bCylLowReg;         // IDE low order cylinder value
//   BYTE bCylHighReg;        // IDE high order cylinder value
//   BYTE bDriveHeadReg;      // IDE drive/head register
//   BYTE bCommandReg;        // Actual IDE command.
//   BYTE bReserved;          // reserved for future use.  Must be zero.
//} IDEREGS, *PIDEREGS, *LPIDEREGS;
//   
// SENDCMDINPARAMS contains the input parameters for the 
// Send Command to Drive function.
//typedef struct _SENDCMDINPARAMS
//{
//   DWORD     cBufferSize;   //  Buffer size in bytes
//   IDEREGS   irDriveRegs;   //  Structure with drive register values.
//   BYTE bDriveNumber;       //  Physical drive number to send 
//                            //  command to (0,1,2,3).
//   BYTE bReserved[3];       //  Reserved for future expansion.
//   DWORD     dwReserved[4]; //  For future use.
//   BYTE      bBuffer[1];    //  Input buffer.
//} SENDCMDINPARAMS, *PSENDCMDINPARAMS, *LPSENDCMDINPARAMS;


// Valid values for the bCommandReg member of IDEREGS.
#define  IDE_ATAPI_IDENTIFY  0xA1  //  Returns ID sector for ATAPI.
#define  IDE_ATA_IDENTIFY    0xEC  //  Returns ID sector for ATA.


// Status returned from driver
//typedef struct _DRIVERSTATUS
//{
//   BYTE  bDriverError;  //  Error code from driver, or 0 if no error.
//   BYTE  bIDEStatus;    //  Contents of IDE Error register.
//                        //  Only valid when bDriverError is SMART_IDE_ERROR.
//   BYTE  bReserved[2];  //  Reserved for future expansion.
//   DWORD  dwReserved[2];  //  Reserved for future expansion.
//} DRIVERSTATUS, *PDRIVERSTATUS, *LPDRIVERSTATUS;


// Structure returned by PhysicalDrive IOCTL for several commands
//typedef struct _SENDCMDOUTPARAMS
//{
//   DWORD         cBufferSize;   //  Size of bBuffer in bytes
//   DRIVERSTATUS  DriverStatus;  //  Driver status structure.
//   BYTE          bBuffer[1];    //  Buffer of arbitrary length in which to store the data read from the                                                       // drive.
//} SENDCMDOUTPARAMS, *PSENDCMDOUTPARAMS, *LPSENDCMDOUTPARAMS;

// The following struct defines the interesting part of the IDENTIFY
// buffer:
typedef struct _IDSECTOR
{
   USHORT  wGenConfig;
   USHORT  wNumCyls;
   USHORT  wReserved;
   USHORT  wNumHeads;
   USHORT  wBytesPerTrack;
   USHORT  wBytesPerSector;
   USHORT  wSectorsPerTrack;
   USHORT  wVendorUnique[3];
   CHAR    sSerialNumber[20];
   USHORT  wBufferType;
   USHORT  wBufferSize;
   USHORT  wECCSize;
   CHAR    sFirmwareRev[8];
   CHAR    sModelNumber[40];
   USHORT  wMoreVendorUnique;
   USHORT  wDoubleWordIO;
   USHORT  wCapabilities;
   USHORT  wReserved1;
   USHORT  wPIOTiming;
   USHORT  wDMATiming;
   USHORT  wBS;
   USHORT  wNumCurrentCyls;
   USHORT  wNumCurrentHeads;
   USHORT  wNumCurrentSectorsPerTrack;
   ULONG   ulCurrentSectorCapacity;
   USHORT  wMultSectorStuff;
   ULONG   ulTotalAddressableSectors;
   USHORT  wSingleWordDMA;
   USHORT  wMultiWordDMA;
   BYTE    bReserved[128];
} IDSECTOR, *PIDSECTOR;


typedef struct _SRB_IO_CONTROL
{
   ULONG HeaderLength;
   UCHAR Signature[8];
   ULONG Timeout;
   ULONG ControlCode;
   ULONG ReturnCode;
   ULONG Length;
} SRB_IO_CONTROL, *PSRB_IO_CONTROL;

#pragma pack(pop)

#define  SENDIDLENGTH  sizeof (SENDCMDOUTPARAMS) + IDENTIFY_BUFFER_SIZE

class CHardDiskSerial  
{

public:
	CHardDiskSerial();
	virtual ~CHardDiskSerial();

public:
	long getHardDriveComputerID();

// attribute
private:
	char HardDriveSerialNumber [1024];
	// Define global buffers.
	BYTE IdOutCmd [sizeof (SENDCMDOUTPARAMS) + IDENTIFY_BUFFER_SIZE - 1];
	BOOL IsNT;
	HANDLE hDriver;
	BOOL IsWinIoInitialized;

// Operation
private:
	int ReadPhysicalDriveInNT(void);
	int ReadIdeDriveAsScsiDriveInNT(void);
	int ReadDrivePortsInWin9X(void);
	void PrintIdeInfo(int drive, DWORD diskdata [256]);
	BOOL DoIDENTIFY (HANDLE, PSENDCMDINPARAMS, PSENDCMDOUTPARAMS, BYTE, BYTE, PDWORD);
	BOOL InitializeWinIo();
	BOOL GetPortVal(WORD wPortAddr, PDWORD pdwPortVal, BYTE bSize);
	BOOL SetPortVal(WORD wPortAddr, DWORD dwPortVal, BYTE bSize);
	void ShutdownWinIo();
	char *ConvertToString (DWORD diskdata [256], int firstIndex, int lastIndex);
	BOOL IsWinNT();
	BOOL CallRing0(PVOID pvRing0FuncAddr, WORD wPortAddr, PDWORD pdwPortVal, BYTE bSize);

};

#endif // !defined(AFX_HARDDISKSERIAL_H__59E897DE_9034_4502_B3DC_EEB3D3725434__INCLUDED_)
