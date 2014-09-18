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
 * ���α׷���	:	mast_def.h
 * ��  ��  ��	:	
 * ��  ��  ��	:	2010.5.12
 * ��      ��	:   ���� Master���� Define ó��
 *				:	������		������		���泻��
 *              :   �Ź�ö    2012.02.23    �ɼǽ¼��������濡 ���� �ɼ��ڵ����Ͽ� �ɼǽ¼����׸� �߰�
 ******************************************************************************/

#define MAST_POSTFIX    ".cod"

#pragma pack(push, 1)

struct STKCODE_STRUC {
/*---------------------------------------------------------------------------*/
/* ���� �⺻���� �׸�                                                        */
/*---------------------------------------------------------------------------*/
    char    Sstd_code       [12]; /* �����ڵ�(Full)                          */
    char    Sjong_code      [ 6]; /* �����ڵ�(����)                          */
    char    Sjong_kname     [40]; /* �ѱ������                              */
    char    Cmkt_f              ; /* ���屸��            1:KOSPI 2:KOSDAQ    */
    char    Sgrp_id         [ 2]; /* �Ҽӱ���                                */
                                  /* ST:�ֽ�              MF:��������ȸ��    */
                                  /* RT:                  SC:��������ȸ��    */
                                  /* IF:������������ȸ��  DR:��Ź����        */
                                  /* SW:�����μ�������    SR:�����μ�������  */
                                  /* EW:�ֽĿ���Ʈ����(ELW) EF:���������ݵ�(ETF) */
                                  /* BC:��������          FE:�ؿ�ETF         */
                                  /* FS:�ؿܿ���                             */
/*---------------------------------------------------------------------------*/
/* �������� �׸�                                                             */
/*---------------------------------------------------------------------------*/
                                  /*-----------------------------------------*/
                                  /* KOSPI/KOSDAQ���� ����    |������:(�ڵ�) */
                                  /*-----------------------------------------*/
    char    Creal_prc_size_f    ; /* �ð��ѾױԸ�                            */
                                  /* 0:��������                              */
                                  /* KOSPI          (2 ~ 4)                  */
                                  /* 2:������                  ������: (002) */
                                  /* 3:������                  ������: (003) */
                                  /* 4:������                  ������: (004) */
                                  /* KOSDAQ         (6 ~ 8)                  */
                                  /* 6:KOSDAQ100        KOSDAQ100����: (339) */
                                  /* 7:MID300       KOSDAQ MID300����: (340) */
                                  /* 8:SMALL         KOSDAQ SMALL����: (341) */
    char    Sup_large       [ 3]; /* �����ڵ�(KOSDAQ:���)�з�               */
                                  /* KOSDAQ���з� (303 ~ 304)              */
                                  /* 303:��Ÿ����        ��Ÿ����: (303) */
                                  /* 304:�ڽ���IT        �ڽ���IT����: (304) */
    char    Sup_middle      [ 3]; /* �����ڵ�(KOSPI:��/KOSDAQ:��)�з�        */
                                  /* KOSPI�ߺз�    (005 ~ 021, 026)         */
                                  /* 005:���ķ�ǰ            ���ķ�ǰ: (005) */
                                  /* 006:����/�Ǻ�          ����,�Ǻ�: (006) */
                                  /* 007:����/����          ����,����: (007) */
                                  /* 008:ȭ��                    ȭ��: (008) */
                                  /* 009:�Ǿ�ǰ                �Ǿ�ǰ: (009) */
                                  /* 010:��ݼӱ���        ��ݼӱ���: (010) */
                                  /* 011:ö��,�ݼ�          ö��,�ݼ�: (011) */
                                  /* 012:���                    ���: (012) */
                                  /* 013:����,����          ����,����: (013) */
                                  /* 014:�Ƿ�����            �Ƿ�����: (014) */
                                  /* 015:������            ������: (015) */
                                  /* 016:�����                �����: (016) */
                                  /* 017:���Ⱑ����        ���Ⱑ����: (017) */
                                  /* 018:�Ǽ���                �Ǽ���: (018) */
                                  /* 019:���â��            ���â��: (019) */
                                  /* 020:��ž�                ��ž�: (020) */
                                  /* 021:������                ������: (021) */
                                  /* 026:���񽺾�            ���񽺾�: (026) */
                                  /* KOSDAQ��з�   (306 ~ 338)              */
                                  /* 306:����                    ����: (306) */
                                  /* 307:�Ǽ�                    �Ǽ�: (307) */
                                  /* 308:����                    ����: (308) */
                                  /* 309:����/����          ����,����: (309) */
                                  /* 310:���                    ���: (310) */
                                  /* 311:����                    ����: (311) */
                                  /* 312:��/�漭��   ��Ź�ۼ���: (312) */
                                  /* 313:IT S/W&SVC      IT S/W & SVC: (313) */
                                  /* 314:IT H/W                IT H/W: (314) */
                                  /* 338:����/��ȭ          ����,��ȭ: (338) */
    char    Sup_small       [ 3]; /* �����ڵ�(KOSPI:��/KOSDAQ:��)�з�        */
                                  /* KOSPI�Һз�    (022 ~ 025)              */
                                  /* 022:����                    ����: (022) */
                                  /* 024:����                    ����: (024) */
                                  /* 025:�����                �����: (025) */
                                  /* KOSDAQ�ߺз�   (315 ~ 337)              */
                                  /* 315:���ķ�/���      ���ķ�,���: (315) */
                                  /* 316:����/�Ƿ�          ����,�Ƿ�: (316) */
                                  /* 317:����/����          ����,����: (317) */
                                  /* 318:����/��ü����  ����,��ü����: (318) */
                                  /* 319:ȭ��                    ȭ��: (319) */
                                  /* 320:����                    ����: (320) */
                                  /* 321:��ݼ�                ��ݼ�: (321) */
                                  /* 322:�ݼ�                    �ݼ�: (322) */
                                  /* 323:���/���          ���,���: (323) */
                                  /* 324:�Ϲ���������    �Ϲ���������: (324) */
                                  /* 325:�Ƿ�/���б��  �Ƿ�,���б��: (325) */
                                  /* 326:������/��ǰ  ������,��ǰ: (326) */
                                  /* 327:��Ÿ����            ��Ÿ����: (327) */
                                  /* 328:��ż���        ��ż���: (328) */
                                  /* 329:��ۼ���        ��ۼ���: (329) */
                                  /* 330:���ͳ�                ���ͳ�: (330) */
                                  /* 331:������������    ������������: (331) */
                                  /* 332:����Ʈ����        ����Ʈ����: (332) */
                                  /* 333:��ǻ�ͼ���    ��ǻ�ͼ���: (333) */
                                  /* 334:������            ������: (334) */
                                  /* 335:�������            �������: (335) */
                                  /* 336:�ݵ�ü                �ݵ�ü: (336) */
                                  /* 337:IT��ǰ                IT��ǰ: (337) */
                                  /*-----------------------------------------*/
                                  /* KOSPI����                |������:(�ڵ�) */
                                  /*-----------------------------------------*/
    char    Cmfac_f             ; /* ����������                ������: (027) */
                                  /* Y:�ش� N:���ش�                         */
    char    Cdivd_f             ; /* ����������񱸺�        �������: (041) */
                                  /* Y:�ش� N:���ش�                         */
    char    Ccntl_idx_f         ; /* ���豸���������    ���豸�����: (042) */
                                  /* Y:�ش� N:���ش�                         */
    char    Ckospi200_f         ; /* KOSPI200����                            */
                                  /* 0:��ä�� ��������       KOSPI200: (101) */
                                  /* 1:������         KOSPI200 ������: (102) */
                                  /* 2:�������     KOSPI200 �������: (103) */
                                  /* 3:�Ǽ���         KOSPI200 �Ǽ���: (104) */
                                  /* 4:����             KOSPI200 ����: (105) */
                                  /* 5:����             KOSPI200 ����: (106) */
    char    Ckospi50100_f       ; /* KOSPI100/KOSPI50����                    */
                                  /* 0:��ä��                                */
                                  /* 1:KOSPI100              KOSPI100: (201) */
                                  /* 2:KOSPI50                KOSPI50: (202) */
                                  /*-----------------------------------------*/
                                  /* KOSDAQ����               |������:(�ڵ�) */
                                  /*-----------------------------------------*/
    char    Cvntr_corp_f        ; /* ��ó�������                ��ó: (302) */
                                  /* Y:�ش� N:���ش�                         */
    char    Ckostar_f           ; /* STAR��������          KOSTAR����: (403) */
                                  /* Y:�ش� N:���ش�                         */
                                  /* ��Ÿ����                  IT��ó: (305) */
                                  /* (304:�ڽ���IT) + (��ó�������)         */
                                  /*-----------------------------------------*/
                                  /* KRX(����)����            |������:(�ڵ�) */
                                  /*-----------------------------------------*/
    char    Ckrx100_f           ; /* KRX100����                KRX100: (501) */
                                  /* Y:�ش� N:���ش�                         */
/*---------------------------------------------------------------------------*/
/* ���� �Ϲ����� �׸�                                                        */
/*---------------------------------------------------------------------------*/
    char    Sdivd_mon       [ 2]; /* ����                                  */
                                  /*                       KOSPI :        NO */
                                  /*                       KOSDAQ:        mm */
    char    Sfprc           [11]; /* �׸鰡                                  */
                                  /*                       KOSPI : 9(9)v9(2) */
                                  /*                       KOSDAQ:      9(7) */
    char    Sstprc          [ 9]; /* ���ذ�                                  */
                                  /*                       KOSPI :      9(9) */
                                  /*                       KOSDAQ:      9(7) */
    char    Scapital        [17]; /* �ں���                                  */
                                  /*                       KOSPI :9(15)v9(2) */
                                  /*                       KOSDAQ:     9(17) */
    char    Slist_jusu      [12]; /* �����ֽļ�                              */
                                  /*                       KOSPI :     9(12) */
                                  /*                       KOSDAQ:     9(12) */
    char    Sdivd_rt        [ 6]; /* ��������                              */
                                  /*                       KOSPI :        NO */
                                  /*                       KOSDAQ: 9(5)v9(1) */
    char    Ss_yj_rate      [ 5]; /* �ſ������ܰ����                        */
                                  /*                       KOSPI : 9(3)v9(2) */
                                  /*                       KOSDAQ: 9(3)v9(2) */
    char    Ctrade_stop_f       ; /* �ŷ���������          N.���� Y.�ŷ����� */
    char    Cargmt_trade_f      ; /* �����Ÿű���          N:���� Y:�����Ÿ� */
    char    Ckwanli_f           ; /* ��������              N:���� Y:����     */
    char    Smkt_warn_f     [ 2]; /* ����溸�����ڵ�                        */
                                  /* 00:���� 01:���� 02:��� 03:����         */
    char    Cmkt_warn_noti_f    ; /* ����溸�������ڵ�  N:���� Y:����     */
    char    Cgongsi_f           ; /* �Ҽ��ǰ�����������    N:���� Y:����     */
    char    Cdetour_list_f      ; /* ��ȸ���屸��          N:���� Y:��ȸ���� */
    char    Slak_f          [ 2]; /* �ǹ������                              */
                                  /* 00:�ش����        01:�Ǹ���            */
                                  /* 02:����          03:�й��            */
                                  /* 04:�ǹ��          05:�߰�����        */
                                  /* 06:�Ǹ��߰�����  99:��Ÿ              */
};
#define	SZ_STKCODE_STRUC	sizeof(struct	STKCODE_STRUC)
#define STKCODE_NAME "STKCODE"

