class LoginMessage:

    def __init__(self):
        self.username = None
        self.password = None
        self._getValues()

    def _getValues(self):
        self.username = input("Enter username: ")
        self.password = input("Enter password: ")

    def get_username(self):
        return self.username

    def set_username(self, username: str):
        self.username = username

    def get_password(self):
        return self.password

    def set_password(self, password: str):
        self.password = password


class SignupMessage:
    def __init__(self):
        self.username = None
        self.password = None
        self.mail = None
        self._getValues()

    def _getValues(self):
        self.set_username(input("Enter username: "))
        self.set_password(input("Enter password: "))
        self.set_mail(input("Enter mail: "))

    def get_username(self):
        return self.username

    def set_username(self, username: str):
        self.username = username

    def get_password(self):
        return self.password

    def set_password(self, password: str):
        self.password = password

    def get_username(self):
        return self.mail

    def set_mail(self, mail: str):
        self.mail = mail
