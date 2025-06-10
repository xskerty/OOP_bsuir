using System;
using System.Collections.Generic;
using System.IO;
using System.Text.Json;
using Lab3.Domain;

namespace Lab3.DataAccess
{
    public class StudentRepository
    {
        private readonly string _path;
        private List<Student> _data;

        public StudentRepository(string path = "students.json")
        {
            _path = path;
            LoadData();
        }

        private void LoadData()
        {
            try
            {
                if (File.Exists(_path))
                {
                    string json = File.ReadAllText(_path);
                    var items = JsonSerializer.Deserialize<List<Dictionary<string, object>>>(json);
                    _data = new List<Student>();
                    foreach (var item in items)
                    {
                        string name = item["name"].ToString();
                        double grade = Convert.ToDouble(item["grade"]);
                        _data.Add(new Student(name, grade));
                    }
                }
                else
                {
                    _data = new List<Student>();
                }
            }
            catch (Exception)
            {
                _data = new List<Student>();
            }
        }

        private void SaveData()
        {
            var items = new List<Dictionary<string, object>>();
            foreach (var student in _data)
            {
                items.Add(new Dictionary<string, object>
                {
                    { "name", student.Name },
                    { "grade", student.Grade }
                });
            }
            string json = JsonSerializer.Serialize(items, new JsonSerializerOptions { WriteIndented = true });
            File.WriteAllText(_path, json);
        }

        public void Add(Student student)
        {
            _data.Add(student);
            SaveData();
        }

        public void Update(int index, Student student)
        {
            if (index >= 0 && index < _data.Count)
            {
                _data[index] = student;
                SaveData();
            }
            else
            {
                throw new IndexOutOfRangeException("Student not found");
            }
        }

        public List<Student> ListAll()
        {
            return new List<Student>(_data);
        }
    }
} 