/*****************************************************************************/
/* ELW ��������   �׸�                                                       */
/*****************************************************************************/
struct ELWCODE_STRUC {
    char    Sjong_code      [ 7];		/* �����ڵ�                                */
    char    Sjong_kname     [40];		/* �ѱ������                              */
    char    Sbase_ast		[5][12];	/* ELW�����ڻ�(5��)                        */
                                  		/* KOSPI100����: �����ڵ�                  */
                                  		/* KOSPI200����: "KSP200"                  */
    char    Sisu_prtc_kname [40]; 		/* ELW�ѱ۹�������                       */
    char    Sisu_prtc_no    [ 5]; 		/* ELW�������ڵ�                         */
    char    Sexrc_prc       [10]; 		/* ELW��簡��                   9(8)v9(2) */
    char    Slast_trdt      [ 8]; 		/* ELW�����ŷ���                  YYYYMMDD */
    char    Sremn_day       [ 4]; 		/* �����ϼ� (�񿵾��� ����)                */
    char    Sremn_bus_day   [ 4]; 		/* �����������ϼ�                          */
    char    Crgt_type_f         ; 		/* ELW �Ǹ�����  C.CALL P:PUT E:��Ÿ       */
    char    Smkt_prtc_no1   [ 5]; 		/* ELW LPȸ����ȣ1                         */
    char    Smkt_prtc_no2   [ 5]; 		/* ELW LPȸ����ȣ2                         */
    char    Smkt_prtc_no3   [ 5]; 		/* ELW LPȸ����ȣ3                         */
    char    Smkt_prtc_no4   [ 5]; 		/* ELW LPȸ����ȣ4                         */
    char    Smkt_prtc_no5   [ 5]; 		/* ELW LPȸ����ȣ5                         */
    char    Smkt_prtc_no6   [ 5]; 		/* ELW LPȸ����ȣ6                         */
    char    Smkt_prtc_no7   [ 5]; 		/* ELW LPȸ����ȣ7                         */
    char    Smkt_prtc_no8   [ 5]; 		/* ELW LPȸ����ȣ8                         */
    char    Smkt_prtc_no9   [ 5]; 		/* ELW LPȸ����ȣ9                         */
    char    Smkt_prtc_no10  [ 5]; 		/* ELW LPȸ����ȣ10                        */
    char    Sstd_code       [12]; 		/* ǥ�������ڵ�                            */
    char    Cnovel_opt_f;		 		/* ELW �̻��ɼ� 0:ǥ�� 1:������ 2:�������� */
	char	SLPlast_day		[ 8];		//KJI 20110823 ELW LP ������ �߰�
};
#define	SZ_ELWCODE_STRUC	sizeof(struct	ELWCODE_STRUC)
#define ELWCODE_NAME "ELWCODE"

