# Random Semantic Versioning Tags

I wrote this to test some tools, and I needed a random set of [semantic versions](https://semver.org/).

This was written for macOS, using the clang C compiler. It should also
work with Linux, or any other UNIX-like operating system with a fairly
modern C compiler.

Note that this relies on the `arc4random_uniform()` function, that
generates a pseudo-random number evenly distributed across a range.

# Usage

Usage: `./rv [ -d ] [ -h ] [ -r ] <number of versions>`

Arguments:

- `-h`  This option prints the help summary.
- `-d`  This option turns on debug output to stderr.
- `-r`  This option randomizes the output, in case you need or want to
        test sorting the semantic versions correctly.

# Notes

Note that this program assumes you have a color terminal, and uses
ASCII color codes in some cases.

I also know that this could have been written in some other language,
but I used C in order to easily leverage the
[arc4random_uniform()](https://www.freebsd.org/cgi/man.cgi?query=arc4random_uniform&sektion=3&manpath=freebsd-release-ports)
function, as implemented in macOS.

# License

This is licensed under the [MIT license](https://opensource.org/licenses/MIT). If you find it useful, great!



*(C) Copyright 2020 Michael A. Jarvis*