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


## Seguimiento de una persona

El *behavior tree* empleado en este caso para el seguimiento de una pelota ha sido este:
![Image text](https://github.com/Docencia-fmrico/visual-behavior-nocom-pila/blob/main/raw/Behavior_tree_person.png)


## Comportamiento mixto

Para la versión completa del comportamiento visual del kobuki, el *behavior tree* final resultante de "combinar" los dos anteriores y adaptarlo a los requerimientos de actuación ha sido el próximo:
![Image text](https://github.com/Docencia-fmrico/visual-behavior-nocom-pila/blob/main/raw/Behavior_tree_complete.png)
