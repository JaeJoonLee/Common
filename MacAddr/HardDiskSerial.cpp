// HardDiskSerial.cpp: implementation of the CHardDiskSerial class.
//
//////////////////////////////////////////////////////////////////////
//******************************************************************
//  All Rights Reserved. Copyright(c)   2009 (ÁÖ)ÇÑ±¹¼Ò¸®¸¶Ä¡        
//******************************************************************
//  File Name     : HardDiskSerial.cpp
//  Function      : 
//  System Name   : CommApi
//  Create        : 
//  Update        : ±èÈ£°â, 2009/10/08 VS 2008 Upgrade¸¦ À§ÇÑ ÀÛ¾÷
//  Comment       : 
//*****************************************************************
#include "stdafx.h"
//#include "HardDisk.h"
#include "HardDiskSerial.h"

#include <winioctl.h>
//#include ".\include\port32.h"
//#include ".\include\winio.h"
#include "port32.h"
#include "winio.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

__declspec(naked) void Ring0GetPortVal()
{
  _asm
  {
    Cmp CL, 1
    Je ByteVal
    Cmp CL, 2
    Je WordVal
    Cmp CL, 4
    Je DWordVal

ByteVal:

    In AL, DX
    Mov [EBX], AL
    Retf

WordVal:

    In AX, DX
    Mov [EBX], AX
    Retf

DWordVal:

    In EAX, DX
    Mov [EBX], EAX
    Retf
  }
}


__declspec(naked) void Ring0SetPortVal()
{
  _asm
  {
    Cmp CL, 1
    Je ByteVal
    Cmp CL, 2
    Je WordVal
    Cmp CL, 4
    Je DWordVal

ByteVal:

    Mov AL, [EBX]
    Out DX, AL
    Retf

WordVal:

    Mov AX, [EBX]
    Out DX, AX
    Retf

DWordVal:

    Mov EAX, [EBX]
    Out DX, EAX
    Retf
  }
}

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

//******************************************************************
//  Function Name : CHardDiskSerial
//  Function      : »ý¼ºÀÚ
//  Param         : ¾øÀ½
//  Return        : ¾øÀ½ 
//  Create        : 
//  Update        : ±èÈ£°â, 2009/10/08 VS 2008 Upgrade¸¦ À§ÇÑ ÀÛ¾÷
//  Comment       : 
//******************************************************************
CHardDiskSerial::CHardDiskSerial()
{
	IsWinIoInitialized = false;
}

//******************************************************************
//  Function Name : ~CHardDiskSerial
//  Function      : ¼Ò¸êÀÚ
//  Param         : ¾øÀ½
//  Return        : ¾øÀ½ 
//  Create        : 
//  Update        : ±èÈ£°â, 2009/10/08 VS 2008 Upgrade¸¦ À§ÇÑ ÀÛ¾÷
//  Comment       : 
//******************************************************************
CHardDiskSerial::~CHardDiskSerial()
{

}

