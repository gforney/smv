SOURCE = ..\..\Source
ZLIB = $(SOURCE)\zlib131

SOURCES = $(SOURCE)\gzip\minigzip.c \
          $(ZLIB)\adler32.c $(ZLIB)\crc32.c $(ZLIB)\deflate.c \
          $(ZLIB)\gzclose.c $(ZLIB)\gzlib.c $(ZLIB)\gzread.c $(ZLIB)\gzwrite.c \
          $(ZLIB)\inffast.c $(ZLIB)\inflate.c $(ZLIB)\inftrees.c \
          $(ZLIB)\trees.c $(ZLIB)\zutil.c

HEADERS = $(ZLIB)\crc32.h $(ZLIB)\deflate.h $(ZLIB)\gzguts.h \
          $(ZLIB)\inffast.h $(ZLIB)\inffixed.h $(ZLIB)\inflate.h \
          $(ZLIB)\inftrees.h $(ZLIB)\trees.h $(ZLIB)\zconf.h \
          $(ZLIB)\zlib.h $(ZLIB)\zutil.h

gzip.exe: Makefile $(SOURCES) $(HEADERS)
		cl /nologo /O2 /MT /D_CRT_SECURE_NO_WARNINGS /I"$(ZLIB)" /Fe:$@ $(SOURCES)
