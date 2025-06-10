using Lab3.DTO;
using Lab3.Domain;

namespace Lab3.Factory
{
    public static class EntityFactory
    {
        public static Student CreateStudent(StudentDTO dto)
        {
            return new Student(dto.Name, dto.Grade);
        }

        public static Quote CreateQuote(QuoteDTO dto)
        {
            return new Quote(dto.Content, dto.Author);
        }
    }
} 