# Parte I. Conceptos y definiciones

## Pregunta 1

**¿Qué es un árbol de decisión y cuál es su objetivo principal dentro de un problema de clasificación?**

Un árbol de decisión es una forma de tomar decisiones paso a paso, parecida a un diagrama de flujo donde se van haciendo preguntas sucesivas sobre las características de los datos, teniendo como objetivo separar los ejemplos en grupos cada vez más claros para asignarle a cada uno la categoría correcta

---

## Pregunta 2

**Explique los siguientes elementos de un árbol de decisión:**

* **Nodo raíz:** Es el punto de partida de todo el árbol, donde se formula la primera pregunta sobre la característica más relevante para comenzar a dividir la información
* **Nodo interno:** Son las preguntas intermedias del camino, en las cuales se evalúan condiciones adicionales para seguir separando los datos en grupos más pequeños
* **Rama:** Es el conector o flecha que une una pregunta con la siguiente, representando las distintas respuestas o caminos posibles que se pueden tomar
* **Hoja:** Es el final del trayecto, donde ya no se hacen más preguntas y simplemente se entrega el resultado o la clase asignada

---

## Pregunta 3

**¿Qué es una red neuronal multicapa y qué función cumplen las siguientes capas?**

Una red neuronal multicapa es un sistema inspirado en el cerebro humano compuesto por varios niveles de neuronas conectadas entre sí, el cual procesa información de forma encadenada para resolver problemas complejos y encontrar patrones difíciles, donde sus capas cumplen las siguientes funciones:

* **Capa de entrada:** Es la puerta por donde ingresan los datos iniciales, y se encarga únicamente de recibirlos y pasarlos al resto de la red sin alterarlos
* **Capa oculta:** Son los niveles intermedios que hacen el trabajo pesado de análisis, combinando las señales recibidas para detectar relaciones ocultas y patrones no evidentes a simple vista
* **Capa de salida:** Es la que entrega la respuesta final del modelo, reuniendo todo lo procesado para dar una predicción, una categoría o una probabilidad

---

## Pregunta 4

**¿Qué representan los pesos y los sesgos dentro de una red neuronal? Explique también por qué sus valores cambian durante el entrenamiento.**

Los pesos representan qué tanta importancia o influencia tiene cada dato de entrada sobre una neurona, mientras que el sesgo es un valor de ajuste que ayuda a mover el punto de partida de la neurona para que sea más fácil o difícil que se active, ambos valores cambian durante el entrenamiento porque el modelo va comparando lo que predijo con la respuesta real y midiendo en qué falló y recalculando los números para tener menos errores con cada intento

---

## Pregunta 5

**¿Cuál es la principal diferencia entre la forma en que aprende un árbol de decisión y la forma en que aprende una red neuronal multicapa? Explique qué elementos aprende cada modelo.**

La diferencia está en la forma en que trabajan los datos, ya que el árbol de decisión aprende creando divisiones lógicas y directas, mientras que la red neuronal aprende mediante ajustes numéricos mediante el cálculo de sus errores. El árbol obtiene un conjunto de reglas y preguntas con valores límite sobre las variables, y la red neuronal aprende valores numéricos que corresponden a los pesos y sesgos que conectan a todas sus neuronas

---

# Parte II. Análisis y aplicación

## Pregunta 6

**Una institución bancaria desea desarrollar un sistema que detecte posibles compras fraudulentas.**

El sistema dispone de información como: monto de la compra, hora de la operación, ciudad donde se realizó, tipo de establecimiento, número de compras realizadas durante el día e historial de compras del cliente

**Ventajas y desventajas de cada modelo:**
* **Árbol de decisión:** Es muy transparente y fácil de interpretar, lo que permite saber con exactitud qué regla bloqueó una compra, pero su desventaja es que le cuesta trabajo detectar patrones sutiles o combinaciones raras entre muchas variables a la vez
* **Red neuronal multicapa:** Es excelente para descubrir relaciones complejas y hábitos de consumo ocultos entre los horarios y los montos, aunque su gran desventaja es que actúa como una caja negra, lo que complica explicarle al cliente o a las autoridades la razón exacta por la que se rechazó su tarjeta

**¿Cuál utilizaría y por qué?**
Utilizaría la red neuronal multicapa porque usualmente los ladrones cambian  sus métodos, entonces conviene priorizar la capacidad de encontrar patrones diferentes y reducir las estafas, pero teniendo tambien algun registo que puedan interpretar los humanos

