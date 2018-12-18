using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace ConsoleApp2
{
    class Program
    {
       /* static string ArValue()
        {
            string ary=null;
            for (int i = 65; i < (65 + 26); i++)
            {
                char character = (char)i;
                string text = character.ToString();
                ary +=text;
             
            }
            return ary;
        }  */

            static string Encryption(string p,int k)
            {
                string C=null;
            int temp=0;
            foreach(char c in p)
            {
                temp = System.Convert.ToInt16(c) + k;
                if (temp > 122)
                {
                    temp =(temp-96) % 26;
                    temp = temp + 96;
                }
                char character = (char)(temp);
                string text = character.ToString();
                C += text;
            }
                
                return C;
            }

        static string Decryption(string p, int k)
        {
            string C = null;
            int temp = 0;
            foreach (char c in p)
            {
                temp = System.Convert.ToInt16(c) - k;
                if (temp<97)
                {
                    temp = (96-temp) % 26;
                    temp = 122-temp;
                }
                char character = (char)(temp);
                string text = character.ToString();
                C += text;
            }

            return C;
        }


        static void Main(string[] args)
        {

            //string ary;
            string P;
            int K;
            string Ci;
            
            //ary = ArValue();
            Console.WriteLine("Input PintText");
            P = Console.ReadLine();
            Console.WriteLine("Input Key");
            K = Convert.ToInt32(Console.ReadLine()); ;
            Ci = Encryption(P, K);
            Console.WriteLine("Encryption : {0}",Ci);
            Ci = Decryption(Ci, K);
            Console.WriteLine("Decryption : {0}", Ci);

            // Go to http://aka.ms/dotnet-get-started-console to continue learning how to build a console app! 
        }
    }
}
