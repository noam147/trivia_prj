import smtplib
from email.mime.text import MIMEText
import ssl
import sys


def send_email():
    # Define the sender and recipient
    me = 'triviaproject@outlook.co.il'
    you = 'noam24@zvialod.com'
    you = sys.argv[1]

    # Create the message
    msg = MIMEText("verification code: "+str(sys.argv[2]))

    # Set the email headers
    msg['Subject'] = 'Your Subject'
    msg['From'] = me
    msg['To'] = you

    # SMTP server configuration for Outlook
    smtp_server = "smtp.office365.com"
    port = 587  # For starttls
    password = "magshimim!1"

    # Create a secure SSL context
    context = ssl.create_default_context()

    try:
        # Connect to the server
        server = smtplib.SMTP(smtp_server, port)
        server.starttls(context=context)  # Secure the connection
        server.login(me, password)

        # Send the email
        server.sendmail(me, [you], msg.as_string())
        print("Email sent successfully")
    except Exception as e:
        print(e)
    finally:
        server.quit()


if __name__ == "__main__":
    send_email()
