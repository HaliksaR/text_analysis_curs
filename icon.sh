#!/bin/bash

BREAK='\033[m'     # ${BREAK} все атрибуты по умолчанию
LCYAN='\033[1;36m' # ${LCYAN} цвет волны

current_dir=$(pwd)

echo "[Desktop Entry]
Version=1.0
Name=Frequency_analysis
Exec=$current_dir/.Frequency_analysis -ui
Path=$current_dir/
Icon=$current_dir/style/img/sredny (3).png
Terminal=false
Type=Application
Categories=Gtk+3;Application;" > /home/$USER/Desktop/Frequency_analysis.desktop

chmod +x /home/$USER/Desktop/Frequency_analysis.desktop

echo -e "${LCYAN}|----------------------\\ ${BREAK}"
echo -e "${LCYAN}|Create icon on desktop |${BREAK}"
echo -e "${LCYAN}|----------------------/ ${BREAK}"