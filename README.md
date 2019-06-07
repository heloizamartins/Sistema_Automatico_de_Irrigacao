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
Muitas pessoas, hoje em dia, tem plantas nas suas residências, porém não providenciam cuidado necessário a elas, como por exemplo não irrigar no tempo. Por isso, este produto tem como objetivo  possuir um sistema automático para o controle de irrigação de plantas, tanto com a quantidade e a distribuição de água como o horário em que será fornecida. Isso tudo será automático, pré-definido pelo próprio usuário, de acordo com a planta monitorada, utilizando comunicação wireless.
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
Alimentação     	 	| não informado | Bateria 9V        		| 220V CA			|Bateria
Configuração de tempo   	|         	| x    				| x				|x
Distribuição de água   		| pavio        	| Gotejamento/gravidade 	| injeção direta/vazão e pressão|gotejamento
Programa para controle		|         	| pré-definido pelo usuário 	| menu intuitivo		|celular
Autonomia 			|        	| 20 plantas por 40 dias 	| 5 a 90 m^3/h			|30 dias
Sinalização 			|         	| em funcionamnto/bateria baix a| entrada digital/12 sensores	| em funcionamnto/ nível da água
Sistema de comunicação 		|   		|    				|				| Wi-Fi 

Além desses produtos, também foram encontrados alguns projetos feitos para uso pessoal, utilizando o microcontrolador Arduino. No entanto, a maioria não tinha um reservatório de água, nem um meio para mandar água automaticamente para a planta, apenas os dados do sensor de umidade eram mandados para um dispositivo, para que a irrigação fosse feita manualmente.


# <a name=Materiais></a> Materiais
## Sensor de Umidade <a name=Sensor-de-Umidade>
	
Para a verificação da umidade do solo, utilizou-se o sensor de umidade do solo Higrômetro HL-69, Figura abaixo. O princípio de funcionamento deste sensor é da seguinte forma, através da aplicação de uma determinada corrente nos seus eletrodos existentes nas hastes, é possível estimar quão úmido ou seco o solo está, devido a condutividade do solo. Sendo que, quando o solo estiver úmido há uma condutividade maior, que resulta num fluxo maior de corrente entre os dois eletrodos. E quando o solo estiver seco, ocorrerá o oposto, pouca corrente passará. 


<p align="center">
  <img width="400"  src="https://github.com/heloizamartins/Sistema_Automatico_de_Irrigacao/blob/master/Figuras/sensor-de-umidade-do-solo-higrmetro.jpg">
</p>

O circuito empregado para a aquisição de dados foi um divisor de tensão alimentado a 3.3V, representado pela Figura abaixo. Os dois pinos do sensor estão em série o resistor de 10㏀, e em paralelo com o capacitor de 10nF, que tem a função de remover os picos indesejados nos trilhos de energia. A saída do divisor é conectada ao conversor AD do microcontrolador para ler o seu valor de tensão e calcular a resistência do sensor. Essa irá ser máxima e muito maior que 10㏀, quando o solo está seco, assim, a saída irá ter o mesmo valor de alimentação (efeito pull-up do resistor de 10㏀). Caso contrário, a saída terá o valor referente à queda de tensão na eletrodos do sensor, que será um valor bem menor.

<p align="center">
  <img width="400"  src="https://github.com/heloizamartins/Sistema_Automatico_de_Irrigacao/blob/master/Figuras/sensor_Umidade_circuito.jpg">
</p>

## Sensor de Nível de Água <a name=Sensor-de-Nivel-de-agua>

Para medir o nível d’água optou-se por produzir um sensor capacitivo, que consiste em uma placa interdigitada, cujo layout pode ser visto a seguir. 

<p align="center">
  <img width="80"  src="https://github.com/heloizamartins/Sistema_Automatico_de_Irrigacao/blob/master/Figuras/Placa_Interdigitada.jpg">
</p>
	
## Motor <a name=Motor>
	
O motor escolhido para fazer parte do produto foi uma bomba d'água submersível, de 3,6 V com capacidade de 120L/h, que pode ser vista na Figura que segue. O acionamento do motor é feito por um regulador de corrente, LM317, controlado por tensão, limitando uma corrente máxima necessária para o seu funcionamento.  A tensão de entrada é adquirida por um sinal de PWM gerado pelo microcontrolador, o qual modifica a velocidade do motor de acordo com o duty cycle definido. 

Na saída do microcontrolador utilizou-se o um transistor como inversor garantindo uma tensão de 5V quando está em alto em vez de 3.3V, tensão necessário para o funcionamento do curcuito. O amplificador TL071 opera como seguidor de tensão, o qual tem a finalidade de de isolar as variações do sinal de PWM do transistor BC337, tendo assim mais segurança de que não haverá interferência no circuito. O transistor BC337 atua como amplificador de corrente.

<p align="center">
  <img width="800"  src="https://github.com/heloizamartins/Sistema_Automatico_de_Irrigacao/blob/master/Figuras/Motor.jpg">
</p>
	
## Comunicação Wi-Fi <a name=comunicacao>
Após o condicionamento dos dados dos sensores, estes valores foram enviados ao módulo **WiFi ESP8266 ESP-01**, que enviará os dados do sensor à Internet através do protocolo MQTT (*Message Queuing Telemetry Transport*). Para isso, utilizou-se o arquivo `modbus.c`, onde foi enviado o pacote RTU contendo (*addr, cmd, reg, data, crc*) 

* **addr**: endereço do dispositivo que se deseja enviar uma mensagem (0x15) (1 byte)

* **cmd**: comando que se deseja enviar, geralmente escrita (0x01) ou leitura (0x02). (1 byte)

* **reg**: qual registrador do dispositivo deseja-se escrever ou ler. (2 bytes)

* **data**: dado que se deseja escrever no registrador ou número de registradores que se deseja ler. (2 bytes)

* **crc**: verificação cíclica de redundância. (2 bytes)

:red_circle: Para o envio dos dados que são de 2 bytes, foi necessário trocar os primeiros dois bytes com os dois últimos, pois o Modbus é do tipo big endian.


Os resultados podem ser visualizados através do aplicativo **MQTT Dash**, disponível para android, onde é possível visualizar as duas medidas, de umidade e de nível de água.

<p align="center">
  <img width="600"  src="https://github.com/heloizamartins/Sistema_Automatico_de_Irrigacao/blob/master/Figuras/ESP8266_.jpg">
</p>

## Alimentação <a name=Alimentacao>
	
<p align="center">
  <img width="600"  src="https://github.com/heloizamartins/Sistema_Automatico_de_Irrigacao/blob/master/Figuras/alimentacao.png">
</p>

# <a name=Resultados></a> Resultados

# <a name=referencia></a> Referências
