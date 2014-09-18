#ifndef _DEBUG_H
#define _DEBUG_H

#ifdef WIN32
#ifndef  WINAPI
#define WINAPI __stdcall
#endif
#ifdef __XECURELIB__
#define XECURE_API __declspec(dllexport)
#else
#define XECURE_API __declspec(dllimport)
#endif
#else
#define WINAPI
#define XECURE_API 
#endif

#define XECURE_DUMP				1  /* data_dump() �Լ� ���� ��Ŵ */
#define XECURE_DEBUG			2  /* debug_out() �Լ� ���� ��Ŵ */	
#define XECURE_LOG				4  /* log_out() �Լ� ���� ��Ŵ  */ 

#ifdef  __cplusplus
extern "C" {
#endif

/* -------------------------------------------------------------------------
 �Լ��̸� : TurnOnDefenceOption
 ����     : ������ ���� �ɼ��� �Ѱų� ����. 
			Xecure �Լ��� �Է� ���� �����ϱ� ���� ����ϴ� �Լ� 
			���� ���´� ������ ���� �ɼ��� ���� ���� 
			�ѹ� ȣ�� �ø��� ������ ���� �ɼ��� �ٲ��. 
			�� �Լ��� data_dump()�Լ��� �Բ� ���ȴ�. 
			(����) ������ ������ ���� ���� 
 ���� ��  : void 
 �Է�     : int fOpt
				XECURE_DUMP				1  - data_dump() �Լ� ���� ��Ŵ 
				XECURE_DEBUG			2  - debug_out() �Լ� ���� ��Ŵ 	
				XECURE_LOG				4  - log_out() �Լ� ���� ��Ŵ   
 �Է�     : char *pPath -  XECURE_LOG �ɼ� ���ý� �α� ������ �н�
						   XecureGate Log File Path+name 
------------------------------------------------------------------------- */
XECURE_API void WINAPI TurnOnDefenceOption(int fOpt, const char *pPath);


/* -------------------------------------------------------------------------
 �Լ��̸� : data_dump
 ����     : �����͸� ���� ����ϴ� �Լ� 
			ToggleDump() �Լ��� �� ��� �Է� �����͸� �÷����� ���� 
			DBWIN �Ǵ� stdout�� ����Ѵ�. 
 ���� ��  : void 
 �Է�     : char *pDataName - �Է��ѵ������� �̸� 
 �Է�     : unsigned char *pData - �����ϰ��� �ϴ� �������� ������ 
 �Է�     : int nLen - �����ϰ��� �ϴ� �������� ũ�� 
------------------------------------------------------------------------- */
XECURE_API void WINAPI data_dump(char *pDataName, unsigned char *pData, int nLen);

/* -------------------------------------------------------------------------
 �Լ��̸� : debug_out
 ����     : ����׸� ���� �Լ�, 
			�÷����� ���� DBWIN �Ǵ� stdout�� �����͸� ����Ѵ�. 
 ���� ��  : void 
 �Է�     : char* lpszFmt
 �Է�     : ...
------------------------------------------------------------------------- */
XECURE_API void debug_out(char* lpszFmt, ...);
XECURE_API void log_out(char* lpszFmt, ...);

#ifdef  __cplusplus
}
#endif


#endif  /* _DEBUG_H */



