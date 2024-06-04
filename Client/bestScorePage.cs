using JsonDeserialzierHelper;
using JsonSerialzierHelper;
using Newtonsoft.Json.Linq;
using System;
using System.Collections.Generic;
using System.Threading;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace clientGuiTrivia
{
    public partial class bestScorePage : Form
    {
        private string username;
        private ClientHandler clientHandler;

        private CancellationTokenSource cts = new CancellationTokenSource(); // Used for cancelling task
        private static readonly object lockSocket = new object();
        private Task task = null;

        public bestScorePage(string user, ClientHandler clientHandler)
        {
            this.clientHandler = clientHandler;
            username = user;
            InitializeComponent();

            // Attach the FormClosing event handler
            this.FormClosing += bestScoresPage_FormClosing;

            // Start the task
            this.task = Task.Run(() => RefreshScores(cts.Token));
        }

        private async Task RefreshScores(CancellationToken token)
        {
            try
            {
                getHighScoreMessageFields getHighScore = new getHighScoreMessageFields
                {
                    username = username
                };
                string msgToSend = Serializer.serialize(getHighScore);
                string msgReceive;
                List<Dictionary<string, string>> users;

                Label[] labels = { label1, label2, label3, label4, label5 };

                while (!token.IsCancellationRequested)
                {
                    Console.WriteLine("Task running...");

                    lock (lockSocket)
                    {
                        clientHandler.sendMsg(msgToSend);
                        msgReceive = clientHandler.receiveMsg();
                    }
                    users = Deserializer.desirializeGetHighscoreResponse(msgReceive);

                    // Update the labels on the UI thread
                    if (labels != null && users != null && !this.IsDisposed && this.IsHandleCreated)
                    {
                        this.Invoke(new Action(() =>
                        {
                            if (!this.IsDisposed && this.IsHandleCreated)
                            {
                                for (int i = 0; i < users.Count; i++)
                                {
                                    foreach (var kvp in users[i])
                                    {
                                        if (i < labels.Length)
                                        {
                                            labels[i].Text = "The player: " + kvp.Key + " scored: " + kvp.Value;
                                            Console.WriteLine($"Key: {kvp.Key}, Value: {kvp.Value}");
                                        }
                                    }
                                }
                            }
                        }));
                    }

                    await Task.Delay(1000, token);
                }
            }
            catch (TaskCanceledException)
            {
                Console.WriteLine("Task was canceled.");
            }
            catch (Exception ex)
            {
                Console.WriteLine($"Unexpected error: {ex.Message}");
            }
        }

        private void button1_Click(object sender, EventArgs e)
        {
            loggedUserPage frm = new loggedUserPage(this.username, clientHandler);
            frm.Show();
            this.Close();
        }

        private void bestScoresPage_FormClosing(object sender, FormClosingEventArgs e)
        {
            cts.Cancel();

            // Optionally, wait for the task to complete without blocking the UI thread
            // Note: Removing the blocking Wait() call to avoid deadlock
            this.task?.ContinueWith(t =>
            {
                if (t.Exception != null)
                {
                    foreach (var ex in t.Exception.InnerExceptions)
                    {
                        if (ex is TaskCanceledException)
                        {
                            Console.WriteLine("Task was canceled.");
                        }
                        else
                        {
                            Console.WriteLine($"Unexpected error: {ex.Message}");
                        }
                    }
                }
            }, TaskContinuationOptions.OnlyOnFaulted | TaskContinuationOptions.ExecuteSynchronously);
        }

        // Other event handlers...
    }
}