/*****************************************************************************/
/* ELW ��������� �׸�                                                       */
/*****************************************************************************/
struct ELWISUCODE_STRUC {
    char Sisu_code           [ 5]; /* ELW�������ڵ�                       */
    char Sisu_name           [40]; /* ELW�ѱ۹�������                     */
};
#define	SZ_ELWISUCODE_STRUC	sizeof(struct	ELWISUCODE_STRUC)
#define ELWISUCODE_NAME "ELWISUCODE"

/*****************************************************************************/
/* ELW�����ڻ��ڵ� ����Ʈ                                                    */
/*****************************************************************************/
struct ELWBASECODE_STRUC {
	char Sstd_code           [12]; /* �����ڻ��ڵ�(ǥ��)                     */
	char Sjong_code          [10]; /* �����ڻ��ڵ�(����)					 */
	char Sjong_kname         [40]; /* �����ڻ��                             */
	char Sstd_mkt			 [ 1]; /* �����ڻ���屸��						 */
	char Sstd_fmt			 [ 1]; /* �����ڻ�Format						 */
	char Sort_gb			 [ 1]; /* ���ı���								 */
};
#define SZ_ELWBASECODE_STRUC  sizeof( struct ELWBASECODE_STRUC )
#define ELWBASECODE_NAME "ELWBASECODE"

