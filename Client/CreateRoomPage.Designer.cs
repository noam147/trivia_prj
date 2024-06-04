namespace clientGuiTrivia
{
    partial class CreateRoomPage
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
            System.ComponentModel.ComponentResourceManager resources = new System.ComponentModel.ComponentResourceManager(typeof(CreateRoomPage));
            this.label1 = new System.Windows.Forms.Label();
            this.button1 = new System.Windows.Forms.Button();
            this.button2 = new System.Windows.Forms.Button();
            this._roomName = new System.Windows.Forms.TextBox();
            this.warningLabel = new System.Windows.Forms.Label();
            this.label7 = new System.Windows.Forms.Label();
            this.label8 = new System.Windows.Forms.Label();
            this.label9 = new System.Windows.Forms.Label();
            this.label2 = new System.Windows.Forms.Label();
            this._numberOfPlayers = new System.Windows.Forms.TextBox();
            this._numberOfQuestions = new System.Windows.Forms.TextBox();
            this._TimeForQuestion = new System.Windows.Forms.TextBox();
            this.SuspendLayout();
            // 
            // label1
            // 
            this.label1.AutoSize = true;
            this.label1.FlatStyle = System.Windows.Forms.FlatStyle.System;
            this.label1.Font = new System.Drawing.Font("Modern No. 20", 10F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.label1.ForeColor = System.Drawing.Color.Crimson;
            this.label1.Location = new System.Drawing.Point(481, 115);
            this.label1.Name = "label1";
            this.label1.Size = new System.Drawing.Size(108, 22);
            this.label1.TabIndex = 0;
            this.label1.Text = "room name";
            this.label1.Click += new System.EventHandler(this.label1_Click);
            // 
            // button1
            // 
            this.button1.AutoSize = true;
            this.button1.AutoSizeMode = System.Windows.Forms.AutoSizeMode.GrowAndShrink;
            this.button1.FlatAppearance.BorderSize = 0;
            this.button1.FlatAppearance.MouseDownBackColor = System.Drawing.Color.WhiteSmoke;
            this.button1.FlatAppearance.MouseOverBackColor = System.Drawing.Color.WhiteSmoke;
            this.button1.FlatStyle = System.Windows.Forms.FlatStyle.Flat;
            this.button1.Font = new System.Drawing.Font("Agency FB", 16F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.button1.ForeColor = System.Drawing.Color.Crimson;
            this.button1.Location = new System.Drawing.Point(485, 399);
            this.button1.Name = "button1";
            this.button1.Size = new System.Drawing.Size(96, 49);
            this.button1.TabIndex = 4;
            this.button1.Text = "Create";
            this.button1.UseVisualStyleBackColor = false;
            this.button1.Click += new System.EventHandler(this.button1_Click);
            // 
            // button2
            // 
            this.button2.AutoSize = true;
            this.button2.AutoSizeMode = System.Windows.Forms.AutoSizeMode.GrowAndShrink;
            this.button2.FlatAppearance.BorderSize = 0;
            this.button2.FlatStyle = System.Windows.Forms.FlatStyle.Flat;
            this.button2.Image = ((System.Drawing.Image)(resources.GetObject("button2.Image")));
            this.button2.Location = new System.Drawing.Point(82, 50);
            this.button2.Name = "button2";
            this.button2.RightToLeft = System.Windows.Forms.RightToLeft.Yes;
            this.button2.Size = new System.Drawing.Size(38, 38);
            this.button2.TabIndex = 5;
            this.button2.UseVisualStyleBackColor = true;
            this.button2.Click += new System.EventHandler(this.button2_Click);
            // 
            // _roomName
            // 
            this._roomName.Font = new System.Drawing.Font("Microsoft Sans Serif", 9F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(177)));
            this._roomName.Location = new System.Drawing.Point(485, 144);
            this._roomName.Margin = new System.Windows.Forms.Padding(7);
            this._roomName.Name = "_roomName";
            this._roomName.Size = new System.Drawing.Size(100, 28);
            this._roomName.TabIndex = 6;
            this._roomName.TextChanged += new System.EventHandler(this._roomName_TextChanged);
            // 
            // warningLabel
            // 
            this.warningLabel.AutoSize = true;
            this.warningLabel.FlatStyle = System.Windows.Forms.FlatStyle.System;
            this.warningLabel.Font = new System.Drawing.Font("Microsoft Sans Serif", 9F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(177)));
            this.warningLabel.Location = new System.Drawing.Point(425, 13);
            this.warningLabel.Name = "warningLabel";
            this.warningLabel.Size = new System.Drawing.Size(0, 22);
            this.warningLabel.TabIndex = 11;
            // 
            // label7
            // 
            this.label7.AutoSize = true;
            this.label7.FlatStyle = System.Windows.Forms.FlatStyle.System;
            this.label7.Font = new System.Drawing.Font("Modern No. 20", 10F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.label7.ForeColor = System.Drawing.Color.Crimson;
            this.label7.Location = new System.Drawing.Point(457, 307);
            this.label7.Name = "label7";
            this.label7.Size = new System.Drawing.Size(163, 22);
            this.label7.TabIndex = 13;
            this.label7.Text = "time for question";
            // 
            // label8
            // 
            this.label8.AutoSize = true;
            this.label8.FlatStyle = System.Windows.Forms.FlatStyle.System;
            this.label8.Font = new System.Drawing.Font("Modern No. 20", 10F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.label8.ForeColor = System.Drawing.Color.Crimson;
            this.label8.Location = new System.Drawing.Point(449, 243);
            this.label8.Name = "label8";
            this.label8.Size = new System.Drawing.Size(190, 22);
            this.label8.TabIndex = 14;
            this.label8.Text = "number of questions";
            this.label8.Click += new System.EventHandler(this.label8_Click);
            // 
            // label9
            // 
            this.label9.AutoSize = true;
            this.label9.FlatStyle = System.Windows.Forms.FlatStyle.System;
            this.label9.Font = new System.Drawing.Font("Modern No. 20", 10F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.label9.ForeColor = System.Drawing.Color.Crimson;
            this.label9.Location = new System.Drawing.Point(449, 179);
            this.label9.Name = "label9";
            this.label9.Size = new System.Drawing.Size(171, 22);
            this.label9.TabIndex = 15;
            this.label9.Text = "number of players";
            // 
            // label2
            // 
            this.label2.AutoSize = true;
            this.label2.FlatStyle = System.Windows.Forms.FlatStyle.System;
            this.label2.Font = new System.Drawing.Font("Monotype Corsiva", 16F, ((System.Drawing.FontStyle)((System.Drawing.FontStyle.Bold | System.Drawing.FontStyle.Italic))), System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.label2.ForeColor = System.Drawing.Color.Crimson;
            this.label2.Location = new System.Drawing.Point(400, 50);
            this.label2.Name = "label2";
            this.label2.Size = new System.Drawing.Size(273, 39);
            this.label2.TabIndex = 16;
            this.label2.Text = "Enter Room Settings";
            // 
            // _numberOfPlayers
            // 
            this._numberOfPlayers.Font = new System.Drawing.Font("Microsoft Sans Serif", 9F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(177)));
            this._numberOfPlayers.Location = new System.Drawing.Point(485, 208);
            this._numberOfPlayers.Margin = new System.Windows.Forms.Padding(7);
            this._numberOfPlayers.Name = "_numberOfPlayers";
            this._numberOfPlayers.Size = new System.Drawing.Size(100, 28);
            this._numberOfPlayers.TabIndex = 17;
            this._numberOfPlayers.TextChanged += new System.EventHandler(this._numberOfPlayers_TextChanged);
            // 
            // _numberOfQuestions
            // 
            this._numberOfQuestions.Font = new System.Drawing.Font("Microsoft Sans Serif", 9F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(177)));
            this._numberOfQuestions.Location = new System.Drawing.Point(485, 272);
            this._numberOfQuestions.Margin = new System.Windows.Forms.Padding(7);
            this._numberOfQuestions.Name = "_numberOfQuestions";
            this._numberOfQuestions.Size = new System.Drawing.Size(100, 28);
            this._numberOfQuestions.TabIndex = 18;
            this._numberOfQuestions.TextChanged += new System.EventHandler(this._numberOfQuestions_TextChanged);
            // 
            // _TimeForQuestion
            // 
            this._TimeForQuestion.Font = new System.Drawing.Font("Microsoft Sans Serif", 9F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(177)));
            this._TimeForQuestion.Location = new System.Drawing.Point(485, 336);
            this._TimeForQuestion.Margin = new System.Windows.Forms.Padding(7);
            this._TimeForQuestion.Name = "_TimeForQuestion";
            this._TimeForQuestion.Size = new System.Drawing.Size(100, 28);
            this._TimeForQuestion.TabIndex = 19;
            this._TimeForQuestion.TextChanged += new System.EventHandler(this._TimeForQuestion_TextChanged);
            // 
            // CreateRoomPage
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(9F, 20F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.BackColor = System.Drawing.Color.DeepSkyBlue;
            this.ClientSize = new System.Drawing.Size(928, 744);
            this.Controls.Add(this._TimeForQuestion);
            this.Controls.Add(this._numberOfQuestions);
            this.Controls.Add(this._numberOfPlayers);
            this.Controls.Add(this.label2);
            this.Controls.Add(this.label9);
            this.Controls.Add(this.label8);
            this.Controls.Add(this.label7);
            this.Controls.Add(this.warningLabel);
            this.Controls.Add(this._roomName);
            this.Controls.Add(this.button2);
            this.Controls.Add(this.button1);
            this.Controls.Add(this.label1);
            this.Name = "CreateRoomPage";
            this.ShowIcon = false;
            this.Load += new System.EventHandler(this.CreateRoomPage_Load);
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.Label label1;
        private System.Windows.Forms.Button button1;
        private System.Windows.Forms.Button button2;
        private System.Windows.Forms.TextBox _roomName;
        private System.Windows.Forms.Label warningLabel;
        private System.Windows.Forms.Label label7;
        private System.Windows.Forms.Label label8;
        private System.Windows.Forms.Label label9;
        private System.Windows.Forms.Label label2;
        private System.Windows.Forms.TextBox _numberOfPlayers;
        private System.Windows.Forms.TextBox _numberOfQuestions;
        private System.Windows.Forms.TextBox _TimeForQuestion;
    }
}