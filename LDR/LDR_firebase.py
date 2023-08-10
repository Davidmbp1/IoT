import machine
import urequests
import network
import time
import json

# Define el pin ADC que estás utilizando (GPIO13)
ldr_pin = machine.ADC(machine.Pin(32))

ssid = 'NATALY'
password = '8182181AB'

firebase_url = 'https://ldr-esp32-1f4c8-default-rtdb.firebaseio.com/'
firebase_secret = 'VbwvjAlaEUpSSz2lmQ2TZ3rmNN0RqqF2M07bKmi3'
NODE_PATH = 'ldr.json'

UPDATE_TIME_INTERVAL = 2000  # Intervalo de actualización en ms
last_update = time.ticks_ms()

# Configurar ESP32 como estación (conectarse a Wi-Fi)
sta_if = network.WLAN(network.STA_IF)
sta_if.active(True)

if not sta_if.isconnected():
    print('Conectando a la red...')
    sta_if.connect(ssid, password)
    while not sta_if.isconnected():
        pass
print('Configuración de red:', sta_if.ifconfig())

# cont = 0  # Contador de lecturas

while True:
    if time.ticks_ms() - last_update >= UPDATE_TIME_INTERVAL:
        # Leer el valor analógico del LDR
        ldr_value = ldr_pin.read()

        # Construir el objeto de datos a enviar a Firebase

        # ldr_data = {'ldr_value': ldr_value}
        ldr_data = {'reading': reading_count, 'ldr_value': ldr_value}

        # Enviar los datos a Firebase utilizando POST para agregar una nueva fila
        headers = {'Content-Type': 'application/json'}
        url = f'{firebase_url}/{NODE_PATH}?auth={firebase_secret}'
        # response = urequests.put(url, data=json.dumps(ldr_data), headers=headers)
        response = urequests.post(url, data=json.dumps(ldr_data), headers=headers)
        response.close()
        print(ldr_data)

        # Incrementar el contador de lecturas
        cont = cont + 1

        # Actualizar el tiempo de la última actualización
        last_update = time.ticks_ms()