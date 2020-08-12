 #include "Server.h"

 int nsock;
 void s_action(int sig){
        close(nsock);
        printf("SERVER: got SIGPIPE.\n");
    }

void Server::StartServer()
 {
     // Объявление локалных переменных и структур данных
    char buffer[LBUF];
    char buffer2[LBUF2] = "success\n";
    struct sockaddr_in client, server;
    int n, sock, s_len, fil, fil2;
    socklen_t c_len = LEN;
    time_t t;
    struct tm *timeinfo;
    static struct sigaction sact;
    sact.sa_handler = s_action;
    sigfillset(&(sact.sa_mask));
    sigaction(SIGPIPE, &sact, NULL);

    // Создание сокета сервера
    if ((sock = socket(AF_INET, SOCK_STREAM, 0)) < 0){
        printf("SERVER: unable to create socket.\n");
        exit(1);
    }
    
    // Задание адреса своего сокета
    bzero(&server, LEN);
    server.sin_family = AF_INET;
    server.sin_port = 1305;
    server.sin_addr.s_addr = INADDR_ANY;
    int optval = 1;
    setsockopt(sock, SOL_SOCKET, SO_REUSEADDR, &optval, sizeof(optval));

    // Связывание сокета сервера с его адресом
    if ((bind(sock, (struct sockaddr *) &server, LEN)) < 0){
        printf("SERVER: unable to bind socket.\n");
        exit(1);
    }

    // Создание очереди запросов на создание соединений
    if ((listen(sock, 1)) < 0){
        printf("SERVER: unable to create queue.\n");
        exit(1);
    }

    // Бесконечный цикл приема запросов клиентов на создание соединений
    for (;;){
        
        // Выборка из очереди запросов на создание соединения
        if ((nsock = accept(sock, (struct sockaddr *) &client, &c_len)) < 0){
            printf("SERVER: unable to pull from queue.\n");
            continue;
        }

        // Создание дочернего процесса для обслуживания сединения
        if (fork() == 0){
            memset(buffer, 0, LBUF);
            n = read(nsock, buffer, LBUF);
            if (n < 0){
                printf("SERVER: recieving error.\n");
                exit(1);
            }

            //printf(buffer);
            if(CheckSum(buffer) != 0)
                printf("Сумма больше двух символов или не кратна 32\n");
            else{
                printf("Данные получены.\n");
                printf(buffer);
                printf("Проверка пройдена успешно\n");
            }
            write(nsock,buffer2, LBUF2);

            // Завершение дочернего процесса
            close(nsock);
            exit(0);
        }

        // В главном процессе новый сокет не нужен
        close(nsock);
    }
 }

 // Проверка суммы
int Server::CheckSum(char *msg)
    {
        int ia = atoi(msg);
        if (strlen(msg) > 2 && (ia % 32 == 0))
            return 0;
        else return 1;
    }
