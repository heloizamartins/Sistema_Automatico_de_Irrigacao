# Sistema Automático de Irrigação - nome do produto

## Sumário
1. [Nome do Produto](#Nome-do-Produto)
	* [Descrição do Produto](#Descricao-do-Produto)
	* [Produtos Existentes](#Produtos-Existentes)
2. [Materiais](#Materiais)
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


# <a name=Materiais></a> Materiais
## Sensor de Umidade <a name=Sensor-de-Umidade>
	
Para a verificação da umidade do solo, utilizou-se o sensor de umidade do solo Higrômetro HL-69, Figura abaixo. O princípio de funcionamento deste sensor é da seguinte forma, através da aplicação de uma determinada corrente nos seus eletrodos existentes nas hastes, é possível estimar quão úmido ou seco o solo está, devido a condutividade do solo. Sendo que, quando o solo estiver úmido há uma condutividade maior, que resulta num fluxo maior de corrente entre os dois eletrodos. E quando o solo estiver seco, ocorrerá o oposto, pouca corrente passará. 


<p align="center">
  <img width="400"  src="https://github.com/heloizamartins/Sistema_Automatico_de_Irrigacao/blob/master/Figuras/sensor-de-umidade-do-solo-higrmetro.jpg">
</p>

O circuito empregado para a aquisição de dados foi um divisor de tensão alimentado a 3V3, representado pela Figura abaixo. Os dois pinos do sensor estão em série com o resistor de 10㏀, e em paralelo com o capacitor de 10nF, que tem a função de remover os picos indesejados nos trilhos de energia. A saída do divisor é conectada ao conversor AD do microcontrolador STM32F103C8 para ler o seu valor de tensão e calcular a resistência do sensor. Essa irá ser máxima e muito maior que 10㏀, quando o solo está seco, assim, a saída irá ter o mesmo valor de alimentação (efeito pull-up do resistor de 10㏀). Caso contrário, a saída terá o valor referente à queda de tensão na eletrodos do sensor, que será um valor bem menor.

<p align="center">
  <img width="400"  src="https://github.com/heloizamartins/Sistema_Automatico_de_Irrigacao/blob/master/Figuras/sensor_Umidade_circuito.jpg">
</p>

A partir dos dados obtidos com o sensor de umidade foi gerado o gráfico da Figura abaixo, representando a umidade da planta em relação ao tempo, a partir do momento em que houve a irrigação. Para obter esse valores, optou-se pelo uso da planta Avenca, devido a necessidade de irriga-lá todos os dias.


<p align="center">
  <img width="400"  src="">
</p>


Os dados do sensor de umidade foram adquiridos pelo ADC do microcontrolador, assim como os dados do sensor de nível, que será explicado em seguida. Como há certa variação nas leituras, foi implementado um sistema que calcula a média a partir de 8 amostras obtidas.

Esses dados obtidos pelo sensor de umidade foram tratados em porcentagem, dado que não existe uma unidade para a umidade, e sim uma relação de quantidade, ou seja, o quanto que um determinado solo está úmido. Decidiu-se também por trabalhar dessa forma, pois facilita o entendimento do usuário em relação à necessidade de água do solo. Além disso, o usuário pode definir uma umidade mínima que o solo deve estar, caso esse valor seja maior do que o sensor está medindo, a planta será irrigada, até chegar no valor determinado. Caso o valor escolhido pelo usuário seja menor do que 10%, o sistema irá setar esse valor para 10%.


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
  <img width="600"  src="https://github.com/heloizamartins/Sistema_Automatico_de_Irrigacao/blob/master/Figuras/tensaoxNivel.png">
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
