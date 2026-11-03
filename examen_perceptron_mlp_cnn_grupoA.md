# Examen Teórico — Perceptrón, MLP y CNN (Grupo A)

## Armando Casanova Lemus 
## 22121351
## 03 de Noviembre de 2026

## Pregunta 1 — Idea del perceptrón

1. **Explica qué recibe un perceptrón, qué hace con los pesos y el bias, y qué produce.**
Recibe varios datos numéricos de entrada, luego multiplica cada uno por su peso y le suma el bias o sesgo para ajustar que tan fácil se activa la neurona y así produce una sola respuesta de salida que suele ser 0 o uno

2. **¿Qué quiere decir que dos clases sean linealmente separables?**
significa que podemos trazar una sola línea recta o un plano liso que divida y separe perfectamente a los dos grupos de datos sin revolverlos

3. **Señala una limitación fuerte del perceptrón de una sola capa.**
su limitación es que no es capaz de resolver problemas donde los datos no se puedan separar con una línea recta


## Pregunta 2 — Por qué aparece el MLP

1. **¿En qué sentido un MLP es “más de una capa de neuronas”?**
Es más de una capa porque acomoda a las neuronas en varios niveles seguidos y los resultados de un grupo se convierten en la entrada del siguiente grupo y se hace una cadena

2. **¿Para qué sirve la capa oculta?**
sirve para encontrar y combinar rasgos intermedios que son más elaborados y con eso se aprendenden patrones y curvas difíciles que una sola capa no puede ver

3. **Si quitas todas las activaciones no lineales, ¿qué tipo de comportamiento te queda y por qué importa?**
queda un comportamiento lineal como el del perceptrón simple, y esto importa porque no serviría tener tantas capas si la red solo puede trazar líneas rectas


## Pregunta 3 — XOR como lección histórica

1. **¿Qué enseña el ejemplo XOR sobre el perceptrón simple?**
nos enseña que los problemas reales sencillos no siempre se pueden dividir con una línea recta y eso significa que el perceptrón básico tiene alcances muy reducidos

2. **¿Qué cambia al pasar a una red con capas ocultas y no linealidad?**
que ahora el modelo divide diferente porque ahora puede doblar, torcer o combinar el espacio y puede clasificar y separar combinaciones más complejas

3. **¿Eso significa que el perceptrón nunca sirve en problemas reales? Argumenta.**
No significa eso porque en la vida real hay muchos problemas simples donde los grupos o la información están bien separada y además el perceptrón es muy rápido y gasta pocos recursos, entonces con poquitos datos pero ordenados se pueden estimar resultados confiables


## Pregunta 4 — Cómo “aprende” la red

1. **Describe con palabras el ciclo: predicción → medir error → ajustar pesos.**
Primero la red recibe los datos e intenta adivinar la respuesta, después compara el intento con el valor real y así ver por cuánto se equivocó y al final modifica los pesos para fallar menos en el siguiente intento

2. **¿Qué controla el learning rate (tasa de aprendizaje) a nivel conceptual?**
Controla el tamaño del salto o el paso que tiene el modelo al corregir sus pesos en cada intento, y así define si será como a poco y más tiempo o con pasos más grandes

3. **Diferencia *subajuste* y *sobreajuste* con un ejemplo escolar breve.**
El subajuste es como un alumno que no estudio casi nada y entonces reprueba el examen porque no entendió, y el sobreajuste es un alumno que se aprendio todos los apuntes y clase de memoria y saca bien las tareas pero si en el examen cambia algo un poco como los numeros, reprueba porque memorizo tal cual


## Pregunta 5 — Salidas: sigmoide y softmax

1. **¿Cuándo usarías sigmoide y cuándo softmax?**
uso sigmoide cuando la respuesta es de sí o no entre dos opciones, y el softmax cuando debes elegir una sola opción entre tres o más categorías diferentes

2. **¿Qué significa el vector que sale de un softmax en un problema de varias clases?**
es una lista de probabilidades que representan que tan seguro esta el modelo para cada clase, y donde las opciones suman 1 en total y así se ve la que tiene el valor mas alto


3. **Pon un ejemplo del curso (juego, riesgo, imágenes, etc.) y di qué salida encajaría.**
en el juego del dinosaurio donde debe decidir  saltar, agacharse o correr encajaría usar softmax porque tiene que elegir una acción entre tres opciones posibles


## Pregunta 6 — Motivación de la CNN

