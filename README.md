
# vesper-libs

Copyright (c) 2014, Max Mertens, Simon Michalke.
All rights reserved.

## Modules

`vesper-libs` is a collection of useful common software modules:

### vesper-log

`vesper-log` provides buffered and prefixed logging outputs to console.

### vesper-sphtp

`vesper-sphtp` provides an implementation of the [SphTP protocol][sphtp_link]
and lets you build simulation servers and clients connected over network.

[sphtp_link]: https://github.com/jellysheep/spheresim/wiki/Protocol

### vesper-test

`vesper-test` is a small unit test checking functionality of C modules.

### vesper-error

`vesper-error` is a helper module providing small functions for error numbers
and names (like standard `errno` and `strerror()`).

### vesper-util

`vesper-util` is a helper module providing a header file with symbol export
markers.

## License

vesper-libs is released under the BSD 3-Clause License.
Please refer to [`LICENSE`](LICENSE) file for details.
