# Identificação

* Página do repositório do trabalho ([link GitHub](TODO)) 

* Discente 1
	* Nome: Lucas Tadeu Vieira Moura de Santana
	* Matrícula: 15111983 
* Discente 2
	* Nome: Esther Nascimento Soares de Freitas
	* Matrícula: 15111883

# Discussão 

## Utilização intensa da CPU
* EXPLICAÇÃO DO TESTE DE CONSUMO DE CPU: Nesse teste avaliamos como o processador reage ao criarmos um processo filho que tem em seu código uma função de grande utilização de tempo de CPU. A função utilizada e o while(1), basicamente criamos um loop infinito dentro do processo filho. Além deste loop, foram adicionadas, ao processo filho, as funções de  alarm(), para que após 10 segundos seja disparado um sinal de interrupção de tempo real, (interrupções são sinais que mandamos ao processador solicitando algum comportamento específico do mesmo), neste caso ao ser gerada a interrupção o processo filho foi deixado em modo de espera, enquanto o processo pai recebeu o sinal e o tratou com uma chamada de função, tal função pegou o pid do processo filho e pode então finalizá-lo; a função getrusage(), responsável por obter os dados dos recursos utilizados pelo processo, nos dando então a possibilidade de calcular o quanto de tempo de CPU foi gasto. Dividimos o tempo de processamento em 2 tipos, tempo de processamento em modo usuário e tempo de processamento em modo sistema. O tempo de processamento em modo usuário demonstra o tempo que o processo utilizou a CPU com funções comuns ao usuário, sem nenhum privilégio especial de sistema, enquanto que o tempo de processamento em modo sistema, demonstra o tempo gasto com as funções que apenas podem ser executadas pelo modo kernel. Tais funções representam mais tempo de processamento do processo filho, pois ele não as executa diretamente, é necessário fazer uma requisição ao modo kernel do sistema para que ele se responsabilize pela execução das mesmas; A utilização da struct tm, da variável do tipo time_t e da função localtime() se dá devido a lógica que nós utilizamos no processo filho para poder imprimir o relatório do uso de processamento a cada 1 segundo. Elas nos possibilitam utilizar o horário do sistema e então, através de um algoritmo, fizemos com que o processo filho, sempre que "notasse" que 1 segundo se passou imprimisse os dados do tempo de uso de cpu.
* AVALIAÇÃO DO TESTE DE CONSUMO DE CPU: O teste foi realizado com várias funções a modo usuário, principalmente para imprimir os dados na tela, e algumas chamadas ao sistema, como a obtenção da utilização da cpu pelo processo filho. Mesmo com as chamadas ao sistema sendo mais "burocráticas" com relação à seu uso, a repetição das funções usuário conseguiram tornar o tempo de cpu de ambas bastante parecido. A diferença média obtida foi de 5%, o que representa em tempo real, 0,5 segundos. Notamos então a enorme diferença no tempo para um humano e para um computador: foi pouco tempo aos olhos humanos, o que poderíamos fazer em 0,5 segundos; mas em tempo de processador isso é uma grande diferença, ele pode ter rodado o loop cerca de 100 vezes ou mais. Essa diferença vai se tornando mais evidente, à medida que nosso hardware vai se aperfeiçoando, e fazendo, cada vez mais, esses 0,5 segundos parecerem uma eternidade.

* TODO: Em cada seção:
	* explicar e discutir sobre o comportamento do programa para cada experimento;
	* sempre referenciar o código fonte e o gráfico do experimento realizado;
	* colocar um gráfico do consumo da UCP e da memória pelo processo filho em função do tempo sendo duas curvas;
		* cada curva representa uma métrica medida (consumo de CUP em porcentagem e consumo de memória em Kilobytes);
		* o eixo das abscissas deve representar o tempo medido a cada segundo e o eixo das coordenadas deve ser a métrica medida.



## Utilização intensa da CPU e memória
* EXPLICAÇÃO DO TESTE DE CONSUMO DE CPU e memória: Utilizamos de um processo filho para utilizar a função while(1) em conjunto com a função malloc(10) para que, dentro de um loop infinito fosse alocada uma grande quantidade de memória para assim podermos estudar como o processador responde à um processo com este comportamento. Basicamente foram utilizadas todas as funções do teste anterior, de Utilização Intensa de CPU, o diferencial acrescentado foi a função malloc(), uma função responsável por alocar memória dinamicamente para um processo. O teste consiste em avaliar como será o comportamente do processo filho agora que estamos atribuindo esta função a ele, dentro de seu loop infinito, para então compararmos como isso afetou o tempo de utilização de CPU pelo modo usuário e pelo modo sistema (kernel).
* AVALIAÇÃO DO TESTE DE CONSUMO DE CPU: Obtivemos resultados bastante interessantes, que reforçam o conhecimento obtido durante as aulas teóricas. Devido a adição da função malloc() pudemos observar como o uso do processador em modo sistema foi incrementado, pois as funções que manipulam a memória são gerenciadas por este modo privilegiado, e que, logicamente, ocasionou a diminuição do tempo de utilização da cpu em modo usuário, já que nosso processo filho, "tem tempo limite de 10 segundos". Constatamos também que: só pelo fato do processo ter que chamar continuamente o modo sistema para alocar memória, podemos ver que a diferença em tempo de uso da cpu cresceu de 5% (0,5 segundos) para, em média, 10% (1,0 segundos), 0,5 segundos de tempo de uso da cpu, o que, como já foi citado na discussão anterior, é uma eternidade para o processador. Observemos então, como apenas uma chamada do modo sistema impactou no desempenho do nosso programa. Por fim, este estudo pode ter aparentado ser simples, mas as fundações por traz do mesmo são bastante complexas. Nossos resultados não mentem, cada função que escolhemos colocar ou não em nossos programas influencia, e muito, no seu desempenho, devemos então fazer uso da Engenharia de Software para pensar na maneira mais eficaz de criar nossos programas, a fim de maximizar seu desempenho.

** Fim do relatório **

[link GitHub] : <https://github.com/lucastvms/teaching/tree/master/2015.1-IAC-trabalho-pratico>
