# memtrace-interposer

On a Linux machine, build it and `LD_PRELOAD` it before your command.

```shell
$ cd ~/memtrace-interposer
$ make
$ cd ~/xlsynth
$ LD_PRELOAD=$HOME/memtrace-interposer/memtrace.so bazel-bin/xls/dslx/interpreter_main xls/dslx/stdlib/apfloat.x 
$ python3 $HOME/memtrace-interposer/plot.py
```
