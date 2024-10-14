#include <boost/program_options.hpp>
#include <fcntl.h>
#include <fstream>
#include <iostream>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>

struct Config {
  int criticalLevel;
  int batteryNumber;

  Config() : criticalLevel(15), batteryNumber(1) {} // Default values
};

std::string getBatteryStatus(int &capacity, int criticalLevel,
                             int batteryNumber) {
  std::string batteryPath = "/sys/class/power_supply/BAT" +
                            std::to_string(batteryNumber) + "/capacity";
  std::ifstream capacityFile(batteryPath);

  if (capacityFile.is_open()) {
    capacityFile >> capacity;
  }

  std::string status;
  if (capacity < criticalLevel) {
    status = "Critical";
  } else {
    status = "Normal";
  }

  return status;
}

void sendNotification() {
  system("notify-send -u critical 'Low Battery' 'Charge soon'");
}

void sendBatteryFull() {
  system("notify-send -u normal 'Battery Full' 'Battery at 100%'");
}

bool readLockState(const std::string &lockFilePath) {
  std::ifstream lockFile(lockFilePath);
  bool lockState = false;
  if (lockFile.is_open()) {
    lockFile >> lockState;
  }
  return lockState;
}

void writeLockState(const std::string &lockFilePath, bool lockState) {
  std::ofstream lockFile(lockFilePath, std::ios_base::trunc);
  lockFile << lockState;
}

Config readConfig(const std::string &configFilePath) {
  Config config;
  boost::program_options::options_description desc("Allowed options");
  desc.add_options()("critical_bat",
                     boost::program_options::value<int>(&config.criticalLevel),
                     "Critical battery level")(
      "bat", boost::program_options::value<int>(&config.batteryNumber),
      "Battery number");

  boost::program_options::variables_map vm;
  std::ifstream configFile(configFilePath);
  if (configFile) {
    boost::program_options::store(
        boost::program_options::parse_config_file(configFile, desc), vm);
    boost::program_options::notify(vm);
  }

  return config;
}

int main() {
  const char *homeDir = getenv("HOME");
  std::string logFilePath = std::string(homeDir) + "/.battery_monitor.log";
  std::string lockFilePath = std::string(homeDir) + "/.battery_monitor.lock";
  std::string configFilePath = std::string(homeDir) + "/.config/lowkey/config";
  std::ofstream logFile(logFilePath, std::ios_base::trunc);

  Config config = readConfig(configFilePath);

  int criticalLevel = config.criticalLevel;
  int batteryNumber = config.batteryNumber;
  bool lockState = readLockState(lockFilePath);

  int capacity = 0;
  std::string status = getBatteryStatus(capacity, criticalLevel, batteryNumber);

  logFile << "Battery Capacity: " << capacity << "%, Status: " << status
          << "\n";
  logFile.flush();

  if (capacity < criticalLevel && !lockState) {
    sendNotification();
    lockState = true;
    writeLockState(lockFilePath, lockState);
  } else if (capacity >= criticalLevel && lockState && capacity < 100) {
    lockState = false;
    writeLockState(lockFilePath, lockState);
  } else if (capacity == 100 && !lockState) {
    sendBatteryFull();
    lockState = true;
    writeLockState(lockFilePath, lockState);
  }

  std::cout << "Battery Capacity: " << capacity << "%, Status: " << status
            << std::endl;
  std::cout << "lockState: " << lockState << std::endl;
  std::cout << "Critical Level: " << criticalLevel << std::endl;
  std::cout << "Battery Number: " << batteryNumber << std::endl;

  return 0;
}
