using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Permutation
{
    class Program
    {
        static string sbstr(string p,int k,int count)
        {
            string value = p.Substring(count,k);
            return value;
        }

        static string Encryption(string sub, string k){
            string value=null;
            int j = 0;
            for(int i = 0; i < k.Length; i++)
            {
                j = (int)char.GetNumericValue(k[i]);
                value += sub[j-1];
            }
        return value;
        }

        static string Decryption(string sub, string k)
        {
            string value = null;
            int j = 0;
            for (int i = 0; i < k.Length; i++)
            {
                j = (int)char.GetNumericValue(k[i]);
                value += sub[j - 1];
            }
            return value;
        }

        static void Main(string[] args)
        {
            string p;
            string k;
            string sub=null;
            string sub2;
            string temp =null;
            string ecyp = null;
            string dcyp = null;
            int bi = 0;
            Console.WriteLine("input painttext");
            p = Console.ReadLine();
            Console.WriteLine("input key");
            k = Console.ReadLine();
            bi = p.Length / k.Length;
            for(int i = 0; i < p.Length; i += k.Length)
            {
                
                ecyp += Encryption(sub, k);
                temp = ecyp;
                
            }
            Console.WriteLine("Encryption : {0}", ecyp);

          
            Console.WriteLine("input key");
            k = Console.ReadLine();
            for (int i = 0; i < p.Length; i += k.Length)
            {
                sub2 = sbstr(temp, k.Length, i);
                dcyp += Decryption(sub2, k);
            }
            Console.WriteLine("Decryption : {0}", dcyp);
        } 
    }
}
