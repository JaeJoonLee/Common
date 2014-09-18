///////////////////////////////////////////////////////////////////////////////
// CustExtDefs.h
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

#if !defined __CUSTEXTDEFS__H__
#define __CUSTEXTDEFS__H__

// For Customer/Application/Sample use of an MFC Extension Dynamic Link Library.
#pragma message("Stingray Extension Dll")

//-----------------------------------------------------------------------------
// USAGE:
//
// Project Settings:
// Add "_CUSTEXTDLL" to your C++ Preprocessor Definitions.
// Add "_AFXDLL" to your C++ Preprocessor Definitions.
// Make sure the project Configuration Type is set to "Dynamic Library (.dll)."
// Make sure the project Use of MFC is set to "MFC in a Shared Dll."
// For Debug, set the Code Generation Runtime Library to /MDd. 
// For Release, set the Code Generation Runtime Library to /MD.
//
// Code:
// Include this header file in your project.
// Add "#define _CUSTEXTEXPORT_IMPL" to the top of stdafx.cpp.
// Use export definitions below as needed to export needed functionality.
//-----------------------------------------------------------------------------

#ifdef _CUSTEXTDLL // (Dll Build)
	#ifdef _CUSTEXTEXPORT_IMPL // We're building
			#pragma message("Exporting from Extension Dll")
			// Reference to a GLOBAL Function, these must be inline definitions with no 
			// function prototype.
			#define CUSTEXT_GLOBAL_FUNC_API(rettype)	extern "C" rettype	__declspec(dllexport) 
			// Reference to a CLASS Function
			#define CUSTEXT_CLASS_FUNC_API				__declspec(dllexport)
			// Reference to a GLOBAL Variable
			#define CUSTEXT_GLOBAL_VAR_API				CUSTEXT_CLASS_FUNC_API
	#else	// Someone else is linking
			#pragma message("Importing from Extension Dll")
			// Reference to a GLOBAL Function 
			#define CUSTEXT_GLOBAL_FUNC_API(rettype)	extern "C" rettype	__declspec(dllimport)
			// Reference to a CLASS Function
			#define CUSTEXT_CLASS_FUNC_API				__declspec(dllimport)
			// Reference to a GLOBAL Variable
			#define CUSTEXT_GLOBAL_VAR_API				CUSTEXT_CLASS_FUNC_API
	#endif // _CUSTEXTEXPORT_IMPL
#else // !_CUSTEXTDLL (Static Build)
	// Reference to a CLASS Function
	#define CUSTEXT_CLASS_FUNC_API						// Nothing
	// Reference to a GLOBAL Function, these must be inline definitions with no 
	// function prototype.
	#define CUSTEXT_GLOBAL_FUNC_API(rettype)			extern "C" rettype  __cdecl // Don't mangle the name. Must use __cdecl here.

	#ifdef _CUSTEXTEXPORT_IMPL // We're Building
		#pragma message("Exporting from Extension Dll")
	// Reference to a GLOBAL Variable
		#define CUSTEXT_GLOBAL_VAR_API					// Nothing
	#else // Someone else is linking
		// Reference to a GLOBAL Variable
		#define CUSTEXT_GLOBAL_VAR_API					extern				// Someone else has defined the variable.
	#endif // _CUSTEXTEXPORT_IMPL
#endif // _CUSTEXTDLL

