# Reporte EDA Operación Dino Crash
**Analista:** Armando Casanova Lemus | 22121351

## 1. Problema y dataset (Misión 1)

### P1 Muerte en el siguiente frame
* **Variable objetivo (Y):** `died_next_frame`, es binaria con valores 0 o 1, indica si el dino choca en el siguiente cuadro.
* **Variables de entrada (X):**
  * `dist_obstacle`: distancia en pixeles al obstáculo más cercano para saber qué tan cerca está el peligro.
  * `obstacle_type`: tipo de obstáculo para conocer el tamaño de lo que viene.
  * `obstacle_y`: altura del obstáculo, sirve mucho para las aves que vuelan a diferentes niveles.
  * `dino_y`: altura del dinosaurio respecto al suelo para ver si va en el aire o pisando.
  * `speed`: velocidad actual del juego, entre más rápido va menos tiempo hay para reaccionar.
* **Granularidad:** Cuadro por cuadro, cada 16 milisegundos, porque la colisión ocurre en un instante exacto y si resumimos por segundo nos perdemos el choque.
* **Tamaño mínimo razonable:** Unas 150 a 200 partidas completas, porque en cada partida el dino solo muere una vez y necesitamos ver bastantes muertes con diferentes velocidades y obstáculos para que el modelo aprenda bien.
* **Riesgo si el dataset está mal definido:** Poner la variable de muerte en el mismo cuadro donde ya chocó, lo que provocaría que el modelo solo aprenda a avisar cuando ya perdiste en lugar de prevenir el choque.

### P2 Cuántos puntos alcanzará esta partida al morir
* **Variable objetivo (Y):** `final_score`, es numérica continua o entera, representa el puntaje final acumulado al terminar la partida.
* **Variables de entrada (X):**
  * `promedio_puntos_previos`: promedio de puntos que saca ese jugador para medir su habilidad.
  * `lag_pantalla`: retraso en milisegundos de los primeros saltos para ver si el juego responde rápido.
  * `hora_del_dia`: momento en que juega, ya que influye en el cansancio o los reflejos de la persona.
  * `primeros_saltos_buenos`: precisión del jugador en los primeros 3 obstáculos.
  * `fps_juego`: estabilidad de los cuadros por segundo del equipo al iniciar.
* **Granularidad:** Una fila por partida completa, con datos resumidos de la sesión.
* **Tamaño mínimo razonable:** Al menos 1000 partidas completas, ya que cada fila es un juego entero y con pocas partidas el modelo no va a encontrar patrones confiables.
* **Riesgo si el dataset está mal definido:** Meter el tiempo total jugado como variable de entrada, porque entre más tiempo dura la partida más puntos se hacen y el modelo solo copiaría ese dato sin predecir nada útil.

### P3 Qué tipo de obstáculo viene próximo
* **Variable objetivo (Y):** `next_obstacle_type`, es categórica con clases como cactus chico, cactus grande o pájaro.
* **Variables de entrada (X):**
  * `score_actual`: puntuación que lleva la partida, porque los pájaros solo salen después de ciertos puntos.
  * `speed`: velocidad del juego en ese momento.
  * `ultimo_obstaculo`: qué obstáculo acaba de esquivar.
  * `distancia_recorrida_desde_ultimo`: cuánta distancia libre ha pasado desde el obstáculo anterior.
  * `cactus_seguidos`: cuántos cactus han salido en racha.
* **Granularidad:** Un registro por cada evento donde aparece un obstáculo nuevo en pantalla.
* **Tamaño mínimo razonable:** Unos 3000 o 4000 obstáculos generados en varias partidas para ver suficientes combinaciones de cada tipo de obstáculo.
* **Riesgo si el dataset está mal definido:** Guardar una fila por cada cuadro mientras el obstáculo sigue en pantalla, lo que repetiría el mismo obstáculo muchas veces y confundiría al modelo haciéndole creer que hay miles de obstáculos cuando solo fue uno.

## 2. Diccionario y muestra (Misión 2)

* **Patrón en died=1:** En los cuadros 80 y 81 el dinosaurio venía saltando con `jump=1` pasando por arriba del cactus, pero en el cuadro 82 cayó al suelo con `jump=0` cuando el cactus todavía estaba a solo 12 pixeles, o sea que saltó antes de tiempo o bajó antes de librarlo por completo y por eso chocó.
* **score como predictor:** No sirve para predecir si mueres en el siguiente cuadro, porque el puntaje solo cuenta cuánto tiempo llevas jugando y no si tienes un obstáculo enfrente, ya que puedes morir teniendo 16 puntos o durar hasta 500 si brincas a tiempo.
* **Falta alguna columna crítica:** Sí, falta saber qué tan arriba está el dinosaurio en el aire con una columna de altura, también falta saber si se agachó para esquivar pájaros, y la altura del propio obstáculo.
* **died sirve tal como está:** No sirve directamente para predecir, porque solo marca el momento en el que el dinosaurio ya está muerto, así que tendríamos que recorrerla un cuadro hacia atrás para que marque 1 en el cuadro previo al choque.

