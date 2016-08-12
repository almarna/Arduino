using System;
using System.Collections.Generic;
using System.Linq;
using System.Threading.Tasks;

namespace SerialComm
{
    class Program
    {
        static void Main(string[] args)
        {
            Console.Clear();
            JsonDataHandler jsonDataHandler = new JsonDataHandler();
            MainLoopHandler handler = new MainLoopHandler("COM11", 38400, jsonDataHandler.Execute);
            handler.Execute();
        }

    }
}
;