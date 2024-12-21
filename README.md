Ардуино проект для блока управления нагревателем с положительным температурным коэффициентом.

В качестве нагревателя предусматривается 1K0963235F или аналогичные (G, H) без управления по can-шине.
Управление основано на ардуино нано (atmega328), которая управляет схемой силовых ключей на полевых транзисторах. Контроль температуры осуществлен с помощью датчика ds18b20 (Dallas).
Измерение напряжения бортовой сети для контроля запуска только при запущенном двигателе, основано на делителе напряжения и измерении аналоговым входом.
Питание Ардуино организовано на линейном стабилизаторе напряжения КР142ЕН8Б (КРЕН8Б, 7805).

Больше информации в бортжурнале по ссылке https://www.drive2.ru/l/689339090985821175/.


Arduino project for a control unit for a heater with a positive temperature coefficient.

The heater is 1K0963235F or similar (G, H) without control via CAN-bus.
The control is based on the Arduino nano (atmega328), which controls the power key circuit on MOSFET's transistors. Temperature control is carried out using the Dallas ds18b20 sensor.
Measuring the voltage of the on-board network for monitoring the start only when the engine is running is based on a voltage divider and measuring the analog input.
Arduino power supply is organized on a linear voltage stabilizer 7805.
More information in the logbook on https://www.drive2.ru/l/689339090985821175/.
