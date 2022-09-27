1 udp
  （1）编译udp  
    基于arm
  aarch64-linux-gnu-gcc -o udp_server_arm udp_server.c 
  aarch64-linux-gnu-gcc -o udp_client_arm udp_client.c
    基于x86
   gcc -o  udp_server udp_server.c 
   gcc -o  udp_client udp_client.c
   （2）移植 scp
   （3）执行(ip地址为服务端ip地址）
        ./udp_client_arm 192.168.1.11 9000   命令先
        ./udp_server_arm 192.168.1.11 9000   命令后
    (4) 同理x86
     
2 tcp
  （1）编译tcp  
    基于arm
  aarch64-linux-gnu-gcc -o tcp_server_arm tcp_server.c 
  aarch64-linux-gnu-gcc -o tcp_client_arm tcp_client.c
    基于x86
   gcc -o  tcp_server  tcp_server.c 
   gcc -o  tcp_client  tcp_client.c
   （2）移植 scp
   （3）执行(ip地址为服务端ip地址）
        ./tcp_client_arm 192.168.1.11 9000  命令后
        ./tcp_server_arm 192.168.1.11 9000  命令先
    (4) 同理x86
