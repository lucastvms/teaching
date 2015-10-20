#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <sys/resource.h>
#include <time.h>

void handler_alarm(int signal)
{
	kill(getpid(), SIGKILL);
}

int main (int argc, char *argv[], char *envp[]) {

	int pid ; /* identificador de processo || process identifier*/

	struct rusage r_usage_c, r_usage_s;
	time_t fim;
	struct tm *f;
	int inicio = -1;
	float tempo = 1.000000;


	pid = fork () ; /* replicação do processo || process replication*/

	if ( pid < 0 ) { /* se fork não funcionou || if the fork has not worked*/
	perror ("Erro: ") ;
	exit (-1) ; /* encerra o processo com código de erro -1 || terminates the process with error code -1*/
	}
	else if( pid > 0 ) /* se sou o processo pai || if it's the parent process*/
	{
		printf("\nPARENT'S PROCESS\n");
		wait(NULL);
		signal(SIGALRM, (void(*)(int))handler_alarm);
		
		getrusage(RUSAGE_CHILDREN, &r_usage_c);
		
		//printf("\nConsumo total de Memória: %ld\n", 			r_usage_c.ru_maxrss);
			
	//TODO guarde a cada segundo o consumo de memória (em Kilobytes) e CPU (em porcentagem) do processo filho
	//TODO após 10 segundos de execução, mate o proceso filho
	}
	else /* senão, sou o processo filho || else, it's child process*/
	{
		alarm(10);
		
		printf("\nCHILD'S PROCESS\n");

    //TODO se argv[1] for igual a 'cpu', executar código com utilização intensa da UCP
   
    if(strcmp(argv[1], "cpu") == 0)
    {
	while(1)
	{
		fim = time(0);
		f = localtime(&fim);

		if(inicio == -1)
			inicio = f->tm_sec;

		getrusage(RUSAGE_SELF, &r_usage_s);
			
		if((float)f->tm_sec - inicio == tempo)
		{
			printf("\nUso do processador apos %.0f segundos:\n",tempo);
			//printf("\nTempo de processamento (user) (child): %ld.%06ld\n", r_usage_s.ru_utime.tv_sec, r_usage_s.ru_utime.tv_usec);
			//printf("\nTempo de processamento (system) (child): %ld.%06ld\n", r_usage_s.ru_stime.tv_sec, r_usage_s.ru_stime.tv_usec);
			printf("Uso do processador (user) (percentage): %.2lf%%\n", (r_usage_s.ru_utime.tv_sec + ((1.0/1000000) * r_usage_s.ru_utime.tv_usec)) / 10 * 100);
			printf("Uso do processador (system) (percentage): %.2lf%%\n", (r_usage_s.ru_stime.tv_sec + ((1.0/1000000) * r_usage_s.ru_stime.tv_usec)) / 10 * 100);
			tempo+=1.000000;
		} 				
	}
    }

	//TODO se argv[1] for igual a 'cpu-mem', executar código com utilização intensa da UCP e da memória:
    else if(strcmp(argv[1], "cpu-mem") == 0)
    {
        while(1)
	{
		fim = time(0);
		f = localtime(&fim);

		if(inicio == -1)
			inicio = f->tm_sec;

		getrusage(RUSAGE_SELF, &r_usage_s);
			
		if((float)f->tm_sec - inicio == tempo)
		{
			printf("\nUso de memoria apos %.0f segundos: %ld\n",tempo, r_usage_s.ru_maxrss);
			//printf("\nTempo de processamento (user) (child): %ld.%06ld\n", r_usage_s.ru_utime.tv_sec, r_usage_s.ru_utime.tv_usec);
			//printf("\nTempo de processamento (system) (child): %ld.%06ld\n", r_usage_s.ru_stime.tv_sec, r_usage_s.ru_stime.tv_usec);
			printf("Uso do processador (user) (percentage): %.2lf%%\n", (r_usage_s.ru_utime.tv_sec + ((1.0/1000000) * r_usage_s.ru_utime.tv_usec)) / 10 * 100);
			printf("Uso do processador (system) (percentage): %.2lf%%\n", (r_usage_s.ru_stime.tv_sec + ((1.0/1000000) * r_usage_s.ru_stime.tv_usec)) / 10 * 100);
			tempo+=1.000000;
		} 				
		malloc(10);
	}
    }

}
perror ("Erro: ") ; /* execve não funcionou || execve has not worked*/

printf ("Tchau !\n") ;
exit(0) ; /* encerra o processo com sucesso (código 0) || terminates the process successfully (code 0)*/

}
