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
        private void refresh()
        {

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
                string msgRecive;
                List<Dictionary<string, string>> users;

                Label[] labels = { label1, label2, label3, label4, label5 };

                while (!token.IsCancellationRequested)
                {
                    Console.WriteLine("Task running...");

                    lock (lockSocket)
                    {
                        clientHandler.sendMsg(msgToSend);
                        msgRecive = clientHandler.receiveMsg();
                    }

                    users = Deserializer.desirializeGetHighscoreResponse(msgRecive);

                    // Update the labels on the UI thread
                    if (labels != null && users != null)
                    {
                        this.Invoke(new Action(() =>
                        {

                            for (int i = 0; i < users.Count; i++)
                            {
                                foreach (var kvp in users[i])
                                {
                                    labels[i].Text = "The player: " + kvp.Key + " scored: " + kvp.Value;
                                    Console.WriteLine($"Key: {kvp.Key}, Value: {kvp.Value}");
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

            try
            {
                this.task?.Wait();
            }
            catch (AggregateException ex)
            {
                if (ex.InnerException is TaskCanceledException)
                {
                    Console.WriteLine("Task was canceled.");
                }
                else
                {
                    throw;
                }
            }
        }

        // Other event handlers...
    }
}