1. **¿Qué inconveniente conceptual tiene aplastar una imagen y meterla a un MLP denso?**
el incoveniete es que se pierde la forma original del dibujo y la cercanía entre los píxeles vecinos y también genera demasiados conexiones y hacen el cálculo muy pesado

2. **¿Qué aporta la idea de *filtro local* y *pesos compartidos*?**
esas ideas hacen que el modelo reutilice la misma pequeña plantilla de detección por toda la imagen y ahorra memoria y reconoce el mismo rasgo sin importar en qué parte o rincon aparezca

3. **Menciona *dos* dominios (además de fotos cotidianas) donde una CNN tiene sentido.**
en el análisis de radiografías médicas para buscar enfermedades y en la revisión de sonidos que se convierten en graficas para reconocer una voz


## Pregunta 7 — Piezas de una CNN

1. **Convolución:** este es para que se pase una plantilla sobre la foto y se resaltan detalles pequeños como los bordes, las esquinas o la textura

2. **Pooling:** este sirve para hacer más chica la imagen y se queda con los razgos mas importantes o fuertes y hace el modelo más rapido y ligero

3. **Flatten + Dense al final:** Sirve para poner los rasgos encontrados en una sola fila y conectarlos a neuronas para que decidan que hay en la imagen

4. **Dropout durante el entrenamiento:** 
Sirve para apagar neuronas random en el entrenamientoy asi se obligue a que la red no dependa de las mismas neuronas y aprenda sin memorizar de memoria


## Pregunta 8 — Capas bajas vs capas altas

1. **¿Qué suelen captar las primeras capas de una CNN frente a las más profundas?**
Las primeras captan líneas simples y cambios de brillo y las capas profundas juntan esas líneas para captar siluetas, caras y objetos

2. **Usa una analogía (lupas, detectores, “de simple a complejo”).**
la analogia de la lupa podria ser con un rompecabezas donde al prinicipio con las primeras lupas detectas cosas simples como manchas o bordes, y ya con lupas mas grandes se pueden unir piezas para ver de que es el rompecabezas

3. **¿Por qué “poner más capas” no garantiza mejor modelo?**
Porque hacer la red demasiado grande puede provocar que memorice los datos en vez de aprender de verdad y tambien de que se vuelve más lenta y difícil de ajustar


## Pregunta 9 — Análisis: elige arquitectura

1. **Tabla de alumnos: promedio, faltas, horas de estudio → ¿aprueba?**
elijo MLP porque es buena para relacionar datos en columnas de numeros y predecir una categoría

2. **Clasificar el color de un semáforo en una fotografía.**
Elegiría CNN porque es de una imagen donde importa ubicar la forma del semáforo y los colores en el espacio

3. **Clases en el plano que *no* se separan con una recta.**
MLP porque tiene capas ocultas y puede trazar fronteras curvas para separar datos que una línea recta no puede dividir

4. **¿Usarías CNN para autocompletar código o una secuencia larga de texto? ¿Sí/no y qué alternativa del curso mencionarías?**
No usaría una CNN porque las imágenes tienen estructura espacial mientras que el texto largo depende del orden de las palabras a lo largo del tiempo, así que mencionaría como alternativa los modelos secuenciales o redes para texto vistas en el curso


## Pregunta 10 — Análisis: mirada de proyecto

1. **Train accuracy altísima y validation baja: ¿qué sospechas? ¿Qué dos preguntas le harías al equipo en la defensa?**
   sospecho que el modelo tiene sobreajuste porque se aprendió de memoria los datos de entrenamiento y falla con casos nuevo y entonces les preguntaría cuántos ejemplos distintos usaron para entrenar y si aplicaron algo para que no memorice

2. **¿Por qué más neuronas o más capas no sustituyen un buen planteamiento del problema y buenos datos?**
   Porque si los datos estan mal etiquetados o no tienen relación con lo que queremos resolver la red solo va a aprender de datos basura sin importar qué tan grande o potente sea

3. **Escribe *tres* preguntas orales (tuyas) para verificar que distinguen perceptrón, MLP y CNN.**
* ¿Por qué una sola neurona no puede aprender el comportamiento de la compuerta XOR?
* ¿Qué ventaja tiene colocar una capa oculta entre la entrada y la salida de un modelo?
* ¿Por qué una capa convolucional necesita muchísimos menos parámetros que una capa densa para revisar una fotografía?

