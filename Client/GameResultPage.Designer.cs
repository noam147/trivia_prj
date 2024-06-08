namespace clientGuiTrivia
{
    partial class GameResultPage
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
            this.label2 = new System.Windows.Forms.Label();
            this.menuButton = new System.Windows.Forms.Button();
            this.playAgainButton = new System.Windows.Forms.Button();
            this.playersLabel = new System.Windows.Forms.Label();
            this.SuspendLayout();
            // 
            // label2
            // 
            this.label2.AutoSize = true;
            this.label2.Font = new System.Drawing.Font("Microsoft Sans Serif", 14F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(177)));
            this.label2.ForeColor = System.Drawing.Color.IndianRed;
            this.label2.Location = new System.Drawing.Point(229, 72);
            this.label2.Name = "label2";
            this.label2.Size = new System.Drawing.Size(425, 32);
            this.label2.TabIndex = 2;
            this.label2.Text = "Waiting for all players to finish";
            this.label2.Click += new System.EventHandler(this.label2_Click);
            // 
            // menuButton
            // 
            this.menuButton.AutoSize = true;
            this.menuButton.AutoSizeMode = System.Windows.Forms.AutoSizeMode.GrowAndShrink;
            this.menuButton.FlatAppearance.BorderColor = System.Drawing.SystemColors.ActiveBorder;
            this.menuButton.FlatAppearance.BorderSize = 0;
            this.menuButton.FlatStyle = System.Windows.Forms.FlatStyle.Flat;
            this.menuButton.Font = new System.Drawing.Font("ROG Fonts", 14F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.menuButton.ForeColor = System.Drawing.Color.Red;
            this.menuButton.Location = new System.Drawing.Point(48, 609);
            this.menuButton.Name = "menuButton";
            this.menuButton.Size = new System.Drawing.Size(246, 44);
            this.menuButton.TabIndex = 4;
            this.menuButton.Text = "go to menu";
            this.menuButton.UseVisualStyleBackColor = true;
            this.menuButton.Click += new System.EventHandler(this.menuButton_Click);
            // 
            // playAgainButton
            // 
            this.playAgainButton.AutoSize = true;
            this.playAgainButton.AutoSizeMode = System.Windows.Forms.AutoSizeMode.GrowAndShrink;
            this.playAgainButton.FlatAppearance.BorderSize = 0;
            this.playAgainButton.FlatStyle = System.Windows.Forms.FlatStyle.Flat;
            this.playAgainButton.Font = new System.Drawing.Font("ROG Fonts", 14F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.playAgainButton.ForeColor = System.Drawing.Color.Lime;
            this.playAgainButton.Location = new System.Drawing.Point(628, 609);
            this.playAgainButton.Name = "playAgainButton";
            this.playAgainButton.Size = new System.Drawing.Size(242, 44);
            this.playAgainButton.TabIndex = 5;
            this.playAgainButton.Text = "play again";
            this.playAgainButton.UseVisualStyleBackColor = true;
            this.playAgainButton.Click += new System.EventHandler(this.playAgainButton_Click);
            // 
            // playersLabel
            // 
            this.playersLabel.AutoSize = true;
            this.playersLabel.Font = new System.Drawing.Font("Segoe Print", 14F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.playersLabel.ForeColor = System.Drawing.Color.Indigo;
            this.playersLabel.Location = new System.Drawing.Point(39, 181);
            this.playersLabel.Name = "playersLabel";
            this.playersLabel.Size = new System.Drawing.Size(196, 50);
            this.playersLabel.TabIndex = 6;
            this.playersLabel.Text = "PlayersLabel";
            // 
            // GameResultPage
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(9F, 20F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.BackColor = System.Drawing.Color.DeepSkyBlue;
            this.ClientSize = new System.Drawing.Size(928, 744);
            this.Controls.Add(this.playersLabel);
            this.Controls.Add(this.playAgainButton);
            this.Controls.Add(this.menuButton);
            this.Controls.Add(this.label2);
            this.Name = "GameResultPage";
            this.ShowIcon = false;
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.Label label2;
        private System.Windows.Forms.Button menuButton;
        private System.Windows.Forms.Button playAgainButton;
        private System.Windows.Forms.Label playersLabel;
    }
}