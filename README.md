[![Open in Visual Studio Code](https://classroom.github.com/assets/open-in-vscode-f059dc9a6f8d3a56e377f745f24479a46679e63a5d9fe6f495e02850cd0d8118.svg)](https://classroom.github.com/online_ide?assignment_repo_id=7213786&assignment_repo_type=AssignmentRepo)
# visual-behaviors

La práctica se compone de tres partes:

1. Seguimiento visual de la pelota: El robot debe seguir una pelota. El robot debe avanzar hasta estar a un metro, aproximadamente, de la pelota. A partir de ahí, seguira orientandose hacia ella, y tratando de mantener la distancia de un metro incluso si la pelota se mueve hacia el robot. Se usará:
   1.  Un filtro de color en HSV
   2.  Una estimación de la distancia al objeto filtrado, ya sea con PointCloud o con la imagen de profundidad.
   3.  Behavior Trees para programar la lógica de control.
   4.  PIDs para la orientación y la distancia.
2. Seguimiento visual de una persona: Similar al punto anterior, pero detectando a la persona con darket_ros.
3. Comportamiento mixto: El robot debe seguir tanto a las personas como a las pelotas que perciba con la cámara, teniendo prioridad la pelota.

Entrega: Viernes 11 de Marzo.


## Seguimiento de la pelota

El *behavior tree* utilizado para el seguimiento de la pelota ha sido el siguiente:
![Image text](https://github.com/Docencia-fmrico/visual-behavior-nocom-pila/blob/main/raw/Behavior_tree_ball.png)

El funcionamiento a partir de dicho behavior tree es relativamente simple. El robot, al arrancar el código con el launcher, en un comienzo permanecerá girando sobre sí mismo hasta detectar en cámara una pelota. Dicha detección se realiza por medio de *bounding boxes* y filtrado de color, y en cuanto ocurre, el kobuki pasa a seguir a dicha pelota encontrada. Cuando está siendo captada en cámara, el código dicta al kobuki qué hacer de la siguiente forma:
1. Se calcula el centro del la bola que está siendo captada
2. El robot dependiendo de la distancia hasta la misma, se acercará hacia ella con mayor o menor velocidad, o retrocederá si está demasiado cerca
3. En caso de que la pelota se mueva o se encuentre desplazada ya hacia un lateral del kobuki, girará hacia ese mismo para centrar la imagen
4. Cuando se haya quedado a una distancia aproximada estipulada de la pelota en cámara, cesará su movimiento y se quedará esperando
5. En caso de que deje de captar en cámara a dicha bola, volverá al bucle de "búsqueda" y comenzará a girar sobre sí mismo de nuevo hasta encontrar una pelota de nuevo


## Seguimiento de una persona

El *behavior tree* empleado en este caso para el seguimiento de una pelota ha sido este:
![Image text](https://github.com/Docencia-fmrico/visual-behavior-nocom-pila/blob/main/raw/Behavior_tree_person.png)

El funcionamiento a partir de dicho behavior tree es relativamente simple. El robot, al arrancar el código con el launcher, en un comienzo permanecerá girando sobre sí mismo hasta detectar en cámara a una persona. Dicha detección se realiza por medio de *bounding boxes*, y en cuanto ocurre, el kobuki pasa a seguir a la persona que ha encontrado. Cuando alguien está siendo detectado en cámara, el código dicta al kobuki qué hacer de la siguiente forma:
1. Se calcula el centro del la "box" de la persona que hay detectada
2. El robot en función de la distancia hasta esa persona, se acercará hacia ella con mayor o menor velocidad, o retrocederá en caso de estar demasiado cerca
3. En caso de que la persona se desplace o se encuentre desplazada ya hacia un lateral del kobuki, girará hacia el mismo para centrar su imagen
4. Cuando se haya quedado a una distancia aproximada estipulada de la persona en cámara, cesará su movimiento y se quedará esperando
5. En caso de perder al sujeto que se hubiera detectado, volverá al bucle de "búsqueda" y comenzará a girar sobre sí mismo de nuevo hasta encontrar a alguien otra vez


## Comportamiento mixto

Para la versión completa del comportamiento visual del kobuki, el *behavior tree* final resultante de "combinar" los dos anteriores y adaptarlo a los requerimientos de actuación ha sido el próximo:
![Image text](https://github.com/Docencia-fmrico/visual-behavior-nocom-pila/blob/main/raw/Behavior_tree_complete.png)

El comportamiento mixto derivaría de los dos anteriores, y en su *behavior tree* ya podemos observar algunos elementos que aparecen en los árboles anteriores. En este caso el kobuki priorizará el tratar de captar una pelota en cámara, y en caso de no encontrarla buscará a una persona. Podemos diferenciar aquí entonces tres posibles modos de comportamiento:
1. En caso de no captar nada en cámara, permanecerá en un bucle comprobando a intervalos muy pequeños de tiempo si se observa una pelota o una persona en cámara. Mientras tanto también estará girando sobre sí mismo.
2. Si detecta alguna de las dos opciones mencionadas anteriormente (o una persona o una bola), pasará a un comportamiento de seguimiento igual que alguno de los dos anteriores, dependiendo del elemento que se haya captado. Si es una bola, mediante *bounding boxes* y filtrado de color, sacará su centro y la seguirá. En el caso de una persona, empleará únicamente *bounding boxes*
3. Si tanto una pelota como una persona están siendo detectadas en cámara, el kobuki priorizará el seguimiento de la bola. Si esta misma desaparece de su campo de visión y la persona sigue en él, pasará a seguir ahora a dicha persona. Si se encuentra siguiendo a la bola y desaparece de su campo de visión la persona que fuera, no cambiará su modo de actuar y continuará siguiendo la bola. Si en cualquier momento ambos elementos desaparecen de su rango de visión, pasará al bucle de "búsqueda" ya mencionado anteriormente.

El código implementado de dichos behavior trees **ha pasado** los test de roslint. 
