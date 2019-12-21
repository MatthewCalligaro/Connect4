# Connect4
An efficient implementation of Connect 4 with several agents.

Repository link: https://github.com/MatthewCalligaro/Connect4

## Documentation
To generate complete documentation for this project, run `make doxygen` from the root directory of this project.  If this fails, you may first need to install doxygen with `apt-get`.  You can then find the project's documentation in `documentation/html/index.html`.

## Compilation
To compile the command line executable, run `make` from the root directory of this project.  You can then execute the program with `./c4`.

## Usage
`Usage: ./c4 [-t <test type>] [-n <number of trials>] [-d <depth>] [-v] [-h]`

### Options
* `-t`: test type (single, time, win, winTrain, depth)
* `-n`: number of trials (positive integer number)
* `-d`: depth for minimax agents (positive integer number)
* `-v`: verbose
* `-h`: show this help message