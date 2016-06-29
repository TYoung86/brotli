#ifndef BROTLI_TOOLS_WIN32_SUPPORT_H_
#define BROTLI_TOOLS_WIN32_SUPPORT_H_

#if defined(_WIN32)
#include <io.h>
#include <share.h>


#ifndef STDIN_FILENO
#define STDIN_FILENO _fileno(stdin)
#endif
#ifndef STDOUT_FILENO 
#define STDOUT_FILENO _fileno(stdout)
#endif
#ifndef S_IRUSR 
#define S_IRUSR S_IREAD
#endif
#ifndef S_IWUSR 
#define S_IWUSR S_IWRITE
#endif

#ifdef fdopen
#undef fdopen
#define fdopen _fdopen
#endif
#ifdef unlink
#undef unlink
#define unlink _unlink
#endif
#ifdef fopen
#undef fopen
#define fopen ms_fopen
#endif
#ifdef open
#undef open
#define open ms_open
#endif

#if defined(_MSC_VER) && (_MSC_VER >= 1400)
#ifdef fseek
#undef fseek
#define fseek _fseeki64
#endif
#ifdef ftell
#undef ftell
#define ftell _ftelli64
#endif
#endif

int _fmode = _O_BINARY;
unsigned int _CRT_fmode = _O_BINARY;


static inline FILE* ms_fopen(const char *filename, const char *mode) {
  FILE* result = 0;
  fopen_s(&result, filename, mode);
  return result;
}

static inline int ms_open(const char *filename, int oflag, int pmode) {
  int result = -1;
  _sopen_s(&result, filename, ( oflag & ~ O_TEXT ) | O_BINARY, _SH_DENYNO, pmode);
  return result;
}
#endif  /* WIN32 */

#endif  /* BROTLI_TOOLS_WIN32_SUPPORT_H_ */