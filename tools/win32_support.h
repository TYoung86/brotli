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
#endif
#define fdopen _fdopen

#ifdef unlink
#undef unlink
#endif
#define unlink _unlink

#ifdef fopen
#undef fopen
#endif
#define fopen ms_fopen

#ifdef open
#undef open
#endif
#define open ms_open

#if defined(_MSC_VER) && (_MSC_VER >= 1400)
#ifdef fseek
#undef fseek
#endif
#define fseek _fseeki64

#ifdef ftell
#undef ftell
#endif
#define ftell _ftelli64

#endif /* defined(_MSC_VER) && (_MSC_VER >= 1400) */

#pragma push_macro("_fmode")
#undef _fmode
int _fmode = _O_BINARY;
#pragma pop_macro("_fmode")
int _CRT_fmode = _O_BINARY;


static inline FILE* ms_fopen(const char *filename, const char *mode) {
  FILE* result = 0;
  fopen_s(&result, filename, mode);
  return result;
}

static inline int ms_open(const char *filename, int oflag, int pmode) {
  int result = -1;
  if ( (oflag & O_TEXT) == 0 ) {
    oflag |= O_BINARY;
  }
  _sopen_s(&result, filename, oflag, _SH_DENYNO, pmode);
  return result;
}
#endif  /* _WIN32 */

#endif  /* BROTLI_TOOLS_WIN32_SUPPORT_H_ */