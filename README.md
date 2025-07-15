# Mobo MIDI Player

Play midi files on your motherboard beeper! (if you have one)

Only works on linux

## Compiling

```sh
mkdir build
cd build
cmake .. -GNinja -DCMAKE_EXPORT_COMPILE_COMMANDS=ON
cmake --build . -j
```

## Running

```sh
sudo ./mobomidiplayer "../midi/night of nights.mid"
```
