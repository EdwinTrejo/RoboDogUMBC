This is main readme for the full program

This project is a series of programs that run on each platform which allows you 
to communicate from a regular computer running microsft dotnet core to operate an arduino. For this project 
I modified the Raspberry pi to run in Ad Hoc mode. The Raspberry Pi is the central part of this project it allows for communication from 
a central python REST server using flask. The computer simply runs a simple asynchronous program to detect keystrokes and send a get request to
the Flask server. The Raspberry Pi now receives the value and serializes the value incoming from the rest API and uses /dev/serial0 to send the data 
to the arduino. The Arduino now deserializes the integer and takes an action based on the actionID received. 
