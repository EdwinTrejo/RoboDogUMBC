how to perform correct calls
this library uses the following libraries

none

you should know how to install the dotnetcore enviroment on your system as it is    
available on linux and windows. The base libraries include all needed to run.

How to run from console/terminal:

1. The RPI software requires install of different python components

	a. Flask
	
	b. python serial

install them through python pip install

2. using the software is rather easy
	
	sudo chmod a+rw /dev/serial0 && python3 fl-app.py

just run that command, we need rights to use serial0 and the second part is just running the application on python3
