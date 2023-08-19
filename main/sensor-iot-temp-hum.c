#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "string.h"
#include "esp_wifi.h"
#include "nvs_flash.h"
#include "protocol_examples_common.h"
#include "esp_http_server.h"
#include "dht.h"

extern const char index_start[] asm("_binary_index_html_start");
extern const char index_end[] asm("_binary_index_html_end");

#define SENSOR_TYPE DHT_TYPE_AM2301
#define GPIO_DHT 32

//----------Variables de captura de temperatura y humedad---------//
float temperature = 0, humidity = 0;
//------ Variables mock para enviar al index----------//
int humgerm;

//-----------Handler obtenerdatos---------//
static esp_err_t data_sensor_get_handler(httpd_req_t *req) {
    
    httpd_resp_set_hdr(req, "Content-Type", "application/json");
    char res[100];
    if (humidity > 70) {
        humgerm = 1; //"Riego aereo On";
    }
    else if (humidity<= 70) {
        humgerm = 0; //"Riego aereo Off";
    }

    sprintf(res, "{ \"humidity\": %f, \"temperature\": %f, \"alarma\": %d}", humidity, temperature,humgerm);
    httpd_resp_send(req, res, HTTPD_RESP_USE_STRLEN);
    return ESP_OK;
}

//-------------------Handler Home------------------//
static esp_err_t home_get_handler(httpd_req_t *req) {

    const u_int32_t index_len = index_end - index_start;

    httpd_resp_set_type(req,"text/html");
    httpd_resp_send(req,index_start,index_len);
    return ESP_OK;
}
//-----------Uris--------------------///
static const httpd_uri_t sensor = {
  .uri = "/value",
  .method = HTTP_GET,
  .handler = data_sensor_get_handler
}; 

static const httpd_uri_t home = {
  .uri = "/viewsensor",
  .method = HTTP_GET,
  .handler = home_get_handler
};

//-----------Inicialización del servidor-----------//
void web_server_init() {
  httpd_handle_t server = NULL;
  httpd_config_t config = HTTPD_DEFAULT_CONFIG();

  if (httpd_start(&server, &config) == ESP_OK) {
    httpd_register_uri_handler(server, &sensor);
    httpd_register_uri_handler(server, &home);
    return;
  }
  printf("Error al iniciar servidor\n");
}

//-----------Task para el sensado--------// 
void sensorDHT(void *pvParameters){

    while(1)
    {
        // IP:192,168,10,19
        ESP_ERROR_CHECK(dht_read_float_data(SENSOR_TYPE, GPIO_DHT,  &humidity, &temperature));
         printf("humidity: %f  temperatura: %f\n", humidity,temperature);

        if (temperature < 20.0){
            printf("Pongase saco porque la temperatura actual es: %f\n", temperature);
        }

        vTaskDelay(10000 / portTICK_PERIOD_MS);
    }
}

esp_netif_t* network_interface_ini() {
    nvs_flash_init();
    esp_netif_init();
    esp_event_loop_create_default();
    
    example_connect();
    return esp_netif_get_handle_from_ifkey("WIFI_STA_DEF");
}

void app_main(void)
{
    esp_netif_ip_info_t ip_info;
    esp_netif_t* netif = NULL;
    
    //-----Inicio de la interfaz de red--------//
    netif =  network_interface_ini();
    esp_netif_get_ip_info(netif, &ip_info);
    printf("IP: %d.%d.%d.%d\n", IP2STR(&ip_info.ip));

    if (netif == NULL) {
        printf("No hay interfaz\n");
    } else {
        xTaskCreate(sensorDHT, "sensorDHT", configMINIMAL_STACK_SIZE * 3, NULL, 5, NULL);
        web_server_init();
    }
}