/////////////////////////////////////////////////////////////////////////////
// Window message map handling
#ifdef _CUSTEXTDLL // Dynamic Link Library

	#if(_MSC_VER >= 1310) // Visual Studio 2003 +

		#ifdef _AFXDLL
			#define CUSTEXT_DECLARE_MESSAGE_MAP() \
			private: \
				static const AFX_MSGMAP_ENTRY _messageEntries[]; \
			protected: \
				static const AFX_MSGMAP messageMap; \
				CUSTEXT_CLASS_FUNC_API static const AFX_MSGMAP* PASCAL GetThisMessageMap(); \
				CUSTEXT_CLASS_FUNC_API virtual const AFX_MSGMAP* GetMessageMap() const; \

		#else
			#define CUSTEXT_DECLARE_MESSAGE_MAP() \
			private: \
				static const AFX_MSGMAP_ENTRY _messageEntries[]; \
			protected: \
				static const AFX_MSGMAP messageMap; \
				CUSTEXT_CLASS_FUNC_API virtual const AFX_MSGMAP* GetMessageMap() const; \

		#endif

	#elif(_MSC_VER == 1200) // MSVC6

		#ifdef _AFXDLL
			#define CUSTEXT_DECLARE_MESSAGE_MAP() \
			private: \
				static const AFX_MSGMAP_ENTRY _messageEntries[]; \
			protected: \
				static AFX_DATA const AFX_MSGMAP messageMap; \
				CUSTEXT_CLASS_FUNC_API static const AFX_MSGMAP* PASCAL _GetBaseMessageMap(); \
				CUSTEXT_CLASS_FUNC_API virtual const AFX_MSGMAP* GetMessageMap() const; \

		#else
			#define CUSTEXT_DECLARE_MESSAGE_MAP() \
			private: \
				static const AFX_MSGMAP_ENTRY _messageEntries[]; \
			protected: \
				static AFX_DATA const AFX_MSGMAP messageMap; \
				CUSTEXT_CLASS_FUNC_API virtual const AFX_MSGMAP* GetMessageMap() const; \

		#endif

	#else // !_MSC_VER >= 1310

		#define CUSTEXT_DECLARE_MESSAGE_MAP()			DECLARE_MESSAGE_MAP()

	#endif

	//////////////////////////////////////////////////////////////////////////////
	// Helper macros for declaring CRuntimeClass compatible classes
	#if(_MSC_VER >= 1310)

		#ifdef _AFXDLL
			#define CUSTEXT_DECLARE_DYNAMIC(class_name) \
			protected: \
				CUSTEXT_CLASS_FUNC_API static CRuntimeClass* PASCAL _GetBaseClass(); \
			public: \
				static const CRuntimeClass class##class_name; \
				CUSTEXT_CLASS_FUNC_API static CRuntimeClass* PASCAL GetThisClass(); \
				CUSTEXT_CLASS_FUNC_API virtual CRuntimeClass* GetRuntimeClass() const; 
			
			#define _CUSTEXT_DECLARE_DYNAMIC(class_name) \
			protected: \
				CUSTEXT_CLASS_FUNC_API static CRuntimeClass* PASCAL _GetBaseClass(); \
			public: \
				CUSTEXT_CLASS_FUNC_API static CRuntimeClass class##class_name; \
				CUSTEXT_CLASS_FUNC_API static CRuntimeClass* PASCAL GetThisClass(); \
				CUSTEXT_CLASS_FUNC_API virtual CRuntimeClass* GetRuntimeClass() const; 

		#else // !_AFXDLL

			#define CUSTEXT_DECLARE_DYNAMIC(class_name) \
			public: \
				static const CRuntimeClass class##class_name; \
				CUSTEXT_CLASS_FUNC_API virtual CRuntimeClass* GetRuntimeClass() const;
			
			#define _CUSTEXT_DECLARE_DYNAMIC(class_name) \
			public: \
				static CRuntimeClass class##class_name; \
				CUSTEXT_CLASS_FUNC_API virtual CRuntimeClass* GetRuntimeClass() const;

		#endif // MFC DLL/LIB

	#elif(_MSC_VER == 1200)

		#ifdef _AFXDLL
			#define CUSTEXT_DECLARE_DYNAMIC(class_name) \
			protected: \
				CUSTEXT_CLASS_FUNC_API static CRuntimeClass* PASCAL _GetBaseClass(); \
			public: \
				static const AFX_DATA CRuntimeClass class##class_name; \
				CUSTEXT_CLASS_FUNC_API virtual CRuntimeClass* GetRuntimeClass() const; \

			#define _CUSTEXT_DECLARE_DYNAMIC(class_name) \
			protected: \
				CUSTEXT_CLASS_FUNC_API static CRuntimeClass* PASCAL _GetBaseClass(); \
			public: \
				static AFX_DATA CRuntimeClass class##class_name; \
				CUSTEXT_CLASS_FUNC_API virtual CRuntimeClass* GetRuntimeClass() const; \

		#else
			#define CUSTEXT_DECLARE_DYNAMIC(class_name) \
			public: \
				static const AFX_DATA CRuntimeClass class##class_name; \
				CUSTEXT_CLASS_FUNC_API virtual CRuntimeClass* GetRuntimeClass() const; \

			#define _CUSTEXT_DECLARE_DYNAMIC(class_name) \
			public: \
				static AFX_DATA CRuntimeClass class##class_name; \
				CUSTEXT_CLASS_FUNC_API virtual CRuntimeClass* GetRuntimeClass() const; \

		#endif // _AFXDLL

	#else

		#define CUSTEXT_DECLARE_DYNAMIC(class_name)	DECLARE_DYNAMIC(class_name)

	#endif // Declare Dynamic
		
		// not serializable, but dynamically constructable
		#define CUSTEXT_DECLARE_DYNCREATE(class_name) \
			CUSTEXT_DECLARE_DYNAMIC(class_name) \
			CUSTEXT_CLASS_FUNC_API static CObject* PASCAL CreateObject();
		
		#define _CUSTEXT_DECLARE_DYNCREATE(class_name) \
			_CUSTEXT_DECLARE_DYNAMIC(class_name) \
			CUSTEXT_CLASS_FUNC_API static CObject* PASCAL CreateObject();

		#define CUSTEXT_DECLARE_SERIAL(class_name) \
			_CUSTEXT_DECLARE_DYNCREATE(class_name) \
			AFX_API friend CUSTEXT_CLASS_FUNC_API CArchive& AFXAPI operator>>(CArchive& ar, class_name* &pOb);

		// Grid Extension
		#define CUSTEXT_DECLARE_CONTROL(class_name) \
			protected: \
				CUSTEXT_CLASS_FUNC_API static CGXControlClass* PASCAL _GetControlBaseClass(); \
			public: \
				CUSTEXT_CLASS_FUNC_API static  CGXControlClass ctrl##class_name; \
				CUSTEXT_CLASS_FUNC_API virtual CGXControlClass* GetControlClass() const; \

		// Grid Extension
		#define CUSTEXT_IMPLEMENT_CONTROL(class_name, base_class_name) \
			CGXControlClass* PASCAL class_name::_GetControlBaseClass() \
				{ return CONTROL_CLASS(base_class_name); } \
				/*GX_DATADEF*/ CGXControlClass class_name::ctrl##class_name = { \
			#class_name, &class_name::_GetControlBaseClass }; \
			CGXControlClass* class_name::GetControlClass() const \
				{ return &class_name::ctrl##class_name; } \

	#ifdef _AFXDLL
		#define CUSTEXT_DECLARE_INTERFACE_MAP() \
			private: \
			static const AFX_INTERFACEMAP_ENTRY _interfaceEntries[]; \
			protected: \
			static const AFX_INTERFACEMAP interfaceMap; \
			CUSTEXT_CLASS_FUNC_API static const AFX_INTERFACEMAP* PASCAL GetThisInterfaceMap(); \
			CUSTEXT_CLASS_FUNC_API virtual const AFX_INTERFACEMAP* GetInterfaceMap() const; \

	#else
		#define CUSTEXT_DECLARE_INTERFACE_MAP() \
			private: \
			static const AFX_INTERFACEMAP_ENTRY _interfaceEntries[]; \
			protected: \
			static const AFX_INTERFACEMAP interfaceMap; \
			CUSTEXT_CLASS_FUNC_API virtual const AFX_INTERFACEMAP* GetInterfaceMap() const; \

	#endif // AFXDLL


	//Declare Register Override from Objective Grid///////
	#define CUSTEXT_DECLARE_REGISTER() \
	public: \
		CUSTEXT_CLASS_FUNC_API static LPCTSTR AFXAPI RegisterClass(); \
		CUSTEXT_CLASS_FUNC_API static void AFXAPI UnregisterClass(); \
		CUSTEXT_CLASS_FUNC_API static LPCTSTR AFXAPI RegisterClass(HINSTANCE hInstance); \
		CUSTEXT_CLASS_FUNC_API static void AFXAPI UnregisterClass(HINSTANCE hInstance); \
	protected: \
		CUSTEXT_CLASS_FUNC_API static LRESULT CALLBACK AFX_EXPORT WndProcHook(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam); \
		CUSTEXT_CLASS_FUNC_API virtual void PostNcDestroy();
	// END GRID_DECLARE_REGISTER


	#ifdef _WIN64

		#define CUSTEXT_IMPLEMENT_REGISTER(class_name, _style, icon, cursor, background) \
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
		// END CUSTEXT_IMPLEMENT_REGISTER

	#else	//WIN32

		#define CUSTEXT_IMPLEMENT_REGISTER(class_name, _style, icon, cursor, background) \
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
		// END CUSTEXT_IMPLEMENT_REGISTER

	#endif	//_WIN64
	//Declare Register/////////////////////////////////

	// Toolkit Extension
	#ifdef _AFXDLL
		#define CUSTEXT_DECLARE_DISPATCH_MAP() \
			private: \
			static const AFX_DISPMAP_ENTRY _dispatchEntries[]; \
			static UINT _dispatchEntryCount; \
			static DWORD _dwStockPropMask; \
			protected: \
			static const AFX_DISPMAP dispatchMap; \
			CUSTEXT_CLASS_FUNC_API static const AFX_DISPMAP* PASCAL GetThisDispatchMap(); \
			CUSTEXT_CLASS_FUNC_API virtual const AFX_DISPMAP* GetDispatchMap() const; \

	#else
		#define CUSTEXT_DECLARE_DISPATCH_MAP() \
			private: \
			static const AFX_DISPMAP_ENTRY _dispatchEntries[]; \
			static UINT _dispatchEntryCount; \
			static DWORD _dwStockPropMask; \
			protected: \
			static const AFX_DISPMAP dispatchMap; \
			CUSTEXT_CLASS_FUNC_API virtual const AFX_DISPMAP* GetDispatchMap() const; \

	#endif // _AFXDLL

	// end Helper Macros
#else // !_CUSTEXTDLL Static Library

	#define CUSTEXT_DECLARE_MESSAGE_MAP()			DECLARE_MESSAGE_MAP()
	#define CUSTEXT_DECLARE_DYNAMIC(class_name)		DECLARE_DYNAMIC(class_name)
	#define CUSTEXT_DECLARE_DYNCREATE(class_name)	DECLARE_DYNCREATE(class_name)
	#define CUSTEXT_DECLARE_SERIAL(class_name)		DECLARE_SERIAL(class_name)
    #define CUSTEXT_DECLARE_INTERFACE_MAP			DECLARE_INTERFACE_MAP()
	#define CUSTEXT_DECLARE_DISPATCH_MAP()			DECLARE_DISPATCH_MAP()

	#define CUSTEXT_DECLARE_CONTROL(class_name) \
		public: \
			static CGXControlClass GXNEAR ctrl##class_name; \
			virtual CGXControlClass* GetControlClass() const; \

	#define CUSTEXT_IMPLEMENT_CONTROL(class_name, base_class_name) \
		CGXControlClass GXNEAR class_name::ctrl##class_name = { \
		#class_name, CONTROL_CLASS(base_class_name) }; \
		CGXControlClass* class_name::GetControlClass() const \
			{ return &class_name::ctrl##class_name; } \


	//Declare Register Override from Objective Grid////
	#define CUSTEXT_DECLARE_REGISTER() \
		public: \
			CUSTEXT_CLASS_FUNC_API static LPCTSTR AFXAPI RegisterClass(); \
			CUSTEXT_CLASS_FUNC_API static void AFXAPI UnregisterClass(); \
			CUSTEXT_CLASS_FUNC_API static LPCTSTR AFXAPI RegisterClass(HINSTANCE hInstance); \
			CUSTEXT_CLASS_FUNC_API static void AFXAPI UnregisterClass(HINSTANCE hInstance); \
			CUSTEXT_CLASS_FUNC_API static CMapPtrToWord GXNEAR _gxregmap; \
		protected: \
			CUSTEXT_CLASS_FUNC_API static LRESULT CALLBACK AFX_EXPORT WndProcHook(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam); \
			CUSTEXT_CLASS_FUNC_API virtual void PostNcDestroy();
		// END CUSTEXT_DECLARE_REGISTER

	#ifdef _WIN64

		#define CUSTEXT_IMPLEMENT_REGISTER(class_name, _style, icon, cursor, background) \
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
		// END CUSTEXT_IMPLEMENT_REGISTER

	#else	//WIN32

		#define CUSTEXT_IMPLEMENT_REGISTER(class_name, _style, icon, cursor, background) \
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

#endif // End Static Library

// Toolkit Extension
#define CUSTEXT_DECLARE_BUTTON(class_name) \
	public: \
		static const AFX_DATA SECButtonClass class##class_name; \
		virtual SECButtonClass* GetButtonClass() const; \
		static SECStdBtn* PASCAL CreateButton();

// Toolkit Extension
#define CUSTEXT_IMPLEMENT_BUTTON(class_name) \
	SECStdBtn* PASCAL class_name::CreateButton() \
		{ return new class_name; } \
		const AFX_DATADEF SECButtonClass class_name::class##class_name = { \
		class_name::CreateButton }; \
		SECButtonClass* class_name::GetButtonClass() const \
		{ return ((SECButtonClass*)(&class_name::class##class_name)); } \

#endif // __CUSTEXTDEFS__H__

