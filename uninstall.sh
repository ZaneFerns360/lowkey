#!/usr/bin/zsh

PROJECT_DIR="$(dirname "$(realpath "$0")")"
BUILD_DIR="$PROJECT_DIR/build"

uninstall_project() {
    echo "Uninstalling the project..."
    sudo systemctl disable battery-monitor.service
    sudo systemctl stop battery-monitor.service
    sudo systemctl daemon-reload
    sudo cmake --build build --target uninstall
}

uninstall_project
