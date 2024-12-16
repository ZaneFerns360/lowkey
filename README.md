# lowkey

A sleek and efficient battery notification daemon for Linux systems.

## Features

- Real-time battery status monitoring
- Low battery notifications
- Customizable notification thresholds
- Lightweight and resource-efficient

## Prerequisites

Before you begin, ensure you have met the following requirements:

- CMake (3.10 or higher)
- Boost libs
- libnotify
- D-Bus
- A notification manager (e.g., dunst or mako)

## Installation

### AUR-

   ```
   yay -S lowkey
   ```

### Using an installation script

To install lowkey on your system, use the installation script:

   ```
   bash <(curl -L https://raw.githubusercontent.com/ZaneFerns360/lowkey/main/install.sh)
   ```

## Uninstallation

To remove lowkey from your system, use the uninstallation script:

```
bash <(curl -L https://raw.githubusercontent.com/ZaneFerns360/lowkey/main/uninstall.sh)
```

## Usage

Once installed, lowkey will run as a daemon. You can configure its behavior by editing the configuration file located at `~/.config/lowkey/config`.

## Contributing

Contributions to lowkey are welcome! Here's how you can contribute:

1. Fork the repository
2. Create a new branch (`git checkout -b feature/amazing-feature`)
3. Make your changes
4. Commit your changes (`git commit -m 'Add some amazing feature'`)
5. Push to the branch (`git push origin feature/amazing-feature`)
6. Open a Pull Request

## License

This project is licensed under the MIT License - see the [LICENSE](LICENSE) file for details.

## Contact

If you have any questions or feedback, please open an issue on the GitHub repository.

## Acknowledgements

- [Boost](https://www.boost.org/)
- [libnotify](https://developer.gnome.org/libnotify/)
- [D-Bus](https://www.freedesktop.org/wiki/Software/dbus/)
- [dunst](https://dunst-project.org/) / [mako](https://github.com/emersion/mako)


Lowkey uses a simple configuration file located at `~/.config/lowkey/config`. This file allows you to customize the behavior of the battery monitoring daemon.

Here's an example of the configuration file:

```
# Lowkey Configuration File
# Set the critical battery level (in percentage)
critical_bat=25
# Set the battery number to monitor
bat=1
```

### Configuration Options

- `critical_bat`: This sets the battery percentage at which lowkey will send a critical battery notification. In the example, it's set to 25%.
- `bat`: This specifies which battery to monitor if your system has multiple batteries. It's set to 1 in the example, which typically corresponds to the main battery.

### Editing the Configuration

To modify the configuration:

1. Open the configuration file in your preferred text editor:
   ```
   nano ~/.config/lowkey/config
   ```

2. Adjust the values as needed. For example, to change the critical battery level to 20% and monitor battery 2:
   ```
   critical_bat=20
   bat=1
   ```

3. Save the file and exit the editor.

Remember to use whole numbers for the percentage and battery number. If you're unsure about which battery number to use, you can check the available batteries in your system by looking at the contents of the `/sys/class/power_supply/` directory.

