using Microsoft.SqlServer.Server;

namespace clientGuiTrivia
{
    partial class adminWaitingRoom
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
            this.label6 = new System.Windows.Forms.Label();
            this.label7 = new System.Windows.Forms.Label();
            this.closeRoomButton = new System.Windows.Forms.Button();
            this.startGmaeButton = new System.Windows.Forms.Button();
            this.UsersList = new System.Windows.Forms.ListBox();
            this.usersListLabel = new System.Windows.Forms.Label();
            this.kickButton = new System.Windows.Forms.Button();
            this.banButton = new System.Windows.Forms.Button();
            this.SuspendLayout();
            // 
            // label6
            // 
            this.label6.AutoSize = true;
            this.label6.BackColor = System.Drawing.Color.DeepSkyBlue;
            this.label6.Font = new System.Drawing.Font("Times New Roman", 18F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(177)));
            this.label6.ForeColor = System.Drawing.Color.LightGoldenrodYellow;
            this.label6.Location = new System.Drawing.Point(320, 34);
            this.label6.Name = "label6";
            this.label6.Size = new System.Drawing.Size(0, 41);
            this.label6.TabIndex = 0;
            // 
            // label7
            // 
            this.label7.AutoSize = true;
            this.label7.BackColor = System.Drawing.Color.DeepSkyBlue;
            this.label7.Font = new System.Drawing.Font("Times New Roman", 12F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(177)));
            this.label7.ForeColor = System.Drawing.Color.Indigo;
            this.label7.Location = new System.Drawing.Point(367, 88);
            this.label7.Name = "label7";
            this.label7.Size = new System.Drawing.Size(0, 26);
            this.label7.TabIndex = 1;
            // 
            // closeRoomButton
            // 
            this.closeRoomButton.AutoSize = true;
            this.closeRoomButton.AutoSizeMode = System.Windows.Forms.AutoSizeMode.GrowAndShrink;
            this.closeRoomButton.FlatAppearance.BorderColor = System.Drawing.SystemColors.ActiveBorder;
            this.closeRoomButton.FlatAppearance.BorderSize = 0;
            this.closeRoomButton.FlatStyle = System.Windows.Forms.FlatStyle.Flat;
            this.closeRoomButton.Font = new System.Drawing.Font("ROG Fonts", 14F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.closeRoomButton.ForeColor = System.Drawing.Color.Red;
            this.closeRoomButton.Location = new System.Drawing.Point(64, 600);
            this.closeRoomButton.Name = "closeRoomButton";
            this.closeRoomButton.Size = new System.Drawing.Size(259, 44);
            this.closeRoomButton.TabIndex = 3;
            this.closeRoomButton.Text = "close room";
            this.closeRoomButton.UseVisualStyleBackColor = true;
            this.closeRoomButton.Click += new System.EventHandler(this.button3_Click);
            // 
            // startGmaeButton
            // 
            this.startGmaeButton.AutoSize = true;
            this.startGmaeButton.AutoSizeMode = System.Windows.Forms.AutoSizeMode.GrowAndShrink;
            this.startGmaeButton.FlatAppearance.BorderSize = 0;
            this.startGmaeButton.FlatStyle = System.Windows.Forms.FlatStyle.Flat;
            this.startGmaeButton.Font = new System.Drawing.Font("ROG Fonts", 14F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.startGmaeButton.ForeColor = System.Drawing.Color.Lime;
            this.startGmaeButton.Location = new System.Drawing.Point(598, 600);
            this.startGmaeButton.Name = "startGmaeButton";
            this.startGmaeButton.Size = new System.Drawing.Size(265, 44);
            this.startGmaeButton.TabIndex = 4;
            this.startGmaeButton.Text = "Start Game";
            this.startGmaeButton.UseVisualStyleBackColor = true;
            this.startGmaeButton.Click += new System.EventHandler(this.startGmaeButton_Click);
            // 
            // UsersList
            // 
            this.UsersList.BackColor = System.Drawing.Color.DeepSkyBlue;
            this.UsersList.Cursor = System.Windows.Forms.Cursors.Default;
            this.UsersList.Font = new System.Drawing.Font("Impact", 12F, ((System.Drawing.FontStyle)((System.Drawing.FontStyle.Bold | System.Drawing.FontStyle.Italic))), System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.UsersList.ForeColor = System.Drawing.Color.HotPink;
            this.UsersList.FormattingEnabled = true;
            this.UsersList.ItemHeight = 29;
            this.UsersList.Location = new System.Drawing.Point(36, 120);
            this.UsersList.Name = "UsersList";
            this.UsersList.Size = new System.Drawing.Size(246, 410);
            this.UsersList.TabIndex = 5;
            this.UsersList.SelectedIndexChanged += new System.EventHandler(this.UsersList_SelectedIndexChanged);
            // 
            // usersListLabel
            // 
            this.usersListLabel.AutoSize = true;
            this.usersListLabel.Font = new System.Drawing.Font("Haettenschweiler", 14F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.usersListLabel.ForeColor = System.Drawing.Color.HotPink;
            this.usersListLabel.Location = new System.Drawing.Point(109, 88);
            this.usersListLabel.Name = "usersListLabel";
            this.usersListLabel.Size = new System.Drawing.Size(87, 29);
            this.usersListLabel.TabIndex = 6;
            this.usersListLabel.Text = "Players";
            // 
            // kickButton
            // 
            this.kickButton.FlatAppearance.BorderSize = 0;
            this.kickButton.FlatStyle = System.Windows.Forms.FlatStyle.Flat;
            this.kickButton.Font = new System.Drawing.Font("Showcard Gothic", 10F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.kickButton.ForeColor = System.Drawing.Color.Red;
            this.kickButton.Location = new System.Drawing.Point(327, 120);
            this.kickButton.Name = "kickButton";
            this.kickButton.Size = new System.Drawing.Size(137, 60);
            this.kickButton.TabIndex = 7;
            this.kickButton.Text = "kick";
            this.kickButton.UseVisualStyleBackColor = true;
            this.kickButton.Click += new System.EventHandler(this.kickButton_Click);
            // 
            // banButton
            // 
            this.banButton.FlatAppearance.BorderSize = 0;
            this.banButton.FlatStyle = System.Windows.Forms.FlatStyle.Flat;
            this.banButton.Font = new System.Drawing.Font("Showcard Gothic", 10F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.banButton.ForeColor = System.Drawing.Color.FromArgb(((int)(((byte)(1)))), ((int)(((byte)(0)))), ((int)(((byte)(64)))));
            this.banButton.Location = new System.Drawing.Point(327, 214);
            this.banButton.Name = "banButton";
            this.banButton.Size = new System.Drawing.Size(137, 60);
            this.banButton.TabIndex = 8;
            this.banButton.Text = "ban";
            this.banButton.UseVisualStyleBackColor = true;
            this.banButton.Click += new System.EventHandler(this.banButton_Click);
            // 
            // adminWaitingRoom
            // 
            this.BackColor = System.Drawing.Color.DeepSkyBlue;
            this.ClientSize = new System.Drawing.Size(928, 744);
            this.Controls.Add(this.banButton);
            this.Controls.Add(this.kickButton);
            this.Controls.Add(this.usersListLabel);
            this.Controls.Add(this.UsersList);
            this.Controls.Add(this.startGmaeButton);
            this.Controls.Add(this.closeRoomButton);
            this.Controls.Add(this.label7);
            this.Controls.Add(this.label6);
            this.Font = new System.Drawing.Font("Microsoft Sans Serif", 12F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(177)));
            this.ForeColor = System.Drawing.SystemColors.ActiveCaption;
            this.Name = "adminWaitingRoom";
            this.FormClosing += new System.Windows.Forms.FormClosingEventHandler(this.AdminWaitingRoom_FormClosing);
            this.Load += new System.EventHandler(this.AdminWaitingRoom_Load);
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.Label label6;
        private System.Windows.Forms.Label label7;
        private System.Windows.Forms.Button closeRoomButton;
        private System.Windows.Forms.Button startGmaeButton;
        private System.Windows.Forms.Button backButton;
        private System.Windows.Forms.ListBox UsersList;
        private System.Windows.Forms.Label usersListLabel;
        private System.Windows.Forms.Button kickButton;
        private System.Windows.Forms.Button banButton;
    }
}