/*****************************************************************************/
/* ELW LP ����Ʈ                                                             */
/*****************************************************************************/
struct ELWLPCODE_STRUC {
	char Slp_code           [ 3]; /* ȸ�����ڵ�			                      */
	char Slp_name           [12]; /* ȸ�����					             */
	char Skrx_code          [ 5]; /* KRXȸ�����ڵ�				             */
};
#define SZ_ELWLPCODE_STRUC  sizeof( struct ELWLPCODE_STRUC )
#define ELWLPCODE_NAME "ELWLPCODE"

/*****************************************************************************/
/* OTCBB                                                                     */
/*****************************************************************************/
struct OTBCODE_STRUC {
    char Sjong_code         [ 6]; /* �����ڵ�                               */
    char Sstd_code          [12]; /* ǥ���ڵ�                               */
    char Sjong_kname        [30]; /* �ѱ������                             */
};
#define	SZ_OTBCODE_STRUC	sizeof(struct	OTBCODE_STRUC)
#define OTBCODE_NAME "OTBCODE"


/*****************************************************************************/
/* KOSPI����                                                                 */
/*****************************************************************************/
struct KSPICODE_STR4C {
    char Sup_code            [ 3]; /* �����ڵ�                               */
    char Sup_name            [20]; /* �ѱ������                             */
};
#define	SZ_KSPICODE_STRUC	sizeof(struct	KSPICODE_STRUC)
#define KSPICODE_NAME "KSPICODE"

/*****************************************************************************/
/* KOSDAQ����                                                                */
/*****************************************************************************/
struct KSDICODE_STRUC {
    char Sup_code            [ 3]; /* �����ڵ�                               */
    char Sup_name            [20]; /* �ѱ������                             */
};
#define	SZ_KSDICODE_STRUC	sizeof(struct	KSDICODE_STRUC)
#define KSDICODE_NAME "KSDICODE"

