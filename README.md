# exec-time-record

C++17 library for measuring how long a block of code takes to run.

Wrap a callable with `etr::Chronometer`, and read the elapsed time as a
`timeUtils::Timestamp` (hours, minutes, seconds, milliseconds) via
`etr::ChronoResult`.

## Requirements

- CMake 3.24+
- A C++17 compiler
- [Ninja](https://ninja-build.org/) or Make
- `jq` (used by `compile.sh`)
- [Doxygen](https://www.doxygen.nl/) (optional, for API docs)

Vendored dependency: [cpp-time-utils](vendor/cpp-time-utils) (stopwatch / sleep).

## Build

```bash
./compile.sh setup    # configure (Debug); add ndev for Release
./compile.sh          # build
./run.sh              # demo: printf() vs write() timing
```

Artifacts land under `build/bin/` and `build/lib/`.

## Usage

```cpp
#include "exec_time_record/chronometer.hpp"

etr::ChronoResult result{};
etr::Chronometer chrono(&result /*, startDelaySec, endLimitSec */);

chrono.run([]() {
    // code to measure
});

etr::ChronoResult done = chrono.exit();
// done.timestampTotal.{hour,min,sec,ms}
```

| Member / method | Role |
| --- | --- |
| `startDelay` | Seconds to wait before timing starts (constructor arg). |
| `end` | Max measured seconds; values `< 0` mean no limit. |
| `run(func)` | Time `func` until it returns (or until `end`). |
| `stop()` / `exit()` | Finalize and copy the stopwatch into `ChronoResult`. |
| `getState()` / `isFinished()` | Query lifecycle state. |

Link against the static library target `exec_time_record` (alias
`exec_time_record::exec_time_record`) and include headers from `inc/`.

## Documentation

API comments are written for Doxygen. Generate HTML docs:

```bash
doxygen Doxygen
```

Output is written to `docs/` (gitignored). Open `docs/html/index.html`.

This README is also used as the Doxygen main page (`USE_MDFILE_AS_MAINPAGE`).

## License

GNU General Public License v3.0 — see [LICENSE.txt](LICENSE.txt).
