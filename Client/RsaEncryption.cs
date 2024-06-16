using System;
using System.Security.Cryptography;
using System.Text;

public static class RSAEncryptionUtility
{
    private static RSACryptoServiceProvider rsa;

    static RSAEncryptionUtility()
    {
        // Initialize RSACryptoServiceProvider with key size
        rsa = new RSACryptoServiceProvider();
    }

    // Function to encrypt a string using RSA
    public static void Encrypt(ref string text)
    {
        try
        {
            // Use the public key for encryption
            string publicKey = rsa.ToXmlString(false);

            // Convert the text to bytes
            byte[] bytesToEncrypt = Encoding.UTF8.GetBytes(text);

            // Encrypt the bytes
            byte[] encryptedBytes = rsa.Encrypt(bytesToEncrypt, true);

            // Convert encrypted bytes to Base64 for easier storage/transmission
            text = Convert.ToBase64String(encryptedBytes);
        }
        catch (CryptographicException e)
        {
            Console.WriteLine("RSA encryption error: " + e.Message);
        }
    }

    // Function to decrypt a string using RSA
    public static string Decrypt(string encryptedBase64)
    {
        try
        {
            // Use the private key for decryption (assuming you have access to the private key)
            string privateKey = rsa.ToXmlString(true);

            // Convert the Base64 encrypted string back to bytes
            byte[] encryptedBytes = Convert.FromBase64String(encryptedBase64);

            // Decrypt the bytes
            byte[] decryptedBytes = rsa.Decrypt(encryptedBytes, true);

            // Convert decrypted bytes back to string
            string decryptedText = Encoding.UTF8.GetString(decryptedBytes);

            return decryptedText;
        }
        catch (CryptographicException e)
        {
            Console.WriteLine("RSA decryption error: " + e.Message);
            return null; // Or handle the error as per your application's logic
        }
    }
}
