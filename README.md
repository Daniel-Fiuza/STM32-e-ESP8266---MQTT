#Tutorial Comunica��o MQTT com STM32 e ESP8266 utilizando comandos AT

## Configurando Placa STM32
1 - Fazer o Bootloader do stmduino (generic_boot20_pc13.bin) utilizando a ferramenta STM32CubeProg, a qual pode ser obtida atrav�s do link:
https://www.st.com/en/development-tools/stm32cubeprog.html

2 - Instalar os drivers Maple (install_drivers.bat e install_STM_COM_drivers.bat) para o microcontrolador ser reconhecido pela IDE do Arduino.

## Configurando ESP8266-01
3 - Instalar Firmware (Ai-Thinker_ESP8266_DOUT_8Mbit_v1.5.4.1-a_20171130.bin) no ESP8266 utilizando a ferramenta nodemcu-flasher que pode ser baixada por esse link:
https://github.com/nodemcu/nodemcu-flasher

## Conex�o STM32 - Arduino
4 - Conectar UART1 do stm32 nos pinos Serial do ESP8266 (ver imagens dos pinouts). Ambas as seriais ter�o baud rate: 115200

## Configura��o do Script 
5 - Baixar as bibliotecas WiFiEsp e PubSubClient na IDE do Arduino.
6 - Se houver erro na biblioteca WiFiEsp durante a compila��o, realize as etapas:
	6.1 - Inserir biblioteca stdarg.h no arquivo EspDrv.cpp (Documentos/Arduino/libraries/WiFiEsp/src/utility/EspDrv.cpp) 
por que n�o estava reconhecendo argumentos opcionais: 
	#include <stdarg.h>
6.2 - Modifique fun��o:
	vsnprintf_P (cmdBuf, CMD_BUFFER_SIZE, (char*)cmd, args); por
	vsnprintf (cmdBuf, CMD_BUFFER_SIZE, (char*)cmd, args);

7 - Ap�s instalar a biblioteca PubSubCliente, altere os seguintes par�metros no arquivo PubSubClient.h para os definidos abaixo:

#define MQTT_MAX_PACKET_SIZE 256
#define MQTT_KEEPALIVE 120
#define MQTT_SOCKET_TIMEOUT 120

## Execu��o do Script
Pronto, agora � s� compilar o script (Example_Stm32_WiFiEsp_MQTT.ino) e executar.
