/******************************************************************************
 *  Copyright (C) 2000, Korea Securities Computer Corp.
 *                      Dept. of SAVE+, SI Team
 *	All Rights Reserved
 *
 *	This is PROPRIETARY SOURCE CODE OF KOSCOM.
 *	The copyright notice above does not evidence any
 *	actual or intended publication of such source code.
 *	Only HANWHA Securities Company use this source code.
 *
 *
 * 프로그램명	:	mast_def.h
 * 작  성  자	:	
 * 작  성  일	:	2010.5.12
 * 기      능	:   각종 Master구조 Define 처리
 *				:	변경자		변경일		변경내역
 *              :   신민철    2012.02.23    옵션승수제도변경에 따른 옵션코드파일에 옵션승수값항목 추가
 ******************************************************************************/

#define MAST_POSTFIX    ".cod"

#pragma pack(push, 1)

struct STKCODE_STRUC {
/*---------------------------------------------------------------------------*/
/* 종목 기본정보 항목                                                        */
/*---------------------------------------------------------------------------*/
    char    Sstd_code       [12]; /* 종목코드(Full)                          */
    char    Sjong_code      [ 6]; /* 종목코드(단축)                          */
    char    Sjong_kname     [40]; /* 한글종목명                              */
    char    Cmkt_f              ; /* 시장구분            1:KOSPI 2:KOSDAQ    */
    char    Sgrp_id         [ 2]; /* 소속구분                                */
                                  /* ST:주식              MF:증권투자회사    */
                                  /* RT:                  SC:선박투자회사    */
                                  /* IF:인프라투융자회사  DR:예탁증서        */
                                  /* SW:신주인수권증권    SR:신주인수권증서  */
                                  /* EW:주식워런트증권(ELW) EF:상장지수펀드(ETF) */
                                  /* BC:수익증권          FE:해외ETF         */
                                  /* FS:해외원주                             */
/*---------------------------------------------------------------------------*/
/* 지수구분 항목                                                             */
/*---------------------------------------------------------------------------*/
                                  /*-----------------------------------------*/
                                  /* KOSPI/KOSDAQ지수 공통    |업종명:(코드) */
                                  /*-----------------------------------------*/
    char    Creal_prc_size_f    ; /* 시가총액규모                            */
                                  /* 0:제외종목                              */
                                  /* KOSPI          (2 ~ 4)                  */
                                  /* 2:대형주                  대형주: (002) */
                                  /* 3:중형주                  중형주: (003) */
                                  /* 4:소형주                  소형주: (004) */
                                  /* KOSDAQ         (6 ~ 8)                  */
                                  /* 6:KOSDAQ100        KOSDAQ100업종: (339) */
                                  /* 7:MID300       KOSDAQ MID300업종: (340) */
                                  /* 8:SMALL         KOSDAQ SMALL업종: (341) */
    char    Sup_large       [ 3]; /* 업종코드(KOSDAQ:대대)분류               */
                                  /* KOSDAQ대대분류 (303 ~ 304)              */
                                  /* 303:기타서비스        기타서비스: (303) */
                                  /* 304:코스닥IT        코스닥IT종합: (304) */
    char    Sup_middle      [ 3]; /* 업종코드(KOSPI:중/KOSDAQ:대)분류        */
                                  /* KOSPI중분류    (005 ~ 021, 026)         */
                                  /* 005:음식료품            음식료품: (005) */
                                  /* 006:섬유/의복          섬유,의복: (006) */
                                  /* 007:종이/목재          종이,목재: (007) */
                                  /* 008:화학                    화학: (008) */
                                  /* 009:의약품                의약품: (009) */
                                  /* 010:비금속광물        비금속광물: (010) */
                                  /* 011:철강,금속          철강,금속: (011) */
                                  /* 012:기계                    기계: (012) */
                                  /* 013:전기,전자          전기,전자: (013) */
                                  /* 014:의료정밀            의료정밀: (014) */
                                  /* 015:운수장비            운수장비: (015) */
                                  /* 016:유통업                유통업: (016) */
                                  /* 017:전기가스업        전기가스업: (017) */
                                  /* 018:건설업                건설업: (018) */
                                  /* 019:운수창고            운수창고: (019) */
                                  /* 020:통신업                통신업: (020) */
                                  /* 021:금융업                금융업: (021) */
                                  /* 026:서비스업            서비스업: (026) */
                                  /* KOSDAQ대분류   (306 ~ 338)              */
                                  /* 306:제조                    제조: (306) */
                                  /* 307:건설                    건설: (307) */
                                  /* 308:유통                    유통: (308) */
                                  /* 309:숙박/음식          숙박,음식: (309) */
                                  /* 310:운송                    운송: (310) */
                                  /* 311:금융                    금융: (311) */
                                  /* 312:통/방서비스   통신방송서비스: (312) */
                                  /* 313:IT S/W&SVC      IT S/W & SVC: (313) */
                                  /* 314:IT H/W                IT H/W: (314) */
                                  /* 338:오락/문화          오락,문화: (338) */
    char    Sup_small       [ 3]; /* 업종코드(KOSPI:소/KOSDAQ:중)분류        */
                                  /* KOSPI소분류    (022 ~ 025)              */
                                  /* 022:은행                    은행: (022) */
                                  /* 024:증권                    증권: (024) */
                                  /* 025:보험업                보험업: (025) */
                                  /* KOSDAQ중분류   (315 ~ 337)              */
                                  /* 315:음식료/담배      음식료,담배: (315) */
                                  /* 316:섬유/의류          섬유,의류: (316) */
                                  /* 317:종이/목재          종이,목재: (317) */
                                  /* 318:출판/매체복제  출판,매체복제: (318) */
                                  /* 319:화학                    화학: (319) */
                                  /* 320:제약                    제약: (320) */
                                  /* 321:비금속                비금속: (321) */
                                  /* 322:금속                    금속: (322) */
                                  /* 323:기계/장비          기계,장비: (323) */
                                  /* 324:일반전기전자    일반전기전자: (324) */
                                  /* 325:의료/정밀기기  의료,정밀기기: (325) */
                                  /* 326:운송장비/부품  운송장비,부품: (326) */
                                  /* 327:기타제조            기타제조: (327) */
                                  /* 328:통신서비스        통신서비스: (328) */
                                  /* 329:방송서비스        방송서비스: (329) */
                                  /* 330:인터넷                인터넷: (330) */
                                  /* 331:디지털컨텐츠    디지털컨텐츠: (331) */
                                  /* 332:소프트웨어        소프트웨어: (332) */
                                  /* 333:컴퓨터서비스    컴퓨터서비스: (333) */
                                  /* 334:통신장비            통신장비: (334) */
                                  /* 335:정보기기            정보기기: (335) */
                                  /* 336:반도체                반도체: (336) */
                                  /* 337:IT부품                IT부품: (337) */
                                  /*-----------------------------------------*/
                                  /* KOSPI지수                |업종명:(코드) */
                                  /*-----------------------------------------*/
    char    Cmfac_f             ; /* 제조업구분                제조업: (027) */
                                  /* Y:해당 N:비해당                         */
    char    Cdivd_f             ; /* 배당지수종목구분        배당지수: (041) */
                                  /* Y:해당 N:비해당                         */
    char    Ccntl_idx_f         ; /* 지배구조우수구분    지배구조우수: (042) */
                                  /* Y:해당 N:비해당                         */
    char    Ckospi200_f         ; /* KOSPI200구분                            */
                                  /* 0:미채택 제외전부       KOSPI200: (101) */
                                  /* 1:제조업         KOSPI200 제조업: (102) */
                                  /* 2:전기통신     KOSPI200 전기통신: (103) */
                                  /* 3:건설업         KOSPI200 건설업: (104) */
                                  /* 4:유통             KOSPI200 유통: (105) */
                                  /* 5:금융             KOSPI200 금융: (106) */
    char    Ckospi50100_f       ; /* KOSPI100/KOSPI50구분                    */
                                  /* 0:미채용                                */
                                  /* 1:KOSPI100              KOSPI100: (201) */
                                  /* 2:KOSPI50                KOSPI50: (202) */
                                  /*-----------------------------------------*/
                                  /* KOSDAQ지수               |업종명:(코드) */
                                  /*-----------------------------------------*/
    char    Cvntr_corp_f        ; /* 벤처기업구분                벤처: (302) */
                                  /* Y:해당 N:비해당                         */
    char    Ckostar_f           ; /* STAR지수구분          KOSTAR업종: (403) */
                                  /* Y:해당 N:비해당                         */
                                  /* 기타구분                  IT벤처: (305) */
                                  /* (304:코스닥IT) + (벤처기업구분)         */
                                  /*-----------------------------------------*/
                                  /* KRX(섹터)지수            |업종명:(코드) */
                                  /*-----------------------------------------*/
    char    Ckrx100_f           ; /* KRX100구분                KRX100: (501) */
                                  /* Y:해당 N:비해당                         */
/*---------------------------------------------------------------------------*/
/* 종목 일반정보 항목                                                        */
/*---------------------------------------------------------------------------*/
    char    Sdivd_mon       [ 2]; /* 결산월                                  */
                                  /*                       KOSPI :        NO */
                                  /*                       KOSDAQ:        mm */
    char    Sfprc           [11]; /* 액면가                                  */
                                  /*                       KOSPI : 9(9)v9(2) */
                                  /*                       KOSDAQ:      9(7) */
    char    Sstprc          [ 9]; /* 기준가                                  */
                                  /*                       KOSPI :      9(9) */
                                  /*                       KOSDAQ:      9(7) */
    char    Scapital        [17]; /* 자본금                                  */
                                  /*                       KOSPI :9(15)v9(2) */
                                  /*                       KOSDAQ:     9(17) */
    char    Slist_jusu      [12]; /* 상장주식수                              */
                                  /*                       KOSPI :     9(12) */
                                  /*                       KOSDAQ:     9(12) */
    char    Sdivd_rt        [ 6]; /* 배당수익율                              */
                                  /*                       KOSPI :        NO */
                                  /*                       KOSDAQ: 9(5)v9(1) */
    char    Ss_yj_rate      [ 5]; /* 신용융자잔고비율                        */
                                  /*                       KOSPI : 9(3)v9(2) */
                                  /*                       KOSDAQ: 9(3)v9(2) */
    char    Ctrade_stop_f       ; /* 거래정지구분          N.정상 Y.거래정지 */
    char    Cargmt_trade_f      ; /* 정리매매구분          N:정상 Y:정리매매 */
    char    Ckwanli_f           ; /* 관리구분              N:정상 Y:관리     */
    char    Smkt_warn_f     [ 2]; /* 시장경보구분코드                        */
                                  /* 00:정상 01:주의 02:경고 03:위험         */
    char    Cmkt_warn_noti_f    ; /* 시장경보예고구분코드  N:정상 Y:예고     */
    char    Cgongsi_f           ; /* 불성실공시지정여부    N:정상 Y:지정     */
    char    Cdetour_list_f      ; /* 우회상장구분          N:정상 Y:우회상장 */
    char    Slak_f          [ 2]; /* 권배락구분                              */
                                  /* 00:해당없음        01:권리락            */
                                  /* 02:배당락          03:분배락            */
                                  /* 04:권배락          05:중간배당락        */
                                  /* 06:권리중간배당락  99:기타              */
};
#define	SZ_STKCODE_STRUC	sizeof(struct	STKCODE_STRUC)
#define STKCODE_NAME "STKCODE"

