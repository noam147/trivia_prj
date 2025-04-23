namespace clientGuiTrivia
{
    partial class GameFinishScreen
    {
        /// <summary>
        /// Required designer variable.
        /// </summary>
        private System.ComponentModel.IContainer components = null;

        /// <summary>
        /// Clean up any resources being used.
        /// </summary>
        /// <param name="disposing">true if managed resources should be disposed; otherwise, false.</param>
        protected override void Dispose(bool disposing)
        {
            if (disposing && (components != null))
            {
                components.Dispose();
            }
            base.Dispose(disposing);
        }

        #region Windows Form Designer generated code

        /// <summary>
        /// Required method for Designer support - do not modify
        /// the contents of this method with the code editor.
        /// </summary>
        private void InitializeComponent()
        {
            System.ComponentModel.ComponentResourceManager resources = new System.ComponentModel.ComponentResourceManager(typeof(GameFinishScreen));
            this.Title = new System.Windows.Forms.Label();
            this.NotAllFinished = new System.Windows.Forms.Label();
            this.playersStats = new System.Windows.Forms.DataGridView();
            ((System.ComponentModel.ISupportInitialize)(this.playersStats)).BeginInit();
            this.SuspendLayout();
            // 
            // Title
            // 
            resources.ApplyResources(this.Title, "Title");
            this.Title.ForeColor = System.Drawing.Color.Orange;
            this.Title.Name = "Title";
            // 
            // NotAllFinished
            // 
            resources.ApplyResources(this.NotAllFinished, "NotAllFinished");
            this.NotAllFinished.ForeColor = System.Drawing.Color.Orange;
            this.NotAllFinished.Name = "NotAllFinished";
            // 
            // dataGridView1
            // 
            this.playersStats.BackgroundColor = System.Drawing.Color.DeepSkyBlue;
            this.playersStats.BorderStyle = System.Windows.Forms.BorderStyle.None;
            this.playersStats.ColumnHeadersHeightSizeMode = System.Windows.Forms.DataGridViewColumnHeadersHeightSizeMode.AutoSize;
            resources.ApplyResources(this.playersStats, "playersStats");
            this.playersStats.Name = "playersStats";
            this.playersStats.RowTemplate.Height = 28;
            // 
            // GameFinishScreen
            // 
            resources.ApplyResources(this, "$this");
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.AutoValidate = System.Windows.Forms.AutoValidate.EnablePreventFocusChange;
            this.BackColor = System.Drawing.Color.DeepSkyBlue;
            this.Controls.Add(this.playersStats);
            this.Controls.Add(this.NotAllFinished);
            this.Controls.Add(this.Title);
            this.Name = "GameFinishScreen";
            this.ShowIcon = false;
            ((System.ComponentModel.ISupportInitialize)(this.playersStats)).EndInit();
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.Label Title;
        private System.Windows.Forms.Label NotAllFinished;
        private System.Windows.Forms.DataGridView playersStats;
    }
}