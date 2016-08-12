using System;
using System.IO.Ports;
using System.Threading;

namespace SerialComm
{
    public class MainLoopHandler
    {
        private readonly string portName;
        private readonly int baudRate;
        private readonly Action<string> onPackageComplete;

        public MainLoopHandler(string portName, int baudRate, Action<string> onPackageComplete)
        {
            this.portName = portName;
            this.baudRate = baudRate;
            this.onPackageComplete = onPackageComplete;
        }

        public void Execute()
        {
            JsonBuffer buffer = new JsonBuffer();
            DateTime timeoutTime = DateTime.Now.AddSeconds(2);
            using (SerialPort arduinoPort = new SerialPort(portName, baudRate, Parity.Mark))
            {
                arduinoPort.Open();
                while (!Console.KeyAvailable)
                {
                    string indata = arduinoPort.ReadExisting();

                    if (!string.IsNullOrWhiteSpace(indata))
                    {
                        foreach (char character in indata)
                        {
                            if (buffer.AddChar(character))
                            {
                                onPackageComplete(indata);
                                timeoutTime = DateTime.Now.AddSeconds(2);
                            }
                        }
                    }
                    if (timeoutTime < DateTime.Now)
                    {
                        buffer.ResetBuffer();
                    }

                    Thread.Sleep(100);
                }
            }
        }
        
    }
}