/*****************************************************************************/
/* ELW 종목정보   항목                                                       */
/*****************************************************************************/
struct ELWCODE_STRUC {
    char    Sjong_code      [ 7];		/* 종목코드                                */
    char    Sjong_kname     [40];		/* 한글종목명                              */
    char    Sbase_ast		[5][12];	/* ELW기초자산(5개)                        */
                                  		/* KOSPI100종목: 종목코드                  */
                                  		/* KOSPI200지수: "KSP200"                  */
    char    Sisu_prtc_kname [40]; 		/* ELW한글발행기관명                       */
    char    Sisu_prtc_no    [ 5]; 		/* ELW발행기관코드                         */
    char    Sexrc_prc       [10]; 		/* ELW행사가격                   9(8)v9(2) */
    char    Slast_trdt      [ 8]; 		/* ELW최종거래일                  YYYYMMDD */
    char    Sremn_day       [ 4]; 		/* 잔존일수 (비영업일 포함)                */
    char    Sremn_bus_day   [ 4]; 		/* 영업일잔존일수                          */
    char    Crgt_type_f         ; 		/* ELW 권리유형  C.CALL P:PUT E:기타       */
    char    Smkt_prtc_no1   [ 5]; 		/* ELW LP회원번호1                         */
    char    Smkt_prtc_no2   [ 5]; 		/* ELW LP회원번호2                         */
    char    Smkt_prtc_no3   [ 5]; 		/* ELW LP회원번호3                         */
    char    Smkt_prtc_no4   [ 5]; 		/* ELW LP회원번호4                         */
    char    Smkt_prtc_no5   [ 5]; 		/* ELW LP회원번호5                         */
    char    Smkt_prtc_no6   [ 5]; 		/* ELW LP회원번호6                         */
    char    Smkt_prtc_no7   [ 5]; 		/* ELW LP회원번호7                         */
    char    Smkt_prtc_no8   [ 5]; 		/* ELW LP회원번호8                         */
    char    Smkt_prtc_no9   [ 5]; 		/* ELW LP회원번호9                         */
    char    Smkt_prtc_no10  [ 5]; 		/* ELW LP회원번호10                        */
    char    Sstd_code       [12]; 		/* 표준종목코드                            */
    char    Cnovel_opt_f;		 		/* ELW 이색옵션 0:표준 1:디지털 2:조기종료 */
	char	SLPlast_day		[ 8];		//KJI 20110823 ELW LP 종료일 추가
};
#define	SZ_ELWCODE_STRUC	sizeof(struct	ELWCODE_STRUC)
#define ELWCODE_NAME "ELWCODE"

