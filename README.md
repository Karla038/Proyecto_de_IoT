# Proyecto_de_IoT
Proyecto Final de la asignatura de IoT 

# Brumm-Brumm Smart
Este es el repositorio oficial del proyecto Brumm-Brumm Smart, un carrito sembrador autónomo diseñado para ayudar en la siembra de cultivos.

# Características
El Brumm-Brumm Smart está equipado con una variedad de sensores y actuadores, lo que le permite operar de manera autónoma y sembrar semillas en cada cierta distancia. Aquí están algunas de sus principales características:

# Placa Principal
La Placa Principal usada fue una ESP32 que es una mejor opción sobre la placa Arduino UNO gracias a su Documentación y la inclusion de Circuitos para la conexión a Internet y Bluetooth, esta Placa se encuentra en el  Mercado por un Precio Bastante Accesible en Promedio de $150 a $200 (Aprox $10 USD).
![image](https://user-images.githubusercontent.com/106613848/234410848-ce0a1b6c-6763-4bde-909a-45041ac3bfad.png)


# Sensores

| Nombre        | Modelo        | Precio   | Imagen        |
| ------------- | ------------- | ---------| ------------- |
| Lluvia        | FC-37         | $60      | ![image](https://user-images.githubusercontent.com/124712008/234090635-235aa2bb-ec7a-45bd-98c6-b4c4dc360c2f.png)  |
| Gas           | Mq-2          | $70      | ![image](https://user-images.githubusercontent.com/124712008/234089856-e0737a07-cde6-4aa3-b9c9-9584419a2d2c.png)  |
| Choque        | Ky-002        | $40      | ![image](https://user-images.githubusercontent.com/124712008/234090104-febc3f7b-9815-45d3-b476-3a441e73a900.png)  |
| Ultrasonico   | HC-SR04       | $100     | ![image](https://user-images.githubusercontent.com/124712008/234090402-439eacd5-c4a5-4bd8-8ce8-814e63eaf8d1.png)  |
| Temperatura y Humedad| DHT11  | $50      | ![image](https://user-images.githubusercontent.com/124712008/234089647-34c15013-2f75-4860-b161-bb33166ebcab.png)  |

# Circuitos usados
| Nombre        | Modelo        | Precio   | Imagen        |
| ------------- | ------------- | ---------| ------------- |
| Circuito Integrado   | L293D  | $30      | ![image](https://user-images.githubusercontent.com/106613848/234408836-36ea4519-25de-4ae5-8aff-e58fe3df4e53.png)  |
     

# Actuadores
| Nombre                        | Cantidad      | Modelo        | Precio   | Imagen        |
| -------------                 | ------------- | ------------- | ---------| ------------- |
| Motor de corriente continua   | 4             | 12v           | $190     | ![image](https://user-images.githubusercontent.com/124712008/234345476-6458980c-76fe-4462-8c99-fabf11ec611b.png)|
| ServoMotor                    | 1             | SG90 RC 9g    | $70      | ![image](https://user-images.githubusercontent.com/124712008/234345116-5ed6ec73-3c9c-4d69-b8c3-6bbbbf75aa19.png)|


# Funcionamiento
El Brumm-Brumm Smart está diseñado para operar de manera autónoma en cualquier terreno. Después de cargar sus baterías a través del panel solar, el carrito se mueve y utiliza sus sensores para detectar el ambiente a su alrededor. Cuando llega a la distancia deseada, el carrito libera una semilla en el suelo.

Los sensores del Brumm-Brumm Smart le permiten adaptarse al ambiente en tiempo real. Por ejemplo, si detecta lluvia, puede detenerse temporalmente hasta que la lluvia pase. También puede detectar gas y alertar a los agricultores para que tomen medidas de seguridad. Además, el carrito es capaz de detectar choques y obstáculos y evitarlos para evitar daños.

Para almacenar los datos de los sensores se optpo por usar mariaDB, como broker para la conexion remota se uso mosquitto MQTT y Node-RED para la craacion del dashboard de control. Para mayor organizacion se instalaron estas tecnologias en una Raspberrry PI virtualizada
para asi solo tener que conectarse a un splo punto.

Más detalladamente el Brum Brum Smart se comunica a la Raspberry mediante un microcontrolador ESP32, el cual se conecta mediante los protocoles del código generado en Arduino IDE para recibir y enviar mensajes al broker MQTT, despues con Node-RED se genera un dashboard en donde solo se necesita crear los nodos necesarios para que los datos que mandan los sensores sean tambien virtualizados en el dashboard.

MariaDB:

![image](https://user-images.githubusercontent.com/114528947/234418158-57c43e01-1cdb-4da1-b90d-1ab2a791911e.png)

Node-RED: 

![image](https://user-images.githubusercontent.com/114528947/234418503-930fbdaf-85e3-47f6-a38f-b3b6d4353767.png)

![image](https://user-images.githubusercontent.com/114528947/234418543-b0c4ab81-0eda-4b79-a646-c49902e4f84e.png)

Dashboard Node-RED: 

![image](https://user-images.githubusercontent.com/114528947/234418675-844706b1-428e-4ba3-99ce-c14bada2b248.png)


# Precio al mercado
El precio oficial del Brumm-Brumm Smart es de $500 USD. Este precio incluye todos los componentes necesarios para construir el carrito sembrador autónomo.

# Esquema en Fritzing
![image](https://user-images.githubusercontent.com/124712008/234340252-ca42547b-439e-4b11-b079-36bd9e6ded66.png)

# Prototipo
El prototipo fue tomado de un carro tipo arduino con Motores Activos en las 4 llantas hacendo que sea muy dificil que este quede atascado en su Area de Trabajo
El programa utilizado para Crear El proyecto fu Arduino IDE que utilizo una Dependecia que le premitia cargar pogramas a esta Placa ESP32 
Las Librerias usadas para facilitar el uso de los sensores son las Siguientes

| Nombre        | Libreria      | Link de Descarga |
| ------------- | ------------- | ---------------- |
| Sensor de Temperatura y Humedad   | DHT11  | https://www.google.com/url?sa=t&rct=j&q=&esrc=s&source=web&cd=&cad=rja&uact=8&ved=2ahUKEwiDx8_Ag8b-AhWcOEQIHQbuCZ8QFnoECAwQAQ&url=https%3A%2F%2Fwww.arduinolibraries.info%2Flibraries%2Fdht-sensor-library&usg=AOvVaw0mGD6kVAry9l71QgBzbBYO      |
| Sensor Ultrasonico  | HC-SR04  | https://www.google.com/url?sa=t&rct=j&q=&esrc=s&source=web&cd=&cad=rja&uact=8&ved=2ahUKEwjJufimhMb-AhXEM0QIHYJUBo8QFnoECA4QAQ&url=https%3A%2F%2Fwww.arduinolibraries.info%2Flibraries%2Fhcsr04&usg=AOvVaw2rrw6zn5pSEsVAHq6SuUEJ |
| Lluvia        | FC-37         | https://www.google.com/url?sa=t&rct=j&q=&esrc=s&source=web&cd=&cad=rja&uact=8&ved=2ahUKEwiM2bDchMb-AhWBIEQIHWoiB44QFnoECCEQAQ&url=https%3A%2F%2Fwww.arduinolibraries.info%2Flibraries%2Frain&usg=AOvVaw25Ey1R1szUSnWUzdTaHVHr |
| Gas           | Mq-2          | https://www.google.com/url?sa=t&rct=j&q=&esrc=s&source=web&cd=&cad=rja&uact=8&ved=2ahUKEwjTiYmYhcb-AhWYDkQIHXfjBgUQFnoECAwQAQ&url=https%3A%2F%2Fwww.arduinolibraries.info%2Flibraries%2Fmq-unifiedsensor&usg=AOvVaw0KkdoUsfDnsoplBolvtcTP  |


![Imagen de WhatsApp 2023-04-24 a las 12 33 56](https://user-images.githubusercontent.com/124712008/234086150-a30f9e61-faf1-43e2-94f5-182b63313c4a.jpg)
![Imagen de WhatsApp 2023-04-24 a las 12 33 56](https://user-images.githubusercontent.com/124712008/234086211-1514cb46-72cd-46e1-b8d6-87f7a83a05f2.jpg)

# Link del video
https://drive.google.com/file/d/1ntzOzh_sRI7MPzfZtahKKE6SzCEpW7rx/view?usp=drivesdk

# Integrantes (Estudiantes de la Universidad Técnologica del Norte de Guanajuato)
### **Fernando Arvizu Sotelo** 
### **Karla Moya Díaz**
### **Juan Antonio Dominguez Rosales** 
### **Jose Carlos Duarte Vázquez** 



