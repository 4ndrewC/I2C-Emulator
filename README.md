# I2C-Emulator

This is kind of trash, just learning about the protocol, hopefully it becomes a useful emulation tool eventually

Todo list:

- Master
  - Struct
- Slave
  - Start/End condition
  - ACK bit
  - Struct
  - Reset x (not tested)
  - Check address x
  - Parse bitstream x
- I2C
  - Read x
  - Write x
  - SCL (in master.c) x
  - SDA (in master.c) x
  - Simulate continuous SDA line with periodic/non-periodic bitstreams sent
- Converting bitstream char[] to byte[] and reverse x
