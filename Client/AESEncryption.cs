using System;
using System.IO;
using System.Security.Cryptography;
using System.Text;

namespace clientGuiTrivia
{
    public class AesEncryption
    {
        // Key and IV should be the same for both encryption and decryption
        private static readonly byte[] key = Encoding.UTF8.GetBytes("0123456789abcdef"); // 16 bytes for AES-128
        private static readonly byte[] iv = Encoding.UTF8.GetBytes("1234567890abcdef"); // 16 bytes for the IV


        public static void Encrypt(ref string Text)
        {
            using (Aes aesAlg = Aes.Create())
            {
                aesAlg.Key = key;
                aesAlg.IV = iv;

                ICryptoTransform encryptor = aesAlg.CreateEncryptor(aesAlg.Key, aesAlg.IV);
                aesAlg.Padding = PaddingMode.PKCS7;

                using (MemoryStream msEncrypt = new MemoryStream())
                {
                    using (CryptoStream csEncrypt = new CryptoStream(msEncrypt, encryptor, CryptoStreamMode.Write))
                    {
                        using (StreamWriter swEncrypt = new StreamWriter(csEncrypt))
                        {
                            swEncrypt.Write(Text);
                        }
                    }

                    Text = ByteArrayToHexString(msEncrypt.ToArray());
                }
            }
        }


        private static string ByteArrayToHexString(byte[] byteArray)
        {
            StringBuilder hex = new StringBuilder(byteArray.Length * 2);
            foreach (byte b in byteArray)
            {
                hex.AppendFormat("{0:x2}", b);
            }
            return hex.ToString();
        }

        public static string Decrypt(string encryptedHex)
        {
            if (encryptedHex == null || encryptedHex.Length <= 0)
                throw new ArgumentNullException(nameof(encryptedHex));
            if (key == null || key.Length <= 0)
                throw new ArgumentNullException(nameof(key));
            if (iv == null || iv.Length <= 0)
                throw new ArgumentNullException(nameof(iv));

            try
            {
                // Convert hexadecimal ciphertext to byte array
                byte[] encryptedBytes = HexToByteArray(encryptedHex);

                // Create AES decryptor
                using (Aes aesAlg = Aes.Create())
                {
                    aesAlg.Key = key;
                    aesAlg.IV = iv;
                    aesAlg.Padding = PaddingMode.PKCS7;

                    ICryptoTransform decryptor = aesAlg.CreateDecryptor(aesAlg.Key, aesAlg.IV);

                    // Decrypt ciphertext
                    using (MemoryStream msDecrypt = new MemoryStream(encryptedBytes))
                    {
                        using (CryptoStream csDecrypt = new CryptoStream(msDecrypt, decryptor, CryptoStreamMode.Read))
                        {
                            using (StreamReader srDecrypt = new StreamReader(csDecrypt))
                            {
                                return srDecrypt.ReadToEnd();
                            }
                        }
                    }
                }
            }
            catch (Exception ex)
            {
                Console.WriteLine($"Error during decryption: {ex.Message}");
                return null;
            }
        }

        // Helper method to convert hexadecimal string to byte array
        public static byte[] HexToByteArray(string hex)
        {
            int numberChars = hex.Length;
            byte[] bytes = new byte[numberChars / 2];
            System.Console.WriteLine("length: " + hex);
            for (int i = 0; i < numberChars; i += 2)
            {
                bytes[i / 2] = Convert.ToByte(hex.Substring(i, 2), 16);
            }
            return bytes;
        }

    }
}