/*****************************************************************************/
/* KRX����                                                                   */
/*****************************************************************************/
struct KRXICODE_STRUC {
    char Sup_code            [ 3]; /* �����ڵ�                               */
    char Sup_name            [20]; /* �ѱ������                             */
};
#define	SZ_KRXICODE_STRUC	sizeof(struct	KRXICODE_STRUC)
#define KRXICODE_NAME "KRXICODE"

/*****************************************************************************/
/* OTCBB����                                                                 */
/*****************************************************************************/
struct OTBICODE_STRUC {
    char Sup_code            [ 3]; /* �����ڵ�                               */
    char Sup_name            [20]; /* �ѱ������                             */
};
#define SZ_OTBICODE_STRUC   sizeof(struct   OTBICODE_STRUC)
#define OTBICODE_NAME "OTBICODE"

/*****************************************************************************/
/* ����                                                                      */
/*****************************************************************************/
struct FUTCODE_STRUC {
    char Sjong_code          [ 8]; /* �����ڵ�                               */
    char Sstd_code           [12]; /* ǥ���ڵ�                               */
    char Sjong_kname         [30]; /* �ѱ������                             */
};
#define SZ_FUTCODE_STRUC   sizeof(struct   FUTCODE_STRUC)
#define FUTCODE_NAME "FUTCODE"

/*****************************************************************************/
/* ����(��������)                                                            */
/*****************************************************************************/
struct FUTSCODE_STRUC {
    char Sjong_code          [ 8]; /* �����ڵ�                               */
    char Sstd_code           [12]; /* ǥ���ڵ�                               */
    char Sjong_kname         [30]; /* �ѱ������                             */
};
#define SZ_FUTSCODE_STRUC   sizeof(struct   FUTSCODE_STRUC)
#define FUTSCODE_NAME "FUTSCODE"

/*****************************************************************************/
/* �ɼ�                                                                      */
/*****************************************************************************/
struct OPTCODE_STRUC {
    char Sjong_code			[ 8]; /* �����ڵ�                               */
    char Sstd_code			[12]; /* ǥ���ڵ�                               */
    char Sjong_Name			[19]; /* �����1(��/ǲ ���� �κ�)               */
	char Sjong_Price		[11]; /* �����2(���ݺκ�)						*/
    char Catm_f					; /* ATM����       1:ATM, 2:ITM, 3:OTM		*/
	char Sjong_Mult			[ 8]; /* �ɼ� �ŷ��¼�							*/
};
#define SZ_OPTCODE_STRUC   sizeof(struct   OPTCODE_STRUC)
#define OPTCODE_NAME "OPTCODE"

/*****************************************************************************/
/* �ɼ� ATM����(�ֱٿ���)                                                    */
/*****************************************************************************/
struct ATMPRC_STRUC {
    char Satm_prc            [ 6]; /* ATM����                      9(4)v9(2) */
};
#define SZ_ATMPRC_STRUC   sizeof(struct   ATMPRC_STRUC)
#define ATMPRC_NAME "ATMPRC"

/*****************************************************************************/
/* �ֽļ���                                                                  */
/*****************************************************************************/
struct ZFUTCODE_STRUC {
    char Sjong_code			[ 8]; /* �����ڵ�                               */
    char Sstd_code			[12]; /* ǥ���ڵ�                               */
    char SBase_Name			[20]; /* �����ڻ��								*/
	char Sjong_kname		[30]; /* �ѱ������                             */
    char Catm_f                  ; /* ATM����       1:ATM, 2:ITM, 3:OTM      */
};
#define SZ_ZFUTCODE_STRUC   sizeof(struct   ZFUTCODE_STRUC)
#define ZFUTCODE_NAME "ZFUTCODE"


/*****************************************************************************/
/* �ֽĿɼ�                                                                  */
/*****************************************************************************/
struct ZOPTCODE_STRUC {
    char Sjong_code			[ 8];	/* �����ڵ�								*/
    char Sstd_code			[12];	/* ǥ���ڵ�								*/
	char SBase_Name			[11];	/* �����-�����ڻ��					*/
	char SJong_CallPut		[1];	/* �����-��/ǲ ����					*/
	char SJong_Month		[4];	/* �����-���							*/
	char SJong_Price		[10];	/* �����-����							*/
    char SJong_Etc			[24];	/* �����-������						*/
    char Catm_f					;	/* ATM����       1:ATM, 2:ITM, 3:OTM	*/
};
#define SZ_ZOPTCODE_STRUC   sizeof(struct   ZOPTCODE_STRUC)
#define ZOPTCODE_NAME "ZOPTCODE"

