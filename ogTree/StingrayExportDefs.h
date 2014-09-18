///////////////////////////////////////////////////////////////////////////////
// StingrayExportDefs.h
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


#ifndef STINGRAY_EXPORT_H_
#define STINGRAY_EXPORT_H_

/* ==========================================================================
	SUPPORTED COMPILERS:
	Microsoft Visual Studio 2003 SP1 (VC 7.1 SP1), 
	Microsoft Visual Studio 2005 SP1 (VC 8.0 SP1),
	Microsoft Visual Studio 2008 SP1 (VC 9.0 SP1 with Feature Pack)
   ========================================================================== */

//===========================================================================//
// NOTE: These are INTERNAL preprocessor macros ONLY!                 	     //
//                                                                           //
//    _SFL_EXPORT_IMPL, _OC_EXPORT_IMPL, _OCUT_EXPORT_IMPL, _OE_EXPORT_IMPL,             //
//    _OG_EXPORT_IMPL, _OT_EXPORT_IMPL, and _OV_EXPORT_IMPL should be        //
//    #defined in each product's stdafx.h file. (Is this a guarantee?)       //
//                                                                           //
//   Otherwise, if not a guarantee, #define each *_IMPL before all includes  //
//   in each .cpp file                                                       //
//===========================================================================//

/////////////////////////////////////////////////////////////////////////////
//
// EXPORT MACROS
//
/////////////////////////////////////////////////////////////////////////////
#ifdef _RWDLL // (Dll Build)
	#ifdef _RW_IMPL // We're building
			// Reference to a GLOBAL Function, these must be inline definitions with no 
			// function prototype.
			#define RWGLOBAL_FUNC_API(rettype)	extern "C" rettype	__declspec(dllexport) 
			// Reference to a CLASS Function
			#define RWCLASS_FUNC_API            __declspec(dllexport)
			// Reference to a GLOBAL Variable
			#define RWGLOBAL_VAR_API			RWCLASS_FUNC_API
	#else	// Someone else is linking
			// Reference to a GLOBAL Function 
			#define RWGLOBAL_FUNC_API(rettype)	extern "C" rettype	__declspec(dllimport)
			// Reference to a CLASS Function
			#define RWCLASS_FUNC_API			__declspec(dllimport)
			// Reference to a GLOBAL Variable
			#define RWGLOBAL_VAR_API			RWCLASS_FUNC_API
	#endif // RW_IMPL
#else // !_RWDLL (Static Build)
	// Reference to a CLASS Function
	#define RWCLASS_FUNC_API					// Nothing
	// Reference to a GLOBAL Function, these must be inline definitions with no 
	// function prototype.
	#define RWGLOBAL_FUNC_API(rettype)			extern "C" rettype  __cdecl // Don't mangle the name. Must use __cdecl here.

	#ifdef _RW_IMPL // We're Building
	// Reference to a GLOBAL Variable
		#define RWGLOBAL_VAR_API				// Nothing
	#else // Someone else is linking
		// Reference to a GLOBAL Variable
		#define RWGLOBAL_VAR_API                extern				// Someone else has defined the variable.
	#endif // _RW_IMPL
#endif // _RWDLLL

#ifdef _SFLDLL
	#ifdef _SFL_EXPORT_IMPL
		#define FOUNDATION_API __declspec( dllexport )
		//		#pragma message("FOUNDATION_API: dllexport")
		#define FOUNDATION_GLOBAL_FUNC_API(rettype)	extern "C" rettype __declspec(dllexport) 
	#else
		#define FOUNDATION_API __declspec( dllimport ) 
		//      #pragma message("FOUNDATION_API: dllimport")
		// Reference to a GLOBAL Function 
		#define FOUNDATION_GLOBAL_FUNC_API(rettype)	extern "C" rettype	__declspec(dllimport)
	#endif
#else //  !_SFLDLL
	#define FOUNDATION_API
	// Reference to a GLOBAL Function, these must be inline definitions with no 
	// function prototype.
	#define FOUNDATION_GLOBAL_FUNC_API(rettype)     extern "C" rettype __cdecl // Don't mangle the name. Must use __cdecl here.

#endif

#ifdef _SFLEXDLL
	#ifdef _SFLEX_EXPORT_IMPL
		#define FOUNDATIONEX_API __declspec( dllexport )
		//		#pragma message("FOUNDATION_API: dllexport")
		#define FOUNDATIONEX_GLOBAL_FUNC_API(rettype)	extern "C" rettype __declspec(dllexport) 
	#else
		#define FOUNDATIONEX_API __declspec( dllimport ) 
		//      #pragma message("FOUNDATION_API: dllimport")
		// Reference to a GLOBAL Function 
		#define FOUNDATIONEX_GLOBAL_FUNC_API(rettype)	extern "C" rettype	__declspec(dllimport)
	#endif
#else //  !_SFLDLL
	#define FOUNDATIONEX_API
	// Reference to a GLOBAL Function, these must be inline definitions with no 
	// function prototype.
	#define FOUNDATIONEX_GLOBAL_FUNC_API(rettype)     extern "C" rettype __cdecl // Don't mangle the name. Must use __cdecl here.

#endif // _SFLEXDLL

#ifdef _GXDLL
	#ifdef _OG_EXPORT_IMPL
		#define GRID_API __declspec( dllexport )
//		#pragma message("GRID_API: dllexport")
	#else
		#define GRID_API __declspec( dllimport ) 
//		#pragma message("GRID_API: dllimport")
	#endif
#else //  !_GXDLL
	#define GRID_API
#endif

#ifdef _OGEXDLL
	#ifdef _OGEX_EXPORT_IMPL
		#define GRIDEX_API __declspec( dllexport )
//		#pragma message("GRID_API: dllexport")
	#else
		#define GRIDEX_API __declspec( dllimport ) 
//		#pragma message("GRID_API: dllimport")
	#endif
#else //  !_GXEXDLL
	#define GRIDEX_API
#endif // _GXEXDLL

#ifdef _SECDLL
	#ifdef _OT_EXPORT_IMPL
		#define TOOLKIT_API __declspec( dllexport )
//		#pragma message("TOOLKIT_API: dllexport")
	#else
		#define TOOLKIT_API __declspec( dllimport ) 
//		#pragma message("TOOLKIT_API: dllimport")
	#endif
#else //  !_SECDLL
	#define TOOLKIT_API
#endif

#ifdef _OBJCHART_DLL
	#ifdef _OC_EXPORT_IMPL
		#define CHART_API __declspec( dllexport )
//		#pragma message("CHART_API: dllexport")
	#else
		#define CHART_API __declspec( dllimport ) 
//		#pragma message("CHART_API: dllimport")
	#endif
#else //  !_OBJCHART_DLL
	#define CHART_API
#endif

#ifdef _OBJCHART_UT_DLL
	#ifdef _OCUT_EXPORT_IMPL
		#define CHART_UT_API __declspec( dllexport )
//		#pragma message("CHART_UT_API: dllexport")
	#else
		#define CHART_UT_API __declspec( dllimport ) 
//		#pragma message("CHART_UT_API: dllimport")
	#endif
#else //  !_OBJCHART_UT_DLL
	#define CHART_UT_API
#endif

#ifdef _SECEDITDLL
	#ifdef _OE_EXPORT_IMPL
		#define EDIT_API __declspec( dllexport )
//		#pragma message("EDIT_API: dllexport")
	#else
		#define EDIT_API __declspec( dllimport ) 
//		#pragma message("EDIT_API: dllimport")
	#endif
#else //  !_SECEDITDLL
	#define EDIT_API
#endif

#ifdef _OVDLL
	#ifdef _OV_EXPORT_IMPL
		#define VIEWS_API __declspec( dllexport )
//		#pragma message("VIEWS_API: dllexport")
	#else
		#define VIEWS_API __declspec( dllimport ) 
//		#pragma message("VIEWS_API: dllimport")
	#endif
#else //  !_OVDLL
	#define VIEWS_API
#endif

#ifdef _GXDLL
	#ifdef _OGXDLL_IMPL
		// Exporting from lib
		#define GRIDX_API __declspec( dllexport )
//		#pragma message("GRIDX_API: dllexport")
	#else
		// Importing to ocx
		#define GRIDX_API __declspec( dllimport ) 
//		#pragma message("GRIDX_API: dllimport")
	#endif
#else //  !_GXDLL
	#define GRIDX_API
#endif

#ifdef _GXDLL
	#ifdef _OGXOGODLL_IMPL
		// Exporting from lib
		#define GRIDX_OGO_API __declspec( dllexport )
//		#pragma message("GRIDX_OGO_API: dllexport")
	#else
		// Importing to ocx
		#define GRIDX_OGO_API __declspec( dllimport ) 
//		#pragma message("GRIDX_OGO_API: dllimport")
	#endif
#else //  !_GXDLL
	#define GRIDX_OGO_API
#endif

#ifdef _GXDLL
	#ifdef _OGXDBDLL_IMPL
		// Exporting from lib
		#define GRIDX_DB_API __declspec( dllexport )
//		#pragma message("GRIDX_DB_API: dllexport")
	#else
		// Importing to ocx
		#define GRIDX_DB_API __declspec( dllimport ) 
//		#pragma message("GRIDX_DB_API: dllimport")
	#endif
#else //  !_GXDLL
	#define GRIDX_DB_API
#endif

#ifdef _GXDLL
	#ifdef _OGXADODLL_IMPL
		// Exporting from lib
		#define GRIDX_ADO_API __declspec( dllexport )
//		#pragma message("GRIDX_ADO_API: dllexport")
	#else
		// Importing to ocx
		#define GRIDX_ADO_API __declspec( dllimport ) 
//		#pragma message("GRIDX_ADO_API: dllimport")
	#endif
#else //  !_GXDLL
	#define GRIDX_ADO_API
#endif

#ifdef _GXDLL
	#ifdef _OGXDAODLL_IMPL
		// Exporting from lib
		#define GRIDX_DAO_API __declspec( dllexport )
//		#pragma message("GRIDX_DAO_API: dllexport")
	#else
		// Importing to ocx
		#define GRIDX_DAO_API __declspec( dllimport ) 
//		#pragma message("GRIDX_DAO_API: dllimport")
	#endif
#else //  !_GXDLL
	#define GRIDX_DAO_API
#endif

/////////////////////////////////////////////////////////////////////////////
//
// DECLARE_... MACROS [DEPENDENT ON EXPORT MACROS ABOVE]
//
/////////////////////////////////////////////////////////////////////////////
#ifdef _SFLDLL

/////////////////////////////////////////////////////////////////////////////
// Window message map handling

	#if(_MSC_VER >= 1310) // Visual Studio 2003 +

		#ifdef _AFXDLL
			#define FOUNDATION_DECLARE_MESSAGE_MAP() \
			private: \
				static const AFX_MSGMAP_ENTRY _messageEntries[]; \
			protected: \
				static const AFX_MSGMAP messageMap; \
				FOUNDATION_API static const AFX_MSGMAP* PASCAL GetThisMessageMap(); \
				FOUNDATION_API virtual const AFX_MSGMAP* GetMessageMap() const; \

		#else // !_AFXDLL
			#define FOUNDATION_DECLARE_MESSAGE_MAP() \
			private: \
				static const AFX_MSGMAP_ENTRY _messageEntries[]; \
			protected: \
				static const AFX_MSGMAP messageMap; \
				FOUNDATION_API virtual const AFX_MSGMAP* GetMessageMap() const; \

		#endif

	#elif(_MSC_VER == 1200) // MSVC6

		#ifdef _AFXDLL
			#define FOUNDATION_DECLARE_MESSAGE_MAP() \
			private: \
				static const AFX_MSGMAP_ENTRY _messageEntries[]; \
			protected: \
				static AFX_DATA const AFX_MSGMAP messageMap; \
				FOUNDATION_API static const AFX_MSGMAP* PASCAL _GetBaseMessageMap(); \
				FOUNDATION_API virtual const AFX_MSGMAP* GetMessageMap() const; \

		#else
			#define FOUNDATION_DECLARE_MESSAGE_MAP() \
			private: \
				static const AFX_MSGMAP_ENTRY _messageEntries[]; \
			protected: \
				static AFX_DATA const AFX_MSGMAP messageMap; \
				FOUNDATION_API virtual const AFX_MSGMAP* GetMessageMap() const; \

		#endif


	#else // !_MSC_VER >= 1310

		#define FOUNDATION_DECLARE_MESSAGE_MAP()			DECLARE_MESSAGE_MAP()

	#endif

	//////////////////////////////////////////////////////////////////////////////
	// Helper macros for declaring CRuntimeClass compatible classes
	#if(_MSC_VER >= 1310) 

		#ifdef _AFXDLL
			#define FOUNDATION_DECLARE_DYNAMIC(class_name) \
			protected: \
				FOUNDATION_API static CRuntimeClass* PASCAL _GetBaseClass(); \
			public: \
				static const CRuntimeClass class##class_name; \
				FOUNDATION_API static CRuntimeClass* PASCAL GetThisClass(); \
				FOUNDATION_API virtual CRuntimeClass* GetRuntimeClass() const;
			
			#define _FOUNDATION_DECLARE_DYNAMIC(class_name) \
			protected: \
				FOUNDATION_API static CRuntimeClass* PASCAL _GetBaseClass(); \
			public: \
				static CRuntimeClass class##class_name; \
				FOUNDATION_API static CRuntimeClass* PASCAL GetThisClass(); \
				FOUNDATION_API virtual CRuntimeClass* GetRuntimeClass() const; 

		#else // !_AFXDLL

			#define FOUNDATION_DECLARE_DYNAMIC(class_name) \
			public: \
				static const CRuntimeClass class##class_name; \
				FOUNDATION_API virtual CRuntimeClass* GetRuntimeClass() const;
			
			#define _FOUNDATION_DECLARE_DYNAMIC(class_name) \
			public: \
				static CRuntimeClass class##class_name; \
				FOUNDATION_API virtual CRuntimeClass* GetRuntimeClass() const;

		#endif // MFC DLL/LIB

	#elif(_MSC_VER == 1200)

		#ifdef _AFXDLL
			#define FOUNDATION_DECLARE_DYNAMIC(class_name) \
			protected: \
				FOUNDATION_API static CRuntimeClass* PASCAL _GetBaseClass(); \
			public: \
				static const AFX_DATA CRuntimeClass class##class_name; \
				FOUNDATION_API virtual CRuntimeClass* GetRuntimeClass() const; \

			#define _FOUNDATION_DECLARE_DYNAMIC(class_name) \
			protected: \
				FOUNDATION_API static CRuntimeClass* PASCAL _GetBaseClass(); \
			public: \
				static AFX_DATA CRuntimeClass class##class_name; \
				FOUNDATION_API virtual CRuntimeClass* GetRuntimeClass() const; \

		#else
			#define FOUNDATION_DECLARE_DYNAMIC(class_name) \
			public: \
				static const AFX_DATA CRuntimeClass class##class_name; \
				FOUNDATION_API virtual CRuntimeClass* GetRuntimeClass() const; \

			#define _FOUNDATION_DECLARE_DYNAMIC(class_name) \
			public: \
				static AFX_DATA CRuntimeClass class##class_name; \
				FOUNDATION_API virtual CRuntimeClass* GetRuntimeClass() const; \

		#endif // _AFXDLL

	#else

		#define FOUNDATION_DECLARE_DYNAMIC(class_name)	DECLARE_DYNAMIC(class_name)

	#endif // Declare Dynamic

		// not serializable, but dynamically constructable
		#define FOUNDATION_DECLARE_DYNCREATE(class_name) \
			FOUNDATION_DECLARE_DYNAMIC(class_name) \
			FOUNDATION_API static CObject* PASCAL CreateObject();

		#define _FOUNDATION_DECLARE_DYNCREATE(class_name) \
			_FOUNDATION_DECLARE_DYNAMIC(class_name) \
			FOUNDATION_API static CObject* PASCAL CreateObject();

		#define FOUNDATION_DECLARE_SERIAL(class_name) \
			_FOUNDATION_DECLARE_DYNCREATE(class_name) \
			AFX_API friend FOUNDATION_API CArchive& AFXAPI operator>>(CArchive& ar, class_name* &pOb);

	// end Helper Macros

#else // !_SFLDLL

	#define FOUNDATION_DECLARE_MESSAGE_MAP()			DECLARE_MESSAGE_MAP()
	#define FOUNDATION_DECLARE_DYNAMIC(class_name)		DECLARE_DYNAMIC(class_name)
	#define FOUNDATION_DECLARE_DYNCREATE(class_name)	DECLARE_DYNCREATE(class_name)
	#define FOUNDATION_DECLARE_SERIAL(class_name)		DECLARE_SERIAL(class_name)
	
#endif // _SFLDLL

//---------------------------------------------------------------------------
#ifdef _SFLEXDLL

