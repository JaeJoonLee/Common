/*** 8����Ʈ double �� ��Ʈü�����ϴ� �Լ� *********/
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

/****** 4����Ʈ Long Integer�� ��Ʈü�����ϴ� �Լ� *********/
int reverse_32 ( int a )
{
	int ret;
	ret = ( (a & 0xff000000)>>24 | (a & 0x00ff0000)>>8 | (a & 0x0000ff00)<<8 |(a & 0x000000ff)<<24 );
	return ret;
}

/*********** 2����Ʈ short Integer�� ��Ʈü�����ϴ� �Լ�  ********/
short reverse_16 ( short a )
{
	short ret;
	ret = (a & 0xff00)>>8 | (a & 0x00ff)<<8 ;
	return ret;
}



/******** ����� üũ�Ͽ� ��Ʈü���� ***********/
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