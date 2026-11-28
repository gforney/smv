#include "gzfile_util.h"

#include <errno.h>
#include <limits.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <zlib.h>

struct fgfile {
  bool compressed;
  union {
    FILE *plain;
    gzFile gzip;
  } handle;
};

/* ------------------ FGOPEN ------------------------ */

FGFILE *FGOPEN(const char *file, const char *mode){
  size_t length = strlen(file);
  FGFILE *stream = malloc(sizeof *stream);

  if(stream == NULL)return NULL;

  stream->compressed = length >= 3 && strcmp(file + length - 3, ".gz") == 0;
  if(stream->compressed){
    stream->handle.gzip = gzopen(file, mode);
    if(stream->handle.gzip != NULL)return stream;
  }
  else{
    stream->handle.plain = fopen(file, mode);
    if(stream->handle.plain != NULL)return stream;
  }

  free(stream);
  return NULL;
}

/* ------------------ FGREAD ------------------------ */

size_t FGREAD(void *ptr, size_t size, size_t count, FGFILE *stream){
  if(stream->compressed){
    return gzfread(ptr, size, count, stream->handle.gzip);
  }
  return fread(ptr, size, count, stream->handle.plain);
}

/* ------------------ FGGETS ------------------------ */

char *FGGETS(char *buffer, int size, FGFILE *stream){
  if(stream->compressed){
    return gzgets(stream->handle.gzip, buffer, size);
  }
  return fgets(buffer, size, stream->handle.plain);
}

/* ------------------ FGTELL ------------------------ */

long FGTELL(FGFILE *stream){
  if(stream->compressed){
    z_off_t offset = gztell(stream->handle.gzip);
    if(offset < 0)return -1L;
    if(offset > LONG_MAX){
      errno = EOVERFLOW;
      return -1L;
    }
    return (long)offset;
  }
  return ftell(stream->handle.plain);
}

/* ------------------ FGSEEK ------------------------ */

int FGSEEK(FGFILE *stream, long offset, int whence){
  if(stream->compressed){
    return gzseek(stream->handle.gzip, offset, whence) < 0 ? -1 : 0;
  }
  return fseek(stream->handle.plain, offset, whence);
}

/* ------------------ FGCLOSE ------------------------ */

int FGCLOSE(FGFILE *stream){
  int status;

  if(stream->compressed){
    status = gzclose(stream->handle.gzip);
  }
  else{
    status = fclose(stream->handle.plain);
  }
  free(stream);
  return status;
}
