#!/bin/bash

sudo git clone --recurse-submodules \
    https://github.com/Beebopi-Home-Server/Beebopi-Server.git \
    /opt/Beebopi-Server

# Dá permissão de execução aos scripts do Beebopi
cd /opt/Beebopi-Server
sudo chmod +x ./scripts/*

# Instala o master_mind
cd /opt
sudo ln -s Beebopi-Server/services/master_mind .
cd /opt/master_mind
sudo chmod +x ./scripts/install.sh
./scripts/install.sh

