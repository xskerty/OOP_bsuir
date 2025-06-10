using System;
using System.Threading.Tasks;
using Lab3.DTO;
using Lab3.Domain;
using Lab3.Factory;
using Lab3.DataAccess;
using Lab3.Adapter;

namespace Lab3.Application
{
    public class StudentService
    {
        private readonly StudentRepository _repo;
        private readonly QuoteAPIAdapter _quoteAdapter;

        public StudentService()
        {
            _repo = new StudentRepository();
            _quoteAdapter = new QuoteAPIAdapter();
        }

        public async Task<Quote> AddStudentAsync(StudentDTO dto)
        {
            Student student = EntityFactory.CreateStudent(dto);
            _repo.Add(student);

            try
            {
                var quoteDto = await _quoteAdapter.FetchQuoteAsync();
                return EntityFactory.CreateQuote(quoteDto);
            }
            catch (Exception ex)
            {
                Console.WriteLine($"(Не удалось получить цитату: {ex.GetType().Name})");
                var fallback = new QuoteDTO
                {
                    Content = "Не сдавайся — впереди только лучшее!",
                    Author = "Система"
                };
                return EntityFactory.CreateQuote(fallback);
            }
        }

        public void EditStudent(int index, StudentDTO dto)
        {
            Student student = EntityFactory.CreateStudent(dto);
            _repo.Update(index, student);
        }

        public System.Collections.Generic.List<Student> ListStudents()
        {
            return _repo.ListAll();
        }
    }
} 