//******************************************************************
//  Function Name : getHardDriveComputerID 
//  Function      : 
//  Param         : ¾øÀ½
//  Return        : long 
//  Create        : 
//  Update        : ±èÈ£°â, 2009/10/08 VS 2008 Upgrade¸¦ À§ÇÑ ÀÛ¾÷
//  Comment       : 
//******************************************************************
long CHardDiskSerial::getHardDriveComputerID ()
{
   int done = FALSE;
   //char string [1024];
   __int64 id = 0;

   strcpy (HardDriveSerialNumber, "");  // ÃÊ±âÈ­

      //  this works under WinNT4 or Win2K if you have admin rights
   done = ReadPhysicalDriveInNT ();

      //  this should work in WinNT or Win2K if previous did not work
      //  this is kind of a backdoor via the SCSI mini port driver into
      //     the IDE drives
   if ( ! done) done = ReadIdeDriveAsScsiDriveInNT ();

      //  this works under Win9X and calls WINIO.DLL
   if ( ! done) done = ReadDrivePortsInWin9X ();

   if (done)
   {
      char *p = HardDriveSerialNumber;

      //WriteConstantString ("HardDriveSerialNumber", HardDriveSerialNumber);

         //  ignore first 5 characters from western digital hard drives if
         //  the first four characters are WD-W
      if ( ! strncmp (HardDriveSerialNumber, "WD-W", 4)) p += 5;
      for ( ; p && *p; p++)
      {
         if ('-' == *p) continue;
         id *= 10;
         switch (*p)
         {
            case '0': id += 0; break;
            case '1': id += 1; break;
            case '2': id += 2; break;
            case '3': id += 3; break;
            case '4': id += 4; break;
            case '5': id += 5; break;
            case '6': id += 6; break;
            case '7': id += 7; break;
            case '8': id += 8; break;
            case '9': id += 9; break;
            case 'a': case 'A': id += 10; break;
            case 'b': case 'B': id += 11; break;
            case 'c': case 'C': id += 12; break;
            case 'd': case 'D': id += 13; break;
            case 'e': case 'E': id += 14; break;
            case 'f': case 'F': id += 15; break;
            case 'g': case 'G': id += 16; break;
            case 'h': case 'H': id += 17; break;
            case 'i': case 'I': id += 18; break;
            case 'j': case 'J': id += 19; break;
            case 'k': case 'K': id += 20; break;
            case 'l': case 'L': id += 21; break;
            case 'm': case 'M': id += 22; break;
            case 'n': case 'N': id += 23; break;
            case 'o': case 'O': id += 24; break;
            case 'p': case 'P': id += 25; break;
            case 'q': case 'Q': id += 26; break;
            case 'r': case 'R': id += 27; break;
            case 's': case 'S': id += 28; break;
            case 't': case 'T': id += 29; break;
            case 'u': case 'U': id += 30; break;
            case 'v': case 'V': id += 31; break;
            case 'w': case 'W': id += 32; break;
            case 'x': case 'X': id += 33; break;
            case 'y': case 'Y': id += 34; break;
            case 'z': case 'Z': id += 35; break;
         }                            
      }
   }

      //   make sure no bigger than 16^7
   if (id > 268435455) id %= 268435456;

   TRACE("\nComputer ID_______________________: %d\n", id);

   return (long) id;
}

//******************************************************************
//  Function Name : ReadPhysicalDriveInNT 
//  Function      : 
//  Param         : void
//  Return        : int 
//  Create        : 
//  Update        : ±èÈ£°â, 2009/10/08 VS 2008 Upgrade¸¦ À§ÇÑ ÀÛ¾÷
//  Comment       : 
//******************************************************************
int CHardDiskSerial::ReadPhysicalDriveInNT (void)
{
   int done = FALSE;
   int drive = 0;

   for (drive = 0; drive < MAX_IDE_DRIVES; drive++)
   {
      HANDLE hPhysicalDriveIOCTL = 0;

         //  Try to get a handle to PhysicalDrive IOCTL, report failure
         //  and exit if can't.
      char driveName [256];

      sprintf (driveName, "\\\\.\\PhysicalDrive%d", drive);

         //  Windows NT, Windows 2000, must have admin rights
      hPhysicalDriveIOCTL = CreateFile (driveName,
                               GENERIC_READ | GENERIC_WRITE, 
                               FILE_SHARE_READ | FILE_SHARE_WRITE, NULL,
                               OPEN_EXISTING, 0, NULL);
      // if (hPhysicalDriveIOCTL == INVALID_HANDLE_VALUE)
      //    printf ("Unable to open physical drive %d, error code: 0x%lX\n",
      //            drive, GetLastError ());

      if (hPhysicalDriveIOCTL != INVALID_HANDLE_VALUE)
      {
         GETVERSIONOUTPARAMS VersionParams;
         DWORD               cbBytesReturned = 0;

            // Get the version, etc of PhysicalDrive IOCTL
         memset ((void*) &VersionParams, 0, sizeof(VersionParams));

         if ( ! DeviceIoControl (hPhysicalDriveIOCTL, DFP_GET_VERSION,
                   NULL, 
                   0,
                   &VersionParams,
                   sizeof(VersionParams),
                   &cbBytesReturned, NULL) )
         {         
            // printf ("DFP_GET_VERSION failed for drive %d\n", i);
            // continue;
         }

            // If there is a IDE device at number "i" issue commands
            // to the device
         if (VersionParams.bIDEDeviceMap > 0)
         {
            BYTE             bIDCmd = 0;   // IDE or ATAPI IDENTIFY cmd
            SENDCMDINPARAMS  scip;
            //SENDCMDOUTPARAMS OutCmd;

			// Now, get the ID sector for all IDE devices in the system.
               // If the device is ATAPI use the IDE_ATAPI_IDENTIFY command,
               // otherwise use the IDE_ATA_IDENTIFY command
            bIDCmd = (VersionParams.bIDEDeviceMap >> drive & 0x10) ? \
                      IDE_ATAPI_IDENTIFY : IDE_ATA_IDENTIFY;

            memset (&scip, 0, sizeof(scip));
            memset (IdOutCmd, 0, sizeof(IdOutCmd));

            if ( DoIDENTIFY (hPhysicalDriveIOCTL, 
                       &scip, 
                       (PSENDCMDOUTPARAMS)&IdOutCmd, 
                       (BYTE) bIDCmd,
                       (BYTE) drive,
                       &cbBytesReturned))
            {
               DWORD diskdata [256];
               int ijk = 0;
               USHORT *pIdSector = (USHORT *)
                             ((PSENDCMDOUTPARAMS) IdOutCmd) -> bBuffer;

               for (ijk = 0; ijk < 256; ijk++)
                  diskdata [ijk] = pIdSector [ijk];

               PrintIdeInfo (drive, diskdata);

               done = TRUE;
            }
	    }

         CloseHandle (hPhysicalDriveIOCTL);
      }
   }

   return done;
}

