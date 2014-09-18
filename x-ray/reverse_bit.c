/*** 8바이트 double 를 비트체인지하는 함수 *********/
double reverse_64 ( double a )
{

    int    high, low;
    int    a_high, a_low;

    memcpy((char *)&high, &a,   4);
    memcpy((char *)&low,  &a+4, 4);

    a_high = (high & 0xff000000)>>24 | (high & 0x00ff0000)>>8 | (high & 0x0000ff00)<<8 |(high & 0x000000ff)<<24;

    a_low = (low & 0xff000000)>>24 | (low & 0x00ff0000)>>8 | (low & 0x0000ff00)<<8 |(low & 0x000000ff)<<24;

    memcpy(&a,    (char *)&a_low,  4);
    memcpy(&a+4,  (char *)&a_high, 4);
    return a;

}

/****** 4바이트 Long Integer를 비트체인지하는 함수 *********/
int reverse_32 ( int a )
{
	int ret;
	ret = ( (a & 0xff000000)>>24 | (a & 0x00ff0000)>>8 | (a & 0x0000ff00)<<8 |(a & 0x000000ff)<<24 );
	return ret;
}

/*********** 2바이트 short Integer를 비트체인지하는 함수  ********/
short reverse_16 ( short a )
{
	short ret;
	ret = (a & 0xff00)>>8 | (a & 0x00ff)<<8 ;
	return ret;
}



/******** 사이즈를 체크하여 비트체인지 ***********/
double reverse_bit ( double a, short size_a )
{
	double res;

	if ( size_a == 8 )
	{
		res = reverse_64 ( a );
		return res;
	}

	else if ( size_a == 4 )
	{
		res = reverse_32 ( a );
		return res;
	}
	else if ( size_a == 2 )
	{
		res = reverse_16 (a );

		return res;
	}
	else
		return (0);
}