
# vesper-libs

Copyright (c) 2014, Max Mertens, Simon Michalke.
All rights reserved.

## Modules

`vesper-libs` is a collection of useful common software modules:

### vesper-log

`vesper-log` provides buffered and prefixed logging outputs to console.

### vesper-cmcp

`vesper-cmcp` provides an implementation of the [CMCP protocol][cmcp_link]
and lets you build connected servers and clients, e.g. for physical simulations
over a network.

[cmcp_link]: https://github.com/jellysheep/spheresim/wiki/Protocol

### vesper-test

`vesper-test` is a small unit test checking functionality of C modules.

### vesper-util

`vesper-util` is a helper module providing header files with symbol export
markers and small functions for error numbers and names (like standard
`errno` and `strerror()`).

## Coding style

See [`CODING_STYLE.md`](CODING_STYLE.md) file for details about coding style of
this project.

## License

vesper-libs is released under the BSD 3-Clause License.
Please refer to [`LICENSE`][license_link] file for details.

[license_link]:
https://github.com/VesperCommunity/vesper-libs/blob/master/LICENSE