/*****************************************************************************/
/* ELW 발행사정보 항목                                                       */
/*****************************************************************************/
struct ELWISUCODE_STRUC {
    char Sisu_code           [ 5]; /* ELW발행기관코드                       */
    char Sisu_name           [40]; /* ELW한글발행기관명                     */
};
#define	SZ_ELWISUCODE_STRUC	sizeof(struct	ELWISUCODE_STRUC)
#define ELWISUCODE_NAME "ELWISUCODE"

/*****************************************************************************/
/* ELW기초자산코드 리스트                                                    */
/*****************************************************************************/
struct ELWBASECODE_STRUC {
	char Sstd_code           [12]; /* 기초자산코드(표준)                     */
	char Sjong_code          [10]; /* 기초자산코드(단축)					 */
	char Sjong_kname         [40]; /* 기초자산명                             */
	char Sstd_mkt			 [ 1]; /* 기초자산시장구분						 */
	char Sstd_fmt			 [ 1]; /* 기초자산Format						 */
	char Sort_gb			 [ 1]; /* 정렬구분								 */
};
#define SZ_ELWBASECODE_STRUC  sizeof( struct ELWBASECODE_STRUC )
#define ELWBASECODE_NAME "ELWBASECODE"

/*****************************************************************************/
/* ELW LP 리스트                                                             */
/*****************************************************************************/
struct ELWLPCODE_STRUC {
	char Slp_code           [ 3]; /* 회원사코드			                      */
	char Slp_name           [12]; /* 회원사명					             */
	char Skrx_code          [ 5]; /* KRX회원사코드				             */
};
#define SZ_ELWLPCODE_STRUC  sizeof( struct ELWLPCODE_STRUC )
#define ELWLPCODE_NAME "ELWLPCODE"

