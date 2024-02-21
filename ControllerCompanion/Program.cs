using ControllerCompanion.Enums;
using ControllerCompanion.Views;
using System.Runtime.InteropServices;

namespace ControllerCompanion
{
    internal static class Program
    {
        /// <summary>
        ///  The main entry point for the application.
        /// </summary>
        [STAThread]
        static void Main()
        {
            // To customize application configuration such as set high DPI settings or default font,
            // see https://aka.ms/applicationconfiguration.
            ApplicationConfiguration.Initialize();
            AllocConsole();
            ChannelInputTypes.PopulateInputTypes();
            Application.Run(new Form1());
        }

        [DllImport("kernel32.dll", SetLastError = true)]
        [return: MarshalAs(UnmanagedType.Bool)]
        static extern bool AllocConsole();
    }
}