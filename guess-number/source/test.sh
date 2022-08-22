#!/bin/bash -e

ROOT=$(dirname "$0")/..
cd $ROOT

ID=$(cat /dev/urandom | tr -dc 'a-zA-Z0-9' | fold -w ${1:-10} | head -n 1)
NAME=$(cat NAME)
PORT=$(cat PORT)

# +1 to make sure that it's independent to the PORT number
PORT=$(($PORT + 1))

echo "[!] launching a docker container"
docker run -p $PORT:9999 --name $ID --rm -t $NAME &

while ! nc -z -w5 localhost $PORT; do
    echo  "[!] waiting .."
    sleep 1;
done

trap "docker container stop $ID &>/dev/null" EXIT

sleep 2
PORT=$PORT REMOTE=1 source/exploit.py
