using System;
using Lab3.Application;
using Lab3.Commands;

namespace Lab3
{
    class Program
    {
        static void Main(string[] args)
        {
            var service = new StudentService();
            Console.WriteLine("=== Student Records Management ===");
            while (true)
            {
                Console.Write("\nВведите команду [add, edit, view, exit]: ");
                string cmd = Console.ReadLine().Trim().ToLower();
                if (cmd == "exit")
                {
                    Console.WriteLine("Выход.");
                    break;
                }
                var command = CommandFactory.GetCommand(cmd, service);
                if (command != null)
                {
                    command.Execute();
                }
                else
                {
                    Console.WriteLine("Неизвестная команда.");
                }
            }
        }
    }
} 