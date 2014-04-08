# blinky-tape-test-status

Blinky Tape sketch for high-performance TDD/BDD notifications

## Install

  1. Install [Arduino 1.0.5](http://arduino.cc/en/Main/Software)
  2. Install [ino](https://pypi.python.org/pypi/ino/)
  3. make upload

## Test It

    ino serial


## Commands

    r : Red
    b : Blue
    g : Green
    y : Yellow
    w : White
    f : Flash current color quickly
    p : Pulse current color slowly
    s : Solid
    t : Test Pattern
    x : Rainbow Pattern
    c : Cop Lights
    i : One-shot progress bar
    0 - 9 : Brightness (0-100%)


## Development Setup

In order to run tests, you'll need cppunit. On Debian based systems:

    sudo apt-get install libcppunit-dev

### Running Tests

    make test

### Build, Test and Upload

    make all

