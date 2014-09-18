//
//
//


#ifdef __cplusplus__
extern "C"
{
#endif
int InitialLZO();
int CompressLZO(unsigned char *src, unsigned char *tar, int slen);
int DecompressLZO(unsigned char *src, unsigned char *tar, int slen);
#ifdef __cplusplus__
}
#endif