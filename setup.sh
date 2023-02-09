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

# sendir breituna af sketchinu til make til að halda breitonum eins
SKETCH=sketch
make SKETCH=$SKETCH 

serial_port=$(arduino-cli board list | grep "arduino:avr:uno" | cut -d ' ' -f 1)

if [ -z $serial_port ]
then
	echo "no uno board found" >&2
elif [ "$(stat -c %u $serial_port)" = "$UID" ] || [ "$UID" = "0" ]
then
	echo "you do not have the permission to do that" >&2
	echo "run as super user or use chown 'sudo chown $USER ${serial_port}'" >&2
	exit 1
fi

# sendir til unoinn
arduino-cli upload -p $serial_port --fqbn arduino:avr:uno ${SKETCH}/${SKETCH}.ino
