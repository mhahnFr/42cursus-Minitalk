# Welcome to 42cursus-Minitalk!
This repository contains an project of the [42 school]. The exercise is to
write a small server and client application, which should be capable to send a
string from the client to the server, using only UNIX signals.

## Approach
My approach is pretty straight forward: once the server received a signal, the
associated bit is stored and a signal is sent back to the client. The signal
handler of the client sends then the next bit of the input string.

### Final notes
This repository showcases my solutions of this exercise.

© 2021 [mhahnFr](https://www.github.com/mhahnFr)

[42 school]: https://www.42heilbronn.de/learncoderepeat
