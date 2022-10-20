---
title: microPython mpy-cross binary encoding
tags: [microPython/mpy-cross]
---

## dependencies install

- install by `pip install mpy-cross` in a common Python pip
```text
(base) PS D:\Projects\DengHuiP\micropython\pirani_ESP32> mpy-cross --help
usage: C:\Users\zekun\anaconda3\lib\site-packages\mpy_cross\mpy-cross.exe [<opts>] [-X <implopt>] <input filename>
Options:
--version : show version information
-o : output file for compiled bytecode (defaults to input with .mpy extension)
-s : source filename to embed in the compiled bytecode (defaults to input file)
-v : verbose (trace various operations); can be multiple
-O[N] : apply bytecode optimizations of level N

Target specific options:
-msmall-int-bits=number : set the maximum bits used to encode a small-int
-march=<arch> : set architecture for native emitter; x86, x64, armv6, armv6m, armv7m, armv7em, armv7emsp, armv7emdp, xtensa, xtensawin

Implementation specific options:
  emit={bytecode,native,viper} -- set the default code emitter
  heapsize=<n> -- set the heap size for the GC (default 2097152)
```

- check the mpy version and and native architecture
```Python
import sys
  

def main():
    sys_mpy = sys.implementation._mpy
    # 10246 = b0010,1000,0000,0110
    # first 8 digits: mpy version
    # next 2 digits: mpy features
    # next 4 digits: mpy native architecture
    arch = [None, 'x86', 'x64',
        'armv6', 'armv6m', 'armv7m', 'armv7em', 'armv7emsp', 'armv7emdp',
        'xtensa', 'xtensawin'][sys_mpy >> 10]  # = b1010 = 10
    print('mpy version:', sys_mpy & 0xff)  # 6 for my ESP32 Devkit-C v4
    print('mpy flags:', end='')  # -march=xtensawin -mno-unicode
    if arch:
        print(' -march=' + arch, end='')
    if sys_mpy & 0x100:
        print(' -mcache-lookup-bc', end='')
    if not sys_mpy & 0x200:
        print(' -mno-unicode', end='')
    print()
  
if __name__ == "__main__":
    main()
```







## tutorials


