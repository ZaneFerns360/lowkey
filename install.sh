#!/usr/bin/env bash

PROJECT_DIR="$(dirname "$(realpath "$0")")"
BUILD_DIR="$PROJECT_DIR/build"

uninstall_project() {
    echo "Uninstalling the project..."
    sudo systemctl disable battery-monitor.service
    sudo systemctl stop battery-monitor.service
    sudo systemctl daemon-reload
    sudo cmake --build build --target uninstall
}

install_project() {
    echo "Reinstalling the project..."
    mkdir -p "$BUILD_DIR"
    cd "$BUILD_DIR" || exit
    cmake ..
    make
    sudo make install
    if [ $? -eq 0 ]; then
        #sudo systemctl daemon-reload
        #sudo systemctl start battery-monitor.service
        echo "Install successful."
    else
        echo "Install failed."
        exit 1
    fi
}

# Uninstall and then reinstall the project
uninstall_project
install_project