/*****************************************************************************/
/* OTCBB                                                                     */
/*****************************************************************************/
struct OTBCODE_STRUC {
    char Sjong_code         [ 6]; /* 종목코드                               */
    char Sstd_code          [12]; /* 표준코드                               */
    char Sjong_kname        [30]; /* 한글종목명                             */
};
#define	SZ_OTBCODE_STRUC	sizeof(struct	OTBCODE_STRUC)
#define OTBCODE_NAME "OTBCODE"


/*****************************************************************************/
/* KOSPI업종                                                                 */
/*****************************************************************************/
struct KSPICODE_STR4C {
    char Sup_code            [ 3]; /* 업종코드                               */
    char Sup_name            [20]; /* 한글종목명                             */
};
#define	SZ_KSPICODE_STRUC	sizeof(struct	KSPICODE_STRUC)
#define KSPICODE_NAME "KSPICODE"

/*****************************************************************************/
/* KOSDAQ업종                                                                */
/*****************************************************************************/
struct KSDICODE_STRUC {
    char Sup_code            [ 3]; /* 업종코드                               */
    char Sup_name            [20]; /* 한글종목명                             */
};
#define	SZ_KSDICODE_STRUC	sizeof(struct	KSDICODE_STRUC)
#define KSDICODE_NAME "KSDICODE"

