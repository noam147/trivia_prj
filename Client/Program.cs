//using ConsoleApp1Check;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace clientGuiTrivia
{
    internal static class Program
    {
       
        /// <summary>
        /// The main entry point for the application.
        /// </summary>
        [STAThread]
        
        static void Main()
        {

            ClientHandler clientHandler = new ClientHandler();
            
            while (!clientHandler.connectServer())
            {

            }
            clientHandler.receiveMsg();

            Application.EnableVisualStyles();
            Application.SetCompatibleTextRenderingDefault(false);
            var main = new MainScreen(clientHandler);
            main.FormClosed += new FormClosedEventHandler(FormClosed);
            main.Show();
           
            Application.Run();
            clientHandler.closeConnection();
            //Application.Run(new LoadingScreenPage(ref clientHandler));

            
        }

        static void FormClosed(object sender, FormClosedEventArgs e)
        {
            ((Form)sender).FormClosed -= FormClosed;
            if (Application.OpenForms.Count == 0) Application.ExitThread();
            else Application.OpenForms[0].FormClosed += FormClosed;
        }
    }
}