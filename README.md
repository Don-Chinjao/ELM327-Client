OBD-II Diagnostic Tool

Low-level OBD-II diagnostic tool written in C, communicating with vehicle ECUs through an ELM327 adapter over a raw serial interface.

Features

- Linux TTY / POSIX "termios" serial communication
- ELM327 AT command interface
- OBD-II request/response handling
- Raw hexadecimal response inspection
- Basic PID parsing and decoding
- Timeout and buffered stream handling

Currently supports basic read-only diagnostics such as:

```text
010C  → Engine RPM
010D  → Vehicle speed
0100  → Supported PIDs
```

## Architecture

```text
CLI
 ↓
OBD-II parser
 ↓
ELM327 interface
 ↓
POSIX TTY
 ↓
ELM327 → Vehicle ECU
```

The project is developed as a learning platform for low-level communication, protocol parsing, OBD-II and CAN diagnostics.

Roadmap

- [x] ELM327 communication
- [x] AT command handling
- [x] Basic OBD-II requests
- [x] Response buffering and parsing
- [ ] Generic PID decoder
- [ ] CLI interface
- [ ] ISO-TP / UDS exploration
- [ ] Direct CAN communication
- [ ] MCU-based diagnostic hardware
