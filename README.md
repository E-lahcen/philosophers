# Philosophers Project

## Summary
This project explores process threading, focusing on thread creation and the use of mutexes. You will simulate the dining philosophers problem, a classic synchronization challenge, and ensure proper handling of shared resources to avoid issues like race conditions and deadlocks.

## Requirements

### General Guidelines
- **Language**: C.
- Follow the **42 Norm** guidelines.
- Handle errors like segmentation faults, double free, etc., to ensure a functional project.
- Free all allocated memory (no memory leaks allowed).
- Use a `Makefile` to compile your project with the following rules:
  - `$(NAME)`, `all`, `clean`, `fclean`, and `re`.
- Bonus features must be in separate files and compiled using the `bonus` rule.
- Tests are encouraged but will not be submitted.

## Project Structure
philo/ ├── Makefile ├── philo/ │ ├── *.c │ ├── *.h └── philo_bonus/ ├── *.c ├── *.h


## Mandatory Part

### Program Details
- **Name**: `philo`
- **Files**: `Makefile`, `*.h`, `*.c`
- **Arguments**:
number_of_philosophers time_to_die time_to_eat time_to_sleep [number_of_times_each_philosopher_must_eat]

- **External Functions**:
- `memset`, `printf`, `malloc`, `free`, `write`, `usleep`, `gettimeofday`
- `pthread_create`, `pthread_detach`, `pthread_join`
- `pthread_mutex_init`, `pthread_mutex_destroy`, `pthread_mutex_lock`, `pthread_mutex_unlock`
- **Description**: Simulate philosophers with threads and mutexes.

### Rules
- Each philosopher is a thread.
- There is one fork between each pair of philosophers.
- Use mutexes to protect shared resources (forks).
- Display logs for state changes:
timestamp_in_ms X has taken a fork timestamp_in_ms X is eating timestamp_in_ms X is sleeping timestamp_in_ms X is thinking timestamp_in_ms X died

- Ensure no data races occur.
- Philosophers must avoid starvation.

## Bonus Part

### Program Details
- **Name**: `philo_bonus`
- **Files**: `Makefile`, `*.h`, `*.c`
- **Arguments**:

number_of_philosophers time_to_die time_to_eat time_to_sleep [number_of_times_each_philosopher_must_eat]


- **External Functions**:
- `memset`, `printf`, `malloc`, `free`, `write`, `fork`, `kill`, `exit`
- `pthread_create`, `pthread_detach`, `pthread_join`, `usleep`, `gettimeofday`
- `waitpid`, `sem_open`, `sem_close`, `sem_post`, `sem_wait`, `sem_unlink`
- **Description**: Simulate philosophers using processes and semaphores.

### Rules
- Forks are represented as a semaphore.
- Each philosopher is a separate process, managed by a parent process.
- Same logging requirements as the mandatory part.

### Important:
- Bonus features will only be evaluated if the mandatory part is perfect (all requirements met and functional).

## How to Compile and Run

### Mandatory Part
```bash
cd philo
make
./philo <number_of_philosophers> <time_to_die> <time_to_eat> <time_to_sleep> [number_of_times_each_philosopher_must_eat]

