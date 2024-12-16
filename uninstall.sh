#!/usr/bin/env bash

clone_repo(){
  cd /tmp
  git clone https://github.com/ZaneFerns360/lowkey.git
  cd lowkey
}

uninstall_project() {
    echo "Uninstalling the project..."
    sudo systemctl disable battery-monitor.service
    sudo systemctl stop battery-monitor.service
    sudo systemctl daemon-reload
    sudo cmake --build build --target uninstall
}

clean_up(){
  cd ..
  rm -r lowkey
}

clone_repo
uninstall_project
clean_up