/*****************************************************************************/
/* KRX업종                                                                   */
/*****************************************************************************/
struct KRXICODE_STRUC {
    char Sup_code            [ 3]; /* 업종코드                               */
    char Sup_name            [20]; /* 한글종목명                             */
};
#define	SZ_KRXICODE_STRUC	sizeof(struct	KRXICODE_STRUC)
#define KRXICODE_NAME "KRXICODE"

/*****************************************************************************/
/* OTCBB업종                                                                 */
/*****************************************************************************/
struct OTBICODE_STRUC {
    char Sup_code            [ 3]; /* 업종코드                               */
    char Sup_name            [20]; /* 한글종목명                             */
};
#define SZ_OTBICODE_STRUC   sizeof(struct   OTBICODE_STRUC)
#define OTBICODE_NAME "OTBICODE"

/*****************************************************************************/
/* 선물                                                                      */
/*****************************************************************************/
struct FUTCODE_STRUC {
    char Sjong_code          [ 8]; /* 종목코드                               */
    char Sstd_code           [12]; /* 표준코드                               */
    char Sjong_kname         [30]; /* 한글종목명                             */
};
#define SZ_FUTCODE_STRUC   sizeof(struct   FUTCODE_STRUC)
#define FUTCODE_NAME "FUTCODE"

/*****************************************************************************/
/* 선물(스프레드)                                                            */
/*****************************************************************************/
struct FUTSCODE_STRUC {
    char Sjong_code          [ 8]; /* 종목코드                               */
    char Sstd_code           [12]; /* 표준코드                               */
    char Sjong_kname         [30]; /* 한글종목명                             */
};
#define SZ_FUTSCODE_STRUC   sizeof(struct   FUTSCODE_STRUC)
#define FUTSCODE_NAME "FUTSCODE"

/*****************************************************************************/
/* 옵션                                                                      */
/*****************************************************************************/
struct OPTCODE_STRUC {
    char Sjong_code			[ 8]; /* 종목코드                               */
    char Sstd_code			[12]; /* 표준코드                               */
    char Sjong_Name			[19]; /* 종목명1(콜/풋 월물 부분)               */
	char Sjong_Price		[11]; /* 종목명2(가격부분)						*/
    char Catm_f					; /* ATM구분       1:ATM, 2:ITM, 3:OTM		*/
	char Sjong_Mult			[ 8]; /* 옵션 거래승수							*/
};
#define SZ_OPTCODE_STRUC   sizeof(struct   OPTCODE_STRUC)
#define OPTCODE_NAME "OPTCODE"

/*****************************************************************************/
/* 옵션 ATM가격(최근월물)                                                    */
/*****************************************************************************/
struct ATMPRC_STRUC {
    char Satm_prc            [ 6]; /* ATM가격                      9(4)v9(2) */
};
#define SZ_ATMPRC_STRUC   sizeof(struct   ATMPRC_STRUC)
#define ATMPRC_NAME "ATMPRC"

/*****************************************************************************/
/* 주식선물                                                                  */
/*****************************************************************************/
struct ZFUTCODE_STRUC {
    char Sjong_code			[ 8]; /* 종목코드                               */
    char Sstd_code			[12]; /* 표준코드                               */
    char SBase_Name			[20]; /* 기초자산명								*/
	char Sjong_kname		[30]; /* 한글종목명                             */
    char Catm_f                  ; /* ATM구분       1:ATM, 2:ITM, 3:OTM      */
};
#define SZ_ZFUTCODE_STRUC   sizeof(struct   ZFUTCODE_STRUC)
#define ZFUTCODE_NAME "ZFUTCODE"


/*****************************************************************************/
/* 주식옵션                                                                  */
/*****************************************************************************/
struct ZOPTCODE_STRUC {
    char Sjong_code			[ 8];	/* 종목코드								*/
    char Sstd_code			[12];	/* 표준코드								*/
	char SBase_Name			[11];	/* 종목명-기초자산명					*/
	char SJong_CallPut		[1];	/* 종목명-콜/풋 구분					*/
	char SJong_Month		[4];	/* 종목명-년월							*/
	char SJong_Price		[10];	/* 종목명-가격							*/
    char SJong_Etc			[24];	/* 종목명-나머지						*/
    char Catm_f					;	/* ATM구분       1:ATM, 2:ITM, 3:OTM	*/
};
#define SZ_ZOPTCODE_STRUC   sizeof(struct   ZOPTCODE_STRUC)
#define ZOPTCODE_NAME "ZOPTCODE"

