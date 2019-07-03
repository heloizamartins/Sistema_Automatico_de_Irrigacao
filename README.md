# Sistema Automático de Irrigação - nome do produto

## Sumário
1. [SmartPot](#Nome-do-Produto)
	* [Descrição do Produto](#Descricao-do-Produto)
	* [Produtos Existentes](#Produtos-Existentes)
2. [Desenvolvimento do Produto](#desenvolvimento)
	* [Sensor de Umidade](#Sensor-de-Umidade)
	* [Sensor de Nível de Água](#Sensor-de-Nivel-de-agua)
	* [Motor](#Motor)
	* [Comunicação Wi-Fi](#comunicacao)
	* [Alimentação](#Alimentacao)
3. [Resultados](#Resultados)
4. [Referências](#referencia)

### 

# <a name=Nome-do-Produto></a> Nome do Produto
## Descrição do Produto <a name=Descricao-do-Produto>
Muitas pessoas, hoje em dia, tem plantas nas suas residências, porém não providenciam cuidado necessário a elas, como por exemplo não irrigar no tempo adequado. Por isso, este produto tem como objetivo  possuir um sistema automático para o controle de irrigação de plantas, tanto com a quantidade e a distribuição de água como o horário em que será fornecida. Isso tudo será automático, pré-definido pelo próprio usuário, de acordo com a planta monitorada, utilizando comunicação wireless.

O produto conterá um sensor de umidade de solo, que fornecerá informações sobre o estado da planta e, a partir dessas, tomar a decisão de irrigá-la ou não. Além disso, possuirá um reservatório de água, o qual possuirá um sensor de nível, que mandará um aviso ao usuário quando a água estiver acabando. 

![alt text](https://github.com/heloizamartins/Sistema_Automatico_de_Irrigacao/blob/master/Diagrama%20de%20Blocos.jpg)

## Produtos Existentes <a name=Produtos-Existentes>

Para a definição deste produto, realizou-se uma pesquisa de mercado, onde foram destacadas as principais características existentes, apresentados na tabela abaixo.

--------------------------------------------------------------------------------------------------------------------------------------
Características	    		|    Lechuza   	| Oasis                  	| HIDROFERTI  			|   NOME              
--------------------------------|---------------|-------------------------------|-------------------------------|----------------------
Indicador de Nível de água      | x    		|                    		|				|x
Reservatório de água     	| x    		| x         			| x				|x
Controle da quantidade de água 	| x           	| x          			| x				|x
Sistema de aeração     		| x           	|        			| 				|
Alimentação     	 	| não informado | Bateria 9V        		| 220V CA			|Bateria 3,7V
Configuração de tempo   	|         	| x    				| x				|x
Distribuição de água   		| pavio        	| Gotejamento/gravidade 	| injeção direta/vazão e pressão|gotejamento
Programa para controle		|         	| pré-definido pelo usuário 	| menu intuitivo		|Qualquer dispositivo com conexão Wi-Fi
Autonomia 			|        	| 20 plantas por 40 dias 	| 5 a 90 m^3/h			|30 dias
Sinalização 			|         	| em funcionamento/bateria baixa| entrada digital/12 sensores	| Motor/ nível da água
Sistema de comunicação 		|   		|    				|				| Wi-Fi 

Além desses produtos, também foram encontrados alguns projetos feitos para uso pessoal, utilizando o microcontrolador Arduino. No entanto, a maioria não tinha um reservatório de água, nem um meio para mandar água automaticamente para a planta, apenas os dados do sensor de umidade eram mandados para um dispositivo, para que a irrigação fosse feita manualmente.


# <a name=desenvolvimento></a> Desenvolvimento do Produto

## Sensor de Umidade <a name=Sensor-de-Umidade>
	
Para a verificação da umidade do solo, utilizou-se o sensor de umidade do solo Higrômetro HL-69 apresentado na Figura abaixo. O princípio de funcionamento deste sensor é baseado na aplicação de uma determinada corrente nos seus eletrodos existentes nas hastes, assim é possível estimar quão úmido o solo está, devido a condutividade do mesmo. Sendo que, quando o substrato estiver úmido há uma condutividade maior, que resulta num fluxo maior de corrente entre os dois eletrodos, e quando estiver seco, ocorrerá o oposto, ou seja  há uma redução neste fluxo. 


<p align="center">
  <img width="300"  src="https://github.com/heloizamartins/Sistema_Automatico_de_Irrigacao/blob/master/Figuras/sensor-de-umidade-do-solo-higrmetro.jpg">
</p>

O circuito empregado para a aquisição de dados foi um divisor de tensão alimentado a 3V3, representado pela Figura abaixo. Os dois pinos do sensor estão em série com o resistor de 10㏀, e em paralelo com o capacitor de 10nF, que tem a função de remover os picos indesejados nos trilhos de energia. A saída do divisor é conectada ao conversor AD do microcontrolador STM32F103C8 para ler o seu valor de tensão que é proporcional à resistência do sensor. Essa irá ser máxima e muito maior que 10㏀, quando o solo está seco, assim, a saída irá ter o mesmo valor de alimentação (efeito pull-up do resistor de 10㏀). Caso contrário, a saída terá o valor referente à queda de tensão na eletrodos do sensor, que será um valor bem menor.

<p align="center">
  <img width="400"  src="https://github.com/heloizamartins/Sistema_Automatico_de_Irrigacao/blob/master/Figuras/sensor_Umidade_circuito.jpg">
</p>

Foram feitos testes deste sensor com a planta Avenca e os dados foram adquiridos num período de 6 horas com um intervalo de uma hora entre cada aquisição. Então, gerou-se o gráfico da Figura abaixo, sendo que o primeiro dado foi obtido logo após a primeira e única irrigação que houve naquele dia.

<p align="center">
  <img width="400"  src="https://github.com/heloizamartins/Sistema_Automatico_de_Irrigacao/blob/master/Figuras/UmidadexTempo.png">
</p>


A leitura destes dados foi realizada pelo ADC do microcontrolador, assim como os dados do sensor de nível, que será explicado em seguida. Devido a variação dos valores, foi implementado um sistema que calcula a média a partir de 8 amostras obtidas, e em seguida, para facilitar o entendimento do usuário, converteu-se esse valor para porcentagem, dado que não existe uma unidade para a umidade, e sim uma relação de quantidade, ou seja, o quanto que um determinado solo está úmido. Além disso, o usuário pode definir uma umidade mínima que o solo deve estar, caso esse valor seja maior do que o sensor está medindo, a planta será irrigada, até chegar no valor definido. O sistema estabelece uma porcentagem mínima de 10% caso nenhum valor seja determinado ou este seja menor que 10%. 


## Sensor de Nível de Água <a name=Sensor-de-Nivel-de-agua>

Para medir o nível d’água optou-se por produzir um sensor capacitivo de placa interdigitada, cujo layout pode ser visto a seguir. 

<p align="center">
  <img width="80"  src="https://github.com/heloizamartins/Sistema_Automatico_de_Irrigacao/blob/master/Figuras/Placa_Interdigitada.jpg">
</p>

Um capacitor interdigitado é uma estrutura coplanar que contém múltiplos eletrodos de pentes interpenetrante, e seu princípio de funcionamento é similar a de um capacitor de placas paralelas. Ao aplicar uma diferença de potencial em cada pente de eletrodos, é gerado um campo elétrico entre o positivo e o negativo dos eletrodos. A partir desse campo, do material e das dimensões da placa, é possível obter o valor da capacitância.

Para realizar a medida do nível de água, é lido o valor de tensão nos terminais do capacitor, que irá variar de acordo com a quantidade de água e de ar em contato com o capacitor.

Para isso, utilizou-se um circuito RC, apresentado abaixo, onde dois sinais de PWM opostos são gerados pelo mesmo *Timer*, porém com dois canais diferentes, para a carga e a descarga do capacitor com frequência de 200Hz e razão cíclica de 30% (3,5ms de descarga). O carregamento é feito pelo Resistor de 100k e o descarregamento pelo 8.2M. Para configurar o ADC utilizou-se o modo *output compare* do terceiro canal do *Timer*, onde ele irá adquirir a medida a cada 2ms (0,5ms após a descarga do capacitor), garantindo assim a sincronização temporal do efeito RC com a aquisição da medida.

<p align="center">
  <img width="600"  src="https://github.com/heloizamartins/Sistema_Automatico_de_Irrigacao/blob/master/Figuras/RC%20CIRCUIT%20CAPACITOR.png">
</p>
	
Assim como o sensor de umidade, foi realizada uma média com 8 amostras obtidas. A Figura a seguir mostra a carga e descarga do capacitor, assim como o instante que foi feita a aquisição do valor de tensão (500us após o início da descarga do capacitor).

<p align="center">
  <img width="300"  src="https://github.com/heloizamartins/Sistema_Automatico_de_Irrigacao/blob/master/Figuras/TEK0001.JPG">
</p>

Como o objetivo de se utilizar o sensor capacitivo era o de medir o nível de água no reservatório do sistema, a tensão medida foi convertida em milímetros. O gráfico a seguir mostra a variância da altura da água no reservatório em relação ao valor de ADC lido no mesmo instante. A partir desses pontos, gerou-se uma equação, para converter todos os valores lidos em mm. Dessa maneira, o usuário pode saber aproximadamente qual a quantidade de água que ainda há no seu reservatório. 

Além disso, também foi implementada uma sinalização que avisa ao usuário quando não há mais água o suficiente no reservatório, sendo que, quando o sinal está em 1, significa que há pouca ou nenhuma água no recipiente, e quando o sinal está em 0, significa que ainda há água o suficiente para a irrigação.

<p align="center">
  <img width="500"  src="https://github.com/heloizamartins/Sistema_Automatico_de_Irrigacao/blob/master/Figuras/tensaoxNivel.png">
</p>


## Motor <a name=Motor>
	
O motor escolhido para fazer parte do produto foi uma bomba d'água submersível, de 3,6 V com capacidade de 120L/h, que pode ser vista na Figura que segue. O acionamento do motor é feito por um regulador de corrente, LM317, controlado por tensão, limitando uma corrente máxima necessária para o seu funcionamento.  A tensão de entrada é adquirida por um sinal de PWM gerado pelo microcontrolador, o qual modifica a velocidade do motor de acordo com o *duty cycle* definido. 

Na saída do microcontrolador utilizou-se o um transistor como inversor garantindo uma tensão de 5V quando está em alto em vez de 3.3V, tensão necessária para o funcionamento do circuito. O amplificador TL071 opera como seguidor de tensão, o qual tem a finalidade de de isolar as variações do sinal de PWM do transistor BC337, tendo assim mais segurança de que não haverá interferência no circuito. O transistor BC337 atua como amplificador de corrente.

<p align="center">
  <img width="800"  src="https://github.com/heloizamartins/Sistema_Automatico_de_Irrigacao/blob/master/Figuras/Motor.jpg">
</p>

O acionamento do motor depende da umidade do solo e da umidade mínima que o solo deve sempre estar, ou seja, se a umidade do solo estiver menor do que 10%, ou menor do que a umidade que foi definida pelo usuário (sendo este um valor maior do que 10%), o motor irá ligar, e irriga-rá a planta até que o valor de umidade lido seja maior do valor mínimo configurado.

No entanto, esse motor só irá ser acionado, se a sinalização do nível de água estiver em 0, ou seja, se tiver água o suficiente no reservatório.
	
## Comunicação Wi-Fi <a name=comunicacao>
Após o condicionamento dos dados dos sensores, estes valores foram enviados ao módulo **WiFi ESP8266 ESP-01**, que enviará os dados dos sensores à Internet através do protocolo MQTT (*Message Queuing Telemetry Transport*). 
	
<p align="center">
  <img width="600"  src="https://github.com/heloizamartins/Sistema_Automatico_de_Irrigacao/blob/master/Figuras/ESP8266_.jpg">
</p>

Para isso, utilizou-se o protocolo de comunicação [modbus](https://github.com/heloizamartins/Sistema_Automatico_de_Irrigacao/blob/master/IrrigationSystem/Src/modbus.c), onde foi enviado o pacote em formato RTU, *Remote Terminal Unit*, contendo (*addr, cmd, reg, data, crc*) 

* **addr**: endereço do dispositivo que se deseja enviar uma mensagem (0x15) (1 byte)

* **cmd**: comando que se deseja enviar, escrita (0x01) ou leitura (0x02). (1 byte)

* **reg**: qual registrador do dispositivo deseja-se escrever ou ler. (2 bytes)

* **data**: dado que se deseja escrever no registrador ou número de registradores que se deseja ler. (2 bytes)

* **crc**: verificação cíclica de redundância. (2 bytes)

:red_circle: Para o envio dos dados que são de 2 bytes, foi necessário trocar os primeiros dois bytes com os dois últimos, pois o Modbus é do tipo *big endian* e o microcontrolador STM32F103C8 é *little endian*.

Os resultados podem ser visualizados através do aplicativo **MQTT Dash**, disponível para android, onde é possível visualizar: a medida de umidade em porcentagem, de nível de água em milímetro, o estado do motor (*on/off*) e a sinalização do nível de água. Além disso, o usuário pode definir o valor de umidade mínima pelo aplicativo.

<p align="center">
  <img width="300"  src="https://github.com/heloizamartins/Sistema_Automatico_de_Irrigacao/blob/master/Figuras/MQTT_DASH_INTERFACE.png">
</p>


## Alimentação <a name=Alimentacao>
A alimentação do produto é feita a partir de uma bateria recarregável de lítio-íon. Para o melhor aproveitamento, o circuito já contém um módulo carregador USB de baterias, permitindo que o cliente possa sempre fazer o reuso dessa bateria, apenas carregando-a quando necessário. 

Além disso, para a alimentação de alguns circuitos utilizados era necessário tensões de 5V e 9V. Por isso, a placa de alimentação foi composta por um boost, responsável por elevar a tensão fornecida pela bateria até 9V. Essa é tensão que alimenta o circuito do motor, e para os outros circuitos, utilizou-se um regulador de tensão 7805, que fornece como saída 5V, que irá alimentar o microcontrolador, o qual será o responsável por fornecer a tensão necessário para os outros circuitos.

Abaixo é possível observar o esquemático utilizado para a alimentação.

<p align="center">
  <img width="600"  src="https://github.com/heloizamartins/Sistema_Automatico_de_Irrigacao/blob/master/Figuras/alimentacao.png">
</p>

# <a name=Resultados></a> Resultados



<p align="center">
  <img width="800"  src="https://github.com/heloizamartins/Sistema_Automatico_de_Irrigacao/blob/master/Figuras/Placa_final_alimentacao_controle.jpg">
</p>

<p align="center">
  <img width="400"  src="https://github.com/heloizamartins/Sistema_Automatico_de_Irrigacao/blob/master/Figuras/MQTT_DASH_LW.png">
</p>
<p align="center">
  <img width="400"  src="https://github.com/heloizamartins/Sistema_Automatico_de_Irrigacao/blob/master/Figuras/MQTT_DASH_Motor.png">
</p>


# <a name=referencia></a> Referências

CHETPATTANANONDH, Kanadit et al. A self-calibration water level measurement using an interdigital capacitive sensor. **Elsevier: Sensors and Actuators A: Physical**. Thailand, p. 175-182. 2014.

CHIRAG PARMAR. **Know Your Sensor — YL38 Soil Hygrometer**. Disponível em: <https://medium.com/@chirag.parmar/know-your-sensor-yl38-soil-hygrometer-fceca860faac>. Acesso em: 03 jul. 2019.

CLABER OASIS. **Claber 8053 Oasis 4-Programs/20 Plants Garden Automatic Drip Watering System**. Disponível em: <https://www.amazon.com/Claber-8053-4-Programs-Automatic-Watering/dp/B000U5YFR4/ref=as_li_ss_tl?s=lawn-garden&ie=UTF8&qid=1512597471&sr=1-4&keywords=indoor+watering+system&linkCode=sl1&tag=culinaryherb-20&linkId=ab3f02bb2b0c518f48dbd2a272eaca80>. Acesso em: 03 jul. 2019.

HIDROSENSE .**HIDROFERTI - CONTROLADOR DE FERTIRRIGAÇÃO POR INJEÇÃO DIRETA**. Disponível em: <https://www.hidrosense.com.br/controle-de-irrigacao/hidroferti-s-controlador-de-fertirrigacao-por-injecao-direta>. Acesso em: 03 jul. 2019.

 **Lechuza**. Disponível em: <https://www.lechuza.us/home/>. Acesso em: 03 jul. 2019.

SHENZHEN ANXINKE TECHNOLOGY. **ESP-01 WiFi Module**. Disponível em: <http://www.microchip.ua/wireless/esp01.pdf>. Acesso em: 03 jul. 2019

**Reference Manual**. 2018. Disponível em: <https://www.st.com/content/st_com/en.html>. Acesso em: 03 jul. 2019.

STARKE, Renan. **Gateway MODBUS MQTT usando ESP8266**. 2019. Disponível em: <https://github.com/xtarke/mqtt_modbus>. Acesso em: 03 jul. 2019.

TEXAS INSTRUMENTS. **µA7800 SERIES. POSITIVE-VOLTAGE REGULATORS**. Disponível em: <https://www.sparkfun.com/datasheets/Components/LM7805.pdf>. Acesso em: 03 jul. 2019.

TEXAS INSTRUMENTS. **LM317 3-Terminal Adjustable Regulator**. Disponível em: <http://www.ti.com/lit/ds/slvs044x/slvs044x.pdf>. Acesso em: 03 jul. 2019.
