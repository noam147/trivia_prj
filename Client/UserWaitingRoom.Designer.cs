namespace clientGuiTrivia
{
    partial class UserWaitingRoom
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
            this.button1 = new System.Windows.Forms.Button();
            this.roomNameLabel = new System.Windows.Forms.Label();
            this.UsersListLabel = new System.Windows.Forms.Label();
            this.roomSettingsLabel = new System.Windows.Forms.Label();
            this.UsersList = new System.Windows.Forms.ListBox();
            this.SuspendLayout();
            // 
            // button1
            // 
            this.button1.AutoSize = true;
            this.button1.AutoSizeMode = System.Windows.Forms.AutoSizeMode.GrowAndShrink;
            this.button1.FlatAppearance.BorderSize = 0;
            this.button1.FlatStyle = System.Windows.Forms.FlatStyle.Flat;
            this.button1.Font = new System.Drawing.Font("ROG Fonts", 16F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.button1.ForeColor = System.Drawing.Color.Red;
            this.button1.Location = new System.Drawing.Point(264, 478);
            this.button1.Name = "button1";
            this.button1.Size = new System.Drawing.Size(295, 48);
            this.button1.TabIndex = 0;
            this.button1.Text = "leave room";
            this.button1.UseVisualStyleBackColor = true;
            this.button1.Click += new System.EventHandler(this.button1_Click);
            // 
            // roomNameLabel
            // 
            this.roomNameLabel.AutoSize = true;
            this.roomNameLabel.Font = new System.Drawing.Font("Microsoft Uighur", 26F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.roomNameLabel.ForeColor = System.Drawing.Color.DarkViolet;
            this.roomNameLabel.Location = new System.Drawing.Point(370, 51);
            this.roomNameLabel.Name = "roomNameLabel";
            this.roomNameLabel.Size = new System.Drawing.Size(119, 62);
            this.roomNameLabel.TabIndex = 1;
            this.roomNameLabel.Text = "Name";
            // 
            // UsersListLabel
            // 
            this.UsersListLabel.AutoSize = true;
            this.UsersListLabel.Font = new System.Drawing.Font("Microsoft YaHei", 12F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.UsersListLabel.ForeColor = System.Drawing.Color.HotPink;
            this.UsersListLabel.Location = new System.Drawing.Point(79, 108);
            this.UsersListLabel.Name = "UsersListLabel";
            this.UsersListLabel.Size = new System.Drawing.Size(101, 31);
            this.UsersListLabel.TabIndex = 2;
            this.UsersListLabel.Text = "Players";
            // 
            // roomSettingsLabel
            // 
            this.roomSettingsLabel.AutoSize = true;
            this.roomSettingsLabel.Font = new System.Drawing.Font("Microsoft Uighur", 16F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.roomSettingsLabel.ForeColor = System.Drawing.Color.Navy;
            this.roomSettingsLabel.Location = new System.Drawing.Point(416, 165);
            this.roomSettingsLabel.Name = "roomSettingsLabel";
            this.roomSettingsLabel.Size = new System.Drawing.Size(199, 38);
            this.roomSettingsLabel.TabIndex = 4;
            this.roomSettingsLabel.Text = "roomSettingsLabel";
            // 
            // UsersList
            // 
            this.UsersList.BackColor = System.Drawing.Color.DeepSkyBlue;
            this.UsersList.Font = new System.Drawing.Font("Microsoft YaHei", 10F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.UsersList.ForeColor = System.Drawing.Color.HotPink;
            this.UsersList.FormattingEnabled = true;
            this.UsersList.ItemHeight = 27;
            this.UsersList.Location = new System.Drawing.Point(34, 154);
            this.UsersList.Name = "UsersList";
            this.UsersList.Size = new System.Drawing.Size(212, 301);
            this.UsersList.TabIndex = 5;
            // 
            // UserWaitingRoom
            // 
            this.BackColor = System.Drawing.Color.DeepSkyBlue;
            this.ClientSize = new System.Drawing.Size(928, 744);
            this.Controls.Add(this.UsersList);
            this.Controls.Add(this.roomSettingsLabel);
            this.Controls.Add(this.UsersListLabel);
            this.Controls.Add(this.roomNameLabel);
            this.Controls.Add(this.button1);
            this.Name = "UserWaitingRoom";
            this.Load += new System.EventHandler(this.UserWaitingRoom_Load);
            this.FormClosing += UserWaitingRoom_FormClosing;
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.Label label1;
        private System.Windows.Forms.Button button1;
        private System.Windows.Forms.Label roomNameLabel;
        private System.Windows.Forms.Label UsersListLabel;
        private System.Windows.Forms.Label roomSettingsLabel;
        private System.Windows.Forms.ListBox UsersList;
    }
}