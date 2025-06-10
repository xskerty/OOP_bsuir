using System;

namespace Lab3.Domain
{
    public class Student
    {
        public string Name { get; private set; }
        public double Grade { get; private set; }

        public Student(string name, double grade)
        {
            if (string.IsNullOrWhiteSpace(name))
                throw new ArgumentException("Name cannot be empty", nameof(name));
            if (grade < 0 || grade > 100)
                throw new ArgumentException("Grade must be between 0 and 100", nameof(grade));
            Name = name;
            Grade = grade;
        }
    }
} 