/*****************************************************************************/
/* �ֽĿɼ� ATM����(�ֱٿ���)                                                */
/*****************************************************************************/
struct ZATMPRC_STRUC {
    char Sjong_code          [ 8]; /* �����ڵ�                               */
    char Satm_prc            [ 8]; /* ATM����                      9(8)      */
};
#define SZ_ZATMPRC_STRUC   sizeof(struct   ZATMPRC_STRUC)
#define ZATMPRC_NAME "ZATMPRC"

/*****************************************************************************/
/* �ֽļ���/�ɼ� �����ڻ�����                                                */
/*****************************************************************************/
struct ZOBJCODE_STRUC {
   USHORT   Wdrvt_id;              /* �����ڻ� �ŷ�����ڵ�  */
   UCHAR    Cfiller11;             /* 0x20 ' '                 */
   UCHAR    Sfdrvt_id[10];         /* �ֽļ����Ļ���ǰID       */
   UCHAR    Cfiller12;             /* 0x20 ' '                 */
   UCHAR    Sodrvt_id[10];         /* �ֽĿɼ��Ļ���ǰID       */
   UCHAR    Cfiller13;             /* 0x20 ' '                 */
   UCHAR    Sbase_ast_id[3];       /* �����ڻ�ID               */
   UCHAR    Cfiller14;             /* 0x20 ' '                 */
   UCHAR    Sobject_cd[12];        /* �����ڻ� �ڵ�            */
   UCHAR    Cfiller21;             /* 0x31 ':'                 */
   UCHAR    Sobject_nm[16];        /* �����ڻ� ��              */
   UCHAR    Cfiller22;             /* 0x31 ':'                 */
   UCHAR    Cfutopt_f;             /* �����ɼ� ������          */
                                   /* 'A' : �����ɼ� ��� ��� */
                                   /* 'F' : ����          ��� */
                                   /* 'O' : �ɼ�          ��� */
   UCHAR    Cfiller31;             /* 0x0d "CR"                */
};
#define SZ_ZOBJCODE_STRUC  sizeof( struct ZOBJCODE_STRUC )
#define ZOBJCODE_NAME "ZOBJCODE"

/*****************************************************************************/
/* �׷��                                                                    */
/*****************************************************************************/
struct GRPCODE_STRUC {
    char Sgrp_code           [ 4]; /* �׷���ڵ�                             */
                                   /*                  ���ǻ�����: 0001~0999 */
                                   /*                    ��������: 1001~1999 */
    char Sgrp_name           [20]; /* �׷���                               */
    char Sjong_code          [ 6]; /* �����ڵ�                               */
};
#define SZ_GRPCODE_STRUC   sizeof(struct   GRPCODE_STRUC)
#define GRPCODE_NAME "GRPCODE"

/*****************************************************************************/
/* �׸��ڵ� ����Ʈ                                                           */
/*****************************************************************************/
struct THEMACODE_STRUC {
    char Sthema_code         [ 4]; /* �׸��ڵ�                               */
    char Sthema_name         [50]; /* �׸���                                 */
    char Sjong_code          [ 6]; /* �����ڵ�                               */
};
#define SZ_THEMACODE_STRUC   sizeof(struct   THEMACODE_STRUC)
#define THEMACODE_NAME "THEMACODE"

/*****************************************************************************/
/* �ŷ��� ����Ʈ                                                             */
/*****************************************************************************/
struct MEMBCODE_STRUC {
    char Smemb_code          [ 3]; /* �ŷ����ڵ�                             */
    char Smemb_name          [20]; /* �ŷ�����                               */
    char Cmemb_f                 ; /* 0:����, 1:�ܱ���                       */
    char Smemb_fcode         [ 5]; /* �ŷ��� Full�ڵ�                        */
};
#define SZ_MEMBCODE_STRUC   sizeof(struct   MEMBCODE_STRUC)
#define MEMBCODE_NAME "MEMBCODE"