/*****************************************************************************/
/* 주식옵션 ATM가격(최근월물)                                                */
/*****************************************************************************/
struct ZATMPRC_STRUC {
    char Sjong_code          [ 8]; /* 종목코드                               */
    char Satm_prc            [ 8]; /* ATM가격                      9(8)      */
};
#define SZ_ZATMPRC_STRUC   sizeof(struct   ZATMPRC_STRUC)
#define ZATMPRC_NAME "ZATMPRC"

/*****************************************************************************/
/* 주식선물/옵션 기초자산정보                                                */
/*****************************************************************************/
struct ZOBJCODE_STRUC {
   USHORT   Wdrvt_id;              /* 기초자산 거래대상물코드  */
   UCHAR    Cfiller11;             /* 0x20 ' '                 */
   UCHAR    Sfdrvt_id[10];         /* 주식선물파생상품ID       */
   UCHAR    Cfiller12;             /* 0x20 ' '                 */
   UCHAR    Sodrvt_id[10];         /* 주식옵션파생상품ID       */
   UCHAR    Cfiller13;             /* 0x20 ' '                 */
   UCHAR    Sbase_ast_id[3];       /* 기초자산ID               */
   UCHAR    Cfiller14;             /* 0x20 ' '                 */
   UCHAR    Sobject_cd[12];        /* 기초자산 코드            */
   UCHAR    Cfiller21;             /* 0x31 ':'                 */
   UCHAR    Sobject_nm[16];        /* 기초자산 명              */
   UCHAR    Cfiller22;             /* 0x31 ':'                 */
   UCHAR    Cfutopt_f;             /* 선물옵션 구분자          */
                                   /* 'A' : 선물옵션 모두 사용 */
                                   /* 'F' : 선물          사용 */
                                   /* 'O' : 옵션          사용 */
   UCHAR    Cfiller31;             /* 0x0d "CR"                */
};
#define SZ_ZOBJCODE_STRUC  sizeof( struct ZOBJCODE_STRUC )
#define ZOBJCODE_NAME "ZOBJCODE"

/*****************************************************************************/
/* 그룹사                                                                    */
/*****************************************************************************/
struct GRPCODE_STRUC {
    char Sgrp_code           [ 4]; /* 그룹사코드                             */
                                   /*                  증권사제공: 0001~0999 */
                                   /*                    유진제공: 1001~1999 */
    char Sgrp_name           [20]; /* 그룹사명                               */
    char Sjong_code          [ 6]; /* 종목코드                               */
};
#define SZ_GRPCODE_STRUC   sizeof(struct   GRPCODE_STRUC)
#define GRPCODE_NAME "GRPCODE"

/*****************************************************************************/
/* 테마코드 리스트                                                           */
/*****************************************************************************/
struct THEMACODE_STRUC {
    char Sthema_code         [ 4]; /* 테마코드                               */
    char Sthema_name         [50]; /* 테마명                                 */
    char Sjong_code          [ 6]; /* 종목코드                               */
};
#define SZ_THEMACODE_STRUC   sizeof(struct   THEMACODE_STRUC)
#define THEMACODE_NAME "THEMACODE"

/*****************************************************************************/
/* 거래원 리스트                                                             */
/*****************************************************************************/
struct MEMBCODE_STRUC {
    char Smemb_code          [ 3]; /* 거래원코드                             */
    char Smemb_name          [20]; /* 거래원명                               */
    char Cmemb_f                 ; /* 0:국내, 1:외국계                       */
    char Smemb_fcode         [ 5]; /* 거래원 Full코드                        */
};
#define SZ_MEMBCODE_STRUC   sizeof(struct   MEMBCODE_STRUC)
#define MEMBCODE_NAME "MEMBCODE"

