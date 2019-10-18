A simple peer to peer network

to be use with the robot for low power wireless
communications. This test uses UDP connections.
The test also depends on newtonsoft Json to 
serialize and deserialize data to increase the efficiency 
of data transfers and reduce parsing on the listener side.

# make a project with dotnet core
* make a folder with the name of your project
* dotnet new console
* dotnet add package Newtonsoft.Json --version 12.0.2


# references
* https://www.newtonsoft.com/json/help/html/SerializationAttributes.htm
* https://www.nuget.org/packages/Newtonsoft.Json/
* https://docs.microsoft.com/en-us/dotnet/api/system.net.sockets.udpclient?view=netframework-4.8
* https://docs.microsoft.com/en-us/dotnet/framework/network-programming/using-udp-services