//******************************************************************
//  Function Name : ReadIdeDriveAsScsiDriveInNT 
//  Function      : 
//  Param         : void
//  Return        : int 
//  Create        : 
//  Update        : ±èÈ£°â, 2009/10/08 VS 2008 Upgrade¸¦ À§ÇÑ ÀÛ¾÷
//  Comment       : 
//******************************************************************
int CHardDiskSerial::ReadIdeDriveAsScsiDriveInNT (void)
{
   int done = FALSE;
   int controller = 0;

   for (controller = 0; controller < 2; controller++)
   {
      HANDLE hScsiDriveIOCTL = 0;
      char   driveName [256];

         //  Try to get a handle to PhysicalDrive IOCTL, report failure
         //  and exit if can't.
      sprintf (driveName, "\\\\.\\Scsi%d:", controller);

         //  Windows NT, Windows 2000, any rights should do
      hScsiDriveIOCTL = CreateFile (driveName,
                               GENERIC_READ | GENERIC_WRITE, 
                               FILE_SHARE_READ | FILE_SHARE_WRITE, NULL,
                               OPEN_EXISTING, 0, NULL);
      // if (hScsiDriveIOCTL == INVALID_HANDLE_VALUE)
      //    printf ("Unable to open SCSI controller %d, error code: 0x%lX\n",
      //            controller, GetLastError ());

      if (hScsiDriveIOCTL != INVALID_HANDLE_VALUE)
      {
         int drive = 0;

         for (drive = 0; drive < 2; drive++)
         {
            char buffer [sizeof (SRB_IO_CONTROL) + SENDIDLENGTH];
            SRB_IO_CONTROL *p = (SRB_IO_CONTROL *) buffer;
            SENDCMDINPARAMS *pin =
                   (SENDCMDINPARAMS *) (buffer + sizeof (SRB_IO_CONTROL));
            DWORD dummy;
   
            memset (buffer, 0, sizeof (buffer));
            p -> HeaderLength = sizeof (SRB_IO_CONTROL);
            p -> Timeout = 10000;
            p -> Length = SENDIDLENGTH;
            p -> ControlCode = IOCTL_SCSI_MINIPORT_IDENTIFY;
            strncpy((char *) p -> Signature, "SCSIDISK", 8);
  
            pin -> irDriveRegs.bCommandReg = IDE_ATA_IDENTIFY;
            pin -> bDriveNumber = drive;

            if (DeviceIoControl (hScsiDriveIOCTL, IOCTL_SCSI_MINIPORT, 
                                 buffer,
                                 sizeof (SRB_IO_CONTROL) +
                                         sizeof (SENDCMDINPARAMS) - 1,
                                 buffer,
                                 sizeof (SRB_IO_CONTROL) + SENDIDLENGTH,
                                 &dummy, NULL))
            {
               SENDCMDOUTPARAMS *pOut =
                    (SENDCMDOUTPARAMS *) (buffer + sizeof (SRB_IO_CONTROL));
               IDSECTOR *pId = (IDSECTOR *) (pOut -> bBuffer);
               if (pId -> sModelNumber [0])
               {
                  DWORD diskdata [256];
                  int ijk = 0;
                  USHORT *pIdSector = (USHORT *) pId;
          
                  for (ijk = 0; ijk < 256; ijk++)
                     diskdata [ijk] = pIdSector [ijk];

                  PrintIdeInfo (controller * 2 + drive, diskdata);

                  done = TRUE;
               }
            }
         }
         CloseHandle (hScsiDriveIOCTL);
      }
   }

   return done;
}