/////////////////////////////////////////////////////////////////////////////
// Window message map handling

	#if(_MSC_VER >= 1310) // Visual Studio 2003 +

		#ifdef _AFXDLL
			#define FOUNDATIONEX_DECLARE_MESSAGE_MAP() \
			private: \
				static const AFX_MSGMAP_ENTRY _messageEntries[]; \
			protected: \
				static const AFX_MSGMAP messageMap; \
				FOUNDATIONEX_API static const AFX_MSGMAP* PASCAL GetThisMessageMap(); \
				FOUNDATIONEX_API virtual const AFX_MSGMAP* GetMessageMap() const; \

		#else // !_AFXDLL
			#define FOUNDATIONEX_DECLARE_MESSAGE_MAP() \
			private: \
				static const AFX_MSGMAP_ENTRY _messageEntries[]; \
			protected: \
				static const AFX_MSGMAP messageMap; \
				FOUNDATIONEX_API virtual const AFX_MSGMAP* GetMessageMap() const; \

		#endif

	#elif(_MSC_VER == 1200) // MSVC6

		#ifdef _AFXDLL
			#define FOUNDATIONEX_DECLARE_MESSAGE_MAP() \
			private: \
				static const AFX_MSGMAP_ENTRY _messageEntries[]; \
			protected: \
				static AFX_DATA const AFX_MSGMAP messageMap; \
				FOUNDATIONEX_API static const AFX_MSGMAP* PASCAL _GetBaseMessageMap(); \
				FOUNDATIONEX_API virtual const AFX_MSGMAP* GetMessageMap() const; \

		#else
			#define FOUNDATIONEX_DECLARE_MESSAGE_MAP() \
			private: \
				static const AFX_MSGMAP_ENTRY _messageEntries[]; \
			protected: \
				static AFX_DATA const AFX_MSGMAP messageMap; \
				FOUNDATIONEX_API virtual const AFX_MSGMAP* GetMessageMap() const; \

		#endif


	#else // !_MSC_VER >= 1310

		#define FOUNDATIONEX_DECLARE_MESSAGE_MAP()			DECLARE_MESSAGE_MAP()

	#endif

	//////////////////////////////////////////////////////////////////////////////
	// Helper macros for declaring CRuntimeClass compatible classes
	#if(_MSC_VER >= 1310) 

		#ifdef _AFXDLL
			#define FOUNDATIONEX_DECLARE_DYNAMIC(class_name) \
			protected: \
				FOUNDATIONEX_API static CRuntimeClass* PASCAL _GetBaseClass(); \
			public: \
				static const CRuntimeClass class##class_name; \
				FOUNDATIONEX_API static CRuntimeClass* PASCAL GetThisClass(); \
				FOUNDATIONEX_API virtual CRuntimeClass* GetRuntimeClass() const;
			
			#define _FOUNDATIONEX_DECLARE_DYNAMIC(class_name) \
			protected: \
				FOUNDATIONEX_API static CRuntimeClass* PASCAL _GetBaseClass(); \
			public: \
				static CRuntimeClass class##class_name; \
				FOUNDATIONEX_API static CRuntimeClass* PASCAL GetThisClass(); \
				FOUNDATIONEX_API virtual CRuntimeClass* GetRuntimeClass() const; 

		#else // !_AFXDLL

			#define FOUNDATIONEX_DECLARE_DYNAMIC(class_name) \
			public: \
				static const CRuntimeClass class##class_name; \
				FOUNDATIONEX_API virtual CRuntimeClass* GetRuntimeClass() const;
			
			#define _FOUNDATIONEX_DECLARE_DYNAMIC(class_name) \
			public: \
				static CRuntimeClass class##class_name; \
				FOUNDATIONEX_API virtual CRuntimeClass* GetRuntimeClass() const;

		#endif // MFC DLL/LIB

	#elif(_MSC_VER == 1200)

		#ifdef _AFXDLL
			#define FOUNDATIONEX_DECLARE_DYNAMIC(class_name) \
			protected: \
				FOUNDATIONEX_API static CRuntimeClass* PASCAL _GetBaseClass(); \
			public: \
				static const AFX_DATA CRuntimeClass class##class_name; \
				FOUNDATIONEX_API virtual CRuntimeClass* GetRuntimeClass() const; \

			#define _FOUNDATIONEX_DECLARE_DYNAMIC(class_name) \
			protected: \
				FOUNDATIONEX_API static CRuntimeClass* PASCAL _GetBaseClass(); \
			public: \
				static AFX_DATA CRuntimeClass class##class_name; \
				FOUNDATIONEX_API virtual CRuntimeClass* GetRuntimeClass() const; \

		#else
			#define FOUNDATIONEX_DECLARE_DYNAMIC(class_name) \
			public: \
				static const AFX_DATA CRuntimeClass class##class_name; \
				FOUNDATIONEX_API virtual CRuntimeClass* GetRuntimeClass() const; \

			#define _FOUNDATIONEX_DECLARE_DYNAMIC(class_name) \
			public: \
				static AFX_DATA CRuntimeClass class##class_name; \
				FOUNDATIONEX_API virtual CRuntimeClass* GetRuntimeClass() const; \

		#endif // _AFXDLL

	#else

		#define FOUNDATIONEX_DECLARE_DYNAMIC(class_name)	DECLARE_DYNAMIC(class_name)

	#endif // Declare Dynamic

		// not serializable, but dynamically constructable
		#define FOUNDATIONEX_DECLARE_DYNCREATE(class_name) \
			FOUNDATIONEX_DECLARE_DYNAMIC(class_name) \
			FOUNDATIONEX_API static CObject* PASCAL CreateObject();

		#define _FOUNDATIONEX_DECLARE_DYNCREATE(class_name) \
			_FOUNDATIONEX_DECLARE_DYNAMIC(class_name) \
			FOUNDATIONEX_API static CObject* PASCAL CreateObject();

		#define FOUNDATIONEX_DECLARE_SERIAL(class_name) \
			_FOUNDATIONEX_DECLARE_DYNCREATE(class_name) \
			AFX_API friend FOUNDATIONEX_API CArchive& AFXAPI operator>>(CArchive& ar, class_name* &pOb);

	// end Helper Macros

#else // !_SFLEXDLL

	#define FOUNDATIONEX_DECLARE_MESSAGE_MAP()			DECLARE_MESSAGE_MAP()
	#define FOUNDATIONEX_DECLARE_DYNAMIC(class_name)		DECLARE_DYNAMIC(class_name)
	#define FOUNDATIONEX_DECLARE_DYNCREATE(class_name)	DECLARE_DYNCREATE(class_name)
	#define FOUNDATIONEX_DECLARE_SERIAL(class_name)		DECLARE_SERIAL(class_name)
	
#endif // _SFLEXDLL
//---------------------------------------------------------------------------


#ifdef _GXDLL

