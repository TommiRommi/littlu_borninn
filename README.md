# Littlu Börninn
### arduino-cli
notaðu `arduino-cli` til að compila og uploada forritið á unoinn <a href="https://arduino.github.io/arduino-cli/0.19/">arduino-cli</a>. 

Þegar að `arduino-cli` er set up þarftu setja up `avr` fyrir `arv-g++` C++ compilerinn sem er notaður til að compila forritið fyrir unoinn.

`avr` getur verið set up með,
```sh
arduino-cli core install arduino:avr
```
hægt er að sannræna að `avr` er set up með,
```sh
arduino-cil core list
```
og útkoman ætti að vera svippuð þessu.
```
ID          Installed Latest Name              
arduino:avr 1.8.6     1.8.6  Arduino AVR Boards
```
### Compiling og Upload
