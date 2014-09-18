#if !defined(_COMMSEPDEF_H_)
#define _COMMSEPDEF_H_

// 데이터 전문에 포함된 구분자 정의 .
#define US						(BYTE)0x1F				// 개별의 요소를 분리하는 단위(Unit Separator)
#define FS						(BYTE)0x1E				// 컨트롤 사이의 구분자로 사용 (Field Separator)
#define PS						(BYTE)0x0D				// 복수의 KEY FID가 존재할 때 구분자로 사용.
#define RS						(BYTE)0x0A				// 복수의 레코드가 존재할 때 ROW구분자로 사용.
#define IS						(BYTE)0x7F				// FID와 입력 데이터 사이의 구분자로 사용.

#define	GS						US
#define	CS						PS						// Control구분자

#define _TCH_US					US
#define _TCH_FS					FS
#define _TCH_PS					PS
#define _TCH_RS					RS
#define _TCH_IS					IS

#endif // !defined(_COMMSEPDEF_H_)
