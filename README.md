# Littlu Börninn
### arduino-cli
notaðu `arduino-cli` til að compila og uploada forritið á unoinn <a href="https://arduino.github.io/arduino-cli/0.19/">arduino-cli</a>. 

Þegar að `arduino-cli` er set up þarftu að setja up `avr` fyrir `arv-g++` C++ compilerinn sem er notaður til að compila forritið fyrir unoinn.

`avr` getur verið set up með,
```sh
arduino-cli core install arduino:avr
```
hægt er að sannræna að `avr` er set up með,
```sh
arduino-cli core list
```
og útkoman ætti að vera svippuð þessu.
```
ID          Installed Latest Name              
arduino:avr 1.8.6     1.8.6  Arduino AVR Boards
```
### Compiling og Uploading
Passaðu það að notandinn þinn hefur leif til að skrifa í serial `character special file` sem er búið til frá því að stínga unoinum í samband.

Það er hægt að skoða hver hann file er með því að skrifa,
```
arduino-cli board list
```
```
Port         Protocol Type              Board Name  FQBN            Core       
/dev/ttyACM0 serial   Serial Port (USB) Arduino Uno arduino:avr:uno arduino:avr
------------
```
maður gefur notandanum læfi með a skrifa.
```
sudo chown $USER </path/to/serial/port>
```
Í lokinn keyrir þú `setup.sh` til að Compila og Uploada
```
chmod +x setup.sh; ./setup.sh
```
