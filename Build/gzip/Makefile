CC = icx
SOURCE = ..\..\..\Source
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

OBJECTS = minigzip.obj adler32.obj crc32.obj deflate.obj \
          gzclose.obj gzlib.obj gzread.obj gzwrite.obj \
          inffast.obj inflate.obj inftrees.obj trees.obj zutil.obj

gzip.exe: ..\Makefile $(SOURCES) $(HEADERS)
	$(CC) /nologo /c /O2 /MT /D_CRT_SECURE_NO_WARNINGS /D_CRT_NONSTDC_NO_WARNINGS /I"$(ZLIB)" $(SOURCES)
	$(CC) /nologo /MT /Fe:$@ $(OBJECTS)

clang_win:
	$(MAKE) /nologo /a /f ..\Makefile CC=clang-cl gzip.exe
