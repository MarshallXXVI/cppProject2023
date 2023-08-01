# cppProject2023

## Installation
To compile :# cppProject2023
RUN following command.

```bash 
~make
```

## Solver
To run binary solverMain :

```bash
~make solver
```
This will run ./solverMain a.options a.constraints a.models

After generated a.models now can modify every files to test if Checker work as intended.
Example try to configure a.options or a.constraints to invalid input file.

## Checker
To run the binary checkerMain :

```bash
~make checker
```
This will run ./checkerMain a.options a.constraints a.models
