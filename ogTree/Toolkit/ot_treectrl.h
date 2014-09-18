///////////////////////////////////////////////////////////////////////////////
// ot_treectrl.h
//
// Copyright (c) 1999-2009 Rogue Wave Software, Inc.  All Rights Reserved.
//
// This computer software is owned by Rogue Wave Software, Inc. and is protected by
// U.S. copyright laws and other laws and by international treaties. This
// computer software is furnished by Rogue Wave Software, Inc. pursuant to a written
// license agreement and may be used, copied, transmitted, and stored
// only in accordance with the terms of such license agreement and with
// the inclusion of the above copyright notice.  This computer software or
// any other copies thereof may not be provided or otherwise made available
// to any other person.
//
// U.S. Government Restricted Rights.  This computer software:
//      (a) was developed at private expense and is in all respects the
//          proprietary information of Rogue Wave Software, Inc.;
//      (b) was not developed with government funds;
//      (c) is a trade secret of Rogue Wave Software, Inc. for all purposes of the
//          Freedom of Information Act; and
//      (d) is a commercial item and thus, pursuant to Section 12.212
//          of the Federal Acquisition Regulations (FAR) and DFAR
//          Supplement Section 227.7202, Government’s use, duplication or
//          disclosure of the computer software is subject to the restrictions
//          set forth by Rogue Wave Software, Inc.
//
///////////////////////////////////////////////////////////////////////////////
// 
//  Author:			Rob Oliver
//  Description:	ot_treectrl.h - Tree control component header
//  Created:		Tue Aug 27 14:08:25 1998
//
//

#ifndef __OTM_TREECTRL_H__
#define __OTM_TREECTRL_H__

// ***********************************************************
// *
// *  OT needs 8 byte packing for structures
// *
// ***********************************************************

#if (_MFC_VER >= 0x0300)
// pshpack8.h saves the current #pragma pack value
#include "pshpack8.h"
#else
#pragma pack(8)
#endif

// ***********************************************************
// *
// *  OT optimized include file
// *
// ***********************************************************

#ifndef __SECOPT_H__
    #include "secopt.h"
#endif

// ***********************************************************
// *
// *  Enhanced Win32 List Control
// *
// ***********************************************************

#ifdef OT_BLD_TREECTRL

	// SECListTip
	#ifndef __SLSTCTIP_H__
//	#include "OgTree\toolkit\slstctip.h"
	#endif // __SLSTCTIP_H__

	// SECListClient
	#ifndef __SLSTEDIT_H__
//	#include "OgTree\toolkit\slstedit.h"
	#endif // __SLSTEDIT_H__

	// SECListCtrl
	#ifndef __SLSTCTL_H__
	#include "slstctl.h"
	#endif // __SLSTCTL_H__

	// SECListView
	#ifndef __SLSTVW_H__
	//#include "OgTree\toolkit\slstvw.h"
	#endif // __SLSTVW_H__

	// SECTreeNode
	#ifndef __TREENODE_H__
	#include "TreeNode.h"
	#endif // __TREENODE_H__

	// SECTreeCtrl
	#ifndef __TRCTLX_H__
	#include "TrCtlX.h"
	#endif // __TRCTLX_H__

	// SECTreeView
	#ifndef __TRVWX_H__
//	#include "OgTree\toolkit\TrVwX.h"
	#endif // __TRVWX_H__

#else
	#pragma message("Warning:  The tree control component was not included in the Objective Toolkit library.")
	#pragma message("          Add this component to the library using the BuildWizard and rebuild Objective Toolkit.")
#endif // OT_BLD_TREECTRL

// ***********************************************************
// *
// *  Restore default byte packing
// *
// ***********************************************************

#if (_MFC_VER >= 0x0300)
// poppack.h restores the original #pragma pack value
#include /* */ "poppack.h"
#else
// restore default packing value
#pragma pack()
#endif

#endif // __OTM_TREECTRL_H__
