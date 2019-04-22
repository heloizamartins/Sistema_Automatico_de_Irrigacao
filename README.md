# Sistema Automático de Irrigação - nome do produto

## Sumário
1. [Nome do Produto](#Nome-do-Produto)
	* [Descrição do Produto](#Descricao-do-Produto)
	* [Produtos Existentes](#Produtos-Existentes)
2. [Materiais](#Materiais)
	* [Sensor de Umidade](#Sensor-de-Umidade)
	* [Sensor de Nível de Água](#Sensor-de-Nivel-de-agua)
	* [Motor](#Motor)
3. [Referências](#referencia)

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

![alt text](https://github.com/heloizamartins/Sistema_Automatico_de_Irrigacao/blob/master/Figuras/sensor-de-umidade-do-solo-higrmetro.jpg)

O circuito empregado para a aquisição de dados foi um divisor de tensão alimentado a 3.3V, representado pela Figura abaixo. Os dois pinos do sensor estão em série o resistor de 10㏀, e em paralelo com o capacitor de 10nF, que tem a função de remover os picos indesejados nos trilhos de energia. A saída do divisor é conectada ao conversor AD do microcontrolador para ler o seu valor de tensão e calcular a resistência do sensor. Essa irá ser máxima e muito maior que 10㏀, quando o solo está seco, assim, a saída irá ter o mesmo valor de alimentação (efeito pull-up do resistor de 10㏀). Caso contrário, a saída terá o valor referente à queda de tensão na eletrodos do sensor, que será um valor bem menor.

![alt text](https://github.com/heloizamartins/Sistema_Automatico_de_Irrigacao/blob/master/sensor_Umidade_circuito.jpg)
## Sensor de Nível de Água <a name=Sensor-de-Nivel-de-agua>
	
## Motor <a name=Motor>
	
O motor escolhido para fazer parte do produto foi uma bomba d'água submersível, de 3,6 V com capacidade de 120L/h. Para fazer o uso dessa bomba foi montado o circuito da Figura abaixo, que consiste em um transistor NPN, permitindo controlar os estados ligado e desligado do motor, além de sua velocidade. O resistor conectado na entrada do circuito será ligado no microcontrolador, e serve para limitar a corrente que fará o chaveamento do transistor. O diodo atua como proteção para quando há o efeito de tensão reversa causado em cargas indutivas quando a energia é cortada.

A velocidade do motor será controlada por PWM, de acordo com a necessidade de água que a planta necessita, informação que será adquirida pelo sensor de umidade, e processada pelo microcontrolador, para que então possa ser regulada a quantidade de água que irá irrigar a planta.

![alt text](https://github.com/heloizamartins/Sistema_Automatico_de_Irrigacao/blob/master/Figuras/Motor.jpg)

# <a name=referencia></a> Referências
