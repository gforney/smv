#ifndef FILE_UTIL_H_DEFINED
#define FILE_UTIL_H_DEFINED
#include "fopen.h"

#ifdef IN_FILE_UTIL
int show_timings = 0;
#else
extern int show_timings;
#endif

// vvvvvvvvvvvvvvvvvvvvvvvv header files vvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvv

#include <time.h>
#ifdef __MINGW32__
#include "options.h"
#include <stdio.h>
#endif
#ifdef pp_GCC
#include <unistd.h>
#endif

#if defined(__linux__) || (defined(__APPLE__) && defined(__MACH__))
#include <sys/stat.h>
#include <unistd.h>
#endif

#ifdef WIN32
#define PATH_MAX MAX_PATH
#elif defined(__linux__)
#include <linux/limits.h>
#elif defined(__APPLE__) && defined(__MACH__)
#include <mach-o/dyld.h>
#include <sys/syslimits.h>
#endif

/* --------------------------  mtfiledata ------------------------------------
 */

typedef struct {
  char *file;
  unsigned char *buffer;
  FILE_SIZE file_size, chars_read, file_offset, nchars;
  int i, nthreads;
} mtfiledata;

// vvvvvvvvvvvvvvvvvvvvvvvv structures vvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvv

/* --------------------------  filelistdata ------------------------------------
 */

typedef struct {
  char *file;
  int type;
} filelistdata;

/* --------------------------  bufferdata ------------------------------------
 */

typedef struct {
  char *file;
  unsigned char *buffer; // copy of file
  FILE_SIZE nbuffer;     // size of buffer
  FILE_SIZE nfile;       // amount of data in buffer
} bufferdata;

// vvvvvvvvvvvvvvvvvvvvvvvv preprocessing directives
// vvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvv

#ifdef WIN32
#define UNLINK _unlink
#else
#define UNLINK unlink
#endif

#ifdef X64
#define FSEEK(a, b, c) _fseeki64(a, b, c)
#define FTELL(a) _ftelli64(a)
#else
#define FSEEK(a, b, c) fseeko(a, b, c)
#define FTELL(a) ftello(a)
#endif

#define ALLDATA_OFFSET 0
#define ALLDATA_NVALS 0

#define REPLACE_FILE 0
#define APPEND_FILE 1

#define FILE_MODE 0
#define DIR_MODE 1

#define NOT_FORCE_IN_DIR 0
#define FORCE_IN_DIR 1

#define DATA_AT_START 0
#define DATA_MAPPED 1

#define FEOF(stream) feof_buffer(stream->fileinfo)
#define FGETS(buffer, size, stream) fgets_buffer(stream->fileinfo, buffer, size)
#define REWIND(stream) rewind_buffer(stream->fileinfo)
#define FCLOSE(stream) fclose_buffer(stream->fileinfo)

#define BFILE bufferstreamdata

#define FILE_EXISTS(a) FileExists(a, NULL, 0, NULL, 0)
#define FILE_EXISTS_CASEDIR(a)                                                 \
  FileExists(a, filelist_casename, nfilelist_casename, filelist_casedir,       \
             nfilelist_casedir)
int FileExistsOrig(char *filename);

#ifdef WIN32
#define MKDIR(a) CreateDirectory(a, NULL)
#else
#define MKDIR(a)                                                               \
  mkdir(a, S_IRUSR | S_IWUSR | S_IXUSR | S_IRGRP | S_IXGRP | S_IROTH | S_IXOTH)
#endif

#ifdef WIN32
#define ACCESS _access
#define F_OK 0
#define W_OK 2
#else
#define ACCESS access
#endif

#ifndef NO
#define NO 0
#endif

#ifndef YES
#define YES 1
#endif

#ifdef WIN32
#define CHDIR _chdir
#define GETCWD _getcwd
#define SEP '\\'
#else
#define CHDIR chdir
#define GETCWD getcwd
#define SEP '/'
#endif

#include "string_util.h"

// vvvvvvvvvvvvvvvvvvvvvvvv headers vvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvv
EXTERNCPP int MakeFile(char *file, int size);
EXTERNCPP void FreeBufferInfo(bufferdata *bufferinfoptr);
EXTERNCPP bufferdata *InitBufferData(char *file);
EXTERNCPP bufferdata *File2Buffer(char *file, bufferdata *bufferinfo,
                                  int *nreadptr);
EXTERNCPP FILE_SIZE fread_p(char *file, unsigned char *buffer, FILE_SIZE offset,
                            FILE_SIZE nchars, int nthreads);
