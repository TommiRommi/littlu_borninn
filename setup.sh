#!/usr/bin/sh

SKETCH=sketch
c=0

help_text()
{
	echo "${0##*/} <help_text|compile|clean|/path/to/serial/port> ..."
	echo 
	echo "help_text:"
	echo "	prints this text"
	echo "compile:"
	echo "	compiles the programs and exits"
	echo "clean:"
	echo "	removes the output build directory"
	echo "<path/to/serial/port>:"
	echo "	where to upload the program"
}

compile()
{
	# sendir breituna af sketchinu til make til að halda breitonum eins
	if ! make SKETCH=$SKETCH
	then
		exit 1
	fi
}

compile_and_upload()
{
	if [ "c" = "0" ]
	then
		compile
	fi

	arduino-cli upload -p $1 --fqbn arduino:avr:uno ${SKETCH}/${SKETCH}.ino
}

if ! [ -f makefile ]
then
	echo "no makefile found" >&2
	exit 1
elif [ $# != 0 ]
then
	# skiptir út gömul cores fyrir ný custom cores og setur up platform.txt
	avr_version=$(arduino-cli core list | grep "arduino:avr" | cut -d ' ' -f 2)
	arduino_avr=~/.arduino15/packages/arduino/hardware/avr/${avr_version}
	arduino_libs=${arduino_avr}/cores/arduino

	cp -r platform.txt $arduino_avr
	cp -r custom_cores/* $arduino_libs

	# loopar í gegnum öll arguments og notar shift til að aðgengast þeim á $1
	for x in {0..$#}
	do
		case $1 in
			'help')
				help_text
				exit;;
			'compile')
				compile
				exit;;
			'clean')
				make clean
				exit;;
			*)
				if [ -c $1 ]
				then
					compile_and_upload $1
				else
					help_text
					exit 1
				fi;;
		esac

		shift
		c=$((c += 1))
	done
else
	help_text
	exit 1
fi
