#!/bin/bash

# Get the list of current environment variables
env_vars=$(printenv)

delimiter="="

unset "GDMSESSION"
unset "OLDPWD"
unset "DBUS_SESSION_BUS_ADDRESS"

# Loop through each variable and unset it
for line in $env_vars; do
    env_var=$(echo $line | cut -d "$delimiter" -f1)
    if [[ $line == "PATH"* ]]; then
        break
    echo $env_var
    fi
    unset "$env_var"
done

#unset "PATH"