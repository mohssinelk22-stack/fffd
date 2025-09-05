
# 42 Philosophers (mandatory)

Minimal implementation following 42 constraints:
- Only uses: `write`, `malloc`, `free`, `usleep`, `gettimeofday`, `pthread_*`
- No `for` loops; only `while`.
- Logs via `write` helpers (no `printf`).
- Deadlock-avoidance by alternating fork order per philosopher (even picks right first).
- Death monitoring thread checks frequently; simulation stops on death or when all ate `must_eat` times.

## Build
```bash
make
```

## Run
```bash
./philo number_of_philosophers time_to_die time_to_eat time_to_sleep [must_eat]
# Example
./philo 5 800 200 200 7
```

## Notes
- Handles the single philosopher edge case.
- Avoids printing after stop, except the final "died" line.
- Uses small functions to be norm-friendly.