## 3. Checklist EDA (Misión 3)

* **Pregunta 3 (Clase balanceada):** La clase está súper desbalanceada, de miles de cuadros jugados solo el último cuadro de cada partida tiene valor de muerte y todos los demás son normales, por eso no podemos usar exactitud típica porque decir siempre que no va a morir daría casi 100 por ciento de acierto sin servir de nada.
* **Pregunta 5 (Variables correlacionadas):** El tiempo, el cuadro y el puntaje aumentan exactamente al mismo ritmo, son casi lo mismo repetido y tenerlas juntas estorba en modelos simples, así que conviene quitar dos de ellas y quedarnos solo con una.
* **Pregunta 9 (Estacionariedad):** El juego no se comporta igual al inicio que al final porque la velocidad va subiendo, así que la distancia para esquivar un cactus cambia mucho conforme avanza la partida y un modelo simple puede fallar si no toma en cuenta esa velocidad.
* **Problema con i.i.d. al mezclar cuadros de la misma partida:** Si revolvemos cuadros de la misma partida en entrenamiento y prueba, el modelo va a memorizar esa partida en específico porque los cuadros pegados son casi idénticos, y al evaluar va a parecer que el modelo es perfecto pero cuando juegue una partida nueva va a fallar, por eso se debe separar por partidas completas y no por cuadros sueltos.
* **Ejemplo de fuga de datos:** Si creamos una variable que divida el puntaje actual entre el puntaje máximo que se alcanzó en esa partida, cuando ese valor se acerque a 1 el modelo sabrá que la partida ya va a terminar, pero ese dato no existe mientras juegas en tiempo real.

## 4. Interpretación de resúmenes (Misión 4)

* **Desbalance en P1 cuantificado:** En 12000 cuadros solo hay 50 cuadros con muerte, lo que representa apenas el 0.41 por ciento de los datos, mientras que el 99.59 por ciento restante son cuadros normales.
* **Implicación en métricas:** La exactitud común no nos sirve porque si el modelo dice siempre que el dino sigue vivo acertaría el 99.59 por ciento de las veces, entonces debemos medir qué tantas muertes reales detecta a tiempo y qué tantas falsas alarmas genera usando métricas como recall y precisión.
* **dist_obstacle como predictor:** Es muy útil porque las estadísticas dicen que la distancia promedio es de 95 pixeles, pero en la nota se aclara que las muertes casi siempre pasan cuando la distancia baja de 20 pixeles, lo que muestra que debajo de 20 pixeles el peligro es real.
* **Distribución de score:** Tiene una cola larga hacia la derecha porque la mayoría de partidas duran poco y pocas llegan muy lejos, por eso para predecir puntos no conviene meter el dato crudo en una regresión directa sin antes transformarlo o usar modelos basados en árboles que aguanten datos chuecos.

## 5. Elección de modelo (Misiones 5 y 6)

| Escenario | Fila de la guía aplicable | Modelo propuesto | 2 condiciones del dataset requeridas |
| :--- | :--- | :--- | :--- |
| P1 | Variable binaria muy desbalanceada con datos tabulares | Bosque aleatorio o regresión logística con peso a la clase minoritaria | Que se separe por partidas completas en las pruebas y que incluya la altura del dinosaurio |
| P2 | Variable numérica con cola larga y datos tabulares | Árbol de regresión potenciado | Que cada fila sea una partida distinta y que no tenga variables que delaten el final |
| P3 | Variable categórica con varias clases | Bosque aleatorio clasificador | Que los datos sean por evento de obstáculo y que haya suficientes ejemplos de pájaros |

### Contraejemplos

* **Árbol profundo desaconsejado:** Un árbol de decisión con mucha profundidad parecería bueno para memorizar cada situación, pero con solo 50 muertes en los datos terminaría aprendiéndose de memoria cada muerte individual, provocando sobreajuste y fallando en partidas nuevas con velocidades diferentes.
* **Cuándo usar una red neuronal:** Tendría sentido si en lugar de tablas con distancias le pasáramos directamente capturas de pantalla del juego en video, teniendo cientos de miles de imágenes para que aprenda a ver los obstáculos por su cuenta.
* **Reglas fijas frente a modelos aprendidos:** Una regla como si la distancia es menor a 20 y no está saltando entonces muere es súper rápida, fácil de programar y no gasta memoria, pero el gran problema es que cuando el juego acelera a velocidad alta esa distancia de 20 ya queda corta y el dinosaurio choca antes, mientras que un modelo con datos puede adaptarse a cómo cambia el peligro según la velocidad.

## Síntesis
Pediría primero un dataset por cuadros con distancias, alturas, velocidad y tipo de obstáculo separado por partidas completas, y solo después de revisar el desbalance y la correlación en el análisis exploratorio propondría un bosque aleatorio ligero cuidando el peso de las muertes y evaluando con precisión y recall.
