#ifndef __MD5_H__
#define __MD5_H__

//error: 0; ok: 1
int md5_hex(const char *lpszBuff, unsigned int uLength, void *lpszMD5, unsigned int size = 16);
int md5_str(const char *lpszBuff, unsigned int uLength, void *lpszMD5, unsigned int size = 33);

#endif //__MD5_H__