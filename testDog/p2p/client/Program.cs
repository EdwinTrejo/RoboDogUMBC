using System;
using System.Collections.Generic;
using System.Linq;
using System.Net;
using System.Net.Sockets;
using System.Text;
using System.Threading;
using System.Threading.Tasks;
using Newtonsoft.Json;

namespace client {
    class Program {
        const int sendport = 9701;
        const string localhost = "127.0.0.1";
        const string server = "192.168.1.36";

        static void Main (string[] args) {
            sendMessage ();
        }

        static void sendMessage () {
            UdpClient udpClient = new UdpClient (sendport);
            udpClient.Connect (server, sendport);
            directions moveForward = new directions (10, 10);
            string serializedData = JsonConvert.SerializeObject(moveForward);

            while (true) {
                try {
                    Byte[] sendBytes = Encoding.ASCII.GetBytes(serializedData);
                    udpClient.Send (sendBytes, sendBytes.Length);

                } catch (Exception e) {
                    Console.WriteLine (e.ToString ());
                }
                Thread.Sleep (1000);
            }
            udpClient.Close ();
        }
    }

    public class directions {
        public int x;
        public int y;
        public directions (int _x, int _y) {
            x = _x;
            y = _y;
        }
    }
}