import machine
import time

# Define el pin ADC que estás utilizando (GPIO04)
ldr_pin = machine.ADC(machine.Pin(13))  # El número del pin puede variar, ajusta según tu configuración

# Configura el puerto serial
uart = machine.UART(0, baudrate=115200, tx=17, rx=16)

while True:
    # Lee el valor analógico del pin ADC (rango: 0-4095)
    ldr_value = ldr_pin.read()

    # Imprime el valor leído en el puerto serial
    uart.write("Valor del LDR: {}\n".format(ldr_value))

    # Espera un breve período antes de la siguiente lectura
    time.sleep(0.5)