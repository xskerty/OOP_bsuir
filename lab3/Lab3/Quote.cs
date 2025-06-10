using System;

namespace Lab3.Domain
{
    public class Quote
    {
        public string Content { get; private set; }
        public string Author { get; private set; }

        public Quote(string content, string author)
        {
            if (string.IsNullOrEmpty(content))
                throw new ArgumentException("Quote content cannot be empty", nameof(content));
            Content = content;
            Author = string.IsNullOrEmpty(author) ? "Unknown" : author;
        }
    }
} 