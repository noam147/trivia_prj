﻿namespace clientGuiTrivia
{
    partial class GameQuestions
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
            this.questionLabel = new System.Windows.Forms.Label();
            this.questionsCountLabel = new System.Windows.Forms.Label();
            this.rightQuestionsCountLabel = new System.Windows.Forms.Label();
            this.timeToQuestionLabel = new System.Windows.Forms.Label();
            this.answer1 = new System.Windows.Forms.Button();
            this.answer2 = new System.Windows.Forms.Button();
            this.answer3 = new System.Windows.Forms.Button();
            this.answer4 = new System.Windows.Forms.Button();
            this.NumberOfRightQuestions = new System.Windows.Forms.Label();
            this.NumberOfQuestionLeft = new System.Windows.Forms.Label();
            this.SuspendLayout();
            // 
            // questionLabel
            // 
            this.questionLabel.AutoSize = true;
            this.questionLabel.Font = new System.Drawing.Font("Showcard Gothic", 10F, System.Drawing.FontStyle.Bold);
            this.questionLabel.ForeColor = System.Drawing.Color.Purple;
            this.questionLabel.Location = new System.Drawing.Point(362, 106);
            this.questionLabel.Name = "questionLabel";
            this.questionLabel.Size = new System.Drawing.Size(148, 26);
            this.questionLabel.TabIndex = 0;
            this.questionLabel.Text = "* question *";
            // 
            // questionsCountLabel
            // 
            this.questionsCountLabel.AutoSize = true;
            this.questionsCountLabel.Font = new System.Drawing.Font("Showcard Gothic", 8F, System.Drawing.FontStyle.Bold);
            this.questionsCountLabel.ForeColor = System.Drawing.Color.Purple;
            this.questionsCountLabel.Location = new System.Drawing.Point(128, 88);
            this.questionsCountLabel.Name = "questionsCountLabel";
            this.questionsCountLabel.RightToLeft = System.Windows.Forms.RightToLeft.Yes;
            this.questionsCountLabel.Size = new System.Drawing.Size(151, 20);
            this.questionsCountLabel.TabIndex = 1;
            this.questionsCountLabel.Text = "questions left";
            // 
            // rightQuestionsCountLabel
            // 
            this.rightQuestionsCountLabel.AutoSize = true;
            this.rightQuestionsCountLabel.Font = new System.Drawing.Font("Showcard Gothic", 8F, System.Drawing.FontStyle.Bold);
            this.rightQuestionsCountLabel.ForeColor = System.Drawing.Color.Purple;
            this.rightQuestionsCountLabel.Location = new System.Drawing.Point(54, 48);
            this.rightQuestionsCountLabel.Name = "rightQuestionsCountLabel";
            this.rightQuestionsCountLabel.Size = new System.Drawing.Size(172, 20);
            this.rightQuestionsCountLabel.TabIndex = 2;
            this.rightQuestionsCountLabel.Text = "Right Questions:";
            // 
            // timeToQuestionLabel
            // 
            this.timeToQuestionLabel.AutoSize = true;
            this.timeToQuestionLabel.Font = new System.Drawing.Font("Showcard Gothic", 10F, System.Drawing.FontStyle.Bold);
            this.timeToQuestionLabel.ForeColor = System.Drawing.Color.Purple;
            this.timeToQuestionLabel.Location = new System.Drawing.Point(629, 87);
            this.timeToQuestionLabel.Name = "timeToQuestionLabel";
            this.timeToQuestionLabel.Size = new System.Drawing.Size(231, 26);
            this.timeToQuestionLabel.TabIndex = 3;
            this.timeToQuestionLabel.Text = "Time for question:";
            this.timeToQuestionLabel.Click += new System.EventHandler(this.timeToQuestionLabel_Click);
            // 
            // answer1
            // 
            this.answer1.FlatAppearance.BorderSize = 0;
            this.answer1.FlatStyle = System.Windows.Forms.FlatStyle.Flat;
            this.answer1.Font = new System.Drawing.Font("Showcard Gothic", 10F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.answer1.ForeColor = System.Drawing.Color.Red;
            this.answer1.Location = new System.Drawing.Point(158, 230);
            this.answer1.Name = "answer1";
            this.answer1.Size = new System.Drawing.Size(200, 150);
            this.answer1.TabIndex = 4;
            this.answer1.Text = "button1";
            this.answer1.UseVisualStyleBackColor = true;
            this.answer1.Click += new System.EventHandler(this.answer1_Click);
            // 
            // answer2
            // 
            this.answer2.FlatAppearance.BorderSize = 0;
            this.answer2.FlatStyle = System.Windows.Forms.FlatStyle.Flat;
            this.answer2.Font = new System.Drawing.Font("Showcard Gothic", 10F, System.Drawing.FontStyle.Bold);
            this.answer2.ForeColor = System.Drawing.Color.Blue;
            this.answer2.Location = new System.Drawing.Point(441, 230);
            this.answer2.Name = "answer2";
            this.answer2.Size = new System.Drawing.Size(200, 150);
            this.answer2.TabIndex = 5;
            this.answer2.Text = "button2";
            this.answer2.UseVisualStyleBackColor = true;
            this.answer2.Click += new System.EventHandler(this.answer2_Click);
            // 
            // answer3
            // 
            this.answer3.FlatAppearance.BorderSize = 0;
            this.answer3.FlatStyle = System.Windows.Forms.FlatStyle.Flat;
            this.answer3.Font = new System.Drawing.Font("Showcard Gothic", 10F, System.Drawing.FontStyle.Bold);
            this.answer3.ForeColor = System.Drawing.Color.Yellow;
            this.answer3.Location = new System.Drawing.Point(158, 432);
            this.answer3.Name = "answer3";
            this.answer3.Size = new System.Drawing.Size(200, 150);
            this.answer3.TabIndex = 6;
            this.answer3.Text = "button3";
            this.answer3.UseVisualStyleBackColor = true;
            this.answer3.Click += new System.EventHandler(this.answer3_Click);
            // 
            // answer4
            // 
            this.answer4.FlatAppearance.BorderSize = 0;
            this.answer4.FlatStyle = System.Windows.Forms.FlatStyle.Flat;
            this.answer4.Font = new System.Drawing.Font("Showcard Gothic", 10F, System.Drawing.FontStyle.Bold);
            this.answer4.ForeColor = System.Drawing.Color.Lime;
            this.answer4.Location = new System.Drawing.Point(441, 432);
            this.answer4.Name = "answer4";
            this.answer4.Size = new System.Drawing.Size(200, 150);
            this.answer4.TabIndex = 7;
            this.answer4.Text = "button4";
            this.answer4.UseVisualStyleBackColor = true;
            this.answer4.Click += new System.EventHandler(this.answer4_Click);
            // 
            // NumberOfRightQuestions
            // 
            this.NumberOfRightQuestions.AutoSize = true;
            this.NumberOfRightQuestions.Font = new System.Drawing.Font("Showcard Gothic", 8F, System.Drawing.FontStyle.Bold);
            this.NumberOfRightQuestions.ForeColor = System.Drawing.Color.Purple;
            this.NumberOfRightQuestions.Location = new System.Drawing.Point(232, 48);
            this.NumberOfRightQuestions.Name = "NumberOfRightQuestions";
            this.NumberOfRightQuestions.Size = new System.Drawing.Size(68, 20);
            this.NumberOfRightQuestions.TabIndex = 8;
            this.NumberOfRightQuestions.Text = "label1";
            // 
            // NumberOfQuestionLeft
            // 
            this.NumberOfQuestionLeft.AutoSize = true;
            this.NumberOfQuestionLeft.Font = new System.Drawing.Font("Showcard Gothic", 8F, System.Drawing.FontStyle.Bold);
            this.NumberOfQuestionLeft.ForeColor = System.Drawing.Color.Purple;
            this.NumberOfQuestionLeft.Location = new System.Drawing.Point(54, 87);
            this.NumberOfQuestionLeft.Name = "NumberOfQuestionLeft";
            this.NumberOfQuestionLeft.Size = new System.Drawing.Size(68, 20);
            this.NumberOfQuestionLeft.TabIndex = 9;
            this.NumberOfQuestionLeft.Text = "label2";
            // 
            // GameQuestions
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(9F, 20F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.BackColor = System.Drawing.Color.DeepSkyBlue;
            this.ClientSize = new System.Drawing.Size(928, 744);
            this.Controls.Add(this.NumberOfQuestionLeft);
            this.Controls.Add(this.NumberOfRightQuestions);
            this.Controls.Add(this.answer4);
            this.Controls.Add(this.answer3);
            this.Controls.Add(this.answer2);
            this.Controls.Add(this.answer1);
            this.Controls.Add(this.timeToQuestionLabel);
            this.Controls.Add(this.rightQuestionsCountLabel);
            this.Controls.Add(this.questionsCountLabel);
            this.Controls.Add(this.questionLabel);
            this.Name = "GameQuestions";
            this.ShowIcon = false;
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.Label questionLabel;
        private System.Windows.Forms.Label questionsCountLabel;
        private System.Windows.Forms.Label rightQuestionsCountLabel;
        private System.Windows.Forms.Label timeToQuestionLabel;
        private System.Windows.Forms.Button answer2;
        private System.Windows.Forms.Button answer3;
        private System.Windows.Forms.Button answer4;
        private System.Windows.Forms.Button answer1;
        private System.Windows.Forms.Label NumberOfRightQuestions;
        private System.Windows.Forms.Label NumberOfQuestionLeft;
    }
}