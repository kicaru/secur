using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace bite_overall
{
    class Program
    {
        static string sbstr(string p, int k, int count)
        {
            string value = p.Substring(count, k);
            return value;
        }

        static string Tobytes(string p)
        {
            string myByte=null;
            string sumbytes = null; 
         for(int j = 0; j < p.Length; j++)
            {
               
                byte[] bytes = Encoding.ASCII.GetBytes(p[j].ToString());
                foreach (byte b in bytes)
                {
                    myByte += Convert.ToString(b, 2);

                }
                if (myByte.Length < 8)
                {
                    for (int i = 0; i < (8 - myByte.Length); i++)
                    {
                        myByte = '0' + myByte;
                    }
                }
                sumbytes += myByte;
                myByte = null;
            }
            return sumbytes;
        }

        static string subsub(string p)
        {
            string sum1 = null; 
            string sum2 = null;
            sum1 = p.Substring(0, 3);
            sum2 = p.Substring(3);
            sum1 = sum2 + sum1;
            return sum1;
        }

        static string tranposition(string p)
        {
            string sum = null;
            for(int i = 0; i < p.Length; i += 2)
            {
                sum += p[i + 1];
                sum += p[i];
            }
            return sum;
        }

        static string Vigenere()
        {
            string[] table = {  "0000", "0001", "0010", "0011", "0100", "0101", "0110", "0111", "1000", "1001", "1010", "1011", "1100", "1101", "1110", "1111" } ;

            string[,] vir_table = new string[,]{ { "0010", "1100", "0100", "0001", "0111", "1010", "1011", "0110", "1000", "0101", "0011", "1111", "1101", "0000", "1110", "1001" },
                                  { "1110","1011" ,"0010","1100","0100","0111","1101","0001","0101","0000","1111","1010","0011","1001","1000","0110"},
                                  {  "0100","0010" ,"0001","1011","1010","1101","0111","1000","1111","1001","1101","0101","0110","0011","0000","1110"},
                                  {  "1011","1000" ,"1100","0111","0001","1110","0010","1101","0110","1111","0000","1001","1010","0100","0101","0011"} };
                                        

            return
        }

      static void Main(string[] args)
        {
            string p,k;
            string sumbit,sum;
            

            Console.WriteLine("input string");
            p=Console.ReadLine();
            Console.WriteLine("input key");
            k = Console.ReadLine();
            for (int i = 0; i < p.Length; i += k.Length)
            {
                sum = sbstr(p, k.Length, i);
                sumbit = Tobytes(sum);
                Console.WriteLine(sumbit);
                sum = subsub(sumbit);
                Console.WriteLine(sum);
                sum = tranposition(sum);
                Console.WriteLine(sum);
                Random r = new Random();
               

            }
        }

    }
}

// Console.WriteLine(myByte);