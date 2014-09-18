/***********************************************************
    SFserver.h (Rev 1.2)
	
	Server CGI program for SFSH.

    Copyright(c) 1997 SoftForum

	Programmed by stellar  (1997. 2. 3.)
***********************************************************/

#ifndef _SF_SERVER_H
#define _SF_SERVER_H

#ifdef __cplusplus
extern "C" {
#endif

void    InitSQL(void);
void    ConnectSQL(void);
void    DisconnectSQL(void);
void	SQLerror(char* msg);

long	GetChallenge(char* pUserid, char* passwd);
int		VerifyResponse(char* pUserid, long iResponse);

#ifdef __cplusplus
}
#endif

#endif /* _SF_SERVER_H */




