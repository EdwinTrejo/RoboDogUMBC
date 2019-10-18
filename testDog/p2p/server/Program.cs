using System;
using System.Collections.Generic;
using System.Linq;
using System.Net;
using System.Net.Sockets;
using System.Text;
using System.Threading;
using System.Threading.Tasks;
using Newtonsoft.Json;

namespace server {
    class Program {
        const int listenPort = 9701;
        const string localhost = "127.0.0.1";
        ///<Summary>
        /// starts the listener
        ///</Summary>
        private static void startServer () {
            UdpClient listener = new UdpClient (listenPort);
            IPEndPoint groupEP = new IPEndPoint (IPAddress.Any, listenPort);
            while (true) {
                Console.WriteLine ("Waiting for broadcast");
                byte[] bytes = listener.Receive (ref groupEP);
                string deserialize = Encoding.ASCII.GetString(bytes, 0, bytes.Length);
                directions request = JsonConvert.DeserializeObject<directions>(deserialize);

                Console.WriteLine ($"Received broadcast from {groupEP} :");
                // Console.WriteLine ($" {Encoding.ASCII.GetString(bytes, 0, bytes.Length)}");
                Console.WriteLine ($"{request.x}\t{request.y}\n");
            }
        }

        static void Main (string[] args) {
            Console.WriteLine ("Starting Server!");
            startServer ();
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