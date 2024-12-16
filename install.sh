#!/usr/bin/env bash

CURRENT_DIR="$(pwd)"
BUILD_DIR="/tmp/lowkey/build"

clone_repo(){
  cd /tmp
  git clone https://github.com/ZaneFerns360/lowkey.git
  cd lowkey
}

uninstall_project() {
    echo "Uninstalling the project before reinstalling..."
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

start_daemon(){
  # battery-monitor check not included since the uninstall script will disable it
  systemctl --user daemon-reload
  systemctl --user start battery-monitor.service
  systemctl --user enable battery-monitor.service
}

clean_up(){
  cd ..
  rm -r lowkey
}

# Uninstall and then reinstall the project
clone_repo
uninstall_project
install_project
start_daemon
clean_up

cd $CURRENT_DIR # Return to the original directory
