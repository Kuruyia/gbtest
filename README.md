# gbtest

[![CMake](https://github.com/Kuruyia/gbtest/actions/workflows/cmake.yml/badge.svg?branch=master)](https://github.com/Kuruyia/gbtest/actions/workflows/cmake.yml)  
A test GameBoy emulator written in C++ made for learning the inner workings of this console.

## What's working?

- [x] Bus
- [x] CPU
- [x] PPU (FIFO-based renderer)

## Test ROMs

- [dmg-acid2](https://github.com/mattcurrie/dmg-acid2) – Passes

## Acknowledgments

### Documentation

#### General

- [The Pandocs](https://gbdev.io/pandocs/) – A complete documentation about the GameBoy hardware
- [The Ultimate Game Boy Talk (33c3)](https://youtu.be/HyzD8pNlpwI) – Michael Steil's lecture about the GameBoy at 33c3
- [The Cycle-Accurate Game Boy Docs](https://github.com/AntonioND/giibiiadvance/blob/master/docs/TCAGBD.pdf) – Another
  documentation about the GameBoy hardware, with an emphasis on cycle accuracy
- [Game Boy: Complete Technical Reference](https://gekkio.fi/files/gb-docs/gbctr.pdf) – Another documentation about the
  GameBoy hardware

#### CPU

- [gbdev's optables](https://gbdev.io/gb-opcodes/optables/) – Matrix representing every CPU instruction
- [gbz80](https://rgbds.gbdev.io/docs/v0.5.1/gbz80.7) – A document describing each CPU instruction

#### PPU

- [hacktixme.ga/GBEDG/ppu](https://hacktixme.ga/GBEDG/ppu/) – Nicely written document about how the PPU works

#### APU

- [GbdevWiki - Gameboy sound hardware](https://gbdev.gg8.se/wiki/articles/Gameboy_sound_hardware) – More detailed page
  about the sound hardware
- [Nintendo(TM) Gameboy sound system (PAPU) guide - GBSOUND.txt](http://www.devrs.com/gb/files/hosted/GBSOUND.txt) –
  Another great document about the sound hardware
- [dspguide - The Fourier Series](https://www.dspguide.com/ch13/4.htm) – Fourier series equations for a bunch of
  waveforms

### Libraries

- [Raylib](https://www.raylib.com) – for the cross-platform video/input front-end
- [miniaudio](https://miniaud.io/) – for the cross-platform audio front-end
