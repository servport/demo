#include <stdio.h>

int main(){
/*
TCP SERVER
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>

int main(int argc, char *argv[])
{
    int sockfd, newsockfd, portno;
    char buffer[100];
    struct sockaddr_in serv_addr, cli_addr;
    socklen_t clilen;

    sockfd = socket(AF_INET, SOCK_STREAM, 0);

    bzero(&serv_addr, sizeof(serv_addr));
    portno = atoi(argv[1]);

    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = INADDR_ANY;
    serv_addr.sin_port = htons(portno);

    bind(sockfd, (struct sockaddr *)&serv_addr, sizeof(serv_addr));
    listen(sockfd, 5);

    clilen = sizeof(cli_addr);
    newsockfd = accept(sockfd, (struct sockaddr *)&cli_addr, &clilen);

    bzero(buffer, 100);
    read(newsockfd, buffer, 100);
    printf("Client message: %s\n", buffer);

    write(newsockfd, "Message received", 16);

    close(newsockfd);
    close(sockfd);
    return 0;
}


TCP CLIENT
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>

int main(int argc, char *argv[])
{
    int sockfd, portno;
    char buffer[100];
    struct sockaddr_in serv_addr;
    struct hostent *server;

    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    portno = atoi(argv[2]);

    server = gethostbyname(argv[1]);

    bzero(&serv_addr, sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    bcopy(server->h_addr, &serv_addr.sin_addr.s_addr, server->h_length);
    serv_addr.sin_port = htons(portno);

    connect(sockfd, (struct sockaddr *)&serv_addr, sizeof(serv_addr));

    printf("Enter message: ");
    fgets(buffer, 100, stdin);

    write(sockfd, buffer, strlen(buffer));
    read(sockfd, buffer, 100);

    printf("Server reply: %s\n", buffer);

    close(sockfd);
    return 0;
}


UDP SERVER:
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>

int main(int argc, char *argv[])
{
    int sockfd, portno;
    char buffer[100];
    struct sockaddr_in serv_addr, cli_addr;
    socklen_t len;

    sockfd = socket(AF_INET, SOCK_DGRAM, 0);

    bzero(&serv_addr, sizeof(serv_addr));
    portno = atoi(argv[1]);

    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = INADDR_ANY;
    serv_addr.sin_port = htons(portno);

    bind(sockfd, (struct sockaddr *)&serv_addr, sizeof(serv_addr));

    len = sizeof(cli_addr);
    recvfrom(sockfd, buffer, 100, 0,
             (struct sockaddr *)&cli_addr, &len);

    printf("Client message: %s\n", buffer);

    sendto(sockfd, "UDP message received", 20, 0,
           (struct sockaddr *)&cli_addr, len);

    close(sockfd);
    return 0;
}


UDP CLIENT:
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>

int main(int argc, char *argv[])
{
    int sockfd, portno;
    char buffer[100];
    struct sockaddr_in serv_addr;
    struct hostent *server;
    socklen_t len;

    sockfd = socket(AF_INET, SOCK_DGRAM, 0);
    portno = atoi(argv[2]);

    server = gethostbyname(argv[1]);

    bzero(&serv_addr, sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    bcopy(server->h_addr, &serv_addr.sin_addr.s_addr, server->h_length);
    serv_addr.sin_port = htons(portno);

    printf("Enter message: ");
    fgets(buffer, 100, stdin);

    sendto(sockfd, buffer, strlen(buffer), 0,
           (struct sockaddr *)&serv_addr, sizeof(serv_addr));

    len = sizeof(serv_addr);
    recvfrom(sockfd, buffer, 100, 0,
             (struct sockaddr *)&serv_addr, &len);

    printf("Server reply: %s\n", buffer);

    close(sockfd);
    return 0;
}


---TCP---
🔹 TCP SERVER (Array Sender)

📄 tcp_server_array.c

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>

int main(int argc, char *argv[])
{
    int sockfd, newsockfd, portno;
    int arr[5] = {5, 2, 9, 1, 3};
    int n = 5;
    struct sockaddr_in serv_addr, cli_addr;
    socklen_t clilen;

    sockfd = socket(AF_INET, SOCK_STREAM, 0);

    bzero(&serv_addr, sizeof(serv_addr));
    portno = atoi(argv[1]);

    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = INADDR_ANY;
    serv_addr.sin_port = htons(portno);

    bind(sockfd, (struct sockaddr *)&serv_addr, sizeof(serv_addr));
    listen(sockfd, 5);

    clilen = sizeof(cli_addr);
    newsockfd = accept(sockfd, (struct sockaddr *)&cli_addr, &clilen);

    write(newsockfd, &n, sizeof(n));
    write(newsockfd, arr, sizeof(arr));

    read(newsockfd, arr, sizeof(arr));

    printf("Sorted array received from client:\n");
    for (int i = 0; i < n; i++)
        printf("%d ", arr[i]);

    printf("\n");

    close(newsockfd);
    close(sockfd);
    return 0;
}

🔍 SERVER EXPLANATION (important lines only)
int arr[5] = {5, 2, 9, 1, 3};


→ Array to be sorted

int n = 5;


→ Number of elements (sent first)

write(newsockfd, &n, sizeof(n));


→ Send array size to client

write(newsockfd, arr, sizeof(arr));


→ Send actual array

read(newsockfd, arr, sizeof(arr));


→ Receive sorted array back

🔹 TCP CLIENT (Array Sorter)

📄 tcp_client_array.c

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>

void sort(int arr[], int n)
{
    int temp;
    for (int i = 0; i < n - 1; i++)
        for (int j = i + 1; j < n; j++)
            if (arr[i] > arr[j])
            {
                temp = arr[i];
                arr[i] = arr[j];
                arr[j] = temp;
            }
}

int main(int argc, char *argv[])
{
    int sockfd, portno, n;
    int arr[10];
    struct sockaddr_in serv_addr;
    struct hostent *server;

    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    portno = atoi(argv[2]);

    server = gethostbyname(argv[1]);

    bzero(&serv_addr, sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    bcopy(server->h_addr, &serv_addr.sin_addr.s_addr, server->h_length);
    serv_addr.sin_port = htons(portno);

    connect(sockfd, (struct sockaddr *)&serv_addr, sizeof(serv_addr));

    read(sockfd, &n, sizeof(n));
    read(sockfd, arr, sizeof(int) * n);

    sort(arr, n);

    write(sockfd, arr, sizeof(int) * n);

    close(sockfd);
    return 0;
}

🔍 CLIENT EXPLANATION
read(sockfd, &n, sizeof(n));


→ Receives array size

read(sockfd, arr, sizeof(int) * n);


→ Receives array

sort(arr, n);


→ Sorts array (simple bubble-style logic)

write(sockfd, arr, sizeof(int) * n);


→ Sends sorted array back to server

🔹 HOW TO RUN IN LINUX TERMINAL
1️⃣ Compile
gcc tcp_server_array.c -o server
gcc tcp_client_array.c -o client


📸 Screenshot: successful compilation

2️⃣ Run server (Terminal 1)
./server 2000


📸 Screenshot: server waiting

3️⃣ Run client (Terminal 2)
./client localhost 2000

4️⃣ Server Output
Sorted array received from client:
1 2 3 5 9

--UDP---
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>

int main(int argc, char *argv[])
{
    int sockfd, portno;
    int arr[5] = {7, 3, 9, 1, 4};
    int n = 5;
    struct sockaddr_in serv_addr, cli_addr;
    socklen_t len;

    sockfd = socket(AF_INET, SOCK_DGRAM, 0);

    bzero(&serv_addr, sizeof(serv_addr));
    portno = atoi(argv[1]);

    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = INADDR_ANY;
    serv_addr.sin_port = htons(portno);

    bind(sockfd, (struct sockaddr *)&serv_addr, sizeof(serv_addr));

    len = sizeof(cli_addr);

    recvfrom(sockfd, &n, sizeof(n), 0,
             (struct sockaddr *)&cli_addr, &len);

    sendto(sockfd, arr, sizeof(int) * n, 0,
           (struct sockaddr *)&cli_addr, len);

    recvfrom(sockfd, arr, sizeof(int) * n, 0,
             (struct sockaddr *)&cli_addr, &len);

    printf("Sorted array received from client:\n");
    for (int i = 0; i < n; i++)
        printf("%d ", arr[i]);

    printf("\n");

    close(sockfd);
    return 0;
}
🔍 UDP SERVER EXPLANATION
c
Copy code
socket(AF_INET, SOCK_DGRAM, 0);
→ Creates a UDP socket

c
Copy code
bind(...)
→ Binds server to a fixed port

c
Copy code
recvfrom(sockfd, &n, ...)
→ Waits for client request (array size request)

c
Copy code
sendto(sockfd, arr, ...)
→ Sends array to client

c
Copy code
recvfrom(sockfd, arr, ...)
→ Receives sorted array back

📌 Server does not establish a connection

🟢 UDP CLIENT (Array Sorter)
📄 File: udp_client_array.c

c
Copy code
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>

void sort(int arr[], int n)
{
    int temp;
    for (int i = 0; i < n - 1; i++)
        for (int j = i + 1; j < n; j++)
            if (arr[i] > arr[j])
            {
                temp = arr[i];
                arr[i] = arr[j];
                arr[j] = temp;
            }
}

int main(int argc, char *argv[])
{
    int sockfd, portno, n;
    int arr[10];
    struct sockaddr_in serv_addr;
    struct hostent *server;
    socklen_t len;

    sockfd = socket(AF_INET, SOCK_DGRAM, 0);
    portno = atoi(argv[2]);

    server = gethostbyname(argv[1]);

    bzero(&serv_addr, sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    bcopy(server->h_addr, &serv_addr.sin_addr.s_addr, server->h_length);
    serv_addr.sin_port = htons(portno);

    len = sizeof(serv_addr);

    sendto(sockfd, &n, sizeof(n), 0,
           (struct sockaddr *)&serv_addr, len);

    recvfrom(sockfd, arr, sizeof(arr), 0,
             (struct sockaddr *)&serv_addr, &len);

    sort(arr, 5);

    sendto(sockfd, arr, sizeof(int) * 5, 0,
           (struct sockaddr *)&serv_addr, len);

    close(sockfd);
    return 0;
}
🔍 UDP CLIENT EXPLANATION
c
Copy code
sendto(sockfd, &n, ...)
→ Client requests array size (handshake)

c
Copy code
recvfrom(sockfd, arr, ...)
→ Receives array from server

c
Copy code
sort(arr, 5);
→ Sorts array locally

c
Copy code
sendto(sockfd, arr, ...)
→ Sends sorted array back

📌 Client never binds to a port
📌 OS assigns client port automatically

🔹 HOW TO RUN (LINUX TERMINAL)
1️⃣ Compile
bash
Copy code
gcc udp_server_array.c -o udp_server
gcc udp_client_array.c -o udp_client
📸 Screenshot: compilation success

2️⃣ Run Server (Terminal 1)
bash
Copy code
./udp_server 3000
📸 Screenshot: server waiting

3️⃣ Run Client (Terminal 2)
bash
Copy code
./udp_client localhost 3000
4️⃣ Server Output
php
Copy code
Sorted array received from client:
1 3 4 7 9

-------------------------------

CHECKSUM

#include <stdio.h>
int main() {
    int i, c[8], d[8], e[8];
    char f[4][8];

    printf("Enter frame of length 8 bits\n");
    for (i = 0; i < 4; i++) {
        printf("Frame%d: ", i + 1);
        scanf("%s", f[i]);
    }

    for (i = 0; i < 8; i++) {
        c[i] = (int)f[0][i] | (int)f[1][i];
        d[i] = (int)f[2][i] | (int)f[3][i];
        e[i] = c[i] | d[i];
    }

    for (i = 0; i < 8; i++) {
        if (e[i] == 49)
            e[i] = 0;
        else
            e[i] = 1;
    }

    for (i = 0; i < 8; i++) {
        if (e[i] == 1) {
            printf("Errors in the received frame in destination");
            return 0;
        }
    }

    printf("No errors in the received data frames at destination");
    return 0;
}


CRC

#include <stdio.h>

char exor(char a, char b) {
    if ((a == '0' && b == '0') || (a == '1' && b == '1'))
        return '0';
    else
        return '1';
}

int main() {
    int i, j;
    char d[4], dd[9];

    printf("Enter the divisor : ");
    scanf("%s", d);
    printf("Enter the dividend : ");
    scanf("%s", dd);

    for (j = 0; j < 6; j++) {
        if (dd[j] == '0') {
            dd[j] = exor(dd[j], '0');
            dd[j + 1] = exor(dd[j + 1], '0');
            dd[j + 2] = exor(dd[j + 2], '0');
            dd[j + 3] = exor(dd[j + 3], '0');
        } else {
            dd[j] = exor(dd[j], d[0]);
            dd[j + 1] = exor(dd[j + 1], d[1]);
            dd[j + 2] = exor(dd[j + 2], d[2]);
            dd[j + 3] = exor(dd[j + 3], d[3]);
        }
    }

    if (dd[6] == '0' && dd[7] == '0' && dd[8] == '0')
        printf("No error !");
    else
        printf("Error");

    return 0;
}


LRC

#include <stdio.h>

int main() {
    char f[5][9];
    int i, j, count, c = 0;

    printf("Enter frames of length 8\n");
    for (i = 0; i < 5; i++) {
        printf("frame%d: ", i + 1);
        scanf("%s", f[i]);
    }

    for (i = 0; i < 5; i++) {
        count = 0;
        for (j = 0; j < 8; j++) {
            if (f[i][j] == '1')
                count++;
        }
        if (count % 2 != 0) {
            printf("There is an error in frame %d\n", i + 1);
            c = 1;
        }
    }

    if (c == 0)
        printf("No errors in received data destination node");

    return 0;
}


VRC

#include <stdio.h>

int main() {
    char f[8][4];
    int i, j, c = 0, count;

    printf("Enter 8 frames of length 4\n");
    for (i = 0; i < 8; i++) {
        printf("Frame%d: ", i + 1);
        scanf("%s", f[i]);
    }

    for (i = 0; i < 8; i++) {
        count = 0;
        for (j = 0; j < 4; j++)
            if (f[i][j] == '1')
                count++;

        if (count % 2 != 0) {
            printf("There is an error in Frame %d\n", i + 1);
            c = 1;
        }
    }

    if (c == 0)
        printf("No errors in received data at destination node");

    return 0;
}


HAMMING CODE

#include <stdio.h>
#include <string.h>

int main() {
    char code[10];
    int cr1 = 0, cr2 = 0, cr4 = 0;
    int r1, r2, r4;
    int len, binary, decimal = 0, base = 1, rem;

    printf("Enter 7-bit Hamming code: ");
    scanf("%s", code);

    len = strlen(code);

    for (int i = len - 1, pos = 1; i >= 0; i--, pos++) {
        if ((pos == 1 || pos == 3 || pos == 5 || pos == 7) && code[i] == '1') cr1++;
        if ((pos == 2 || pos == 3 || pos == 6 || pos == 7) && code[i] == '1') cr2++;
        if ((pos == 4 || pos == 5 || pos == 6 || pos == 7) && code[i] == '1') cr4++;
    }

    r1 = cr1 % 2;
    r2 = cr2 % 2;
    r4 = cr4 % 2;

    binary = r4 * 100 + r2 * 10 + r1;

    while (binary != 0) {
        rem = binary % 10;
        decimal += rem * base;
        binary /= 10;
        base *= 2;
    }

    if (decimal != 0) {
        printf("Error detected at position %d\n", decimal);
        code[len - decimal] = (code[len - decimal] == '1') ? '0' : '1';
        printf("Corrected Hamming code: %s\n", code);
    } else {
        printf("No error detected in the data\n");
    }

    return 0;
}


PARITY CHECK

#include <stdio.h>

int main() {
    char byte[10], ch;
    int count = 0;

    printf("Enter 8 bit data:");
    scanf("%s", byte);

    printf("Enter 'e' for even parity or 'o' for odd parity: ");
    scanf(" %c", &ch);

    for (int i = 0; i < 8; i++)
        if (byte[i] == '1')
            count++;

    if (ch == 'e') {
        if (count % 2 == 0)
            printf("No error in received Data");
        else
            printf("There is error in received Data");
    } else if (ch == 'o') {
        if (count % 2 == 1)
            printf("No error in received Data");
        else
            printf("There is error in received Data");
    } else {
        printf("Invalid Choice");
    }

    return 0;
}
----------------

1. ifconfig
2. ip
3. traceroute
4. tracepath
5. ping
6. netstat
7. ss
8. dig
9. nslookup
10.route
11.host
12.arp
13.iwconfig
14.hostname
15.curl or wget
16.mtr
17.whois
18.ifplugstatus
19.iftop
20.tcpdum

*/
}