//******************************************************************
//  Function Name : ReadDrivePortsInWin9X
//  Function      : 
//  Param         : void
//  Return        : int 
//  Create        : 
//  Update        : ±èÈ£°â, 2009/10/08 VS 2008 Upgrade¸¦ À§ÇÑ ÀÛ¾÷
//  Comment       : 
//******************************************************************
int CHardDiskSerial::ReadDrivePortsInWin9X(void)
{
   int done = FALSE;
   int drive = 0;

   InitializeWinIo ();   

      //  Get IDE Drive info from the hardware ports
      //  loop thru all possible drives
   for (drive = 0; drive < 8; drive++)
   {
      DWORD diskdata [256];
      WORD  baseAddress = 0;   //  Base address of drive controller 
      DWORD portValue = 0;
      int waitLoop = 0;
      int index = 0;
 
      switch (drive / 2)
      {
         case 0: baseAddress = 0x1f0; break;
         case 1: baseAddress = 0x170; break;
         case 2: baseAddress = 0x1e8; break;
         case 3: baseAddress = 0x168; break;
      }

         //  Wait for controller not busy 
      waitLoop = 100000;
      while (--waitLoop > 0)
      {
         GetPortVal ((WORD) (baseAddress + 7), &portValue, (BYTE) 1);
            //  drive is ready
         if ((portValue & 0x40) == 0x40) break;
            //  previous drive command ended in error
         if ((portValue & 0x01) == 0x01) break;
      }

      if (waitLoop < 1) continue;

         //  Set Master or Slave drive
      if ((drive % 2) == 0)
         SetPortVal ((WORD) (baseAddress + 6), 0xA0, 1);
      else
         SetPortVal ((WORD) (baseAddress + 6), 0xB0, 1);

         //  Get drive info data
      SetPortVal ((WORD) (baseAddress + 7), 0xEC, 1);

         // Wait for data ready 
      waitLoop = 100000;
      while (--waitLoop > 0)
      {
         GetPortVal ((WORD) (baseAddress + 7), &portValue, 1);
            //  see if the drive is ready and has it's info ready for us
         if ((portValue & 0x48) == 0x48) break;
            //  see if there is a drive error
         if ((portValue & 0x01) == 0x01) break;
      }

         //  check for time out or other error                                                    
      if (waitLoop < 1 || portValue & 0x01) continue;

         //  read drive id information
      for (index = 0; index < 256; index++)
      {
         diskdata [index] = 0;   //  init the space
         GetPortVal (baseAddress, &(diskdata [index]), 2);
      }

      PrintIdeInfo (drive, diskdata);
      done = TRUE;
   }

   ShutdownWinIo ();

   return done;
}