EXTERNCPP void FileErase(char *file);
EXTERNCPP FILE *FOPEN(const char *file, const char *mode);
EXTERNCPP FILE *fopen_indir(char *dir, char *file, char *mode);
EXTERNCPP FILE *fopen_2dir(char *file, char *mode, char *scratch_dir);
EXTERNCPP void TestWrite(char *scratchdir, char **fileptr);
EXTERNCPP int FFLUSH(void);
EXTERNCPP int PRINTF(const char *format, ...);
EXTERNCPP void SetStdOut(FILE *stream);
EXTERNCPP void GetFileSizeLabel(int size, char *sizelabel);
EXTERNCPP char *GetFloatFileSizeLabel(float size, char *sizelabel);
EXTERNCPP void CopyFILE(char *destdir, char *filein, char *fileout, int mode);
EXTERNCPP char *GetSmokeZipPath(char *progdir);
EXTERNCPP int IfFirstLineBlank(char *file);
EXTERNCPP int HaveProg(char *prog);
EXTERNCPP int FileCat(char *file_in1, char *file_in2, char *file_out);
EXTERNCPP unsigned int StreamCopy(FILE *stream_in, FILE *stream_out, int flag);
EXTERNCPP void FileCopy(char *file_in, char *file_out);
EXTERNCPP void MakeOutFile(char *outfile, char *destdir, char *file1,
                           char *ext);
EXTERNCPP void FullFile(char *fileout, char *dir, char *file);
EXTERNCPP char *GetFileName(char *temp_dir, char *file, int force_in_temp_dir);
EXTERNCPP char *GetBaseFileName(char *buffer, char *file);

EXTERNCPP char *SetDir(char *argdir);
EXTERNCPP int GetFileInfo(char *filename, char *sourcedir, FILE_SIZE *filesize);
EXTERNCPP char *GetZoneFileName(char *buffer);
EXTERNCPP int Writable(char *dir);

EXTERNCPP int FileExists(char *filename, filelistdata *filelist, int nfiles,
                         filelistdata *filelist2, int nfiles2);
EXTERNCPP filelistdata *FileInList(char *file, filelistdata *filelist,
                                   int nfiles, filelistdata *filelist2,
                                   int nfiles2);
EXTERNCPP void FreeFileList(filelistdata *filelist, int *nfilelist);
#define FILE_MODE 0
#define DIR_MODE 1
EXTERNCPP int GetFileListSize(const char *path, char *filter, int mode);
EXTERNCPP int MakeFileList(const char *path, char *filter, int maxfiles,
                           int sort_files, filelistdata **filelist, int mode);
EXTERNCPP char *Which(char *progname, char **fullprognameptr);
EXTERNCPP FILE_SIZE GetFileSizeSMV(const char *filename);
EXTERNCPP time_t FileModtime(char *filename);
EXTERNCPP int IsFileNewer(char *file1, char *file2);
/**
 * @brief Get the path of the running executable. This always returns the path
 * of the executable (or a symlink if it is one).
 *
 * @return A buffer allocated by NEWMEMORY or NULL if an error occurred
 * (including hitting the maximum buffer size).
 */
EXTERNCPP char *GetBinPath();
/**
 * @brief Get the SMV root directory. This is the root directory where ancillary
 * files such as textures, object definitions, and global configurations files
 * are stored.
 *
 * This is derived from the following values (in order of descending priority):
 *   1. The value set by -bindir on the commandline.
 *   2. The dir pointed to by the SMV_ROOT_OVERRIDE environment variable
 *   3. The dir pointed to by the SMV_ROOT_OVERRIDE macro
 *   4. The directory of the running executable.
 *
 * @return A buffer allocated by NEWMEMORY or NULL if an error occurred
 * (including hitting the maximum buffer size).
 */
EXTERNCPP char *GetSmvRootDir();
/**
 * @brief Set the override value for the SMV root. Generally this is used
 * because the -bindir commandline parameter is set.
 *
 * @param path The path to set. If NULL, the value is unset.
 */
EXTERNCPP void SetSmvRootOverride(const char *path);
EXTERNCPP void PrintTime(const char *tag, int line, float *timer,
                         const char *label, int stop_flag);

EXTERNCPP int IsSootFile(char *shortlabel, char *longlabel);

EXTERNCPP char *LastName(char *argi);

// vvvvvvvvvvvvvvvvvvvvvvvv variables vvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvv

#ifndef STREXTERN
#ifdef WIN32
STREXTERN char STRDECL(dirseparator[], "\\");
#else
STREXTERN char STRDECL(dirseparator[], "/");
#endif
#endif

#endif
