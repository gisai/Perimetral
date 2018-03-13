/*
 * Codigo de scaneo de WiFi
 * PERIMETER SECURITY G
 * GISAI 2017
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <time.h>

#include <artik_module.h>
#include <artik_loop.h>
#include <artik_wifi.h>

#define CHECK_RET(x)	{ if (x != S_OK) goto exit; }

int antenaID = 1;
int powDevices = 0;
char sistemaID [] = "PERIMETER";


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

	for (i = 0; i < count; i++)
		printf("{ID: {IDSystem:%s, IDGroup:%s, IDPerson:%-17s}, IDAnte:%i, pow:%i, rssi:%i, time:%i}\n",
				sistemaID, list[i].name, list[i].bssid, antenaID, powDevices, list[i].signal_level, (unsigned int)time(NULL));

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
