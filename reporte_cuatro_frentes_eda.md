# Reporte EDA Operación Cuatro Frentes
**Analista:** Armando Casanova Lemus | 22121351

## Misión 1 Semáforo Académico

* **Pregunta de negocio:** ¿Cuál es el nivel de riesgo de reprobar que tiene un alumno al cierre del parcial para intervenir a tiempo?
* **Tipo propuesto:** Clasificación multiclase, porque la variable objetivo es una etiqueta cualitativa con tres categorías discretas que son verde, amarillo y rojo, no estamos calculando un valor continuo sino asignando a cada estudiante a un grupo de riesgo.
* **Y y forma de Y:** Variable categórica ordinal llamada `riesgo` con tres valores posibles, donde el 40 por ciento es verde, el 35 por ciento es amarillo y el 25 por ciento es rojo, mostrando una distribución bastante pareja sin desbalances graves.
* **X candidatas (5 variables):**
  * `asistencia_pct`: porcentaje de asistencia a clases para ver la constancia del alumno.
  * `tareas_entregadas`: número de tareas entregadas a tiempo como indicador de cumplimiento continuo.
  * `promedio_parciales`: promedio obtenido en exámenes parciales para medir el desempeño académico actual.
  * `horas_plataforma`: tiempo de uso en la plataforma virtual para registrar la dedicación fuera del aula.
  * `reprobadas_previas`: historial de materias no acreditadas anteriormente para considerar el antecedente del alumno.
* **Hallazgos EDA:**
  * Alumnos con riesgo verde promedian 91 por ciento de asistencia y 8.4 en parciales con casi cero materias reprobadas previamente.
  * Conforme el riesgo sube a rojo la asistencia se desploma a 52 por ciento, el promedio cae a 5.0 y las materias reprobadas suben a 2.4 en promedio.
* **Leakage evitado:** No se debe incluir la calificación final del curso ni el estatus de acreditación al final del semestre, ya que son datos del futuro que solo existen cuando el curso ya terminó y volverían tramposo el modelo.
* **Métricas coherentes con mi tipo:** Macro F1 y matriz de confusión, porque necesitamos cuidar el balance entre las tres clases y verificar que los alumnos en rojo no se confundan con verdes.
* **Modelo propuesto y condición:** Bosque aleatorio clasificador, con la condición previa de que las variables numéricas no tengan datos vacíos y que se compruebe que el promedio de parciales no esté altamente repetido con las tareas.

## Misión 2 Alerta de Churn

* **Pregunta de negocio:** ¿El estudiante abandonará la materia a mitad de semestre o permanecerá en el curso?
* **Tipo propuesto:** Clasificación binaria, porque la variable de abandono solo toma dos estados posibles que son 0 para quien se queda y 1 para quien deserta, buscando predecir una condición de salida y no una cifra numérica.
* **Distribución de Y e implicaciones:** Con 500 alumnos y 14 por ciento de deserción hay exactamente 70 casos positivos de abandono frente a 430 de permanencia, si alguien presume un 86 por ciento de precisión simplemente está prediciendo que nadie abandona, por lo que esa métrica es totalmente engañosa.
* **Tratamiento de NA:** En la primera actividad muchos alumnos que abandonan tienen valor faltante porque nunca la entregaron, por eso borrar esas filas eliminaría justo a los desertores, lo ideal es crear una columna nueva llamada `entrego_actividad_1` con 0 o 1 y rellenar la nota faltante con un valor numérico neutral como cero.
* **Métricas y costo de error:** Recall y precisión sobre la clase 1, porque el costo de no detectar a un alumno que va a desertar es perderlo definitivamente de la escuela, mientras que una falsa alarma solo implica mandarle un mensaje de apoyo que no hace daño.
* **Modelo propuesto:** Regresión logística o bosque aleatorio con ajuste de peso a la clase minoritaria, vigilando que `dias_sin_login` y `avance_contenido_pct` estén bien limpias.

## Misión 3 Pronóstico de Puntaje

