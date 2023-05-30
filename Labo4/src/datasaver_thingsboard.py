'''
    Universidad de Costa Rica
    Laboratorio de Microcontroladores
    Laboratorio 4 - Sismografo
    Estudiantes:  
    - Katharina Alfaro Solís B80251
    - Mauricio Rodríguez Obando B96694
'''
#!/usr/bin/python3

import time, json
import serial
import paho.mqtt.client as mqtt

# En este archivo se leen los datos enviados por el 
# microcontrolador y publica estos en thingsboard de forma
# que realiza la comunicación entre los datos y el dashboard

def on_connect(client, userdata, flags, rc):
    if (rc == 0):
        client.connected = True
        print("Conexión establecida exitosamente")
    else: 
        print("Conexión fallida. No se estableció conexión ", rc)
        client.loop_stop()

def on_disconnect(client, userdata, flags, rc):
    if(rc == 0):
        print("Desconexión exitosa")
    else:
        print("Sistema desconectado mediante el código: ", rc)

def on_publish(client, userdata, mid):
    print("En medio de llamada on_publish", mid)

ser = serial.Serial("/dev/ttyACM0", 115200, timeout = 1)
print("Conectado al puerto serial /dev/ttyACM0")

# Utilizando MQTT
client = mqtt.Client("labo4_client")
client.connected = False
client.on_connect = on_connect
client.on_disconnect = on_disconnect
client.on_publish = on_publish

#Credenciales del servidor
broker ="iot.eie.ucr.ac.cr"
port = 1883
topic = "v1/devices/me/telemetry"
username = "labo4divicestm32"
token = "0ee29zgjqa9wm3n8mt6n" #Token de usuario
client.username_pw_set(token)
client.connect(broker, port)

# Estructura json
dict = dict()

#Rutina de dormir
while client.connected != True:
    client.loop()
    time.sleep(2)

#Rutina de conexion
while (1):
    try: 
        data = ser.readline().decode('utf-8')
        data = data.replace('\r', "").replace('\n', "")
        data = data.split(',')
        if (len(data) == 4):
            dict["Eje X"] = data[0]
            dict["Eje Y"] = data[1]
            dict["Eje Z"] = data[2]
            dict["Voltaje de Bateria"] = data[3]

            if(float( data[3]) < 7):
                dict["Bateria Baja"] = "Si"
            else:
                dict["Bateria Baja"] = "No"
        
        output = json.dumps(dict)

        #Impresion en consola
        print(output)
        client.publish(topic, output)
        time.sleep(1)
        
    except Exception as error:
        print("Desabilitada la transmision de datos")
