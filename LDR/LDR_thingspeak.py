import machine
import urequests
import network
import time

# Define el pin ADC que estás utilizando (GPIO13)
ldr_pin = machine.ADC(machine.Pin(32))

HTTP_HEADERS = {'Content-Type': 'application/json'}
THINGSPEAK_WRITE_API_KEY = '45AP4F57Z6A6T5QZ'  # Reemplaza con tu clave API

UPDATE_TIME_INTERVAL = 2000  # Intervalo de actualización en ms
last_update = time.ticks_ms()

ssid = 'UNI_LIBRE_H'
password = '123456789'

# Configurar ESP32 como estación (conectarse a Wi-Fi)
sta_if = network.WLAN(network.STA_IF)
sta_if.active(True)

if not sta_if.isconnected():
    print('Conectando a la red...')
    sta_if.connect(ssid, password)
    while not sta_if.isconnected():
        pass
print('Configuración de red:', sta_if.ifconfig())

while True:
    if time.ticks_ms() - last_update >= UPDATE_TIME_INTERVAL:
        # Leer el valor analógico del LDR
        ldr_value = ldr_pin.read()

        # Datos a enviar a ThingSpeak
        ldr_readings = {'field1': ldr_value}
        
        # Enviar datos a ThingSpeak utilizando POST
        request = urequests.post('http://api.thingspeak.com/update?api_key=' + THINGSPEAK_WRITE_API_KEY, json=ldr_readings, headers=HTTP_HEADERS)
        request.close()
        print(ldr_readings)

        # Actualizar el tiempo de la última actualización
        last_update = time.ticks_ms()