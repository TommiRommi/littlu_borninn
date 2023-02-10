#!/usr/bin/sh

if ! [ -f makefile ]
then
	echo "no makefile found" >&2
	exit 1
elif [ "$1" = "clean" ]
then
	make clean
	exit
fi

# skiptir út gömul cores fyrir ný custom cores
avr_version=$(arduino-cli core list | grep "arduino:avr" | cut -d ' ' -f 2)
arduino_libs=~/.arduino15/packages/arduino/hardware/avr/${avr_version}/cores/arduino

cp -r custom_cores/* $arduino_libs

# sendir breituna af sketchinu til make til að halda breitonum eins
SKETCH=sketch
if ! make SKETCH=$SKETCH
then
	exit 1
fi

buff=$(arduino-cli board list)
serial_port=$(echo $buff | grep "arduino:avr:uno" | cut -d ' ' -f 8)

if [ "$buff" = "No boards found." ]
then
	echo "no uno board found" >&2
	exit 1
fi

# uploadar til unoinn
if ! arduino-cli upload -p $serial_port --fqbn arduino:avr:uno ${SKETCH}/${SKETCH}.ino >/dev/null
then
	echo "you do not have the permission to do that" >&2
	echo "run as super user or use chown 'sudo chown $USER ${serial_port}'" >&2
	exit 1
fi