/////////////////////////////////////////////////////////////////////////////
// Window message map handling

	#if(_MSC_VER >= 1310) // Visual Studio 2003 +

		#ifdef _AFXDLL
			#define GRID_DECLARE_MESSAGE_MAP() \
			private: \
				static const AFX_MSGMAP_ENTRY _messageEntries[]; \
			protected: \
				static const AFX_MSGMAP messageMap; \
				GRID_API static const AFX_MSGMAP* PASCAL GetThisMessageMap(); \
				GRID_API virtual const AFX_MSGMAP* GetMessageMap() const; \

		#else
			#define GRID_DECLARE_MESSAGE_MAP() \
			private: \
				static const AFX_MSGMAP_ENTRY _messageEntries[]; \
			protected: \
				static const AFX_MSGMAP messageMap; \
				GRID_API virtual const AFX_MSGMAP* GetMessageMap() const; \

		#endif

	#elif(_MSC_VER == 1200) // MSVC6

		#ifdef _AFXDLL
			#define GRID_DECLARE_MESSAGE_MAP() \
			private: \
				static const AFX_MSGMAP_ENTRY _messageEntries[]; \
			protected: \
				static AFX_DATA const AFX_MSGMAP messageMap; \
				GRID_API static const AFX_MSGMAP* PASCAL _GetBaseMessageMap(); \
				GRID_API virtual const AFX_MSGMAP* GetMessageMap() const; \

		#else
			#define GRID_DECLARE_MESSAGE_MAP() \
			private: \
				static const AFX_MSGMAP_ENTRY _messageEntries[]; \
			protected: \
				static AFX_DATA const AFX_MSGMAP messageMap; \
				GRID_API virtual const AFX_MSGMAP* GetMessageMap() const; \

		#endif

	#else // !_MSC_VER >= 1310

		#define GRID_DECLARE_MESSAGE_MAP()			DECLARE_MESSAGE_MAP()

	#endif

	//////////////////////////////////////////////////////////////////////////////
	// Helper macros for declaring CRuntimeClass compatible classes
	#if(_MSC_VER >= 1310)

		#ifdef _AFXDLL
			#define GRID_DECLARE_DYNAMIC(class_name) \
			protected: \
				GRID_API static CRuntimeClass* PASCAL _GetBaseClass(); \
			public: \
				static const CRuntimeClass class##class_name; \
				GRID_API static CRuntimeClass* PASCAL GetThisClass(); \
				GRID_API virtual CRuntimeClass* GetRuntimeClass() const; 
			
			#define _GRID_DECLARE_DYNAMIC(class_name) \
			protected: \
				GRID_API static CRuntimeClass* PASCAL _GetBaseClass(); \
			public: \
				static CRuntimeClass class##class_name; \
				GRID_API static CRuntimeClass* PASCAL GetThisClass(); \
				GRID_API virtual CRuntimeClass* GetRuntimeClass() const; 

		#else // !_AFXDLL

			#define GRID_DECLARE_DYNAMIC(class_name) \
			public: \
				static const CRuntimeClass class##class_name; \
				GRID_API virtual CRuntimeClass* GetRuntimeClass() const;
			
			#define _GRID_DECLARE_DYNAMIC(class_name) \
			public: \
				static CRuntimeClass class##class_name; \
				GRID_API virtual CRuntimeClass* GetRuntimeClass() const;

		#endif // MFC DLL/LIB

	#elif(_MSC_VER == 1200)

		#ifdef _AFXDLL
			#define GRID_DECLARE_DYNAMIC(class_name) \
			protected: \
				GRID_API static CRuntimeClass* PASCAL _GetBaseClass(); \
			public: \
				static const AFX_DATA CRuntimeClass class##class_name; \
				GRID_API virtual CRuntimeClass* GetRuntimeClass() const; \

			#define _GRID_DECLARE_DYNAMIC(class_name) \
			protected: \
				GRID_API static CRuntimeClass* PASCAL _GetBaseClass(); \
			public: \
				static AFX_DATA CRuntimeClass class##class_name; \
				GRID_API virtual CRuntimeClass* GetRuntimeClass() const; \

		#else
			#define GRID_DECLARE_DYNAMIC(class_name) \
			public: \
				static const AFX_DATA CRuntimeClass class##class_name; \
				GRID_API virtual CRuntimeClass* GetRuntimeClass() const; \

			#define _GRID_DECLARE_DYNAMIC(class_name) \
			public: \
				static AFX_DATA CRuntimeClass class##class_name; \
				GRID_API virtual CRuntimeClass* GetRuntimeClass() const; \

		#endif // _AFXDLL

	#else

		#define GRID_DECLARE_DYNAMIC(class_name)	DECLARE_DYNAMIC(class_name)

	#endif // Declare Dynamic
		
		// not serializable, but dynamically constructable
		#define GRID_DECLARE_DYNCREATE(class_name) \
			GRID_DECLARE_DYNAMIC(class_name) \
			GRID_API static CObject* PASCAL CreateObject();
		
		#define _GRID_DECLARE_DYNCREATE(class_name) \
			_GRID_DECLARE_DYNAMIC(class_name) \
			GRID_API static CObject* PASCAL CreateObject();

		#define GRID_DECLARE_SERIAL(class_name) \
			_GRID_DECLARE_DYNCREATE(class_name) \
			AFX_API friend GRID_API CArchive& AFXAPI operator>>(CArchive& ar, class_name* &pOb);

		#define GRID_DECLARE_CONTROL(class_name) \
			protected: \
				GRID_API static CGXControlClass* PASCAL _GetControlBaseClass(); \
			public: \
				static GX_DATA CGXControlClass ctrl##class_name; \
				GRID_API virtual CGXControlClass* GetControlClass() const; \

		#define GRID_IMPLEMENT_CONTROL(class_name, base_class_name) \
			CGXControlClass* PASCAL class_name::_GetControlBaseClass() \
				{ return CONTROL_CLASS(base_class_name); } \
				GX_DATADEF CGXControlClass class_name::ctrl##class_name = { \
			#class_name, &class_name::_GetControlBaseClass }; \
			CGXControlClass* class_name::GetControlClass() const \
				{ return &class_name::ctrl##class_name; } \


		//Declare Register/////////////////////////////////
		#define GRID_DECLARE_REGISTER() \
		public: \
			GRID_API static LPCTSTR AFXAPI RegisterClass(); \
			GRID_API static void AFXAPI UnregisterClass(); \
			GRID_API static LPCTSTR AFXAPI RegisterClass(HINSTANCE hInstance); \
			GRID_API static void AFXAPI UnregisterClass(HINSTANCE hInstance); \
		protected: \
			GRID_API static LRESULT CALLBACK AFX_EXPORT WndProcHook(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam); \
			GRID_API virtual void PostNcDestroy();
		// END GRID_DECLARE_REGISTER


		#ifdef _WIN64

			#define GRID_IMPLEMENT_REGISTER(class_name, _style, icon, cursor, background) \
				LPCTSTR AFXAPI class_name::RegisterClass() \
				{ \
					WNDCLASS wndcls;  \
					LPCTSTR szName = _T(#class_name) ; \
					if (::GetClassInfo(AfxGetInstanceHandle(), szName, &wndcls)) \
						return szName; \
					wndcls.style = _style ; \
					wndcls.lpfnWndProc = class_name::WndProcHook ; \
					wndcls.cbClsExtra = wndcls.cbWndExtra = 0 ; \
					wndcls.hInstance = AfxGetInstanceHandle() ; \
					wndcls.hIcon = icon ; \
					wndcls.hCursor = cursor ; \
					wndcls.hbrBackground = background ; \
					wndcls.lpszMenuName = NULL ; \
					wndcls.lpszClassName = szName ; \
					if (!::RegisterClass(&wndcls)) \
						AfxThrowResourceException() ; \
					return szName ;  } \
				LPCTSTR AFXAPI class_name::RegisterClass(HINSTANCE hInstance) \
				{ \
					WNDCLASS wndcls;  \
					LPCTSTR szName = _T(#class_name) ; \
					if (::GetClassInfo(hInstance, szName, &wndcls)) \
						return szName; \
					wndcls.style = _style ; \
					wndcls.lpfnWndProc = class_name::WndProcHook ; \
					wndcls.cbClsExtra = wndcls.cbWndExtra = 0 ; \
					wndcls.hInstance = hInstance ; \
					wndcls.hIcon = icon ; \
					wndcls.hCursor = cursor ; \
					wndcls.hbrBackground = background ; \
					wndcls.lpszMenuName = NULL ; \
					wndcls.lpszClassName = szName ; \
					if (!::RegisterClass(&wndcls)) \
						AfxThrowResourceException() ; \
					return szName ;  } \
				LRESULT CALLBACK AFX_EXPORT class_name::WndProcHook(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam) \
				{ \
					class_name * pWnd = new class_name(); \
					pWnd->Attach(hWnd); \
					GXGetAppState()->m_ctlusrState.m_ctrlmap[pWnd] = 1; \
					::SetWindowLongPtr(hWnd, GWLP_WNDPROC, (SEC_LONG)AfxWndProc); \
					return ::CallWindowProc(AfxWndProc, hWnd, msg, wParam, lParam); } \
				void AFXAPI class_name::UnregisterClass() \
				{ \
					::UnregisterClass( _T(#class_name) , AfxGetInstanceHandle() );  } \
				void AFXAPI class_name::UnregisterClass(HINSTANCE hInstance) \
				{ \
					::UnregisterClass( _T(#class_name) , hInstance );  } \
				void class_name::PostNcDestroy() \
				{ \
					WORD w; \
					if (GXGetAppState()->m_ctlusrState.m_ctrlmap.Lookup(this, w)) \
					{ \
						delete this; \
						GXGetAppState()->m_ctlusrState.m_ctrlmap.RemoveKey(this); \
					} \
				}
			// END GRID_IMPLEMENT_REGISTER

		#else	//WIN32

			#define GRID_IMPLEMENT_REGISTER(class_name, _style, icon, cursor, background) \
				LPCTSTR AFXAPI class_name::RegisterClass() \
				{ \
					WNDCLASS wndcls;  \
					LPCTSTR szName = _T(#class_name) ; \
					if (::GetClassInfo(AfxGetInstanceHandle(), szName, &wndcls)) \
						return szName; \
					wndcls.style = _style ; \
					wndcls.lpfnWndProc = class_name::WndProcHook ; \
					wndcls.cbClsExtra = wndcls.cbWndExtra = 0 ; \
					wndcls.hInstance = AfxGetInstanceHandle() ; \
					wndcls.hIcon = icon ; \
					wndcls.hCursor = cursor ; \
					wndcls.hbrBackground = background ; \
					wndcls.lpszMenuName = NULL ; \
					wndcls.lpszClassName = szName ; \
					if (!::RegisterClass(&wndcls)) \
						AfxThrowResourceException() ; \
					return szName ;  } \
				LPCTSTR AFXAPI class_name::RegisterClass(HINSTANCE hInstance) \
				{ \
					WNDCLASS wndcls;  \
					LPCTSTR szName = _T(#class_name) ; \
					if (::GetClassInfo(hInstance, szName, &wndcls)) \
						return szName; \
					wndcls.style = _style ; \
					wndcls.lpfnWndProc = class_name::WndProcHook ; \
					wndcls.cbClsExtra = wndcls.cbWndExtra = 0 ; \
					wndcls.hInstance = hInstance ; \
					wndcls.hIcon = icon ; \
					wndcls.hCursor = cursor ; \
					wndcls.hbrBackground = background ; \
					wndcls.lpszMenuName = NULL ; \
					wndcls.lpszClassName = szName ; \
					if (!::RegisterClass(&wndcls)) \
						AfxThrowResourceException() ; \
					return szName ;  } \
				LRESULT CALLBACK AFX_EXPORT class_name::WndProcHook(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam) \
				{ \
					class_name * pWnd = new class_name(); \
					pWnd->Attach(hWnd); \
					GXGetAppState()->m_ctlusrState.m_ctrlmap[pWnd] = 1; \
					::SetWindowLong(hWnd, GWL_WNDPROC, (DWORD)AfxWndProc); \
					return ::CallWindowProc(AfxWndProc, hWnd, msg, wParam, lParam); } \
				void AFXAPI class_name::UnregisterClass() \
				{ \
					::UnregisterClass( _T(#class_name) , AfxGetInstanceHandle() );  } \
				void AFXAPI class_name::UnregisterClass(HINSTANCE hInstance) \
				{ \
					::UnregisterClass( _T(#class_name) , hInstance );  } \
				void class_name::PostNcDestroy() \
				{ \
					WORD w; \
					if (GXGetAppState()->m_ctlusrState.m_ctrlmap.Lookup(this, w)) \
					{ \
						delete this; \
						GXGetAppState()->m_ctlusrState.m_ctrlmap.RemoveKey(this); \
					} \
				}
			// END GRID_IMPLEMENT_REGISTER

		#endif	//_WIN64
		//Declare Register/////////////////////////////////

	// end Helper Macros

#else // !_GXDLL Static Library

	#define GRID_DECLARE_MESSAGE_MAP()			DECLARE_MESSAGE_MAP()
	#define GRID_DECLARE_DYNAMIC(class_name)	DECLARE_DYNAMIC(class_name)
	#define GRID_DECLARE_DYNCREATE(class_name)	DECLARE_DYNCREATE(class_name)
	#define GRID_DECLARE_SERIAL(class_name)		DECLARE_SERIAL(class_name)

	#define GRID_DECLARE_CONTROL(class_name) \
		public: \
			static CGXControlClass GXNEAR ctrl##class_name; \
			virtual CGXControlClass* GetControlClass() const; \

	#define GRID_IMPLEMENT_CONTROL(class_name, base_class_name) \
		CGXControlClass GXNEAR class_name::ctrl##class_name = { \
		#class_name, CONTROL_CLASS(base_class_name) }; \
		CGXControlClass* class_name::GetControlClass() const \
			{ return &class_name::ctrl##class_name; } \

	//Declare Register/////////////////////////////////
	#define GRID_DECLARE_REGISTER() \
		public: \
			GRID_API static LPCTSTR AFXAPI RegisterClass(); \
			GRID_API static void AFXAPI UnregisterClass(); \
			GRID_API static LPCTSTR AFXAPI RegisterClass(HINSTANCE hInstance); \
			GRID_API static void AFXAPI UnregisterClass(HINSTANCE hInstance); \
			GRID_API static CMapPtrToWord GXNEAR _gxregmap; \
		protected: \
			GRID_API static LRESULT CALLBACK AFX_EXPORT WndProcHook(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam); \
			GRID_API virtual void PostNcDestroy();
		// END GRID_DECLARE_REGISTER

	#ifdef _WIN64

		#define GRID_IMPLEMENT_REGISTER(class_name, _style, icon, cursor, background) \
			CMapPtrToWord GXNEAR class_name::_gxregmap; \
			LPCTSTR AFXAPI class_name::RegisterClass() \
			{ \
				WNDCLASS wndcls;  \
				LPCTSTR szName = _T(#class_name) ; \
				if (::GetClassInfo(AfxGetInstanceHandle(), szName, &wndcls)) \
					return szName; \
				wndcls.style = _style ; \
				wndcls.lpfnWndProc = class_name::WndProcHook ; \
				wndcls.cbClsExtra = wndcls.cbWndExtra = 0 ; \
				wndcls.hInstance = AfxGetInstanceHandle() ; \
				wndcls.hIcon = icon ; \
				wndcls.hCursor = cursor ; \
				wndcls.hbrBackground = background ; \
				wndcls.lpszMenuName = NULL ; \
				wndcls.lpszClassName = szName ; \
				if (!::RegisterClass(&wndcls)) \
					AfxThrowResourceException() ; \
				return szName ;  } \
			LPCTSTR AFXAPI class_name::RegisterClass(HINSTANCE hInstance) \
			{ \
				WNDCLASS wndcls;  \
				LPCTSTR szName = _T(#class_name) ; \
				if (::GetClassInfo(hInstance, szName, &wndcls)) \
					return szName; \
				wndcls.style = _style ; \
				wndcls.lpfnWndProc = class_name::WndProcHook ; \
				wndcls.cbClsExtra = wndcls.cbWndExtra = 0 ; \
				wndcls.hInstance = hInstance ; \
				wndcls.hIcon = icon ; \
				wndcls.hCursor = cursor ; \
				wndcls.hbrBackground = background ; \
				wndcls.lpszMenuName = NULL ; \
				wndcls.lpszClassName = szName ; \
				if (!::RegisterClass(&wndcls)) \
					AfxThrowResourceException() ; \
				return szName ;  } \
			LRESULT CALLBACK AFX_EXPORT class_name::WndProcHook(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam) \
			{ \
				class_name * pWnd = new class_name(); \
				pWnd->Attach(hWnd); \
				_gxregmap[pWnd] = 1; \
				::SetWindowLongPtr(hWnd, GWLP_WNDPROC, (SEC_LONG)AfxWndProc); \
				return ::CallWindowProc(AfxWndProc, hWnd, msg, wParam, lParam); } \
			void AFXAPI class_name::UnregisterClass() \
			{ \
				::UnregisterClass( _T(#class_name) , AfxGetInstanceHandle() );  } \
			void AFXAPI class_name::UnregisterClass(HINSTANCE hInstance) \
			{ \
				::UnregisterClass( _T(#class_name) , hInstance );  } \
			void class_name::PostNcDestroy() \
			{ \
				WORD w; \
				if (_gxregmap.Lookup(this, w)) \
				{ \
					delete this; \
					_gxregmap.RemoveKey(this); \
				} \
			}
		// END GRID_IMPLEMENT_REGISTER

	#else	//WIN32

		#define GRID_IMPLEMENT_REGISTER(class_name, _style, icon, cursor, background) \
			CMapPtrToWord GXNEAR class_name::_gxregmap; \
			LPCTSTR AFXAPI class_name::RegisterClass() \
			{ \
				WNDCLASS wndcls;  \
				LPCTSTR szName = _T(#class_name) ; \
				if (::GetClassInfo(AfxGetInstanceHandle(), szName, &wndcls)) \
					return szName; \
				wndcls.style = _style ; \
				wndcls.lpfnWndProc = class_name::WndProcHook ; \
				wndcls.cbClsExtra = wndcls.cbWndExtra = 0 ; \
				wndcls.hInstance = AfxGetInstanceHandle() ; \
				wndcls.hIcon = icon ; \
				wndcls.hCursor = cursor ; \
				wndcls.hbrBackground = background ; \
				wndcls.lpszMenuName = NULL ; \
				wndcls.lpszClassName = szName ; \
				if (!::RegisterClass(&wndcls)) \
					AfxThrowResourceException() ; \
				return szName ;  } \
			LPCTSTR AFXAPI class_name::RegisterClass(HINSTANCE hInstance) \
			{ \
				WNDCLASS wndcls;  \
				LPCTSTR szName = _T(#class_name) ; \
				if (::GetClassInfo(hInstance, szName, &wndcls)) \
					return szName; \
				wndcls.style = _style ; \
				wndcls.lpfnWndProc = class_name::WndProcHook ; \
				wndcls.cbClsExtra = wndcls.cbWndExtra = 0 ; \
				wndcls.hInstance = hInstance ; \
				wndcls.hIcon = icon ; \
				wndcls.hCursor = cursor ; \
				wndcls.hbrBackground = background ; \
				wndcls.lpszMenuName = NULL ; \
				wndcls.lpszClassName = szName ; \
				if (!::RegisterClass(&wndcls)) \
					AfxThrowResourceException() ; \
				return szName ;  } \
			LRESULT CALLBACK AFX_EXPORT class_name::WndProcHook(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam) \
			{ \
				class_name * pWnd = new class_name(); \
				pWnd->Attach(hWnd); \
				_gxregmap[pWnd] = 1; \
				::SetWindowLong(hWnd, GWL_WNDPROC, (DWORD)AfxWndProc); \
				return ::CallWindowProc(AfxWndProc, hWnd, msg, wParam, lParam); } \
			void AFXAPI class_name::UnregisterClass() \
			{ \
				::UnregisterClass( _T(#class_name) , AfxGetInstanceHandle() );  } \
			void AFXAPI class_name::UnregisterClass(HINSTANCE hInstance) \
			{ \
				::UnregisterClass( _T(#class_name) , hInstance );  } \
			void class_name::PostNcDestroy() \
			{ \
				WORD w; \
				if (_gxregmap.Lookup(this, w)) \
				{ \
					delete this; \
					_gxregmap.RemoveKey(this); \
				} \
			}
		// END GRID_IMPLEMENT_REGISTER

	#endif	// _WIN64

	//Declare Register/////////////////////////////////

#endif // GRID

//-------------------------------------------------------------------------------
#ifdef _OGEXDLL

/////////////////////////////////////////////////////////////////////////////
// Window message map handling

	#if(_MSC_VER >= 1310) // Visual Studio 2003 +

		#ifdef _AFXDLL
			#define GRIDEX_DECLARE_MESSAGE_MAP() \
			private: \
				static const AFX_MSGMAP_ENTRY _messageEntries[]; \
			protected: \
				static const AFX_MSGMAP messageMap; \
				GRIDEX_API static const AFX_MSGMAP* PASCAL GetThisMessageMap(); \
				GRIDEX_API virtual const AFX_MSGMAP* GetMessageMap() const; \

		#else
			#define GRIDEX_DECLARE_MESSAGE_MAP() \
			private: \
				static const AFX_MSGMAP_ENTRY _messageEntries[]; \
			protected: \
				static const AFX_MSGMAP messageMap; \
				GRIDEX_API virtual const AFX_MSGMAP* GetMessageMap() const; \

		#endif

	#elif(_MSC_VER == 1200) // MSVC6

		#ifdef _AFXDLL
			#define GRIDEX_DECLARE_MESSAGE_MAP() \
			private: \
				static const AFX_MSGMAP_ENTRY _messageEntries[]; \
			protected: \
				static AFX_DATA const AFX_MSGMAP messageMap; \
				GRIDEX_API static const AFX_MSGMAP* PASCAL _GetBaseMessageMap(); \
				GRIDEX_API virtual const AFX_MSGMAP* GetMessageMap() const; \

		#else
			#define GRIDEX_DECLARE_MESSAGE_MAP() \
			private: \
				static const AFX_MSGMAP_ENTRY _messageEntries[]; \
			protected: \
				static AFX_DATA const AFX_MSGMAP messageMap; \
				GRIDEX_API virtual const AFX_MSGMAP* GetMessageMap() const; \

		#endif

	#else // !_MSC_VER >= 1310

		#define GRIDEX_DECLARE_MESSAGE_MAP()			DECLARE_MESSAGE_MAP()

	#endif

	//////////////////////////////////////////////////////////////////////////////
	// Helper macros for declaring CRuntimeClass compatible classes
	#if(_MSC_VER >= 1310)

		#ifdef _AFXDLL
			#define GRIDEX_DECLARE_DYNAMIC(class_name) \
			protected: \
				GRIDEX_API static CRuntimeClass* PASCAL _GetBaseClass(); \
			public: \
				static const CRuntimeClass class##class_name; \
				GRIDEX_API static CRuntimeClass* PASCAL GetThisClass(); \
				GRIDEX_API virtual CRuntimeClass* GetRuntimeClass() const; 
			
			#define _GRIDEX_DECLARE_DYNAMIC(class_name) \
			protected: \
				GRIDEX_API static CRuntimeClass* PASCAL _GetBaseClass(); \
			public: \
				static CRuntimeClass class##class_name; \
				GRIDEX_API static CRuntimeClass* PASCAL GetThisClass(); \
				GRIDEX_API virtual CRuntimeClass* GetRuntimeClass() const; 

		#else // !_AFXDLL

			#define GRIDEX_DECLARE_DYNAMIC(class_name) \
			public: \
				static const CRuntimeClass class##class_name; \
				GRIDEX_API virtual CRuntimeClass* GetRuntimeClass() const;
			
			#define _GRIDEX_DECLARE_DYNAMIC(class_name) \
			public: \
				static CRuntimeClass class##class_name; \
				GRIDEX_API virtual CRuntimeClass* GetRuntimeClass() const;

		#endif // MFC DLL/LIB

	#elif(_MSC_VER == 1200)

		#ifdef _AFXDLL
			#define GRIDEX_DECLARE_DYNAMIC(class_name) \
			protected: \
				GRIDEX_API static CRuntimeClass* PASCAL _GetBaseClass(); \
			public: \
				static const AFX_DATA CRuntimeClass class##class_name; \
				GRIDEX_API virtual CRuntimeClass* GetRuntimeClass() const; \

			#define _GRIDEX_DECLARE_DYNAMIC(class_name) \
			protected: \
				GRIDEX_API static CRuntimeClass* PASCAL _GetBaseClass(); \
			public: \
				static AFX_DATA CRuntimeClass class##class_name; \
				GRIDEX_API virtual CRuntimeClass* GetRuntimeClass() const; \

		#else
			#define GRIDEX_DECLARE_DYNAMIC(class_name) \
			public: \
				static const AFX_DATA CRuntimeClass class##class_name; \
				GRIDEX_API virtual CRuntimeClass* GetRuntimeClass() const; \

			#define _GRIDEX_DECLARE_DYNAMIC(class_name) \
			public: \
				static AFX_DATA CRuntimeClass class##class_name; \
				GRIDEX_API virtual CRuntimeClass* GetRuntimeClass() const; \

		#endif // _AFXDLL

	#else

		#define GRIDEX_DECLARE_DYNAMIC(class_name)	DECLARE_DYNAMIC(class_name)

	#endif // Declare Dynamic
		
		// not serializable, but dynamically constructable
		#define GRIDEX_DECLARE_DYNCREATE(class_name) \
			GRIDEX_DECLARE_DYNAMIC(class_name) \
			GRIDEX_API static CObject* PASCAL CreateObject();
		
		#define _GRIDEX_DECLARE_DYNCREATE(class_name) \
			_GRIDEX_DECLARE_DYNAMIC(class_name) \
			GRIDEX_API static CObject* PASCAL CreateObject();

		#define GRIDEX_DECLARE_SERIAL(class_name) \
			_GRIDEX_DECLARE_DYNCREATE(class_name) \
			AFX_API friend GRIDEX_API CArchive& AFXAPI operator>>(CArchive& ar, class_name* &pOb);

		#define GRIDEX_DECLARE_CONTROL(class_name) \
			protected: \
				GRIDEX_API static CGXControlClass* PASCAL _GetControlBaseClass(); \
			public: \
				static GX_DATA CGXControlClass ctrl##class_name; \
				GRIDEX_API virtual CGXControlClass* GetControlClass() const; \

		#define GRIDEX_IMPLEMENT_CONTROL(class_name, base_class_name) \
			CGXControlClass* PASCAL class_name::_GetControlBaseClass() \
				{ return CONTROL_CLASS(base_class_name); } \
				GX_DATADEF CGXControlClass class_name::ctrl##class_name = { \
			#class_name, &class_name::_GetControlBaseClass }; \
			CGXControlClass* class_name::GetControlClass() const \
				{ return &class_name::ctrl##class_name; } \


		//Declare Register/////////////////////////////////
		#define GRIDEX_DECLARE_REGISTER() \
		public: \
			GRIDEX_API static LPCTSTR AFXAPI RegisterClass(); \
			GRIDEX_API static void AFXAPI UnregisterClass(); \
			GRIDEX_API static LPCTSTR AFXAPI RegisterClass(HINSTANCE hInstance); \
			GRIDEX_API static void AFXAPI UnregisterClass(HINSTANCE hInstance); \
		protected: \
			GRIDEX_API static LRESULT CALLBACK AFX_EXPORT WndProcHook(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam); \
			GRIDEX_API virtual void PostNcDestroy();
		// END GRIDEX_DECLARE_REGISTER


		#ifdef _WIN64

			#define GRIDEX_IMPLEMENT_REGISTER(class_name, _style, icon, cursor, background) \
				LPCTSTR AFXAPI class_name::RegisterClass() \
				{ \
					WNDCLASS wndcls;  \
					LPCTSTR szName = _T(#class_name) ; \
					if (::GetClassInfo(AfxGetInstanceHandle(), szName, &wndcls)) \
						return szName; \
					wndcls.style = _style ; \
					wndcls.lpfnWndProc = class_name::WndProcHook ; \
					wndcls.cbClsExtra = wndcls.cbWndExtra = 0 ; \
					wndcls.hInstance = AfxGetInstanceHandle() ; \
					wndcls.hIcon = icon ; \
					wndcls.hCursor = cursor ; \
					wndcls.hbrBackground = background ; \
					wndcls.lpszMenuName = NULL ; \
					wndcls.lpszClassName = szName ; \
					if (!::RegisterClass(&wndcls)) \
						AfxThrowResourceException() ; \
					return szName ;  } \
				LPCTSTR AFXAPI class_name::RegisterClass(HINSTANCE hInstance) \
				{ \
					WNDCLASS wndcls;  \
					LPCTSTR szName = _T(#class_name) ; \
					if (::GetClassInfo(hInstance, szName, &wndcls)) \
						return szName; \
					wndcls.style = _style ; \
					wndcls.lpfnWndProc = class_name::WndProcHook ; \
					wndcls.cbClsExtra = wndcls.cbWndExtra = 0 ; \
					wndcls.hInstance = hInstance ; \
					wndcls.hIcon = icon ; \
					wndcls.hCursor = cursor ; \
					wndcls.hbrBackground = background ; \
					wndcls.lpszMenuName = NULL ; \
					wndcls.lpszClassName = szName ; \
					if (!::RegisterClass(&wndcls)) \
						AfxThrowResourceException() ; \
					return szName ;  } \
				LRESULT CALLBACK AFX_EXPORT class_name::WndProcHook(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam) \
				{ \
					class_name * pWnd = new class_name(); \
					pWnd->Attach(hWnd); \
					GXGetAppState()->m_ctlusrState.m_ctrlmap[pWnd] = 1; \
					::SetWindowLongPtr(hWnd, GWLP_WNDPROC, (SEC_LONG)AfxWndProc); \
					return ::CallWindowProc(AfxWndProc, hWnd, msg, wParam, lParam); } \
				void AFXAPI class_name::UnregisterClass() \
				{ \
					::UnregisterClass( _T(#class_name) , AfxGetInstanceHandle() );  } \
				void AFXAPI class_name::UnregisterClass(HINSTANCE hInstance) \
				{ \
					::UnregisterClass( _T(#class_name) , hInstance );  } \
				void class_name::PostNcDestroy() \
				{ \
					WORD w; \
					if (GXGetAppState()->m_ctlusrState.m_ctrlmap.Lookup(this, w)) \
					{ \
						delete this; \
						GXGetAppState()->m_ctlusrState.m_ctrlmap.RemoveKey(this); \
					} \
				}
			// END GRIDEX_IMPLEMENT_REGISTER

		#else	//WIN32

			#define GRIDEX_IMPLEMENT_REGISTER(class_name, _style, icon, cursor, background) \
				LPCTSTR AFXAPI class_name::RegisterClass() \
				{ \
					WNDCLASS wndcls;  \
					LPCTSTR szName = _T(#class_name) ; \
					if (::GetClassInfo(AfxGetInstanceHandle(), szName, &wndcls)) \
						return szName; \
					wndcls.style = _style ; \
					wndcls.lpfnWndProc = class_name::WndProcHook ; \
					wndcls.cbClsExtra = wndcls.cbWndExtra = 0 ; \
					wndcls.hInstance = AfxGetInstanceHandle() ; \
					wndcls.hIcon = icon ; \
					wndcls.hCursor = cursor ; \
					wndcls.hbrBackground = background ; \
					wndcls.lpszMenuName = NULL ; \
					wndcls.lpszClassName = szName ; \
					if (!::RegisterClass(&wndcls)) \
						AfxThrowResourceException() ; \
					return szName ;  } \
				LPCTSTR AFXAPI class_name::RegisterClass(HINSTANCE hInstance) \
				{ \
					WNDCLASS wndcls;  \
					LPCTSTR szName = _T(#class_name) ; \
					if (::GetClassInfo(hInstance, szName, &wndcls)) \
						return szName; \
					wndcls.style = _style ; \
					wndcls.lpfnWndProc = class_name::WndProcHook ; \
					wndcls.cbClsExtra = wndcls.cbWndExtra = 0 ; \
					wndcls.hInstance = hInstance ; \
					wndcls.hIcon = icon ; \
					wndcls.hCursor = cursor ; \
					wndcls.hbrBackground = background ; \
					wndcls.lpszMenuName = NULL ; \
					wndcls.lpszClassName = szName ; \
					if (!::RegisterClass(&wndcls)) \
						AfxThrowResourceException() ; \
					return szName ;  } \
				LRESULT CALLBACK AFX_EXPORT class_name::WndProcHook(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam) \
				{ \
					class_name * pWnd = new class_name(); \
					pWnd->Attach(hWnd); \
					GXGetAppState()->m_ctlusrState.m_ctrlmap[pWnd] = 1; \
					::SetWindowLong(hWnd, GWL_WNDPROC, (DWORD)AfxWndProc); \
					return ::CallWindowProc(AfxWndProc, hWnd, msg, wParam, lParam); } \
				void AFXAPI class_name::UnregisterClass() \
				{ \
					::UnregisterClass( _T(#class_name) , AfxGetInstanceHandle() );  } \
				void AFXAPI class_name::UnregisterClass(HINSTANCE hInstance) \
				{ \
					::UnregisterClass( _T(#class_name) , hInstance );  } \
				void class_name::PostNcDestroy() \
				{ \
					WORD w; \
					if (GXGetAppState()->m_ctlusrState.m_ctrlmap.Lookup(this, w)) \
					{ \
						delete this; \
						GXGetAppState()->m_ctlusrState.m_ctrlmap.RemoveKey(this); \
					} \
				}
			// END GRIDEX_IMPLEMENT_REGISTER

		#endif	//_WIN64
		//Declare Register/////////////////////////////////

	// end Helper Macros

#else // !_OGEXDLL Static Library

	#define GRIDEX_DECLARE_MESSAGE_MAP()			DECLARE_MESSAGE_MAP()
	#define GRIDEX_DECLARE_DYNAMIC(class_name)	DECLARE_DYNAMIC(class_name)
	#define GRIDEX_DECLARE_DYNCREATE(class_name)	DECLARE_DYNCREATE(class_name)
	#define GRIDEX_DECLARE_SERIAL(class_name)		DECLARE_SERIAL(class_name)

	#define GRIDEX_DECLARE_CONTROL(class_name) \
		public: \
			static CGXControlClass GXNEAR ctrl##class_name; \
			virtual CGXControlClass* GetControlClass() const; \

	#define GRIDEX_IMPLEMENT_CONTROL(class_name, base_class_name) \
		CGXControlClass GXNEAR class_name::ctrl##class_name = { \
		#class_name, CONTROL_CLASS(base_class_name) }; \
		CGXControlClass* class_name::GetControlClass() const \
			{ return &class_name::ctrl##class_name; } \

	//Declare Register/////////////////////////////////
	#define GRIDEX_DECLARE_REGISTER() \
		public: \
			GRIDEX_API static LPCTSTR AFXAPI RegisterClass(); \
			GRIDEX_API static void AFXAPI UnregisterClass(); \
			GRIDEX_API static LPCTSTR AFXAPI RegisterClass(HINSTANCE hInstance); \
			GRIDEX_API static void AFXAPI UnregisterClass(HINSTANCE hInstance); \
			GRIDEX_API static CMapPtrToWord GXNEAR _gxregmap; \
		protected: \
			GRIDEX_API static LRESULT CALLBACK AFX_EXPORT WndProcHook(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam); \
			GRIDEX_API virtual void PostNcDestroy();
		// END GRIDEX_DECLARE_REGISTER

	#ifdef _WIN64

		#define GRIDEX_IMPLEMENT_REGISTER(class_name, _style, icon, cursor, background) \
			CMapPtrToWord GXNEAR class_name::_gxregmap; \
			LPCTSTR AFXAPI class_name::RegisterClass() \
			{ \
				WNDCLASS wndcls;  \
				LPCTSTR szName = _T(#class_name) ; \
				if (::GetClassInfo(AfxGetInstanceHandle(), szName, &wndcls)) \
					return szName; \
				wndcls.style = _style ; \
				wndcls.lpfnWndProc = class_name::WndProcHook ; \
				wndcls.cbClsExtra = wndcls.cbWndExtra = 0 ; \
				wndcls.hInstance = AfxGetInstanceHandle() ; \
				wndcls.hIcon = icon ; \
				wndcls.hCursor = cursor ; \
				wndcls.hbrBackground = background ; \
				wndcls.lpszMenuName = NULL ; \
				wndcls.lpszClassName = szName ; \
				if (!::RegisterClass(&wndcls)) \
					AfxThrowResourceException() ; \
				return szName ;  } \
			LPCTSTR AFXAPI class_name::RegisterClass(HINSTANCE hInstance) \
			{ \
				WNDCLASS wndcls;  \
				LPCTSTR szName = _T(#class_name) ; \
				if (::GetClassInfo(hInstance, szName, &wndcls)) \
					return szName; \
				wndcls.style = _style ; \
				wndcls.lpfnWndProc = class_name::WndProcHook ; \
				wndcls.cbClsExtra = wndcls.cbWndExtra = 0 ; \
				wndcls.hInstance = hInstance ; \
				wndcls.hIcon = icon ; \
				wndcls.hCursor = cursor ; \
				wndcls.hbrBackground = background ; \
				wndcls.lpszMenuName = NULL ; \
				wndcls.lpszClassName = szName ; \
				if (!::RegisterClass(&wndcls)) \
					AfxThrowResourceException() ; \
				return szName ;  } \
			LRESULT CALLBACK AFX_EXPORT class_name::WndProcHook(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam) \
			{ \
				class_name * pWnd = new class_name(); \
				pWnd->Attach(hWnd); \
				_gxregmap[pWnd] = 1; \
				::SetWindowLongPtr(hWnd, GWLP_WNDPROC, (SEC_LONG)AfxWndProc); \
				return ::CallWindowProc(AfxWndProc, hWnd, msg, wParam, lParam); } \
			void AFXAPI class_name::UnregisterClass() \
			{ \
				::UnregisterClass( _T(#class_name) , AfxGetInstanceHandle() );  } \
			void AFXAPI class_name::UnregisterClass(HINSTANCE hInstance) \
			{ \
				::UnregisterClass( _T(#class_name) , hInstance );  } \
			void class_name::PostNcDestroy() \
			{ \
				WORD w; \
				if (_gxregmap.Lookup(this, w)) \
				{ \
					delete this; \
					_gxregmap.RemoveKey(this); \
				} \
			}
		// END GRIDEX_IMPLEMENT_REGISTER

	#else	//WIN32

		#define GRIDEX_IMPLEMENT_REGISTER(class_name, _style, icon, cursor, background) \
			CMapPtrToWord GXNEAR class_name::_gxregmap; \
			LPCTSTR AFXAPI class_name::RegisterClass() \
			{ \
				WNDCLASS wndcls;  \
				LPCTSTR szName = _T(#class_name) ; \
				if (::GetClassInfo(AfxGetInstanceHandle(), szName, &wndcls)) \
					return szName; \
				wndcls.style = _style ; \
				wndcls.lpfnWndProc = class_name::WndProcHook ; \
				wndcls.cbClsExtra = wndcls.cbWndExtra = 0 ; \
				wndcls.hInstance = AfxGetInstanceHandle() ; \
				wndcls.hIcon = icon ; \
				wndcls.hCursor = cursor ; \
				wndcls.hbrBackground = background ; \
				wndcls.lpszMenuName = NULL ; \
				wndcls.lpszClassName = szName ; \
				if (!::RegisterClass(&wndcls)) \
					AfxThrowResourceException() ; \
				return szName ;  } \
			LPCTSTR AFXAPI class_name::RegisterClass(HINSTANCE hInstance) \
			{ \
				WNDCLASS wndcls;  \
				LPCTSTR szName = _T(#class_name) ; \
				if (::GetClassInfo(hInstance, szName, &wndcls)) \
					return szName; \
				wndcls.style = _style ; \
				wndcls.lpfnWndProc = class_name::WndProcHook ; \
				wndcls.cbClsExtra = wndcls.cbWndExtra = 0 ; \
				wndcls.hInstance = hInstance ; \
				wndcls.hIcon = icon ; \
				wndcls.hCursor = cursor ; \
				wndcls.hbrBackground = background ; \
				wndcls.lpszMenuName = NULL ; \
				wndcls.lpszClassName = szName ; \
				if (!::RegisterClass(&wndcls)) \
					AfxThrowResourceException() ; \
				return szName ;  } \
			LRESULT CALLBACK AFX_EXPORT class_name::WndProcHook(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam) \
			{ \
				class_name * pWnd = new class_name(); \
				pWnd->Attach(hWnd); \
				_gxregmap[pWnd] = 1; \
				::SetWindowLong(hWnd, GWL_WNDPROC, (DWORD)AfxWndProc); \
				return ::CallWindowProc(AfxWndProc, hWnd, msg, wParam, lParam); } \
			void AFXAPI class_name::UnregisterClass() \
			{ \
				::UnregisterClass( _T(#class_name) , AfxGetInstanceHandle() );  } \
			void AFXAPI class_name::UnregisterClass(HINSTANCE hInstance) \
			{ \
				::UnregisterClass( _T(#class_name) , hInstance );  } \
			void class_name::PostNcDestroy() \
			{ \
				WORD w; \
				if (_gxregmap.Lookup(this, w)) \
				{ \
					delete this; \
					_gxregmap.RemoveKey(this); \
				} \
			}
		// END GRIDEX_IMPLEMENT_REGISTER

	#endif	// _WIN64

	//Declare Register/////////////////////////////////

#endif // GRID
//-------------------------------------------------------------------------------

#ifdef _SECDLL

	#if(_MSC_VER >= 1310) // Visual Studio 2003 +

	/////////////////////////////////////////////////////////////////////////////
	// Window message map handling

		#ifdef _AFXDLL
			#define TOOLKIT_DECLARE_MESSAGE_MAP() \
			private: \
				static const AFX_MSGMAP_ENTRY _messageEntries[]; \
			protected: \
				static const AFX_MSGMAP messageMap; \
				TOOLKIT_API static const AFX_MSGMAP* PASCAL GetThisMessageMap(); \
				TOOLKIT_API virtual const AFX_MSGMAP* GetMessageMap() const; \

		#else
			#define TOOLKIT_DECLARE_MESSAGE_MAP() \
			private: \
				static const AFX_MSGMAP_ENTRY _messageEntries[]; \
			protected: \
				static const AFX_MSGMAP messageMap; \
				TOOLKIT_API virtual const AFX_MSGMAP* GetMessageMap() const; \

		#endif

	#elif(_MSC_VER == 1200) // MSVC6

		#ifdef _AFXDLL
			#define TOOLKIT_DECLARE_MESSAGE_MAP() \
			private: \
				static const AFX_MSGMAP_ENTRY _messageEntries[]; \
			protected: \
				static AFX_DATA const AFX_MSGMAP messageMap; \
				TOOLKIT_API static const AFX_MSGMAP* PASCAL _GetBaseMessageMap(); \
				TOOLKIT_API virtual const AFX_MSGMAP* GetMessageMap() const; \

		#else
			#define TOOLKIT_DECLARE_MESSAGE_MAP() \
			private: \
				static const AFX_MSGMAP_ENTRY _messageEntries[]; \
			protected: \
				static AFX_DATA const AFX_MSGMAP messageMap; \
				TOOLKIT_API virtual const AFX_MSGMAP* GetMessageMap() const; \

		#endif

	#else // !_MSC_VER >= 1310

		#define TOOLKIT_DECLARE_MESSAGE_MAP()			DECLARE_MESSAGE_MAP()

	#endif

	//////////////////////////////////////////////////////////////////////////////
	// Helper macros for declaring CRuntimeClass compatible classes
	#if(_MSC_VER >= 1310)

		#ifdef _AFXDLL
			#define TOOLKIT_DECLARE_DYNAMIC(class_name) \
			protected: \
				TOOLKIT_API static CRuntimeClass* PASCAL _GetBaseClass(); \
			public: \
				static const CRuntimeClass class##class_name; \
				TOOLKIT_API static CRuntimeClass* PASCAL GetThisClass(); \
				TOOLKIT_API virtual CRuntimeClass* GetRuntimeClass() const; 
			
			#define _TOOLKIT_DECLARE_DYNAMIC(class_name) \
			protected: \
				TOOLKIT_API static CRuntimeClass* PASCAL _GetBaseClass(); \
			public: \
				static CRuntimeClass class##class_name; \
				TOOLKIT_API static CRuntimeClass* PASCAL GetThisClass(); \
				TOOLKIT_API virtual CRuntimeClass* GetRuntimeClass() const; 

		#else // !_AFXDLL

			#define TOOLKIT_DECLARE_DYNAMIC(class_name) \
			public: \
				static const CRuntimeClass class##class_name; \
				TOOLKIT_API virtual CRuntimeClass* GetRuntimeClass() const; \
			
			#define _TOOLKIT_DECLARE_DYNAMIC(class_name) \
			public: \
				static CRuntimeClass class##class_name; \
				TOOLKIT_API virtual CRuntimeClass* GetRuntimeClass() const; 

		#endif // MFC DLL/LIB

	#elif(_MSC_VER == 1200)

		#ifdef _AFXDLL
			#define TOOLKIT_DECLARE_DYNAMIC(class_name) \
			protected: \
				TOOLKIT_API static CRuntimeClass* PASCAL _GetBaseClass(); \
			public: \
				static const AFX_DATA CRuntimeClass class##class_name; \
				TOOLKIT_API virtual CRuntimeClass* GetRuntimeClass() const; \

			#define _TOOLKIT_DECLARE_DYNAMIC(class_name) \
			protected: \
				TOOLKIT_API static CRuntimeClass* PASCAL _GetBaseClass(); \
			public: \
				static AFX_DATA CRuntimeClass class##class_name; \
				TOOLKIT_API virtual CRuntimeClass* GetRuntimeClass() const; \

		#else
			#define TOOLKIT_DECLARE_DYNAMIC(class_name) \
			public: \
				static const AFX_DATA CRuntimeClass class##class_name; \
				TOOLKIT_API virtual CRuntimeClass* GetRuntimeClass() const; \

			#define _TOOLKIT_DECLARE_DYNAMIC(class_name) \
			public: \
				static AFX_DATA CRuntimeClass class##class_name; \
				TOOLKIT_API virtual CRuntimeClass* GetRuntimeClass() const; \

		#endif // _AFXDLL

	#else

		#define TOOLKIT_DECLARE_DYNAMIC(class_name)	DECLARE_DYNAMIC(class_name)

	#endif // Declare Dynamic
		
		// Not serializable, but dynamically constructable
		#define TOOLKIT_DECLARE_DYNCREATE(class_name) \
			TOOLKIT_DECLARE_DYNAMIC(class_name) \
			TOOLKIT_API static CObject* PASCAL CreateObject();
		
		#define _TOOLKIT_DECLARE_DYNCREATE(class_name) \
			_TOOLKIT_DECLARE_DYNAMIC(class_name) \
			TOOLKIT_API static CObject* PASCAL CreateObject();
		
		#define TOOLKIT_DECLARE_SERIAL(class_name) \
			_TOOLKIT_DECLARE_DYNCREATE(class_name) \
			AFX_API friend TOOLKIT_API CArchive& AFXAPI operator>>(CArchive& ar, class_name* &pOb);

	// QA: 31982 - Interface Map
	#ifdef _AFXDLL
		#define TOOLKIT_DECLARE_INTERFACE_MAP() \
			private: \
			static const AFX_INTERFACEMAP_ENTRY _interfaceEntries[]; \
			protected: \
			static const AFX_INTERFACEMAP interfaceMap; \
			TOOLKIT_API static const AFX_INTERFACEMAP* PASCAL GetThisInterfaceMap(); \
			TOOLKIT_API virtual const AFX_INTERFACEMAP* GetInterfaceMap() const; \

	#else
		#define TOOLKIT_DECLARE_INTERFACE_MAP() \
			private: \
			static const AFX_INTERFACEMAP_ENTRY _interfaceEntries[]; \
			protected: 
			static const AFX_INTERFACEMAP interfaceMap; \
			TOOLKIT_API virtual const AFX_INTERFACEMAP* GetInterfaceMap() const; \

	#endif // AFXDLL

	// QA: 31982 - Dispatch Map
	#ifdef _AFXDLL
		#define TOOLKIT_DECLARE_DISPATCH_MAP() \
			private: \
			static const AFX_DISPMAP_ENTRY _dispatchEntries[]; \
			static UINT _dispatchEntryCount; \
			static DWORD _dwStockPropMask; \
			protected: \
			static const AFX_DISPMAP dispatchMap; \
			TOOLKIT_API static const AFX_DISPMAP* PASCAL GetThisDispatchMap(); \
			TOOLKIT_API virtual const AFX_DISPMAP* GetDispatchMap() const; \

	#else
		#define TOOLKIT_DECLARE_DISPATCH_MAP() \
			private: \
			static const AFX_DISPMAP_ENTRY _dispatchEntries[]; \
			static UINT _dispatchEntryCount; \
			static DWORD _dwStockPropMask; \
			protected: \
			static const AFX_DISPMAP dispatchMap; \
			TOOLKIT_API virtual const AFX_DISPMAP* GetDispatchMap() const; \

	#endif // _AFXDLL

	// QA 32167: Begin Interface Part
	#define TOOLKIT_BEGIN_INTERFACE_PART(localClass, baseClass) \
	class X##localClass : public baseClass \
	{ \
	public: \
		TOOLKIT_API STDMETHOD_(ULONG, AddRef)(); \
		TOOLKIT_API STDMETHOD_(ULONG, Release)(); \
		TOOLKIT_API STDMETHOD(QueryInterface)(REFIID iid, LPVOID* ppvObj); \
			
	// end Helper Macros

#else // !_SECDLL

	#define TOOLKIT_DECLARE_MESSAGE_MAP()			DECLARE_MESSAGE_MAP()
	#define TOOLKIT_DECLARE_DYNAMIC(class_name)		DECLARE_DYNAMIC(class_name)
	#define TOOLKIT_DECLARE_DYNCREATE(class_name)	DECLARE_DYNCREATE(class_name)
	#define TOOLKIT_DECLARE_SERIAL(class_name)		DECLARE_SERIAL(class_name)
	#define TOOLKIT_DECLARE_INTERFACE_MAP			DECLARE_INTERFACE_MAP()
	#define TOOLKIT_DECLARE_DISPATCH_MAP()			DECLARE_DISPATCH_MAP()
	#define TOOLKIT_BEGIN_INTERFACE_PART(localClass, baseClass)			BEGIN_INTERFACE_PART(localClass, baseClass) // QA: 32167

#endif // TOOLKIT

// Global Toolkit
#define TOOLKIT_DECLARE_BUTTON(class_name) \
	public: \
		static const AFX_DATA SECButtonClass class##class_name; \
		TOOLKIT_API virtual SECButtonClass* GetButtonClass() const; \
		TOOLKIT_API static SECStdBtn* PASCAL CreateButton();

#define TOOLKIT_IMPLEMENT_BUTTON(class_name) \
	SECStdBtn* PASCAL class_name::CreateButton() \
		{ return new class_name; } \
		const AFX_DATADEF SECButtonClass class_name::class##class_name = { \
		class_name::CreateButton }; \
		SECButtonClass* class_name::GetButtonClass() const \
		{ return ((SECButtonClass*)(&class_name::class##class_name)); } \


#ifdef _OBJCHART_DLL

	#if(_MSC_VER >= 1310) // Visual Studio 2003 +

	/////////////////////////////////////////////////////////////////////////////
	// Window message map handling

		#ifdef _AFXDLL
			#define CHART_DECLARE_MESSAGE_MAP() \
			private: \
				static const AFX_MSGMAP_ENTRY _messageEntries[]; \
			protected: \
				static const AFX_MSGMAP messageMap; \
				CHART_API static const AFX_MSGMAP* PASCAL GetThisMessageMap(); \
				CHART_API virtual const AFX_MSGMAP* GetMessageMap() const; \

		#else
			#define CHART_DECLARE_MESSAGE_MAP() \
			private: \
				static const AFX_MSGMAP_ENTRY _messageEntries[]; \
			protected: \
				static const AFX_MSGMAP messageMap; \
				CHART_API virtual const AFX_MSGMAP* GetMessageMap() const; \

		#endif

	#elif(_MSC_VER == 1200) // MSVC6

		#ifdef _AFXDLL
			#define CHART_DECLARE_MESSAGE_MAP() \
			private: \
				static const AFX_MSGMAP_ENTRY _messageEntries[]; \
			protected: \
				static AFX_DATA const AFX_MSGMAP messageMap; \
				CHART_API static const AFX_MSGMAP* PASCAL _GetBaseMessageMap(); \
				CHART_API virtual const AFX_MSGMAP* GetMessageMap() const; \

		#else
			#define CHART_DECLARE_MESSAGE_MAP() \
			private: \
				static const AFX_MSGMAP_ENTRY _messageEntries[]; \
			protected: \
				static AFX_DATA const AFX_MSGMAP messageMap; \
				CHART_API virtual const AFX_MSGMAP* GetMessageMap() const; \

		#endif

	#else // !_MSC_VER >= 1310

		#define CHART_DECLARE_MESSAGE_MAP()			DECLARE_MESSAGE_MAP()

	#endif

	//////////////////////////////////////////////////////////////////////////////
	// Helper macros for declaring CRuntimeClass compatible classes

	#if(_MSC_VER >= 1310)

		#ifdef _AFXDLL
			#define CHART_DECLARE_DYNAMIC(class_name) \
			protected: \
				CHART_API static CRuntimeClass* PASCAL _GetBaseClass(); \
			public: \
				static const CRuntimeClass class##class_name; \
				CHART_API static CRuntimeClass* PASCAL GetThisClass(); \
				CHART_API virtual CRuntimeClass* GetRuntimeClass() const; 
			
			#define _CHART_DECLARE_DYNAMIC(class_name) \
			protected: \
				CHART_API static CRuntimeClass* PASCAL _GetBaseClass(); \
			public: \
				static CRuntimeClass class##class_name; \
				CHART_API static CRuntimeClass* PASCAL GetThisClass(); \
				CHART_API virtual CRuntimeClass* GetRuntimeClass() const; 

		#else // !_AFXDLL

			#define CHART_DECLARE_DYNAMIC(class_name) \
			public: \
				static const CRuntimeClass class##class_name; \
				CHART_API virtual CRuntimeClass* GetRuntimeClass() const; 
			
			#define _CHART_DECLARE_DYNAMIC(class_name) \
			public: \
				static CRuntimeClass class##class_name; \
				CHART_API virtual CRuntimeClass* GetRuntimeClass() const; 

		#endif // MFC DLL/LIB

	#elif(_MSC_VER == 1200)

		#ifdef _AFXDLL
			#define CHART_DECLARE_DYNAMIC(class_name) \
			protected: \
				CHART_API static CRuntimeClass* PASCAL _GetBaseClass(); \
			public: \
				static const AFX_DATA CRuntimeClass class##class_name; \
				CHART_API virtual CRuntimeClass* GetRuntimeClass() const; \

			#define _CHART_DECLARE_DYNAMIC(class_name) \
			protected: \
				CHART_API static CRuntimeClass* PASCAL _GetBaseClass(); \
			public: \
				static AFX_DATA CRuntimeClass class##class_name; \
				CHART_API virtual CRuntimeClass* GetRuntimeClass() const; \

		#else
			#define CHART_DECLARE_DYNAMIC(class_name) \
			public: \
				static const AFX_DATA CRuntimeClass class##class_name; \
				CHART_API virtual CRuntimeClass* GetRuntimeClass() const; \

			#define _CHART_DECLARE_DYNAMIC(class_name) \
			public: \
				static AFX_DATA CRuntimeClass class##class_name; \
				CHART_API virtual CRuntimeClass* GetRuntimeClass() const; \

		#endif // _AFXDLL

	#else

		#define CHART_DECLARE_DYNAMIC(class_name)	DECLARE_DYNAMIC(class_name)

	#endif // Declare Dynamic
		
		// not serializable, but dynamically constructable
		#define CHART_DECLARE_DYNCREATE(class_name) \
			CHART_DECLARE_DYNAMIC(class_name) \
			CHART_API static CObject* PASCAL CreateObject();
		
		#define _CHART_DECLARE_DYNCREATE(class_name) \
			_CHART_DECLARE_DYNAMIC(class_name) \
			CHART_API static CObject* PASCAL CreateObject();
		
		#define CHART_DECLARE_SERIAL(class_name) \
			_CHART_DECLARE_DYNCREATE(class_name) \
			AFX_API friend CHART_API CArchive& AFXAPI operator>>(CArchive& ar, class_name* &pOb);

	// end Helper Macros

#else // !_OBJCHART_DLL

	#define CHART_DECLARE_MESSAGE_MAP()			DECLARE_MESSAGE_MAP()
	#define CHART_DECLARE_DYNAMIC(class_name)	DECLARE_DYNAMIC(class_name)
	#define CHART_DECLARE_DYNCREATE(class_name)	DECLARE_DYNCREATE(class_name)
	#define CHART_DECLARE_SERIAL(class_name)	DECLARE_SERIAL(class_name)

#endif // CHART

	
#ifdef _OBJCHART_UT_DLL

	#if(_MSC_VER >= 1310) // Visual Studio 2003 +

	/////////////////////////////////////////////////////////////////////////////
	// Window message map handling

		#ifdef _AFXDLL
			#define CHART_UT_DECLARE_MESSAGE_MAP() \
			private: \
				static const AFX_MSGMAP_ENTRY _messageEntries[]; \
			protected: \
				static const AFX_MSGMAP messageMap; \
				CHART_UT_API static const AFX_MSGMAP* PASCAL GetThisMessageMap(); \
				CHART_UT_API virtual const AFX_MSGMAP* GetMessageMap() const; \

		#else
			#define CHART_UT_DECLARE_MESSAGE_MAP() \
			private: \
				static const AFX_MSGMAP_ENTRY _messageEntries[]; \
			protected: \
				static const AFX_MSGMAP messageMap; \
				CHART_UT_API virtual const AFX_MSGMAP* GetMessageMap() const; \

		#endif

	#elif(_MSC_VER == 1200) // MSVC6

		#ifdef _AFXDLL
			#define CHART_UT_DECLARE_MESSAGE_MAP() \
			private: \
				static const AFX_MSGMAP_ENTRY _messageEntries[]; \
			protected: \
				static AFX_DATA const AFX_MSGMAP messageMap; \
				CHART_UT_API static const AFX_MSGMAP* PASCAL _GetBaseMessageMap(); \
				CHART_UT_API virtual const AFX_MSGMAP* GetMessageMap() const; \

		#else
			#define CHART_UT_API DECLARE_MESSAGE_MAP() \
			private: \
				static const AFX_MSGMAP_ENTRY _messageEntries[]; \
			protected: \
				static AFX_DATA const AFX_MSGMAP messageMap; \
				CHART_UT_API virtual const AFX_MSGMAP* GetMessageMap() const; \

		#endif

	#else // !_MSC_VER >= 1310

		#define CHART_UT_DECLARE_MESSAGE_MAP()			DECLARE_MESSAGE_MAP()

	#endif

	//////////////////////////////////////////////////////////////////////////////
	// Helper macros for declaring CRuntimeClass compatible classes

	#if(_MSC_VER >= 1310)

		#ifdef _AFXDLL
			#define CHART_UT_DECLARE_DYNAMIC(class_name) \
			protected: \
				CHART_UT_API static CRuntimeClass* PASCAL _GetBaseClass(); \
			public: \
				static const CRuntimeClass class##class_name; \
				CHART_UT_API static CRuntimeClass* PASCAL GetThisClass(); \
				CHART_UT_API virtual CRuntimeClass* GetRuntimeClass() const; 
			
			#define _CHART_UT_DECLARE_DYNAMIC(class_name) \
			protected: \
				CHART_UT_API static CRuntimeClass* PASCAL _GetBaseClass(); \
			public: \
				static CRuntimeClass class##class_name; \
				CHART_UT_API static CRuntimeClass* PASCAL GetThisClass(); \
				CHART_UT_API virtual CRuntimeClass* GetRuntimeClass() const; 

		#else // !_AFXDLL

			#define CHART_UT_DECLARE_DYNAMIC(class_name) \
			public: \
				static const CRuntimeClass class##class_name; \
				CHART_UT_API virtual CRuntimeClass* GetRuntimeClass() const; 
			
			#define _CHART_UT_DECLARE_DYNAMIC(class_name) \
			public: \
				static CRuntimeClass class##class_name; \
				CHART_UT_API virtual CRuntimeClass* GetRuntimeClass() const; 

		#endif // MFC DLL/LIB

	#elif(_MSC_VER == 1200)

		#ifdef _AFXDLL
			#define CHART_UT_DECLARE_DYNAMIC(class_name) \
			protected: \
				CHART_UT_API static CRuntimeClass* PASCAL _GetBaseClass(); \
			public: \
				static const AFX_DATA CRuntimeClass class##class_name; \
				CHART_UT_API virtual CRuntimeClass* GetRuntimeClass() const; \

			#define _CHART_UT_DECLARE_DYNAMIC(class_name) \
			protected: \
				CHART_UT_API static CRuntimeClass* PASCAL _GetBaseClass(); \
			public: \
				static AFX_DATA CRuntimeClass class##class_name; \
				CHART_UT_API virtual CRuntimeClass* GetRuntimeClass() const; \

		#else
			#define CHART_UT_DECLARE_DYNAMIC(class_name) \
			public: \
				static const AFX_DATA CRuntimeClass class##class_name; \
				CHART_UT_API virtual CRuntimeClass* GetRuntimeClass() const; \

			#define _CHART_UT_DECLARE_DYNAMIC(class_name) \
			public: \
				static AFX_DATA CRuntimeClass class##class_name; \
				CHART_UT_API virtual CRuntimeClass* GetRuntimeClass() const; \

		#endif // _AFXDLL

	#else

		#define CHART_UT_DECLARE_DYNAMIC(class_name)	DECLARE_DYNAMIC(class_name)

	#endif // Declare Dynamic
		
		// not serializable, but dynamically constructable
		#define CHART_UT_DECLARE_DYNCREATE(class_name) \
			CHART_UT_DECLARE_DYNAMIC(class_name) \
			CHART_UT_API static CObject* PASCAL CreateObject();
		
		#define _CHART_UT_DECLARE_DYNCREATE(class_name) \
			_CHART_UT_DECLARE_DYNAMIC(class_name) \
			CHART_UT_API static CObject* PASCAL CreateObject();
		
		#define CHART_UT_DECLARE_SERIAL(class_name) \
			_CHART_UT_DECLARE_DYNCREATE(class_name) \
			AFX_API friend CHART_UT_API CArchive& AFXAPI operator>>(CArchive& ar, class_name* &pOb);

	// end Helper Macros

#else // !_OBJCHART_UT_DLL

	#define CHART_UT_DECLARE_MESSAGE_MAP()			DECLARE_MESSAGE_MAP()
	#define CHART_UT_DECLARE_DYNAMIC(class_name)	DECLARE_DYNAMIC(class_name)
	#define CHART_UT_DECLARE_DYNCREATE(class_name)	DECLARE_DYNCREATE(class_name)
	#define CHART_UT_DECLARE_SERIAL(class_name)		DECLARE_SERIAL(class_name)
	
#endif // CHART UTILITY TOOLKIT
	
	
#ifdef _SECEDITDLL

	#if(_MSC_VER >= 1310) // Visual Studio 2003 +

	/////////////////////////////////////////////////////////////////////////////
	// Window message map handling

		#ifdef _AFXDLL
			#define EDIT_DECLARE_MESSAGE_MAP() \
			private: \
				static const AFX_MSGMAP_ENTRY _messageEntries[]; \
			protected: \
				static const AFX_MSGMAP messageMap; \
				EDIT_API static const AFX_MSGMAP* PASCAL GetThisMessageMap(); \
				EDIT_API virtual const AFX_MSGMAP* GetMessageMap() const; \

		#else
			#define EDIT_DECLARE_MESSAGE_MAP() \
			private: \
				static const AFX_MSGMAP_ENTRY _messageEntries[]; \
			protected: \
				static const AFX_MSGMAP messageMap; \
				EDIT_API virtual const AFX_MSGMAP* GetMessageMap() const; \

		#endif

	#elif(_MSC_VER == 1200) // MSVC6

		#ifdef _AFXDLL
			#define EDIT_DECLARE_MESSAGE_MAP() \
			private: \
				static const AFX_MSGMAP_ENTRY _messageEntries[]; \
			protected: \
				static AFX_DATA const AFX_MSGMAP messageMap; \
				EDIT_API static const AFX_MSGMAP* PASCAL _GetBaseMessageMap(); \
				EDIT_API virtual const AFX_MSGMAP* GetMessageMap() const; \

		#else
			#define EDIT_DECLARE_MESSAGE_MAP() \
			private: \
				static const AFX_MSGMAP_ENTRY _messageEntries[]; \
			protected: \
				EDIT_API static AFX_DATA const AFX_MSGMAP messageMap; \
				EDIT_API virtual const AFX_MSGMAP* GetMessageMap() const; \

		#endif

	#else // !_MSC_VER >= 1310

		#define EDIT_DECLARE_MESSAGE_MAP()			DECLARE_MESSAGE_MAP()

	#endif

	//////////////////////////////////////////////////////////////////////////////
	// Helper macros for declaring CRuntimeClass compatible classes

	#if(_MSC_VER >= 1310)

		#ifdef _AFXDLL
			#define EDIT_DECLARE_DYNAMIC(class_name) \
			protected: \
				EDIT_API static CRuntimeClass* PASCAL _GetBaseClass(); \
			public: \
				static const CRuntimeClass class##class_name; \
				EDIT_API static CRuntimeClass* PASCAL GetThisClass(); \
				EDIT_API virtual CRuntimeClass* GetRuntimeClass() const; 
			
			#define _EDIT_DECLARE_DYNAMIC(class_name) \
			protected: \
				EDIT_API static CRuntimeClass* PASCAL _GetBaseClass(); \
			public: \
				static CRuntimeClass class##class_name; \
				EDIT_API static CRuntimeClass* PASCAL GetThisClass(); \
				EDIT_API virtual CRuntimeClass* GetRuntimeClass() const; 

		#else // !_AFXDLL

			#define EDIT_DECLARE_DYNAMIC(class_name) \
			public: \
				static const CRuntimeClass class##class_name; \
				EDIT_API virtual CRuntimeClass* GetRuntimeClass() const; 
			
			#define _EDIT_DECLARE_DYNAMIC(class_name) \
			public: \
				static CRuntimeClass class##class_name; \
				EDIT_API virtual CRuntimeClass* GetRuntimeClass() const; 

		#endif // MFC DLL/LIB

	#elif(_MSC_VER == 1200)

		#ifdef _AFXDLL
			#define EDIT_DECLARE_DYNAMIC(class_name) \
			protected: \
				EDIT_API static CRuntimeClass* PASCAL _GetBaseClass(); \
			public: \
				static const AFX_DATA CRuntimeClass class##class_name; \
				EDIT_API virtual CRuntimeClass* GetRuntimeClass() const; \

			#define _EDIT_DECLARE_DYNAMIC(class_name) \
			protected: \
				EDIT_API static CRuntimeClass* PASCAL _GetBaseClass(); \
			public: \
				static AFX_DATA CRuntimeClass class##class_name; \
				EDIT_API virtual CRuntimeClass* GetRuntimeClass() const; \

		#else
			#define EDIT_DECLARE_DYNAMIC(class_name) \
			public: \
				static const AFX_DATA CRuntimeClass class##class_name; \
				EDIT_API virtual CRuntimeClass* GetRuntimeClass() const; \

			#define _EDIT_DECLARE_DYNAMIC(class_name) \
			public: \
				static AFX_DATA CRuntimeClass class##class_name; \
				EDIT_API virtual CRuntimeClass* GetRuntimeClass() const; \

		#endif // _AFXDLL

	#else

		#define EDIT_DECLARE_DYNAMIC(class_name)	DECLARE_DYNAMIC(class_name)

	#endif // Declare Dynamic
		
		// not serializable, but dynamically constructable
		#define EDIT_DECLARE_DYNCREATE(class_name) \
			EDIT_DECLARE_DYNAMIC(class_name) \
			EDIT_API static CObject* PASCAL CreateObject();
		
		#define _EDIT_DECLARE_DYNCREATE(class_name) \
			_EDIT_DECLARE_DYNAMIC(class_name) \
			EDIT_API static CObject* PASCAL CreateObject();
		
		#define EDIT_DECLARE_SERIAL(class_name) \
			_EDIT_DECLARE_DYNCREATE(class_name) \
			AFX_API friend EDIT_API CArchive& AFXAPI operator>>(CArchive& ar, class_name* &pOb);
		
	// end Helper Macros


#else // !_SECEDIT_DLL

	#define EDIT_DECLARE_MESSAGE_MAP()			DECLARE_MESSAGE_MAP()
	#define EDIT_DECLARE_DYNAMIC(class_name)	DECLARE_DYNAMIC(class_name)
	#define EDIT_DECLARE_DYNCREATE(class_name)	DECLARE_DYNCREATE(class_name)
	#define EDIT_DECLARE_SERIAL(class_name)		DECLARE_SERIAL(class_name)
	
#endif // EDIT
	
	
#ifdef _OVDLL

	#if(_MSC_VER >= 1310) // Visual Studio 2003 +

	/////////////////////////////////////////////////////////////////////////////
	// Window message map handling

		#ifdef _AFXDLL
			#define VIEWS_DECLARE_MESSAGE_MAP() \
			private: \
				static const AFX_MSGMAP_ENTRY _messageEntries[]; \
			protected: \
				static const AFX_MSGMAP messageMap; \
				VIEWS_API static const AFX_MSGMAP* PASCAL GetThisMessageMap(); \
				VIEWS_API virtual const AFX_MSGMAP* GetMessageMap() const; \

		#else
			#define VIEWS_DECLARE_MESSAGE_MAP() \
			private: \
				static const AFX_MSGMAP_ENTRY _messageEntries[]; \
			protected: \
				static const AFX_MSGMAP messageMap; \
				VIEWS_API virtual const AFX_MSGMAP* GetMessageMap() const; \

		#endif

	#elif(_MSC_VER == 1200) // MSVC6

		#ifdef _AFXDLL
			#define VIEWS_DECLARE_MESSAGE_MAP() \
			private: \
				static const AFX_MSGMAP_ENTRY _messageEntries[]; \
			protected: \
				static AFX_DATA const AFX_MSGMAP messageMap; \
				VIEWS_API static const AFX_MSGMAP* PASCAL _GetBaseMessageMap(); \
				VIEWS_API virtual const AFX_MSGMAP* GetMessageMap() const; \

		#else
			#define VIEWS_DECLARE_MESSAGE_MAP() \
			private: \
				static const AFX_MSGMAP_ENTRY _messageEntries[]; \
			protected: \
				static AFX_DATA const AFX_MSGMAP messageMap; \
				VIEWS_API virtual const AFX_MSGMAP* GetMessageMap() const; \

		#endif

	#else // !_MSC_VER >= 1310

		#define VIEWS_DECLARE_MESSAGE_MAP()			DECLARE_MESSAGE_MAP()

	#endif

	//////////////////////////////////////////////////////////////////////////////
	// Helper macros for declaring CRuntimeClass compatible classes

	#if(_MSC_VER >= 1310)

		#ifdef _AFXDLL
			#define VIEWS_DECLARE_DYNAMIC(class_name) \
			protected: \
				VIEWS_API static CRuntimeClass* PASCAL _GetBaseClass(); \
			public: \
				static const CRuntimeClass class##class_name; \
				VIEWS_API static CRuntimeClass* PASCAL GetThisClass(); \
				VIEWS_API virtual CRuntimeClass* GetRuntimeClass() const; 
			
			#define _VIEWS_DECLARE_DYNAMIC(class_name) \
			protected: \
				VIEWS_API static CRuntimeClass* PASCAL _GetBaseClass(); \
			public: \
				static CRuntimeClass class##class_name; \
				VIEWS_API static CRuntimeClass* PASCAL GetThisClass(); \
				VIEWS_API virtual CRuntimeClass* GetRuntimeClass() const; 

		#else // !_AFXDLL

				#define VIEWS_DECLARE_DYNAMIC(class_name) \
			public: \
				static const CRuntimeClass class##class_name; \
				VIEWS_API virtual CRuntimeClass* GetRuntimeClass() const; 
			
			#define _VIEWS_DECLARE_DYNAMIC(class_name) \
			public: \
				static CRuntimeClass class##class_name; \
				VIEWS_API virtual CRuntimeClass* GetRuntimeClass() const; 

		#endif // MFC DLL/LIB 

	#elif(_MSC_VER >= 1200)

		#ifdef _AFXDLL
			#define VIEWS_DECLARE_DYNAMIC(class_name) \
			protected: \
				VIEWS_API static CRuntimeClass* PASCAL _GetBaseClass(); \
			public: \
				static const AFX_DATA CRuntimeClass class##class_name; \
				VIEWS_API virtual CRuntimeClass* GetRuntimeClass() const; \

			#define _VIEWS_DECLARE_DYNAMIC(class_name) \
			protected: \
				VIEWS_API static CRuntimeClass* PASCAL _GetBaseClass(); \
			public: \
				static AFX_DATA CRuntimeClass class##class_name; \
				VIEWS_API virtual CRuntimeClass* GetRuntimeClass() const; \

		#else
			#define VIEWS_DECLARE_DYNAMIC(class_name) \
			public: \
				static const AFX_DATA CRuntimeClass class##class_name; \
				VIEWS_API virtual CRuntimeClass* GetRuntimeClass() const; \

			#define _VIEWS_DECLARE_DYNAMIC(class_name) \
			public: \
				static AFX_DATA CRuntimeClass class##class_name; \
				VIEWS_API virtual CRuntimeClass* GetRuntimeClass() const; \

		#endif // _AFXDLL

	#else

		#define VIEWS_DECLARE_DYNAMIC(class_name)	DECLARE_DYNAMIC(class_name)

	#endif // Declare Dynamic
		
		// not serializable, but dynamically constructable
		#define VIEWS_DECLARE_DYNCREATE(class_name) \
			VIEWS_DECLARE_DYNAMIC(class_name) \
			VIEWS_API static CObject* PASCAL CreateObject();
		
		#define _VIEWS_DECLARE_DYNCREATE(class_name) \
			_VIEWS_DECLARE_DYNAMIC(class_name) \
			VIEWS_API static CObject* PASCAL CreateObject();
		
		#define VIEWS_DECLARE_SERIAL(class_name) \
			_VIEWS_DECLARE_DYNCREATE(class_name) \
			AFX_API friend VIEWS_API CArchive& AFXAPI operator>>(CArchive& ar, class_name* &pOb);
		
	// end Helper Macros

#else // !_OVDLL

	#define VIEWS_DECLARE_MESSAGE_MAP()			DECLARE_MESSAGE_MAP()
	#define VIEWS_DECLARE_DYNAMIC(class_name)	DECLARE_DYNAMIC(class_name)
	#define VIEWS_DECLARE_DYNCREATE(class_name)	DECLARE_DYNCREATE(class_name)
	#define VIEWS_DECLARE_SERIAL(class_name)	DECLARE_SERIAL(class_name)
	
#endif // VIEWS

//--------------------------------------------------------------------------//
// Grid for ActiveX                                                         //
//--------------------------------------------------------------------------//

#ifdef _GXDLL // Grid for ActiveX

/////////////////////////////////////////////////////////////////////////////
// Window message map handling

	#if(_MSC_VER >= 1310) // Visual Studio 2003 +

		#ifdef _AFXDLL
			#define GRIDX_DECLARE_MESSAGE_MAP() \
			private: \
				static const AFX_MSGMAP_ENTRY _messageEntries[]; \
			protected: \
				static const AFX_MSGMAP messageMap; \
				GRIDX_API static const AFX_MSGMAP* PASCAL GetThisMessageMap(); \
				GRIDX_API virtual const AFX_MSGMAP* GetMessageMap() const; \

		#else
			#define GRIDX_DECLARE_MESSAGE_MAP() \
			private: \
				static const AFX_MSGMAP_ENTRY _messageEntries[]; \
			protected: \
				static const AFX_MSGMAP messageMap; \
				GRIDX_API virtual const AFX_MSGMAP* GetMessageMap() const; \

		#endif

	#elif(_MSC_VER == 1200) // MSVC6

		#ifdef _AFXDLL
			#define GRIDX_DECLARE_MESSAGE_MAP() \
			private: \
				static const AFX_MSGMAP_ENTRY _messageEntries[]; \
			protected: \
				static AFX_DATA const AFX_MSGMAP messageMap; \
				GRIDX_API static const AFX_MSGMAP* PASCAL _GetBaseMessageMap(); \
				GRIDX_API virtual const AFX_MSGMAP* GetMessageMap() const; \

		#else
			#define GRIDX_DECLARE_MESSAGE_MAP() \
			private: \
				static const AFX_MSGMAP_ENTRY _messageEntries[]; \
			protected: \
				static AFX_DATA const AFX_MSGMAP messageMap; \
				GRIDX_API virtual const AFX_MSGMAP* GetMessageMap() const; \

		#endif

	#else // !_MSC_VER >= 1310

		#define GRIDX_DECLARE_MESSAGE_MAP()			DECLARE_MESSAGE_MAP()

	#endif

	//////////////////////////////////////////////////////////////////////////////
	// Helper macros for declaring CRuntimeClass compatible classes
	#if(_MSC_VER >= 1310)

		#ifdef _AFXDLL
			#define GRIDX_DECLARE_DYNAMIC(class_name) \
			protected: \
				GRIDX_API static CRuntimeClass* PASCAL _GetBaseClass(); \
			public: \
				static const CRuntimeClass class##class_name; \
				GRIDX_API static CRuntimeClass* PASCAL GetThisClass(); \
				GRIDX_API virtual CRuntimeClass* GetRuntimeClass() const; 
			
			#define _GRIDX_DECLARE_DYNAMIC(class_name) \
			protected: \
				GRIDX_API static CRuntimeClass* PASCAL _GetBaseClass(); \
			public: \
				static CRuntimeClass class##class_name; \
				GRIDX_API static CRuntimeClass* PASCAL GetThisClass(); \
				GRIDX_API virtual CRuntimeClass* GetRuntimeClass() const; 

		#else // !_AFXDLL

			#define GRIDX_DECLARE_DYNAMIC(class_name) \
			public: \
				static const CRuntimeClass class##class_name; \
				GRIDX_API virtual CRuntimeClass* GetRuntimeClass() const;
			
			#define _GRIDX_DECLARE_DYNAMIC(class_name) \
			public: \
				static CRuntimeClass class##class_name; \
				GRIDX_API virtual CRuntimeClass* GetRuntimeClass() const;

		#endif // MFC DLL/LIB

	#elif(_MSC_VER == 1200)

		#ifdef _AFXDLL
			#define GRIDX_DECLARE_DYNAMIC(class_name) \
			protected: \
				GRIDX_API static CRuntimeClass* PASCAL _GetBaseClass(); \
			public: \
				static const AFX_DATA CRuntimeClass class##class_name; \
				GRIDX_API virtual CRuntimeClass* GetRuntimeClass() const; \

			#define _GRIDX_DECLARE_DYNAMIC(class_name) \
			protected: \
				GRIDX_API static CRuntimeClass* PASCAL _GetBaseClass(); \
			public: \
				static AFX_DATA CRuntimeClass class##class_name; \
				GRIDX_API virtual CRuntimeClass* GetRuntimeClass() const; \

		#else
			#define GRIDX_DECLARE_DYNAMIC(class_name) \
			public: \
				static const AFX_DATA CRuntimeClass class##class_name; \
				GRIDX_API virtual CRuntimeClass* GetRuntimeClass() const; \

			#define _GRIDX_DECLARE_DYNAMIC(class_name) \
			public: \
				static AFX_DATA CRuntimeClass class##class_name; \
				GRIDX_API virtual CRuntimeClass* GetRuntimeClass() const; \

		#endif // _AFXDLL

	#else

		#define GRIDX_DECLARE_DYNAMIC(class_name)	DECLARE_DYNAMIC(class_name)

	#endif // Declare Dynamic
		
	// not serializable, but dynamically constructable
	#define GRIDX_DECLARE_DYNCREATE(class_name) \
		GRIDX_DECLARE_DYNAMIC(class_name) \
		GRIDX_API static CObject* PASCAL CreateObject();
	
	#define _GRIDX_DECLARE_DYNCREATE(class_name) \
		_GRIDX_DECLARE_DYNAMIC(class_name) \
		GRIDX_API static CObject* PASCAL CreateObject();
	
	#define GRIDX_DECLARE_SERIAL(class_name) \
		_GRIDX_DECLARE_DYNCREATE(class_name) \
		AFX_API friend GRIDX_API CArchive& AFXAPI operator>>(CArchive& ar, class_name* &pOb);

	// INTERFACE_MAP
	#ifdef _AFXDLL 
		#define GRIDX_DECLARE_INTERFACE_MAP() \
		private: \
			static const AFX_INTERFACEMAP_ENTRY _interfaceEntries[]; \
		protected: \
			static const AFX_INTERFACEMAP interfaceMap; \
			GRIDX_API static const AFX_INTERFACEMAP* PASCAL GetThisInterfaceMap(); \
			GRIDX_API virtual const AFX_INTERFACEMAP* GetInterfaceMap() const; \

	#else
		#define GRIDX_DECLARE_INTERFACE_MAP() \
		private: \
			static const AFX_INTERFACEMAP_ENTRY _interfaceEntries[]; \
		protected: \
			static const AFX_INTERFACEMAP interfaceMap; \
			GRIDX_API virtual const AFX_INTERFACEMAP* GetInterfaceMap() const; \

	#endif // INTERFACE_MAP

	// DISPATCH_MAP
	#ifdef _AFXDLL
		#define GRIDX_DECLARE_DISPATCH_MAP() \
		private: \
			static const AFX_DISPMAP_ENTRY _dispatchEntries[]; \
			static UINT _dispatchEntryCount; \
			static DWORD _dwStockPropMask; \
		protected: \
			static const AFX_DISPMAP dispatchMap; \
			GRIDX_API static const AFX_DISPMAP* PASCAL GetThisDispatchMap(); \
			GRIDX_API virtual const AFX_DISPMAP* GetDispatchMap() const; \

	#else
		#define GRIDX_DECLARE_DISPATCH_MAP() \
		private: \
			static const AFX_DISPMAP_ENTRY _dispatchEntries[]; \
			static UINT _dispatchEntryCount; \
			static DWORD _dwStockPropMask; \
		protected: \
			static const AFX_DISPMAP dispatchMap; \
			GRIDX_API virtual const AFX_DISPMAP* GetDispatchMap() const; \

	#endif // DISPATCH_MAP

	// end Helper Macros

#else // !_GXDLL

	#define GRIDX_DECLARE_MESSAGE_MAP()			DECLARE_MESSAGE_MAP()
	#define GRIDX_DECLARE_DYNAMIC(class_name)	DECLARE_DYNAMIC(class_name)
	#define GRIDX_DECLARE_DYNCREATE(class_name)	DECLARE_DYNCREATE(class_name)
	#define GRIDX_DECLARE_SERIAL(class_name)	DECLARE_SERIAL(class_name)
	#define GRIDX_DECLARE_INTERFACE_MAP()		DECLARE_INTERFACE_MAP()
	#define GRIDX_DECLARE_DISPATCH_MAP()		DECLARE_DISPATCH_MAP()

#endif // GRIDX

////////////////////////////////////////////

#ifdef _GXDLL // Grid for ActiveX

/////////////////////////////////////////////////////////////////////////////
// Window message map handling

	#if(_MSC_VER >= 1310) // Visual Studio 2003 +

		#ifdef _AFXDLL
			#define GRIDX_OGO_DECLARE_MESSAGE_MAP() \
			private: \
				static const AFX_MSGMAP_ENTRY _messageEntries[]; \
			protected: \
				static const AFX_MSGMAP messageMap; \
				GRIDX_OGO_API static const AFX_MSGMAP* PASCAL GetThisMessageMap(); \
				GRIDX_OGO_API virtual const AFX_MSGMAP* GetMessageMap() const; \

		#else
			#define GRIDX_OGO_DECLARE_MESSAGE_MAP() \
			private: \
				static const AFX_MSGMAP_ENTRY _messageEntries[]; \
			protected: \
				static const AFX_MSGMAP messageMap; \
				GRIDX_OGO_API virtual const AFX_MSGMAP* GetMessageMap() const; \

		#endif

	#elif(_MSC_VER == 1200) // MSVC6

		#ifdef _AFXDLL
			#define GRIDX_OGO_DECLARE_MESSAGE_MAP() \
			private: \
				static const AFX_MSGMAP_ENTRY _messageEntries[]; \
			protected: \
				static AFX_DATA const AFX_MSGMAP messageMap; \
				GRIDX_OGO_API static const AFX_MSGMAP* PASCAL _GetBaseMessageMap(); \
				GRIDX_OGO_API virtual const AFX_MSGMAP* GetMessageMap() const; \

		#else
			#define GRIDX_OGO_DECLARE_MESSAGE_MAP() \
			private: \
				static const AFX_MSGMAP_ENTRY _messageEntries[]; \
			protected: \
				static AFX_DATA const AFX_MSGMAP messageMap; \
				GRIDX_OGO_API virtual const AFX_MSGMAP* GetMessageMap() const; \

		#endif

	#else // !_MSC_VER >= 1310

		#define GRIDX_OGO_DECLARE_MESSAGE_MAP()			DECLARE_MESSAGE_MAP()

	#endif

	//////////////////////////////////////////////////////////////////////////////
	// Helper macros for declaring CRuntimeClass compatible classes
	#if(_MSC_VER >= 1310)

		#ifdef _AFXDLL
			#define GRIDX_OGO_DECLARE_DYNAMIC(class_name) \
			protected: \
				GRIDX_OGO_API static CRuntimeClass* PASCAL _GetBaseClass(); \
			public: \
				static const CRuntimeClass class##class_name; \
				GRIDX_OGO_API static CRuntimeClass* PASCAL GetThisClass(); \
				GRIDX_OGO_API virtual CRuntimeClass* GetRuntimeClass() const; 
			
			#define _GRIDX_OGO_DECLARE_DYNAMIC(class_name) \
			protected: \
				GRIDX_OGO_API static CRuntimeClass* PASCAL _GetBaseClass(); \
			public: \
				static CRuntimeClass class##class_name; \
				GRIDX_OGO_API static CRuntimeClass* PASCAL GetThisClass(); \
				GRIDX_OGO_API virtual CRuntimeClass* GetRuntimeClass() const; 

		#else // !_AFXDLL

			#define GRIDX_OGO_DECLARE_DYNAMIC(class_name) \
			public: \
				static const CRuntimeClass class##class_name; \
				GRIDX_OGO_API virtual CRuntimeClass* GetRuntimeClass() const;
			
			#define _GRIDX_OGO_DECLARE_DYNAMIC(class_name) \
			public: \
				static CRuntimeClass class##class_name; \
				GRIDX_OGO_API virtual CRuntimeClass* GetRuntimeClass() const;

		#endif // MFC DLL/LIB

	#elif(_MSC_VER == 1200)

		#ifdef _AFXDLL
			#define GRIDX_OGO_DECLARE_DYNAMIC(class_name) \
			protected: \
				GRIDX_OGO_API static CRuntimeClass* PASCAL _GetBaseClass(); \
			public: \
				static const AFX_DATA CRuntimeClass class##class_name; \
				GRIDX_OGO_API virtual CRuntimeClass* GetRuntimeClass() const; \

			#define _GRIDX_OGO_DECLARE_DYNAMIC(class_name) \
			protected: \
				GRIDX_OGO_API static CRuntimeClass* PASCAL _GetBaseClass(); \
			public: \
				static AFX_DATA CRuntimeClass class##class_name; \
				GRIDX_OGO_API virtual CRuntimeClass* GetRuntimeClass() const; \

		#else
			#define GRIDX_OGO_DECLARE_DYNAMIC(class_name) \
			public: \
				static const AFX_DATA CRuntimeClass class##class_name; \
				GRIDX_OGO_API virtual CRuntimeClass* GetRuntimeClass() const; \

			#define _GRIDX_OGO_DECLARE_DYNAMIC(class_name) \
			public: \
				static AFX_DATA CRuntimeClass class##class_name; \
				GRIDX_OGO_API virtual CRuntimeClass* GetRuntimeClass() const; \

		#endif // _AFXDLL

	#else

		#define GRIDX_OGO_DECLARE_DYNAMIC(class_name)	DECLARE_DYNAMIC(class_name)

	#endif // Declare Dynamic
		
	// not serializable, but dynamically constructable
	#define GRIDX_OGO_DECLARE_DYNCREATE(class_name) \
		GRIDX_OGO_DECLARE_DYNAMIC(class_name) \
		GRIDX_OGO_API static CObject* PASCAL CreateObject();
	
	#define _GRIDX_OGO_DECLARE_DYNCREATE(class_name) \
		_GRIDX_OGO_DECLARE_DYNAMIC(class_name) \
		GRIDX_OGO_API static CObject* PASCAL CreateObject();
	
	#define GRIDX_OGO_DECLARE_SERIAL(class_name) \
		_GRIDX_OGO_DECLARE_DYNCREATE(class_name) \
		AFX_API friend GRIDX_OGO_API CArchive& AFXAPI operator>>(CArchive& ar, class_name* &pOb);

	// INTERFACE_MAP
	#ifdef _AFXDLL 
		#define GRIDX_OGO_DECLARE_INTERFACE_MAP() \
		private: \
			static const AFX_INTERFACEMAP_ENTRY _interfaceEntries[]; \
		protected: \
			static const AFX_INTERFACEMAP interfaceMap; \
			GRIDX_OGO_API static const AFX_INTERFACEMAP* PASCAL GetThisInterfaceMap(); \
			GRIDX_OGO_API virtual const AFX_INTERFACEMAP* GetInterfaceMap() const; \

	#else
		#define GRIDX_OGO_DECLARE_INTERFACE_MAP() \
		private: \
			static const AFX_INTERFACEMAP_ENTRY _interfaceEntries[]; \
		protected: \
			static const AFX_INTERFACEMAP interfaceMap; \
			GRIDX_OGO_API virtual const AFX_INTERFACEMAP* GetInterfaceMap() const; \

	#endif // INTERFACE_MAP

	// DISPATCH_MAP
	#ifdef _AFXDLL
		#define GRIDX_OGO_DECLARE_DISPATCH_MAP() \
		private: \
			static const AFX_DISPMAP_ENTRY _dispatchEntries[]; \
			static UINT _dispatchEntryCount; \
			static DWORD _dwStockPropMask; \
		protected: \
			static const AFX_DISPMAP dispatchMap; \
			GRIDX_OGO_API static const AFX_DISPMAP* PASCAL GetThisDispatchMap(); \
			GRIDX_OGO_API virtual const AFX_DISPMAP* GetDispatchMap() const; \

	#else
		#define GRIDX_OGO_DECLARE_DISPATCH_MAP() \
		private: \
			static const AFX_DISPMAP_ENTRY _dispatchEntries[]; \
			static UINT _dispatchEntryCount; \
			static DWORD _dwStockPropMask; \
		protected: \
			static const AFX_DISPMAP dispatchMap; \
			GRIDX_OGO_API virtual const AFX_DISPMAP* GetDispatchMap() const; \

	#endif // DISPATCH_MAP

	#define GRIDX_OGO_DECLARE_CONTROL(class_name) \
	protected: \
		GRIDX_OGO_API static CGXControlClass* PASCAL _GetControlBaseClass(); \
	public: \
		static GX_DATA CGXControlClass ctrl##class_name; \
		GRIDX_OGO_API virtual CGXControlClass* GetControlClass() const; \

	#define GRIDX_OGO_IMPLEMENT_CONTROL(class_name, base_class_name) \
		CGXControlClass* PASCAL class_name::_GetControlBaseClass() \
			{ return CONTROL_CLASS(base_class_name); } \
		GX_DATADEF CGXControlClass class_name::ctrl##class_name = { \
			#class_name, &class_name::_GetControlBaseClass }; \
		CGXControlClass* class_name::GetControlClass() const \
			{ return &class_name::ctrl##class_name; } \

	// end Helper Macros

#else // !_GXDLL

	#define GRIDX_OGO_DECLARE_MESSAGE_MAP()			DECLARE_MESSAGE_MAP()
	#define GRIDX_OGO_DECLARE_DYNAMIC(class_name)	DECLARE_DYNAMIC(class_name)
	#define GRIDX_OGO_DECLARE_DYNCREATE(class_name)	DECLARE_DYNCREATE(class_name)
	#define GRIDX_OGO_DECLARE_SERIAL(class_name)	DECLARE_SERIAL(class_name)
	#define GRIDX_OGO_DECLARE_INTERFACE_MAP()		DECLARE_INTERFACE_MAP()
	#define GRIDX_OGO_DECLARE_DISPATCH_MAP()		DECLARE_DISPATCH_MAP()

	#define GRIDX_OGO_DECLARE_CONTROL(class_name) \
	public: \
		static CGXControlClass GXNEAR ctrl##class_name; \
		GRIDX_OGO_API virtual CGXControlClass* GetControlClass() const; \

	#define GRIDX_OGO_IMPLEMENT_CONTROL(class_name, base_class_name) \
		CGXControlClass GXNEAR class_name::ctrl##class_name = { \
			#class_name, CONTROL_CLASS(base_class_name) }; \
		CGXControlClass* class_name::GetControlClass() const \
			{ return &class_name::ctrl##class_name; } \

#endif // GRIDX_OGO

#ifdef _GXDLL // Grid for ActiveX

/////////////////////////////////////////////////////////////////////////////
// Window message map handling

	#if(_MSC_VER >= 1310) // Visual Studio 2003 +

		#ifdef _AFXDLL
			#define GRIDX_DB_DECLARE_MESSAGE_MAP() \
			private: \
				static const AFX_MSGMAP_ENTRY _messageEntries[]; \
			protected: \
				static const AFX_MSGMAP messageMap; \
				GRIDX_DB_API static const AFX_MSGMAP* PASCAL GetThisMessageMap(); \
				GRIDX_DB_API virtual const AFX_MSGMAP* GetMessageMap() const; \

		#else
			#define GRIDX_DB_DECLARE_MESSAGE_MAP() \
			private: \
				static const AFX_MSGMAP_ENTRY _messageEntries[]; \
			protected: \
				static const AFX_MSGMAP messageMap; \
				GRIDX_DB_API virtual const AFX_MSGMAP* GetMessageMap() const; \

		#endif

	#elif(_MSC_VER == 1200) // MSVC6

		#ifdef _AFXDLL
			#define GRIDX_DB_DECLARE_MESSAGE_MAP() \
			private: \
				static const AFX_MSGMAP_ENTRY _messageEntries[]; \
			protected: \
				static AFX_DATA const AFX_MSGMAP messageMap; \
				GRIDX_DB_API static const AFX_MSGMAP* PASCAL _GetBaseMessageMap(); \
				GRIDX_DB_API virtual const AFX_MSGMAP* GetMessageMap() const; \

		#else
			#define GRIDX_DB_DECLARE_MESSAGE_MAP() \
			private: \
				static const AFX_MSGMAP_ENTRY _messageEntries[]; \
			protected: \
				static AFX_DATA const AFX_MSGMAP messageMap; \
				GRIDX_DB_API virtual const AFX_MSGMAP* GetMessageMap() const; \

		#endif

	#else // !_MSC_VER >= 1310

		#define GRIDX_DB_DECLARE_MESSAGE_MAP()			DECLARE_MESSAGE_MAP()

	#endif

	//////////////////////////////////////////////////////////////////////////////
	// Helper macros for declaring CRuntimeClass compatible classes
	#if(_MSC_VER >= 1310)

		#ifdef _AFXDLL
			#define GRIDX_DB_DECLARE_DYNAMIC(class_name) \
			protected: \
				GRIDX_DB_API static CRuntimeClass* PASCAL _GetBaseClass(); \
			public: \
				static const CRuntimeClass class##class_name; \
				GRIDX_DB_API static CRuntimeClass* PASCAL GetThisClass(); \
				GRIDX_DB_API virtual CRuntimeClass* GetRuntimeClass() const; 
			
			#define _GRIDX_DB_DECLARE_DYNAMIC(class_name) \
			protected: \
				GRIDX_DB_API static CRuntimeClass* PASCAL _GetBaseClass(); \
			public: \
				static CRuntimeClass class##class_name; \
				GRIDX_DB_API static CRuntimeClass* PASCAL GetThisClass(); \
				GRIDX_DB_API virtual CRuntimeClass* GetRuntimeClass() const; 

		#else // !_AFXDLL

			#define GRIDX_DB_DECLARE_DYNAMIC(class_name) \
			public: \
				static const CRuntimeClass class##class_name; \
				GRIDX_DB_API virtual CRuntimeClass* GetRuntimeClass() const;
			
			#define _GRIDX_DB_DECLARE_DYNAMIC(class_name) \
			public: \
				static CRuntimeClass class##class_name; \
				GRIDX_DB_API virtual CRuntimeClass* GetRuntimeClass() const;

		#endif // MFC DLL/LIB

	#elif(_MSC_VER == 1200)

		#ifdef _AFXDLL
			#define GRIDX_DB_DECLARE_DYNAMIC(class_name) \
			protected: \
				GRIDX_DB_API static CRuntimeClass* PASCAL _GetBaseClass(); \
			public: \
				static const AFX_DATA CRuntimeClass class##class_name; \
				GRIDX_DB_API virtual CRuntimeClass* GetRuntimeClass() const; \

			#define _GRIDX_DB_DECLARE_DYNAMIC(class_name) \
			protected: \
				GRIDX_DB_API static CRuntimeClass* PASCAL _GetBaseClass(); \
			public: \
				static AFX_DATA CRuntimeClass class##class_name; \
				GRIDX_DB_API virtual CRuntimeClass* GetRuntimeClass() const; \

		#else
			#define GRIDX_DB_DECLARE_DYNAMIC(class_name) \
			public: \
				static const AFX_DATA CRuntimeClass class##class_name; \
				GRIDX_DB_API virtual CRuntimeClass* GetRuntimeClass() const; \

			#define _GRIDX_DB_DECLARE_DYNAMIC(class_name) \
			public: \
				static AFX_DATA CRuntimeClass class##class_name; \
				GRIDX_DB_API virtual CRuntimeClass* GetRuntimeClass() const; \

		#endif // _AFXDLL

	#else

		#define GRIDX_DB_DECLARE_DYNAMIC(class_name)	DECLARE_DYNAMIC(class_name)

	#endif // Declare Dynamic
		
	// not serializable, but dynamically constructable
	#define GRIDX_DB_DECLARE_DYNCREATE(class_name) \
		GRIDX_DB_DECLARE_DYNAMIC(class_name) \
		GRIDX_DB_API static CObject* PASCAL CreateObject();
	
	#define _GRIDX_DB_DECLARE_DYNCREATE(class_name) \
		_GRIDX_DB_DECLARE_DYNAMIC(class_name) \
		GRIDX_DB_API static CObject* PASCAL CreateObject();
	
	#define GRIDX_DB_DECLARE_SERIAL(class_name) \
		_GRIDX_DB_DECLARE_DYNCREATE(class_name) \
		AFX_API friend GRIDX_DB_API CArchive& AFXAPI operator>>(CArchive& ar, class_name* &pOb);

	// INTERFACE_MAP
	#ifdef _AFXDLL 
		#define GRIDX_DB_DECLARE_INTERFACE_MAP() \
		private: \
			static const AFX_INTERFACEMAP_ENTRY _interfaceEntries[]; \
		protected: \
			static const AFX_INTERFACEMAP interfaceMap; \
			GRIDX_DB_API static const AFX_INTERFACEMAP* PASCAL GetThisInterfaceMap(); \
			GRIDX_DB_API virtual const AFX_INTERFACEMAP* GetInterfaceMap() const; \

	#else
		#define GRIDX_DB_DECLARE_INTERFACE_MAP() \
		private: \
			static const AFX_INTERFACEMAP_ENTRY _interfaceEntries[]; \
		protected: \
			static const AFX_INTERFACEMAP interfaceMap; \
			GRIDX_DB_API virtual const AFX_INTERFACEMAP* GetInterfaceMap() const; \

	#endif // INTERFACE_MAP

	// DISPATCH_MAP
	#ifdef _AFXDLL
		#define GRIDX_DB_DECLARE_DISPATCH_MAP() \
		private: \
			static const AFX_DISPMAP_ENTRY _dispatchEntries[]; \
			static UINT _dispatchEntryCount; \
			static DWORD _dwStockPropMask; \
		protected: \
			static const AFX_DISPMAP dispatchMap; \
			GRIDX_DB_API static const AFX_DISPMAP* PASCAL GetThisDispatchMap(); \
			GRIDX_DB_API virtual const AFX_DISPMAP* GetDispatchMap() const; \

	#else
		#define GRIDX_DB_DECLARE_DISPATCH_MAP() \
		private: \
			static const AFX_DISPMAP_ENTRY _dispatchEntries[]; \
			static UINT _dispatchEntryCount; \
			static DWORD _dwStockPropMask; \
		protected: \
			static const AFX_DISPMAP dispatchMap; \
			GRIDX_DB_API virtual const AFX_DISPMAP* GetDispatchMap() const; \

	#endif // DISPATCH_MAP

	// end Helper Macros

#else // !_GXDLL

	#define GRIDX_DB_DECLARE_MESSAGE_MAP()			DECLARE_MESSAGE_MAP()
	#define GRIDX_DB_DECLARE_DYNAMIC(class_name)	DECLARE_DYNAMIC(class_name)
	#define GRIDX_DB_DECLARE_DYNCREATE(class_name)	DECLARE_DYNCREATE(class_name)
	#define GRIDX_DB_DECLARE_SERIAL(class_name)	DECLARE_SERIAL(class_name)
	#define GRIDX_DB_DECLARE_INTERFACE_MAP()		DECLARE_INTERFACE_MAP()
	#define GRIDX_DB_DECLARE_DISPATCH_MAP()		DECLARE_DISPATCH_MAP()

#endif // GRIDX_DB

#ifdef _GXDLL // Grid for ActiveX

/////////////////////////////////////////////////////////////////////////////
// Window message map handling

	#if(_MSC_VER >= 1310) // Visual Studio 2003 +

		#ifdef _AFXDLL
			#define GRIDX_ADO_DECLARE_MESSAGE_MAP() \
			private: \
				static const AFX_MSGMAP_ENTRY _messageEntries[]; \
			protected: \
				static const AFX_MSGMAP messageMap; \
				GRIDX_ADO_API static const AFX_MSGMAP* PASCAL GetThisMessageMap(); \
				GRIDX_ADO_API virtual const AFX_MSGMAP* GetMessageMap() const; \

		#else
			#define GRIDX_ADO_DECLARE_MESSAGE_MAP() \
			private: \
				static const AFX_MSGMAP_ENTRY _messageEntries[]; \
			protected: \
				static const AFX_MSGMAP messageMap; \
				GRIDX_ADO_API virtual const AFX_MSGMAP* GetMessageMap() const; \

		#endif

	#elif(_MSC_VER == 1200) // MSVC6

		#ifdef _AFXDLL
			#define GRIDX_ADO_DECLARE_MESSAGE_MAP() \
			private: \
				static const AFX_MSGMAP_ENTRY _messageEntries[]; \
			protected: \
				static AFX_DATA const AFX_MSGMAP messageMap; \
				GRIDX_ADO_API static const AFX_MSGMAP* PASCAL _GetBaseMessageMap(); \
				GRIDX_ADO_API virtual const AFX_MSGMAP* GetMessageMap() const; \

		#else
			#define GRIDX_ADO_DECLARE_MESSAGE_MAP() \
			private: \
				static const AFX_MSGMAP_ENTRY _messageEntries[]; \
			protected: \
				static AFX_DATA const AFX_MSGMAP messageMap; \
				GRIDX_ADO_API virtual const AFX_MSGMAP* GetMessageMap() const; \

		#endif

	#else // !_MSC_VER >= 1310

		#define GRIDX_ADO_DECLARE_MESSAGE_MAP()			DECLARE_MESSAGE_MAP()

	#endif

	//////////////////////////////////////////////////////////////////////////////
	// Helper macros for declaring CRuntimeClass compatible classes
	#if(_MSC_VER >= 1310)

		#ifdef _AFXDLL
			#define GRIDX_ADO_DECLARE_DYNAMIC(class_name) \
			protected: \
				GRIDX_ADO_API static CRuntimeClass* PASCAL _GetBaseClass(); \
			public: \
				static const CRuntimeClass class##class_name; \
				GRIDX_ADO_API static CRuntimeClass* PASCAL GetThisClass(); \
				GRIDX_ADO_API virtual CRuntimeClass* GetRuntimeClass() const; 
			
			#define _GRIDX_ADO_DECLARE_DYNAMIC(class_name) \
			protected: \
				GRIDX_ADO_API static CRuntimeClass* PASCAL _GetBaseClass(); \
			public: \
				static CRuntimeClass class##class_name; \
				GRIDX_ADO_API static CRuntimeClass* PASCAL GetThisClass(); \
				GRIDX_ADO_API virtual CRuntimeClass* GetRuntimeClass() const; 

		#else // !_AFXDLL

			#define GRIDX_ADO_DECLARE_DYNAMIC(class_name) \
			public: \
				static const CRuntimeClass class##class_name; \
				GRIDX_ADO_API virtual CRuntimeClass* GetRuntimeClass() const;
			
			#define _GRIDX_ADO_DECLARE_DYNAMIC(class_name) \
			public: \
				static CRuntimeClass class##class_name; \
				GRIDX_ADO_API virtual CRuntimeClass* GetRuntimeClass() const;

		#endif // MFC DLL/LIB

	#elif(_MSC_VER == 1200)

		#ifdef _AFXDLL
			#define GRIDX_ADO_DECLARE_DYNAMIC(class_name) \
			protected: \
				GRIDX_ADO_API static CRuntimeClass* PASCAL _GetBaseClass(); \
			public: \
				static const AFX_DATA CRuntimeClass class##class_name; \
				GRIDX_ADO_API virtual CRuntimeClass* GetRuntimeClass() const; \

			#define _GRIDX_ADO_DECLARE_DYNAMIC(class_name) \
			protected: \
				GRIDX_ADO_API static CRuntimeClass* PASCAL _GetBaseClass(); \
			public: \
				static AFX_DATA CRuntimeClass class##class_name; \
				GRIDX_ADO_API virtual CRuntimeClass* GetRuntimeClass() const; \

		#else
			#define GRIDX_ADO_DECLARE_DYNAMIC(class_name) \
			public: \
				static const AFX_DATA CRuntimeClass class##class_name; \
				GRIDX_ADO_API virtual CRuntimeClass* GetRuntimeClass() const; \

			#define _GRIDX_ADO_DECLARE_DYNAMIC(class_name) \
			public: \
				static AFX_DATA CRuntimeClass class##class_name; \
				GRIDX_ADO_API virtual CRuntimeClass* GetRuntimeClass() const; \

		#endif // _AFXDLL

	#else

		#define GRIDX_ADO_DECLARE_DYNAMIC(class_name)	DECLARE_DYNAMIC(class_name)

	#endif // Declare Dynamic
		
	// not serializable, but dynamically constructable
	#define GRIDX_ADO_DECLARE_DYNCREATE(class_name) \
		GRIDX_ADO_DECLARE_DYNAMIC(class_name) \
		GRIDX_ADO_API static CObject* PASCAL CreateObject();
	
	#define _GRIDX_ADO_DECLARE_DYNCREATE(class_name) \
		_GRIDX_ADO_DECLARE_DYNAMIC(class_name) \
		GRIDX_ADO_API static CObject* PASCAL CreateObject();
	
	#define GRIDX_ADO_DECLARE_SERIAL(class_name) \
		_GRIDX_ADO_DECLARE_DYNCREATE(class_name) \
		AFX_API friend GRIDX_ADO_API CArchive& AFXAPI operator>>(CArchive& ar, class_name* &pOb);

	// INTERFACE_MAP
	#ifdef _AFXDLL 
		#define GRIDX_ADO_DECLARE_INTERFACE_MAP() \
		private: \
			static const AFX_INTERFACEMAP_ENTRY _interfaceEntries[]; \
		protected: \
			static const AFX_INTERFACEMAP interfaceMap; \
			GRIDX_ADO_API static const AFX_INTERFACEMAP* PASCAL GetThisInterfaceMap(); \
			GRIDX_ADO_API virtual const AFX_INTERFACEMAP* GetInterfaceMap() const; \

	#else
		#define GRIDX_ADO_DECLARE_INTERFACE_MAP() \
		private: \
			static const AFX_INTERFACEMAP_ENTRY _interfaceEntries[]; \
		protected: \
			static const AFX_INTERFACEMAP interfaceMap; \
			GRIDX_ADO_API virtual const AFX_INTERFACEMAP* GetInterfaceMap() const; \

	#endif // INTERFACE_MAP

	// DISPATCH_MAP
	#ifdef _AFXDLL
		#define GRIDX_ADO_DECLARE_DISPATCH_MAP() \
		private: \
			static const AFX_DISPMAP_ENTRY _dispatchEntries[]; \
			static UINT _dispatchEntryCount; \
			static DWORD _dwStockPropMask; \
		protected: \
			static const AFX_DISPMAP dispatchMap; \
			GRIDX_ADO_API static const AFX_DISPMAP* PASCAL GetThisDispatchMap(); \
			GRIDX_ADO_API virtual const AFX_DISPMAP* GetDispatchMap() const; \

	#else
		#define GRIDX_ADO_DECLARE_DISPATCH_MAP() \
		private: \
			static const AFX_DISPMAP_ENTRY _dispatchEntries[]; \
			static UINT _dispatchEntryCount; \
			static DWORD _dwStockPropMask; \
		protected: \
			static const AFX_DISPMAP dispatchMap; \
			GRIDX_ADO_API virtual const AFX_DISPMAP* GetDispatchMap() const; \

	#endif // DISPATCH_MAP

	// end Helper Macros

#else // !_GXDLL

	#define GRIDX_ADO_DECLARE_MESSAGE_MAP()			DECLARE_MESSAGE_MAP()
	#define GRIDX_ADO_DECLARE_DYNAMIC(class_name)	DECLARE_DYNAMIC(class_name)
	#define GRIDX_ADO_DECLARE_DYNCREATE(class_name)	DECLARE_DYNCREATE(class_name)
	#define GRIDX_ADO_DECLARE_SERIAL(class_name)	DECLARE_SERIAL(class_name)
	#define GRIDX_ADO_DECLARE_INTERFACE_MAP()		DECLARE_INTERFACE_MAP()
	#define GRIDX_ADO_DECLARE_DISPATCH_MAP()		DECLARE_DISPATCH_MAP()

#endif // GRIDX_ADO

#ifdef _GXDLL // Grid for ActiveX

/////////////////////////////////////////////////////////////////////////////
// Window message map handling

	#if(_MSC_VER >= 1310) // Visual Studio 2003 +

		#ifdef _AFXDLL
			#define GRIDX_DAO_DECLARE_MESSAGE_MAP() \
			private: \
				static const AFX_MSGMAP_ENTRY _messageEntries[]; \
			protected: \
				static const AFX_MSGMAP messageMap; \
				GRIDX_DAO_API static const AFX_MSGMAP* PASCAL GetThisMessageMap(); \
				GRIDX_DAO_API virtual const AFX_MSGMAP* GetMessageMap() const; \

		#else
			#define GRIDX_DAO_DECLARE_MESSAGE_MAP() \
			private: \
				static const AFX_MSGMAP_ENTRY _messageEntries[]; \
			protected: \
				static const AFX_MSGMAP messageMap; \
				GRIDX_DAO_API virtual const AFX_MSGMAP* GetMessageMap() const; \

		#endif

	#elif(_MSC_VER == 1200) // MSVC6

		#ifdef _AFXDLL
			#define GRIDX_DAO_DECLARE_MESSAGE_MAP() \
			private: \
				static const AFX_MSGMAP_ENTRY _messageEntries[]; \
			protected: \
				static AFX_DATA const AFX_MSGMAP messageMap; \
				GRIDX_DAO_API static const AFX_MSGMAP* PASCAL _GetBaseMessageMap(); \
				GRIDX_DAO_API virtual const AFX_MSGMAP* GetMessageMap() const; \

		#else
			#define GRIDX_DAO_DECLARE_MESSAGE_MAP() \
			private: \
				static const AFX_MSGMAP_ENTRY _messageEntries[]; \
			protected: \
				static AFX_DATA const AFX_MSGMAP messageMap; \
				GRIDX_DAO_API virtual const AFX_MSGMAP* GetMessageMap() const; \

		#endif

	#else // !_MSC_VER >= 1310

		#define GRIDX_DAO_DECLARE_MESSAGE_MAP()			DECLARE_MESSAGE_MAP()

	#endif

	//////////////////////////////////////////////////////////////////////////////
	// Helper macros for declaring CRuntimeClass compatible classes
	#if(_MSC_VER >= 1310)

		#ifdef _AFXDLL
			#define GRIDX_DAO_DECLARE_DYNAMIC(class_name) \
			protected: \
				GRIDX_DAO_API static CRuntimeClass* PASCAL _GetBaseClass(); \
			public: \
				static const CRuntimeClass class##class_name; \
				GRIDX_DAO_API static CRuntimeClass* PASCAL GetThisClass(); \
				GRIDX_DAO_API virtual CRuntimeClass* GetRuntimeClass() const; 
			
			#define _GRIDX_DAO_DECLARE_DYNAMIC(class_name) \
			protected: \
				GRIDX_DAO_API static CRuntimeClass* PASCAL _GetBaseClass(); \
			public: \
				static CRuntimeClass class##class_name; \
				GRIDX_DAO_API static CRuntimeClass* PASCAL GetThisClass(); \
				GRIDX_DAO_API virtual CRuntimeClass* GetRuntimeClass() const; 

		#else // !_AFXDLL

			#define GRIDX_DAO_DECLARE_DYNAMIC(class_name) \
			public: \
				static const CRuntimeClass class##class_name; \
				GRIDX_DAO_API virtual CRuntimeClass* GetRuntimeClass() const;
			
			#define _GRIDX_DAO_DECLARE_DYNAMIC(class_name) \
			public: \
				static CRuntimeClass class##class_name; \
				GRIDX_DAO_API virtual CRuntimeClass* GetRuntimeClass() const;

		#endif // MFC DLL/LIB

	#elif(_MSC_VER == 1200)

		#ifdef _AFXDLL
			#define GRIDX_DAO_DECLARE_DYNAMIC(class_name) \
			protected: \
				GRIDX_DAO_API static CRuntimeClass* PASCAL _GetBaseClass(); \
			public: \
				static const AFX_DATA CRuntimeClass class##class_name; \
				GRIDX_DAO_API virtual CRuntimeClass* GetRuntimeClass() const; \

			#define _GRIDX_DAO_DECLARE_DYNAMIC(class_name) \
			protected: \
				GRIDX_DAO_API static CRuntimeClass* PASCAL _GetBaseClass(); \
			public: \
				static AFX_DATA CRuntimeClass class##class_name; \
				GRIDX_DAO_API virtual CRuntimeClass* GetRuntimeClass() const; \

		#else
			#define GRIDX_DAO_DECLARE_DYNAMIC(class_name) \
			public: \
				static const AFX_DATA CRuntimeClass class##class_name; \
				GRIDX_DAO_API virtual CRuntimeClass* GetRuntimeClass() const; \

			#define _GRIDX_DAO_DECLARE_DYNAMIC(class_name) \
			public: \
				static AFX_DATA CRuntimeClass class##class_name; \
				GRIDX_DAO_API virtual CRuntimeClass* GetRuntimeClass() const; \

		#endif // _AFXDLL

	#else

		#define GRIDX_DAO_DECLARE_DYNAMIC(class_name)	DECLARE_DYNAMIC(class_name)

	#endif // Declare Dynamic
		
	// not serializable, but dynamically constructable
	#define GRIDX_DAO_DECLARE_DYNCREATE(class_name) \
		GRIDX_DAO_DECLARE_DYNAMIC(class_name) \
		GRIDX_DAO_API static CObject* PASCAL CreateObject();
	
	#define _GRIDX_DAO_DECLARE_DYNCREATE(class_name) \
		_GRIDX_DAO_DECLARE_DYNAMIC(class_name) \
		GRIDX_DAO_API static CObject* PASCAL CreateObject();
	
	#define GRIDX_DAO_DECLARE_SERIAL(class_name) \
		_GRIDX_DAO_DECLARE_DYNCREATE(class_name) \
		AFX_API friend GRIDX_DAO_API CArchive& AFXAPI operator>>(CArchive& ar, class_name* &pOb);

	// INTERFACE_MAP
	#ifdef _AFXDLL 
		#define GRIDX_DAO_DECLARE_INTERFACE_MAP() \
		private: \
			static const AFX_INTERFACEMAP_ENTRY _interfaceEntries[]; \
		protected: \
			static const AFX_INTERFACEMAP interfaceMap; \
			GRIDX_DAO_API static const AFX_INTERFACEMAP* PASCAL GetThisInterfaceMap(); \
			GRIDX_DAO_API virtual const AFX_INTERFACEMAP* GetInterfaceMap() const; \

	#else
		#define GRIDX_DAO_DECLARE_INTERFACE_MAP() \
		private: \
			static const AFX_INTERFACEMAP_ENTRY _interfaceEntries[]; \
		protected: \
			static const AFX_INTERFACEMAP interfaceMap; \
			GRIDX_DAO_API virtual const AFX_INTERFACEMAP* GetInterfaceMap() const; \

	#endif // INTERFACE_MAP

	// DISPATCH_MAP
	#ifdef _AFXDLL
		#define GRIDX_DAO_DECLARE_DISPATCH_MAP() \
		private: \
			static const AFX_DISPMAP_ENTRY _dispatchEntries[]; \
			static UINT _dispatchEntryCount; \
			static DWORD _dwStockPropMask; \
		protected: \
			static const AFX_DISPMAP dispatchMap; \
			GRIDX_DAO_API static const AFX_DISPMAP* PASCAL GetThisDispatchMap(); \
			GRIDX_DAO_API virtual const AFX_DISPMAP* GetDispatchMap() const; \

	#else
		#define GRIDX_DAO_DECLARE_DISPATCH_MAP() \
		private: \
			static const AFX_DISPMAP_ENTRY _dispatchEntries[]; \
			static UINT _dispatchEntryCount; \
			static DWORD _dwStockPropMask; \
		protected: \
			static const AFX_DISPMAP dispatchMap; \
			GRIDX_DAO_API virtual const AFX_DISPMAP* GetDispatchMap() const; \

	#endif // DISPATCH_MAP

	// end Helper Macros

#else // !_GXDLL

	#define GRIDX_DAO_DECLARE_MESSAGE_MAP()			DECLARE_MESSAGE_MAP()
	#define GRIDX_DAO_DECLARE_DYNAMIC(class_name)	DECLARE_DYNAMIC(class_name)
	#define GRIDX_DAO_DECLARE_DYNCREATE(class_name)	DECLARE_DYNCREATE(class_name)
	#define GRIDX_DAO_DECLARE_SERIAL(class_name)	DECLARE_SERIAL(class_name)
	#define GRIDX_DAO_DECLARE_INTERFACE_MAP()		DECLARE_INTERFACE_MAP()
	#define GRIDX_DAO_DECLARE_DISPATCH_MAP()		DECLARE_DISPATCH_MAP()

#endif // GRIDX_DAO

// Backward compatiblity with versions <= Stingray Studio 2006 v3 (CD49U1)
#define _SFLDLL_IMPL	_SFL_EXPORT_IMPL
#define _OC_DLL_IMPL	_OC_EXPORT_IMPL
#define _OE_DLL_IMPL	_OE_EXPORT_IMPL
#define _GXDLL_IMPL		_GX_EXPORT_IMPL
#define _SECDLL_IMPL	_OT_EXPORT_IMPL
#define _OV_DLL_IMPL	_OV_EXPORT_IMPL

#endif //STINGRAY_EXPORT_H_


