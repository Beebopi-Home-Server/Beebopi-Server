#!/bin/bash

sudo git clone --recurse-submodules \
    https://github.com/Beebopi-Home-Server/Beebopi-Server.git \
    /opt/Beebopi-Server

# Dá permissão de execução aos scripts do Beebopi
sudo chmod +x /opt/Beebopi-Server/scripts/*

# Instala o master_mind
sudo ln -s /opt/Beebopi-Server/services/master_mind /opt
sudo chmod +x /opt/master_mind/scripts/install.sh
/opt/master_mind/scripts/install.sh

