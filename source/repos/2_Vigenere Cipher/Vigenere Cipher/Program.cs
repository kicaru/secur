using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Vigenere_Cipher
{
    class Program
    {
        static string Sbstring(string p,string k)
        {
            while (p.Length > k.Length)
            {
                k += k;
            }
            return k;

        }
        
        static string Encryption(string p, string k)
        {
            string C = null;
            int temp1 = 0;
            int temp2 = 0;
            int count =0;
            while (count < p.Length)
            {
                temp1 = System.Convert.ToInt16(p[count])-97;
                temp2 = System.Convert.ToInt16(k[count])-97;
                char character = (char)(((temp1 + temp2) % 26)+97);
                string text = character.ToString();
                C += text;
                count++;
            }

            return C;
        }
        
        static string Decryption(string c, string k)
        {
            string C = null;
            int temp1 = 0;
            int temp2 = 0;
            int count =0;
            while (count < c.Length)
            {
                temp1 = System.Convert.ToInt16(c[count])-97;
                temp2 = System.Convert.ToInt16(k[count])-97;
                temp2 = temp1 - temp2;
                if (temp2 < 0)
                {
                    temp2 *= -1;
                    temp2 = 26 - temp2;
                }
                char character = (char)((temp2 % 26)+97);
                string text = character.ToString();
                C += text;
                count++;
            }

            return C;
        }
        
        static void Main(string[] args)
        {
            String p,k,c;
            Console.WriteLine("Input Plainttext");
            p=Console.ReadLine();
            Console.WriteLine("Input Key");
            k =Console.ReadLine();
            k = Sbstring(p, k);
            //Console.WriteLine(k);
           // char character = (char)(97);
            //string text = character.ToString();
            //Console.WriteLine(text);
            c = Encryption(p, k);
            Console.WriteLine("Encryption : {0}",c);
            p = Decryption(c, k);
            Console.WriteLine("Decryption : {0}", p);
        }
    }
}

