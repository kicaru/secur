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
            }
        }
    }
}

// Console.WriteLine(myByte);