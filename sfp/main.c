#include <stdio.h>
#include <conio.h>
#include <time.h>

struct processo {
int pid;
int cycles_required;
int cycles_executados;
int cpu_cycles;
enum { CPU, HD, IMPRESSORA, VIDEO } device_required;
int device_cycles;
int device_cycles_executados;
enum  { CRIADO, APTO, EXECUTANDO, BLOQUEADO, DESTRUIDO } state;
};

void delay(int milliseconds);

int main ()
{
int nproc=20, vtemp=2,i=0,x;

struct processo procs[nproc];

int fila_hd[nproc];
int fila_hd_ultimo = 0;

int fila_video[nproc];
int fila_video_ultimo = 0;

int fila_impressora[nproc];
int fila_impressora_ultimo = 0;

int fila_cpu[nproc];
int fila_cpu_ultimo = 0;

int sorteio_device = 0;

int temp = 0;

srand (time(NULL)); //renova o seed do rand

//inicializa os processos
for(x=0; x < nproc; x++){
    procs[x].pid = x;
    procs[x].cycles_required = (100 + rand() %200); // define os cyclos de CPU necessarios 100~300
    procs[x].device_required = CPU;
    procs[x].cycles_executados = 0;
    procs[x].cpu_cycles = 0;
    procs[x].device_cycles = 0;
    procs[x].device_cycles_executados = 0;
    procs[x].state = CRIADO;
    fila_cpu[fila_cpu_ultimo] = x;
    fila_cpu_ultimo++;
}

do{
    //executa o HD
    if(fila_hd_ultimo >= 1){
        procs[fila_hd[0]].device_cycles_executados++;
        printf("\n\nHD pid:%d ciclos:%d",procs[fila_hd[0]].pid,procs[fila_hd[0]].device_cycles_executados);
        if(procs[fila_hd[0]].device_cycles_executados >= procs[fila_hd[0]].device_cycles ){
            procs[fila_hd[0]].device_required = CPU;
            fila_cpu[fila_cpu_ultimo] = fila_hd[0];
            fila_cpu_ultimo++;
            for(x=0; x <= fila_hd_ultimo; x++){ //move os processos para frente na fila
                fila_hd[x] = fila_hd[x+1];
            }
            fila_hd_ultimo--;
        }
    }
    printf("\n fila_hd_ultimo: %d", fila_hd_ultimo);
    printf("\n FILA HD\n");
    for(x=0;x<fila_hd_ultimo;x++){
        printf("%d ", procs[fila_hd[x]].pid);
    }

    //executa a Impressora
    if(fila_impressora_ultimo >= 1){
        procs[fila_impressora[0]].device_cycles_executados++;
        printf("\n\nIMPRESSORA pid:%d ciclos:%d",procs[fila_impressora[0]].pid,procs[fila_impressora[0]].device_cycles_executados);
        if(procs[fila_impressora[0]].device_cycles_executados >= procs[fila_impressora[0]].device_cycles ){
            procs[fila_impressora[0]].device_required = CPU;
            fila_cpu[fila_cpu_ultimo] = fila_impressora[0];
            fila_cpu_ultimo++;
            for(x=0; x <= fila_impressora_ultimo; x++){ //move os processos para frente na fila
                fila_impressora[x] = fila_impressora[x+1];
            }
            fila_impressora_ultimo--;
        }
    }
    printf("\n fila_impressora_ultimo: %d", fila_impressora_ultimo);
    printf("\n FILA IMPRESSORA\n");
    for(x=0;x<fila_impressora_ultimo;x++){
        printf("%d ", procs[fila_impressora[x]].pid);
    }

    //executa o Video
    if(fila_video_ultimo >= 1){
        procs[fila_video[0]].device_cycles_executados++;
        printf("\n\nVIDEO pid:%d ciclos:%d",procs[fila_video[0]].pid,procs[fila_video[0]].device_cycles_executados);
        if(procs[fila_video[0]].device_cycles_executados >= procs[fila_video[0]].device_cycles ){
            procs[fila_video[0]].device_required = CPU;
            fila_cpu[fila_cpu_ultimo] = fila_video[0];
            fila_cpu_ultimo++;
            for(x=0; x <= fila_video_ultimo; x++){ //move os processos para frente na fila
                fila_video[x] = fila_video[x+1];
            }
            fila_video_ultimo--;
        }
    }
    printf("\n fila_video_ultimo: %d", fila_video_ultimo);
    printf("\n FILA VIDEO\n");
    for(x=0;x<fila_video_ultimo;x++){
        printf("%d ", procs[fila_video[x]].pid);
    }
printf("\n");
    //executa o CPU
    if(fila_cpu_ultimo >= 1){
        procs[fila_cpu[0]].cycles_executados++;
        procs[fila_cpu[0]].cpu_cycles++;
        printf("\n\npid:%d ciclos:%d",procs[fila_cpu[0]].pid,procs[fila_cpu[0]].cycles_executados);

        //limita a 50 ciclos maximos de CPU
        if(procs[fila_cpu[0]].cpu_cycles > 50){
            procs[fila_cpu[0]].cpu_cycles = 0;// zera o contador de ciclos de cpu
            temp = fila_cpu[0]; //copia para temp o primeiro processo //fila_cpu[fila_cpu_ultimo+1] = fila_cpu[0]; //copia para o endereço apos o ultimo, o primeiro da fila
            for(x=0; x <= fila_cpu_ultimo; x++){ //move os processos para frente na fila
                fila_cpu[x] = fila_cpu[x+1];
            }
            fila_cpu[fila_cpu_ultimo-1] = temp; //coloca de volta o processo no final da fila
        }
        if(rand() %1000 < 10){
            procs[fila_cpu[0]].device_cycles_executados = 0; //zera os ciclos de dispositivo
            sorteio_device = (rand() %3);
            switch ( sorteio_device )
              {
                 case 0 : //HD
                   procs[fila_cpu[0]].device_required = HD;
                   procs[fila_cpu[0]].device_cycles = (200 + rand() %100);
                   fila_hd[fila_hd_ultimo] = fila_cpu[0];
                   fila_hd_ultimo++;
                   for(x=0; x <= fila_cpu_ultimo; x++){ //move os processos para frente na fila
                        fila_cpu[x] = fila_cpu[x+1];
                    }
                    fila_cpu_ultimo--;
                 break;

                 case 1 : //Impressora
                   procs[fila_cpu[0]].device_required = IMPRESSORA;
                   procs[fila_cpu[0]].device_cycles = (100 + rand() %100);
                   fila_impressora[fila_impressora_ultimo] = fila_cpu[0];
                   fila_impressora_ultimo++;
                   for(x=0; x <= fila_cpu_ultimo; x++){ //move os processos para frente na fila
                        fila_cpu[x] = fila_cpu[x+1];
                    }
                   fila_cpu_ultimo--;
                 break;

                 case 2 : //Video
                   procs[fila_cpu[0]].device_required = VIDEO;
                   procs[fila_cpu[0]].device_cycles = (500 + rand() %100);
                   fila_video[fila_video_ultimo] = fila_cpu[0];
                   fila_video_ultimo++;
                   for(x=0; x <= fila_cpu_ultimo; x++){ //move os processos para frente na fila
                        fila_cpu[x] = fila_cpu[x+1];
                    }
                    fila_cpu_ultimo--;
                 break;
              }
        }
        if(fila_cpu_ultimo >= 1){
            if(procs[fila_cpu[0]].cycles_executados >= procs[fila_cpu[0]].cycles_required ){
                procs[fila_cpu[0]].device_required = CPU;
                for(x=0; x <= fila_cpu_ultimo; x++){ //move os processos para frente na fila
                    fila_cpu[x] = fila_cpu[x+1];
                }
                fila_cpu_ultimo--;
            }
        }
    }
    printf("\n fila_cpu_ultimo: %d", fila_cpu_ultimo);
    printf("\n FILA CPU\n");
    for(x=0;x<fila_cpu_ultimo;x++){
        printf("%d ", procs[fila_cpu[x]].pid);
    }
    delay(100);
printf("\n sorteio=%d\n", sorteio_device);
//for(x=0;x<nproc;x++){
//printf("\n ultimo_cpu %d\n", procs[fila_cpu[fila_cpu_ultimo]]);
//}




printf("\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n");
}while(fila_cpu_ultimo > 0 || fila_hd_ultimo > 0 || fila_video_ultimo > 0 || fila_impressora_ultimo > 0);

/*for(x=0; x<nproc; x++){
    printf("\npid=%d ciclos=%d", procs[x].pid, procs[x].cycles_required);
}*/
printf("\n tcharam! \n");
getch();
return(0);

}

void delay(int milliseconds)
{
    long pause;
    clock_t now,then;

    pause = milliseconds*(CLOCKS_PER_SEC/1000);
    now = then = clock();
    while( (now-then) < pause )
        now = clock();
}