/*****************************************************************************/
/* �ؿ��ڵ�                                                                  */
/*****************************************************************************/
struct FRGNCODE_STRUC {
    char Ssymbol		[10];   /* �ɺ��ڵ�                             */
    char Cdata_kind_f	[ 1];   /* ���� - P:�̱����� Q:�̱�����         */
								/*        D:�̱����� �������(ADR)      */
								/*        C:��ǰ���� F:CME����          */
								/*        G:�������� �������(GDR)      */
								/*        X:ȯ�� R:�ݸ� L:�����ݸ�      */
								/*        B:�ֿ䱹����ä N:�����ݸ�     */
								/*        M:�ݵ�ü H:�����ֿ�����       */
								/*        E:ECN W:�����ְ�����          */
    char Skname			[40];   /* �ѱ۸�                               */
    char Sename			[39];   /* ������                               */
    char Sup_code		[ 4];   /* MULTEX ���� �з��ڵ�                 */
    char Cdowj_inc		[ 1];   /* �ٿ�30 ��������   (�̱����� �ش�)  */
    char Cnasd_inc		[ 1];   /* ������100 ��������(�̱����� �ش�)  */
    char Csnp_inc		[ 1];   /* S&P500 ��������   (�̱����� �ش�)  */
    char Sisu_jusu		[15];   /* �� �ֽ� �߻���                       */
    char Strade_f		[ 4];   /* �ŷ��� �ڵ�                          */
    char Sevent_date	[10];   /* �̺�Ʈ ��¥                          */
    char Snatl_f		[ 3];   /* ���������ڵ�                         */
};
#define SZ_FRGNCODE_STRUC   sizeof(struct   FRGNCODE_STRUC)
#define FRGNCODE_NAME "FRGNCODE"
/*****************************************************************************/
/* �ؿ�����                                                                  */
/*****************************************************************************/
struct FRGNJISU_STRUC {
    char Ssymbol		[10];   /* �ɺ��ڵ�                             */
    char Sname			[40];   /* �����                               */
    char SGubun1		[1];
	char SGubun2		[1];
};
#define SZ_FRGNJISU_STRUC   sizeof(struct   FRGNJISU_STRUC)
#define FRGNJISU_NAME "FRGNJISU"

/*****************************************************************************/
/* ��ǰ ����                                                                 */
/*****************************************************************************/
struct CFUTCODE_STRUC {
    char 	Sjong_code       [ 8]; /* �����ڵ�                               */
    char 	Sstd_code        [12]; /* ǥ���ڵ�                               */
	// -->2011/01/21 Yunchang - ������� �߸��� ������ �־ �������� 50byte�� ��������� �ش޶�� ��û�Ͽ� ������.
	//char 	Sjong_kname      [20]; /* �ѱ������                             */
    //char 	Smon_kname       [30]; /* �ѱۿ��������                         */
	char 	Sjong_kname      [50]; /* �ѱ������                             */
	// -->2011/01/21 Yunchang
    UCHAR	Sbase_ast_cd     [ 6]; /* �����ڻ�ID               	             */
                                   /* 'KTB   ':3�ⱹä    '5TB   ':5�ⱹä   */
                                   /* 'LKTB  ':10�ⱹä   'MSB   ':���ä    */
                                   /* 'CRD   ':CD                            */
                                   /* 'USD   ':�̱��޷�   'JPY   ':�Ϻ���    */
                                   /* 'EUR   ':��������                      */
                                   /* 'GOLD  ':��         'LHG   ':����      */
	UCHAR   Sdesc            [ 2]; /* �Ҽ��� ����                            */
    char    Shoga_unit       [ 5]; /* ȣ������                      9(3)v9(2)*/
};
#define SZ_CFUTCODE_STRUC   sizeof(struct   CFUTCODE_STRUC)
#define CFUTCODE_NAME "CFUTCODE"

/*****************************************************************************/
/* ��ǰ ����(��������)                                                       */
/*****************************************************************************/
struct CFUTSCODE_STRUC {
    char 	Sjong_code       [ 8]; /* �����ڵ�                               */
    char 	Sstd_code        [12]; /* ǥ���ڵ�                               */
	// -->2011/01/21 Yunchang - ������� �߸��� ������ �־ �������� 50byte�� ��������� �ش޶�� ��û�Ͽ� ������.
	//char 	Sjong_kname      [20]; /* �ѱ������                             */
    //char 	Smon_kname       [30]; /* �ѱۿ��������                         */
	char 	Sjong_kname      [50]; /* �ѱ������                             */
	// -->2011/01/21 Yunchang
   	UCHAR   Sbase_ast_cd     [ 6]; /* �����ڻ�ID                             */
                                   /* 'KTB   ':3�ⱹä    '5TB   ':5�ⱹä   */
                                   /* 'LKTB  ':10�ⱹä   'MSB   ':���ä    */
                                   /* 'CRD   ':CD                            */
                                   /* 'USD   ':�̱��޷�   'JPY   ':�Ϻ���    */
                                   /* 'EUR   ':��������                      */
                                   /* 'GOLD  ':��         'LHG   ':����      */
	UCHAR   Sdesc            [ 2]; /* �Ҽ��� ����                            */
    char    Shoga_unit       [ 5]; /* ȣ������                      9(3)v9(2)*/
};
#define SZ_CFUTSCODE_STRUC   sizeof(struct   CFUTSCODE_STRUC)
#define CFUTSCODE_NAME "CFUTSCODE"