* **Pregunta de negocio:** ¿Qué calificación final numérica obtendrá el estudiante en una escala de 0 a 100?
* **Tipo propuesto:** Predicción numérica mediante regresión, porque la variable objetivo es un puntaje continuo en un rango de números y nos interesa estimar el valor exacto de la nota y no solo encasillarlo.
* **Qué se gana y se pierde si se convierte a aprobado o reprobado:** Se ganaría sencillez al transformar el problema en una clasificación fácil de interpretar, pero se perdería toda la precisión sobre qué tan bien o qué tan mal le fue al alumno, ya que no es lo mismo pasar con 70 apenas que con 98, ni quedarse en 68 que reprobar con 20.
* **Outliers y errores de captura:** Hay 3 registros con calificación mayor a 100 en los datos crudos, como la escala máxima permitida es 100 esos datos son errores de dedo al capturar, por lo que se deben corregir si el examen original lo permite o eliminarse del dataset si no hay forma de verificar el dato real.
* **Métricas (2):**
  * MAE (Error absoluto medio): para saber en promedio cuántos puntos de calificación se equivoca el modelo al estimar la nota.
  * RMSE (Raíz del error cuadrático medio): para castigar con más fuerza los errores grandes donde el modelo falle por muchos puntos de diferencia.
* **Modelo propuesto:** Regresión lineal si la relación entre los exámenes y la nota final es recta y continua, o un árbol de regresión si la calificación se comporta en bloques o escalones por criterios de redondeo escolar.

## Misión 4 Tiempo de Estudio

* **Pregunta de negocio:** ¿Cuántas horas adicionales de estudio necesita un alumno para lograr el dominio de un tema?
* **Tipo propuesto:** Predicción numérica mediante regresión, porque la variable a estimar son horas cuantitativas continuas que pueden tomar valores con decimales como 2.0, 18.0 o 35.0 horas.
* **Hipótesis dificultad contra horas:** A mayor dificultad del tema se incrementa sustancialmente la cantidad de horas adicionales requeridas, pasando de un promedio de 3.2 horas en temas de dificultad baja hasta 16.5 horas en temas de dificultad alta.
* **Cola larga de horas:** La cola de alumnos que requieren más de 40 horas representa apenas el 3 por ciento pero no se debe borrar a la ligera, son casos reales de alumnos con gran rezago que la escuela necesita atender con urgencia, así que conviene conservarlos y usar modelos robustos a valores extremos o transformar la variable con logaritmo.
* **Alternativa de binarizar Y:** Convertir las horas a un umbral como tutoría intensiva sí o no facilitaría armar grupos de apoyo para los que pasen de 15 horas, pero se perdería el detalle fino de cuántas horas reales de asesor debe programar la institución para cada estudiante.
* **Métricas y modelo con dos chequeos EDA:**
  * Métricas: MAE y mediana del error absoluto para que los valores extremos de muchas horas no distorsionen la evaluación.
  * Modelo: Árbol de regresión potenciado como LightGBM o regresión robusta.
  * Dos chequeos EDA obligatorios: comprobar la correlación entre el examen diagnóstico y los ejercicios correctos para descartar redundancia entre variables, y verificar que no existan horas negativas o datos imposibles en la variable objetivo.

## Síntesis

| Misión | Nombre en clave | Tipo propuesto | Justificación breve |
| :--- | :--- | :--- | :--- |
| M1 | Semáforo Académico | Clasificación multiclase | La meta es asignar un nivel de riesgo discreto (verde, amarillo, rojo) |
| M2 | Alerta de Churn | Clasificación binaria | El resultado es saber si el alumno deserta o se queda (1 o 0) |
| M3 | Pronóstico de Puntaje Final | Predicción numérica (Regresión) | El objetivo es estimar una calificación numérica en escala de 0 a 100 |
| M4 | Estimación de Tiempo de Estudio | Predicción numérica (Regresión) | Se busca calcular una cantidad continua de horas de estudio necesarias |

Para decidir entre clase o número en cualquier misión me fijé en la naturaleza de la respuesta deseada, si la pregunta pide categorizar o elegir una etiqueta se trata de una clase, mientras que si pide calcular cuánto de una cantidad medible se trata de un número.
El tipo de problema se deduce de la pregunta y de Y porque la pregunta define la necesidad de la escuela y la variable objetivo marca matemáticamente si buscamos separar grupos o estimar una cantidad continua.