/*****************************************************************************/
/* 해외코드                                                                  */
/*****************************************************************************/
struct FRGNCODE_STRUC {
    char Ssymbol		[10];   /* 심볼코드                             */
    char Cdata_kind_f	[ 1];   /* 구분 - P:미국지수 Q:미국종가         */
								/*        D:미국상장 국내기업(ADR)      */
								/*        C:상품선물 F:CME선물          */
								/*        G:유럽상장 국내기업(GDR)      */
								/*        X:환율 R:금리 L:리보금리      */
								/*        B:주요국정부채 N:국내금리     */
								/*        M:반도체 H:세계주요종목       */
								/*        E:ECN W:세계주가지수          */
    char Skname			[40];   /* 한글명                               */
    char Sename			[39];   /* 영문명                               */
    char Sup_code		[ 4];   /* MULTEX 업종 분류코드                 */
    char Cdowj_inc		[ 1];   /* 다우30 편입종목   (미국종목만 해당)  */
    char Cnasd_inc		[ 1];   /* 나스닥100 편입종목(미국종목만 해당)  */
    char Csnp_inc		[ 1];   /* S&P500 편입종목   (미국종목만 해당)  */
    char Sisu_jusu		[15];   /* 총 주식 발생수                       */
    char Strade_f		[ 4];   /* 거래소 코드                          */
    char Sevent_date	[10];   /* 이벤트 날짜                          */
    char Snatl_f		[ 3];   /* 국가구분코드                         */
};
#define SZ_FRGNCODE_STRUC   sizeof(struct   FRGNCODE_STRUC)
#define FRGNCODE_NAME "FRGNCODE"
/*****************************************************************************/
/* 해외지수                                                                  */
/*****************************************************************************/
struct FRGNJISU_STRUC {
    char Ssymbol		[10];   /* 심볼코드                             */
    char Sname			[40];   /* 종목명                               */
    char SGubun1		[1];
	char SGubun2		[1];
};
#define SZ_FRGNJISU_STRUC   sizeof(struct   FRGNJISU_STRUC)
#define FRGNJISU_NAME "FRGNJISU"

/*****************************************************************************/
/* 상품 선물                                                                 */
/*****************************************************************************/
struct CFUTCODE_STRUC {
    char 	Sjong_code       [ 8]; /* 종목코드                               */
    char 	Sstd_code        [12]; /* 표준코드                               */
	// -->2011/01/21 Yunchang - 종목명이 잘리는 문제가 있어서 서버에서 50byte를 종목명으로 해달라고 요청하여 수정함.
	//char 	Sjong_kname      [20]; /* 한글종목명                             */
    //char 	Smon_kname       [30]; /* 한글월물종목명                         */
	char 	Sjong_kname      [50]; /* 한글종목명                             */
	// -->2011/01/21 Yunchang
    UCHAR	Sbase_ast_cd     [ 6]; /* 기초자산ID               	             */
                                   /* 'KTB   ':3년국채    '5TB   ':5년국채   */
                                   /* 'LKTB  ':10년국채   'MSB   ':통안채    */
                                   /* 'CRD   ':CD                            */
                                   /* 'USD   ':미국달러   'JPY   ':일본엔    */
                                   /* 'EUR   ':유럽유로                      */
                                   /* 'GOLD  ':금         'LHG   ':돈육      */
	UCHAR   Sdesc            [ 2]; /* 소수점 정보                            */
    char    Shoga_unit       [ 5]; /* 호가단위                      9(3)v9(2)*/
};
#define SZ_CFUTCODE_STRUC   sizeof(struct   CFUTCODE_STRUC)
#define CFUTCODE_NAME "CFUTCODE"

/*****************************************************************************/
/* 상품 선물(스프레드)                                                       */
/*****************************************************************************/
struct CFUTSCODE_STRUC {
    char 	Sjong_code       [ 8]; /* 종목코드                               */
    char 	Sstd_code        [12]; /* 표준코드                               */
	// -->2011/01/21 Yunchang - 종목명이 잘리는 문제가 있어서 서버에서 50byte를 종목명으로 해달라고 요청하여 수정함.
	//char 	Sjong_kname      [20]; /* 한글종목명                             */
    //char 	Smon_kname       [30]; /* 한글월물종목명                         */
	char 	Sjong_kname      [50]; /* 한글종목명                             */
	// -->2011/01/21 Yunchang
   	UCHAR   Sbase_ast_cd     [ 6]; /* 기초자산ID                             */
                                   /* 'KTB   ':3년국채    '5TB   ':5년국채   */
                                   /* 'LKTB  ':10년국채   'MSB   ':통안채    */
                                   /* 'CRD   ':CD                            */
                                   /* 'USD   ':미국달러   'JPY   ':일본엔    */
                                   /* 'EUR   ':유럽유로                      */
                                   /* 'GOLD  ':금         'LHG   ':돈육      */
	UCHAR   Sdesc            [ 2]; /* 소수점 정보                            */
    char    Shoga_unit       [ 5]; /* 호가단위                      9(3)v9(2)*/
};
#define SZ_CFUTSCODE_STRUC   sizeof(struct   CFUTSCODE_STRUC)
#define CFUTSCODE_NAME "CFUTSCODE"