/*****************************************************************************/
/* ��ǰ �ɼ�                                                                 */
/*****************************************************************************/
struct COPTCODE_STRUC {
    char 	Sjong_code       [ 8]; /* �����ڵ�                               */
    char 	Sstd_code        [12]; /* ǥ���ڵ�                               */
    char 	Sjong_kname      [30]; /* �ѱ������                             */
    char 	Catm_f               ; /* ATM����       1:ATM, 2:ITM, 3:OTM      */
   	UCHAR   Sbase_ast_cd     [ 6]; /* �����ڻ�ID                             */
                                   /* 'KTB   ':3�ⱹä    '5TB   ':5�ⱹä   */
                                   /* 'LKTB  ':10�ⱹä   'MSB   ':���ä    */
                                   /* 'CRD   ':CD                            */
                                   /* 'USD   ':�̱��޷�   'JPY   ':�Ϻ���    */
                                   /* 'EUR   ':��������                      */
                                   /* 'GOLD  ':��         'LHG   ':����      */
	UCHAR   Sdesc            [ 2]; /* �Ҽ��� ����                            */
    char    Shoga_unit       [ 5]; /* ȣ������                9(3)v9(2)      */
};
#define SZ_COPTCODE_STRUC   sizeof(struct   COPTCODE_STRUC)
#define COPTCODE_NAME "COPTCODE"

/*****************************************************************************/
/* ��ǰ�ɼ� ATM����(�ֱٿ���)                                                */
/*****************************************************************************/
struct CATMPRC_STRUC {
    char Sjong_code          [ 8]; /* �����ڵ�                               */
    char Satm_prc            [ 8]; /* ATM����                      9(8)      */
};
#define SZ_CATMPRC_STRUC   sizeof(struct   CATMPRC_STRUC)
#define CATMPRC_NAME "CATMPRC"

/*****************************************************************************/
/* ��ǰ����                                                                  */
/*****************************************************************************/
struct COBJCODE_STRUC {
	UCHAR    Sdrvt_id1[2];          /* �����ڻ� ID 2byte            */
    UCHAR    Cfiller;               /* 0x20 ' '                     */
    UCHAR    Sdrvt_id2[10];         /* �����ڻ� ID 10byte           */
    UCHAR    Cfiller1;              /* 0x20 ' '                     */
    UCHAR    Sbase_ast_cd[3];       /* �����ڻ� CODE 6byte          */
                                    /* 'KTB   ':3�ⱹä    '5TB   ':5�ⱹä   */
                                    /* 'LKTB  ':10�ⱹä   'MSB   ':���ä    */
                                    /* 'CRD   ':CD                            */
                                    /* 'USD   ':�̱��޷�   'JPY   ':�Ϻ���    */
                                    /* 'EUR   ':��������                      */
                                    /* 'GOLD  ':��         'LHG   ':����      */
    UCHAR    Cfiller2;              /* 0x20 ' '                     */
    UCHAR    Sobject_nm[20];        /* �����ڻ� �ѱ۸�              */
    UCHAR    Cfiller3;              /* 0x31 ':'                     */
    UCHAR    Cfutopt_f;             /* �����ɼ� ������              */
                                    /* 'A' : �����ɼ� ��� ���     */
                                    /* 'F' : ����          ���     */
                                    /* 'O' : �ɼ�          ���     */
    UCHAR    Cfiller4;              /* 0x31 ':'                     */
    UCHAR    Sdesc[2];              /* �Ҽ��� ����                  */
 //   UCHAR    Cfiller5;              /* 0x31 ':'                     */
};
#define SZ_COBJCODE_STRUC   sizeof(struct   COBJCODE_STRUC)
#define COBJCODE_NAME "COBJCODE"

#pragma pack(pop)
/********** mast_def.h : end of list **********/
