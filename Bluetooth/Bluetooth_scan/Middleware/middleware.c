
void m_lista_dispositivos_cercanos_Bluetooth (int pipe) {
	// Creación de un proceso aparte para evitar bloqueo
    int pid;
      pid = fork();
      switch(pid){
        case -1: // Si pid es -1 quiere decir que ha habido un error
         fprintf(pipe, "No se ha podido crear el proceso\n");
         break;
        case 0: 
		 // Cuando pid es cero quiere decir que es el proceso hijo
         // Llamada al conjunto de funciones	
		  char str[16];
          snprintf(str, 16, "%d", pipe);
          execlp("lista_dispositivos_cercanos_Bluetooth", , 0);
		  fprintf(pipe, "No se ha podido realizar el exec\n");
          break;
        default: // Cuando es distinto de cero es el padre
          break;
      }
}

void m_lista_dispositivos_emparejados_Bluetooth (int pipe) {
	// Creación de un proceso aparte para evitar bloqueo
    int pid;
      pid = fork();
      switch(pid){
        case -1: // Si pid es -1 quiere decir que ha habido un error
         fprintf(pipe, "No se ha podido crear el proceso\n");
         break;
        case 0: 
		 // Cuando pid es cero quiere decir que es el proceso hijo
         // Llamada al conjunto de funciones	
		  char str[16];
          snprintf(str, 16, "%d", pipe);
          execlp("lista_dispositivos_emparejados_Bluetooth", , 0);
		  fprintf(pipe, "No se ha podido realizar el exec\n");
          break;
        default: // Cuando es distinto de cero es el padre
          break;
      }
}

void m_lista_dispositivos_todos_Bluetooth (int pipe) {
	// Creación de un proceso aparte para evitar bloqueo
    int pid;
      pid = fork();
      switch(pid){
        case -1: // Si pid es -1 quiere decir que ha habido un error
         fprintf(pipe, "No se ha podido crear el proceso\n");
         break;
        case 0: 
		 // Cuando pid es cero quiere decir que es el proceso hijo
         // Llamada al conjunto de funciones	
		  char str[16];
          snprintf(str, 16, "%d", pipe);
          execlp("lista_dispositivos_todos_Bluetooth", , 0);
		  fprintf(pipe, "No se ha podido realizar el exec\n");
          break;
        default: // Cuando es distinto de cero es el padre
          break;
      }
}

