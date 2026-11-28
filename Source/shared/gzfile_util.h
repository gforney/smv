#ifndef GZFILE_UTIL_H_DEFINED
#define GZFILE_UTIL_H_DEFINED

#include <stddef.h>

#include "options_common.h"

typedef struct fgfile FGFILE;

// Opens .gz paths with zlib and other paths with stdio.
EXTERNCPP FGFILE *FGOPEN(const char *file, const char *mode);
// Returns the number of complete elements read.
EXTERNCPP size_t FGREAD(void *ptr, size_t size, size_t count, FGFILE *stream);
EXTERNCPP char *FGGETS(char *buffer, int size, FGFILE *stream);
// Returns the current byte position, or -1L on failure.
EXTERNCPP long FGTELL(FGFILE *stream);
// Returns 0 on success. Gzip offsets are uncompressed and SEEK_END is unsupported.
EXTERNCPP int FGSEEK(FGFILE *stream, long offset, int whence);
// Closes the underlying stream and frees the handle.
EXTERNCPP int FGCLOSE(FGFILE *stream);

#endif
