# Building minigzip on Windows

From a Visual Studio Developer Command Prompt, run
`Build\gzip\make_minigzip.bat` from the repository root, or run `nmake /f Makefile` from `Build\gzip`. The build produces
`Build\gzip\gzip.exe` with the bundled zlib sources and the static MSVC
runtime.

From Command Prompt, use `-c` and redirect stdout to keep the input file:

```bat
gzip.exe -c file.xyz > file.xyz.gz
gzip.exe -d -c file.xyz.gz > restored.xyz
```

With a filename and no `-c`, minigzip removes the input after a successful
conversion. Use the system `gzip` command on Linux and macOS.
