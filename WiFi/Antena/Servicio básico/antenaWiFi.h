/*
 * Codigo de scaneo de WiFi
 * PERIMETER SECURITY G
 * GISAI 2017
 */


#ifndef ANTENAWIFI_H_
#define ANTENAWIFI_H_

static void get_scan_result(void);
static void on_scan_result(void*, void*);
static void on_scan_timeout(void*);
artik_error test_wifi_scan(void);
int main(int, char*[]);


#endif /* ANTENAWIFI_H_ */
