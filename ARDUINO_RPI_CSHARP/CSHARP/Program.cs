using System;
using System.Net;
using System.Net.Http;
using System.Threading;
using System.Threading.Tasks;

namespace CSHARP
{
    class Program
    {
        #region consts
        const string localhost = "127.0.0.1";
        const string server = "http://192.168.4.1:5000";
        #endregion

        static void Main(string[] args)
        {
            int actionID = 0;
            bool messageSendReady = false;
            Task.Run(() =>
            {
                // actionID = 1;
                //tasks here
                while (true)
                {
                    //gets a valid keycode and returns to regular program
                    var keyPress = Console.ReadKey().Key;
                    // Console.Clear();
                    //move up
                    if (keyPress == ConsoleKey.W) { actionID = 1; messageSendReady = true; Console.WriteLine($"\n up {actionID}"); }
                    //move down
                    else if (keyPress == ConsoleKey.S) { actionID = 2; messageSendReady = true; Console.WriteLine($"\n down {actionID}"); }
                    //move left
                    else if (keyPress == ConsoleKey.A) { actionID = 3; messageSendReady = true; Console.WriteLine($"\n left {actionID}"); }
                    //move right
                    else if (keyPress == ConsoleKey.D) { actionID = 4; messageSendReady = true; Console.WriteLine($"\n right {actionID}"); }

                    // if(actionID == 1) {
                    //     actionID = 3;
                    // } else {
                    //     actionID = 1;
                    // }
                    // Console.WriteLine(actionID);
                    // messageSendReady = true;
                    // Thread.Sleep(500);
                }
            });
            while (true)
            {
                if (messageSendReady) { sendMessage(actionID); messageSendReady = false; }
                Thread.Sleep(10); //in milliseconds //10 ms is safe
            }
        }

        static void sendMessage(int count)
        {
            using (var client = new HttpClient(new HttpClientHandler { AutomaticDecompression = DecompressionMethods.GZip | DecompressionMethods.Deflate }))
            {
                client.BaseAddress = new Uri(server);
                //HttpResponseMessage response = client.GetAsync($"/").Result; //reset serial connections from rpi to arduino
                HttpResponseMessage response = client.GetAsync($"/change/{count}").Result;
                response.EnsureSuccessStatusCode();
                string result = response.Content.ReadAsStringAsync().Result;
                //Console.WriteLine("Result: " + result);
            }
        }
    }
}
