#include <stdio.h>
#include <netinet/in.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <unistd.h>


int creer_serveur(int port){
  int socket_serveur;
  socket_serveur = socket(AF_INET, SOCK_STREAM,0);
  /*Creer la socket serveur*/
  if( socket_serveur == -1){
    printf("%d",errno);
    perror("socket");
    exit(1);
  }
  struct sockaddr_in saddr;
  saddr.sin_family = AF_INET;
  saddr.sin_port = htons(port);
  saddr.sin_addr.s_addr = INADDR_ANY;
  /* Configure le socket et attache l'interface reseau*/
  if(bind(socket_serveur, (struct sockaddr *)&saddr, sizeof(saddr)) == -1){
    printf("%d", errno);
    perror("bind socket_serveur");
    //exit(1);
  }
  /* Demarrer attente de connexion */
  if(listen(socket_serveur,10) == -1){
      printf("%d", errno);
      perror("listen socket_serveur");
      exit(1);
    }
    int socket_client;
    socket_client = accept(socket_serveur, NULL,NULL);
    if(socket_client == -1){
      perror("accept");
      printf("connexion fermée");
      exit(1);
    }
    const char *message_bienvenue = "Lorem ipsum dolor sit amet, consectetur adipiscing elit. Suspendisse suscipit convallis nunc, in placerat dolor sodales id. Nulla imperdiet nunc in turpis pulvinar ullamcorper. Proin placerat aliquet mauris id mattis. Praesent iaculis enim dolor, sit amet pharetra ligula rhoncus suscipit. Integer ac urna vel metus mattis vehicula venenatis ut velit. Aenean vel ligula sagittis, mattis sapien nec, rutrum elit. Sed at pretium magna. Sed placerat enim eget purus vestibulum, vel pretium lorem volutpat. Duis tempus in nisl id imperdiet. Morbi ac consectetur felis. Duis gravida, erat et lobortis feugiat, sapien magna ornare nisi, id finibus sem nisl eget sapien.\n ";
    while(1){
    write(socket_client, message_bienvenue, strlen(message_bienvenue));
    }
    
    close(socket_serveur);
    close(socket_client);
    return 0;
}