---

## Pregunta 7

**Una escuela quiere detectar estudiantes que presentan riesgo de reprobar una materia a partir de su asistencia, calificaciones, tareas entregadas, participación y número de materias reprobadas anteriormente. Suponga que un árbol de decisión y una red neuronal obtienen prácticamente la misma precisión.**

**¿Qué otros factores tomaría en cuenta para elegir uno de los dos modelos? Justifique su respuesta.**

Tomaría en cuenta principalmente la interpretabilidad del modelo, la facilidad para explicárselo a los maestros y los recursos que necesito para mantenerlo funcionando, así que elegiría el árbol de decisión porque si ambos tienen la misma precision pero el árbol permite ver claramente la causa del problema

---

## Pregunta 8

**Un hospital desarrolla un sistema para determinar qué pacientes necesitan atención prioritaria utilizando edad, temperatura, presión arterial, frecuencia cardiaca, síntomas y antecedentes médicos. Una red neuronal obtiene mejores resultados que un árbol de decisión, pero resulta más difícil explicar cómo obtuvo su respuesta.**

**¿Considera que la mayor precisión es suficiente para elegir la red neuronal? Analice las consecuencias que podría tener esta decisión.**

No considero que una mayor precisión sea suficiente para elegir la red neuronal, ya que en el área médica están en juego vidas humanas y los doctores necesitan confiar plenamente en el criterio del sistema para tomar decisiones críticas, entonces confiar a ciegas en un modelo que no se puede explicar podría traer consecuencias muy graves

---

## Pregunta 9

**Una empresa de reparto quiere predecir si un pedido llegará tarde considerando distancia, tráfico, clima, hora del día, cantidad de pedidos y experiencia del repartidor. Para determinado pedido, el árbol de decisión indica que llegará a tiempo mientras que la red neuronal indica que probablemente llegará tarde.**

**¿Cómo determinaría cuál de los dos modelos está realizando una mejor predicción? Explique qué información adicional debería analizar.**

Para determinar el mejor esperaría que la entrega concluya en la vida real para comparar el resultado verdadero con lo que predijo cada uno, y además analizaría el porcentaje de confianza que arrojó la red neuronal y las reglas exactas que siguió el árbol de decisión, ademas analizaría información en tiempo real que quizá el sistema no captó a fondo, como reportes recientes de accidentes viales, lluvias imprevistas o retrasos del restaurante al preparar la comida

---

## Pregunta 10

**Una empresa desarrolla dos sistemas para decidir si una persona puede recibir un crédito. El primer sistema utiliza un árbol de decisión y permite explicar claramente por qué una solicitud fue rechazada. El segundo utiliza una red neuronal multicapa y obtiene mejores resultados de predicción, pero es más difícil explicar sus decisiones.**

**Si usted fuera responsable del proyecto:**
* **¿Cuál de los dos modelos utilizaría?**
Elegiría el que de mayor claridad, es decir el árbol de decisión, pero lo ideal sería que utilizara los dos
* **¿Qué ventajas tendría su elección?**
La ventaja sería cumplir con las normas financieras como explicarle al cliente el motivo del rechazo, lo que genera confianza y evita que la empresa enfrente problemas legales
* **¿Qué riesgos tendría?**
El riesgo principal sería rechazar a algunos clientes confiables o aceptar riesgosos con mayor frecuencia que la red neuronal
* **¿Consideraría posible utilizar ambos modelos dentro del mismo sistema? Justifique su respuesta.**
Sí ya que la red neuronal podría encargarse de analizar primero todas las solicitudes para detectar riesgos sutiles y predecir la probabilidad de pago, mientras que el árbol de decisión podría servir como filtro secundario o generador de explicaciones claras sobre los casos, y así se logra un equilibrio

---

## Explicar la afirmación:

**"No existe un algoritmo de Inteligencia Artificial que sea el mejor para todos los problemas."**

Dice que cada situación del mundo real tiene necesidades distintas, donde a veces lo más importante es la precisión matemática para detectar patrones en una enorme cantidad de datos, mientras que en otros casos la interpretabilidad es indispensable para entender el porqué del resultado, entonces la elección del modelo siempre depende de la complejidad del problema y sobre todo de las consecuencias de una decisión incorrecta, ya que cometer un error en una recomendación de compras no tiene el mismo impacto que equivocarse en un diagnóstico médico o en la negación de un crédito
