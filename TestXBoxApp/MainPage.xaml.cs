using System;
using System.Collections.Generic;
using System.IO;
using System.Linq;
using System.Runtime.InteropServices.WindowsRuntime;
using System.Text;
using System.Threading.Tasks;
using Windows.Foundation;
using Windows.Foundation.Collections;
using Windows.Gaming.Input;
using Windows.System;
using Windows.UI.Core;
using Windows.UI.Xaml;
using Windows.UI.Xaml.Controls;
using Windows.UI.Xaml.Controls.Primitives;
using Windows.UI.Xaml.Data;
using Windows.UI.Xaml.Input;
using Windows.UI.Xaml.Media;
using Windows.UI.Xaml.Navigation;

// The Blank Page item template is documented at https://go.microsoft.com/fwlink/?LinkId=402352&clcid=0x409

namespace TestXBoxApp
{
    /// <summary>
    /// An empty page that can be used on its own or navigated to within a Frame.
    /// </summary>
    public sealed partial class MainPage : Page
    {
        private List<Gamepad> m_gamepads = new List<Gamepad>();
        private readonly object m_gamepadLock = new object();
        private volatile bool m_running;
        private volatile Task m_pollTask;

        public MainPage()
        {
            this.InitializeComponent();

            this.InitializeGamepads();

            SystemNavigationManager.GetForCurrentView().BackRequested += OnBackRequested;
        }

        private void InitializeGamepads()
        {
            lock (m_gamepadLock)
            {
                foreach (var gamepad in Gamepad.Gamepads)
                {
                    AddGamepad(gamepad);
                }
            }

            Gamepad.GamepadAdded += Gamepad_GamepadAdded;
            Gamepad.GamepadRemoved += Gamepad_GamepadRemoved;
        }

        private void Gamepad_GamepadAdded(object sender, Gamepad gamepad)
        {
            AddGamepad(gamepad);
        }

        private void Gamepad_GamepadRemoved(object sender, Gamepad gamepad)
        {
            RemoveGamepad(gamepad);
        }

        private void AddGamepad(Gamepad gamepad)
        {
            lock (m_gamepadLock)
            {
                if (m_gamepads.Contains(gamepad)) return;
                m_gamepads.Add(gamepad);
                StartPollingGamepads();
            }
        }

        private void RemoveGamepad(Gamepad gamepad)
        {
            lock (m_gamepadLock)
            {
                m_gamepads.Remove(gamepad);
                StopPollingGamepads();
            }
        }

        private string GetControllerStateText()
        {
            StringBuilder sb = new StringBuilder();

            float deadzone = .1f;

            lock (m_gamepadLock)
            {
                for (var q = 0; q < m_gamepads.Count; q++)
                {
                    if (q != 0) sb.Append("\r\n");
                    sb.Append($"Controller: {q + 1}\r\n");

                    var gamepad = m_gamepads[q];
                    var reading = gamepad.GetCurrentReading();

                    sb.Append($"Left thumbstick: {FormatDeadzone(reading.LeftThumbstickX, deadzone)}, {FormatDeadzone(reading.LeftThumbstickY, deadzone)}\r\n");
                    sb.Append($"Right thumbstick: {FormatDeadzone(reading.RightThumbstickX, deadzone)}, {FormatDeadzone(reading.RightThumbstickY, deadzone)}\r\n");
                    sb.Append($"Left trigger: {FormatDeadzone(reading.LeftTrigger, deadzone)}\r\n");
                    sb.Append($"Right trigger: {FormatDeadzone(reading.RightTrigger, deadzone)}\r\n");

                    var pressedButtons = Enum.GetValues(typeof(GamepadButtons))
                                             .Cast<GamepadButtons>()
                                             .Where(btn => (reading.Buttons & btn) != 0)
                                             .Select(btn => Enum.GetName(typeof(GamepadButtons), btn))
                                             .DefaultIfEmpty()
                                             .Select(name => name ?? "None");
                    sb.Append($"Buttons: {string.Join(", ", pressedButtons)}\r\n");
                }

                if (m_gamepads.Count == 0)
                {
                    sb.Append("No controllers connected.\r\n");
                }
            }

            return sb.ToString();
        }

        private string FormatDeadzone(double value, float deadzone)
        {
            if (value < deadzone && value > -deadzone) return "0";

            return $"{value:0.00}";
        }

        private void StartPollingGamepads()
        {
            lock (m_gamepadLock)
            {
                if (m_running) return;

                m_running = true;
                m_pollTask = Task.Run(PollGamepad);
            }
        }

        private void StopPollingGamepads()
        {
            lock (m_gamepadLock)
            {
                if (!m_running || m_pollTask == null) return;

                m_running = false;
            }

            m_pollTask.Wait();
            m_pollTask = null;
        }

        private async Task PollGamepad()
        {
            while (true)
            {
                string controllerStateText;

                lock (m_gamepadLock)
                {
                    if (!m_running) break;

                    controllerStateText = GetControllerStateText();
                }

                await Dispatcher.RunAsync(CoreDispatcherPriority.High, () =>
                {
                    ControllerState.Text = controllerStateText;
                });

                await Task.Delay(1000 / 30);
            }
        }

        private void OnBackRequested(object sender, BackRequestedEventArgs e)
        {
            e.Handled = true;
        }
    }
}
