namespace clientGuiTrivia
{
    partial class UserStatusPage
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
            System.ComponentModel.ComponentResourceManager resources = new System.ComponentModel.ComponentResourceManager(typeof(UserStatusPage));
            this.label1 = new System.Windows.Forms.Label();
            this.GamesLabel = new System.Windows.Forms.Label();
            this.RightAnswerLabel = new System.Windows.Forms.Label();
            this.WrongAnswersLabel = new System.Windows.Forms.Label();
            this.AvgTimeLabel = new System.Windows.Forms.Label();
            this.button1 = new System.Windows.Forms.Button();
            this.TotalScoreLabel = new System.Windows.Forms.Label();
            this.SuspendLayout();
            // 
            // label1
            // 
            this.label1.AutoSize = true;
            this.label1.Font = new System.Drawing.Font("Onyx", 18F, System.Drawing.FontStyle.Bold);
            this.label1.ForeColor = System.Drawing.Color.DarkOrange;
            this.label1.Location = new System.Drawing.Point(271, 46);
            this.label1.Name = "label1";
            this.label1.Size = new System.Drawing.Size(214, 41);
            this.label1.TabIndex = 0;
            this.label1.Text = "Your Personal Stats";
            // 
            // GamesLabel
            // 
            this.GamesLabel.AutoSize = true;
            this.GamesLabel.BackColor = System.Drawing.Color.Transparent;
            this.GamesLabel.Font = new System.Drawing.Font("Franklin Gothic Heavy", 12F);
            this.GamesLabel.ForeColor = System.Drawing.Color.Yellow;
            this.GamesLabel.Image = ((System.Drawing.Image)(resources.GetObject("GamesLabel.Image")));
            this.GamesLabel.ImageAlign = System.Drawing.ContentAlignment.MiddleLeft;
            this.GamesLabel.Location = new System.Drawing.Point(272, 159);
            this.GamesLabel.Name = "GamesLabel";
            this.GamesLabel.Size = new System.Drawing.Size(221, 30);
            this.GamesLabel.TabIndex = 1;
            this.GamesLabel.Text = "       Games Played ";
            this.GamesLabel.TextAlign = System.Drawing.ContentAlignment.MiddleRight;
            // 
            // RightAnswerLabel
            // 
            this.RightAnswerLabel.AutoSize = true;
            this.RightAnswerLabel.Font = new System.Drawing.Font("Franklin Gothic Heavy", 12F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.RightAnswerLabel.ForeColor = System.Drawing.Color.Lime;
            this.RightAnswerLabel.Image = ((System.Drawing.Image)(resources.GetObject("RightAnswerLabel.Image")));
            this.RightAnswerLabel.ImageAlign = System.Drawing.ContentAlignment.MiddleLeft;
            this.RightAnswerLabel.Location = new System.Drawing.Point(272, 237);
            this.RightAnswerLabel.Name = "RightAnswerLabel";
            this.RightAnswerLabel.Size = new System.Drawing.Size(350, 30);
            this.RightAnswerLabel.TabIndex = 2;
            this.RightAnswerLabel.Text = "       Number Of Right Answers ";
            this.RightAnswerLabel.TextAlign = System.Drawing.ContentAlignment.MiddleRight;
            this.RightAnswerLabel.Click += new System.EventHandler(this.label3_Click);
            // 
            // WrongAnswersLabel
            // 
            this.WrongAnswersLabel.AutoSize = true;
            this.WrongAnswersLabel.Font = new System.Drawing.Font("Franklin Gothic Heavy", 12F);
            this.WrongAnswersLabel.ForeColor = System.Drawing.Color.Red;
            this.WrongAnswersLabel.Image = ((System.Drawing.Image)(resources.GetObject("WrongAnswersLabel.Image")));
            this.WrongAnswersLabel.ImageAlign = System.Drawing.ContentAlignment.MiddleLeft;
            this.WrongAnswersLabel.Location = new System.Drawing.Point(272, 334);
            this.WrongAnswersLabel.Name = "WrongAnswersLabel";
            this.WrongAnswersLabel.Size = new System.Drawing.Size(362, 30);
            this.WrongAnswersLabel.TabIndex = 3;
            this.WrongAnswersLabel.Text = "       Number Of Wrong Answers ";
            this.WrongAnswersLabel.TextAlign = System.Drawing.ContentAlignment.MiddleRight;
            // 
            // AvgTimeLabel
            // 
            this.AvgTimeLabel.AutoSize = true;
            this.AvgTimeLabel.Font = new System.Drawing.Font("Franklin Gothic Heavy", 12F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.AvgTimeLabel.ForeColor = System.Drawing.Color.MediumBlue;
            this.AvgTimeLabel.Image = ((System.Drawing.Image)(resources.GetObject("AvgTimeLabel.Image")));
            this.AvgTimeLabel.ImageAlign = System.Drawing.ContentAlignment.MiddleLeft;
            this.AvgTimeLabel.Location = new System.Drawing.Point(272, 428);
            this.AvgTimeLabel.Name = "AvgTimeLabel";
            this.AvgTimeLabel.Size = new System.Drawing.Size(329, 30);
            this.AvgTimeLabel.TabIndex = 4;
            this.AvgTimeLabel.Text = "       Avrage Time For Answer ";
            this.AvgTimeLabel.TextAlign = System.Drawing.ContentAlignment.MiddleRight;
            // 
            // button1
            // 
            this.button1.AutoSize = true;
            this.button1.AutoSizeMode = System.Windows.Forms.AutoSizeMode.GrowAndShrink;
            this.button1.FlatAppearance.BorderSize = 0;
            this.button1.FlatStyle = System.Windows.Forms.FlatStyle.Flat;
            this.button1.Image = ((System.Drawing.Image)(resources.GetObject("button1.Image")));
            this.button1.Location = new System.Drawing.Point(46, 26);
            this.button1.Name = "button1";
            this.button1.Size = new System.Drawing.Size(38, 38);
            this.button1.TabIndex = 5;
            this.button1.UseVisualStyleBackColor = true;
            this.button1.Click += new System.EventHandler(this.button1_Click);
            // 
            // TotalScoreLabel
            // 
            this.TotalScoreLabel.AutoSize = true;
            this.TotalScoreLabel.Font = new System.Drawing.Font("Franklin Gothic Heavy", 12F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.TotalScoreLabel.ForeColor = System.Drawing.Color.Black;
            this.TotalScoreLabel.ImageAlign = System.Drawing.ContentAlignment.MiddleLeft;
            this.TotalScoreLabel.Location = new System.Drawing.Point(273, 494);
            this.TotalScoreLabel.Name = "TotalScoreLabel";
            this.TotalScoreLabel.Size = new System.Drawing.Size(146, 30);
            this.TotalScoreLabel.TabIndex = 6;
            this.TotalScoreLabel.Text = "Total Score:";
            this.TotalScoreLabel.TextAlign = System.Drawing.ContentAlignment.MiddleRight;
            // 
            // UserStatusPage
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(9F, 20F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.BackColor = System.Drawing.Color.DeepSkyBlue;
            this.ClientSize = new System.Drawing.Size(928, 744);
            this.Controls.Add(this.TotalScoreLabel);
            this.Controls.Add(this.button1);
            this.Controls.Add(this.AvgTimeLabel);
            this.Controls.Add(this.WrongAnswersLabel);
            this.Controls.Add(this.RightAnswerLabel);
            this.Controls.Add(this.GamesLabel);
            this.Controls.Add(this.label1);
            this.Name = "UserStatusPage";
            this.ShowIcon = false;
            this.Load += new System.EventHandler(this.UserStatusPage_Load);
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.Label label1;
        private System.Windows.Forms.Label GamesLabel;
        private System.Windows.Forms.Label RightAnswerLabel;
        private System.Windows.Forms.Label WrongAnswersLabel;
        private System.Windows.Forms.Label AvgTimeLabel;
        private System.Windows.Forms.Button button1;
        private System.Windows.Forms.Label TotalScoreLabel;
    }
}