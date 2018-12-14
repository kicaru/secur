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

        static string xorconcpt(string p,string key)
        {
            int pen2 = Convert.ToInt32((p.Substring(8)), 2);
            int key1 = Convert.ToInt32((key.Substring(0,8)), 2);
            int key2 = Convert.ToInt32((key.Substring(8)), 2);
            int pen1 = Convert.ToInt32((p.Substring(0, 8)), 2);
            pen1 ^= key1;
            pen2 ^= key2;
            string part1 = Convert.ToString(pen1, 2);
            string part2 = Convert.ToString(pen2, 2);
            part1 = part1.PadLeft(8, '0');
            part2 = part2.PadLeft(8, '0');
            Console.WriteLine(part1+part2);
            int temp1 = Convert.ToInt16(part1,2);
            int temp2 = Convert.ToInt16(part2,2);
            char character = (char)(temp1);
            char character1 = (char)(temp2);
            string text = character.ToString();
            text += character1.ToString();
            return text;
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

                myByte = myByte.PadLeft(8, '0');
                
                sumbytes += myByte;
                myByte = null;
            }
            return sumbytes;
        }

        static string shiftbit(string p)
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
        
        static string Vigenere(string p)
        {

            string[,] vir_table = new string[,]{ { "0010", "1100", "0100", "0001", "0111", "1010", "1011", "0110", "1000", "0101", "0011", "1111", "1101", "0000", "1110", "1001" },
                                  { "1110","1011" ,"0010","1100","0100","0111","1101","0001","0101","0000","1111","1010","0011","1001","1000","0110"},
                                  {  "0100","0010" ,"0001","1011","1010","1101","0111","1000","1111","1001","1101","0101","0110","0011","0000","1110"},
                                  {  "1011","1000" ,"1100","0111","0001","1110","0010","1101","0110","1111","0000","1001","1010","0100","0101","0011"} };
            string sum = null;
            string temp = null;
            string part = p.Substring(0, 8);
            int i = 0;
            while (i<2) {
                
                string a = part.Substring(0, 2);
                string b = part.Substring(4);
                int strA = Convert.ToInt32(a, 2);
                int strB = Convert.ToInt32(b, 2);
             
                temp = part.Substring(0,4)+vir_table[strA,strB];
                sum += temp;
                part = p.Substring(8);
                i++;
            }
            return sum;
        } 

        static void Main(string[] args)
        {
            string p,k;
            string sumbit,sum,sumkey;

            String sumall= null;
            Console.WriteLine("input string");
            p=Console.ReadLine();
            Console.WriteLine("input key");
            k = Console.ReadLine();
            for (int i = 0; i < p.Length; i += k.Length)
            {
                sum = sbstr(p, k.Length, i);
                sumbit = Tobytes(sum);
                Console.WriteLine("Convert text to binary : {0}",sumbit);
                sum = shiftbit(sumbit);
                Console.WriteLine("shift left 3 bit: {0}",sum);
                sum = tranposition(sum);
                Console.WriteLine("tranposition bit : {0}",sum);
                sum = Vigenere(sum);
                Console.WriteLine("substition bit : {0}", sum);
                sumkey = Tobytes(k);
                Console.WriteLine("Convert key to binary : {0}",sumkey);
                sum=xorconcpt(sum, sumkey);
                Console.WriteLine("XOR : {0}",sum);
                sumall += sum;
                
            }
            Console.WriteLine("sum {0}", sumall);
        }

    }
}
