using Lab3.Application;

namespace Lab3.Commands
{
    public static class CommandFactory
    {
        public static Command GetCommand(string cmdName, StudentService service)
        {
            switch (cmdName)
            {
                case "add":
                    return new AddStudentCommand(service);
                case "edit":
                    return new EditStudentCommand(service);
                case "view":
                    return new ViewStudentsCommand(service);
                default:
                    return null;
            }
        }
    }
} 