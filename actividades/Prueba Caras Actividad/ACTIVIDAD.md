# Actividad Reconocimiento Facial

## Captura de fotos
Para tomar las fotos se uso la camara web de la computadora mediante OpenCV junto con el clasificador haarcascade_frontalface_alt2.xml que detecta cuando hay una cara al frente entonces cada rostro detectado se pasa a escala de grises y se recorta a un tamano de 100 por 100 pixeles para guardar de manera automatica 50 fotos dentro de la carpeta pruebacaras con el nombre de armando

## Entrenamiento
Para entrenar se leyeron las 1000 fotos guardadas de la carpeta pruebacaras y se empleo el metodo Eigenfaces de OpenCV que analiza las imagenes y crea el archivo llamado armandoEigenface.xml que contiene los datos entrenados para identificar a la persona

## Reconocimiento en vivo
Para reconocer las caras se abre otra vez la camara web y se usa el detector haarcascade para ubicar la cara en tiempo real entonces esa imagen se recorta a 100 por 100 pixeles y se compara usando el archivo armandoEigenface.xml que calcula un valor de distancia donde si el valor es menor a 2800 se reconoce como armando mostrando un cuadro verde y si supera ese numero o no coincide se muestra en color rojo como desconocido

## Modificaciones realizadas
En el script capturar_fotos.py se cambio el texto de tu_nombre por el de las 5 personas para que las fotos se guardaran en la carpeta correcta

Tambien en entrenar.py se modifico la ruta de las fotos que venia fija con una direccion de Linux /home/likcos/pruebacaras y se dejo solo como pruebacaras para que pudiera encontrar la carpeta del proyecto en Windows

Por ultimo en reconocer.py se cambio la carga del modelo que venia con el nombre laloEigenface.xml para que leyera armandoEigenface.xml que fue el archivo generado durante el entrenamiento
