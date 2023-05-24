'''
    Universidad de Costa Rica
    Laboratorio de Microcontroladores
    Laboratorio 4 - Sismografo
    Estudiantes:  
    - Katharina Alfaro Solís B80251
    - Mauricio Rodríguez Obando B96694
'''

import csv
import time, json
import time
import paho.mqtt.client as mqtt

# En este archivo se leen los datos enviados por el 
# microcontrolador y publica estos en thingsboard de forma
# que realiza la comunicación entre los datos y el dashboard

def on_connect(client, userdata, flags, rc):
    if rc == 0:
        client.connected = True
        print("Conexión establecida exitosamente")
    else: 
        print("Conexión fallida. No se estableció conexión ", rc)
        client.loop_stop()

def on_disconnect(client, userdata, rc):
    if(rc == 0):
        print("Desconexión exitosa")
    else:
        print("Sistema desconectado mediante el código: ", rc)

def on_publish(client, userdata, mid):
    print("En medio de llamada on_publish", mid)
