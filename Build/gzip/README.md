# Building minigzip on Windows

With Intel oneAPI and Visual Studio C++ build tools installed, run
`Build\gzip\intel_win\make_gzip.bat` from the repository root. The script
sets up oneAPI if needed and keeps it available for later builds in the same
Command Prompt. From an initialized oneAPI prompt, you can also
run `nmake /f ..\Makefile intel_win` in `Build\gzip\intel_win`.
The build uses Intel `icx`, the
bundled zlib sources, and the static C runtime. It writes `gzip_win.exe` and the
`.obj` files to `Build\gzip\intel_win`.

For a Clang build, run `Build\gzip\clang_win\make_gzip.bat` from the
repository root, or run `nmake /f ..\Makefile clang_win` from
`Build\gzip\clang_win` in a Visual Studio Developer Command Prompt with
`clang-cl` on PATH. This writes `gzip_win.exe` and the object files to
`Build\gzip\clang_win`.

From Command Prompt, use `-c` and redirect stdout to keep the input file:

```bat
gzip_win.exe -c file.xyz > file.xyz.gz
gzip_win.exe -d -c file.xyz.gz > restored.xyz
```

With a filename and no `-c`, minigzip removes the input after a successful
conversion. Use the system `gzip` command on Linux and macOS.