/*****************************************************************************/
/* 상품 옵션                                                                 */
/*****************************************************************************/
struct COPTCODE_STRUC {
    char 	Sjong_code       [ 8]; /* 종목코드                               */
    char 	Sstd_code        [12]; /* 표준코드                               */
    char 	Sjong_kname      [30]; /* 한글종목명                             */
    char 	Catm_f               ; /* ATM구분       1:ATM, 2:ITM, 3:OTM      */
   	UCHAR   Sbase_ast_cd     [ 6]; /* 기초자산ID                             */
                                   /* 'KTB   ':3년국채    '5TB   ':5년국채   */
                                   /* 'LKTB  ':10년국채   'MSB   ':통안채    */
                                   /* 'CRD   ':CD                            */
                                   /* 'USD   ':미국달러   'JPY   ':일본엔    */
                                   /* 'EUR   ':유럽유로                      */
                                   /* 'GOLD  ':금         'LHG   ':돈육      */
	UCHAR   Sdesc            [ 2]; /* 소수점 정보                            */
    char    Shoga_unit       [ 5]; /* 호가단위                9(3)v9(2)      */
};
#define SZ_COPTCODE_STRUC   sizeof(struct   COPTCODE_STRUC)
#define COPTCODE_NAME "COPTCODE"

/*****************************************************************************/
/* 상품옵션 ATM가격(최근월물)                                                */
/*****************************************************************************/
struct CATMPRC_STRUC {
    char Sjong_code          [ 8]; /* 종목코드                               */
    char Satm_prc            [ 8]; /* ATM가격                      9(8)      */
};
#define SZ_CATMPRC_STRUC   sizeof(struct   CATMPRC_STRUC)
#define CATMPRC_NAME "CATMPRC"

/*****************************************************************************/
/* 상품현물                                                                  */
/*****************************************************************************/
struct COBJCODE_STRUC {
	UCHAR    Sdrvt_id1[2];          /* 기초자산 ID 2byte            */
    UCHAR    Cfiller;               /* 0x20 ' '                     */
    UCHAR    Sdrvt_id2[10];         /* 기초자산 ID 10byte           */
    UCHAR    Cfiller1;              /* 0x20 ' '                     */
    UCHAR    Sbase_ast_cd[3];       /* 기초자산 CODE 6byte          */
                                    /* 'KTB   ':3년국채    '5TB   ':5년국채   */
                                    /* 'LKTB  ':10년국채   'MSB   ':통안채    */
                                    /* 'CRD   ':CD                            */
                                    /* 'USD   ':미국달러   'JPY   ':일본엔    */
                                    /* 'EUR   ':유럽유로                      */
                                    /* 'GOLD  ':금         'LHG   ':돈육      */
    UCHAR    Cfiller2;              /* 0x20 ' '                     */
    UCHAR    Sobject_nm[20];        /* 기초자산 한글명              */
    UCHAR    Cfiller3;              /* 0x31 ':'                     */
    UCHAR    Cfutopt_f;             /* 선물옵션 구분자              */
                                    /* 'A' : 선물옵션 모두 사용     */
                                    /* 'F' : 선물          사용     */
                                    /* 'O' : 옵션          사용     */
    UCHAR    Cfiller4;              /* 0x31 ':'                     */
    UCHAR    Sdesc[2];              /* 소숫점 정보                  */
 //   UCHAR    Cfiller5;              /* 0x31 ':'                     */
};
#define SZ_COBJCODE_STRUC   sizeof(struct   COBJCODE_STRUC)
#define COBJCODE_NAME "COBJCODE"

#pragma pack(pop)
/********** mast_def.h : end of list **********/
