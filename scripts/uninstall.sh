#!/bin/bash

sudo rm -r /opt/Beebopi-Server
sudo rm -r /opt/master_mind
sudo systemctl disable master_mind
sudo systemctl stop master_mind
sudo rm /lib/systemd/system/master_mind.service
