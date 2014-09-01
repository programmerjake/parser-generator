#!/bin/bash

install_file=bin/Release/parser-generator
dest_dir=/usr/local/bin/

if [ ! -x "$install_file" ]; then
    echo "can't find $install_file" >&2
    exit 1
elif [ "a`whoami`" != "aroot" ]; then
    echo "running sudo to change to root"
    sudo -- "$0" "$@"
    exit
fi
echo "installing $install_file to $dest_dir"
install "$install_file" "$dest_dir"

