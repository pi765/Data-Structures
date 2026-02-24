#include <iostream>
#include <string>
#include <sstream>
#include <fstream>

const int SIZE = 100; // size of array

using namespace std;

class Node
{
public:
   int k;      // key
   float v;    // value
   Node *next; // next
   Node(int key, float value, Node *ptr = 0)
   {
      k = key;
      v = value;
      next = ptr;
   }
};

class HashTable
{
public:
   Node **table;

   HashTable()
   {
      table = new Node *[SIZE];
      for (int i = 0; i < SIZE; i++)
         table[i] = NULL;
   }

   int Hash(string variable)
   {
      int sum = 0;
      int count = 1;
      for (int i = 0; i < variable.size(); i++)
      {
         int number;
         number = (int)variable[i];
         number = number * count;
         count++;
         sum = sum + number;
      }
      return sum % SIZE;
   }

   void Add(string variable, float value)
   {
      int index = Hash(variable); // calculate index
      Node *prev = NULL;
      Node *entry = table[index];

      while (entry != NULL)
      {
         prev = entry;
         entry = entry->next;
      }

      if (entry == NULL) // if there is no node, create one
      {
         entry = new Node(index, value);
         if (prev == NULL)
         {
            table[index] = entry;
         }
         else
         {
            prev->next = entry;
         }
      }
      else // insert value
      {
         entry->v = value;
      }
   }

   void Delete(string variable)
   {
      int index = Hash(variable);
      Node *entry = table[index];
      Node *prev = NULL;

      if (entry == NULL || entry->k != index) // no element at index
      {
         return;
      }

      while (entry->next != NULL) // move to bucket
      {
         prev = entry;
         entry = entry->next;
      }

      if (prev != NULL) // search list in bucket
      {
         prev->next = entry->next;
      }

      delete entry;
   }


   void print(string variable)
   {
      int index = Hash(variable);

      if (table[index] == NULL)
      {
         cout << variable << " IS UNDEFINED" << endl;
         return;
      }

      Node *entry = table[index];
      if (entry != NULL)
      {
         while (entry != NULL)
         {
            if (entry->k != index) // when there's no more value at the index
            {
               cout << variable << "IS UNDEFINED" << endl;
               return;
            }
            else
            {
               cout << variable << " IS " << entry->v << endl;
            }

            entry = entry->next; // move to the next entry
         }
      }
   }

   void maths(string variable, string op, int num)
   {
      int index = Hash(variable);

      if (table[index] == NULL)
      {
         cout << variable << " IS UNDEFINED" << endl;
         return;
      }

      Node *entry = table[index];
      if (entry != NULL)
      {
         while (entry != NULL)
         {
            if (entry->k != index)
            {
               cout << variable << " IS UNDEFINED" << endl;
               return;
            }
            else
            {
               if (op == "++")
               {
                  entry->v = entry->v + 1;
               }
               if (op == "--")
               {
                  entry->v = entry->v - 1;
               }
               if (op == "=")
               {
                  entry->v = num;
               }

               if (op == "+")
               {
                  cout << variable << " " << op << " " << num << " IS " << entry->v + num;
               }
               else if (op == "-")
               {
                  cout << variable << " " << op << " " << num << " IS " << entry->v - num;
               }
               else if (op == "/")
               {
                  cout << variable << " " << op << " " << num << " IS " << entry->v / num;
               }
               else if (op == "*")
               {
                  cout << variable << " " << op << " " << num << " IS " << entry->v * num;
               }
               else if (op == "%")
               {
                  int number = entry->v;
                  cout << variable << " " << op << " " << num << " IS " << number % num;
               }
               else if (op == "^")
               {
                  int number = entry->v;
                  int power = number;
                  for (int i = 0; i < num; i++)
                  {
                     power = power * number;
                  }
                  cout << variable << " " << op << " " << num << " IS " << power;
               }
            }

            entry = entry->next; // move to the next entry
         }
      }
   }
};
int main()
{
   ifstream file;
   file.open("borg.txt");

   HashTable menu;

   string line;
   string DeleteVariable;
   for (string line; getline(file, line);)
   {
      stringstream sentence; // create object
      string word;
      sentence << line;

      sentence >> word;
      if (word == "COM")
      {
      } // comment
      else if (word == "START"){}
      else if (word == "FINISH")
      {
         menu.Delete(DeleteVariable);
      }
      else if (word == "VAR")
      {
         string variable;
         sentence >> variable;
         DeleteVariable = variable;

         sentence >> word;

         if (word == "=")
         {
            sentence >> word;
            stringstream number(word);
            float num;
            if (number >> num)
            {
               menu.Add(variable, num);
            }
         }
      }
      else if (word == "PRINT")
      {
         string variable, op;
         sentence >> variable;
         sentence >> op;
         if (op == "+" || op == "-" || op == "/" || op == "*" || op == "%" || op == "^")
         {
            sentence >> word;
            stringstream number(word);
            int num;
            if (number >> num)
            {
               menu.maths(variable, op, num);
               cout << endl;
            }
         }
         else
            menu.print(variable);
      }
      else // ++ -- =
      {
         string op, integer;
         sentence >> op;

         if (op == "=")
         {
            sentence >> integer;
            stringstream number(integer);
            int num;
            if (number >> num)
            {
               menu.maths(word, op, num);
            }
         }
         else
         {
            int num; // placeholder number
            menu.maths(word, op, num);
         }
      }
   }

   return 0;
}

/* Output:
BORAMIR IS 25       
LEGOLAS IS 101      
GANDALF IS UNDEFINED
BORAMIR * 2 IS 52   
GANDALF IS 49       
BORAMIR IS 26       
GANDALF IS 49       
LEGOLAS IS 1000     
LEGOLAS IS 1000
LEGOLAS IS 999 */