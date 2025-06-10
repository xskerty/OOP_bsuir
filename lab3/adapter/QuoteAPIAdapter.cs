using System;
using System.Net.Http;
using System.Threading.Tasks;
using Lab3.DTO;
using System.Text.Json;

namespace Lab3.Adapter
{
    public class QuoteAPIAdapter
    {
        private const string API_URL = "https://api.quotable.io/random";
        private readonly HttpClient _httpClient;

        public QuoteAPIAdapter()
        {
            _httpClient = new HttpClient();
            _httpClient.DefaultRequestHeaders.Add("Accept", "application/json");
        }

        public async Task<QuoteDTO> FetchQuoteAsync()
        {
            try
            {
                var response = await _httpClient.GetStringAsync(API_URL);
                var data = JsonSerializer.Deserialize<JsonElement>(response);
                
                return new QuoteDTO
                {
                    Content = data.GetProperty("content").GetString() ?? "Stay motivated!",
                    Author = data.GetProperty("author").GetString() ?? "Unknown"
                };
            }
            catch (Exception ex)
            {
                Console.WriteLine($"(Не удалось получить цитату: {ex.GetType().Name})");
                return new QuoteDTO
                {
                    Content = "Не сдавайся — впереди только лучшее!",
                    Author = "Система"
                };
            }
        }
    }
} 