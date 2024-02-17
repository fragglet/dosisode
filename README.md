This repository contains Peter Kay's DOS port of the [ISO Development
Environment](https://en.wikipedia.org/wiki/ISO_Development_Environment).
The port is notable in that it contains a TSR version of the WATTCP
stack that exposes an (incomplete) version of the BSD sockets API. This
allows programs to use WATTCP without having to compile it in as a
library.

The API for the TSR is hooked on interrupt 17h; [the Ralf Brown
Interrupt List](https://www.ctyme.com/intr/int-17.htm) has details of
it (or just look at the source code). The C client library for using
the TSR [is found here](isode8.wrk/unix/lib/socket.c), but Berczi
Gabor also created [a Pascal library](https://github.com/fragglet/gabor/blob/trunk/freesock/watsocks.pas)
for it.

