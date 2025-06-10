using System;
using Lab3.Application;

namespace Lab3.Commands
{
    public abstract class Command
    {
        public abstract void Execute();
    }

    public class AddStudentCommand : Command
    {
        private readonly StudentService _service;

        public AddStudentCommand(StudentService service)
        {
            _service = service;
        }

        public override async void Execute()
        {
            Console.Write("Имя студента: ");
            string name = Console.ReadLine().Trim();
            Console.Write("Оценка (0–100): ");
            if (double.TryParse(Console.ReadLine().Trim(), out double grade))
            {
                var dto = new DTO.StudentDTO { Name = name, Grade = grade };
                try
                {
                    var quote = await _service.AddStudentAsync(dto);
                    Console.WriteLine($"Студент добавлен! Мотивационная цитата:\n\"{quote.Content}\" — {quote.Author}");
                }
                catch (Exception ex)
                {
                    Console.WriteLine($"Ошибка: {ex.Message}");
                }
            }
            else
            {
                Console.WriteLine("Ошибка: неверный формат оценки.");
            }
        }
    }

    public class EditStudentCommand : Command
    {
        private readonly StudentService _service;

        public EditStudentCommand(StudentService service)
        {
            _service = service;
        }

        public override void Execute()
        {
            Console.Write("Индекс студента для редактирования: ");
            if (int.TryParse(Console.ReadLine().Trim(), out int idx))
            {
                Console.Write("Новое имя: ");
                string name = Console.ReadLine().Trim();
                Console.Write("Новая оценка (0–100): ");
                if (double.TryParse(Console.ReadLine().Trim(), out double grade))
                {
                    var dto = new DTO.StudentDTO { Name = name, Grade = grade };
                    try
                    {
                        _service.EditStudent(idx, dto);
                        Console.WriteLine("Студент обновлен.");
                    }
                    catch (Exception ex)
                    {
                        Console.WriteLine($"Ошибка: {ex.Message}");
                    }
                }
                else
                {
                    Console.WriteLine("Ошибка: неверный формат оценки.");
                }
            }
            else
            {
                Console.WriteLine("Ошибка: неверный формат индекса.");
            }
        }
    }

    public class ViewStudentsCommand : Command
    {
        private readonly StudentService _service;

        public ViewStudentsCommand(StudentService service)
        {
            _service = service;
        }

        public override void Execute()
        {
            var students = _service.ListStudents();
            if (students.Count == 0)
            {
                Console.WriteLine("Список студентов пуст.");
            }
            else
            {
                for (int i = 0; i < students.Count; i++)
                {
                    Console.WriteLine($"[{i}] {students[i].Name} — {students[i].Grade}");
                }
            }
        }
    }
} 