//******************************************************************
//  Function Name : DoIDENTIFY 
//  Function      : 
//  Param         : HANDLE hPhysicalDriveIOCTL, PSENDCMDINPARAMS pSCIP,
//					PSENDCMDOUTPARAMS pSCOP, BYTE bIDCmd, BYTE bDriveNum,
//					PDWORD lpcbBytesReturned
//  Return        : BOOL 
//  Create        : 
//  Update        : ±èÈ£°â, 2009/10/08 VS 2008 Upgrade¸¦ À§ÇÑ ÀÛ¾÷
//  Comment       : 
//******************************************************************
BOOL CHardDiskSerial::DoIDENTIFY (HANDLE hPhysicalDriveIOCTL, PSENDCMDINPARAMS pSCIP,
                 PSENDCMDOUTPARAMS pSCOP, BYTE bIDCmd, BYTE bDriveNum,
                 PDWORD lpcbBytesReturned)
{
      // Set up data structures for IDENTIFY command.
   pSCIP -> cBufferSize = IDENTIFY_BUFFER_SIZE;
   pSCIP -> irDriveRegs.bFeaturesReg = 0;
   pSCIP -> irDriveRegs.bSectorCountReg = 1;
   pSCIP -> irDriveRegs.bSectorNumberReg = 1;
   pSCIP -> irDriveRegs.bCylLowReg = 0;
   pSCIP -> irDriveRegs.bCylHighReg = 0;

      // Compute the drive number.
   pSCIP -> irDriveRegs.bDriveHeadReg = 0xA0 | ((bDriveNum & 1) << 4);

      // The command can either be IDE identify or ATAPI identify.
   pSCIP -> irDriveRegs.bCommandReg = bIDCmd;
   pSCIP -> bDriveNumber = bDriveNum;
   pSCIP -> cBufferSize = IDENTIFY_BUFFER_SIZE;

   return ( DeviceIoControl (hPhysicalDriveIOCTL, DFP_RECEIVE_DRIVE_DATA,
               (LPVOID) pSCIP,
               sizeof(SENDCMDINPARAMS) - 1,
               (LPVOID) pSCOP,
               sizeof(SENDCMDOUTPARAMS) + IDENTIFY_BUFFER_SIZE - 1,
               lpcbBytesReturned, NULL) );
}
//******************************************************************
//  Function Name : PrintIdeInfo 
//  Function      : 
//  Param         : int drive, DWORD diskdata [256]
//  Return        : void 
//  Create        : 
//  Update        : ±èÈ£°â, 2009/10/08 VS 2008 Upgrade¸¦ À§ÇÑ ÀÛ¾÷
//  Comment       : 
//******************************************************************
void CHardDiskSerial::PrintIdeInfo (int drive, DWORD diskdata [256])
{
      //  copy the hard driver serial number to the buffer
   strcpy (HardDriveSerialNumber, ConvertToString (diskdata, 10, 19));

#ifdef PRINTING_TO_CONSOLE_ALLOWED

   switch (drive / 2)
   {
      case 0: printf ("\nPrimary Controller - ");
              break;
      case 1: printf ("\nSecondary Controller - ");
              break;
      case 2: printf ("\nTertiary Controller - ");
              break;
      case 3: printf ("\nQuaternary Controller - ");
              break;
   }

   switch (drive % 2)
   {
      case 0: printf ("Master drive\n\n");
              break;
      case 1: printf ("Slave drive\n\n");
              break;
   }

   printf ("Drive Model Number________________: %s\n",
           ConvertToString (diskdata, 27, 46));
   printf ("Drive Serial Number_______________: %s\n",
           ConvertToString (diskdata, 10, 19));
   printf ("Drive Controller Revision Number__: %s\n",
           ConvertToString (diskdata, 23, 26));

   printf ("Controller Buffer Size on Drive___: %u bytes\n",
           diskdata [21] * 512);

   printf ("Drive Type________________________: ");
   if (diskdata [0] & 0x0080)
      printf ("Removable\n");
   else if (diskdata [0] & 0x0040)
      printf ("Fixed\n");
   else printf ("Unknown\n");
           
   printf ("Physical Geometry:     "
           "%u Cylinders     %u Heads     %u Sectors per track\n",
           diskdata [1], diskdata [3], diskdata [6]);

#else   //  PRINTING_TO_CONSOLE_ALLOWED

   //  nothing to do

#endif  // PRINTING_TO_CONSOLE_ALLOWED

}
//******************************************************************
//  Function Name : InitializeWinIo
//  Function      : 
//  Param         : ¾øÀ½
//  Return        : BOOL 
//  Create        : 
//  Update        : ±èÈ£°â, 2009/10/08 VS 2008 Upgrade¸¦ À§ÇÑ ÀÛ¾÷
//  Comment       : 
//******************************************************************
BOOL CHardDiskSerial::InitializeWinIo()
{
  char szExePath[MAX_PATH];
  PSTR pszSlash;

  IsNT = IsWinNT();

  if (IsNT)
  {
    if (!GetModuleFileName(GetModuleHandle(NULL), szExePath, sizeof(szExePath)))
      return false;

    pszSlash = strrchr(szExePath, '\\');

    if (pszSlash)
      pszSlash[1] = 0;
    else
      return false;

    strcat(szExePath, "winio.sys");

//    UnloadDeviceDriver("WINIO");

//    if (!LoadDeviceDriver("WINIO", szExePath, &hDriver))
//      return false;
  }
  
  IsWinIoInitialized = true;

  return true;
}
//******************************************************************
//  Function Name : GetPortVal
//  Function      : 
//  Param         : WORD wPortAddr, PDWORD pdwPortVal, BYTE bSize
//  Return        : BOOL 
//  Create        : 
//  Update        : ±èÈ£°â, 2009/10/08 VS 2008 Upgrade¸¦ À§ÇÑ ÀÛ¾÷
//  Comment       : 
//******************************************************************
BOOL CHardDiskSerial::GetPortVal(WORD wPortAddr, PDWORD pdwPortVal, BYTE bSize)
{
  BOOL Result;
  DWORD dwBytesReturned;
  struct tagPort32Struct Port32Struct;

  if (IsNT)
  {
    if (!IsWinIoInitialized)
      return false;

    Port32Struct.wPortAddr = wPortAddr;
    Port32Struct.bSize = bSize;

    if (!DeviceIoControl(hDriver, IOCTL_WINIO_READPORT, &Port32Struct,
                         sizeof(struct tagPort32Struct), &Port32Struct, 
						 sizeof(struct tagPort32Struct),
                         &dwBytesReturned, NULL))
      return false;
    else
      *pdwPortVal = Port32Struct.dwPortVal;
  }
  else
  {
    Result = CallRing0((PVOID)Ring0GetPortVal, wPortAddr, pdwPortVal, bSize);

    if (Result == false)
      return false;
  }

  return true;
}
//******************************************************************
//  Function Name : SetPortVal
//  Function      : 
//  Param         : WORD wPortAddr, DWORD dwPortVal, BYTE bSize
//  Return        : BOOL 
//  Create        : 
//  Update        : ±èÈ£°â, 2009/10/08 VS 2008 Upgrade¸¦ À§ÇÑ ÀÛ¾÷
//  Comment       : 
//******************************************************************
BOOL CHardDiskSerial::SetPortVal(WORD wPortAddr, DWORD dwPortVal, BYTE bSize)
{
  DWORD dwBytesReturned;
  struct tagPort32Struct Port32Struct;

  if (IsNT)
  {
    if (!IsWinIoInitialized)
      return false;

    Port32Struct.wPortAddr = wPortAddr;
    Port32Struct.dwPortVal = dwPortVal;
    Port32Struct.bSize = bSize;

    if (!DeviceIoControl(hDriver, IOCTL_WINIO_WRITEPORT, &Port32Struct,
                         sizeof(struct tagPort32Struct), NULL, 0, &dwBytesReturned, NULL))
      return false;
  }
  else
    return CallRing0((PVOID)Ring0SetPortVal, wPortAddr, &dwPortVal, bSize);
  
  return true;
}
//******************************************************************
//  Function Name : ShutdownWinIo
//  Function      : 
//  Param         : ¾øÀ½
//  Return        : void 
//  Create        : 
//  Update        : ±èÈ£°â, 2009/10/08 VS 2008 Upgrade¸¦ À§ÇÑ ÀÛ¾÷
//  Comment       : 
//******************************************************************
void CHardDiskSerial::ShutdownWinIo()
{
//  if (IsNT)
//    UnloadDeviceDriver("WINIO");
}
//******************************************************************
//  Function Name : ConvertToString 
//  Function      : 
//  Param         : DWORD diskdata [256], int firstIndex, int lastIndex
//  Return        : char 
//  Create        : 
//  Update        : ±èÈ£°â, 2009/10/08 VS 2008 Upgrade¸¦ À§ÇÑ ÀÛ¾÷
//  Comment       : 
//******************************************************************
char *CHardDiskSerial::ConvertToString (DWORD diskdata [256], int firstIndex, int lastIndex)
{
   static char string [1024];
   int index = 0;
   int position = 0;

      //  each integer has two characters stored in it backwards
   for (index = firstIndex; index <= lastIndex; index++)
   {
         //  get high byte for 1st character
      string [position] = (char) (diskdata [index] / 256);
      position++;

         //  get low byte for 2nd character
      string [position] = (char) (diskdata [index] % 256);
      position++;
   }

      //  end the string 
   string [position] = '\0';

      //  cut off the trailing blanks
   for (index = position - 1; index > 0 && ' ' == string [index]; index--)
      string [index] = '\0';

   return string;
}
//******************************************************************
//  Function Name : IsWinNT
//  Function      : 
//  Param         : ¾øÀ½
//  Return        : BOOL 
//  Create        : 
//  Update        : ±èÈ£°â, 2009/10/08 VS 2008 Upgrade¸¦ À§ÇÑ ÀÛ¾÷
//  Comment       : 
//******************************************************************
BOOL CHardDiskSerial::IsWinNT()
{
  OSVERSIONINFO OSVersionInfo;

  OSVersionInfo.dwOSVersionInfoSize = sizeof(OSVERSIONINFO);

  GetVersionEx(&OSVersionInfo);

  return OSVersionInfo.dwPlatformId == VER_PLATFORM_WIN32_NT;
}
//******************************************************************
//  Function Name : CallRing0
//  Function      : 
//  Param         : PVOID pvRing0FuncAddr, WORD wPortAddr, PDWORD pdwPortVal, BYTE bSize
//  Return        : BOOL 
//  Create        : 
//  Update        : ±èÈ£°â, 2009/10/08 VS 2008 Upgrade¸¦ À§ÇÑ ÀÛ¾÷
//  Comment       : 
//******************************************************************
BOOL CHardDiskSerial::CallRing0(PVOID pvRing0FuncAddr, WORD wPortAddr, PDWORD pdwPortVal, BYTE bSize)
{

  struct GDT_DESCRIPTOR *pGDTDescriptor;
  struct GDTR gdtr;
  WORD CallgateAddr[3];
  WORD wGDTIndex = 1;

  _asm Sgdt [gdtr]

  // Skip the null descriptor

  pGDTDescriptor = (struct GDT_DESCRIPTOR *)(gdtr.dwGDTBase + 8);

  // Search for a free GDT descriptor

  for (wGDTIndex = 1; wGDTIndex < (gdtr.wGDTLimit / 8); wGDTIndex++)
  {
    if (pGDTDescriptor->Type == 0     &&
        pGDTDescriptor->System == 0   &&
        pGDTDescriptor->DPL == 0      &&
        pGDTDescriptor->Present == 0)
    {
      // Found one !
      // Now we need to transform this descriptor into a callgate.
      // Note that we're using selector 0x28 since it corresponds
      // to a ring 0 segment which spans the entire linear address
      // space of the processor (0-4GB).

      struct CALLGATE_DESCRIPTOR *pCallgate;

      pCallgate =	(struct CALLGATE_DESCRIPTOR *) pGDTDescriptor;
      pCallgate->Offset_0_15 = LOWORD(pvRing0FuncAddr);
      pCallgate->Selector = 0x28;
      pCallgate->ParamCount =	0;
      pCallgate->Unused = 0;
      pCallgate->Type = 0xc;
      pCallgate->System = 0;
      pCallgate->DPL = 3;
      pCallgate->Present = 1;
      pCallgate->Offset_16_31 = HIWORD(pvRing0FuncAddr);

      // Prepare the far call parameters

      CallgateAddr[0] = 0x0;
      CallgateAddr[1] = 0x0;
      CallgateAddr[2] = (wGDTIndex << 3) | 3;

      // Please fasten your seat belts!
      // We're about to make a hyperspace jump into RING 0.

      _asm Mov DX, [wPortAddr]
      _asm Mov EBX, [pdwPortVal]
      _asm Mov CL, [bSize]
      _asm Call FWORD PTR [CallgateAddr]

      // We have made it !
      // Now free the GDT descriptor

      memset(pGDTDescriptor, 0, 8);

      // Our journey was successful. Seeya.

      return true;
    }

    // Advance to the next GDT descriptor

    pGDTDescriptor++; 
  }

  // Whoops, the GDT is full

  return false;
}

