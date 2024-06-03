using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading;
using System.Threading.Tasks;

namespace mySpace
{
    internal class Refresher
    {
        private Thread backgroundThread;
        private ManualResetEvent resetEvent = new ManualResetEvent(false);
        private bool running = true;


        public Refresher()
        {
            backgroundThread = new Thread(Run);
            backgroundThread.IsBackground = true;
            backgroundThread.Start();
        }

        public void Run()
        {
            while (running)
            {
                resetEvent.WaitOne(); // Wait until signaled

                

                // Sleep for a short duration to prevent high CPU usage
                Thread.Sleep(100);
            }
        }

        public void Start()
        {
            resetEvent.Set(); // Signal the thread to start work
        }

        public void Stop()
        {
            resetEvent.Reset(); // Signal the thread to stop work
        }

        public void Terminate()
        {
            running = false; // Signal the thread to terminate
            resetEvent.Set(); // Ensure the thread wakes up to terminate
        }

        private void RefreshUsersList(System.Windows.Forms.ListBox usersList)
        {
            /*// Lock shared resources
            lock (*//* lock object for socket/stream *//*)
            {
                // Refresh logic that involves socket/stream
            }

            lock (*//* lock object for GUI component *//*)
            {
                // GUI refresh logic
            }

            // Perform any other tasks needed to refresh the windows*/
    }
}
}
