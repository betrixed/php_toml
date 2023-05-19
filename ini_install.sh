#!/bin/sh
INI_FILE=`php-config --ini-dir`/toml.ini
cp toml.ini $INI_FILE
echo "installed $INI_FILE"
