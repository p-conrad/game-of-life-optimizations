# Optimized Conway's Game of Life

This is a simple program to simulate [Conway's Game of Life](https://en.wikipedia.org/wiki/Conway%27s_Game_of_Life) with
the default 23/3 ruleset. It has been developed as an algorithm engineering project implementing many optimizations from
[Michael Abrash's Graphics Programming Black Book](http://www.jagregory.com/abrash-black-book/#chapter-17-the-game-of-life).
Both graphics output and benchmarking the algorithm on custom patterns are supported. Patterns may be provided in the
[RLE format](https://www.conwaylife.com/wiki/Run_Length_Encoded).

## Usage

Run the program from the command line:
```
$ ./game-of-life [parameters]
```

The following parameters are available:

* `-i`, `--infile`: The pattern file to use. This parameter is required.
  Some standard patterns are available in the _patterns_ directory.
* `-f`, `--fieldsize`: The size of the field in _WxH_ format. If not provided, a size of 500x500 will be used.
* `-w`, `--winsize`: The size of the window in _WxH_ format. Should be greater than or equal to the field dimensions
  (multiples work best). The game will try to scale the field to fit the window as good as possible. If not provided,
  the field size will be used.
* `-b`, `--benchmark`: Do a benchmark of the algorithm. This will disable graphics output to maximize speed. A CSV file
  containing the results will be generated. Be sure to also specify the `-g` and `-l` parameters below.
* `-g`, `--generations`: How many generations to run. Currently only works for benchmarking. If not provided, a default
  value of 30000 will be used.
* `-l`, `--logfrequency`: How many generations to average the benchmark measurements over. A value of N means the next
  generation is calculated N times, logging the average run time over those N iterations.
  For N=1, the run time for each generation will be stored explicitly.
  If not provided, a default value of 50 will be used.
