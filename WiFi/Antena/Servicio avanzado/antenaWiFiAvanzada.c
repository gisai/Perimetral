/*
 * Codigo de scaneo de WiFi con servicio Avanzado
 * PERIMETER SECURITY
 * GISAI 2017
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <time.h>

#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>

#include <artik_module.h>
#include <artik_loop.h>
#include <artik_wifi.h>

#define CHECK_RET(x)	{ if (x != S_OK) goto exit; }
#define PORT 80

#define MAXDATASIZE 100
/* El número máximo de datos en bytes */

int antenaID = 1;
int powDevices = 0;
char sistemaID [] = "PERIMETER";
char psk [] = "1234";

int fd, numbytes;
/* ficheros descriptores */

char buf[MAXDATASIZE];
/* en donde es almacenará el texto recibido */

struct hostent *he;
/* estructura que recibirá información sobre el nodo remoto */

struct sockaddr_in server;
/* información sobre la dirección del servidor */


artik_error test_wifi_connect(char name[])
{
	artik_loop_module *loop = (artik_loop_module *)
					artik_request_api_module("loop");
	artik_wifi_module *wifi = (artik_wifi_module *)
					artik_request_api_module("wifi");
	artik_error ret = S_OK;

	ret = wifi->init(ARTIK_WIFI_MODE_STATION);
	if (ret != S_OK)
		goto exit;
	ret = wifi->connect(name, psk, 0);
	if (ret != S_OK)
		goto exit;

	loop->run();

	if ((he=gethostbyname(name))==NULL){
	      /* llamada a gethostbyname() */
	      printf("gethostbyname() error\n");
	      exit(-1);
   }

   if ((fd=socket(AF_INET, SOCK_STREAM, 0))==-1){
	  /* llamada a socket() */
	  printf("socket() error\n");
	  exit(-1);
   }

   server.sin_family = AF_INET;
  server.sin_port = htons(PORT);
  /* htons() es necesaria nuevamente ;-o */
  server.sin_addr = *((struct in_addr *)he->h_addr);
  /*he->h_addr pasa la información de ``*he'' a "h_addr" */
  bzero(&(server.sin_zero),8);

  if(connect(fd, (struct sockaddr *)&server,
	 sizeof(struct sockaddr))==-1){
	 /* llamada a connect() */
	 printf("connect() error\n");
	 exit(-1);
  }

  if ((numbytes=recv(fd,buf,MAXDATASIZE,0)) == -1){
	 /* llamada a recv() */
	 printf("Error en recv() \n");
	 exit(-1);
  }

  buf[numbytes]='\0';

  printf("Mensaje del Servidor: %s\n",buf);
  /* muestra el mensaje de bienvenida del servidor =) */

  close(fd);   /* cerramos fd =) */

	wifi->deinit();

exit:
	fprintf(stdout, "TEST: %s %s\n", __func__,
		(ret == S_OK) ? "succeeded" : "failed");

	artik_release_api_module(loop);
	artik_release_api_module(wifi);

	return ret;
}



/*
 * Función de escritura
 */
static void get_scan_result(void)
{
	artik_wifi_module *wifi = (artik_wifi_module *)artik_request_api_module("wifi");
	artik_wifi_ap *list = NULL;
	int count = 0;
	int ret = 0;
	int i = 0;

	ret = wifi->get_scan_result(&list, &count);
	CHECK_RET(ret);

	char options[] = test_wifi_connect(list[i].name);

	for (i = 0; i < count; i++)
		printf("{ID: {IDSystem:%s, IDGroup:%s, IDPerson:%-17s}, IDAnte:%i, pow:%i, rssi:%i, time:%i, options:%s}\n",
				sistemaID, list[i].name, list[i].bssid, antenaID, powDevices, list[i].signal_level, (unsigned int)time(NULL), options);

	free(list);
	artik_release_api_module(wifi);



	return;

exit:

	artik_release_api_module(wifi);
	fprintf(stdout, "failed");
}

/*
 * Callback para los eventos de detección
 */
static void on_scan_result(void *result, void *user_data)
{
	artik_loop_module *loop = (artik_loop_module *)artik_request_api_module("loop");
	artik_wifi_module *wifi = (artik_wifi_module *)artik_request_api_module("wifi");

	get_scan_result();

	wifi->deinit();
	loop->quit();

	artik_release_api_module(loop);
	artik_release_api_module(wifi);
}

/*
 * Calback por timeout
 */
static void on_scan_timeout(void *user_data)
{
	artik_loop_module *loop = (artik_loop_module *)artik_request_api_module("loop");
	artik_wifi_module *wifi = (artik_wifi_module *)artik_request_api_module("wifi");

	get_scan_result();

	wifi->deinit();
	loop->quit();

	artik_release_api_module(loop);
	artik_release_api_module(wifi);
}

/*
 * Función para iniciar escaneo
 */
artik_error test_wifi_scan(void)
{
	artik_loop_module *loop = (artik_loop_module *)artik_request_api_module("loop");
	artik_wifi_module *wifi = (artik_wifi_module *)artik_request_api_module("wifi");
	artik_error ret;
	int timeout_id = 0;

	ret = wifi->init(ARTIK_WIFI_MODE_STATION);
	CHECK_RET(ret);
	ret = wifi->set_scan_result_callback(on_scan_result, NULL);
	CHECK_RET(ret);
	ret = wifi->scan_request();
	CHECK_RET(ret);

	loop->add_timeout_callback(&timeout_id, 3 * 1000, on_scan_timeout,
				   NULL);
	loop->run();

exit:
	artik_release_api_module(loop);
	artik_release_api_module(wifi);

	return ret;
}

/*
 * Función main
 */
int main(int argc, char *argv[])
{
	artik_error ret = S_OK;

	if (!artik_is_module_available(ARTIK_MODULE_WIFI)) {
		fprintf(stdout,
			"TEST: Wifi module is not available, skipping...\n");
		return -1;
	}
	fprintf(stdout, "WIFI SCAN PERIMETER: %s starting\n", __func__);

	while (1) {
		ret = test_wifi_scan();
		sleep(1);
	}

	CHECK_RET(ret);

exit:
	return (ret == S_OK) ? 0 : -1;
}
