# Monitor de Temperatura y Humedad en Tiempo Real

Este es un programa que muestra la temperatura y humedad en tiempo real utilizando un sensor DHT22 conectado a un dispositivo ESP32. El programa recopila los datos del sensor y los muestra en una página HTML de manera dinámica, actualizando los valores cada segundo.

## Funcionamiento

El programa consiste en dos partes principales: el código del dispositivo ESP32 y el código HTML para la visualización en el navegador.

El código del dispositivo ESP32 se encarga de leer los valores de temperatura y humedad del sensor DHT22 y proporcionarlos a través de una API. El ESP32 actúa como un servidor web que responde a las solicitudes en la ruta `/value` con los datos en formato JSON.

El código HTML es la interfaz de usuario que muestra los valores de temperatura y humedad en tiempo real. Utiliza jQuery para hacer solicitudes periódicas a la API del ESP32 y actualizar los valores en la página sin necesidad de recargarla.

## Requisitos

Para utilizar este programa, necesitarás:

- Un dispositivo ESP32 con el firmware adecuado y el código del sensor DHT22 configurado.
- Un sensor DHT22 conectado al ESP32 para medir la temperatura y humedad.
- Un entorno de desarrollo o IDE para cargar el código en el ESP32.
- Un navegador web compatible con JavaScript para visualizar la página HTML.

## Configuración

1. Carga el código del dispositivo ESP32 en tu dispositivo y asegúrate de que esté conectado correctamente al sensor DHT22.
2. Asegúrate de que tu ESP32 esté configurado para actuar como un servidor web y responder a las solicitudes en la ruta `/value`.
3. Abre el archivo HTML en un navegador web. Asegúrate de que el ESP32 esté conectado a la red y el servidor web esté en funcionamiento.
4. La página HTML mostrará los valores de temperatura y humedad en tiempo real.

## Personalización

Si deseas personalizar este programa, aquí hay algunas áreas que podrías modificar:

- Estilos CSS: Puedes ajustar los estilos en el archivo HTML para cambiar la apariencia de la página.
- Intervalo de actualización: Puedes modificar el intervalo de actualización en la función `setInterval()` del archivo HTML para ajustar la frecuencia de actualización de los valores.

## Contribuciones

Si deseas contribuir a este programa, siéntete libre de hacerlo. Puedes abrir un pull request con tus mejoras o sugerencias.

Esperamos que este programa te sea útil para monitorear la temperatura y humedad en tiempo real. Si tienes alguna pregunta o problema, no dudes en comunicarte con nosotros.

¡Disfruta y mantente informado sobre el clima al interior de tu vivienda, o en algún espacio donde lo necesites, con este monitor de temperatura y humedad en tiempo real!
