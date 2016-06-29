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

#ifdef __cplusplus
    #define INITIALIZER(f) \
        static void f(void); \
        struct f##_t_ { f##_t_(void) { f(); } }; static f##_t_ f##_; \
        static void f(void)
#elif defined(_MSC_VER) && !defined(__GNUC__) && !defined(__MINGW32__) && !defined(__CYGWIN__)
    #pragma section(".CRT$XCU",read)
    #define INITIALIZER2_(f,p) \
        static void f(void); \
        __declspec(allocate(".CRT$XCU")) void (*f##_)(void) = f; \
        __pragma(comment(linker,"/include:" p #f "_")) \
        static void f(void)
    #ifdef _WIN64
        #define INITIALIZER(f) INITIALIZER2_(f,"")
    #else
        #define INITIALIZER(f) INITIALIZER2_(f,"_")
    #endif
#else
    #define INITIALIZER(f) \
        static void f(void) __attribute__((constructor)); \
        static void f(void)
#endif

INITIALIZER(win32_support) {
	_set_fmode( _O_BINARY );
}

static inline FILE* ms_fopen(const char *filename, const char *mode) {
  FILE* result = 0;
  fopen_s(&result, filename, mode);
  return result;
}

static inline int ms_open(const char *filename, int oflag, int pmode) {
  int result = -1;
  _sopen_s(&result, filename, oflag | O_BINARY, _SH_DENYNO, pmode);
  return result;
}
#endif  /* WIN32 */

#endif  /* BROTLI_TOOLS_WIN32_SUPPORT_H_ */