*Ein Gelehrter in seinem Laboratorium ist nicht nur ein Techniker; er steht auch vor den Naturgesetzen wie ein Kind vor der Märchenwelt. - Marie Curie*

# gpOskar

This program constructs a gnuplot program call from individual voltage measurements, which has been optimized for inclusion in documents. The plot thus represents a snapshot of a digital oscilloscope screen and
the program calculates the optimal axis scaling in t-y mode and the default configuration file for gnuplot can easily be extended to perform measurement interpolation, signal analysis, or anything else.<br><br>

Currently two channels are supported in one graphic.


![example oscillogram](docs/example_oscillogram.png)

![example terminal output](docs/example_terminal_output.png)


##  Build

The project can be built by using `make`.<br>
You need a working gnuplot installation with version >=5.0<br>

## Usage 
You need raw data from your oscilloscope in the following form:<br>
#header<br>
Voltage value in volts<br>
Voltage value in volts<br>
...<br>
#header<br>
Voltage value in volts<br>
...

The header contains the channel and the time resolution in seconds as e-notation in the form: #CHX, time resolution.<br>
Example:<br>
#CH1,2e-08<br>
1.42279<br>
1.5<br>
1.57965<br>
...

The raw data should be stored as ASCII text and the basic gnuplot config file is in /src

## Licence

This program by Michael Krause is licensed under the terms of the [GPLv3](https://www.gnu.org/licenses/gpl-3.0.de.html).<br>
Please note that gnuplot is an independent software that is not from the gpOskar author. gnuplot has its own licensing terms.

## Thanks to:

Jeremy Heighway for mentoring English grammar and spelling.