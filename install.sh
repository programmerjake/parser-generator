#!/bin/bash

install_file=parser-generator
dest_dir=/usr/local/bin/

if [ ! -x "$install_file" ]; then
    echo "can't find $install_file" >&2
    exit 1
elif [ "a`whoami`" != "aroot" ]; then
    echo "must be run as root" >&2
    exit 1
fi
echo "installing $install_file to $dest_dir"
install "$install_file" "$dest_dir"

